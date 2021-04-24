#include <iostream>
#include <queue>

int main()
{
    int int_Num;

    std::cin>> int_Num;

    int intarr_Time[int_Num];
    std::queue<int> que_Time;

    for(int i = 0; i < int_Num; i++)
    {
        std::cin>> intarr_Time[i];
    }

    for(int i = 0; i < int_Num; i++)
    {
        if(que_Time.empty()) que_Time.push(intarr_Time[i]);
        else
        {
            while(intarr_Time[i] - que_Time.front() > 3000) que_Time.pop();

            que_Time.push(intarr_Time[i]);
        }

        std::cout<< que_Time.size() << ' ';
    }

    return 0;
}
