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

	// =======================================

	
	// Storage for blobs
    vector<KeyPoint> keypoints;

	// Setup SimpleBlobDetector parameters.
    SimpleBlobDetector::Params params;

	// Set up detector with params
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    // Detect blobs
    detector->detect(greyimage, keypoints);
	// Draw detected blobs as red circles.
    // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
    // the size of the circle corresponds to the size of blob

    Mat im_with_keypoints;
    drawKeypoints(greyimage, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);



	// Print (cout) the number of circles in the image 
	if (keypoints.size() >= 1) {
		cout << keypoints.size() << " circles detected!" << endl;
	}
	else {
		cout << "No circled detected." << endl;
	}

       // Print for each circle the coordinates of the centre and the radius 
	/*/ example: circle[0][2]is the radius of circle number 0  

      	int k;
 	for (k = 0; k < keypoints.size(); k++) {
		cout << keypoints[k][0] << "    " << keypoints[k][1] << "   "   
                << keypoints[k][2] << endl;
	}*/

    // Show blobs
	namedWindow("keypoints", WINDOW_AUTOSIZE);
    imshow("keypoints", im_with_keypoints);

	waitKey(0);

	// ======================================
    
	// each element of the vector (array) circles is a vector of three float 
       // numbers: x-coordinate of the midpoint, y-coordinate of the midpoint, 
       // radius
	vector<Vec3f> circles;


	return 0;
}

