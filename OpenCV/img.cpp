#include <iostream>
#include <vector>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "img.h"

void Sample(size_t num_images, SUBSAMPLE sub_sample)
{
  std::vector<cv::Mat> Images;
  std::vector<cv::Mat> Images_out;

  for (size_t i = 1; i < num_images; i++)
  {
    cv::Mat temp_image;
    temp_image = cv::imread("../data/" + std::to_string(i)+ ".png", cv::IMREAD_GRAYSCALE);
    Images.push_back(temp_image);
  }
  for (auto i : Images)
  {
    int temp_sample, temp_size;
    if (sub_sample == SUB128)
    {
      temp_sample = i.rows / 128;
      temp_size = 128;
    }
    else if (sub_sample == SUB64)
    {
      temp_sample = i.rows / 64;
      temp_size = 64;
    }
    else
    {
      temp_sample = i.rows / 32;
      temp_size = 32;
    }
    cv::Mat temp_image_out(temp_size, temp_size, i.type());

    for (int row = 0; row < temp_size; row++)
    {
      for (int col = 0; col < temp_size; col++)
      {
        temp_image_out.at<uchar>(row, col) = i.at<uchar>(row * temp_sample, col * temp_sample);
      }
    }
    Images_out.push_back(temp_image_out);
  }
  int index = 0;
  for (auto i : Images_out)
  {
    cv::namedWindow("Image "+std::to_string(index), cv::WINDOW_AUTOSIZE); // Create a window for display.
    cv::imshow("Image " + std::to_string(index), i);                      // Show our image inside it.
    index++;
  }

  cv::waitKey(0);
}