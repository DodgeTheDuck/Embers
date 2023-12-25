#pragma once

#include <core/asset/asset.h>
#include <core/geometry/mesh.h>

namespace Core {
	class AssetMesh : public Asset, public Mesh {	
	public:
		AssetMesh() : Mesh() {};
		AssetMesh(Primitive& primitive) : Mesh(primitive) {};
	};
}