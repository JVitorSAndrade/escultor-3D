#include <iostream>
#include "Sculptor.h"

int main()
{
    Sculptor planeta(30, 30, 30);

    planeta.setColor(0.0, 0.2, 1.0, 1.0);

    planeta.putSphere(15, 15, 15, 10);

    planeta.writeOFF("planeta.off");

    std::cout << "Planeta gerado!" << std::endl;

    return 0;
}