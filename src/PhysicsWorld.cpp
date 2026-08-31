//
// Created by Michael Adeyelure on 31/08/2026.
//

#include "../include/engine/BPhysics/PhysicsWorld.h"

void PhysicsWorld::update(double dt) {

}


std::size_t PhysicsWorld::create_2d_body(const Vector<2> position, const double mass,
                                         const double width, const double height, const bool fixed) {

    if (!free_indices.empty()) {
        const std::size_t index = free_indices.back();
        free_indices.pop_back();

        bodies[index] = RigidBody2D(position, mass, width, height, fixed);

        return index;
    }

    bodies.emplace_back(position, mass, width, height, fixed);
    return bodies.size() - 1;
}


void PhysicsWorld::destroy_2d_body(const std::size_t index) {
    assert(index < bodies.size() && "Out of bounds");

    if (bodies[index].alive){
        bodies[index].alive = false;
        free_indices.push_back(index);
    }
}


RigidBody2D &PhysicsWorld::get_2d_body(const std::size_t index) {
    assert(index < bodies.size() && "Out of bounds");
    assert(bodies[index].alive && "Attempted to access destroyed body");

    return bodies[index];
}
