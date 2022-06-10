#include "railnotclear.h"

#include <vector>
#include <highgui.hpp>

using namespace std;
using namespace cv;

RAILNOTCLEAR::RAILNOTCLEAR(
    cv::Mat_<uchar> &empty,
    std::string zone_a_mask_path
  //  std::vector<double> line_between_lanes,
   )
    : zone_a_mask(imread(zone_a_mask_path, IMREAD_GRAYSCALE))
    , ready(false)
{
    equalizeHist(empty, reference);
    if (!reference.data) {
        cout << "Failed to load road traffic reference image\n";
        return;
    }

    if (!zone_a_mask.data) {
        cout << "Failed to load " << zone_a_mask_path << "\n";
        return;
    }

    ready = true;
}

bool RAILNOTCLEAR::operator()(cv::Mat_<uchar> input)
{
    // vector of events occuring in the given image
    vector<LevelCrossingEvent> events;

    // processed image
    Mat_<uchar> image;



  
    // histogram to enhance the image
    equalizeHist(input, image);


    // difference from the empty image
    // difference image between current and reference images
    absdiff(image, reference, image);

    // trim image by mask
    bitwise_and(image, zone_a_mask, image);




    // morphological opening
    erode(image, image, getStructuringElement(MORPH_ELLIPSE, Size(erode_size, erode_size)));
    dilate(image, image, getStructuringElement(MORPH_ELLIPSE, Size(dilate_size, dilate_size)));

    // binarying the image
    // thresholding
    threshold(image, image, threshold_value, 255, THRESH_BINARY);

    return countNonZero(image) > 0;
}

