#include "road.h"

cv::Mat CannyEdge(cv::Mat image)
{
  cv::Mat gray, blur, canny_image;

  cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
  cv::GaussianBlur(gray, blur, cv::Size(5, 5), 0);

  cv::Canny(blur, canny_image, 50, 150);

  return canny_image;
}

cv::Mat regionOfInterest(cv::Mat image)
{
  //std::vector<cv::Point> triangle;
  //cv::Point a(200, height), b(550, 250), c(1100, height);
  //triangle.push_back(a);
  //triangle.push_back(b);
  //triangle.push_back(c);
  //std::vector<std::vector<cv::Point> > fillContAll;
  //fillContAll.push_back(triangle);


  //void cv::fillPoly(Mat & img,
  //  const Point * *pts,
  //  const int* npts,
  //  int  	ncontours,
  //  const Scalar & color,
  //  int  	lineType = LINE_8,
  //  int  	shift = 0,
  //  Point  	offset = Point()
  //)

  cv::Mat mask;              //used for mask kernel
  cv::Mat masked_image;      //final image

  int height = image.rows;   // get the number of rows

  std::vector<cv::Point> triangle{ cv::Point(200, height), 
                                   cv::Point(550, 250), 
                                   cv::Point(1100, height) };
  
  std::vector<std::vector<cv::Point>> contour{ triangle };

  mask = cv::Mat(image.rows, image.cols, CV_8UC1, cv::Scalar(0));
  //mask = cv::Mat::zeros( cv::Size(image.rows, image.cols), CV_8UC3);

  cv::fillPoly(mask, contour, cv::Scalar(255));

  cv::bitwise_and(image, mask, masked_image);
  
  return masked_image;

  /*
  



  
  https://medium.com/@yogeshojha/self-driving-cars-beginners-guide-to-computer-vision-finding-simple-lane-lines-using-python-a4977015e232
  https://stackoverflow.com/questions/8281239/drawing-polygons-in-opencv
  https://stackoverflow.com/questions/44061999/opencv-bitwise-and-difference-in-python-and-c
  https://cppsecrets.com/users/183911510497105108108121106971051104953495064103109971051084699111109/C00-cvbitwiseand-.php
  https://numpy.org/doc/stable/reference/generated/numpy.zeros_like.html
  https://answers.opencv.org/question/7682/copyto-and-clone-functions/?answer=7683
  https://stackoverflow.com/questions/4337902/how-to-fill-opencv-image-with-one-solid-color



  */

  // // triangle = np.array([[(200, height), (550, 250), (1100, height), ]], np.int32)
  //mask = image;
  //mask.setTo(cv::Scalar(0));
  // // mask = np.zeros_like(image)
  // // cv2.fillPoly(mask, triangle, 255)
  //cv::fillPoly(mask, fillContAll, cv::Scalar(255));
  //cv::bitwise_and(image, mask, masked_image);
  // // masked_image = cv2.bitwise_and(image, mask)
  //return masked_image;
}

void displayLines(cv::Mat image, std::vector<cv::Vec4i> lines)
{

}

void roadDetection()
{
  cv::Mat canny_image, triangle_image, input_image;
  input_image = cv::imread("../data/road.png");
  canny_image = CannyEdge(input_image);
  createWindow(canny_image, "canny_Image");

  triangle_image = regionOfInterest(canny_image);
  createWindow(triangle_image, "triangle_image");
}

void createWindow(cv::Mat image, std::string window_name)
{
  // Create windows with above names
  cv::namedWindow(window_name);
  // Show our images inside the created windows.
  cv::imshow(window_name, image);
}

/*
def region_of_interest(image):
    height = image.shape[0]
    triangle = np.array([[(200, height),(550, 250),(1100, height),]], np.int32)
    mask = np.zeros_like(image)
    cv2.fillPoly(mask, triangle, 255)
    masked_image = cv2.bitwise_and(image, mask)
    return masked_image

def display_lines(image, lines):
    line_image = np.zeros_like(image)
    if lines is not None:
        for line in lines:
            x1, y1, x2, y2 = line.reshape(4)
            cv2.line(line_image, (x1, y1), (x2, y2), (255, 0, 0), 10)
    return line_image

cap = cv2.VideoCapture("test.mp4")
while(cap.isOpened()):
    _, frame = cap.read()
    canny = CannyEdge(frame)
    cropped_Image = region_of_interest(canny)
    rho = 2
    theta = np.pi/180
    threshold = 100
    lines = cv2.HoughLinesP(cropped_Image,rho, theta, threshold, np.array ([ ]), minLineLength=40, maxLineGap=5)
    line_image = display_lines(frame, lines)
    combo_image = cv2.addWeighted(frame, 0.8, line_image, 1, 1)
    cv2.imshow("Image", combo_image)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()

*/