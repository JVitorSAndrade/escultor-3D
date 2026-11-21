#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "../Sculptor.h"
#include "FiguraGeometrica.h"
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
    std::ifstream arquivo("parte2/comandos.txt");

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir arquivo!" << std::endl;
        return 1;
    }

    int nx = 0, ny = 0, nz = 0;

    std::vector<std::unique_ptr<FiguraGeometrica>> figuras;

    std::string linha;

    while (std::getline(arquivo, linha))
    {
        std::stringstream ss(linha);
        std::string comando;

        if (!(ss >> comando))
        {
            continue;
        }

        if (comando == "dim")
        {
            if (!(ss >> nx >> ny >> nz))
            {
                std::cout << "Erro ao ler dimensoes!" << std::endl;
                return 1;
            }

            if (nx <= 0 || ny <= 0 || nz <= 0)
            {
                std::cout << "Dimensoes invalidas!" << std::endl;
                return 1;
            }

            std::cout << "Dimensoes: " << nx << " x " << ny << " x " << nz << std::endl;
        }

        else if (comando == "putvoxel")
        {
            int x, y, z;
            float r, g, b, a;

            if (!(ss >> x >> y >> z >> r >> g >> b >> a))
            {
                std::cout << "Erro nos parametros de putvoxel!" << std::endl;
                return 1;
            }

            figuras.push_back(std::make_unique<PutVoxel>(x, y, z, r, g, b, a));
        }

        else if (comando == "cutvoxel")
        {
            int x, y, z;

            if (!(ss >> x >> y >> z))
            {
                std::cout << "Erro nos parametros de cutvoxel!" << std::endl;
                return 1;
            }

            figuras.push_back(std::make_unique<CutVoxel>(x, y, z));
        }

        else if (comando == "putbox")
        {
            int x0, x1, y0, y1, z0, z1;
            float r, g, b, a;

            if (!(ss >> x0 >> x1 >> y0 >> y1 >> z0 >> z1 >> r >> g >> b >> a))
            {
                std::cout << "Erro nos parametros de putbox!" << std::endl;
                return 1;
            }

            figuras.push_back(std::make_unique<PutBox>(x0, x1, y0, y1, z0, z1, r, g, b, a));
        }

        else if (comando == "cutbox")
        {
            int x0, x1, y0, y1, z0, z1;

            if (!(ss >> x0 >> x1 >> y0 >> y1 >> z0 >> z1))
            {
                std::cout << "Erro nos parametros de cutbox!" << std::endl;
                return 1;
            }

            figuras.push_back(std::make_unique<CutBox>(x0, x1, y0, y1, z0, z1));
        }

        else if (comando == "putsphere")
        {
            int xcenter, ycenter, zcenter, radius;
            float r, g, b, a;

            if (!(ss >> xcenter >> ycenter >> zcenter >> radius >> r >> g >> b >> a))
            {
                std::cout << "Erro nos parametros de putsphere!" << std::endl;
                return 1;
            }

            figuras.push_back(std::make_unique<PutSphere>(xcenter, ycenter, zcenter, radius, r, g, b, a));
        }

        else if (comando == "cutsphere")
        {
            int xcenter, ycenter, zcenter, radius;

            if (!(ss >> xcenter >> ycenter >> zcenter >> radius))
            {
                std::cout << "Erro nos parametros de cutsphere!" << std::endl;
                return 1;
            }

            figuras.push_back(std::make_unique<CutSphere>(xcenter, ycenter, zcenter, radius));
        }

        else if (comando == "putellipsoid")
        {
            int xcenter, ycenter, zcenter, rx, ry, rz;
            float r, g, b, a;

            if (!(ss >> xcenter >> ycenter >> zcenter >> rx >> ry >> rz >> r >> g >> b >> a))
            {
                std::cout << "Erro nos parametros de putellipsoid!" << std::endl;
                return 1;
            }

            figuras.push_back(std::make_unique<PutEllipsoid>(xcenter, ycenter, zcenter, rx, ry, rz, r, g, b, a));
        }

        else if (comando == "cutellipsoid")
        {
            int xcenter, ycenter, zcenter, rx, ry, rz;

            if (!(ss >> xcenter >> ycenter >> zcenter >> rx >> ry >> rz))
            {
                std::cout << "Erro nos parametros de cutellipsoid!" << std::endl;
                return 1;
            }

            figuras.push_back(std::make_unique<CutEllipsoid>(xcenter, ycenter, zcenter, rx, ry, rz));
        }
        else
        {
            std::cout << "Comando desconhecido: " << comando << std::endl;
            return 1;
        }
    }

    arquivo.close();

    if (nx <= 0 || ny <= 0 || nz <= 0)
    {
        std::cout << "Dimensoes nao definidas!" << std::endl;
        return 1;
    }

    Sculptor escultura(nx, ny, nz);

    for (const auto &figura : figuras)
    {
        figura->draw(escultura);
    }

    escultura.writeOFF("escultura_final_saturno.off");

    std::cout << "Escultura gerada com sucesso!" << std::endl;
    std::cout << "Operacoes executadas: " << figuras.size() << std::endl;

    return 0;
}
