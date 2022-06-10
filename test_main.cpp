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
#include <fstream>


using namespace std;
using namespace cv;

// usage: find whether the target picture belongs to the target class.

template <class Container, class T>
bool contains(const Container& c, const T& val)
{
    return find(begin(c), end(c), val) != end(c);
}

int getImagePathList(std::string folder, std::vector<cv::String>& imagePathList)
{
    //search all the image in a folder
    cv::glob(folder, imagePathList);
    return 0;
}


// Main function accepts 2 parameters. The second one should be the path of the pictures.
int main(int argc, char* argv[])
{

    ofstream fout;

    fout.open("output.txt");

    LevelCrossingMonitoring monitoring;
    /*
    if (!monitoring.is_ready()) {
        cout << "Failed to initialize monitoring object.\n";
        return -1;
    }
    */

    // paths to all images
    vector<string> all_paths(&argv[1], &argv[argc]);

    cv::String folder = argv[1];
    std::vector<cv::String> imagePathList;
    getImagePathList(folder, imagePathList);
    for (int i = 0; i < imagePathList.size(); i++)
    {
        fout << imagePathList[i] << "\t";
        auto img = cv::imread(imagePathList[i],cv::IMREAD_GRAYSCALE);
        if (!img.data) {
            cout << "Failed to load " << argv[i] << "\n";
            return -1;
        }
      
    

        // vector of events occured in the current picture
        vector<LevelCrossingEvent> events = monitoring(img);

        // screen output
       // cout << argv[i] << " : ";
        int flag = 0;

        if (contains(events, LevelCrossingEvent::ONTRACK)) {
            fout << "event1" << "\t";
            flag = 1;
        }
        else { fout <<  "0" << "\t"; }

        if (contains(events, LevelCrossingEvent::ENTERING)) {
            fout << "event2" << "\t";
            flag = 1;
        }
        else { fout << "0" << "\t"; }

        if (contains(events, LevelCrossingEvent::LEAVING)) {
            fout << "event3" << "\t";
            flag = 1;
        }
        else { fout << "0" << "\t"; }

        if (contains(events, LevelCrossingEvent::BARRIER)) {
            fout << "event4" << "\t";
            flag = 1;
        }
        else { fout << "0" << "\t"; }

        if (contains(events, LevelCrossingEvent::TRAIN)) {
            fout << "event5"<<"\t";
            flag = 1;
        }
        else { fout << "0" << "\t"; }

        if (flag == 0) fout << "empty";

        fout << '\n';

        events.clear();

        
    }
    fout.close();
    return 0;
}