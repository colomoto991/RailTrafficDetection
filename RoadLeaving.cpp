#include "RoadLeaving.h"

#include <vector>
#include <highgui.hpp>

using namespace std;
using namespace cv;

RoadLeaving::RoadLeaving(
    cv::Mat_<uchar> &empty,
    std::string zone_c1_mask_path,
    std::string zone_c2_mask_path,
  //  std::vector<double> line_between_lanes,
    double min_object_area,
    int erode_size,
    int dilate_size,
    int threshold_value)
    : zone_c1_mask(imread(zone_c1_mask_path, IMREAD_GRAYSCALE))
    , zone_c2_mask(imread(zone_c2_mask_path, IMREAD_GRAYSCALE))
    , erode_size(erode_size)
    , dilate_size(dilate_size)
    , threshold_value(threshold_value)
    , ready(false)
{
    equalizeHist(empty, reference);
    if (!reference.data) {
        cout << "Failed to load road traffic reference image\n";
        return;
    }

    if (!zone_c1_mask.data) {
        cout << "Failed to load " << zone_c1_mask_path << "\n";
        return;
    }

    if (!zone_c2_mask.data) {
        cout << "Failed to load " << zone_c2_mask_path << "\n";
        return;
    }

    ready = true;
}

bool RoadLeaving::operator()(cv::Mat_<uchar> input)
{
    // vector of events occuring in the given image
    vector<LevelCrossingEvent> events;

    // processed image
    Mat_<uchar> image;

    // merge 2 seperate masks
    zone_c_mask = zone_c1_mask + zone_c2_mask;

    // histogram to enhance the image
    equalizeHist(input, image);

    // difference from the empty image
    // difference image between current and reference images
    absdiff(image, reference, image);

    // trim image by mask
    bitwise_and(image, zone_c_mask, image);

    // morphological opening
    erode(image, image, getStructuringElement(MORPH_ELLIPSE, Size(erode_size, erode_size)));
    dilate(image, image, getStructuringElement(MORPH_ELLIPSE, Size(dilate_size, dilate_size)));

    // binarying the image
    // thresholding
    threshold(image, image, threshold_value, 255, THRESH_BINARY);

    
  
 
    return countNonZero(image) > 0;
}

