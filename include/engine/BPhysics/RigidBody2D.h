//
// Created by Michael Adeyelure on 31/08/2026.
//

#ifndef BIZZAREPHYSICS_RIGIDBODY2D_H
#define BIZZAREPHYSICS_RIGIDBODY2D_H

#include "../maths/Vector.h"

struct RigidBody2D {
    Vector<2> position;
    Vector<2> velocity;
    Vector<2> net_force;

    double width = 0;
    double height = 0;

    double mass = 0;

    bool alive = true;
    bool fixed = false;

    RigidBody2D(Vector<2> position, double mass, double width, double height, bool fixed) :
    position(position), width(width), height(height), mass(mass), fixed(fixed) {}
};

#endif //BIZZAREPHYSICS_RIGIDBODY2D_H
