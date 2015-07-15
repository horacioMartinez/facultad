git clone https://github.com/Itseez/opencv.git
git clone https://github.com/Itseez/opencv_contrib
mkdir -p opencv/release
cd opencv/release
cmake -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ../
make -j4
make install
sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
ldconfig
