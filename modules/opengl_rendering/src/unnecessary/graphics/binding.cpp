#include <unnecessary/graphics/binding.h>

namespace un {

    Identified::Identified(uint32_t id) : id(id) {}

    uint32_t Identified::getId() const {
        return id;
    }
}