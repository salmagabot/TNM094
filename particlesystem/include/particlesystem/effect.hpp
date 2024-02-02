#ifndef effect_hpp
#define effect_hpp

#include "rendering/window.h"

#include "particle.hpp"

#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

#include <stdio.h>
#include <vector>
#include <cmath>

class Effect {
public:
    //definerar position vector
    glm::vec2 position = {0, 0};
    
    //defienerar affectPartikel
    virtual void affectParticle(std::vector<Particle> &particles) = 0;
};

//================================= gravity well ============================================
class GravityWell : public Effect{
    
public:
    //gravity
    GravityWell(float gravity) : Effect(), gravity(gravity){
    }
    
    // affectPartikel
    void affectParticle(std::vector<Particle> &particles) override{
        
        float diffX, diffY;
        
        for(size_t i = 0; i < particles.size(); i++){

            //definerar vad differense har för värde för varje i
            diffX = position.x - particles[i].position.x;
            diffY = position.y - particles[i].position.y;
            
            //vilka partiklar ska dras mot gravitywell
            if(diffX < 1 && diffY < 1){
                particles[i].velocity.x += gravity * float(0.005) * diffX;
                particles[i].velocity.y += gravity * float(0.005) * diffY;
            }
        }
    }float gravity;
};

//================================= wind ============================================
class Wind : public Effect{
public:
    // powerrr
    Wind(float power) : Effect(), power(power){
    }
    
    //affect
    void affectParticle(std::vector<Particle> &particles) override{
        
        float diffX, diffY;
        
        for(size_t i = 0; i < particles.size(); i++){
            
            //definerar vad differense har för värde för varje i
            diffX = position.x - particles[i].position.x;
            diffY = position.y - particles[i].position.y;
            
            //vilka partiklar ska påverkas av vinden
            if(diffX < 1 & diffY < 1){
                particles[i].velocity.x += float(0.005) * power;
                particles[i].velocity.y += float(0.005) * power;
            }
        }
    }float power;
};
#endif
