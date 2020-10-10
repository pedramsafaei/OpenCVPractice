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
  cv::Mat mask;              //used for mask kernel
  cv::Mat masked_image;      //final image

  int height = image.rows;   // get the number of rows
  int width = image.cols;    // get the number of cols
  //int channel = image.channels();

  std::vector<cv::Point> triangle{ cv::Point(0, height), 
                                   cv::Point(width/2, height/2), 
                                   cv::Point(width, height) };
  
  std::vector<std::vector<cv::Point>> contour{ triangle };

  mask = cv::Mat(image.rows, image.cols, CV_8UC1, cv::Scalar(0));

  cv::fillPoly(mask, contour, cv::Scalar(255));

  cv::bitwise_and(image, mask, masked_image);
  
  return masked_image;
}

cv::Mat displayLines(cv::Mat image, std::vector<cv::Vec4i> lines, bool lines_on_original)
{
  cv::Mat line_image = cv::Mat(image.rows, image.cols, CV_8UC1, cv::Scalar(0));
  for (size_t i = 0; i < lines.size(); i++)
  {
    cv::Vec4i line = lines[i];
    cv::line(line_image, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(255, 0, 0), 10);
  }
  if (lines_on_original) 
  {
    cv::Mat original_image_gray, combo_image;
    cv::cvtColor(image, original_image_gray, cv::COLOR_BGR2GRAY);
    cv::addWeighted(original_image_gray, 0.8, line_image, 1.0, 1.0, combo_image);
    return combo_image;
  }
  return line_image;
}

void roadDetection()
{
  // Canny Edge Detection
  cv::Mat canny_image, triangle_image, input_image, line_image;
  input_image = cv::imread("../data/road.png");
  canny_image = CannyEdge(input_image);
  createWindow(canny_image, "canny_Image");

  // Area of interest (triangle shape)
  triangle_image = regionOfInterest(canny_image), true;
  createWindow(triangle_image, "triangle_image");

  // Lines using Hough Transform
  std::vector<cv::Vec4i> lines;
  cv::HoughLinesP(triangle_image, lines, 1, 2 * CV_PI / 180, 100, 40, 5);
  line_image = displayLines(input_image, lines, true);
  createWindow(line_image, "line_image");
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