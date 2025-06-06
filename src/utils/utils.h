#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cstdint>

std::string read_sequence(const std::string& path);
std::vector<uint8_t> nucleotides_to_numbers(const std::string& path);
std::string numbers_to_nucleotides(const std::vector<uint8_t>& path);

#endif
