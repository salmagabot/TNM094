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

class particleSystem;

class Effect3 {
public:
    void effect(std::vector<Particle>& Particals, const float& dt);

    virtual void preformEffect(std::vector<Particle>& Particals, const float& dt) = 0;

    virtual bool hasPosition() = 0;

    virtual std::string getType() = 0;

    virtual glm::vec2 getPosition() { return glm::vec2(NULL, NULL); }

    virtual void changePosition(glm::vec2){};

    virtual glm::vec2 getForceXY() { return glm::vec2(NULL, NULL); }

    virtual float getForce() { return NULL; }

    virtual void changeForce(glm::vec2 newForce) {}

    virtual void changeForce(float newForce) {}
};

class Field : public Effect3 {
private:
    float force;
    glm::vec2 position;
    bool hasPositionBool = true;
    std::string type = "Field";

public:
    Field(glm::vec2 newPosition) : position{newPosition}, force{-0.1f} {}
    
    void preformEffect(std::vector<Particle>& Particals, const float& dt) override;

    glm::vec2 getPosition() override { return position; }

    float getForce() override { return force; }

    void changePosition(glm::vec2 newPosition) override { position = newPosition; }

    void changeForce(glm::vec2 newForce) override {
        force = std::sqrt(std::pow(newForce.x, 2) + std::pow(newForce.y, 2));
    }

    bool hasPosition() override { return hasPositionBool; }

    std::string getType() override { return type; }
};

class GravityWell : public Effect3 {
private:
    float force;
    glm::vec2 position;
    bool hasPositionBool = true;
    std::string type = "GravityWell";

public:
    GravityWell(glm::vec2 newPosition, float newForce) : position{newPosition}, force{newForce} {}

    void preformEffect(std::vector<Particle>& Particals, const float& dt) override;

    glm::vec2 getPosition() override { return position; }

    float getForce() { return force; }

    void changePosition(glm::vec2 newPosition) override { position = newPosition; }

    void changeForce(float newForce) override { force = newForce;}

    bool hasPosition() override { return hasPositionBool; }

    std::string getType() override { return type; }
};

class Wind : public Effect3 {
private:
    float forceX;
    float forceY;
    bool hasPositionBool = false;
    std::string type = "Wind";

public:
    Wind(float newForceX, float newForceY) : forceX{newForceX}, forceY{newForceY} {}

    void preformEffect(std::vector<Particle>& Particals, const float& dt) override;

    glm::vec2 getForceXY() { return glm::vec2(forceX, forceY); }

    void changeForce(glm::vec2 newForce) override {
        forceX = newForce.x;
        forceY = newForce.y;
    }

    bool hasPosition() override { return hasPositionBool; }

    std::string getType() override { return type; }
};

class GravityWell2 : public Effect3 {
private:
    float force;
    glm::vec2 position;
    bool hasPositionBool = true;
    std::string type = "GravityWell2";

public:
    GravityWell2(glm::vec2 newPosition, float newForce) : position{newPosition}, force{newForce} {}

    void preformEffect(std::vector<Particle>& Particals, const float& dt) override;

    glm::vec2 getPosition() override { return position; }

    float getForce() { return force; }

    void changePosition(glm::vec2 newPosition) override { position = newPosition; }

    void changeForce(float newForce) override { force = newForce; }

    bool hasPosition() override { return hasPositionBool; }

    std::string getType() override { return type; }
};
