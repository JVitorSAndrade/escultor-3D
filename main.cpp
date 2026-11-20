#include <iostream>
#include "Sculptor.h"

int main()
{
    Sculptor escultura(80, 40, 40);

    escultura.setColor(0, 0, 0.9, 1.0);
    escultura.putVoxel(2, 5, 5);
    escultura.putVoxel(3, 5, 5);
    escultura.cutVoxel(3, 5, 5);
    
    escultura.setColor(0.9, 0, 0, 1.0);
    escultura.putBox(10, 24, 8, 24, 8, 24);
    escultura.cutBox(15, 21, 15, 24, 15, 24);
    
    escultura.setColor(0, 0, 0.9, 1.0);
    escultura.putSphere(39, 16, 16, 9);
    escultura.cutSphere(44, 16, 16, 5);
    
    escultura.setColor(1, 0.843, 0, 1.0);
    escultura.putEllipsoid(62, 16, 16, 10, 6, 8);
    escultura.cutEllipsoid(67, 16, 16, 5, 4, 5);

    escultura.writeOFF("teste_completo.off");

    std::cout << "Teste completo gerado!" << std::endl;

    return 0;
}