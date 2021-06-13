#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#define FileName "Time.txt"

typedef struct tm Time;

struct TimeInfo
{
    std::string str_Day = "";
    std::string str_Month = "";
    int int_Day = 0;
    int int_Month = 0;
    int int_Date = 0;
    int int_Hr = 0;
    int int_Min = 0;
    int int_Sec = 0;
    int int_Year = 0;

    TimeInfo(std::string str_Time);
    int operator - (TimeInfo ti_Prev);
};

char* fn_GetCurrTime(time_t &time_Curr, Time* time_Info);
void  fn_OutputSavedTime();
void  fn_OutputCurrTime(char* str_Time, time_t &time_Curr, Time* time_Info);
void  fn_Update(char* str_Time, time_t &time_Curr, Time* time_Info);
void  fn_ToWords(char* str_Time, std::string &str_Words);
int   fn_CalculateSec();

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

int   fn_CalculateSec()
{
    int int_Sec = 0;
    time_t time_Curr;
    Time*  time_Info;
    char*  str_CurrTime;
    std::ifstream read_File;
    std::string str_PrevTime;

    read_File.open(FileName);
    getline(read_File, str_PrevTime, '\n');
    read_File.close();

    str_CurrTime = fn_GetCurrTime(time_Curr, time_Info);

    TimeInfo ti_Prev(str_PrevTime), ti_Curr(str_CurrTime);

    int_Sec = ti_Curr - ti_Prev;

    return int_Sec;
}

TimeInfo::TimeInfo(std::string str_Time)
{
    std::string str_Date = "", str_Hr = "", str_Min = "", str_Sec = "", str_Year = "";

    for(int i = 0; i < 3; i++) str_Day += str_Time[i];

    for(int i = 4; i < 7; i++) str_Month += str_Time[i];

    for(int i = 8; i < 10; i++) str_Date += str_Time[i];

    for(int i = 11; i < 13; i++) str_Hr += str_Time[i];

    for(int i = 14; i < 16; i++) str_Min += str_Time[i];

    for(int i = 17; i < 19; i++) str_Sec += str_Time[i];

    for(int i = 20; i < 24; i++) str_Year += str_Time[i];

    int_Date = std::stoi(str_Date);
    int_Hr   = std::stoi(str_Hr);
    int_Min  = std::stoi(str_Min);
    int_Sec  = std::stoi(str_Sec);
    int_Year = std::stoi(str_Year);
}

int TimeInfo::operator - (TimeInfo ti_Prev)
{
    return 0;
}
