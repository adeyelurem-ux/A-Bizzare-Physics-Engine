//
// Created by Michael Adeyelure on 31/08/2026.
//

#ifndef BIZZAREPHYSICS_EULERINTEGRATOR_H
#define BIZZAREPHYSICS_EULERINTEGRATOR_H

#include <functional>
#include "Vector.h"

class EulerIntegrator {
public:
    using ScalarSystem = std::function<double(double t, double x)>;

    [[nodiscard]] static double step(double t, double x, const double dt, const ScalarSystem& sys) {
        const double gradient = sys(t, x);
       return x + gradient * dt;
    }


    using Vector2System = std::function<Vector<2>(double t, const Vector<2>& r)>;

    [[nodiscard]] static Vector<2> step(double t, Vector<2> r, const double dt, const Vector2System& sys) {
        const Vector<2> gradient = sys(t, r);
        r += gradient * dt;
        return r;
    }
};

#endif //BIZZAREPHYSICS_EULERINTEGRATOR_H
