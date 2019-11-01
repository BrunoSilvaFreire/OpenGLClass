#ifndef OPENGL_PROGRAM_H
#define OPENGL_PROGRAM_H

#include <unnecessary/graphics/shaders/shader.h>

namespace un {

    class ShaderProgram {
    private:
        uint32_t id;
        uint32_t vShader;
        uint32_t fShader;
        uint32_t gShader;
    public:
        explicit ShaderProgram(
                const un::Shader &shader
        );

        uint32_t getId() const;

        uint32_t getVShader() const;

        uint32_t getFShader() const;
    };
}
#endif
