#include "compressor.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;


// author: Mateo Jakšić
// function for referential genome compression
void compress(const string& reference, const string& target) {

    string reference_nucleotides_sequence = read_sequence(reference);
    string target_nucleotides_sequence = read_sequence(target);
    
    vector<uint8_t> reference_number_sequence = nucleotides_to_numbers(reference_nucleotides_sequence);
    vector<uint8_t> target_number_sequence = nucleotides_to_numbers(target_nucleotides_sequence);

    
}