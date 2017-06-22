#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

std::string basename(const std::string &name)
{
    const auto idx = name.find_last_of('/');
    if (idx == std::string::npos) {
        return name;
    }
    return name.substr(idx + 1);
}

std::string trim_ext(const std::string &name)
{
    const auto idx = name.find_last_of('.');
    if (idx == std::string::npos) {
        return name;
    }
    return name.substr(0, idx);
}

template <typename T> T gcd(const T a, const T b)
{
    const T r = a % b;
    return r ? gcd(b, r) : b;
}

void info(const cv::Mat &img)
{
    const auto s = img.size();
    std::cout << "type: " << img.type() << std::endl
              << "channels: " << img.channels() << std::endl
              << "depth: " << img.depth() << std::endl
              << "CV_8U: " << CV_8U << std::endl
              << "size: " << s.height << " X " << s.width << std::endl;
}

struct rational {
    const int64_t a, b; // r = a / b

    rational(int64_t a, int64_t b) : a(a), b(b) {}

    rational reduced() const
    {
        int64_t d = gcd(a, b);
        return rational(a / d, b / d);
    }
};

bool operator<(const rational &r, const rational &s)
{
    return r.a * s.b < r.b * s.a;
}

struct normalizer {
    const cv::Size bound;

    normalizer(const cv::Size &bound) : bound(bound) {}

    cv::Mat operator()(const cv::Mat &img) const
    {
        const auto     size = img.size();
        const auto     r1   = rational(bound.width, size.width);
        const auto     r2   = rational(bound.height, size.height);
        const auto     r    = r1 < r2 ? r1 : r2;
        const cv::Size new_size(size.width * r.a / r.b,
                                size.height * r.a / r.b);
        cv::Mat dst(new_size, CV_8UC(3));
        cv::resize(img, dst, dst.size(), 0, 0);
        return dst;
    }
};

cv::Mat normalize(const cv::Mat &img)
{
    const cv::Size   bound(1920, 1080);
    const normalizer normalize(bound);
    return normalize(img);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage:\n\t%s <filename>\n", argv[0]);
    }
    const std::string name(argv[1]);
    const auto        base     = trim_ext(basename(name));
    const auto        png_name = base + ".png";
    const auto        new_name = "www/images/" + base + ".jpg";

    std::cout << name << " -> " << new_name << std::endl;
    cv::Mat img = cv::imread(name);
    info(img);
    img = normalize(img);
    info(img);
    cv::imwrite(new_name, img);

    return 0;
}
