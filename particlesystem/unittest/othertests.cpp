
#include <catch2/catch_all.hpp>
#include <particlesystem/particlesystem.hpp>
#include <particlesystem/particle.hpp>

TEST_CASE("Particles are deleted after a while", "[particle system]") {
    ParticleSystem particleSystem;
    Particle temporaryParticle;
    temporaryParticle.lifetime = 1;
    
    // Add an emitter to create particles
    particleSystem.particles.push_back(temporaryParticle);

    float dt = float(0.1);
    
    for(int i = 0; i < 10; i++) {
        particleSystem.update(dt);
    }
    
    // Check that there are no particles left in the particle system
    REQUIRE(particleSystem.particles.empty());
}

SCENARIO("Uni emitter adds particles correctly", "[emitter]") {
    GIVEN("A test emitter with specific radius and velocity") {
        
        Uni emitter;
        
        WHEN("addParticle is called 10 times") {
            std::vector<Particle> particles;
            for (int i = 0; i < 10; i++) {
                emitter.addParticle(particles, float(0.1));
            }
            
            THEN("10 particles are added with expected properties") {
                
                for (const auto& particle : particles) {
                    
                    REQUIRE(particle.velocity.y == Catch::Approx(1.0));
                    REQUIRE(particle.velocity.x == Catch::Approx(2.0));
                    
                    REQUIRE(particle.radius == Catch::Approx(20));
                }
            }
        }
    }
}

