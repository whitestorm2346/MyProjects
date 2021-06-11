#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>

void fn_Line();
void fn_TryOpenFile(std::string& str_FilePath);

int main()
{
    std::string str_FilePath;

    fn_Line();

    std::cout<< "\n                 Random Assignment\n\n";

    fn_Line();

    std::cout<< "\nInput the file\'s path.\n";

    fn_TryOpenFile(str_FilePath);
    srand(time(nullptr));

    unsigned int int_GroupCount, int_PeopleNum;
    std::vector<std::string> vec_Name;
    std::ifstream read_File;
    std::string str_Name;

    std::cout<< "Input the amount of the group.\n";
    std::cin>> int_GroupCount;
    std::cout<< '\n';

    read_File.open(str_FilePath);

    while(getline(read_File, str_Name, '\n'))
    {
        vec_Name.push_back(str_Name);
    }

    read_File.close();

    int_PeopleNum = vec_Name.size();

    if(int_PeopleNum % int_GroupCount > 0) int_PeopleNum = int_PeopleNum / int_GroupCount + 1;
    else int_PeopleNum /= int_GroupCount;

    std::vector<std::string> vec_Group[int_GroupCount];

    while(!vec_Name.empty())
    {
        int int_RandGroup = rand() % int_GroupCount;

        while(vec_Group[int_RandGroup].size() >= int_PeopleNum)
        {
            int_RandGroup = rand() % int_GroupCount;
        }

        vec_Group[int_RandGroup].push_back(vec_Name.back());
        vec_Name.pop_back();
    }

    std::fstream write_File;

    write_File.open("Result.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

    for(unsigned int i = 0; i < int_GroupCount; i++)
    {
        write_File<< "Group " << i + 1 << ": ";

        for(unsigned int j = 0; j < vec_Group[i].size(); j++)
        {
            write_File<< vec_Group[i][j];

            if(j != vec_Group[i].size() - 1) write_File<< ", ";
        }

        write_File<< std::endl;
    }

    write_File.close();

    return 0;
}

void fn_Line()
{
    for(int i = 0; i < 50; i++)
    {
        std::cout<< '=';
    }

    std::cout<< '\n';
}

void fn_TryOpenFile(std::string& str_FilePath)
{
    std::ifstream read_File;

    while(true)
    {
        getline(std::cin, str_FilePath, '\n');

        read_File.open(str_FilePath);

        if(read_File.is_open())
        {
            read_File.close();

            std::cout<< '\n';

            return;
        }

        read_File.close();

        std::cout<< "\nFile did not find.\n";
        std::cout<< "Please check if the file\'s path is right, and input the path again.\n\n";
        std::cout<< "\nInput the file\'s path.\n";
    }
}
