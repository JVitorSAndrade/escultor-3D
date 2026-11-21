# 🪐 Escultor 3D — C++

Projeto desenvolvido em **C++** para a disciplina de Programação Avançada da UFRN.

O objetivo é criar esculturas tridimensionais utilizando **voxels**, permitindo desenhar e remover formas geométricas e exportar os resultados para arquivos no formato `.off`, que podem ser visualizados no MeshLab.

## 📌 Funcionalidades

- Criação de matrizes tridimensionais de voxels.
- Desenho e remoção de voxels, caixas, esferas e elipsoides.
- Definição de cores e transparência.
- Leitura de comandos geométricos a partir de arquivos `.txt`.
- Exportação de esculturas no formato `.off`.

## 📂 Organização do projeto

**Parte 1 — Estruturas básicas**

Implementação da classe `Sculptor`, responsável pela manipulação dos voxels e pelas operações geométricas.

**Parte 2 — Estruturas avançadas**

Implementação da classe abstrata `FiguraGeometrica` e suas classes derivadas, utilizando conceitos de herança e polimorfismo para interpretar comandos e gerar esculturas.

## 🪐 Escultura desenvolvida

Como demonstração das funcionalidades, foi criada uma representação tridimensional de **Saturno**, com um planeta azul e um anel dourado.

A escultura final está disponível no arquivo `escultura_final_saturno.off`.

## 🛠️ Tecnologias utilizadas

- C++17
- Programação Orientada a Objetos (POO)
- Git e GitHub
- MeshLab

---

Projeto acadêmico desenvolvido para fins de aprendizagem e aplicação dos conceitos de programação em C++.
