# Instrucciones de uso:

## Complicación
* Para realizar la compilacion del programa "paraleloOpenMP.cpp", se debe entrar en la carpeta que corresponde a Paralelo_OpenMP, donde debera escribir y ejecutar el comando "make" en la terminal, el cual le creara un archivo ejecutable dentro de la misma carpeta.

```
make
```

## Ejecución
* Para realizar la ejecucion del programa recientemente creado con el comando "make", se debe escribir y ejecutar el comando "./openejecutable" en la terminal, seguido de los parametros de entrada y salida y el numero de hebras que desea utilizar. Quedando de la siguiente manera:
```
./openejecutable <inputfile> <outputfile> <numhebras>
```
* Ejemplo:

```
./openejecutable prueba.jpg salida.jpg 2
```


## Eliminación de archivos
* Para eliminar los archivos creados por el comando "make", se debe escribir y ejecutar el comando "make clean" en la terminal, el cual eliminara los archivos creados por el comando "make" en la carpeta que corresponde a Paralelo_OpenMP.

```
make clean
```
