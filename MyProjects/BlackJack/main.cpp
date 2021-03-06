#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

struct Card
{
    std::string str_Suit;
    std::string str_Word;
    int int_Count;
};

struct Player
{
    Card crd_Visible;
    Card crd_Invisible;
    Card crd_Add[3];
    int  int_CardCount;
    int  int_PointCount = 0;
    bool bl_HaveAce = false;
} plr_Banker, plr_Main;

int   intarr_UsedCard[4][13] = {};

bool  fn_CheckUsedCard(int int_Num1, int int_Num2);
void  fn_Line();
void  fn_ResetBkr();
void  fn_ResetPlr();
void  fn_CardDisplay(bool bl_SeeBkrCard);
void  fn_CountPoint(Player &plr_Func);
void  fn_Catch(bool &bl_GameOver, bool &bl_WinOrLose);
void  fn_Intro();
void  fn_GameOver(bool bl_WinOrLose);
void  fn_EndGame();
void  fn_SetCard(Card &crd_Poker, bool &bl_HaveAce);

int main()
{
    srand(time(NULL));

    int int_Ans;

    fn_Intro();

    while(true)
    {
        std::cout<< "\n(1) New Game\n"
                 << "(2) Quit Game\n\n";
        std::cin>> int_Ans;

        if(int_Ans == 2)
        {
            fn_EndGame();

            break;
        }

        intarr_UsedCard[4][13] = {};

        fn_ResetBkr();
        fn_ResetPlr();
        fn_SetCard(plr_Banker.crd_Visible, plr_Banker.bl_HaveAce);
        fn_SetCard(plr_Banker.crd_Invisible, plr_Banker.bl_HaveAce);
        fn_SetCard(plr_Main.crd_Visible, plr_Main.bl_HaveAce);
        fn_SetCard(plr_Main.crd_Invisible, plr_Main.bl_HaveAce);

        bool bl_WinGame;
        bool bl_PlrRoundEnd = false;
        bool bl_BkrRoundEnd = false;
        bool bl_FirstRound = true;
        bool bl_SeeBkrCard = false;
        bool bl_GameOver = false;

        while(!bl_PlrRoundEnd)
        {
            int int_Ans;

            fn_Line();
            fn_CardDisplay(bl_SeeBkrCard);
            fn_CountPoint(plr_Main);

            if(bl_FirstRound && plr_Main.bl_HaveAce && plr_Main.int_PointCount == 11)
            {
                bl_BkrRoundEnd = true;
                bl_WinGame = true;
                bl_GameOver = true;

                std::cout<< "\n[system] 21 Points in the first round!\n\n";

                break;
            }
            else if(plr_Main.int_PointCount > 21)
            {
                bl_BkrRoundEnd = true;
                bl_WinGame = false;
                bl_GameOver = true;

                std::cout<< "\n[system] Your points have exceed 21 points!\n\n";

                break;
            }
            else if(plr_Main.int_CardCount == 5)
            {
                bl_BkrRoundEnd = true;
                bl_WinGame = true;
                bl_GameOver = true;

                std::cout<< "\n[system] You got a \"Charlie\"!\n\n";

                break;
            }

            bl_FirstRound = false;

            std::cout<< "Add more cards or not?\n"
                     << "(1) Add a card\n"
                     << "(2) End up adding the card\n\n";
            std::cin>> int_Ans;

            if(int_Ans == 1)
            {
                fn_SetCard(plr_Main.crd_Add[plr_Main.int_CardCount - 2], plr_Main.bl_HaveAce);

                plr_Main.int_CardCount++;
            }
            else if(int_Ans == 2)
            {
                bl_SeeBkrCard = true;

                if(plr_Main.bl_HaveAce && plr_Main.int_PointCount <= 11)
                {
                    plr_Main.int_PointCount += 10;
                }

                fn_Line();

                break;
            }
        }

        if(bl_GameOver) fn_GameOver(bl_WinGame);
        else
        {
            fn_Line();

            std::cout<< "\n[system] Banker\'s turn!\n\n";
        }

        while(!bl_BkrRoundEnd)
        {
            fn_Line();
            fn_CardDisplay(bl_SeeBkrCard);
            fn_CountPoint(plr_Banker);

            int int_PlrSignboard = plr_Main.int_PointCount - plr_Main.crd_Invisible.int_Count;
            int int_Temp;

            if(plr_Banker.bl_HaveAce && plr_Banker.int_PointCount <= 11)
            {
                int_Temp = plr_Banker.int_PointCount + 10;
            }

            if(int_Temp > 21)
            {
                bl_GameOver = true;
                bl_WinGame = true;

                break;
            }
            else if(int_Temp >= 18)
            {
                fn_Catch(bl_GameOver, bl_WinGame);
            }
            else if(int_Temp < int_PlrSignboard + 11)
            {
                fn_SetCard(plr_Banker.crd_Add[plr_Banker.int_CardCount - 2], plr_Banker.bl_HaveAce);

                plr_Banker.int_CardCount++;
            }
            else if(int_Temp > (int_PlrSignboard + 11) || int_Temp < 16)
            {
                fn_SetCard(plr_Banker.crd_Add[plr_Banker.int_CardCount - 2], plr_Banker.bl_HaveAce);

                plr_Banker.int_CardCount++;
            }
            else
            {
                fn_Catch(bl_GameOver, bl_WinGame);
            }
        }

        if(!bl_BkrRoundEnd && bl_GameOver) fn_GameOver(bl_WinGame);
    }

    return 0;
}

