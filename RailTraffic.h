#pragma once

#include <opencv.hpp>

class RailTraffic
{
public:
    RailTraffic(
        cv::Mat_<uchar> &empty,
        std::string zone_a_mask_path = "masks/zone_a.png",
        double min_average = 46.0);

    bool operator()(cv::Mat_<uchar> input);
    bool is_ready() { return ready; }

private: 

    // grayscale reference (empty background) image
    cv::Mat_<uchar> reference;

    cv::Mat_<uchar> zone_a_mask;

    int zone_a_pixels;
    

    // minimum percentage of edge pixels in barrier region
    double min_average;

    // object is initialized properly
    bool ready;
};

