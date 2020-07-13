#ifndef UNNECESSARYENGINE_DRAWING_H
#define UNNECESSARYENGINE_DRAWING_H

#include <entityx/System.h>
#include <glm/glm.hpp>
#include <unnecessary/graphics/geometry.h>
#include <unnecessary/graphics/buffers/uniform_buffer.h>
#include <unnecessary/application.h>

namespace un {

    struct Camera {
        float fieldOfView, nearPlane, farPlane;
        glm::mat4 projection;
    };

    struct Drawable {
    public:
        static Drawable create(Geometry *geom) {
            auto buf = UniformBuffer::create();
            return {
                    geom,
                    buf
            };
        }

        Geometry *geometry;
        UniformBuffer pointLights;
    };

    struct DrawableLoadingSystem
            : entityx::System<DrawableLoadingSystem>, public entityx::Receiver<entityx::ComponentAddedEvent<Drawable>> {
    private:
        ResourceManager *resourceManager;
    public:
        void receive(const entityx::ComponentAddedEvent<Drawable> & event);

        void configure(entityx::EventManager &events) override;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
    };

    struct DrawingSystem : entityx::System<DrawingSystem> {
    private:
        GLFWwindow *wnd;
    public:
        explicit DrawingSystem(GLFWwindow *wnd);

#define PI 3.14159265359F
#define RAD_TO_DEGREE 57.2957795F
#define DEG_TO_RAD 0.0174533F

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;

    };

}

#endif