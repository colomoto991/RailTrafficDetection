#include <highgui.hpp>
#include "LevelCrossingMonitoring.h"

using namespace std;
using namespace cv;



LevelCrossingMonitoring::LevelCrossingMonitoring(string reference_image_path)
    : reference(imread(reference_image_path, cv::IMREAD_GRAYSCALE))
    , road_entering(reference)
    , road_leaving(reference)
    , rail_not_clear(reference)
    , rail_traffic(reference)
    , ready(false)
{
    if (!reference.data) {
        cout << "Failed to load " << reference_image_path << "\n";
        return;
    }

    if (!road_entering.is_ready()) {
        cout << "Failed to initialize road traffic object.\n";
        return;
    }

    if (!road_leaving.is_ready()) {
        cout << "Failed to initialize road traffic object.\n";
        return;
    }
    if (!rail_not_clear.is_ready()) {
        cout << "Failed to initialize road traffic object.\n";
        return;
    }

    if (!safety_barrier.is_ready()) {
        cout << "Failed to initialize safety barrier object.\n";
        return;
    }

    if (!rail_traffic.is_ready()) {
        cout << "Failed to initialize rail traffic object.\n";
        return;
    }

    ready = true;
}

vector<LevelCrossingEvent> LevelCrossingMonitoring::operator()(Mat_<uchar> input)
{
    vector<LevelCrossingEvent> events;

    // level crossing monitoring object is not properly initialized
    if (!ready)
        return events;

    if (rail_traffic(input)) { // there is a train
        events.push_back(LevelCrossingEvent::TRAIN);
    } 

    if (rail_not_clear(input)) { // there is leaving traffic
        events.push_back(LevelCrossingEvent::ONTRACK);
    }

    if (road_entering(input)) { // there is entering traffic
        events.push_back(LevelCrossingEvent::ENTERING);
    }
    
    if (road_leaving(input)) { // there is leaving traffic
        events.push_back(LevelCrossingEvent::LEAVING);
    }
   

    if (safety_barrier(input)) { // safety barrier is deployed
        events.push_back(LevelCrossingEvent::BARRIER);
    }

    return events;
}
