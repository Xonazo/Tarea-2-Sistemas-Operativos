#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <mutex>

using namespace cv;
using namespace std;

void applyFilterThreaded(Mat& inputImage, Mat& outputImage, int startRow, int endRow) {
    // Se comienza a iterar por cada pixel de la imagen
    for (int r = startRow; r < endRow; ++r) {
        for (int c = 0; c < inputImage.cols; ++c) {
            Vec3b pixel = inputImage.at<Vec3b>(r, c);
            uchar grayValue = static_cast<uchar>(0.3 * pixel[2] + 0.59 * pixel[1] + 0.11 * pixel[0]);
            outputImage.at<uchar>(r, c) = grayValue;
        }
    }
}

// Se aplica el filtro para cada hilo
void applyFilterParallel(Mat& inputImage, Mat& outputImage, int numThreads) {
    // Se verifica que las dimensiones de entrada y salida coincidan
    int rows = inputImage.rows;
    int chunkSize = rows / numThreads;
    vector<thread> threads;

    // Se crean los hilos
    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * chunkSize;
        int endRow = (i == numThreads - 1) ? rows : (i + 1) * chunkSize;
        threads.emplace_back(applyFilterThreaded, ref(inputImage), ref(outputImage), startRow, endRow);
    }

    // Se espera a que los hilos terminen
    for (auto& t : threads) {
        t.join();
    }
}

int main(int argc, char** argv) {
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida> <num_hilos>" << endl;
        return -1;
    }

    Mat inputImage = imread(argv[1], IMREAD_COLOR);

    if (inputImage.empty()) {
        cerr << "Error al leer la imagen de entrada." << endl;
        return -1;
    }

    Mat outputImage(inputImage.rows, inputImage.cols, CV_8UC1);

    int numThreads = atoi(argv[3]);

    // Se mide el tiempo de ejecucion
    auto start = chrono::high_resolution_clock::now();

    // Se aplica el filtro para cada hilo
    applyFilterParallel(inputImage, outputImage, numThreads);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    imwrite(argv[2], outputImage);

    // Se muestra el tiempo de ejecucion
    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}

