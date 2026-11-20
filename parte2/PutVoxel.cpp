#include "PutVoxel.h"

PutVoxel::PutVoxel(int x, int y, int z, float r, float g, float b, float a)
    : x(x), y(y), z(z), r(r), g(g), b(b), a(a)
{
}

void PutVoxel::draw(Sculptor &s)
{
    s.setColor(r, g, b, a);
    s.putVoxel(x, y, z);
}