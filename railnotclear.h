#pragma once

#include <vector>
#include <opencv.hpp>
#include "LevelCrossingEvent.h"

class RAILNOTCLEAR
{
public:
    RAILNOTCLEAR(
        cv::Mat_<uchar> &empty,
        std::string zone_a_mask_path = "masks/zone_a.png"
      //  std::vector<double> line_between_lanes = std::vector<double>{0.5, -2.5},
        );
    bool operator()(cv::Mat_<uchar> input);
    bool is_ready() { return ready; }

private:
    cv::Mat_<uchar> reference;
    cv::Mat_<uchar> zone_a_mask;
   // std::vector<double> line_between_lanes;
    double min_object_area = 1;
    int erode_size = 5;
    int dilate_size = 5;
    int threshold_value = 100;
    bool ready;
};

