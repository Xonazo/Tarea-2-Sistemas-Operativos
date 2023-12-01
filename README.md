# Tarea 2 Sistemas operativos

## Integrantes
- **Edison Muñoz** -  20.514.683-0
- **Domingo Vega** -  20.731.242-8
- **Ingenieria Civil Informatica** - **Universidad del Bío-Bío.**

## Descripción
Supongamos que tiene una imagen a color representada como una matriz bidimensional de pıxeles.
La tarea consiste en aplicar un filtro a dicha imagen para transformala a escala de grises (sin utilizar alguna funcion o metodo disponible, debe ser mediante la manipulacion de la matriz que representa la imagen).
Debe implementar una version secuencial funcional y dos versiones paralelas, una de ellas utilizando la clase thread1 y otra utilizando la API OpenMP2 (Revisar practicos de la Leccion 4 en moodle).
Para leer una imagen y manipularla como una matriz de pıxeles utilizar la librerıa OpenCV3.
En Debian (y distribuciones basadas en) debe instalar el paquete libopencv-dev.
Para convertir a escala de grises existen varios metodos.
En esta tarea debe utilizar el metodo de luminosidad (Luminosity Method).
El enfoque paralelo puede consistir en dividir la imagen en varias partes y asignar cada parte a una hebra para que aplique las modificaciones de manera independiente.

## Consideraciones
* El programa debe correr en equipos con sistema operativo Linux.
* Debe utilizar el lenguaje de programacion C++.
* Debe utilizar el compilador GNU g++.
* Debe utilizar un archivo Makefile por cada version (secuencial y las paralelas) para la compilacion mediante el comando make. Organice su proyecto como sea mas conveniente.
* Utilizar imagenes de prueba de gran tamaño (megas o gigabytes) para apreciar mejor las ventajas de la paralelizacion.
* Realizar pruebas utilizando difentes numeros de hebras para obtener medidas de rendimiento.
* No olvidar un archivo README por cada versi´on con las intrucciones para compilar y ejecutar los programas.
* Para medir tiempo de ejecucion utilice la clase chrono5.
* La tarea es en parejas.
* Los programas deben compilar para ser revisados.
 ## Importante
* *Para las pruebas se recomienda usar la imagen "prueba.jpg", la cual es una imagen modificada para que pese mas. **
* En caso de usar otras imagenes estan deben estar en formato ".jpg"*

## Parametros de entrada
* Nombre imagen a color a procesar.
* Nombre imagen a escala de grises a generar.
* Numero de hebras a utilizar (solo para las versiones paralelas).

## Salida
* Una nueva imagen a escala de grises.
* Tiempo de ejecucion total (en segundos).

# Pasos previos:

## Requisitos
* Tener instalado el compilador de C++.
* Tener instalado el programa make.
* Tener instalado OpenCV3 o libopencv-dev dependiendo de su sistema.

## Como instalar el compilador de C++
* Para instalar el compilador de C++, se debe escribir y ejecutar el siguiente comando en la terminal:
```
sudo apt-get install g++
```

## Como instalar el programa make
* Para instalar el programa make, se debe escribir y ejecutar el siguiente comando en la terminal:
```
sudo apt-get install make
```
