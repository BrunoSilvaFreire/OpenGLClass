//
// Created by bruno on 09/01/2020.
//

#ifndef UNNECESSARYENGINE_SERIALIZATION_BACKEND_H
#define UNNECESSARYENGINE_SERIALIZATION_BACKEND_H

#include <vector>
#include <tuple>

namespace un {

    struct Serialized {
    private:
        std::vector<std::tuple<std::string, int>> ints;
        std::vector<std::tuple<std::string, float>> floats;
        std::vector<std::tuple<std::string, Serialized>> children;
    public:

    };

    class SerializationBackend {
        virtual std::string serialize(const Serialized &serialized) = 0;

        virtual Serialized deserialize(const std::string &origin) = 0;
    };
}
#endif //UNNECESSARYENGINE_SERIALIZATION_BACKEND_H
