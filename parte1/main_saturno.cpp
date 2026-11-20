#include <iostream>
#include "../Sculptor.h"

int main()
{
    Sculptor escultura(80, 80, 80);

    // planeta
    escultura.setColor(0, 0, 0.9, 1.0);
    escultura.putSphere(40, 40, 40, 18);

    // anel do planeta
    escultura.setColor(1.0, 0.75, 0.05, 1.0);

    for (int x = 0; x < 80; x++)
    {
        for (int y = 0; y < 80; y++)
        {
            int dx = x - 40;
            int dy = y - 40;

            int distancia2 = dx * dx + dy * dy;

            if (distancia2 >= 20 * 20 &&
                distancia2 <= 31 * 31)
            {
                for (int z = 38; z <= 42; z++)
                {
                    escultura.putVoxel(x, y, z);
                }
            }
        }
    }

    escultura.writeOFF("saturno.off");

    std::cout << "planeta gerado! :)" << std::endl;

    return 0;
}