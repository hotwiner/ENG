#pragma once

#include <SDL2/SDL.h>
#include <cmath>

struct vec2 {
    float x, y;

    vec2 operator+(vec2& pos) const
    {
        return { .x = (this->x + pos.x), .y = (this->y + pos.y) };
    }

    vec2 operator+=(vec2& pos)
    {
        this->x = this->x + pos.x;
        this->y = this->y + pos.y;
        return *this;
    }

    vec2 operator-(vec2& pos) const
    {
        return { .x = (this->x - pos.x), .y = (this->y - pos.y) };
    }

    vec2 operator-=(vec2& pos)
    {
        this->x = this->x - pos.x;
        this->y = this->y - pos.y;
        return *this;
    }

    vec2 operator*(vec2& pos) const
    {
        return { .x = (this->x * pos.x), .y = (this->y * pos.y) };
    }

    vec2 operator*(float predicate) const
    {
        return { .x = (this->x * predicate), .y = (this->y * predicate) };
    }

    bool operator<(vec2& pos) const
    {
        return ((this->x < pos.x)) && ((this->y < pos.y));
    }
    bool operator>(vec2& pos) const
    {
        return ((this->x > pos.x)) && ((this->y > pos.y));
    }

    bool operator==(vec2& pos) const
    {
        return (std::abs(this->x - pos.x)) < 1.0f && (std::abs(this->y - pos.y) < 1.0f);
    }

    bool operator!=(vec2& pos) const
    {
        return (std::abs(this->x - pos.x)) > 1.0f && (std::abs(this->y - pos.y) > 1.0f);
    }

    vec2 normalize()
    {
        float c = 1 / std::sqrt(x * x + y * y);
        x *= c;
        y *= c;
        return *this;
    }

    float magnitude()
    {
        return std::sqrt(this->x * this->x + this->y * this->y);
    }
};
