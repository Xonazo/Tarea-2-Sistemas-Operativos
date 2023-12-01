#include <iostream>
#include <opencv2/opencv.hpp>
#include <omp.h>

using namespace cv;
using namespace std;


// Funcion que aplica el filtro a la imagen de manera paralela
void applyFilterParallel(Mat& inputImage, Mat& outputImage) {
    // Se obtienen las dimensiones de la imagen en base a filas y columnas
    int rows = inputImage.rows;
    int cols = inputImage.cols;

    // Se comienza la seccion paralela con OpenMP
    #pragma omp parallel
    {
        // Se obtiene el numero de los hilos
        int numThreads = omp_get_num_threads();

        // Se obtiene el id del hilo
        int threadId = omp_get_thread_num();

        // Se calcula el tamaño de cada "chunk" para divir el trabajo entre los hilos
        int chunkSize = rows / numThreads;
        int startRow = threadId * chunkSize;
        int endRow = (threadId == numThreads - 1) ? rows : (threadId + 1) * chunkSize;

        // Se comienza a iterar por cada pixel de la imagen
        for (int r = startRow; r < endRow; ++r) {
            for (int c = 0; c < cols; ++c) {
                // Se obtiene el valor del pixel en formato BGR
                Vec3b pixel = inputImage.at<Vec3b>(r, c);
                // Se calcula el valor del pixel en la imagen de salida
                uchar grayValue = static_cast<uchar>(0.3 * pixel[2] + 0.59 * pixel[1] + 0.11 * pixel[0]);
                // Se asigna el valor del pixel en la imagen de salida
                outputImage.at<uchar>(r, c) = grayValue;
            }
        }
    }
}

int main(int argc, char** argv) {
    // Se lee la imagen de entrada
    Mat inputImage = imread(argv[1], IMREAD_COLOR);

    // Se crea la imagen de salida
    Mat outputImage(inputImage.rows, inputImage.cols, CV_8UC1);

    // Se obtiene el numero de hilos ingresados por el usuario
    int numThreads = atoi(argv[3]);

    // Se mide el tiempo de ejecucion
    auto start = chrono::high_resolution_clock::now();

    // Se establece el numero de hilos
    omp_set_num_threads(numThreads);

    // Se aplica el filtro a la imagen de manera paralela
    applyFilterParallel(inputImage, outputImage);

    // Se obtiene el tiempo de ejecucion
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    // Se escribe la imagen de salida
    imwrite(argv[2], outputImage);

    // Se muestra el tiempo de ejecucion
    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}

