#include "utils.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <bitset>

using namespace std;

// author: Mateo Jakšić
// struct for storing compressed segments
// quick explanation: if it's a match then we store position and lenght
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
// function for getting nucleotide
int get_nucleotide(const vector<uint8_t>& byte, int index) {
    uint8_t packed = byte[index/4];
    int pos = 3 - (index % 4);  // Position within the byte, from right to left
    return (packed >> (2 * pos)) & 0b11;
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
// function for creating hash table and finding matches with greedy algorithm
// quick explanation: <to be added>
// TODO: runcase ref=AAAAGCTTCG, targ=AAAATCTTCGAAC gives [(1,4),(8,2),(7,6),(1)] but should give [(1,4),(8,2),(7,4),(1,2),(1)]
void greedy_hash_table_matching(const vector<uint8_t>& R, const vector<uint8_t>& T, int k, int target_length) {
    int s = 1 << (2 * k);
    int num_r = R.size() * 4;
    int actual_target_length = target_length;

    vector<int> h(s, 0);
    vector<int> p(num_r - k + 1, 0);

    for (int i = 1; i <= num_r - k + 1; i++) {
        int v_r = 0;
        for (int j = 0; j < k; j++) {
            v_r = (v_r << 2) | get_nucleotide(R, i + j - 1);
        }

        p[i-1] = h[v_r % s];
        h[v_r % s] = i;
    }

    int i = 1;
    int p_star = 1;
    vector<Segment> segments;

    while (i <= actual_target_length) {
        int p_max = 0;
        int l_max = 0;

        if (i <= actual_target_length - 1) {
            if (i <= actual_target_length - k + 1) {
                int v_t = 0;
                for (int j = 0; j < k; j++) {
                    v_t = (v_t << 2) | get_nucleotide(T, i + j - 1);
                }
                int j = h[v_t % s];

                while (j != 0) {
                    int l = 0;
                    while ((j + l - 1 < num_r) && (i + l - 1 < actual_target_length) && 
                           get_nucleotide(R, j + l - 1) == get_nucleotide(T, i + l - 1)) {
                        l++;
                    }

                    if (l >= 2 && l > l_max) {
                        p_max = j;
                        l_max = l;
                    }
                    j = p[j-1];
                }
            }

            if (l_max == 0) {
                for (int r_pos = 1; r_pos <= num_r; r_pos++) {
                    int l = 0;
                    while ((r_pos + l - 1 < num_r) && (i + l - 1 < actual_target_length) && 
                           get_nucleotide(R, r_pos + l - 1) == get_nucleotide(T, i + l - 1)) {
                        l++;
                    }
                    
                    if (l >= 2 && l > l_max) {
                        p_max = r_pos;
                        l_max = l;
                    }
                }
            }
        }

        if (l_max >= 2) {
            if (p_star < i) {
                string mismatch_str;
                for (int idx = p_star - 1; idx < i - 1; idx++) {
                    mismatch_str += to_string(get_nucleotide(T, idx));
                }
                segments.push_back(Segment{false, {stoi(mismatch_str)}});
            }
            segments.push_back(Segment{true, {p_max, l_max}});
            
            p_star = i + l_max;
            i = i + l_max;
        } else {
            i++;
        }
    }

    if (p_star <= actual_target_length) {
        string mismatch_str;
        for (int idx = p_star - 1; idx < actual_target_length; idx++) {
            mismatch_str += to_string(get_nucleotide(T, idx));
        }
        if (!mismatch_str.empty()) {
            segments.push_back(Segment{false, {stoi(mismatch_str)}});
        }
    }

    cout << "[";
    for (size_t i = 0; i < segments.size(); ++i) {
        if (i > 0) cout << ",";
        const auto& seg = segments[i];
        cout << "(" << (seg.match ? to_string(seg.data[0]) + "," + to_string(seg.data[1]) 
                                  : to_string(seg.data[0])) << ")";
    }
    cout << "]" << endl;
}
