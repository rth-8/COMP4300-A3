#include "vector2d.h"
#include <math.h>

Vec2::Vec2()
{
}
    
Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vec2::Vec2(const Vec2 & src)
{
    this->x = src.x;
    this->y = src.y;
}

//----------------------------------------------------------

Vec2 Vec2::operator+(const Vec2 & rhs) const
{
    return Vec2(this->x + rhs.x, this->y + rhs.y);
}

Vec2 & Vec2::operator+=(const Vec2 & rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

Vec2 & Vec2::add(const Vec2 & rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

//----------------------------------------------------------

Vec2 Vec2::operator-(const Vec2 & rhs) const
{
    return Vec2(this->x - rhs.x, this->y - rhs.y);
}

Vec2 & Vec2::operator-=(const Vec2 & rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

Vec2 & Vec2::sub(const Vec2 & rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

//----------------------------------------------------------

Vec2 Vec2::operator*(float val) const
{
    return Vec2(this->x * val, this->y * val);
}

Vec2 & Vec2::operator*=(float val)
{
    this->x *= val;
    this->y *= val;
    return *this;
}

Vec2 & Vec2::mul(float val)
{
    this->x *= val;
    this->y *= val;
    return *this;
}

//----------------------------------------------------------

float Vec2::mag()
{
    return sqrt(x*x + y*y);
}

Vec2 & Vec2::normalize()
{
    float m = this->mag();
    if (m != 0)
    {
        x /= m;
        y /= m;
    }
    return *this;
}
