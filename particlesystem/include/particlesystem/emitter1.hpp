#pragma once

#include <tracy/Tracy.hpp>
#include <rendering/window.h>

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>

#include <fmt/format.h>

#include <tuple>
#include <particlesystem/particle1.hpp>

class Emitter3 {
    public:

        std::vector<Particle> emit();

        virtual std::vector<Particle> preformEmit() = 0;

        virtual std::string getType() = 0;

        virtual void changePosition(glm::vec2 newPosition) = 0;

        virtual glm::vec2 getPosition() = 0;

        virtual float getAngle() { return NULL; }

        virtual void changeAngle(float newAngle) {}
};

class Uniform : public Emitter3 {
    private:
        glm::vec2 position;
        float nrOfParticalsDT;
        std::string type;
        float starAcceleration;
        int tickTimer = 0;
    public:
        Uniform(glm::vec2 newPosition)
            : position{newPosition}
            , nrOfParticalsDT{64.0f}
            , starAcceleration{0.1f}
            , type{"Uniform"} {}

        std::vector<Particle> preformEmit() override;

        void changePosition(glm::vec2 newPosition) override { position = newPosition; }

        glm::vec2 getPosition() override { return position; }

        std::string getType() override { return type; }
};

class Directional : public Emitter3 {
    private:
        glm::vec2 position;
        float angle;
        std::string type;

    public:
        Directional(glm::vec2 newPosition, float newAngle)
            : position{newPosition}
            , angle{newAngle}
            , type{"Directional"} {}

        std::vector<Particle> preformEmit() override;

        void changePosition(glm::vec2 newPosition) override { position = newPosition; }

        glm::vec2 getPosition() override { return position; }

        float getAngle() override { return angle; }

        void changeAngle(float newAngle) override { angle = newAngle; }

        std::string getType() override { return type; }
};
