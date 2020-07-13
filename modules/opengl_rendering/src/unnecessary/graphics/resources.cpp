#include <unnecessary/graphics/resources.h>
#include <utility>
#include <algorithm>

namespace un {
    AssetName::AssetName(
            std::string assetNamespace,
            std::string assetName
    ) : assetName(std::move(assetName)), assetNamespace(std::move(assetNamespace)) {
    }

    bool operator<(const AssetName &lhs, const AssetName &rhs) {
        if (lhs.assetNamespace < rhs.assetNamespace) {
            return true;
        }
        if (rhs.assetNamespace < lhs.assetNamespace) {
            return false;
        }
        return lhs.assetName < rhs.assetName;
    }

    bool operator>(const AssetName &lhs, const AssetName &rhs) {
        return rhs < lhs;
    }

    bool operator<=(const AssetName &lhs, const AssetName &rhs) {
        return !(rhs < lhs);
    }

    bool operator>=(const AssetName &lhs, const AssetName &rhs) {
        return !(lhs < rhs);
    }

    ResourceGroup<Texture> &ResourceManager::getTexture() {
        return texture;
    }

    ResourceGroup<Geometry> &ResourceManager::getGeometries() {
        return geometries;
    }

    ResourceGroup<Material> &ResourceManager::getMaterials() {
        return materials;
    }
}
