#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

 // Convert naar grijswaarden
    Mat gray, src_gray, image; // images are stored in datatype Mat (matrix)
    int thresh = 100;
    RNG rng(12345);


void thresh_callback(int, void*);

int main(int argc, char** argv)
{
   
    
 if (argc > 2)
    {
        cout << "Usage: ./program_name" << endl;
        return -1;
    }

     image = imread(argv[1], IMREAD_COLOR);
    if (!image.data)
    {
        cout << "Could not open or find the image." << endl;
        return -1;
    }
     // Laad een voorbeeldafbeelding


    cvtColor(image, gray, COLOR_BGR2GRAY);


    // Binariseer de afbeelding
    threshold(gray, gray, 128, 255, THRESH_BINARY);

    blur( gray , src_gray, Size(3,3) );

    // Identificeer en isoleer de contouren
    std::vector<std::vector<Point>> contours;
    findContours(src_gray, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Loop over de contouren en teken rechthoeken rond de karakters
    for (const auto& contour : contours) {
        Rect boundingRect = cv::boundingRect(contour);
        rectangle(image, boundingRect, Scalar(0, 255, 0), 2);
    }
    const char* source_window = "Source";
    const int max_thresh = 255;
    imshow( source_window, image );

    createTrackbar( "Canny thresh:", source_window, &thresh, max_thresh, thresh_callback, NULL);
    thresh_callback( 0, 0 );

    // Toon de afbeelding met de geïdentificeerde karakters
    imshow("Character Segmentation", image);
    waitKey(0);
}

void thresh_callback(int, void* )
{

    cout << "Current Threshold: " << thresh << endl;
    Mat canny_output;
    Canny( src_gray, canny_output, thresh, thresh*2 );
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        drawContours( drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
    }
    imshow( "Contours", drawing );
}

