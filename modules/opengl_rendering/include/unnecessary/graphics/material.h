#ifndef OPENGL_MATERIAL_H
#define OPENGL_MATERIAL_H

#include <string>
#include <utility>
#include <vector>
#include <glm/glm.hpp>
#include <unnecessary/graphics/shaders/shader.h>
#include <unnecessary/graphics/shaders/program.h>

namespace un {


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
        un::ShaderProgram *shader;
    public:
        Material(
                Shader *shader,
                std::vector<FloatProperty> floats = {},
                std::vector<IntProperty> ints = {},
                std::vector<ColorProperty> colors = {}
        );

        const std::vector<FloatProperty> &getFloats() const;

        const std::vector<IntProperty> &getInts() const;

        const std::vector<ColorProperty> &getColors() const;

        ShaderProgram *getShader() const;
    };
}
#endif
