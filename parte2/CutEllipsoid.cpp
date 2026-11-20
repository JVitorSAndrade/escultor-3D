#include "CutEllipsoid.h"

CutEllipsoid::CutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
    : xcenter(xcenter), ycenter(ycenter), zcenter(zcenter), rx(rx), ry(ry), rz(rz)
{
}

void CutEllipsoid::draw(Sculptor &s)
{
    s.cutEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz);
}