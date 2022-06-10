#include "SafetyBarrier.h"

#include <highgui.hpp>

using namespace cv;
using namespace std;

SafetyBarrier::SafetyBarrier(
    string barrier_mask_path, 
    int canny_first_threshold, 
    int canny_second_threshold,
    double min_barrier_coverage)
    : barrier_mask(imread(barrier_mask_path, cv::IMREAD_GRAYSCALE))
    , barrier_pixels(countNonZero(barrier_mask))
    , canny_first_threshold(canny_first_threshold)
    , canny_second_threshold(canny_second_threshold)
    , min_barrier_coverage(min_barrier_coverage)
    , ready(false)
{
    if (!barrier_mask.data) {
        cout << "Failed to load " << barrier_mask_path << "\n";
        return;
    }

    ready = true;
}

bool SafetyBarrier::operator()(Mat_<uchar> input)
{
    // edge image of current input image
    Mat_<uchar> edges;
    // use canny to get the edge of the input image
    Canny(input, edges, canny_first_threshold, canny_second_threshold);

    // image with mask applied
    Mat_<uchar> masked;

    // calculating coverage with edges for masked regions
    bitwise_and(edges, barrier_mask, masked);
    double barrier_coverage =  (double)countNonZero(masked) / barrier_pixels * 100;
    
    
    // what is the "negative barrier mask" is used for
    // returns true when barrier is deployed
    return barrier_coverage > min_barrier_coverage;
}
