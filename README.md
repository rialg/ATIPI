# ATIPI
Proyecto de evaluación: Compresión/Decompresión de imágenes en colores

## Preferencias del sistema para compilar el proyecto
* MacOS (Catalina 10.15.6): Compilar con ```clang++``` version 11
* Ubuntu 18.04 y 20.04: Compilar con ```gcc-9/g++-9``` version 9 (o superior)

## Como crear ejecutable
1. ```$ mkdir build```
2. ```$ cd build/```
3. ```$ cmake ..```
4. ```$ make```

## Ejemplo de compresión de imágenes de tono gris
1. ```$ ./Compressor test/Imagenes-LOCO-PGM+PPM/barbara.pgm 5```

## Ejemplos de compresión de imágenes a color
1. ```$ ./Compressor test/Imagenes-LOCO-PGM+PPM/kodim07.ppm 5 A```
2. ```$ ./Compressor test/Imagenes-LOCO-PGM+PPM/kodim24.ppm 5 B```

## Ejemplos de decompresión
1. ```$ ./Compressor -d barbara.loco```
2. ```$ ./Compressor -d kodim07.loco```
3. ```$ ./Compressor -d kodim24.loco```

## Alternativa: Imagen de Docker
1. Instalar [Docker](https://docs.docker.com/get-docker/)
2. Ejecutar el script ```scripts/ubuntu_compressor.bash```. Por ejemplo:
    2.1 ```$ bash scripts/ubuntu_compressor.bash test/Imagenes-LOCO-PGM+PPM/barbara.pgm 5```
    2.2 ```$ bash scripts/ubuntu_compressor.bash test/Imagenes-LOCO-PGM+PPM/kodim07.ppm 5 A```
    2.3 ```$ bash scripts/ubuntu_compressor.bash test/Imagenes-LOCO-PGM+PPM/kodim24.ppm 5 B```
    2.4 ```$ bash scripts/ubuntu_compressor.bash -d barbara.loco```
    2.5 ```$ bash scripts/ubuntu_compressor.bash -d kodim07.loco```
    2.6 ```$ bash scripts/ubuntu_compressor.bash -d kodim24.loco```

## Documentación
[archivos de Compressor](./docs/index.html)