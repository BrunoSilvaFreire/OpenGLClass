#include <unnecessary/graphics/material.h>

namespace un {

    Material::Material(
            const ShaderProgram *shader,
            std::vector<FloatProperty> floats,
            std::vector<IntProperty> ints,
            std::vector<ColorProperty> colors
    ) : shader(shader),
        floats(std::move(floats)),
        ints(std::move(ints)),
        colors(std::move(colors)) {}

    const std::vector<Material::FloatProperty> &Material::getFloats() const {
        return floats;
    }

    const std::vector<Material::IntProperty> &Material::getInts() const {
        return ints;
    }

    const std::vector<Material::ColorProperty> &Material::getColors() const {
        return colors;
    }

    const ShaderProgram * Material::getShaderProgram() const {
        return shader;
    }
}