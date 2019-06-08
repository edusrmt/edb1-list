# Lista Encadeada

## Sumário

- **[1. Introdução](#1-introdução)**
- **[2. Compilando](#2-compilando)**
- **[3. Testes](#3-testes)**
- **[4. Uso](#4-uso)**
- **[5. Autoria](#5-autoria)**

## 1. Introdução

Esse projeto implementa uma lista de Tipo de Dado Abstrato, baseado em uma lista duplamente encadeada.
Um projeto semelhante a este, porém baseado em vector também [foi desenvolvido](http://github.com/victorvieirar/project-vector).

## 2. Compilando

Esse projeto pode ser compilado utilizando o [CMake](http://cmake.org). CMake é uma ferramenta _open_souce_ que constroi, testa e empacota _softwares_. Basicamente, CMake lê um script `CMakeLists.txt` com uma _meta-information_ no projeto e cria um arquivo chamado `Makefile`, automaticamente, de acordo com seu sistema. Logo em seguida, você compila utilizando o comando `make`. 

Para compilar esse projeto você pode rodar esses comando na pasta raíz.

- `cmake -G "Unix Makefiles" ..`: Diz ao CMake para criar o arquivo `Makefile` baseado no script `CMakeLists.txt`.
- `make`: Compila o código do projeto e gera um executável na pasta `./bin`.

## 3. Testes

Utilizamos um arquivo de testes e o `CMakeLists.txt` foi escrito com esse arquivo sendo o executável a ser criado, ou seja, no processo de compilação, você poderá gerar, automaticamente, um executável na pasta `./bin` com o nome `run_tests` e, ao executá-lo, você verificará todos os métodos criados de várias maneiras e poderá explorar a capacidade da aplicação.

## 4. Uso

Você poderá verificar a documentação gerada pelo [Doxygen](http://www.doxygen.nl/) para conferir os métodos das classes e seus respectivos usos.

## 5. Autoria

Os autores desse projeto são **Carlos Eduardo Alves Sarmento** < _cealvesarmento@gmail.com_ > e **Victor Raphaell Vieira Rodrigues** < _victorvieira89@gmail.com_ >.
