#pragma once

namespace Core {

	class GraphicsState {
	public:
		virtual void Init() = 0;
		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;
		virtual void BeginPass(uint32_t passIndex) = 0;
		virtual void EndPass(uint32_t passIndex) = 0;		

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();

		void SetProjectMatrix(glm::mat4 projectionMatrix);
		void SetViewMatrix(glm::mat4 viewMatrix);

	private:

		glm::mat4 _projectionMatrix;
		glm::mat4 _viewMatrix;


	};

}