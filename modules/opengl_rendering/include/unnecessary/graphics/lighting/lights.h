#ifndef UNNECESSARYENGINE_LIGHTS_H
#define UNNECESSARYENGINE_LIGHTS_H

#include <glm/glm.hpp>

namespace un {
    struct PointLight {
        glm::vec3 position;
        glm::vec3 color;
        float intensity, range;

        explicit PointLight(
                const glm::vec3 &position = glm::vec3(),
                const glm::vec3 &color = glm::vec3(),
                float intensity = 0.0F,
                float range = 0.0F
        ) : position(position), color(color), intensity(intensity), range(range) {}
    };
}
#endif
