#pragma once

namespace Core {

	class Vertex {
	public:
		Vertex() = default;
		Vertex(glm::vec3 position, glm::vec3 color) : position(position), color(color) {};
		glm::vec3 position;
		glm::vec3 color;
	};

}