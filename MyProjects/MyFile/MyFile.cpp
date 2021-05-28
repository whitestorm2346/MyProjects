#include <iostream>
#include <fstream>
#include <string>

#define FileName "MyFile.txt"

void fn_ReadFile();
void fn_WriteFile(bool bl_Append);

int main()
{
    std::ifstream read_File;

    read_File.open(FileName);

    if(read_File.is_open())
    {
        std::cout<< "[system] File open successfully.\n\n";

        std::string str_Command;

        while(std::cin>> str_Command)
        {
            if(str_Command == "/end")
            {
                std::cout<< '\n';

                break;
            }
            else if(str_Command == "/read") fn_ReadFile();
            else if(str_Command == "/write") fn_WriteFile(false);
            else if(str_Command == "/append") fn_WriteFile(true);
            else std::cout<< "[system] This command doesn\'t exist.\n";

            std::cout<< '\n';
        }
    }
    else
    {
        std::cout<< "[system] File doesn\'t exist.\n";
        std::cout<< "[system] Create \"myFile.txt\" automatically.\n";

        std::fstream new_File;
        std::string str_NewWord = "This is a new file.";

        new_File.open(FileName, std::fstream::in | std::fstream::out | std::fstream::trunc);
        new_File<< str_NewWord;
        new_File.close();

        std::cout<< "[system] Create file successfully.\n";
        std::cout<< "[system] Please rerun the program.\n\n";
    }

    read_File.close();

    std::cout<< "[system] End up the program successfully.\n";

    return 0;
}

void fn_ReadFile()
{
    std::string str_Line, str_Outut = "";
    std::ifstream read_File;

    read_File.open(FileName);

    while(getline(read_File, str_Line, '\n'))
    {
        str_Outut += str_Line;
        str_Outut += '\n';
    }

    std::cout<< "\n==============================================\n\n";
    std::cout<< str_Outut;
    std::cout<< "\n==============================================\n";

    read_File.close();
}

void fn_WriteFile(bool bl_Append)
{
    std::string str_Input;
    std::ofstream write_File;

    if(bl_Append) write_File.open(FileName, std::ios::app);
    else write_File.open(FileName);

    std::cout<< "[system] Input the Message.\n";
    std::cin.ignore();
    getline(std::cin, str_Input, '\n');
    write_File<< str_Input << std::endl;

    write_File.close();

    std::cout<< "[system] Write file successfully.\n";
}
