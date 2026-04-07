#pragma once
#include <compare>

/**
 * точка для описания в координатах
 */
struct Point {
    int x = 0;
    int y = 0;
    std::strong_ordering operator<=>(const Point &) const = default;
};

/**
 * точка с плаввующей точкой флот
 */
struct PointF {
    float x=0.0f;
    float y=0.0f;
    float distSq(const PointF &p) const {
        float dx = x - p.x;
        float dy = y - p.y;
        return dx*dx + dy*dy;
    }
};
