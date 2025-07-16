#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::ifstream inputFile;
    std::ofstream outputFile;
    std::string file1 = "file";
    std::string file2 = file1 + ".replace";

    inputFile.open(file1.c_str(), std::ios::in);
    if (!inputFile.is_open())
        std::cerr << "Could not open input file: " << file1 << "\n";
    outputFile.open(file2.c_str(), std::ios::out);
    if (!outputFile.is_open())
        std::cerr << "Could not open/create output file: " << file2 << "\n";
    std::string line = "hello every body hello";
    std::string s1 = "hello";
    std::string s2 = "good";
    int x = line.find(s1);
    if (x != -1)
    {
         line.erase(x, s1.length());
         line.insert(x, s2);
         while ((x = line.find(s1, x + s1.length())) != -1 )
         {
            line.erase(x, s1.length());
            line.insert(x, s2);
         }

    }
    std::cout << "[" << line << "]" <<std::endl;
    return 0;
}
