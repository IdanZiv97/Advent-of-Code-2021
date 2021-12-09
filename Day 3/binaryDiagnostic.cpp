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
    vector<string> _data;
public:
    binaryDiagnostic(string fileName):_gamma(0),_epsilon(0) {
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
    int powerConsumption();
};

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
    cout << bin.powerConsumption() << endl;
    return 0;
}
