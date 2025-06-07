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
// quick explanation: we want to use 2-bit integers for representing nucleotides, but since is
//                    doesn't exist in C++, we pack four or less 2-bit integers into a single uint8_t
pair<vector<uint8_t>, uint8_t> nucleotides_to_numbers(const string& sequence) {
    vector<uint8_t> encoded;
    encoded.reserve((sequence.size() + 3) / 4);

    uint8_t byte = 0;
    int count = 0;

    for(char nucleotide : sequence) {
        uint8_t value = convert_nucleotide_to_number(nucleotide);
        byte = (byte << 2) | value;
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
// function for geting nucleotide
int get_nucleotide(const vector<uint8_t>& byte, int index) {
    uint8_t packed = byte[index/4];
    int shift = 6 - 2 * (index % 4);  // Start from leftmost bits
    return (packed >> shift) & 0b11;
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
// quick explanation: 
void greedy_hash_table_matching(const vector<uint8_t>& R, const vector<uint8_t>& T, int k) {
    int num_r = R.size() * 4;
    int num_t = T.size() * 4;

    vector<int> h(num_r, 0);
    vector<int> p(num_r, 0);
    vector<Segment> segments;

    // Build hash table for reference sequence
    for (int i = 0; i <= num_r - k; ++i) {
        int v_r = 0;
        for (int j = 0; j < k; ++j) {
            v_r = v_r * 4 + get_nucleotide(R, i + j);
        }
        p[i] = h[v_r % num_r];
        h[v_r % num_r] = i;
    }

    int i = 0;
    int p_star = 0;
    
    while (i <= num_t - k) {
        int v_t = 0;
        for (int j = 0; j < k; ++j) {
            v_t = v_t * 4 + get_nucleotide(T, i + j);
        }

        int j = h[v_t % num_r];
        int p_max = -1;
        int l_max = 0;

        while (j != 0) {
            int l = 0;
            while ((j + l < num_r) && (i + l < num_t) && 
                   get_nucleotide(R, j + l) == get_nucleotide(T, i + l)) {
                ++l;
            }
            
            if (l >= k && l > l_max) {
                p_max = j;
                l_max = l;
            }
            j = p[j % num_r];
        }

        if (l_max > 0) {
            // Handle any mismatches before this match
            if (p_star < i) {
                vector<int> mismatch_segment;
                for (int index = p_star; index < i; ++index) {
                    mismatch_segment.push_back(get_nucleotide(T, index));
                }
                if (!mismatch_segment.empty()) {
                    segments.push_back(Segment{false, mismatch_segment});
                }
            }
            // Add the match
            segments.push_back(Segment{true, {p_max, l_max}});
            p_star = i + l_max;
            i += l_max;
        } else {
            vector<int> mismatch_segment;
            mismatch_segment.push_back(get_nucleotide(T, i));
            segments.push_back(Segment{false, mismatch_segment});
            i++;
        }
    }

    // Handle remaining mismatches at the end
    if (p_star < num_t) {
        vector<int> mismatch_segment;
        for (int index = p_star; index < num_t; ++index) {
            mismatch_segment.push_back(get_nucleotide(T, index));
        }
        if (!mismatch_segment.empty()) {
            segments.push_back(Segment{false, mismatch_segment});
        }
    }

    // Output the segments
    bool first = true;
    cout << "[";
    for (const auto& seg : segments) {
        if (!first) cout << ",";
        if (seg.match) {
            cout << "(" << seg.data[0] << "," << seg.data[1] << ")";
        } else {
            cout << "(";
            for (size_t x = 0; x < seg.data.size(); ++x) {
                cout << seg.data[x];
                if (x + 1 < seg.data.size()) cout << ",";
            }
            cout << ")";
        }
        first = false;
    }
    cout << "]" << endl;
}
