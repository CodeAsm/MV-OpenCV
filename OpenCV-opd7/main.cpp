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
	Mat image, greyimage;  // images are stored in datatype Mat (matrix)

	// Read the image
	image = imread(argv[1], IMREAD_COLOR);
	if (!image.data)
	{
		cout << "Could not open or find " << endl;
		return -1;
	}

	// Convert the image from color to gray values: 
	cvtColor(image, greyimage, COLOR_BGR2GRAY);

       // Reduce noise:
	GaussianBlur(greyimage, greyimage, Size(9, 9), 2, 2);

	// Storage for blobs
    vector<KeyPoint> pins;

	// Setup SimpleBlobDetector parameters.
    SimpleBlobDetector::Params params;

	// Set up detector with params
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    // Detect blobs
    detector->detect(greyimage, pins);

    Mat image_pins;
    drawKeypoints(greyimage, pins, image_pins, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);



	// Print (cout) the number of pins in the image (legaly borrowed from example)
	if (pins.size() >= 1) {
		cout << pins.size() << " pins detected!" << endl;
	}
	else {
		cout << "No pins detected!" << endl;
	}

    // Show blobby circles
	namedWindow("pins", WINDOW_AUTOSIZE);
    imshow("pins", image_pins);
	waitKey(0);
	return 0;
}

