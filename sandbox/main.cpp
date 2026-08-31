//
// Created by Michael Adeyelure on 22/08/2026.
//

#include<iostream>
#include "engine/BPhysics/PhysicsWorld.h"

int main() {
    PhysicsWorld physics_world;

    physics_world.create_2d_body({0, 0}, 1, 0, 0, false);

    for (int i = 0; i < 500; i++) {
        physics_world.get_2d_body(0).net_force = physics_world.get_2d_body(0).mass * Vector<2> {0, -9.81};
        std::cout << "Position: " << physics_world.get_2d_body(0).position <<
            "\nVelocity: " << physics_world.get_2d_body(0).velocity <<
                "\nNet Force: " << physics_world.get_2d_body(0).net_force << "\n\n";

        physics_world.update(1);
    }
}
