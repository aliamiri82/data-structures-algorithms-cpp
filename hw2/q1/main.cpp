#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#include <sstream>

int main() {
    vector<string> not1, not2;
    string line ;
    string word;

    getline(cin, line);
    stringstream ss(line);
    while (ss >> word) {
        not1.push_back(word);
    }
    getline(cin, line);
    stringstream ss1(line);
    while (ss1 >> word) {
        not2.push_back(word);
    }
    int arr[not1.size() + 1], last_arr[not1.size() + 1];
    for (int i = 0; i < not1.size() + 1; i++) {
        last_arr[i] = -2 * i;
    }

    for (int i = 0; i < not2.size(); i++) {
        arr[0] = -(i + 1) * 2;
        for (int j = 1; j < not1.size() + 1; j++) {
            int score;
            if (not1[j - 1] == not2[i]) {
                score = 2;
            }
            else {
                score = -1;
            }
            arr[j] = max(arr[j - 1] - 2, last_arr[j] -2 );
            arr[j] = max(arr[j], last_arr[j - 1] + score);
        }
        for (int l = 0; l < not1.size() + 1; l++) {
            last_arr[l] = arr[l];
        }
    }
    cout << last_arr[not1.size()] << endl;

}