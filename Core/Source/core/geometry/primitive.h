#pragma once

#include <dll.h>
#include <core/geometry/vertex.h>

namespace Core {

	class ENGINE_API Primitive {
	public:
		std::vector<Vertex> GetVertices() {
			return _vertices;
		}
		std::vector<uint32_t> GetIndices() {
			return _indices;
		}
	protected:
		void AddVertex(Vertex vertex) {
			_vertices.push_back(vertex);
		}
		void AddIndex(uint32_t index) {
			_indices.push_back(index);
		}
		std::vector<Vertex> _vertices;
		std::vector<uint32_t> _indices;
	};

	class ENGINE_API Rectangle : public Primitive {
	public:
		static Rectangle Make(float width, float height, glm::vec3 color) {

			auto rect = Rectangle();
			float halfWidth = width / 2.0f;
			float halfHeight = height / 2.0f;

			rect.AddVertex(Vertex(glm::vec3(-halfWidth, -halfHeight, 0), color));
			rect.AddVertex(Vertex(glm::vec3(halfWidth, -halfHeight, 0), color));
			rect.AddVertex(Vertex(glm::vec3(halfWidth, halfHeight, 0), color));
			rect.AddVertex(Vertex(glm::vec3(-halfWidth, halfHeight, 0), color));

			rect.AddIndex(0);
			rect.AddIndex(1);
			rect.AddIndex(2);
			rect.AddIndex(2);
			rect.AddIndex(3);
			rect.AddIndex(0);

			return rect;

		}
	};

}