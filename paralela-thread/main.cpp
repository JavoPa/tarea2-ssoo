#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <vector>

using namespace cv;
using namespace std;
using namespace chrono;

void convertToGrayscale(Mat &image, int start_row, int end_row)
{
    for (int r = start_row; r < end_row; r++)
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
    const int num_threads = stoi(argv[3]);

    Mat image = imread(inputFileName, IMREAD_COLOR);

    if (image.empty())
    {
        cerr << "Error: Debe de ingresar una imagen a color valida" << endl;
        return -1;
    }

    int rows_per_thread = image.rows / num_threads;
    int start_row = 0;

    vector<thread> threads;

    for (int i = 0; i < num_threads - 1; i++)
    {
        int end_row = start_row + rows_per_thread;
        threads.emplace_back(convertToGrayscale, ref(image), start_row, end_row);
        start_row = end_row;
    }

    //El ultimo hilo se encarga de las filas restantes
    threads.emplace_back(convertToGrayscale, ref(image), start_row, image.rows);

    //Espera a todos los hilos para terminar
    for (auto &t : threads)
    {
        t.join();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    imwrite(outputFileName, image);

    cout << "Loading image..." << endl;
    cout << "Rows (height): " << image.rows << " Cols (width): " << image.cols << endl;
    cout << "Start conversion..." << endl;
    cout << "End conversion..." << endl;
    cout << "Total time spent in seconds: " << duration.count() / 1000.0 << endl;

    return 0;
}