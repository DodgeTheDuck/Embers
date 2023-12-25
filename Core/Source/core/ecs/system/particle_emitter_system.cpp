#include <stdafx.h>
#include "particle_emitter_system.h"
#include "core/asset/asset_mesh.h"
#include "core/asset/asset_shader.h"
#include "core/engine/engine.h"
#include "core/ecs/component/particle_emitter_component.h"
#include "core/ecs/component/physics_component.h"
#include "core/ecs/component/transform_component.h"

/*
* TODO:  
*	in progress - Don't use particles as an entity. Too slow. Have emitter own it's own particles.
*   not started - work out an efficient way to only draw particles that exist
* 
* 
*/

namespace Core::System {		

	unsigned int ParticleEmitter::_nParticles = 0;

	void ParticleEmitter::Init()
	{
		_batch = Gfx()->RegisterBatch(
			Core::Assets()->CopyAsset<Core::AssetMesh>("mesh_rect"),
			Material(Core::Assets()->CopyAsset<Core::AssetShader>("shader_particle_instanced"))
		);

		for (uint32_t i = 1; i < MAX_PARTICLES; i++) {
			_particleQueue.push(i);
		}
		
	}

	void ParticleEmitter::Tick(Ref<entt::registry> registry, double dt)
	{
		_TickEmitters(registry, dt);
		_TickParticles(registry, dt);
	}

	void ParticleEmitter::PreRender(Ref<entt::registry> registry)
	{
		_RenderParticles();
	}

	void ParticleEmitter::RenderPass(Ref<entt::registry> registry, uint32_t renderPass)
	{				
		if (ParticleEmitter::_nParticles > 0) {
			Gfx()->SubmitBatch(_batch);
		}
	}

	void ParticleEmitter::Gui(Ref<entt::registry> registry, double dt)
	{

		bool open;
		ImGui::Begin("Particle System", &open, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text((std::string("Particle Count: ") + std::to_string(ParticleEmitter::_nParticles)).c_str());
		ImGui::Text((std::string("Free Indices: ") + std::to_string(_particleQueue.size())).c_str());
		ImGui::End();

	}

	void ParticleEmitter::PostRender(Ref<entt::registry> registry)
	{

	}

	void ParticleEmitter::IncParticle()
	{
		ParticleEmitter::_nParticles++;
	}

	void ParticleEmitter::DecParticle()
	{
		ParticleEmitter::_nParticles--;
	}

	void ParticleEmitter::_TickEmitters(Ref<entt::registry> registry, double dt)
	{

		auto view = registry->view<Component::ParticleEmitter, Component::Transform>();
		for (auto entity : view) {

			auto& cParticleEmitter = registry->get<Component::ParticleEmitter>(entity);
			auto& cTransform = registry->get<Component::Transform>(entity);

			double totalAcc = cParticleEmitter.emitAccumulator + dt;

			if (totalAcc >= 1.0 / cParticleEmitter.emitPerSec) {

				int nSpawn = (int)round(totalAcc / (1.0 / cParticleEmitter.emitPerSec));

				for (int i = 0; i < nSpawn; i++) {

					double initialVelocity = cParticleEmitter.emitVelocityMin + ((double)rand() / RAND_MAX) * (cParticleEmitter.emitVelocityMax - cParticleEmitter.emitVelocityMin);
					double dirVarianceX = ((double)rand() / RAND_MAX) * (cParticleEmitter.emitDirectionVariance * 2) - cParticleEmitter.emitDirectionVariance;
					double dirVarianceY = ((double)rand() / RAND_MAX) * (cParticleEmitter.emitDirectionVariance * 2) - cParticleEmitter.emitDirectionVariance;
					double dirVarianceZ = ((double)rand() / RAND_MAX) * (cParticleEmitter.emitDirectionVariance * 2) - cParticleEmitter.emitDirectionVariance;

					glm::vec3 initialDir = glm::vec3(
						cParticleEmitter.emitDirection.x + glm::radians(dirVarianceX),
						cParticleEmitter.emitDirection.y + glm::radians(dirVarianceY),
						cParticleEmitter.emitDirection.z + glm::radians(dirVarianceZ)
					);

					initialDir = glm::normalize(initialDir);

					Particle p;
					p.id = _particleQueue.front(); //NOTE: create a "next id" thing to make this better
					p.transform = glm::translate(cTransform.position) * glm::scale(glm::vec3(0.1, 0.1, 0.1));
					p.lifeSeconds = cParticleEmitter.lifeTimeS;
					p.lifeStartSeconds = cParticleEmitter.lifeTimeS;
					p.velocity = initialDir * glm::vec3(initialVelocity);					

					_AddParticle(p);

					totalAcc -= 1.0 / cParticleEmitter.emitPerSec;

					ParticleEmitter::IncParticle();

				}
			}

			registry->patch<Component::ParticleEmitter>(entity, [totalAcc](Component::ParticleEmitter& em) {
				em.emitAccumulator = totalAcc;
			});

		}

	}

	void ParticleEmitter::_TickParticles(Ref<entt::registry> registry, double dt)
	{
		for (uint32_t i = _minParticleIndex; i < _maxParticleIndex; i++) {
			auto& p = _particles[i];
			if (p.id == 0) continue;

			double lifeTotal = p.lifeSeconds - dt;
			if (lifeTotal <= 0) {				
				_RemoveParticle(p.id);
			}
			else {				
				p.lifeSeconds = lifeTotal;
			}
			p.velocity.y -= 9.87 * dt;
			p.transform *= glm::translate(p.velocity);

		}
	}

	void ParticleEmitter::_RenderParticles()
	{
		auto gfx = Gfx();
		for (uint32_t i = _minParticleIndex; i < _maxParticleIndex; i++) {
			if (_particles[i].id == 0) continue;
			gfx->PostToBatch(_batch, _particles[i].transform);
		}
	}

	void ParticleEmitter::_UpdateParticleIndexRange(uint32_t index)
	{
		if (index < _minParticleIndex) _minParticleIndex = index;
		if (index > _maxParticleIndex) _maxParticleIndex = index;
	}

	void ParticleEmitter::_RemoveParticle(uint32_t particleId)
	{		
		_particles[particleId].id = 0;
		_particleQueue.push(particleId);
		ParticleEmitter::DecParticle();
	}

	void ParticleEmitter::_AddParticle(Particle p)
	{
		_particles[p.id] = p;
		_particleQueue.pop();
		_UpdateParticleIndexRange(p.id);
	}

}