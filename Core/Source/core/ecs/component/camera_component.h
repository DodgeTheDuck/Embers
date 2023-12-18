#pragma once

namespace Core::Component {

	struct Camera {
		float fov;
		float viewNear;
		float viewFar;
		float pitch;
		float yaw;
		glm::mat4 projection;
		glm::mat4 view;
	};

}