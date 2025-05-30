#include <fstream>
#include <string>

std::ifstream reader("fake_file.txt"); // Reads from file
std::ofstream writer("fake_file.txt"); // Writes to file

std::string line;

while (getline(reader, line)) {
    // Do something
}

reader.close();