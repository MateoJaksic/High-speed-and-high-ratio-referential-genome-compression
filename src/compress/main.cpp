#include "compressor.h"

#include <iostream>
#include <string>

using namespace std;

// author: Mateo Jakšić
// main function used to get arguments and call compress function from compressor.h
int main(int argc, char* argv[]) {

    string reference_path = argv[1];
    string target_path = argv[2]; 
    
    compress(reference_path, target_path);
    return 0;
}
