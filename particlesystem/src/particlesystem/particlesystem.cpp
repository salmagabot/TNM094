//
//  particlesystem.cpp
//  particlesystem
//
//  Created by Salma Gabot on 2023-03-29.
//

#include <particlesystem/particlesystem.hpp>

void ParticleSystem::update(float dt){
    
    for (size_t i = 0; i < particles.size(); i++) {
        
        //lifstiden minskar efter tiden
        particles[i].lifetime -= dt;
        
        //positionen uppdateras utifrån hastighet
        particles[i].position += particles[i].velocity * dt;
        
        
        if (particles[i].lifetime <= 0) {
            //tar bort partiklarna
            particles.erase(particles.begin() + int(i));
        }
    }
    
    //lägger till partiklar utifrån specificerad emitter
    for (size_t i = 0; i < emitters.size(); i++){
        emitters[i]->addParticle(particles,dt);
    }
    
    //påverkar partiklar utifrån specificerad effect
    for(size_t j = 0; j < effects.size(); j++){
        effects[j]->affectParticle(particles);
    }

}
