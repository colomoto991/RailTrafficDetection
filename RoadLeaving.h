#pragma once

#include <vector>
#include <opencv.hpp>
#include "LevelCrossingEvent.h"

class RoadLeaving
{
public:
    RoadLeaving(
        cv::Mat_<uchar> &empty,
        std::string zone_c1_mask_path = "masks/zone_c1.png",
        std::string zone_c2_mask_path = "masks/zone_c2.png",
      //  std::vector<double> line_between_lanes = std::vector<double>{0.5, -2.5},
        double min_object_area = 1,
        int erode_size = 5,
        int dilate_size = 5,
        int threshold_value = 100);
    bool operator()(cv::Mat_<uchar> input);
    bool is_ready() { return ready; }

private:
    cv::Mat_<uchar> reference;
    cv::Mat_<uchar> zone_c1_mask;
    cv::Mat_<uchar> zone_c2_mask;
    cv::Mat_<uchar> zone_c_mask;
   // std::vector<double> line_between_lanes;
    double min_object_area;
    int erode_size;
    int dilate_size;
    int threshold_value;
    bool ready;
};

