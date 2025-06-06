#include "decompressor.h"

#include <iostream>
#include <string>

using namespace std;

// author: Mateo Jakšić
// main function used to get arguments and call decompress function from decompressor.h
int main(int argc, char* argv[]) {

    string reference_path = argv[1];
    string compressed_path = argv[2]; 
    
    decompress(reference_path, compressed_path);
    return 0;
}
