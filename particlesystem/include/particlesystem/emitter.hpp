#ifndef emitter_hpp
#define emitter_hpp

#include "rendering/window.h"

#include "particle.hpp"

#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include <stdio.h>
#include <math.h>
#include <vector>

class Emitter{
public:
    
    //definerar vectors
    glm::vec2 position = {0,0};
    glm::vec2 velocity = {0,0};
    
    //definerar variables
    double time;
    double delay;
    
    
    //clock definierar tid
    //delay seer till att particlar skickas ut med lite mellanrum.
    bool clock(double dt) {
        time += dt;
        if(time > delay) {
            time = 0;
            return true;
        }return false;
    }
    
    //definerar vector
    virtual void addParticle(std::vector<Particle> &particles, float dt) = 0;
};


//================================= directional ============================================
class Directional : public Emitter {
    
public:
        // + angle
       Directional(float angle) : Emitter(), angle(angle) {
      }
    
    void addParticle(std::vector<Particle> &particles, float dt) override {
        
        delay = 0.001;
        
        Particle particle;
        particle.position = {-0.5,0.0};
        particle.lifetime = 4;
        
        if(clock(dt)){
            
            //random färg
            particle.color = {
                rand() / (float)(RAND_MAX),
                rand() / (float)(RAND_MAX),
                rand() / (float)(RAND_MAX),
                1
                
            };
            
            //velocity i x och y led
            particle.velocity.y = float(sin(angle));
            particle.velocity.x = float(cos(angle));
            
            //radie
            particle.radius = float(10);
            
            //lägger till i vektorn
            particles.push_back(particle);
        }
    }
    float angle;
};

//================================= uniform ============================================
class Uniform : public Emitter {
    
public:
    void addParticle(std::vector<Particle> &particles, float dt) override {
        
        delay = 0.001;
        
        Particle particle;
        particle.position = {-0.5,0.5};
        particle.lifetime = 4;
        
        if(clock(dt)){
            
            particle.color = {
                rand() / (float)(RAND_MAX),
                rand() / (float)(RAND_MAX),
                rand() / (float)(RAND_MAX),
                1
                
            };
            
            //skapar random i 360 grader
            particle.velocity.y = float(cos(rand()));
            particle.velocity.x = float(sin(rand()));
            
            
            particle.radius = float(10);
            
            particles.push_back(particle);
        }
    }
};

//================================= explosion ============================================
class Explosion : public Emitter {
    
public:
    Explosion(int amount) : Emitter(), amount(amount) {
   }
    
    void addParticle(std::vector<Particle> &particles, float dt) override {
        
        delay = 0.01;
        
        Particle particle;
        particle.position = {-0.5,-0.5};
        particle.lifetime = 5;
        
        if(clock(dt)){
            
        particle.color = {
            rand() / (float)(RAND_MAX),
            rand() / (float)(RAND_MAX),
            rand() / (float)(RAND_MAX),
            1
            
        };
        
            for (int i = 0; i < amount; i++) {
                
                particle.velocity.y = float(cos(rand()));
                particle.velocity.x = float(sin(rand()));
                
                particle.radius = float(10);
                
                particles.push_back(particle);
            }
        }
    }int amount;
    
};

class Uni : public Emitter {
    
public:
        // + angle
       Uni() : Emitter() {
      }
    
    void addParticle(std::vector<Particle> &particles, float dt) override {
        
        delay = 0.01;
        
        Particle particle;
        particle.position = {0.0,0.0};
        particle.lifetime = 4;
        
        if(clock(dt)){
            
            //random färg
            particle.color = {
                rand() / (float)(RAND_MAX),
                rand() / (float)(RAND_MAX),
                rand() / (float)(RAND_MAX),
                1
                
            };
            
            //velocity i x och y led
            particle.velocity.y = 1.0;
            particle.velocity.x = 2.0;
            
            //radie
            particle.radius = float(20);
            
            //lägger till i vektorn
            particles.push_back(particle);
        }
    }
};
#endif
