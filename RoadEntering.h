#pragma once

#include <vector>
#include <opencv.hpp>
#include "LevelCrossingEvent.h"

class RoadEntering
{
public:
    RoadEntering(
        cv::Mat_<uchar> &empty,
        std::string zone_b1_mask_path = "masks/zone_b1.png",
        std::string zone_b2_mask_path = "masks/zone_b2.png",
      //  std::vector<double> line_between_lanes = std::vector<double>{0.5, -2.5},
        double min_object_area = 1,
        int erode_size = 5,
        int dilate_size = 5,
        int threshold_value = 100);
    bool operator()(cv::Mat_<uchar> input);
    bool is_ready() { return ready; }

private:
    cv::Mat_<uchar> reference;
    cv::Mat_<uchar> zone_b1_mask;
    cv::Mat_<uchar> zone_b2_mask;
    cv::Mat_<uchar> zone_b_mask;
   // std::vector<double> line_between_lanes;
    double min_object_area;
    int erode_size;
    int dilate_size;


    int threshold_value;
    bool ready;
};

bool intersects(const std::vector<cv::Point> &contour, const cv::Mat_<uchar> &mask);
