#include "Sculptor.h"
#include <stdexcept> //uma biblioteca q oferece classes com métodos para tratar erros
#include <fstream>   //biblioteca q nos permite trabalhar com arquivos
#include <iostream>
#include <iomanip>

Sculptor::Sculptor(int _nx, int _ny, int _nz)
    : v(nullptr), nx(_nx), ny(_ny), nz(_nz),
      r(0), g(0), b(0), a(1)
{
    if (nx <= 0 || ny <= 0 || nz <= 0)
    {
        throw std::invalid_argument("Dimensoes invalidas");
    }

    v = new Voxel **[nx];

    for (int x = 0; x < nx; x++)
    {
        v[x] = new Voxel *[ny];

        for (int y = 0; y < ny; y++)
        {
            v[x][y] = new Voxel[nz]{};
        }
    }
}

// DESTRUTOR
Sculptor::~Sculptor()
{
    for (int x = 0; x < nx; x++)
    {
        for (int y = 0; y < ny; y++)
        {
            delete[] v[x][y];
        }

        delete[] v[x];
    }

    delete[] v;
}

// SETCOLOR
void Sculptor::setColor(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
};

// PUTVOXEL
void Sculptor::putVoxel(int x, int y, int z)
{
    if (x < 0 || x >= nx ||
        y < 0 || y >= ny ||
        z < 0 || z >= nz)
    {
        return;
    }

    v[x][y][z].show = true;

    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}

// CUTVOXEL
void Sculptor::cutVoxel(int x, int y, int z)
{
    if (x < 0 || x >= nx ||
        y < 0 || y >= ny ||
        z < 0 || z >= nz)
    {
        return;
    }

    v[x][y][z].show = false;
}

// PUTBOX
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for (int i = x0; i <= x1; i++)
    {
        for (int j = y0; j <= y1; j++)
        {
            for (int k = z0; k <= z1; k++)
            {
                putVoxel(i, j, k);
            }
        }
    }
}

// CUTBOX
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for (int i = x0; i <= x1; i++)
    {
        for (int j = y0; j <= y1; j++)
        {
            for (int k = z0; k <= z1; k++)
            {
                cutVoxel(i, j, k);
            }
        }
    }
}

// WRITEOFF
void Sculptor::writeOFF(const char *filename)
{
    std::ofstream arquivo(filename);

    if (!arquivo)
    {
        std::cerr << "Erro ao criar arquivo OFF!" << std::endl;
        return;
    }

    // CONTAR OS VOXELS
    int totalVoxels = 0; // contador

    for (int x = 0; x < nx; x++)
    {
        for (int y = 0; y < ny; y++)
        {
            for (int z = 0; z < nz; z++)
            {
                if (v[x][y][z].show) // aqui pegamos apenas os voxels ativos
                {
                    totalVoxels++;
                }
            }
        }
    }

    // CABEÇALHO
    arquivo << "OFF\n";
    arquivo << totalVoxels * 8 << " "
            << totalVoxels * 6 << " 0\n"; // 0 é o numero de arestas nao informado

    // VERTICES
    for (int x = 0; x < nx; x++)
    {
        for (int y = 0; y < ny; y++)
        {
            for (int z = 0; z < nz; z++)
            {
                if (!v[x][y][z].show)
                {
                    continue;
                }

                arquivo << x - 0.5 << " " << y + 0.5 << " " << z - 0.5 << "\n";
                arquivo << x - 0.5 << " " << y - 0.5 << " " << z - 0.5 << "\n";
                arquivo << x + 0.5 << " " << y - 0.5 << " " << z - 0.5 << "\n";
                arquivo << x + 0.5 << " " << y + 0.5 << " " << z - 0.5 << "\n";

                arquivo << x - 0.5 << " " << y + 0.5 << " " << z + 0.5 << "\n";
                arquivo << x - 0.5 << " " << y - 0.5 << " " << z + 0.5 << "\n";
                arquivo << x + 0.5 << " " << y - 0.5 << " " << z + 0.5 << "\n";
                arquivo << x + 0.5 << " " << y + 0.5 << " " << z + 0.5 << "\n";
            }
        }
    }

    // FACES
    const int faces[6][4] = {
        {0, 3, 2, 1},
        {4, 5, 6, 7},
        {0, 1, 5, 4},
        {0, 4, 7, 3},
        {3, 7, 6, 2},
        {1, 2, 6, 5}};

    int base = 0;

    arquivo << std::fixed << std::setprecision(6); // precisao de numeros

    for (int x = 0; x < nx; x++)
    {
        for (int y = 0; y < ny; y++)
        {
            for (int z = 0; z < nz; z++)
            {
                if (!v[x][y][z].show)
                {
                    continue;
                }

                const Voxel &voxel = v[x][y][z]; // ref ao voxel atual para acessar suas cores

                for (int f = 0; f < 6; f++)
                {
                    arquivo << "4";

                    for (int i = 0; i < 4; i++)
                    {
                        arquivo << " " << base + faces[f][i];
                    }

                    arquivo << " "
                            << voxel.r << " "
                            << voxel.g << " "
                            << voxel.b << " "
                            << voxel.a << "\n";
                }

                base += 8;
            }
        }
    }

    arquivo.close();
}

// PUTESFERA
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    if (radius < 0)
    {
        return;
    }

    for (int x = 0; x < nx; x++)
    {
        for (int y = 0; y < ny; y++)
        {
            for (int z = 0; z < nz; z++)
            {
                if (((x - xcenter) * (x - xcenter) + (y - ycenter) * (y - ycenter) + (z - zcenter) * (z - zcenter)) <= (radius) * (radius))
                {
                    putVoxel(x, y, z);
                }
            }
        }
    }
}

// CUTESFERA
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    if (radius < 0)
    {
        return;
    }

    for (int x = 0; x < nx; x++)
    {
        for (int y = 0; y < ny; y++)
        {
            for (int z = 0; z < nz; z++)
            {
                if (((x - xcenter) * (x - xcenter) + (y - ycenter) * (y - ycenter) + (z - zcenter) * (z - zcenter)) <= (radius) * (radius))
                {
                    cutVoxel(x, y, z);
                }
            }
        }
    }
}

// PUTELLIPSOID
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    if (rx <= 0 || ry <= 0 || rz <= 0)
    {
        return;
    }

    for (int x = 0; x < nx; x++)
    {
        for (int y = 0; y < ny; y++)
        {
            for (int z = 0; z < nz; z++)
            {
                double dx = (x - xcenter) / static_cast<double>(rx); // static_cast: gera um valor convertido para double... converte o valor dentro da variavel, nao a variavel em si
                double dy = (y - ycenter) / static_cast<double>(ry);
                double dz = (z - zcenter) / static_cast<double>(rz);

                if (dx * dx + dy * dy + dz * dz <= 1.0)
                {
                    putVoxel(x, y, z);
                }
            }
        }
    }
}

// CUTELLIPSOID
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    if (rx <= 0 || ry <= 0 || rz <= 0)
    {
        return;
    }

    for (int x = 0; x < nx; x++)
    {
        for (int y = 0; y < ny; y++)
        {
            for (int z = 0; z < nz; z++)
            {
                double dx = (x - xcenter) / static_cast<double>(rx);
                double dy = (y - ycenter) / static_cast<double>(ry);
                double dz = (z - zcenter) / static_cast<double>(rz);

                if (dx * dx + dy * dy + dz * dz <= 1.0)
                {
                    cutVoxel(x, y, z);
                }
            }
        }
    }
}