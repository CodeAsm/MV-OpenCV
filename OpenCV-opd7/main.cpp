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
    Mat image, greyImage, greyfilteredImage, edges; // images are stored in datatype Mat (matrix)
    
 if (argc < 2)
    {
        cout << "Usage: ./program_name <image_path>" << endl;
        return -1;
    }

    image = imread(argv[1], IMREAD_COLOR);
    if (!image.data)
    {
        cout << "Could not open or find the image." << endl;
        return -1;
    }

    // Convert the image from color to grayscale
    cvtColor(image, greyImage, COLOR_BGR2GRAY);
    //greyImage = image; //They are gray already


    // Simple brightness and contrast controll. legally borrowed from 
    // https://docs.opencv.org/3.4/d3/dc1/tutorial_basic_linear_transform.html
    
    Mat new_image = Mat::zeros( greyImage.size(), greyImage.type() );
    /*double alpha = 1.1; /*< Simple contrast control */
    /*int beta = 2; /*< Simple brightness control */
    /*
     for( int y = 0; y < greyImage.rows; y++ ) {
         for( int x = 0; x < greyImage.cols; x++ ) {
            for( int c = 0; c < greyImage.channels(); c++ ) {
               new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha * greyImage.at<Vec3b>(y,x)[c] + beta );
            }
        }
    }*/
    new_image = greyImage;

    // Reduce noise
    GaussianBlur(new_image, greyfilteredImage, Size(9, 9), 2, 2);

    // Le magic
    threshold(greyfilteredImage, greyfilteredImage, 160, 255, THRESH_BINARY);
    
    // Detecteer edges met Canny
    int lowThreshold = 50;      //50 ai, 20 ?
    int highThreshold = 150;    //150 ai, 376 ?
    Canny(greyfilteredImage, edges, lowThreshold, highThreshold);

    // Apply morph
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 120)); //5, 120 worked "ok", originally MORPH_ELLIPSE
    Mat morph;
    morphologyEx(edges, morph, MORPH_CLOSE, kernel);

    // vind de randen
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(morph, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // vind en tel de pinnen
    int straightPinsCount = 0;
    for (const auto& contour : contours)
    { 
        RotatedRect rect = minAreaRect(contour);
        double areaRatio = abs(contourArea(contour)) / (rect.size.width * rect.size.height);
        if (areaRatio > 0.60 && ((rect.size.height > 150 && rect.size.width < 12) || ( rect.size.width > 150 && rect.size.height < 12 ))) //(ratio >  0.95 and height > 5) 
        {
            straightPinsCount++;
            drawContours(image, vector<vector<Point>>{contour}, -1, Scalar(0, 0, 255), 2);
            
            cout << "rect length " << rect.size.height << " with " << rect.size.width << endl;
            Point2f points[4];
            rect.points(points);
            for (int i = 0; i < 4; i++)
            {
                line(image, points[i], points[(i + 1) % 4], Scalar(0, 255, 0), 2);
                
            }
        }
    }
 
    // Hoeveel pinnen hadden we?

    cout << "Number of straight pins: " << straightPinsCount << endl;
   
    namedWindow("filtered image", WINDOW_AUTOSIZE);
    imshow("filtered image", greyfilteredImage);

    waitKey(0);
   
    namedWindow("Detected Pins", WINDOW_AUTOSIZE);
    imshow("Detected Pins", image);

    waitKey(0);

    return 0;
}

