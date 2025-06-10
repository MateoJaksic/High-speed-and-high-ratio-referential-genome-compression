#include "evaluator.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// author: Mateo Jakšić
// function for evaluating compression and decompression performanse
void evaluate(const string& target_path, const string& decompressed_path) {
    string target = read_sequence(target_path);
    string decompressed = read_sequence(decompressed_path);

    int matches = 0;
    for (size_t i = 0; i < decompressed.length(); i++) {
        if (target[i] == decompressed[i]) {
            matches++;
        }
    }

    float score = (float)matches / (float)target.length() * 100;
    
    cout << "Kompresija i dekompresija rade sa " << score << "% točnosti.";
}