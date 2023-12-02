#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <omp.h>

using namespace cv;
using namespace std;
using namespace chrono;

void convertToGrayscale(Mat &image)
{
#pragma omp parallel for
    for (int r = 0; r < image.rows; r++)
    {
        for (int c = 0; c < image.cols; c++)
        {
            Point3_<uchar> *p = image.ptr<Point3_<uchar>>(r, c);
            uchar gray = static_cast<uchar>(0.299 * p->z + 0.587 * p->y + 0.114 * p->x);
            p->x = p->y = p->z = gray;
        }
    }
}

int main(int argc, char **argv)
{
    auto start = high_resolution_clock::now();

    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " <input_image> <output_image> <num_threads>" << endl;
        return -1;
    }

    const string inputFileName = argv[1];
    const string outputFileName = argv[2];
    const int requested_num_threads = stoi(argv[3]);

    Mat image = imread(inputFileName, IMREAD_COLOR);

    if (image.empty())
    {
        cerr << "Error: Debe de ingresar una imagen a color valida" << endl;
        return -1;
    }

    // Obtener el número máximo de hilos disponibles
    int max_threads = omp_get_max_threads();

    // Determinar el número de hilos a utilizar
    int num_threads = requested_num_threads > 0 ? min(requested_num_threads, max_threads) : max_threads;

    // Establecer el número de hilos
    omp_set_num_threads(num_threads);

    cout << "Number of threads: " << num_threads << endl;

    cout << "Loading image..." << endl;
    cout << "Rows (height): " << image.rows << " Cols (width): " << image.cols << endl;

    auto conversion_start = high_resolution_clock::now();

    // Llamada a la función de conversión paralela
    convertToGrayscale(image);

    auto conversion_stop = high_resolution_clock::now();
    auto conversion_duration = duration_cast<milliseconds>(conversion_stop - conversion_start);

    imwrite(outputFileName, image);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Start conversion..." << endl;
    cout << "End conversion..." << endl;
    cout << "Total time spent in seconds: " << duration.count() / 1000.0 << endl;
    cout << "Conversion time: " << conversion_duration.count() << " Milliseconds" << endl;

    return 0;
}
