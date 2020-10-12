// OpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "img.h"
//
//int main()
//{
//  // number of images
//  size_t num_images = 6;
//  SUBSAMPLE sub_sample = SUB128;
//
//  Sample(num_images, sub_sample);
//  return 0;
//}



#include "road.h"

int main()
{
  //roadDetection(); // one frame
  cv::Mat canny_image, triangle_image, line_image, combo_image;

  cv::VideoCapture cap("../data/Road/test2.mp4");
  if (!cap.isOpened()) {
    std::cout << "Error opening the video stream!" << std::endl;
    return -1;
  }
  while (true) {
    cv::Mat frame;
    cap >> frame;

    if (frame.empty()) {
      break;
    }
    // do the detection
    canny_image = CannyEdge(frame);
    triangle_image = regionOfInterest(canny_image);
    //int rho = 2;
    //double theta = CV_PI / 180;
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(triangle_image, lines, 1, 2 * CV_PI / 180, 100, 40, 5);
    //line_image = displayLines(frame, lines);
    combo_image = displayLines(frame, lines, true);

    createWindow(combo_image, "Test1");

    char exit = (char)cv::waitKey(25);
    if (exit == 27) {
      break;
    }
  }

  //cv::waitKey(0);          // Wait for any keystroke in the window
  cap.release();
  cv::destroyAllWindows(); //destroy all opened windows

  return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
