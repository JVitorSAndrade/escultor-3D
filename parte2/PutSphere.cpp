#include "PutSphere.h"

PutSphere::PutSphere(int xcenter, int ycenter, int zcenter, int radius, float r, float g, float b, float a)
    : xcenter(xcenter), ycenter(ycenter), zcenter(zcenter), radius(radius), r(r), g(g), b(b), a(a)
{
}

void PutSphere::draw(Sculptor &s)
{
    s.setColor(r, g, b, a);
    s.putSphere(xcenter, ycenter, zcenter, radius);
}