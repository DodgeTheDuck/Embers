
#include <stdafx.h>
#include "graphics_state.h"

namespace Core {

	glm::mat4 GraphicsState::GetProjectionMatrix()
	{
		return _projectionMatrix;
	}

	glm::mat4 GraphicsState::GetViewMatrix()
	{
		return _viewMatrix;
	}

	glm::vec3 GraphicsState::GetCameraPosition()
	{
		return _cameraPos;
	}

	void GraphicsState::SetProjectMatrix(glm::mat4 projectionMatrix)
	{
		_projectionMatrix = projectionMatrix;
	}

	void GraphicsState::SetViewMatrix(glm::mat4 viewMatrix)
	{
		_viewMatrix = viewMatrix;
	}

	void GraphicsState::SetCameraPosition(glm::vec3 cameraPos)
	{
		_cameraPos = cameraPos;
	}

}