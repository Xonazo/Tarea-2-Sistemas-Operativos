// tarea_secuencial.cpp
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


// Función que aplica el filtro a la imagen de manera secuencial
void applyFilterSequential(Mat& inputImage, Mat& outputImage) {
    // Verificar que las dimensiones de entrada y salida coincidan
    if (inputImage.size() != outputImage.size()) {
        cerr << "Error: Las dimensiones de entrada y salida no coinciden." << endl;
        return;
    }

    // Obtener el numero de filas y columnas de la imagen
    int rows = inputImage.rows;
    int cols = inputImage.cols;

    // Iterar sobre cada pixel de la imagen
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            //Se obtiene el valor del pixel en formato BGR
            Vec3b pixel = inputImage.at<Vec3b>(r, c);

            // Se calcula el valor del pixel en la imagen de salida
            uchar grayValue = static_cast<uchar>(0.3 * pixel[2] + 0.59 * pixel[1] + 0.11 * pixel[0]);
            // Se asigna el valor del pixel en la imagen de salida
            outputImage.at<uchar>(r, c) = grayValue;
        }
    }
}


int main(int argc, char** argv) {
    // Verificar los parametros de entrada
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida>" << endl;
        return -1;
    }

    // Leer la imagen de entrada
    Mat inputImage = imread(argv[1], IMREAD_COLOR);

    // Se verifica que la imagen se haya leido correctamente
    if (inputImage.empty()) {
        cerr << "Error al leer la imagen de entrada." << endl;
        return -1;
    }

    //Se crea la imagen de salida
    Mat outputImage(inputImage.rows, inputImage.cols, CV_8UC1);

    // Medir tiempo de ejecución
    auto start = chrono::high_resolution_clock::now();

    // Aplicar el filtro a la imagen
    applyFilterSequential(inputImage, outputImage);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    // Guardar la imagen de salida
    imwrite(argv[2], outputImage);

    // Mostrar el tiempo de ejecucion
    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}
