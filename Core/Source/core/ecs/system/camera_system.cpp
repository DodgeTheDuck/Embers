#include <stdafx.h>
#include "camera_system.h"
#include "core/engine/engine.h"
#include "core/input/keys.h"
#include "core/ecs/component/camera_component.h"
#include "core/ecs/component/transform_component.h"

namespace Core::System {

	void Camera::Init()
	{
	}
	void Camera::Tick(Ref<entt::registry> registry, double dt)
	{

		auto view = registry->view<Component::Camera, Component::Transform>();

		for (auto entity : view) {

			auto& cCamera = registry->get<Component::Camera>(entity);
			auto& cTransform = registry->get<Component::Transform>(entity);

			glm::vec3 front;
			glm::vec3 right;
			glm::vec3 up;

			front.x = cos(glm::radians(cCamera.yaw)) * cos(glm::radians(cCamera.pitch));
			front.y = sin(glm::radians(cCamera.pitch));
			front.z = sin(glm::radians(cCamera.yaw)) * cos(glm::radians(cCamera.pitch));
			front = glm::normalize(front);

			right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
			up = glm::normalize(glm::cross(right, front));

			registry->patch<Component::Transform>(entity, [dt, cCamera, front, right](Component::Transform& cTransform) {

				float walkSpeed = 1.0 * dt;
				float sprintSpeed = 10.0 * dt;
				float actualSpeed = walkSpeed;

				if (Keyboard()->GetKeyState(Input::Key::Shift)) {
					actualSpeed = sprintSpeed;
				}

				if (Keyboard()->GetKeyState(Input::Key::W)) {
					cTransform.position += front * actualSpeed;
				}
				if (Keyboard()->GetKeyState(Input::Key::S)) {
					cTransform.position -= front * actualSpeed;
				}
				if (Keyboard()->GetKeyState(Input::Key::A)) {
					cTransform.position -= right * actualSpeed;
				}
				if (Keyboard()->GetKeyState(Input::Key::D)) {
					cTransform.position += right * actualSpeed;
				}
				if (Keyboard()->GetKeyState(Input::Key::Q)) {
					cTransform.position.y += actualSpeed;
				}
				if (Keyboard()->GetKeyState(Input::Key::E)) {
					cTransform.position.y -= actualSpeed;
				}

			});

			registry->patch<Component::Camera>(entity, [dt, cTransform, front, up](Component::Camera& cCamera) {

				if (Keyboard()->GetKeyState(Input::Key::LeftArrow)) {
					cCamera.yaw -= 90.0 * dt;
				}
				if (Keyboard()->GetKeyState(Input::Key::RightArrow)) {
					cCamera.yaw += 90.0 * dt;
				}
				if (Keyboard()->GetKeyState(Input::Key::UpArrow)) {
					cCamera.pitch += 90.0 * dt;
				}
				if (Keyboard()->GetKeyState(Input::Key::DownArrow)) {
					cCamera.pitch -= 90.0 * dt;
				}

				cCamera.projection = glm::perspective(cCamera.fov, 1024.0f / 768.0f, cCamera.viewNear, cCamera.viewFar);
				cCamera.view = glm::lookAt(cTransform.position, cTransform.position + front, up);

			});

		}

	}
	void Camera::PreRender(Ref<entt::registry> registry)
	{

		auto view = registry->view<Component::Camera, Component::Transform>();

		for (auto& entity : view) {
			auto& cCamera = registry->get<Component::Camera>(entity);
			auto& cTransform = registry->get<Component::Transform>(entity);
			auto& state = Gfx()->GetPipeline()->State();
			state.SetProjectMatrix(cCamera.projection);
			state.SetViewMatrix(cCamera.view);
			state.SetCameraPosition(cTransform.position);
		}

	}
	void Camera::RenderPass(Ref<entt::registry> registry, uint32_t passIndex)
	{
	}
	void Camera::Gui(Ref<entt::registry> registry, double dt)
	{
	}
	void Camera::PostRender(Ref<entt::registry> registry)
	{
	}

}