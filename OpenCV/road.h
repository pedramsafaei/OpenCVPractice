#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

cv::Mat CannyEdge(cv::Mat image);
cv::Mat regionOfInterest(cv::Mat image);
cv::Mat displayLines(cv::Mat image, std::vector<cv::Vec4i> lines, bool lines_on_original= false);
void createWindow(cv::Mat image, std::string window_name);
void roadDetection();