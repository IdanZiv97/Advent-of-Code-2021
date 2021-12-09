#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class sonarSweep
{
private:
    vector<int> _measurements;
public:
    sonarSweep(const char* inputFileName) {
        fstream file(inputFileName);
        if(!file.is_open()) {
            cout << "Error: can't open file\n" << endl;
        }
        vector<int> data;
        string buffer;
        while(getline(file, buffer)) {
            data.push_back(stoi(buffer));
        }
        _measurements = data;
    }
    int simpleSweep();
    int windowsSweep();
};


/**
 * @brief first part of the the challenge
 * @return the number of measurements that are bigger than the previous measurement
 */
int sonarSweep::simpleSweep() {
    int increasedMeasurements = 0; //The first measurement doesn't count as an increased
    for(int i = 1; i < _measurements.size(); i++) {
        if (_measurements[i] > _measurements[i - 1]) {
            increasedMeasurements++;
        }
    }
    return increasedMeasurements;
}

int sonarSweep::windowsSweep() {
    // Suppress noise - create measurements windows
    vector<int> windows;
    int windowCounter = 0;
    for(int i = 0; i < _measurements.size() - 2; i++) {
        //sum window's measurements
        int sum = _measurements[i] + _measurements[i + 1] + _measurements[i + 2];
        windows.push_back(sum);
    }
    int increasedMeasurements = 0;
    for(int i = 1; i < windows.size(); i++) {
        if (windows[i] > windows[i -1]) {
            increasedMeasurements++;
        }
    }
    return increasedMeasurements;
}

int main()
{
    sonarSweep sonar("sonarMeasurements.txt");
    cout << "The number of of increased measurements is: " << sonar.windowsSweep() << endl;
    return 0;
}