#include <unnecessary/graphics/material.h>

namespace un {

    Material::Material(
            Shader *shader,
            std::vector<FloatProperty> floats,
            std::vector<IntProperty> ints,
            std::vector<ColorProperty> colors
    ) : floats(std::move(floats)), ints(std::move(ints)), colors(std::move(colors)), shader(shader) {}

    const std::vector<Material::FloatProperty> &Material::getFloats() const {
        return floats;
    }

    const std::vector<Material::IntProperty> &Material::getInts() const {
        return ints;
    }

    const std::vector<Material::ColorProperty> &Material::getColors() const {
        return colors;
    }

    Shader *Material::getShader() const {
        return shader;
    }
}