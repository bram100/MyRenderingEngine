#include "readCommand.hpp"

//to recombile run "cmake -G Xcode .." from "xcode" folder
//https://ericasadun.com/2020/07/15/executing-command-line-directly-from-xcode/

#include <iostream>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib> // for exit function

#include "imageManager.hpp"

#define MAINPROGRAM
#include "variables.hpp"



int main(int argc, char* argv[]) {
    
    
    std::string cur_dir(argv[0]);
    int pos = cur_dir.find_last_of("/\\");
    std::cout << "path: " << cur_dir.substr(0, pos) << std::endl;

    if (argc < 2) {
        cerr << "Error reading .txt file \n";
        exit(-1);
    }
    //print working directory

    
    const std::string fileName = argv[1];
    std::cout << fileName << std::endl;
    std::ifstream file(fileName);

    if (!file) {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    if (std::getline(file, line)) {
        std::cout << "First line of the file: " << line << std::endl;
    } else {
        std::cout << "The file is empty." << std::endl;
    }

    
    std::cout << "Argument " << ": " << argv[1] << std::endl;

    readfile(argv[1]) ;
    closefile(argv[1]) ;

    ofstream outdata;
    
    std::cout << "fuc" << std::endl;

    return 0;

    
}
