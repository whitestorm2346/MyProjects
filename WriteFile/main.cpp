#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::fstream write_File;
    std::string str_FileName, str_FileExtension;

    std::cout<< "Input the name of file.\n";

    getline(std::cin, str_FileName, '\n');

    std::cout<< "\nInput the file extension.\n";
    std::cin>> str_FileExtension;

    str_FileName += ".";
    str_FileName += str_FileExtension;

    write_File.open(str_FileName, std::fstream::in | std::fstream::out | std::fstream::trunc);

    for(std::string str_Input; getline(std::cin, str_Input, '\n');)
    {
        write_File<< str_Input << '\n';
    }

    write_File.close();

    return 0;
}
