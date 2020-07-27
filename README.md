# ATIPI
Proyecto de evaluación: Compresión/Decompresión de imágenes en colores

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

## Documentación
[archivos de Compressor](./docs/index.html)