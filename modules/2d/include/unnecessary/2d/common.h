#ifndef UNNECESSARY_2D_COMMON_H
#define UNNECESSARY_2D_COMMON_H

#include <entityx/entityx.h>
#include <glm/fwd.hpp>
#include <glm/detail/type_mat3x3.hpp>

namespace un {
    struct Rect {
        float x, y;
        float width, height;
    };

    struct Translation2D {
        explicit Translation2D(float x = 0.0F, float y = 0.0F);

        float x, y;
    };

    struct Rotation2D {
        explicit Rotation2D(float angle = 0.0F);

        float angle;
    };

    struct Scale2D {
        explicit Scale2D(float x = 1.0F, float y = 1.0F);

        float x, y;
    };

    struct ModelToWorld2D {
        glm::mat3 value;
    };
    struct WorldToViewport {
        glm::mat3 value;
    };

    struct Transform2DSystem : entityx::System<Transform2DSystem> {
        void update(
                entityx::EntityManager &entities,
                entityx::EventManager &events,
                entityx::TimeDelta dt
        ) override;
    };
}
#endif
