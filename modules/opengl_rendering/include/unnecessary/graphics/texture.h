#ifndef UNNECESSARYENGINE_TEXTURE_H
#define UNNECESSARYENGINE_TEXTURE_H

#include <istream>
#include <vector>
#include <spng.h>
#include <filesystem>
#include <fstream>
#include <unnecessary/graphics/binding.h>

namespace un {


    class Texture : public Identified {
    private:
    public:
        Texture(uint32_t id = -1) : Identified(id) {}

        static Texture pngPush(
                const std::filesystem::path &path
        ) {
            std::fstream stream(path, std::ios::binary | std::ios::ate);
            std::streampos size = stream.tellg();
            stream.seekg(std::ios::beg);
            std::vector<char> buf(size);
            int status = 0;
            spng_ctx *ctx = spng_ctx_new(0);
            spng_set_png_buffer(ctx, buf.data(), buf.size());
            size_t imgSize;
            status = spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &imgSize);
            std::vector<uint8_t> img(imgSize);
            status = spng_decode_image(ctx, img.data(), imgSize, SPNG_FMT_RGBA8, 0);

            spng_ihdr ihdr;
            spng_get_ihdr(ctx, &ihdr);

            uint32_t height = ihdr.height;
            uint32_t width = ihdr.width;
            uint32_t id;
            glGenTextures(1, &id);

// "Bind" the newly created texture : all future texture functions will modify this texture
            glBindTexture(GL_TEXTURE_2D, id);

// Give the image to OpenGL
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            return Texture(id);
        }
    };
}

#endif
