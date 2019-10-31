#ifndef UNNECESSARYENGINE_RENDERING_H
#define UNNECESSARYENGINE_RENDERING_H

#include <entityx/System.h>
#include <glm/glm.hpp>
#include <unnecessary/graphics/geometry.h>
#include <unnecessary/application.h>

namespace gl {
    struct LightPoint {
        float intensity, range;
        glm::vec3 color;
    };

    struct Camera {
        float fieldOfView, nearPlane, farPlane;
        glm::mat4 projection;
    };

    struct Drawable {
        std::string mvpName;
        Geometry geometry;
    };

    struct RenderingSystem : entityx::System<RenderingSystem> {
    private:
        GLFWwindow *wnd;
    public:
        explicit RenderingSystem(GLFWwindow *wnd);

#define PI 3.14159265359F
#define RAD_TO_DEGREE 57.2957795F
#define DEG_TO_RAD 0.0174533F

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;

    };
    namespace gl_rendering {
        void register_default_systems(gl::Application &app);
    }
}

#endif