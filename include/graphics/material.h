#ifndef OPENGL_MATERIAL_H
#define OPENGL_MATERIAL_H

#include <string>
#include <utility>
#include <vector>
#include <glm/glm.hpp>
#include <graphics/shaders/shader.h>

namespace gl {


    class Material {
    public:
        template<typename T>
        struct Property {
            std::string key;
            T value;
        };
        typedef Property<float> FloatProperty;
        typedef Property<int> IntProperty;
        typedef Property<glm::vec4> ColorProperty;
    private:
        std::vector<FloatProperty> floats;
        std::vector<IntProperty> ints;
        std::vector<ColorProperty> colors;
        gl::Shader *shader;
    public:
        Material(
                Shader *shader,
                std::vector<FloatProperty> floats = {},
                std::vector<IntProperty> ints = {},
                std::vector<ColorProperty> colors = {}
        ) : floats(std::move(floats)), ints(std::move(ints)), colors(std::move(colors)), shader(shader) {}

        const std::vector<FloatProperty> &getFloats() const {
            return floats;
        }

        const std::vector<IntProperty> &getInts() const {
            return ints;
        }

        const std::vector<ColorProperty> &getColors() const {
            return colors;
        }

        Shader *getShader() const {
            return shader;
        }
    };
}
#endif
