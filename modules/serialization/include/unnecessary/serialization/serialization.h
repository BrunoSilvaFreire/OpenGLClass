#ifndef UNNECESSARYENGINE_SERIALIZATION_H
#define UNNECESSARYENGINE_SERIALIZATION_H

#include <vector>
#include <cstdint>
#include <unnecessary/serialization/json_backend.h>

namespace un {


    class Serialization {
    private:
        uint32_t priority = -1;
        std::vector<SerializationBackend *> backends;
    public:

        SerializationBackend *getPreferredBackend() {
            if (priority < backends.size()) {

            }
            return nullptr;
        }

        template<typename T>
        T *getSerializationBackend() {
            T *result = nullptr;
            for (SerializationBackend *bk : backends) {
                if ((result = dynamic_cast<T *>(bk)) != nullptr) {
                    break;
                }
            }
            return result;
        }
    };
}
#endif
