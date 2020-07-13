#include <unnecessary/graphics/gl_loaders.h>
#include <tiny_obj_loader.h>
#include <filesystem>
#include <glm/glm.hpp>

namespace un {
    uint32_t FileAssetLoader::load(const AssetName &asset) {
        auto path = std::filesystem::path("assets") / asset.assetNamespace / asset.assetName;
        return load(asset, path);
    }

    uint32_t PNGAssetLoader::load(const AssetName &asset, std::filesystem::path &path) {
        path += ".png";
        auto texture = Texture::pngPush(path);
        return texture.getId();
    }

    uint32_t OBJAssetLoader::load(const AssetName &asset, std::filesystem::path &path) {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string warn;
        std::string err;

        tinyobj::LoadObj(
                &attrib,
                &shapes,
                &materials,
                &warn, &err, file.c_str()
        );

        std::vector<glm::vec3> vData;
        auto verts = attrib.vertices;
        auto count = verts.size();
        vData.reserve(count / 3);
        for (size_t i = 0; i < count; i += 3) {
            auto x = verts[i];
            auto y = verts[i + 1];
            auto z = verts[i + 2];
            vData.emplace_back(
                    x,
                    y,
                    z

            );
        }
        std::vector<Model> models;
        for (auto &shape : shapes) {

            std::vector<uint32_t> i;
            auto &toTransform = shape.mesh.indices;
            std::transform(
                    toTransform.begin(),
                    toTransform.end(),
                    std::back_inserter(i),
                    [](const tinyobj::index_t &index) {
                        return index.vertex_index;
                    }
            );
            models.push_back(
                    {
                            vData,
                            i
                    }
            );
        }
        return models;
    }

    void gl::register_default_loaders(ResourceManager &resourceManager) {
        resourceManager.registerLoaderForNamespace("textures", new PNGAssetLoader());
        resourceManager.registerLoaderForNamespace("models", new OBJAssetLoader());
    }
}