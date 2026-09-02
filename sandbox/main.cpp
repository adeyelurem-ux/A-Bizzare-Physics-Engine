//
// Created by Michael Adeyelure on 22/08/2026.
//

#include<iostream>
#include "engine/BPhysics/PhysicsWorld.h"

int main() {
    PhysicsWorld world;
    std::size_t body1 = world.create_2d_body({-10, 0}, 1, 0.6, 1, 1, false);
    std::size_t body2 = world.create_2d_body({10, 0}, 2, 0.6, 2, 1, false);

    world.get_2d_body(body1).velocity = {1, 0};
    world.get_2d_body(body2).velocity = {-1, 0};

    for (int64_t i = 0; i < 100000; i++) {
        world.update(0.1);
        std::cout << "Position 1: " << world.get_2d_body(body1).position << "\nVelocity 1: "
        << world.get_2d_body(body1).velocity << "\nPosition 2: " << world.get_2d_body(body2).position << "\nVelocity 2: "
        << world.get_2d_body(body2).velocity << "\n\n";
    }
}
