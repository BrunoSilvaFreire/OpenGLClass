#ifndef UNNECESSARYENGINE_LIGHTING_H
#define UNNECESSARYENGINE_LIGHTING_H

#include <entityx/System.h>
#include <unnecessary/graphics/ecs/drawing.h>
#include <unnecessary/graphics/lighting/lights.h>
#include <unnecessary/ecs/common.h>

namespace un {
    class LightingSystem : public entityx::System<LightingSystem> {
    private:
        glm::vec3 ambient;
    public:
        explicit LightingSystem(const glm::vec3 &ambient);

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
    };
}
#endif //UNNECESSARYENGINE_LIGHTING_H
