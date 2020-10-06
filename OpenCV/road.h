#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

cv::Mat CannyEdge(cv::Mat image);
void regionOfInterest(cv::Mat image);
void displayLines(cv::Mat image, std::vector<cv::Vec4i> lines);
void roadDetection();