#ifndef UNNECESSARYENGINE_WORLDS_H
#define UNNECESSARYENGINE_WORLDS_H

#include <entityx/entityx.h>
#include <utility>

namespace un {
    struct World {
    private:
        std::string name;
        entityx::EntityX ecs;
    public:
        explicit World(std::string name) : name(std::move(name)), ecs() {

        }
        const entityx::EntityX &getECS() const {
            return ecs;
        }
    };
}
#endif
