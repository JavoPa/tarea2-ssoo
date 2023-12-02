#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace chrono;

int main(int argc, char** argv) {

    auto start = high_resolution_clock::now();

    if (argc != 3) {
        cerr << "Error: Debe ingresar el nombre de la imagen a Color y luego el nombre de la imagen en gris" << endl;
        return -1;
    }

    const string inputFileName = argv[1];
    const string outputFileName = argv[2];

    Mat image = imread(inputFileName, IMREAD_COLOR);

    if (image.empty()) {
        cerr << "Error: Debe de ingresar una imagen a color valida" << endl;
        return -1;
    }

    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            Point3_<uchar>* p = image.ptr<Point3_<uchar>>(r, c);
            uchar gray = static_cast<uchar>(0.299 * p->z + 0.587 * p->y + 0.114 * p->x);
            p->x = p->y = p->z = gray;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    imwrite(outputFileName, image);

    cout << "Conversion Completa. Imagen en escala de grises guardada como " << outputFileName << endl;
    cout << "Tiempo de duracion: " << duration.count() << " Milisegundos" << endl;

    return 0;
}