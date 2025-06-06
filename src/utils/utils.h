#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cstdint>

std::string read_sequence(const std::string& path);
uint8_t convert_nucleotide_to_number(const char& nucleotide);
std::pair<std::vector<uint8_t>, uint8_t> nucleotides_to_numbers(const std::string& path);
std::string numbers_to_nucleotides(const std::vector<uint8_t>& path);
void write_numbers(const std::vector<uint8_t> reference_values, const uint8_t& reference_leftovers);

#endif