bool  fn_CheckUsedCard(int int_Num1, int int_Num2)
{
    bool bl_UsedCard = false;

    if(intarr_UsedCard[int_Num1][int_Num2] == 1)
    {
        bl_UsedCard = true;
    }

    return bl_UsedCard;
}

void  fn_Line()
{
    for(int i = 0; i < 49; i++)
    {
        std::cout<< '=';
    }

    std::cout<< '\n';

    return;
}

void  fn_ResetBkr()
{
    plr_Banker.int_CardCount = 2;
    plr_Banker.int_PointCount = 0;
    plr_Banker.bl_HaveAce = false;

    for(int i = 0; i < 3; i++)
    {
        plr_Banker.crd_Add[i].int_Count = 0;
    }

    return;
}

void  fn_ResetPlr()
{
    plr_Main.int_CardCount = 2;
    plr_Main.int_PointCount = 0;
    plr_Main.bl_HaveAce = false;

    for(int i = 0; i < 3; i++)
    {
        plr_Main.crd_Add[i].int_Count = 0;
    }

    return;
}

void  fn_CardDisplay(bool bl_SeeBkrCard)
{
    std::cout<< "\nBanker\'s Cards:\n\n    ";

    if(bl_SeeBkrCard)
    {
        std::cout<< plr_Banker.crd_Visible.str_Suit << ' '
                 << plr_Banker.crd_Visible.str_Word << "\n    ";
        std::cout<< plr_Banker.crd_Invisible.str_Suit << ' '
                 << plr_Banker.crd_Invisible.str_Word << "\n    ";

        for(int i = 0; i < plr_Banker.int_CardCount-2; i++)
        {
            std::cout<< plr_Banker.crd_Add[i].str_Suit << ' '
                     << plr_Banker.crd_Add[i].str_Word << "\n    ";
        }
    }
    else
    {
        std::cout<< plr_Banker.crd_Visible.str_Suit << ' '
                 << plr_Banker.crd_Visible.str_Word << "\n    ";
        std::cout<< "??? ???\n";

        for(int i = 0; i < plr_Banker.int_CardCount-2; i++)
        {
            std::cout<< plr_Banker.crd_Add[i].str_Suit << ' '
                     << plr_Banker.crd_Add[i].str_Word << "\n    ";
        }
    }

    std::cout<< "\nYour Cards:\n\n    ";
    std::cout<< plr_Main.crd_Visible.str_Suit << ' '
             << plr_Main.crd_Visible.str_Word << "\n    ";
    std::cout<< plr_Main.crd_Invisible.str_Suit << ' '
             << plr_Main.crd_Invisible.str_Word << "\n    ";

    for(int i = 0; i < plr_Main.int_CardCount-2; i++)
    {
        std::cout<< plr_Main.crd_Add[i].str_Suit << ' '
                 << plr_Main.crd_Add[i].str_Word << "\n    ";
    }

    std::cout<< '\n';

    return;
}

void  fn_CountPoint(Player &plr_Func)
{
    int int_PointCount = 0;

    int_PointCount += plr_Func.crd_Visible.int_Count;
    int_PointCount += plr_Func.crd_Invisible.int_Count;

    for(int i = 0; i < plr_Func.int_CardCount - 2; i++)
    {
        int_PointCount += plr_Func.crd_Add[i].int_Count;
    }

    plr_Func.int_PointCount = int_PointCount;

    return;
}

void  fn_Catch(bool &bl_GameOver, bool &bl_WinOrLose)
{


    return;
}

void  fn_Intro()
{
    fn_Line();

    std::cout<< "\n                   "
             << "Black Jack\n\n";

    fn_Line();

    return;
}

void  fn_GameOver(bool bl_WinOrLose)
{
    if(bl_WinOrLose)
    {
        fn_Line();

        std::cout<< "\n                   "
                 << "You  Win!\n\n";

        fn_Line();
    }
    else
    {
        fn_Line();

        std::cout<< "\n                   "
                 << "You Lose!\n\n";

        fn_Line();
    }

    return;
}

void  fn_EndGame()
{
    fn_Line();

    std::cout<< "\n               "
             << "See You Next Time!\n\n";

    fn_Line();

    return;
}

void  fn_SetCard(Card &crd_Poker, bool &bl_HaveAce)
{
    int int_Num1, int_Num2;

    do
    {
        int_Num1 = rand() % 4;
        int_Num2 = rand() % 13;
    }
    while(fn_CheckUsedCard(int_Num1, int_Num2));

    switch(int_Num1)
    {
        case 0: crd_Poker.str_Suit = "Spade  ";   break;
        case 1: crd_Poker.str_Suit = "Heart  ";   break;
        case 2: crd_Poker.str_Suit = "Clubs  ";   break;
        case 3: crd_Poker.str_Suit = "Diamond";   break;
    }

    if((int_Num2 + 1) > 10) crd_Poker.int_Count = 10;
    else crd_Poker.int_Count = int_Num2 + 1;

    switch(int_Num2)
    {
        case 0 : crd_Poker.str_Word = 'A'; bl_HaveAce = true; break;
        case 10: crd_Poker.str_Word = 'J'; break;
        case 11: crd_Poker.str_Word = 'Q'; break;
        case 12: crd_Poker.str_Word = 'K'; break;

        default:
            if((int_Num2 + 1) >= 10)
            {
                crd_Poker.str_Word = ((int_Num2 + 1) / 10 + '0');
                crd_Poker.str_Word += ((int_Num2 + 1) % 10 + '0');
            }
            else crd_Poker.str_Word = int_Num2 + 1 + '0';
    }

    return;
}
