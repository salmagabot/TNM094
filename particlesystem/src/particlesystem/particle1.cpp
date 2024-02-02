#include <particlesystem/particle1.hpp>


Particle::Particle(glm::vec2 newAcceleration, glm::vec2 newVelocity, glm::vec2 newPosition) {
    acceleration = newAcceleration;
    velocity = newVelocity;
    position = newPosition;
    lifeTime = startLife;
}

void Particle::editParticle(glm::vec2 newAcceleration, glm::vec2 newVelocity, glm::vec2 newPosition, const float& dt) {
    acceleration = newAcceleration;
    velocity = newVelocity;
    position = newPosition;
    lifeTime -= dt;
}

float& Particle::getLifeTime() { return lifeTime; }

glm::vec2 Particle::getAcceleration() { return acceleration; }

glm::vec2 Particle::getVelocity() { return velocity; }

glm::vec2 Particle::getPosition() { return position; }

void Particle::setValues(glm::vec2 newAcceleration, glm::vec2 newVelocity, glm::vec2 newPosition) {
    acceleration = newAcceleration;
    velocity = newVelocity;
    position = newPosition;
}
