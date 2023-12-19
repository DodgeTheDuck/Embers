#pragma once

namespace Core::Component {

	struct ParticleEmitter {

		// Lifetime
		double		lifeTimeS;

		// Timing
		double		emitAccumulator;
		double		emitPerSec;

		// Physics
		float		emitVelocityMin;
		float		emitVelocityMax;
		glm::vec3	emitDirection;
		float		emitDirectionVariance;

		// Visuals
		glm::vec3	emitColorMin;
		glm::vec3	emitColorMax;

		glm::vec3	partColorEnd;

	};

}
