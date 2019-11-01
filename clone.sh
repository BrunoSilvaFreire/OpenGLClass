git clone https://github.com/BrunoSilvaFreire/TheUnnecessaryEngine
cd TheUnnecessaryEngine || exit
git submodule update --init
cd glew/auto || exit
make
cd ../..
cmake -H. -Bcmake-build-debug
cd cmake-build-debug || exit
cmake --build .
./dummy_app/dummy_app