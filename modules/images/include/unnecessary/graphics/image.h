#ifndef UNNECESSARYENGINE_IMAGE_H
#define UNNECESSARYENGINE_IMAGE_H

#include <istream>
#include <utility>
#include <lodepng.h>
#include <iostream>

namespace gl {
    class Image {
    private:
        uint32_t width, height;
        std::vector<uint8_t> buf;
    public:
        Image() = default;

        Image(uint32_t width, uint32_t height, std::vector<uint8_t> buf)
                : width(width), height(height), buf(std::move(buf)) {}

        uint32_t getWidth() const {
            return width;
        }

        uint32_t getHeight() const {
            return height;
        }

        const std::vector<uint8_t> &getPixels() const {
            return buf;
        }
    };

    class ImageFactory {
    public:
        virtual bool loadImage(std::basic_istream<uint8_t> &stream, Image &out) = 0;
    };

    class PNGImageFactory : public ImageFactory {
    public:
        bool loadImage(std::basic_istream<uint8_t> &stream, Image &out) override {
            uint32_t w = 0, h = 0;
            std::vector<uint8_t> buf;
            std::vector<uint8_t> in;
            stream.seekg(std::ios::end);
            auto size = stream.tellg();
            stream.seekg(std::ios::beg);
            in.resize(size);
            stream.read(
                    in.data(),
                    size
            );
            lodepng::State state;
            if (lodepng::decode(buf, w, h, state, in)) {
                std::cout << "Image has " << w << " & " << h << std::endl;
                out = Image(
                        w, h, buf
                );
                return true;
            }
            return false;

        }
    };

}
#endif
