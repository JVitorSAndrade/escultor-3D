#include "CutSphere.h"

CutSphere::CutSphere(int xcenter, int ycenter, int zcenter, int radius)
    : xcenter(xcenter), ycenter(ycenter), zcenter(zcenter), radius(radius)
{
}

void CutSphere::draw(Sculptor &s)
{
    s.cutSphere(xcenter, ycenter, zcenter, radius);
}