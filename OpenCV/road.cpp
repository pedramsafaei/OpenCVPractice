#include "road.h"

cv::Mat CannyEdge(cv::Mat image)
{
  cv::Mat gray, blur, canny_image;

  cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
  cv::GaussianBlur(gray, blur, cv::Size(5, 5), 0);

  cv::Canny(blur, canny_image, 50, 150);

  return canny_image;
}

void regionOfInterest(cv::Mat image)
{

}

void displayLines(cv::Mat image, std::vector<cv::Vec4i> lines)
{

}

void roadDetection()
{
  cv::Mat canny_image, input_image;
  input_image = cv::imread("../data/road.png");
  canny_image = CannyEdge(input_image);


  //Define names of the windows
  std::string window_name = "Lotus";
  // Create windows with above names
  cv::namedWindow(window_name);
  // Show our images inside the created windows.
  cv::imshow(window_name, canny_image);
}


/*

import cv2
import numpy as np


def CannyEdge(image):
  gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
  blur = cv2.GaussianBlur(gray, (5,5), 0)
  cannyImage = cv2.Canny(blur, 50, 150)
  return cannyImage

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