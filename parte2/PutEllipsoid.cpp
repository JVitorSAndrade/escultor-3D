#include "PutEllipsoid.h"

PutEllipsoid::PutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz, float r, float g, float b, float a)
    : xcenter(xcenter), ycenter(ycenter), zcenter(zcenter), rx(rx), ry(ry), rz(rz), r(r), g(g), b(b), a(a)
{
}

void PutEllipsoid::draw(Sculptor &s)
{
    s.setColor(r, g, b, a);
    s.putEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz);
}