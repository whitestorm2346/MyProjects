#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<conio.h>		// getch()
#include<windows.h>		// Sleep()
#include<cctype>		// ::tolower
#include<algorithm>		// transform()

int int_SeatNum[40];    //�b�o�̧�H��
int intarr_V1[6][7], intarr_V2[6][7];   //�b�o�̧�j�p

void  fn_SetSeatNum();
void  fn_FillNum(int int_Num);
void  fn_Display(int int_Vision, int int_Mode, double db_Time = 0)
{
    switch(int_Vision)
    {
        case 1:
            std::cout<< "\t\t\t[���x]\n\n";

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

            std::cout<< "\n\n==================== ���槹�� ====================\n";

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

            std::cout<< "\n\n\t\t\t[���x]\n"
                     << "\n==================== ���槹�� ====================\n";

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

	std::cout<< "=========== 207-�H���y�� ===========\n\n ��Enter�H�Ұʵ{��...\n";

	getch();

	do
	{
		std::cout<< "\n=========== �]�w���� ===========\n";

		while(true)
		{
			std::cout<< "\n �п�ܵ����G(��J�Ʀr1��2)\n(1)�ݦV���x\n(2)�ݦV���\n\n�^���G";
			std::cin>> int_Vision;

			if(int_Vision == 1 || int_Vision == 2)
			{
				std::cout<< "\n=========== �]�w�Ҧ� ===========\n";

				break;
			}

			std::cout<< "\n================================\n"
                     << "\n �L�k���ѡA�Э��s��J�I\n\n================================\n";
		}

		while(true)
		{
			std::cout<< "\n �п����ܤ覡�G(��J�Ʀr1��2��3)\n(1)�P����ܸ��X"
                     << "\n(2)�v�@��ܸ��X\n(3)��Enter����ܸ��X\n\n�^���G";
			std::cin>>int_Mode;

			if(int_Mode == 1 || int_Mode == 2 || int_Mode == 3) break;

			std::cout<< "\n================================\n"
                     << "\n �L�k���ѡA�Э��s��J�I\n\n================================\n";
		}

        do
        {
            fn_SetSeatNum();
            fn_FillNum(int_Vision);

            switch(int_Mode)
            {
                case 1:
                    std::cout<< "\n=========== �]�w���� ===========\n"
                             << "\n==================== �}�l���� ====================\n\n";

                    switch(int_Vision)
                    {
                        case 1: fn_Display(1, 1); break;
                        case 2: fn_Display(2, 1); break;
                    }

                    break;

                case 2:
                    std::cout<< "\n=========== �]�w�ɶ� ===========\n";

                    while(true)
                    {
                        std::cout<< "\n �п�J���j�����(�i��J�B�I��)\n\n�^���G";
                        std::cin>> db_Second;

                        if(db_Second >= 0) break;
                        else
                        {
                            std::cout<< "\n================================\n"
                                     << "\n �L�k���ѡA�Э��s��J�I\n\n================================\n";
                        }
                    }

                    std::cout<< "\n=========== �]�w���� ===========\n"
                             << "\n==================== �}�l���� ====================\n\n";

                    db_Time = 1000 * db_Second;

                    switch(int_Vision)
                    {
                        case 1: fn_Display(1, 2, db_Time); break;
                        case 2: fn_Display(2, 2, db_Time); break;
                    }

                    break;

                case 3:
                    std::cout<< "\n=========== �]�w���� ===========\n"
                             << "\n==================== �}�l���� ====================\n\n";

                    switch(int_Vision)
                    {
                        case 1: fn_Display(1, 3); break;
                        case 2: fn_Display(2, 3); break;
                    }

                    break;
            }

            while(true)
            {
                std::cout<< "\n ��J\"again\"�i�A�����ͷs�y��"
                         << "\n ��J\"reset\"�i���s�]�w"
                         << "\n ��J\"end\"�i�����{��\n\n�^���G";
                std::cin>> str_Ans;

                std::transform(str_Ans.begin(), str_Ans.end(), str_Ans.begin(), ::tolower);

                if(str_Ans == "end" || str_Ans == "again" || str_Ans == "reset") break;

                std::cout<< "\n==================================================\n"
                         << "\n �L�k���ѡA�Э��s��J�I\n\n==================================================\n";
            }
        }
        while(str_Ans == "again");

        if(str_Ans == "end") std::cout<< "\n==================== �{������ ====================\n";
        else if(str_Ans == "reset") std::cout<< "\n=========== �e���]�w ===========\n";
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
