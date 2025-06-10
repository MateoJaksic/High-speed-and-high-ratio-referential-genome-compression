#include "decompressor.h"
#include "utils.h"

#include <iostream>
#include <string>

using namespace std;

void decompress(const string& reference, const string& compressed) {
    
    string reference_nucleotides_sequence = read_sequence(reference);
    pair<vector<uint8_t>, int> reference_pair = nucleotides_to_numbers(reference_nucleotides_sequence);

    pair<vector<vector<int>>,vector<bool>> compressed_sequence = read_compressed_sequence(compressed);

    reassembly_sequence(compressed_sequence.first, compressed_sequence.second, reference_pair.first);
}
