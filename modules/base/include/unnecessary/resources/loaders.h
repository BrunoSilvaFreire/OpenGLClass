#ifndef UNNECESSARYENGINE_LOADERS_H
#define UNNECESSARYENGINE_LOADERS_H

#include <cstdint>
#include <string>

namespace un {
    struct AssetName {
    public:
        const std::string assetNamespace;
        const std::string assetName;

        AssetName(std::string assetNamespace, std::string assetName);

        friend bool operator<(const AssetName &lhs, const AssetName &rhs);

        friend bool operator>(const AssetName &lhs, const AssetName &rhs);

        friend bool operator<=(const AssetName &lhs, const AssetName &rhs);

        friend bool operator>=(const AssetName &lhs, const AssetName &rhs);
    };


    /**
     * Responible for loading a resource of type T
     */
    template<typename T>
    class AssetLoader {
        virtual T load(const AssetName &asset) = 0;
    };

}
#endif //UNNECESSARYENGINE_LOADERS_H
