 #pragma once

#include <vector>
#include <string>
#include <opencv.hpp>
#include "RoadEntering.h"
#include "RoadLeaving.h"
#include "railnotclear.h"
#include "SafetyBarrier.h"
#include "RailTraffic.h"
#include "LevelCrossingEvent.h"



class LevelCrossingMonitoring {
public:
    // constructor
    LevelCrossingMonitoring(std::string reference_image_path = "reference.png");

    // returns vector of events which occur in given image
    std::vector<LevelCrossingEvent> operator()(cv::Mat_<uchar> input);

    // check whether object is initialized properly
    bool is_ready() { return ready; }

private:
    // grayscale reference (empty background) image
    cv::Mat_<uchar> reference;

    // objects used to detect particular events

    RoadEntering road_entering;
    RoadLeaving road_leaving;
    RAILNOTCLEAR rail_not_clear;
    SafetyBarrier safety_barrier;
    RailTraffic rail_traffic;

    // object is initialized properly
    bool ready;
};
