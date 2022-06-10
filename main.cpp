/*

*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <opencv.hpp>
#include <highgui.hpp>
#include <fstream>
#include "LevelCrossingMonitoring.h"


using namespace std;
using namespace cv;

// usage: find whether the target picture belongs to the target class.

template <class Container, class T>
bool contains(const Container &c, const T &val)
{
    return find(begin(c), end(c), val) != end(c);
}


// Main function accepts 2 parameters. The second one should be the path of the pictures.
int main(int argc, char *argv[])
{
    
    LevelCrossingMonitoring monitoring;
    /*
    if (!monitoring.is_ready()) {
        cout << "Failed to initialize monitoring object.\n";
        return -1;
    }
    */

    // paths to all images
    vector<string> all_paths(&argv[1], &argv[argc]);

    // main loop testing all images
    for (int i = 1; i < argc; i++) 
    {
        // current loaded image
        Mat img = imread(argv[i], cv::IMREAD_GRAYSCALE);
        if (!img.data) {
            cout << "Failed to load " << argv[i] << "\n";
            return -1;
        }

        // vector of events occured in the current picture
        vector<LevelCrossingEvent> events = monitoring(img);

        // screen output
        cout << argv[i] << " : ";
        int flag = 0;

        if (contains(events, LevelCrossingEvent::ONTRACK)) {
            cout << "event 1 ";
            flag = 1;
        }
            
        if (contains(events, LevelCrossingEvent::ENTERING)) {
            cout << "event 2 ";
            flag = 1;
        }

        if (contains(events, LevelCrossingEvent::LEAVING)) {
            cout << "event 3 ";
            flag = 1;
        }

        if (contains(events, LevelCrossingEvent::BARRIER)) {
            cout << "event 4 ";
            flag = 1;
        }

        if (contains(events, LevelCrossingEvent::TRAIN)) {
            cout << "event 5 ";
            flag = 1;
        }
        if (flag == 0) cout << "empty";

        cout << '\n';
        }

    return 0;
}