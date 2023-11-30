#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <mutex>

using namespace cv;
using namespace std;

void applyFilterThreaded(Mat& inputImage, Mat& outputImage, int startRow, int endRow) {
    for (int r = startRow; r < endRow; ++r) {
        for (int c = 0; c < inputImage.cols; ++c) {
            Vec3b pixel = inputImage.at<Vec3b>(r, c);
            uchar grayValue = static_cast<uchar>(0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0]);
            outputImage.at<uchar>(r, c) = grayValue;
        }
    }
}

void applyFilterParallel(Mat& inputImage, Mat& outputImage, int numThreads) {
    int rows = inputImage.rows;
    int chunkSize = rows / numThreads;
    vector<thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * chunkSize;
        int endRow = (i == numThreads - 1) ? rows : (i + 1) * chunkSize;
        threads.emplace_back(applyFilterThreaded, ref(inputImage), ref(outputImage), startRow, endRow);
    }

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

    auto start = chrono::high_resolution_clock::now();

    applyFilterParallel(inputImage, outputImage, numThreads);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    imwrite(argv[2], outputImage);

    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}

