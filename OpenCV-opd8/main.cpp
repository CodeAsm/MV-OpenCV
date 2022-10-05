#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>


using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	Mat image;  // images are stored in datatype Mat (matrix)

    // Reduce noise:
	GaussianBlur(imread(argv[1], IMREAD_COLOR), image, Size(9, 9), 2, 2);


	namedWindow("Image filtered", WINDOW_AUTOSIZE);
	imshow("Image filtered", image); 
	waitKey(0);
	return 0;
}

