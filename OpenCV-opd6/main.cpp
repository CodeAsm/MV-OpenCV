#include <opencv2/opencv.hpp>
#include <iostream>



using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    Mat train1, train2, image; // images are stored in datatype Mat (matrix)
    
 if (argc > 1)
    {
        cout << "Usage: ./program_name" << endl;
        return -1;
    }

    train1 = imread("OCR/Image 01.bmp", IMREAD_GRAYSCALE);
    if (!train1.data)
    {
        cout << "Could not open or find the first training file." << endl;
        return -1;
    }
	train2 = imread("OCR/Image 02.bmp", IMREAD_GRAYSCALE);
    if (!train2.data)
    {
        cout << "Could not open or find the second training file." << endl;
        return -1;
    }
	image = imread("OCR/Image 03.bmp", IMREAD_GRAYSCALE);
    if (!image.data)
    {
        cout << "Could not open or find the image." << endl;
        return -1;
    }

    // Reduce noise
   // GaussianBlur(new_image, greyfilteredImage, Size(9, 9), 2, 2);

    // Le magic    
    //threshold(train1, train1, 160, 255, THRESH_BINARY);
    //threshold(train2, train2, 160, 255, THRESH_BINARY);
    //threshold(image, image, 160, 255, THRESH_BINARY);
    
    
   
    namedWindow("Train 1", WINDOW_AUTOSIZE);
    imshow("Train 1", train1);

    waitKey(0);
    namedWindow("Train 2", WINDOW_AUTOSIZE);
    imshow("Train 2", train2);

    waitKey(0);
    namedWindow("Detected char", WINDOW_AUTOSIZE);
    imshow("Detected char", image);

    waitKey(0);

    return 0;
}

