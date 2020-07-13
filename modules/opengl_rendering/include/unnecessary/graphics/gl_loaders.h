#ifndef UNNECESSARYENGINE_GL_LOADERS_H
#define UNNECESSARYENGINE_GL_LOADERS_H

#include <filesystem>
#include <unnecessary/resources/loaders.h>
#include <unnecessary/graphics/texture.h>
#include <unnecessary/graphics/resources.h>

namespace un {
    class FileAssetLoader : public AssetLoader {
        virtual uint32_t load(const AssetName &asset, std::filesystem::path &path) = 0;

        uint32_t load(const AssetName &asset) override;
    };

    class PNGAssetLoader : public FileAssetLoader {
        uint32_t load(const AssetName &asset, std::filesystem::path &path) override;
    };

    class OBJAssetLoader : public FileAssetLoader {
        uint32_t load(const AssetName &asset, std::filesystem::path &path) override;
    };

    namespace gl {
        void register_default_loaders(ResourceManager &resourceManager);
    }
}
#endif
