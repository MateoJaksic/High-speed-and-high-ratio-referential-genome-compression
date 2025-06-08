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
    
    pair<vector<uint8_t>, int> reference_pair = nucleotides_to_numbers(reference_nucleotides_sequence);
    pair<vector<uint8_t>, int> target_pair = nucleotides_to_numbers(target_nucleotides_sequence);

    greedy_hash_table_matching(reference_pair.first, target_pair.first, 4, reference_pair.second, target_pair.second);
}