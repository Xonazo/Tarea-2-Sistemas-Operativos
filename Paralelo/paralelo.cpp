#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <mutex>

using namespace cv;
using namespace std;


//Funcion que aplicara el filtro a la imagen
void applyFilterThreaded(Mat& inputImage, Mat& outputImage, int startRow, int endRow) {
    // Se comienza a iterar por cada pixel de la imagen
    for (int r = startRow; r < endRow; ++r) {
        for (int c = 0; c < inputImage.cols; ++c) {
            // Se obtiene el valor del pixel en formato BGR
            Vec3b pixel = inputImage.at<Vec3b>(r, c);
            // Se calcula el valor del pixel en la imagen de salida
            uchar grayValue = static_cast<uchar>(0.3 * pixel[2] + 0.59 * pixel[1] + 0.11 * pixel[0]);
            // Se asigna el valor del pixel en la imagen de salida
            outputImage.at<uchar>(r, c) = grayValue;
        }
    }
}

//Funcion que divide la imagen en hilos
void applyFilterParallel(Mat& inputImage, Mat& outputImage, int numThreads) {
    int rows = inputImage.rows;
    int chunkSize = rows / numThreads;
    vector<thread> threads;

    // Se crean los hilos
    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * chunkSize;
        int endRow = (i == numThreads - 1) ? rows : (i + 1) * chunkSize;
        //Se crea un hilo y se le pasa la funcion que aplicara el filtro
        threads.emplace_back(applyFilterThreaded, ref(inputImage), ref(outputImage), startRow, endRow);
    }

    // Se espera a que los hilos terminen
    for (auto& t : threads) {
        t.join();
    }
}

int main(int argc, char** argv) {
    //Leer la imagen de entrada
    Mat inputImage = imread(argv[1], IMREAD_COLOR);

    //Se crea la imagen de salida
    Mat outputImage(inputImage.rows, inputImage.cols, CV_8UC1);

    //Se obtiene el numero de hilos ingresados por el usuario
    int numThreads = atoi(argv[3]);

    // Se mide el tiempo de ejecucion
    auto start = chrono::high_resolution_clock::now();

    // Aplica el filtro en paralelo
    applyFilterParallel(inputImage, outputImage, numThreads);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    //Se guarda la imagen de salida
    imwrite(argv[2], outputImage);

    // Se muestra el tiempo de ejecucion
    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}

