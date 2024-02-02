#include <particlesystem/emitter1.hpp>
#include <particlesystem/particlesystem1.hpp>

std::vector<Particle> Emitter3::emit() {
    return preformEmit();
}

std::vector<Particle> Uniform::preformEmit() {

    std::vector<Particle> theNewParticles = std::vector<Particle>();

    std::vector<glm::vec2> accelerations = std::vector<glm::vec2>();
    std::vector<glm::vec2> velocitys = std::vector<glm::vec2>();
    std::vector<glm::vec2> positions = std::vector<glm::vec2>();
    ++tickTimer;

        if (tickTimer == 100) {

            tickTimer = 0;
            double PI = 3.141592;
            double nrOfParticals = 64.0;
            float starAcceleration = 0.1f;
            float randome1 = 0.0f;
            float randome2 = 0.0f;

            glm::vec2 directionAcceleration(0.0, 0.0);

            for (double angle = 0; angle < 2 * PI; angle += 2 * PI / nrOfParticals) {
                randome1 = (rand() / static_cast<float>(RAND_MAX)) * 0.6f;
                randome2 = (rand() / static_cast<float>(RAND_MAX)) * 0.6f;

                directionAcceleration = glm::vec2(starAcceleration * cos(angle + randome1),
                                                  starAcceleration * sin(angle + randome2));
                accelerations.push_back(directionAcceleration);
                velocitys.push_back(glm::vec2(0.0, 0.0));
                positions.push_back(position);
            }

            for (auto index = 0; index < accelerations.size(); ++index) {
                Particle aPartical =
                    Particle(accelerations[index], velocitys[index], positions[index]);
                theNewParticles.push_back(aPartical);
            }
        }
        return theNewParticles;
}

std::vector<Particle> Directional::preformEmit() {

    std::vector<Particle> theNewParticles = std::vector<Particle>();

    float starAcceleration = 0.5f;
    glm::vec2 acceleration = glm::vec2(1.0, 1.0);
    glm::vec2 velocity = glm::vec2(0.0, 0.0);
    float randome1 = (rand() / static_cast<float>(RAND_MAX)) * 0.2f;
    float randome2 = (rand() / static_cast<float>(RAND_MAX)) * 0.2f;

    glm::vec2 directionAcceleration = glm::vec2(starAcceleration * cos(angle + randome1),
                                                starAcceleration * sin(angle + randome2));  //

    Particle aPartical =
        Particle(acceleration * directionAcceleration, velocity, position);

    theNewParticles.push_back(aPartical);

    return theNewParticles;
}


