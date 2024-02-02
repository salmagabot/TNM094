#include <particlesystem/particlesystem1.hpp>

particleSystem::particleSystem() {
    //Emitters2 = std::vector<Emitter2*>();  // den nya :) som inte fungerar :(
    //Effects2 = std::vector<Effect2*>();
    Effects3 = std::vector<Effect3*>();
    Emitters3 = std::vector<Emitter3*>();
    Particles = std::vector<Particle>();
    //counter = 0;
}

#if 0
 void particleSystem::deleteEmitter(int index) {
    if (index > 1 && index < Emitters2.size()) {
            Emitters2.erase(Emitters2.begin() +index);
        }
    }
#endif

  void particleSystem::deleteEmitter3(int index) {
        if (index > 1 && index < Emitters3.size()) {
            Emitters3.erase(Emitters3.begin() + index);
        }
    }
 #if 0
 void particleSystem::deleteEffect(int index) {
        if (index > 1 && index < Effects2.size()) {
            Effects2.erase(Effects2.begin() + index);
        }
    }
#endif
  void particleSystem::deleteEffect3(int index) {
        if (index > 1 && index < Effects3.size()) {
            Effects3.erase(Effects3.begin() + index);
        }
    }

void particleSystem::renderSystem(rendering::Window& theWindow) {

    std::vector<glm::vec2> positions;
    std::vector<glm::vec4> colors;
    glm::vec4 testColor(0.0f, 0.8f, 0.95f, 1.0f);
    float testRadius = 0.0f;
    

    std::for_each(Particles.begin(), Particles.end(), [&](Particle p) {
        positions.push_back(p.getPosition());
        colors.push_back(glm::vec4(0.8f * std::min((p.getStartLifeTime()  - 5.0f*p.getLifeTime()), 1.0f),
                                   rand() / static_cast<float>(RAND_MAX) * 0.78f + 0.02f,
                                   rand() / static_cast<float>(RAND_MAX) *0.25f + 0.7f, 1.0f));
    });

    std::vector<float> radius(positions.size(), 2.8f);

    theWindow.drawPoints(positions, radius, colors);

    positions = std::vector<glm::vec2>();
    std::for_each(Emitters3.begin(), Emitters3.end(),
                  [&](Emitter3* e) { positions.push_back((*e).getPosition()); });

    testColor = glm::vec4(1.0, 0.64, 0.0, 0.8);
    radius = std::vector<float>(positions.size(), 6.0f);
    colors = std::vector<glm::vec4>(positions.size(), testColor);

    theWindow.drawPoints(positions, radius, colors);

    positions = std::vector<glm::vec2>();


    std::for_each(Effects3.begin(), Effects3.end(), [&](Effect3* e) {
        if ((*e).hasPosition()) {
            positions.push_back((*e).getPosition());
        }
    });

    testColor = glm::vec4(1.0, 0.1, 0.0, 0.8);
    radius = std::vector<float>(positions.size(), 6.0f);
    colors = std::vector<glm::vec4>(positions.size(), testColor);

    theWindow.drawPoints(positions, radius, colors);


}

    void particleSystem::emitSystem(const float& dt) {
    std::vector<Particle> emittedParticels;
        for (Emitter3* aEmitter3Ptr : Emitters3) {
            
            emittedParticels = (*aEmitter3Ptr).emit();

            addToSystem(emittedParticels);
        }
    }

#if 0
void particleSystem::addToSystem(Emitter2* aEmitter2) {
    Emitters2.push_back(aEmitter2);
}

void particleSystem::addToSystem(Effect2* aEffect2) { Effects2.push_back(aEffect2); }
#endif
    void particleSystem::addToSystem( Particle& aParticle) { Particles.push_back(aParticle); }

void particleSystem::addToSystem( std::vector<Particle>& vectorOfParticles) {
    for (Particle aParticle : vectorOfParticles) {
        addToSystem(aParticle);
    }
};

std::vector<Particle>& particleSystem::getParticles() { return Particles; }

std::tuple<glm::vec2, glm::vec2, glm::vec2> particleSystem::eulerAprox(glm::vec2& acceleration1,
                                                                       glm::vec2& velocity0,
                                                                       glm::vec2& possition0,
                                                                       const float& dt) {
    glm::vec2 velocity1 = velocity0 + dt * acceleration1;
    glm::vec2 possition1 = possition0 + dt * velocity1;

    return std::tuple<glm::vec2, glm::vec2, glm::vec2>(acceleration1, velocity1, possition1);
}

void particleSystem::uppdateParticels(const float& dt) {
    std::vector<Particle>& theParticles = getParticles();
    int particleIndex = 0;
    glm::vec2 acceleration(0.0);
    glm::vec2 velocity(0.0);
    glm::vec2 possition(0.0);

    std::tuple<glm::vec2, glm::vec2, glm::vec2, glm::vec4> theParticleValue;
    std::tuple<glm::vec2, glm::vec2, glm::vec2> theNEWParticleValue;

      for (Effect3* aEffectPtr : Effects3) {
        (*aEffectPtr).effect(Particles, dt);
    }

    for (Particle& aPartical : Particles) {
        acceleration = aPartical.getAcceleration();
        velocity = aPartical.getVelocity();
        possition = aPartical.getPosition();

        if (aPartical.getLifeTime() > 0) {

            theNEWParticleValue = eulerAprox(acceleration, velocity, possition, dt);
            Particles[particleIndex].editParticle(
                get<0>(theNEWParticleValue), get<1>(theNEWParticleValue),
                get<2>(theNEWParticleValue), dt);
            ++particleIndex;
        } else {
            Particles.erase(Particles.begin() + particleIndex);
        }
    }
}

void particleSystem::display() {
    glm::vec2 acceleration(0.0, 0.0);
    glm::vec2 velocity(0.0, 0.0);
    glm::vec2 position(0.0, 0.0);
    int counter = 0;
    std::cout << "Particles" << std::endl;
    for (auto aParticle : Particles) {
        acceleration = aParticle.getAcceleration();
        velocity = aParticle.getVelocity();
        position = aParticle.getPosition();
        std::cout << "Particle" << counter << ": p=(" << position.x << ", " << position.y << ")"
                  << std::endl;
        counter++;
    }
    std::cout << "---------" << std::endl;
}


    std::vector<glm::vec2> particleSystem::givePositions() {
        std::vector<glm::vec2> thePositions = std::vector<glm::vec2>();
        return thePositions;
   
    }
