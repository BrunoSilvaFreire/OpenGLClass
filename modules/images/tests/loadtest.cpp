#include <unnecessary/graphics/image.h>
#include <fstream>
#include <iostream>

int main() {

    gl::PNGImageFactory factory;
    gl::Image img;
    std::basic_ifstream<unsigned char> st(
            "/home/bruno/CLionProjects/OpenGLClass/modules/images/tests/chungus.png"
    );
    if (factory.loadImage(st, img)) {
        std::cout << "gg" << std::endl;
    } else {
        std::cout << "ohno" << std::endl;
    }
}