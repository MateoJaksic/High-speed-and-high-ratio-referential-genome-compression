#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cstdint>

std::string read_sequence(const std::string& path);
uint8_t convert_nucleotide_to_number(const char& nucleotide);
std::pair<std::vector<uint8_t>, int> nucleotides_to_numbers(const std::string& path);
std::string numbers_to_nucleotides(const std::vector<uint8_t>& path);
void write_numbers(const std::vector<uint8_t> reference_values, const uint8_t& reference_leftovers);
void create_hash_table(const std::vector<uint8_t>& values, int k, std::vector<int>& h, std::vector<int>& p);
int get_nucleotide(const std::vector<uint8_t>& sequence, int index);
int get_hash_value(const std::vector<uint8_t>& seq, int start, int k);
void greedy_hash_table_matching(const std::vector<uint8_t>& R, const std::vector<uint8_t>& T, int k, int reference_length, int target_length);
std::pair<std::vector<std::vector<int>>, std::vector<bool>> read_compressed_sequence(const std::string& path);
void reassembly_sequence(const std::vector<std::vector<int>>& segments, const std::vector<bool>& matches, const std::vector<uint8_t>& reference);

#endif
