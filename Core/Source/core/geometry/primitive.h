#pragma once

#include <dll.h>
#include "core/gfx/material.h"
#include "core/geometry/vertex.h"

namespace Core {

	class ENGINE_API Primitive {
	public:
		std::vector<Vertex> GetVertices() {
			return _vertices;
		}
		std::vector<uint32_t> GetIndices() {
			return _indices;
		}
		MaterialProperties& Properties() {
			return _materialProperties;
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
		MaterialProperties _materialProperties;
	};

	class ENGINE_API Rectangle : public Primitive {
	public:
		static Rectangle Make(float width, float height, glm::vec3 color) {

			auto rect = Rectangle();
			float halfWidth = width / 2.0f;
			float halfHeight = height / 2.0f;

			Vertex v0, v1, v2, v3;

			v0.Position = { -halfWidth, -halfHeight, 0 };
			v1.Position = { halfWidth, -halfHeight, 0 };
			v2.Position = { halfWidth, halfHeight, 0 };
			v3.Position = { -halfWidth, halfHeight, 0 };

			v0.Color = color;
			v1.Color = color;
			v2.Color = color;
			v3.Color = color;

			v0.UV = { 0, 1 };
			v1.UV = { 1, 1 };
			v2.UV = { 1, 0 };
			v3.UV = { 0, 0 };

			v0.Normal = { 0, 0, 1 };
			v1.Normal = { 0, 0, 1 };
			v2.Normal = { 0, 0, 1 };
			v3.Normal = { 0, 0, 1 };

			rect.AddVertex(v0);
			rect.AddVertex(v1);
			rect.AddVertex(v2);
			rect.AddVertex(v3);

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