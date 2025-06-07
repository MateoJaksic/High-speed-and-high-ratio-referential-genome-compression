#include "compressor.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <bitset>

using namespace std;


// author: Mateo Jakšić
// function for referential genome compression
void compress(const string& reference, const string& target) {

    string reference_nucleotides_sequence = read_sequence(reference);
    string target_nucleotides_sequence = read_sequence(target);
    
    pair<vector<uint8_t>, uint8_t> reference_pair = nucleotides_to_numbers(reference_nucleotides_sequence);
    vector<uint8_t> reference_values = reference_pair.first;
    uint8_t reference_leftovers = reference_pair.second;

    pair<vector<uint8_t>, uint8_t> target_pair = nucleotides_to_numbers(target_nucleotides_sequence);
    vector<uint8_t> target_values = target_pair.first;
    uint8_t target_leftovers = target_pair.second;

    // write_numbers(reference_values, reference_leftovers);
    // write_numbers(target_values, target_leftovers);

    greedy_hash_table_matching(reference_values, target_values, 16);
}