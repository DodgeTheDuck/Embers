#pragma once

#include "asset.h"
#include "core/gl/texture.h"

namespace Core {

	class AssetTexture : public Asset, public Texture {
	public:
		AssetTexture() = default;
		AssetTexture(const std::string filePath) : Texture(filePath) {};
	};

}