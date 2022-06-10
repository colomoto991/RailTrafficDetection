#pragma once
#include "LevelCrossingEvent.h"
#include <opencv.hpp>

class SafetyBarrier {
public:
    // default constructor with default values
    SafetyBarrier(
        std::string barrier_mask_path = "masks/barrier.png",
        int canny_first_threshold = 400,
        int canny_second_threshold = 50,
        double min_barrier_coverage = 20.0);

    // returns true if barrier in the given image is deployed
    bool operator()(cv::Mat_<uchar> input);

    // check whether object is initialized properly
    bool is_ready() { return ready; }

private:
    // mask used to show only barrier
    cv::Mat_<uchar> barrier_mask;


    // number of non zero pixels in barrier_mask
    int barrier_pixels;


    // first threshold for the hysteresis procedure
    int canny_first_threshold;

    // second threshold for the hysteresis procedure
    int canny_second_threshold;

    // minimum percentage of edge pixels in barrier region
    double min_barrier_coverage;

    // object is initialized properly
    bool ready;
};
