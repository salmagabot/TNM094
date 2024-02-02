#pragma once

#include <tracy/Tracy.hpp>
#include <rendering/window.h>

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

#include <fmt/format.h>

#include <tuple>

class Particle {

private:
    glm::vec2 acceleration;
    glm::vec2 velocity;
    glm::vec2 position;
    float lifeTime;
    float startLife = 28.5f;


public:

    Particle(glm::vec2 newAcceleration, glm::vec2 newVelocity, glm::vec2 newPosition);

    void editParticle(glm::vec2 newAcceleration, glm::vec2 newVelocity, glm::vec2 newPosition, const float& dt);

    glm::vec2 getAcceleration();

    glm::vec2 getVelocity();

    glm::vec2 getPosition();

    void setValues(glm::vec2 newAcceleration, glm::vec2 newVelocity, glm::vec2 newPosition);

    float& getLifeTime();

    float getStartLifeTime() { return startLife; }
};
