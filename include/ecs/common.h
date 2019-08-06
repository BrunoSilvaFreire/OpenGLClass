#ifndef OPENGL_COMMON_H
#define OPENGL_COMMON_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <entityx/System.h>

namespace gl {
    struct Translation {
        glm::vec3 value;
    };
    struct Rotation {
        glm::quat value;
    };
    struct Scale {
        glm::vec3 value;
    };
    struct ModelToWorld {
        glm::mat4 value;
    };
    struct Camera {

    };

}

#endif
