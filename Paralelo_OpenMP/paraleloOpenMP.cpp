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

    int rows = inputImage.rows;
    int cols = inputImage.cols;

    #pragma omp parallel for
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            Vec3b pixel = inputImage.at<Vec3b>(r, c);

            uchar grayValue = static_cast<uchar>(0.21 * pixel[2] + 0.72 * pixel[1] + 0.07 * pixel[0]);

            #pragma omp critical
            outputImage.at<uchar>(r, c) = grayValue;
        }
    }
}


int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida>" << endl;
        return -1;
    }

    Mat inputImage = imread(argv[1], IMREAD_COLOR);

    if (inputImage.empty()) {
        cerr << "Error al leer la imagen de entrada." << endl;
        return -1;
    }

    Mat outputImage(inputImage.rows, inputImage.cols, CV_8UC1);

    auto start = chrono::high_resolution_clock::now();

    applyFilterParallel(inputImage, outputImage);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    imwrite(argv[2], outputImage);

    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}