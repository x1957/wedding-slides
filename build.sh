set -e

cd `dirname $0`
W=`pwd`

PATH=$HOME/local/cmake/bin:$PATH

mkdir -p .build
cd .build
cmake .. -DCMAKE_BUILD_TYPE=Release
make

mkdir -p $W/bin
cp bin/* $W/bin
echo 'done'
