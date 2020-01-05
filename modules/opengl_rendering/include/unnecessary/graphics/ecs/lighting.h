#ifndef UNNECESSARYENGINE_LIGHTING_H
#define UNNECESSARYENGINE_LIGHTING_H

#include <entityx/System.h>
#include <unnecessary/graphics/ecs/drawing.h>
#include <unnecessary/graphics/lighting/lights.h>
#include <unnecessary/ecs/common.h>

#define MAX_LIGHTS 4

namespace un {
    class LightingSystem : public entityx::System<LightingSystem> {
        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entityx::ComponentHandle<Drawable> drawableView;
            entityx::ComponentHandle<Translation> translationView;
            entityx::ComponentHandle<PointLight> pointLightView;
            for (entityx::Entity entity : entities.entities_with_components(drawableView, translationView)) {
                // Find MAX_LIGHTS nearest lights
                entityx::ComponentHandle<PointLight> hPoint;
                PositionedPointLight points[MAX_LIGHTS];
                float scores[MAX_LIGHTS];
                for (entityx::Entity lightEntity : entities.entities_with_components(hPoint)) {
                    const PointLight &light = *hPoint;
                    auto lightTranslationView = lightEntity.component<Translation>();
                    if (!lightTranslationView) {
                        continue;
                    }
                    auto pos = (*lightTranslationView).value;
                    float distance = glm::distance(pos, (*translationView).value);
                    auto attempt = light.intensity * (1.0F / distance);
                    for (int i = 0; i < MAX_LIGHTS; ++i) {
                        auto bar = scores[i];
                        if (attempt > bar) {
                            points[i] = {
                                    pos,
                                    light
                            };
                            break;
                        }
                    }
                }
                drawableView->pointLights.update(points, sizeof(points));
            }
        }
    };
}
#endif //UNNECESSARYENGINE_LIGHTING_H
