#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <windows.h>

void fn_Line();
void fn_TryOpenFile(std::string& str_FilePath);

int main()
{
    std::string str_FilePath_senior, str_FilePath_junior;

    fn_Line();

    std::cout<< "\n                 Random Pairing\n\n";

    fn_Line();

    std::cout<< "\nInput the file\'s path. (senior students\' name list)\n";

    fn_TryOpenFile(str_FilePath_senior);

    std::cout<< "Input the file\'s path. (junior students\' name list)\n";

    fn_TryOpenFile(str_FilePath_junior);

    srand(time(nullptr));

    int int_GroupCount, int_PeopleNum;
    std::vector<std::string> vec_Name_senior;
    std::vector<std::string> vec_Name_junior;
    std::ifstream read_File;
    std::string str_Name;

    read_File.open(str_FilePath_senior);

    while(getline(read_File, str_Name, '\n'))
    {
        vec_Name_senior.push_back(str_Name);
    }

    read_File.close();

    read_File.open(str_FilePath_junior);

    while(getline(read_File, str_Name, '\n'))
    {
        vec_Name_junior.push_back(str_Name);
    }

    read_File.close();

    int_GroupCount = vec_Name_senior.size();
    int_PeopleNum = vec_Name_junior.size();

    if(int_PeopleNum % int_GroupCount > 0) int_PeopleNum = int_PeopleNum / int_GroupCount + 1;
    else int_PeopleNum /= int_GroupCount;

    std::vector<std::string> vec_Group[int_GroupCount];
    std::set<int> set_Check;

    while(!vec_Name_junior.empty())
    {
        int int_RandGroup;

        do
        {
            int_RandGroup = rand() % int_GroupCount;
        }
        while(set_Check.count(int_RandGroup));

        set_Check.insert(int_RandGroup);

        if(set_Check.size() == int_GroupCount) set_Check.clear();

        vec_Group[int_RandGroup].push_back(vec_Name_junior.back());
        vec_Name_junior.pop_back();
    }

    std::fstream write_File;

    write_File.open("Result.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

    for(int i = 0; i < int_GroupCount; i++)
    {
        write_File<< vec_Name_senior[i] << ": ";

        for(int j = 0; j < vec_Group[i].size(); j++)
        {
            write_File<< vec_Group[i][j];

            if(j != vec_Group[i].size() - 1) write_File<< ", ";
        }

        write_File<< '\n';
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
