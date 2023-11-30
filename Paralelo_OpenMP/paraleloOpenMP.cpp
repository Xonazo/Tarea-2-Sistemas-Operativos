#include <iostream>
#include <opencv2/opencv.hpp>
#include <omp.h>

using namespace cv;
using namespace std;

void applyFilterParallel(Mat& inputImage, Mat& outputImage) {
    if (inputImage.size() != outputImage.size()) {
        cerr << "Error: Las dimensiones de entrada y salida no coinciden." << endl;
        return;
    }

    // Se obtienen las dimensiones de la imagen en base a filas y columnas
    int rows = inputImage.rows;
    int cols = inputImage.cols;

    #pragma omp parallel
    {
        // Se obtiene el numero de los hilos
        int numThreads = omp_get_num_threads();
        int threadId = omp_get_thread_num();
        // Se calcula el tamaño de cada chunk
        int chunkSize = rows / numThreads;
        int startRow = threadId * chunkSize;
        int endRow = (threadId == numThreads - 1) ? rows : (threadId + 1) * chunkSize;

        // Se comienza a iterar por cada pixel de la imagen
        for (int r = startRow; r < endRow; ++r) {
            for (int c = 0; c < cols; ++c) {
                Vec3b pixel = inputImage.at<Vec3b>(r, c);
                uchar grayValue = static_cast<uchar>(0.21 * pixel[2] + 0.72 * pixel[1] + 0.07 * pixel[0]);
                outputImage.at<uchar>(r, c) = grayValue;
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 4) {
        // Se verifica que se ingresen los datos de entrada
        cerr << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida> <num_hilos>" << endl;
        return -1;
    }

    Mat inputImage = imread(argv[1], IMREAD_COLOR);

    if (inputImage.empty()) {
        // Se verifica que la imagen se haya leido correctamente
        cerr << "Error al leer la imagen de entrada." << endl;
        return -1;
    }

    Mat outputImage(inputImage.rows, inputImage.cols, CV_8UC1);

    int numThreads = atoi(argv[3]);

    // Se mide el tiempo de ejecucion
    auto start = chrono::high_resolution_clock::now();

    omp_set_num_threads(numThreads);

    applyFilterParallel(inputImage, outputImage);

    // Se obtiene el tiempo de ejecucion
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    imwrite(argv[2], outputImage);

    // Se muestra el tiempo de ejecucion
    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}

