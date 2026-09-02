//
// Created by Michael Adeyelure on 31/08/2026.
//

#include "../include/engine/BPhysics/PhysicsWorld.h"

#include "engine/maths/EulerIntegrator.h"

void PhysicsWorld::update(const double dt) {
    for (auto& body : bodies) {
        if (!body.alive || body.fixed)
            continue;

        const Vector<2> acceleration = body.net_force/body.mass;

        body.velocity += acceleration * dt;
        body.position += body.velocity * dt;
        body.net_force = {0, 0};
    }

    for (int iter = 0; iter < 10; ++iter) {
        resolve_collisions(dt);
    }
}


void PhysicsWorld::resolve_collisions(const double dt) {
    const std::size_t count = bodies.size();

    // Slop & Baumgarte factor for sinking prevention
    const double slop = 0.01;      // Allowed penetration before correcting
    const double percent = 0.02;    // Penetration percentage corrected per frame

    for (std::size_t i = 0; i < count; ++i) {
        for (std::size_t j = i + 1; j < count; ++j) {
            auto& a = bodies[i];
            auto& b = bodies[j];

            if (!a.alive || !b.alive) continue;

            double w_a = (!a.fixed && a.mass > 0) ? (1.0 / a.mass) : 0.0;
            double w_b = (!b.fixed && b.mass > 0) ? (1.0 / b.mass) : 0.0;
            double w_total = w_a + w_b;
            if (w_total == 0.0) continue;

            double dx = a.position[0] - b.position[0];
            double dy = a.position[1] - b.position[1];
            double x_overlap = a.width / 2.0 + b.width / 2.0 - std::abs(dx);
            double y_overlap = a.height / 2.0 + b.height / 2.0 - std::abs(dy);

            if (x_overlap > 0.0 && y_overlap > 0.0) {
                Vector<2> normal = {0.0, 0.0};
                double penetration = 0.0;

                if (x_overlap < y_overlap) {
                    normal[0] = (dx > 0.0) ? 1.0 : -1.0;
                    penetration = x_overlap;
                } else {
                    normal[1] = (dy > 0.0) ? 1.0 : -1.0;
                    penetration = y_overlap;
                }

                // Relative velocity
                Vector<2> rel_vel = a.velocity - b.velocity;
                double vel_along_normal = rel_vel[0] * normal[0] + rel_vel[1] * normal[1];

                // Only solve if objects are moving toward each other
                if (vel_along_normal < 0.0) {
                    double e = (a.restitution + b.restitution) / 2.0;

                    // Calculate scalar impulse magnitude
                    double j_scalar = -(1.0 + e) * vel_along_normal / w_total;

                    // Apply impulse directly to velocities
                    Vector<2> impulse = normal * j_scalar;
                    a.velocity += impulse * w_a;
                    b.velocity -= impulse * w_b;
                }

                // Baumgarte Stabilization: Gently fix positional sinking
                double correction_magnitude = (std::max(penetration - slop, 0.0) / w_total) * percent;
                Vector<2> correction = normal * correction_magnitude;
                a.position += correction * w_a;
                b.position -= correction * w_b;
            }
        }
    }
}


std::size_t PhysicsWorld::create_2d_body(const Vector<2> position, const double mass, const double restitution,
                                         const double width, const double height, const bool fixed) {

    if (!free_indices.empty()) {
        const std::size_t index = free_indices.back();
        free_indices.pop_back();

        bodies[index] = RigidBody2D(position, mass, restitution, width, height, fixed);

        return index;
    }

    bodies.emplace_back(position, mass, restitution, width, height, fixed);
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
