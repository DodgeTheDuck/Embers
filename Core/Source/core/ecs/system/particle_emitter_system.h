#pragma once

#include "system.h"
#include "core/geometry/mesh.h"

#define MAX_PARTICLES 128000

namespace Core::System {



	class ParticleEmitter : public System {

	private:
		struct Particle {
			uint32_t id{};
			float lifeStartSeconds{};
			float lifeSeconds{};
			glm::mat4 transform;
			glm::vec3 velocity;
			glm::vec3 acceleration;
		};

	public:
		void Init() override;
		void Tick(Ref<entt::registry> registry, double dt) override;
		void PreRender(Ref<entt::registry> registry) override;
		void RenderPass(Ref<entt::registry> registry, uint32_t renderPass) override;
		void Gui(Ref<entt::registry> registry, double dt) override;
		void PostRender(Ref<entt::registry> registry) override;

		static void IncParticle();
		static void DecParticle();

	private:

		void _TickEmitters(Ref<entt::registry> registry, double dt);
		void _TickParticles(Ref<entt::registry> registry, double dt);

		void _RenderParticles();

		void _UpdateParticleIndexRange(uint32_t index);
		void _RemoveParticle(uint32_t particleId);
		void _AddParticle(Particle p);

		static unsigned int _nParticles;
		Mesh _mesh;
		uint32_t _batch;
		std::array<Particle, MAX_PARTICLES> _particles;
		std::queue<uint32_t> _particleQueue;
		uint32_t _minParticleIndex;
		uint32_t _maxParticleIndex;

	};

}