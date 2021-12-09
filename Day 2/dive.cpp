#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class dive
{
private:
    int _position[2] = {0, 0};
    int _aim = 0;
    vector<pair<string, int > > _instructions;
public:
    //constructor
    dive(const char* fileName) {
        vector<pair<string, int> > buffer;
        fstream data(fileName);
        // variables to hold the instructions data
        string instruction;
        int value;
        while(data >> instruction >> value) {
            pair<string, int> temp(instruction, value);
            buffer.push_back(temp);
        }
        _instructions = buffer;
    }
    int calculateDivePosition();
};

int dive::calculateDivePosition() {
    for(pair<string, int> it : _instructions) {
        string step = it.first;
        if (step == "forward") {
            _position[0] += it.second;
            _position[1] += _aim * it.second;
        } else if (step == "up") {
            _aim -= it.second;
        } else if (step == "down") { // step == "down"
            _aim += it.second;
        }
    }
    // calculate the product of horizontal and depth
    return _position[0] * _position [1];
}

int main()
{
    dive diver("directionsInput.txt");
    cout << diver.calculateDivePosition() << endl;
    return 0;
}

