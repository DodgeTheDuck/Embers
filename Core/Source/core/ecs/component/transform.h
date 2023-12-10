#pragma once

namespace Core::Component {

	struct Transform {

		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		Transform() {
			position = glm::vec3(0.0f);
			rotation = glm::quat();
			scale = glm::vec3(1.0f);
		}

		glm::mat4 Matrix() {
			return
				glm::translate(position) *
				glm::mat4_cast(rotation) *
				glm::scale(scale);
		}

	};

}