#include "utils.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <bitset>
#include <algorithm>

using namespace std;


// author: Mateo Jakšić
// struct for storing compressed segments
// quick explanation: if it's a match then we store position and length
//                    if it's a missmatch then we store missmatches
struct Segment {
    bool match;
    vector<int> data;
};


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
pair<vector<uint8_t>, int> nucleotides_to_numbers(const string& sequence) {
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

    if (count > 0) {
        byte = byte << (2 * (4 - count));
        encoded.push_back(byte);
    }

    return {encoded, sequence.size()};
}


// author: Mateo Jakšić
// function for converting from numbers (0, 1, 2, 3) to nucleotides (A, C, G, T)
string numbers_to_nucleotides(const vector<uint8_t>& encoded) {
    std::string sequence;
    sequence.reserve(encoded.size());

    for (uint8_t code : encoded) {
        switch (code) {
            case 0: sequence.push_back('A'); break;
            case 1: sequence.push_back('C'); break;
            case 2: sequence.push_back('G'); break;
            case 3: sequence.push_back('T'); break;
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


// author: Mateo Jakšić
// function for getting nucleotide from packed format
int get_nucleotide(const vector<uint8_t>& sequence, int index) {
    uint8_t byte = sequence[index/4];
    int position = 3 - (index % 4);
    return (byte >> (2 * position)) & 0b11;
}


// author: Mateo Jakšić
// function for getting hash value of each k-length subsequence<
int get_hash_value(const vector<uint8_t>& seq, int start, int k) {
    int value = 0;
    for (int j = 0; j < k; ++j) {
        value = value * 4 + get_nucleotide(seq, start + j);
    }
    return value;
}


// author: Mateo Jakšić
// function for creating hash table and finding matches
// quick explanation: function implements greedy algorithm between reference (R) and target (T) genome
//                    using hash table method where we try to find and output matches (position, length),
//                    keep in mind minimum length needs to be 2, and if we don't find them then we output 
//                    mismatches (mismatched sequence)
void greedy_hash_table_matching(const vector<uint8_t>& reference, const vector<uint8_t>& target, int k, int reference_length, int target_length) {
    int hash_size = 1 << (2 * k);
    int reference_size = reference_length;

    vector<int> hash_table(hash_size, 0);
    vector<int> positions(reference_size - k + 1, 0);

    for (int i = 1; i <= reference_size - k + 1; i++) {
        int reference_value = 0;
        for (int j = 0; j < k; j++) {
            reference_value = (reference_value << 2) | get_nucleotide(reference, i + j - 1);
        }

        positions[i-1] = hash_table[reference_value % hash_size];
        hash_table[reference_value % hash_size] = i;
    }

    int current_position = 1;
    int start_position = 1;
    vector<Segment> segments;

    while (current_position <= target_length) {
        int max_position = 0;
        int max_length = 0;

        if (current_position <= target_length - 1) {
            if (current_position <= target_length - k + 1) {
                int target_value = 0;
                for (int j = 0; j < k; j++) {
                    target_value = (target_value << 2) | get_nucleotide(target, current_position + j - 1);
                }
                int position = hash_table[target_value % hash_size];

                while (position != 0) {
                    int length = 0;
                    while ((position + length - 1 < reference_size) && (current_position + length - 1 < target_length) && 
                           get_nucleotide(reference, position + length - 1) == get_nucleotide(target, current_position + length - 1)) {
                        length++;
                    }

                    if (length >= 2 && length > max_length) {
                        max_position = position;
                        max_length = length;
                    }
                    position = positions[position-1];
                }
            }

            if (max_length == 0) {
                for (int reference_position = 1; reference_position <= reference_size; reference_position++) {
                    int length = 0;
                    while ((reference_position + length - 1 < reference_size) && (current_position + length - 1 < target_length) && 
                           get_nucleotide(reference, reference_position + length - 1) == get_nucleotide(target, current_position + length - 1)) {
                        length++;
                    }
                    
                    if (length >= 2 && length > max_length) {
                        max_position = reference_position;
                        max_length = length;
                    }
                }
            }
        }

        if (max_length >= 2) {
            if (start_position < current_position) {
                string mismatch_sequence;
                for (int index = start_position - 1; index < current_position - 1; index++) {
                    mismatch_sequence += to_string(get_nucleotide(target, index));
                }
                segments.push_back(Segment{false, {stoi(mismatch_sequence)}});
            }
            segments.push_back(Segment{true, {max_position, max_length}});
            
            start_position = current_position + max_length;
            current_position = current_position + max_length;
        } else {
            current_position++;
        }
    }

    if (start_position <= target_length) {
        string mismatch_sequence;
        for (int index = start_position - 1; index < target_length; index++) {
            mismatch_sequence += to_string(get_nucleotide(target, index));
        }
        if (!mismatch_sequence.empty()) {
            segments.push_back(Segment{false, {stoi(mismatch_sequence)}});
        }
    }

    cout << "[";
    for (size_t i = 0; i < segments.size(); ++i) {
        if (i > 0) cout << ",";
        const auto& segment = segments[i];
        cout << "(" << (segment.match ? to_string(segment.data[0]) + "," + to_string(segment.data[1]) 
                                  : to_string(segment.data[0])) << ")";
    }
    cout << "]";
}


// author: Mateo Jakšić
// function for reading compressed file
// quick explanation: we read line from compressed file and convert it in format
//                    where we have vector<bool> that stores information if it's
//                    a match or a mismatch, and vector<vector<int>> that stores 
//                    (position, length) for match or (sequence) for mismatch
pair<vector<vector<int>>,vector<bool>> read_compressed_sequence(const string& path) {
    ifstream file(path);
    string line;
    vector<vector<int>> segments;
    vector<bool> matches;
    string length;
    vector<int> segment;
    bool is_match = false;
    bool is_segment = false;
    
    getline(file, line);

    for (char c : line) {
        if (c == '[') {
            continue;
        } 
        else if (c == '(') {
            segment.clear();
            is_segment = true;
        }
        else if (isdigit(c)) {
            if (!is_match) {
                segment.push_back(stoi(string(1, c)));
            } else {
                length = c;
            }   
        }
        else if (c == ',' && is_segment) {
            is_match = true;
        }
        else if (c == ')') {
            if (is_match) {
                matches.push_back(is_match);
                is_match = false;

                segment.push_back(stoi(length));
                segments.push_back(segment);
            } else {
                matches.push_back(is_match);
                segments.push_back(segment);
            }
            is_segment = false;
        }
        else if (c == ']') {
            break;
        }
    }
    
    return make_pair(segments, matches);
}


// author: Mateo Jakšić
// function for reassembling genome sequence
// quick explanation: function takes compressed segments and reference genome
//                   if it's a match then we copy nucleotides from reference
//                   if it's a mismatch then we use the mismatched nucleotide
void reassembly_sequence(const vector<vector<int>>& segments, const vector<bool>& matches, const vector<uint8_t>& reference) {
    vector<uint8_t> result;
    
    for (size_t i = 0; i < matches.size(); ++i) {
        
        if (matches[i]) {
            int position = segments[i][0];
            int length = segments[i][1];
            
            for (int j = 0; j < length; ++j) {
                result.push_back(get_nucleotide(reference, position + j - 1));
            }
        } else {
            for(int nucleotide : segments[i]) {
                result.push_back(nucleotide);
            }
        }
    }
    cout << numbers_to_nucleotides(result);
}
