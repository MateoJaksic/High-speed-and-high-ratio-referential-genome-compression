#include "utils.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <bitset>

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
// function for converting single nucleotide from (A, C, G, T) to bit format (0b00, 0b01, 0b10, 0b11)
uint8_t convert_nucleotide_to_number(const char& nucleotide) {
    switch(nucleotide) {
            case 'A': return 0b00;
            case 'C': return 0b01;
            case 'G': return 0b10;
            case 'T': return 0b11;
    }
    return 0;
}


// author: Mateo Jakšić
// function for converting from nucleotides (A, C, G, T) to numbers (0, 1, 2, 3)
// quick explanation: we want to use 2-bit integers for representing nucleotides, but since is
//                    doesn't exist in C++, we pack four or less 2-bit integers into a single uint8_t
pair<vector<uint8_t>, uint8_t> nucleotides_to_numbers(const string& sequence) {
    vector<uint8_t> encoded;
    encoded.reserve((sequence.size() + 3) / 4);

    uint8_t byte = 0;
    int count = 0;

    for(char nucleotide : sequence) {
        byte = (byte << 2) | convert_nucleotide_to_number(nucleotide);
        count++;

        if (count == 4) {
            encoded.push_back(byte);
            byte = 0;
            count = 0;
        }
    }

    uint8_t leftovers = 0;
    if (count > 0) {
        leftovers = 2 * (4 - count);
        byte = byte << leftovers;
        encoded.push_back(byte);
    }

    return make_pair(encoded, leftovers);
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


// author: Mateo Jakšić
// function for displaying numbered genomes
void write_numbers(const vector<uint8_t> reference_values, const uint8_t& reference_leftovers) {
    for (size_t i = 0; i < reference_values.size() - 1; ++i) {
        cout << bitset<8>(reference_values[i]);
    }
    uint8_t last_byte = reference_values.back();
    for (int i = 8 - 1; i >= reference_leftovers; --i) {
        cout << ((last_byte >> i) & 1);
    }
    cout << endl;
}