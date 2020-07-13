#ifndef UNNECESSARYENGINE_RESOURCES_H
#define UNNECESSARYENGINE_RESOURCES_H

#include <string>
#include <utility>
#include <vector>
#include <map>
#include <unnecessary/resources/loaders.h>
#include <unnecessary/graphics/texture.h>
#include <unnecessary/graphics/geometry.h>

//TODO: This file should be in base, but it's currently tied to OpenGL
namespace un {

    template<typename T>
    class ResourceGroup {
    private:
        AssetLoader<T> *loader;
        std::map<AssetName, T> loaded;
    public:
        explicit ResourceGroup(AssetLoader<T> *loader) : loader(loader) {}

        T *find(const AssetName &name) {
            auto it = loaded.find(name);
            T *found;
            if (it == loaded.end()) {
                found = loaded[name] = loader->load(name);
            } else {
                found = loaded[it];
            }
            return &found;
        }
    };

    class ResourceManager {
    public:


        ///TODO: A better typedef name?
    private:
        ResourceGroup<Texture> texture;
        ResourceGroup<Geometry> geometries;
        ResourceGroup<Material> materials;

    public:
        ResourceGroup<Texture> &getTexture();

        ResourceGroup<Geometry> &getGeometries();

         ResourceGroup<Material> &getMaterials() ;
    };
}
#endif
