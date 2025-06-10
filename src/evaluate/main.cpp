#include "evaluator.h"

#include <iostream>
#include <string>

using namespace std;

// author: Mateo Jakšić
// main function used to get arguments and call evaluate function from evaluate.h
int main(int argc, char* argv[]) {
    
    string target_path = argv[1];
    string decompressed_path = argv[2]; 
    
    evaluate(target_path, decompressed_path);
    return 0;
}
