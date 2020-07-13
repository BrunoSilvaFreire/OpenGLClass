#include <unnecessary/graphics/material.h>

#include <utility>

namespace un {

    Material::Material(
            const un::ShaderProgram *shader,
            std::vector<FloatProperty> floats,
            std::vector<IntProperty> ints,
            std::vector<ColorProperty> colors,
            std::vector<TextureProperty> textures
    ) : shader(shader),
        floats(std::move(floats)),
        ints(std::move(ints)),
        colors(std::move(colors)),
        textures(std::move(textures)) {}

    const std::vector<Material::FloatProperty> &Material::getFloats() const {
        return floats;
    }

    const std::vector<Material::IntProperty> &Material::getInts() const {
        return ints;
    }

    const std::vector<Material::ColorProperty> &Material::getColors() const {
        return colors;
    }

    const ShaderProgram *Material::getShaderProgram() const {
        return shader;
    }

    const std::vector<Material::TextureProperty> &Material::getTextures() const {
        return textures;
    }

    TextureReference::TextureReference(std::string path) : path(std::move(path)) {}
}