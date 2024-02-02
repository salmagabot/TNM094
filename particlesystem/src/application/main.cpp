#include <tracy/Tracy.hpp>
#include <rendering/window.h>

#include <particlesystem/particlesystem.hpp>
#include <particlesystem/particle.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fmt/format.h>

constexpr float Pi = 3.141592f;

int main(int, char**) try {
    rendering::Window window("Particle System v0.0.1 pre-release alpha", 850, 850);
    
    //skapa pertikelsystem
    ParticleSystem particleSystem;
    
    //skapa tid
    float prevTime = 0.0;
    bool running = true;
    
    while (running) {
        
        window.beginFrame();
        
        float t = float(window.time());
        float dt = t - prevTime;
        prevTime = t;
        
        // Clear screen with color
        window.clear({0, 0.05, 0.1, 0.9});
        
        // ==================================== UI ====================================
        {
            window.beginGuiWindow("Particle System");

            
            /* if (window.button("Close application")) {
                running = false;
            } */
            
            // ==================================== emitter ====================================
            
            // Uniform
            if (window.button("Add uniform emitter")) {
                particleSystem.emitters.push_back(new Uniform);
            }
            
            // Directional
            float angle;
            window.sliderFloat("angle", angle, 0.0, float(2*Pi));
            
            if (window.button("Add directional emitter")) {
                particleSystem.emitters.push_back(new Directional(angle));
            }
            
            // Explosion
            int value;
            window.sliderInt("Amount of particles", value, 1, 100);
            
            if (window.button("Add explosion emitter")) {
                particleSystem.emitters.push_back(new Explosion(value));
            }
            
            // Unique
            if (window.button("Add Uni Emitter")) {
                particleSystem.emitters.push_back(new Uni());
            }
        
            
            
            // ==================================== effect ====================================
            
            // Gravity effect
            float gravity;
            window.sliderFloat("Gravity", gravity, 0.0, 30);
            
            if (window.button("Add Gravity well")) {
                particleSystem.effects.push_back(new GravityWell(gravity));
            }
            
            // Wind effect
            float power;
            window.sliderFloat("Power of wind", power, 0.0, 30);
            
            if (window.button("Add Wind")) {
                particleSystem.effects.push_back(new Wind(power));
            }
            
            window.endGuiWindow();
        }
        
    
        
        // ==================================== rendering ====================================
        
        //uppdatera tiden
        particleSystem.update(dt);
        
        //rita ut partiklar utifrån givna förutsättningar
        for (size_t i = 0; i < particleSystem.particles.size(); i++){
            window.drawPoint(particleSystem.particles[i].position,
                             particleSystem.particles[i].radius,
                             particleSystem.particles[i].color);
        }
        
        // =====================================================================================
        
        window.endFrame();
        running = running && !window.shouldClose();
        
        //std::cout << __FUNCTION__ << " - " << __FILE__ << " - " << __LINE__;
    }
    return EXIT_SUCCESS;
}
catch (const std::exception& e) {
    fmt::print("{}", e.what());
    return EXIT_FAILURE;
}
