//
// Created by Michael Adeyelure on 30/08/2026.
//

#ifndef BIZZAREPHYSICS_PHYSICSWORLD_H
#define BIZZAREPHYSICS_PHYSICSWORLD_H

#include <vector>
#include "RigidBody2D.h"


class PhysicsWorld {
private:
    std::vector<RigidBody2D> bodies;
    std::vector<std::size_t> free_indices;

public:
    static void update(double dt);

    std::size_t create_2d_body(Vector<2> position, double mass, double width, double height, bool fixed);
    void destroy_2d_body(std::size_t index);

    RigidBody2D& get_2d_body(std::size_t index);
};

#endif //BIZZAREPHYSICS_PHYSICSWORLD_H
