

#ifndef UNNECESSARYENGINE_RENDERING_COMPONENTS_H
#define UNNECESSARYENGINE_RENDERING_COMPONENTS_H

#include <glm/glm.hpp>

namespace un {
    struct Camera {
        float fieldOfView, nearPlane, farPlane;
        glm::mat4 projection;
    };

}
#endif
