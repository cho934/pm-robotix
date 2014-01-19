#include <cmath>
#include "Position.hpp"

pmx::Position::Position()
: x_(0.0), y_(0.0), angle_(0.0)
{}

pmx::Position::Position(double x, double y, double angle)
: x_(x), y_(y), angle_(angle)
{
    while (angle_ < -M_PI)
    {
        angle_ += 2.0 * M_PI;
    }
    while (angle_ > M_PI)
    {
        angle_ -= 2.0 * M_PI;
    }
}

pmx::Position::Position(const pmx::Position& position)
: x_(position.x_), y_(position.y_), angle_(position.angle_)
{}

void
pmx::Position::operator =(const pmx::Position& position)
{
    this->x_ = position.x_;
    this->y_ = position.y_;
    this->angle_ = position.angle_;
}

pmx::Position
pmx::Position::rotate(double angle)
{
    return Position(this->x_, this->y_, this->angle_ + angle);
}

std::ostream& operator << (std::ostream& os, const pmx::Position position)
{
    os << "[x:" << position.x() << "] [y:" << position.y() << "] [angle:" << position.angle() << "]";
    return os;
}
