// tarea_secuencial.cpp
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void applyFilterSequential(Mat& inputImage, Mat& outputImage) {
    // Verificar si las dimensiones de entrada coinciden con las de salida
    if (inputImage.size() != outputImage.size()) {
        cerr << "Error: Las dimensiones de entrada y salida no coinciden." << endl;
        return;
    }

    // Obtener el número de filas y columnas de la imagen
    int rows = inputImage.rows;
    int cols = inputImage.cols;

    // Iterar sobre cada píxel de la imagen
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // Obtener los valores de los canales RGB en el píxel actual
            Vec3b pixel = inputImage.at<Vec3b>(r, c);

            // Calcular el valor de luminosidad y asignarlo al píxel de salida
            uchar grayValue = static_cast<uchar>(0.3 * pixel[2] + 0.59 * pixel[1] + 0.11 * pixel[0]);
            outputImage.at<uchar>(r, c) = grayValue;
        }
    }
}


int main(int argc, char** argv) {
    // Parsear argumentos de entrada
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida>" << endl;
        return -1;
    }

    // Leer la imagen de entrada
    Mat inputImage = imread(argv[1], IMREAD_COLOR);

    // Verificar si la imagen se leyó correctamente
    if (inputImage.empty()) {
        cerr << "Error al leer la imagen de entrada." << endl;
        return -1;
    }

    // Crear la imagen de salida en escala de grises
    Mat outputImage(inputImage.rows, inputImage.cols, CV_8UC1);

    // Medir tiempo de ejecución
    auto start = chrono::high_resolution_clock::now();

    // Aplicar el filtro secuencial
    applyFilterSequential(inputImage, outputImage);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    // Guardar la imagen de salida
    imwrite(argv[2], outputImage);

    // Imprimir tiempo de ejecución
    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}
