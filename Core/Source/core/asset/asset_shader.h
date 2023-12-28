#pragma once

#include "asset.h"
#include "core/gfx/shader_program.h"

namespace Core {

	class AssetShader : public Asset, public ShaderProgram {
	public:
		AssetShader() = default;
		AssetShader(const std::string vertName, const std::string fragName) : ShaderProgram(vertName, fragName) {};
		AssetShader(const std::string vertName, const std::string geomName, const std::string fragName) : ShaderProgram(vertName, geomName, fragName) {};
	};

}