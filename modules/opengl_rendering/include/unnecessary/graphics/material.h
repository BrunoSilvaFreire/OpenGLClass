#ifndef OPENGL_MATERIAL_H
#define OPENGL_MATERIAL_H

#include <string>
#include <utility>
#include <vector>
#include <glm/glm.hpp>
#include <unnecessary/graphics/shaders/shader.h>
#include <unnecessary/graphics/shaders/program.h>

namespace un {

    struct TextureReference {
    private:
        std::string path;
    public:
        explicit TextureReference(std::string path = "");
    };

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
        typedef Property<TextureReference> TextureProperty;
    private:
        std::vector<FloatProperty> floats;
        std::vector<IntProperty> ints;
        std::vector<ColorProperty> colors;
        std::vector<TextureProperty> textures;
        const un::ShaderProgram *shader;
    public:
        explicit Material(
                const un::ShaderProgram *shader,
                std::vector<FloatProperty> floats = {},
                std::vector<IntProperty> ints = {},
                std::vector<ColorProperty> colors = {},
                std::vector<TextureProperty> textures = {}
        );

        const std::vector<FloatProperty> &getFloats() const;

        const std::vector<IntProperty> &getInts() const;

        const std::vector<ColorProperty> &getColors() const;

        const std::vector<TextureProperty> &getTextures() const;

        const ShaderProgram *getShaderProgram() const;
    };
}
#endif
