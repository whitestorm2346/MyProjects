#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#define FileName "Time.txt"

typedef struct tm Time;

char* fn_GetCurrTime(time_t &time_Curr, Time* time_Info);
void  fn_OutputSavedTime();
void  fn_OutputCurrTime(char* str_Time, time_t &time_Curr, Time* time_Info);
void  fn_Update(char* str_Time, time_t &time_Curr, Time* time_Info);
void  fn_ToWords(char* str_Time, std::string &str_Words);

int main()
{
    time_t time_Curr;
    Time*  time_Info;
    char*  str_Time;
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
            else if(str_Command == "/update") fn_Update(str_Time, time_Curr, time_Info);
            else if(str_Command == "/saved_time") fn_OutputSavedTime();
            else if(str_Command == "/curr_time") fn_OutputCurrTime(str_Time, time_Curr, time_Info);
            else std::cout<< "[system] This command doesn\'t exist.\n";

            std::cout<< '\n';
        }
    }
    else
    {
        std::cout<< "[system] File doesn\'t exist.\n";
        std::cout<< "[system] Create \"Time.txt\" automatically.\n";

        std::fstream new_File;

        new_File.open(FileName, std::fstream::in | std::fstream::out | std::fstream::trunc);
        str_Time = fn_GetCurrTime(time_Curr, time_Info);
        new_File<< str_Time;
        new_File.close();

        std::cout<< "[system] Create file successfully.\n";
        std::cout<< "[system] Please rerun the program.\n\n";
    }

    read_File.close();

    std::cout<< "[system] End up the program successfully.\n";

    return 0;
}

char* fn_GetCurrTime(time_t &time_Curr, Time* time_Info)
{
    std::time(&time_Curr);
    time_Info = std::localtime(&time_Curr);

    return std::asctime(time_Info);
}

void  fn_OutputSavedTime()
{
    std::ifstream read_File;
    std::string str_Time = "";

    read_File.open(FileName);

    getline(read_File, str_Time, '\n');
    std::cout<< "[system] " << str_Time << '\n';

    read_File.close();
}

void  fn_OutputCurrTime(char* str_Time, time_t &time_Curr, Time* time_Info)
{
    str_Time = fn_GetCurrTime(time_Curr, time_Info);

    std::cout<< "[system] " << str_Time;
}

void  fn_Update(char* str_Time, time_t &time_Curr, Time* time_Info)
{
    std::ofstream write_File;

    write_File.open(FileName);

    str_Time = fn_GetCurrTime(time_Curr, time_Info);
    write_File<< str_Time;
    std::cout<< "[system] Update successfully.\n";

    write_File.close();
}
