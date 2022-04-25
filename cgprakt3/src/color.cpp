#include "color.h"

Color::Color()
{
    this->R =0;
    this->G =0;
    this->B =0;

}

Color::Color( float r, float g, float b) {
    this->R = r;
    this->G = g;
    this->B = b;
}

Color::~Color() {

};

Color Color::operator*(const Color& c) const
{
    return Color(this->R*c.R , this->G*c.G , this->B*c.B);
}

Color Color::operator*(const float Factor) const
{
    return Color( this->R*Factor , this->G*Factor , this->B*Factor );

}

Color Color::operator+(const Color& c) const
{
    return Color(this->R+c.R , this->G+c.G, this->B+c.B);
}

Color& Color::operator+=(const Color& c)
{
    this->R = this->R+c.R;
    this->G = this->G+c.G;
    this->B = this->B+c.B;

    return *this;
}