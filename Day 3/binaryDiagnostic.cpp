#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class binaryDiagnostic
{
private:
    int _rowSize;
    int _numOfRows;
    int _gamma;
    int _epsilon;
    int _threshold;
    int _lifeSupportRating;
    vector<string> _data;
    int oxygenGeneratorRating(vector<string> data);
    int co2ScrubberRating(vector<string> data);
    bool checkBitPosition(string s, char bit, int index) {
        return s[index] == bit;
    }
public:
    binaryDiagnostic(string fileName):_gamma(0),_epsilon(0),_lifeSupportRating(0) {
        vector<string> temp;
        fstream data(fileName);
        string line;
        while(data >> line) {
            temp.push_back(line);
        }
        _data = temp;
        _rowSize = temp[0].size();
        _numOfRows = temp.size();
        _threshold = (_numOfRows / 2);
    }
    vector<string> getData();
    int powerConsumption();
    int lifeSupportRating(vector<string> data);
};

vector<string> binaryDiagnostic::getData() {
    return _data;
}

int binaryDiagnostic::oxygenGeneratorRating(vector<string> data) {
    int rowSize = data[0].size();
    //iterate each bit position to determine the most common value
    for (int bitPosition = 0; bitPosition < rowSize; bitPosition++) {
        int oneCounter = 0;
        int zeroCounter = 0;
        _threshold = data.size() / 2;
        //the only possible values are 0 and 1, so we need to basically sum all the values in the current bit position
        // and determine whether it is larger than the the thrsehold
        for (string line : data) {
            line[bitPosition] == '1' ? oneCounter++ : zeroCounter++;
            if (oneCounter > _threshold || zeroCounter > _threshold) {break;}
        }
        // in this case keep only the numbers with the value 1 in the current bitPosition
        if (zeroCounter == oneCounter) {
            for (int index = 0; index < data.size(); index++) {
            string current = data.at(index);
            //check if the element should be removed
            if (current.at(bitPosition) != '1') {
                data.erase(data.begin() + index);
                index--;
            }
        }
            continue;
        }
        char mostCommonValue = oneCounter > zeroCounter  ? '1' : '0';
        //filtering
        for (int index = 0; index < data.size(); index++) {
            string current = data.at(index);
            //check if the element should be removed
            if (current.at(bitPosition) != mostCommonValue) {
                data.erase(data.begin() + index);
                index--;
            }
        }
        if (data.size() == 1) {break;}
    }
    //found the last
    int power = rowSize - 1;
    int rating = 0;
    for(int i = 0; i < rowSize; i++) {
        if (data[0].at(i) == '1') rating += pow(2, power);
        power--;
    }
    return rating;
}

int binaryDiagnostic::co2ScrubberRating(vector<string> data) {
    int rowSize = data[0].size();
    //iterate each bit position to determine the most common value
    for (int bitPosition = 0; bitPosition < rowSize; bitPosition++) {
        int oneCounter = 0;
        int zeroCounter = 0;
        _threshold = data.size() / 2;
        //the only possible values are 0 and 1, so we need to basically sum all the values in the current bit position
        // and determine whether it is larger than the the thrsehold
        for (string line : data) {
            line[bitPosition] == '1' ? oneCounter++ : zeroCounter++;
            if (oneCounter > _threshold || zeroCounter > _threshold) {break;}
        }
        // in this case keep only the numbers with the value 1 in the current bitPosition
        if (oneCounter == zeroCounter) {
            for (int index = 0; index < data.size(); index++) {
            string current = data.at(index);
            //check if the element should be removed
            if (current.at(bitPosition) != '0') {
                data.erase(data.begin() + index);
                index--;
            }
        }
            continue;
        }
        char leastCommonValue = oneCounter > zeroCounter  ? '0' : '1';
        //filtering
        for (int index = 0; index < data.size(); index++) {
            string current = data.at(index);
            //check if the element should be removed
            if (current.at(bitPosition) != leastCommonValue) {
                data.erase(data.begin() + index);
                index--;
            }
        }
        // check if we are left with only one item
        if (data.size() == 1) {break;}
    }
    //found the last
    int power = rowSize - 1;
    int rating = 0;
    for(int i = 0; i < rowSize; i++) {
        if (data[0].at(i) == '1') rating += pow(2, power);
        power--;
    }
    return rating;
}

int binaryDiagnostic::lifeSupportRating(vector<string> data) {
    int oxygenGeneratorRating = binaryDiagnostic::oxygenGeneratorRating(data);
    int co2ScrubberRating = binaryDiagnostic::co2ScrubberRating(data);
    _lifeSupportRating = oxygenGeneratorRating * co2ScrubberRating;
    return _lifeSupportRating;
}

int binaryDiagnostic::powerConsumption() {
    int power = _rowSize - 1;
    for(int i = 0; i <= _rowSize; i++) {
        int oneCounter = 0;
        int zeroCounter = 0;
        for (string s : _data) {
            s[i] == '1' ? oneCounter++ : zeroCounter++;
            if (oneCounter > _threshold || zeroCounter > _threshold) {break;};
        }
        //check which is the most common
        if (zeroCounter > oneCounter) { // 1 is the most common
            _gamma += pow(2, power);
            power--;
        } else { // 0 is the most common
            _epsilon += pow(2, power);
            power--;
        }
    }
    return _gamma * _epsilon;
}

int main(int argc, char const *argv[])
{
    binaryDiagnostic bin("binaryInput.txt");
    cout << bin.lifeSupportRating(bin.getData());
    return 0;
}
