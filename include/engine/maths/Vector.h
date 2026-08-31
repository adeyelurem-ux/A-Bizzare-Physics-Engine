//
// Created by Michael Adeyelure on 22/08/2026.
//

#ifndef A_BIZZARE_PHYSICS_ENGINE_VECTORN_H
#define A_BIZZARE_PHYSICS_ENGINE_VECTORN_H

#include <array>
#include <cassert>
#include <cstddef>
#include <cmath>
#include <algorithm>
#include <initializer_list>
#include <iostream>


template<std::size_t N>

struct Vector {
    std::array<double, N> data{};

    Vector() = default;
    Vector(const std::initializer_list<double>& list) {
        std::copy_n(list.begin(), std::min(list.size(), N), data.begin());
    }

    [[nodiscard]] constexpr double& operator[](std::size_t i) noexcept {
        return data[i];
    }


    [[nodiscard]] constexpr const double& operator[](std::size_t i) const noexcept {
        return data[i];
    }


    constexpr Vector& operator+=(const Vector& rhs) noexcept {
        std::size_t i = 0;

        for (double& val : data) {
            val += rhs[i++];
        }

        return *this;
    }


    constexpr Vector& operator-=(const Vector& rhs) noexcept {
        std::size_t i = 0;

        for (double& val : data) {
            val -= rhs[i++];
        }

        return *this;
    }


    constexpr Vector& operator*=(const double scalar) noexcept {

        for (double& val : data) {
            val *= scalar;
        }

        return *this;
    }


    constexpr Vector& operator/=(const double scalar) {
        assert(scalar != 0 && "Division by zero");
        const double inv = 1.0/scalar;

        for (double& val : data) {
            val *= inv;
        }

        return *this;
    }


    [[nodiscard]] friend constexpr Vector operator+(const Vector& lhs, const Vector& rhs) noexcept {
        Vector result = lhs;
        result += rhs;

        return result;
    }


    [[nodiscard]] friend constexpr Vector operator-(const Vector& lhs, const Vector& rhs) noexcept {
        Vector result = lhs;
        result -= rhs;

        return result;
    }


    [[nodiscard]] friend constexpr Vector operator*(const Vector& lhs, const double scalar) noexcept {
        Vector result = lhs;
        result *= scalar;

        return result;
    }


    [[nodiscard]] friend constexpr Vector operator*(const double scalar, const Vector& rhs) noexcept {
        Vector result = rhs;
        result *= scalar;

        return result;
    }


    [[nodiscard]] friend constexpr Vector operator/(const Vector& lhs, const double scalar) {
        Vector result = lhs;
        result /= scalar;

        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector<N>& vec) {
        os << "(";
        for (std::size_t i = 0; i < N; ++i) {
            os << vec.data[i];
            if (i < N - 1) {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }


    [[nodiscard]] constexpr double dot(const Vector& other) const noexcept{
        double result = 0;

        std::size_t i = 0;

        for (double val : data) {
            result += val * other[i];
            i++;
        }

        return result;
    }


    [[nodiscard]] constexpr Vector cross(const Vector& other) const requires(N == 3) {
        return Vector
        {
            (data[1] * other[2]) - (data[2] * other[1]),
            (data[2] * other[0]) - (data[0] * other[2]),
            (data[0] * other[1]) - (data[1] * other[0])
        };
    }


    [[nodiscard]] constexpr double magnitudeSqd() const noexcept{
        double result = 0;

        for (const double val : data) {
            result += val * val;
        }

        return result;
    }



    [[nodiscard]] constexpr Vector unitVector() const {
        const double mag = std::sqrt(magnitudeSqd());
        assert(mag != 0.0 && "Division by zero");
        return *this/mag;
    }


    void normalise() noexcept{
        *this = unitVector();
    }


    void normalize() noexcept {
        normalise();
    }
};

#endif //A_BIZZARE_PHYSICS_ENGINE_VECTORN_H
