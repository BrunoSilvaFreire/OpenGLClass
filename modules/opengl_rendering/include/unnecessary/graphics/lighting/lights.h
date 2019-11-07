#ifndef UNNECESSARYENGINE_LIGHTS_H
#define UNNECESSARYENGINE_LIGHTS_H

#include <glm/glm.hpp>

namespace un {
    struct PointLight {
        glm::vec3 color;
        float intensity, range;
    };
}
#endif
