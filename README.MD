## HVA OpenCV 2022

For HVA OpenCV I did a google and found:
<https://stackoverflow.com/a/64886697/1671029>


for **opencv4**

```
sudo pacman -Sy opencv vtk hdf5
```

optionally, install Qt
```
sudo pacman -Sy qt5-base qtcreator qt5-doc gdb cmake
```

create a CMake project in QtCreator
 
paste the following

**CMakeLists.txt**
```
cmake_minimum_required(VERSION 3.5)

project(opencv LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(opencv main.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( opencv ${OpenCV_LIBS} )
```

**main.cpp**
```
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image;
    image = imread( argv[1], 1 );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}
```