#pragma once

#include <dll.h>
#include "asset.h"

namespace Core {

    // AssetManager class template
    class ENGINE_API AssetManager {
    public:
        // Function to get an asset by name and type
        template <typename T>
        Ref<T>  GetAsset(const std::string& name) const {
            auto it = _assets.find(name);
            if (it != _assets.end()) {
                // Cast the base Asset pointer to the desired type
                return std::dynamic_pointer_cast<T>(it->second);
            }
            Error::Exit(L"asset not found");
        }

        template <typename T>
        T CopyAsset(const std::string& name) const {
            auto it = _assets.find(name);
            if (it != _assets.end()) {
                // Use std::dynamic_pointer_cast to cast the base Asset pointer to the desired type
                Ref<T> assetPtr = std::dynamic_pointer_cast<T>(it->second);

                if (assetPtr) {
                    // Return a copy of the asset
                    return *assetPtr;
                }
            }
            // Return a default-constructed object if the asset is not found or cannot be cast to the desired type
            Error::Exit(L"asset not found");
        }

        // Function to add an asset to the manager
        template <typename T>
        void AddAsset(const std::string& name, Ref<T> asset) {
            _assets[name] = std::move(asset);
        }

    private:

        // Using unordered_map to store assets by name
        std::unordered_map<std::string, Ref<Asset>> _assets;

    };

}