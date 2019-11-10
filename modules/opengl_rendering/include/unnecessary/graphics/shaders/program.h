#ifndef OPENGL_PROGRAM_H
#define OPENGL_PROGRAM_H

#include <unnecessary/graphics/shaders/shader.h>

namespace un {

    class ShaderProgram {
    public:
        struct ShaderIndices {
            uint32_t mvp{};
            uint32_t model{};
            uint32_t lights{};

            ShaderIndices();

            ShaderIndices(
                    uint32_t mvp,
                    uint32_t lights
            );

        };

    private:
        ShaderIndices indices;
        uint32_t id;
        uint32_t vShader;
        uint32_t fShader;
        uint32_t gShader;
    public:
        explicit ShaderProgram(
                const un::Shader &shader,
                const std::string &mvpName,
                const std::string &lightsName,
                const std::string &modelName
        );

        uint32_t getId() const;

        uint32_t getVShader() const;

        uint32_t getFShader() const;

        const ShaderIndices &getIndices() const;
    };
}
#endif
