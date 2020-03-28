#ifndef UNNECESSARYENGINE_LIGHTING_H
#define UNNECESSARYENGINE_LIGHTING_H

#include <entityx/System.h>
#include <unnecessary/graphics/ecs/drawing.h>
#include <unnecessary/rendering/lighting/lights.h>
#include <unnecessary/ecs/common.h>

namespace un {
#define POINT_LIGHTS_COUNT 4
#define DIRECTIONAL_LIGHTS_COUNT 2

    struct EntityLighting {

        PositionedPointLight points[POINT_LIGHTS_COUNT];
        DirectionalLight directionals[DIRECTIONAL_LIGHTS_COUNT];
        ALIGN_4F glm::vec3 ambient;

        EntityLighting() : points(), directionals(), ambient() {};

    };

    class LightingSystem : public entityx::System<LightingSystem> {
    private:
        glm::vec3 ambient;
    public:
        explicit LightingSystem(const glm::vec3 &ambient);

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
    };
}
#endif //UNNECESSARYENGINE_LIGHTING_H
