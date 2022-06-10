#include "RailTraffic.h"

#include <iostream>
#include <numeric>
#include <highgui.hpp>

using namespace std;
using namespace cv;

RailTraffic::RailTraffic(Mat_<uchar> &empty, string zone_a_path, double min_average)
    : zone_a_mask(imread(zone_a_path, cv::IMREAD_GRAYSCALE))
    , zone_a_pixels(countNonZero(zone_a_mask))
    , min_average(min_average)
    , ready(false)
{
    equalizeHist(empty, reference);
    if (!reference.data) 
    {
        cout << "Failed to load reference image\n";
        return;
    }

    if (!zone_a_mask.data) {
        cout << "Failed to load " << zone_a_path << "\n";
        return;
    }

    ready = true;
}



bool RailTraffic::operator()(cv::Mat_<uchar> input)
{
    // processed image
    Mat_<uchar> image;

    // applying histogram equalization on current input image
    equalizeHist(input, image);

    // difference image between current and reference images
    absdiff(image, reference, image);
    
    // applying mask to obtained difference
    bitwise_and(image, zone_a_mask, image);

    // calculating average gray value in difference masked region
    double average =
        double(std::accumulate(image.begin(), image.end(), 0)) / zone_a_pixels;

    // if average is higher than minimum, train is detected
    return average > min_average;
}
