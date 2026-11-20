#include "PutBox.h"

PutBox::PutBox(int x0, int x1, int y0, int y1, int z0, int z1, float r, float g, float b, float a)
    : x0(x0), x1(x1), y0(y0), y1(y1), z0(z0), z1(z1), r(r), g(g), b(b), a(a)
{
}

void PutBox::draw(Sculptor &s)
{
    s.setColor(r, g, b,a);
    s.putBox(x0, x1, y0, y1, z0, z1);
}