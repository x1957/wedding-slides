const bind = (e, opts) => {
    let x = opts.x;
    let y = opts.y;
    for (let idx in opts.slides) {
        let slide        = document.createElement('div');
        let slide_config = opts.slides[idx];
        e.appendChild(slide);
        slide.id = 'image_' + (idx);
        slide.classList.add('step');
        slide.classList.add('slide');
        x += slide_config.dx;
        y += slide_config.dy;
        slide.setAttribute('data-x', x);
        slide.setAttribute('data-y', y);
        slide.setAttribute('data-scale', slide_config.scale);
        if (slide_config.file) {
            let img = document.createElement('img');
            slide.appendChild(img);
            img.src = 'images/' + slide_config.file;
        };
        if (slide_config.desc && slide_config.desc.length > 0) {
            let desc = document.createElement('span');
            slide.appendChild(desc);
            desc.classList.add('text');
            desc.innerText = slide_config.desc;
        }
    };
    let obj = impress();
    obj.init();
    return {
        run: () => {
            setInterval(obj.next, opts.duration);
            let au = document.createElement('audio');
            au.src = opts.audio_file;
            document.body.appendChild(au);
            au.play();
        },
    };
};
