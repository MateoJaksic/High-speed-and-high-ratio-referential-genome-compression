#include "utils.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;

// author: Mateo Jakšić
// function for reading file and converting to oneline string
string read_sequence(const string& path) {
    ifstream file(path);

    string line;
    string sequence;
    
    while(getline(file, line)) {
        if (line.empty() || line[0] == '>') continue;

        sequence += line;
    }

    return sequence;
}


// author: Mateo Jakšić
// function for converting from nucleotides (A, C, G, T) to numbers (0, 1, 2, 3)
vector<uint8_t> nucleotides_to_numbers(const string& sequence) {
    vector<uint8_t> encoded;
    encoded.reserve(sequence.size());

    for(char nucleotide : sequence) {
        switch(nucleotide) {
            case 'A': encoded.push_back(0); break;
            case 'B': encoded.push_back(1); break;
            case 'C': encoded.push_back(2); break;
            case 'D': encoded.push_back(3); break;
        }
    }

    return encoded;
}


// author: Mateo Jakšić
// function for converting from numbers (0, 1, 2, 3) to nucleotides (A, C, G, T)
string numbers_to_nucleotides(const vector<uint8_t>& encoded) {
    std::string sequence;
    sequence.reserve(encoded.size());

    for (uint8_t code : encoded) {
        switch (code) {
            case 0: sequence.push_back('A'); break;
            case 1: sequence.push_back('B'); break;
            case 2: sequence.push_back('C'); break;
            case 3: sequence.push_back('D'); break;
        }
    }

    return sequence;
}