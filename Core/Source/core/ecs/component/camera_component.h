#pragma once

#include "dll.h"

namespace Core::Component {

	struct ENGINE_API Camera {	
		float fov;
		float viewNear;
		float viewFar;
		float pitch;
		float yaw;
		glm::mat4 projection;
		glm::mat4 view;
	};

}