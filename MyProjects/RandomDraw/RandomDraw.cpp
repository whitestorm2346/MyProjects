#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <cstdio>

struct Element
{
    std::string str_Elem;
    bool bl_IsPicked;

    Element()
    {
        str_Elem = "";
        bl_IsPicked = false;
    }
};

void fn_Line();
void fn_TryOpenFile(std::string& str_FilePath);
void fn_Reset(Element* ele_Arr, unsigned int int_Size);
void fn_Pick(Element* ele_Arr, unsigned int int_Size);
bool fn_CheckAllPicked(Element* ele_Arr, unsigned int int_Size);

int main()
{
    std::string str_FilePath;

    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
    fn_Line();

    std::cout<< "\n                    Random Draw\n\n";

    fn_Line();

    std::cout<< "\nInput the file\'s path.\n";

    fn_TryOpenFile(str_FilePath);
    srand(time(nullptr));

    std::vector<std::string> vec_Elem;
    std::ifstream read_File;
    std::string str_Elem;

    read_File.open(str_FilePath);

    while(getline(read_File, str_Elem, '\n'))
    {
        vec_Elem.push_back(str_Elem);
    }

    read_File.close();

    unsigned int int_Size = vec_Elem.size();
    Element ele_Arr[int_Size];

    for(unsigned int i = 0; i < int_Size; i++)
    {
        ele_Arr[i].str_Elem = vec_Elem.back();
        vec_Elem.pop_back();
    }

    bool bl_true = true;

    while(bl_true)
    {
        char chr_Command;

        std::cout<< "Input a command.\n";
        std::cout<< "r -> Reset\n";
        std::cout<< "p -> Pick\n";
        std::cout<< "e -> End\n\n";
        std::cin>> chr_Command;

        switch(chr_Command)
        {
            case 'e': bl_true = false; break;
            case 'r': fn_Reset(ele_Arr, int_Size); break;
            case 'p': fn_Pick(ele_Arr, int_Size); if(fn_CheckAllPicked(ele_Arr, int_Size)) fn_Reset(ele_Arr, int_Size);
        }

        std::cout<< '\n';
    }

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

void fn_Reset(Element* ele_Arr, unsigned int int_Size)
{
    for(unsigned int i = 0; i < int_Size; i++)
    {
        ele_Arr[i].bl_IsPicked = false;
    }
}

void fn_Pick(Element* ele_Arr, unsigned int int_Size)
{
    unsigned int int_RandNum = rand() % int_Size;

    while(ele_Arr[int_RandNum].bl_IsPicked)
    {
        int_RandNum = rand() % int_Size;
    }

    ele_Arr[int_RandNum].bl_IsPicked = true;

    std::cout<< "[Result] " << ele_Arr[int_RandNum].str_Elem << '\n';
}

bool fn_CheckAllPicked(Element* ele_Arr, unsigned int int_Size)
{
    for(unsigned int i = 0; i < int_Size; i++)
    {
        if(!ele_Arr[i].bl_IsPicked) return false;
    }

    return true;
}
