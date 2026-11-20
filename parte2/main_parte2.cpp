#include <iostream>
#include "../Sculptor.h"
#include "PutVoxel.h"
#include "CutVoxel.h"
#include "PutBox.h"
#include "CutBox.h"
#include "PutSphere.h"
#include "CutSphere.h"
#include "PutEllipsoid.h"
#include "CutEllipsoid.h"

int main()
{
    Sculptor escultura(40, 40, 40);

    PutEllipsoid ellipsoid(20, 20, 20, 10, 6, 8, 1.0, 0.84, 0.0, 1.0);
    CutEllipsoid ellipsoid2(26, 20, 20, 4, 3, 4);
    
    ellipsoid.draw(escultura);
    ellipsoid2.draw(escultura);

    escultura.writeOFF("teste_parte2_Ellipsoid.off");

    std::cout << "Teste Ellipsoid concluido!" << std::endl;

    return 0;
}