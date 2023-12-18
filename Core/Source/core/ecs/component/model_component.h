#pragma once

#include <dll.h>
#include <core/gfx/model.h>

namespace Core::Component {

	struct Model {
		// --()--
		// (____)
		//  |  |
		std::vector<Mesh> Meshes{};
		Material Material;
	};

}