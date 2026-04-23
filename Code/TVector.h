/**
 * MIT License
 * Copyright (c) 2026 [AlexBo/My3DEngine]
 * * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 */

#pragma once

#include <cmath>
#include <iostream>

 /**
  * Description:
  * EN: 2D Vector structure for screen coordinates and UV mapping.
  */
template <typename T>
struct Vector2
{
    union {
        struct { T x, y; };
        struct { T u, v; };
        T data[2];
    };

    constexpr Vector2() noexcept : x(0), y(0) {}
    constexpr Vector2(T _x, T _y) noexcept : x(_x), y(_y) {}

    [[nodiscard]] constexpr Vector2 operator+(const Vector2& v) const noexcept { return Vector2(x + v.x, y + v.y); }
    [[nodiscard]] constexpr Vector2 operator-(const Vector2& v) const noexcept { return Vector2(x - v.x, y - v.y); }
    [[nodiscard]] constexpr Vector2 operator*(T scalar) const noexcept { return Vector2(x * scalar, y * scalar); }
};

/**
 * Description:
 * EN: 3D Vector structure for positions, normals, and RGB colors.
 */
template <typename T>
struct Vector3
{
    union {
        struct { T x, y, z; };
        struct { T r, g, b; };
        T data[3];
    };

    constexpr Vector3() noexcept : x(0), y(0), z(0) {}
    constexpr Vector3(T _x, T _y, T _z) noexcept : x(_x), y(_y), z(_z) {}
    explicit constexpr Vector3(T val) noexcept : x(val), y(val), z(val) {}

    [[nodiscard]] constexpr Vector3 operator+(const Vector3& v) const noexcept { return Vector3(x + v.x, y + v.y, z + v.z);  }
    [[nodiscard]] constexpr Vector3 operator-(const Vector3& v) const noexcept { return Vector3(x - v.x, y - v.y, z - v.z);  }
    [[nodiscard]] constexpr Vector3 operator*(T scalar) const noexcept { return Vector3(x * scalar, y * scalar, z * scalar); }
    [[nodiscard]] constexpr Vector3 operator/(T scalar) const noexcept { return Vector3(x / scalar, y / scalar, z / scalar); }

    constexpr Vector3& operator+=(const Vector3& v) noexcept { x += v.x; y += v.y; z += v.z; return *this;  }
    constexpr Vector3& operator-=(const Vector3& v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this;  }
    constexpr Vector3& operator*=(T scalar) noexcept { x *= scalar; y *= scalar; z *= scalar; return *this; }
    constexpr Vector3& operator/=(T scalar) noexcept { x /= scalar; y /= scalar; z /= scalar; return *this; }
    constexpr Vector3& operator*=(const Vector3& v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this;  }

    /**
     * Description:
     * EN: Componentwise multiplication of two vectors (for Scale)
     */
    [[nodiscard]] constexpr Vector3 operator*(const Vector3& v) const noexcept {
        return Vector3(x * v.x, y * v.y, z * v.z);
    }

    /**
     * Description:
     * EN: Calculates the precise length of the vector.
     */
    [[nodiscard]] inline T length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    /**
     * Description:
     * EN: Calculates the squared length. Faster for distance comparisons as it avoids std::sqrt.
     */
    [[nodiscard]] constexpr T lengthSquared() const noexcept {
        return x * x + y * y + z * z;
    }

    /**
     * Description:
     * EN: Returns a normalized copy of the vector (length exactly 1.0).
     */
    [[nodiscard]] inline Vector3 normalize() const {
        T len = length();
        if (len > static_cast<T>(0)) {
            T invLen = static_cast<T>(1) / len;
            return Vector3(x * invLen, y * invLen, z * invLen);
        }
        return *this;
    }

    /**
     * Description:
     * EN: Computes the dot product. Used for lighting and angles.
     */
    [[nodiscard]] constexpr T dot(const Vector3& v) const noexcept {
        return x * v.x + y * v.y + z * v.z;
    }

    /**
     * Description:
     * EN: Computes the cross product, returning a vector perpendicular to both.
     */
    [[nodiscard]] constexpr Vector3 cross(const Vector3& v) const noexcept {
        return Vector3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }
};

/**
 * Description:
 * EN: 4D Vector structure for homogeneous coordinates and clipping space.
 */
template <typename T>
struct Vector4
{
    union {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        T data[4];
    };

    constexpr Vector4() noexcept : x(0), y(0), z(0), w(0) {}
    constexpr Vector4(T _x, T _y, T _z, T _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}
    constexpr Vector4(const Vector3<T>& v, T _w) noexcept : x(v.x), y(v.y), z(v.z), w(_w) {}

    [[nodiscard]] constexpr Vector4 operator+(const Vector4& v) const noexcept { return Vector4(x + v.x, y + v.y, z + v.z, w + v.w); }
    [[nodiscard]] constexpr Vector4 operator-(const Vector4& v) const noexcept { return Vector4(x - v.x, y - v.y, z - v.z, w - v.w); }
    [[nodiscard]] constexpr Vector4 operator*(T scalar) const noexcept { return Vector4(x * scalar, y * scalar, z * scalar, w * scalar); }

    /**
     * Description:
     * EN: Linear interpolation between two 4D vectors. Used in clipping intersections.
     */
    [[nodiscard]] static constexpr Vector4 lerp(const Vector4& a, const Vector4& b, T t) noexcept {
        return a + (b - a) * t;
    }

    /**
     * Description:
     * EN: Performs Perspective Divide to convert Homogeneous Clip Space to NDC.
     */
    [[nodiscard]] inline Vector3<T> toNDC() const {
        if (std::abs(w) < static_cast<T>(1e-6)) {
            return Vector3<T>(x, y, z);
        }
        T invW = static_cast<T>(1) / w;
        return Vector3<T>(x * invW, y * invW, z * invW);
    }
};

// ==========================================
// Глобальні оператори (для зручності)
// ==========================================

template <typename T>
[[nodiscard]] constexpr Vector3<T> operator*(T scalar, const Vector3<T>& v) noexcept {
    return v * scalar;
}

template <typename T>
[[nodiscard]] constexpr Vector4<T> operator*(T scalar, const Vector4<T>& v) noexcept {
    return v * scalar;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector3<T>& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

// ==========================================
// Зручні Type Aliases
// ==========================================

using Vector4f = Vector4<float>;
using Vector4i = Vector4<int>;

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
using Vector3d = Vector3<double>;

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;