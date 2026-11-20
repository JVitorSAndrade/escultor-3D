#include "CutVoxel.h"

CutVoxel::CutVoxel(int x, int y, int z)
    : x(x), y(y), z(z)
{
}

void CutVoxel::draw(Sculptor &s)
{
    s.cutVoxel(x, y, z);
}