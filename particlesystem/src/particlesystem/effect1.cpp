#include <particlesystem/particlesystem1.hpp>
#include <particlesystem/effect1.hpp>

void Effect3::effect(std::vector<Particle>& Particals, const float& dt) {
        preformEffect(Particals, dt);
}

// ----- Virtual implementation -----

// Virutal instance of Field effect
void Field::preformEffect(std::vector<Particle>& Particals, const float& dt) {
    for (Particle& aParticle : Particals) {

        float fieldRadius = 0.1f;
        glm::vec2 dp = aParticle.getPosition() - position;
        float distance = sqrt(dp.x * dp.x + dp.y * dp.y);
        float vX = aParticle.getVelocity().x;
        float vY = aParticle.getVelocity().y;

        if (distance < fieldRadius && distance > fieldRadius - 0.005f) {
            aParticle.setValues(aParticle.getAcceleration(), -0.1f * aParticle.getVelocity(),
                                aParticle.getPosition());
        }
    }
}

void GravityWell::preformEffect(std::vector<Particle>& Particals, const float& dt) {
    for (Particle& aParticle : Particals) {
        glm::vec2 dp = aParticle.getPosition() - position;

        // Calculates the gravity force on the particle
        float distance = sqrt(dp.x * dp.x + dp.y * dp.y);

        float gravity = force * (distance * force);
        glm::vec2 newVelocity = (aParticle.getVelocity() -= gravity * dt * dp);
        aParticle.setValues(aParticle.getAcceleration(), newVelocity, aParticle.getPosition());
    }
}

void Wind::preformEffect(std::vector<Particle>& Particals, const float& dt) {
    float windRand = rand() / static_cast<float>(RAND_MAX) * 0.8f + 0.2f;
    for (Particle& aParticle : Particals) {
        glm::vec2 wind = aParticle.getAcceleration() +=
            windRand * 0.01f * glm::vec2(forceX, forceY);
        aParticle.setValues(wind, aParticle.getVelocity(), aParticle.getPosition());
    }
}

void GravityWell2::preformEffect(std::vector<Particle>& Particals, const float& dt) {
    for (Particle& aParticle : Particals) {
        glm::vec2 dp = aParticle.getPosition() - position;

        // Calculates the gravity force on the particle
        float distance = sqrt(dp.x * dp.x + dp.y * dp.y);

        float gravity = force / (distance * distance);
        glm::vec2 newVelocity = (aParticle.getVelocity() -= gravity * dt * dp);
        aParticle.setValues(aParticle.getAcceleration(), newVelocity, aParticle.getPosition());
    }
}
