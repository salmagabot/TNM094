#pragma once

#include <tracy/Tracy.hpp>
#include <rendering/window.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fmt/format.h>
#include <tuple>
#include <particlesystem/particle1.hpp>
#include <particlesystem/effect1.hpp>
#include <particlesystem/emitter1.hpp>

class particleSystem {

private:
    std::vector<Effect3*> Effects3;
    std::vector<Particle> Particles;
    std::vector<Emitter3*> Emitters3;

    // ***** Old vars (Emitter2 & Effect2) *****
    //std::vector<Emitter2*> Emitters2;
    //std::vector<Effect2*> Effects2;
    //int counter;

public:
    particleSystem();

    void emitSystem(const float& dt);  // Loopar alla emitters *

    Effect3* returnEffect3(int index) { return Effects3[index]; }

    Emitter3* returnEimitter3(int index) { return Emitters3[index]; }

    void deleteEmitter3(int index);

    void deleteEffect3(int index);

    int effect3VectorSize() { return Effects3.size(); }

    int emitter3VectorSize() { return Emitters3.size(); }

    void renderSystem(rendering::Window& theWindow);

    void addToSystem(Effect3* aEffectPtr) { Effects3.push_back(aEffectPtr); }

    void addToSystem(Emitter3* aEmitter3) { Emitters3.push_back(aEmitter3); }

    void addToSystem(Particle& aParticle);// ***

    void addToSystem(std::vector<Particle>& vectorOfParticles);// Emitter ger **

    std::vector <glm::vec2> givePositions();

    std::tuple<glm::vec2, glm::vec2, glm::vec2> eulerAprox(glm::vec2& acceleration1,
                                                           glm::vec2& velocity0,
                                                           glm::vec2& possition0, const float& dt);

    std::vector<Particle>& getParticles();

    void uppdateParticels(const float& dt);

    void display();
};
