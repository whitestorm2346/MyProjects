#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<conio.h>		// getch()
#include<windows.h>		// Sleep()
#include<cctype>		// ::tolower
#include<algorithm>		// transform()

int int_SeatNum[40];    //在這裡改人數
int intarr_V1[6][7], intarr_V2[6][7];   //在這裡改大小

void  fn_SetSeatNum();
void  fn_FillNum(int int_Num);
void  fn_Display(int int_Vision, int int_Mode, double db_Time = 0)
{
    switch(int_Vision)
    {
        case 1:
            std::cout<< "\t\t\t[講台]\n\n";

            for(int i = 0; i < 6; i++)
            {
                for(int j = 0; j < 7; j++)
                {
                    if((i == 5 && j == 0) || (i == 5 && j == 6))
                    {
                        std::cout<< '\t';

                        continue;
                    }

                    if(int_Mode == 2) Sleep(db_Time);
                    else if(int_Mode == 3) getch();

                    std::cout<< intarr_V1[i][j] << '\t';
                }

                std::cout<< "\n\n";
            }

            std::cout<< "\n\n==================== 執行完畢 ====================\n";

            break;

        case 2:
            for(int i = 0; i < 6; i++)
            {
                std::cout<< "\n\n";

                for(int j = 0; j < 7; j++)
                {
                    if((i == 0 && j == 6) || (i == 0 && j == 0))
                    {
                        std::cout<< '\t';

                        continue;
                    }

                    if(int_Mode == 2) Sleep(db_Time);
                    else if(int_Mode == 3) getch();

                    std::cout<< intarr_V2[i][j] << '\t';
                }
            }

            std::cout<< "\n\n\t\t\t[講台]\n"
                     << "\n==================== 執行完畢 ====================\n";

            break;
    }

    return;
}

int main()
{
	int int_Vision, int_Mode;
	double db_Second, db_Time;
	std::string str_Ans;

	srand(time(NULL));

	std::cout<< "=========== 207-隨機座位 ===========\n\n 按Enter以啟動程式...\n";

	getch();

	do
	{
		std::cout<< "\n=========== 設定視角 ===========\n";

		while(true)
		{
			std::cout<< "\n 請選擇視角：(輸入數字1或2)\n(1)看向講台\n(2)看向桌椅\n\n回答：";
			std::cin>> int_Vision;

			if(int_Vision == 1 || int_Vision == 2)
			{
				std::cout<< "\n=========== 設定模式 ===========\n";

				break;
			}

			std::cout<< "\n================================\n"
                     << "\n 無法辨識，請重新輸入！\n\n================================\n";
		}

		while(true)
		{
			std::cout<< "\n 請選擇顯示方式：(輸入數字1或2或3)\n(1)同時顯示號碼"
                     << "\n(2)逐一顯示號碼\n(3)按Enter鍵顯示號碼\n\n回答：";
			std::cin>>int_Mode;

			if(int_Mode == 1 || int_Mode == 2 || int_Mode == 3) break;

			std::cout<< "\n================================\n"
                     << "\n 無法辨識，請重新輸入！\n\n================================\n";
		}

        do
        {
            fn_SetSeatNum();
            fn_FillNum(int_Vision);

            switch(int_Mode)
            {
                case 1:
                    std::cout<< "\n=========== 設定完成 ===========\n"
                             << "\n==================== 開始執行 ====================\n\n";

                    switch(int_Vision)
                    {
                        case 1: fn_Display(1, 1); break;
                        case 2: fn_Display(2, 1); break;
                    }

                    break;

                case 2:
                    std::cout<< "\n=========== 設定時間 ===========\n";

                    while(true)
                    {
                        std::cout<< "\n 請輸入間隔的秒數(可輸入浮點數)\n\n回答：";
                        std::cin>> db_Second;

                        if(db_Second >= 0) break;
                        else
                        {
                            std::cout<< "\n================================\n"
                                     << "\n 無法辨識，請重新輸入！\n\n================================\n";
                        }
                    }

                    std::cout<< "\n=========== 設定完成 ===========\n"
                             << "\n==================== 開始執行 ====================\n\n";

                    db_Time = 1000 * db_Second;

                    switch(int_Vision)
                    {
                        case 1: fn_Display(1, 2, db_Time); break;
                        case 2: fn_Display(2, 2, db_Time); break;
                    }

                    break;

                case 3:
                    std::cout<< "\n=========== 設定完成 ===========\n"
                             << "\n==================== 開始執行 ====================\n\n";

                    switch(int_Vision)
                    {
                        case 1: fn_Display(1, 3); break;
                        case 2: fn_Display(2, 3); break;
                    }

                    break;
            }

            while(true)
            {
                std::cout<< "\n 輸入\"again\"可再次產生新座位"
                         << "\n 輸入\"reset\"可重新設定"
                         << "\n 輸入\"end\"可結束程式\n\n回答：";
                std::cin>> str_Ans;

                std::transform(str_Ans.begin(), str_Ans.end(), str_Ans.begin(), ::tolower);

                if(str_Ans == "end" || str_Ans == "again" || str_Ans == "reset") break;

                std::cout<< "\n==================================================\n"
                         << "\n 無法辨識，請重新輸入！\n\n==================================================\n";
            }
        }
        while(str_Ans == "again");

        if(str_Ans == "end") std::cout<< "\n==================== 程式結束 ====================\n";
        else if(str_Ans == "reset") std::cout<< "\n=========== 前往設定 ===========\n";
	}
	while(str_Ans == "reset");

	return 0;
}

void  fn_SetSeatNum()
{
    for(int i = 1; i <= 39; i++)
    {
        int j;

        do
        {
            do
            {
                int_SeatNum[i - 1] = rand() % 43 + 1;
            }
            while(int_SeatNum[i - 1] == 41 || int_SeatNum[i - 1] == 10 ||
				  int_SeatNum[i - 1] == 20 || int_SeatNum[i - 1] == 5);

            for(j = 1; j < i; j++)
            {
                if(int_SeatNum[i - 1] == int_SeatNum[j - 1]) break;
            }
        }
        while(j != i);
    }

    return;
}

void  fn_FillNum(int int_Num)
{
    int int_Count = 0;

    switch(int_Num)
    {
        case 1:
            for(int i = 0; i < 6; i++)
            {
                for(int j = 0; j < 7; j++)
                {
                    if(i == 0 && j == 3)
                    {
                        intarr_V1[0][3] = 20;

                        continue;
                    }

                    if((i == 5 && j == 0) || (i == 5 && j == 6))
                    {
                        std::cout<< '\t';

                        continue;
                    }

                    intarr_V1[i][j] = int_SeatNum[int_Count];
                    int_Count++;
                }
            }

            break;

        case 2:
            for(int i = 0; i < 6; i++)
            {
                for(int j = 0; j < 7; j++)
                {
                    if((i == 0 && j == 6) || (i == 0 && j == 0))
                    {
                        std::cout<< '\t';

                        continue;
                    }

                    if(i == 5 && j == 3)
                    {
                        intarr_V2[5][3] = 20;

                        continue;
                    }

                    intarr_V2[i][j] = int_SeatNum[int_Count];
                    int_Count++;
                }
            }

            break;
    }

    return;
}
