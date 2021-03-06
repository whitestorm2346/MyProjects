#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#define DelayTime 2

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
    int  int_Money;
    bool bl_HaveAce = false;

    void fn_Reset();
} plr_Banker, plr_Main;

bool  fn_CheckUsedCard(int int_Num1, int int_Num2, int* intarr_CheckUsedCard);
void  fn_Line();
void  fn_Delay(int int_Time);
void  fn_CardDisplay(bool bl_SeeBkrCard);
void  fn_CountPoint(Player &plr_Func);
void  fn_Catch(bool &bl_GameOver, int &int_WinOrLose);
void  fn_Intro();
void  fn_GameOver(int int_WinOrLose, int int_BetMoney, int int_Num);
void  fn_EndGame();
void  fn_SetCard(Card &crd_Poker, bool &bl_HaveAce, int* intarr_CheckUsedCard);

int main()
{
    srand(time(NULL));

    int int_Ans;

    fn_Intro();

    plr_Main.int_Money = 10000;

    while(true)
    {
        if(plr_Main.int_Money <= 0)
        {
            fn_Line();

            std::cout<< "\n           You Lost All Your Money!\n\n";

            fn_Line();

            break;
        }

        std::cout<< "\n(1) New Game\n(2) Quit Game\n\n";
        std::cin>> int_Ans;

        if(int_Ans == 2)
        {
            fn_EndGame();

            break;
        }

        int intarr_UsedCard[4][13] = {};
        int* intptr_UsedCard = reinterpret_cast<int*>(intarr_UsedCard);
        int int_BetMoney, int_BetNum = 1;

        fn_Line();

        std::cout<< "\nYour Money: " << plr_Main.int_Money << '\n';


        while(true)
        {
            std::cout<< "\nInput a number of money you want to lay a bet.\n\nBet money: ";
            std::cin>> int_BetMoney;

            if(int_BetMoney > 0 && int_BetMoney <= plr_Main.int_Money) break;
            else std::cout<< "\n[system] Please input a correct number of money!\n";
        }

        std::cout<< "\n\n";

        plr_Banker.fn_Reset();
        plr_Main.fn_Reset();
        fn_SetCard(plr_Banker.crd_Visible, plr_Banker.bl_HaveAce, intptr_UsedCard);
        fn_SetCard(plr_Banker.crd_Invisible, plr_Banker.bl_HaveAce, intptr_UsedCard);
        fn_SetCard(plr_Main.crd_Visible, plr_Main.bl_HaveAce, intptr_UsedCard);
        fn_SetCard(plr_Main.crd_Invisible, plr_Main.bl_HaveAce, intptr_UsedCard);
        fn_CountPoint(plr_Banker);
        fn_CountPoint(plr_Main);

        int  int_Result;
        bool bl_PlrRoundEnd = false;
        bool bl_BkrRoundEnd = false;
        bool bl_FirstRound = true;
        bool bl_SeeBkrCard = false;
        bool bl_GameOver = false;

        while(!bl_PlrRoundEnd)
        {
            int int_Ans;

            if(bl_FirstRound && plr_Banker.bl_HaveAce && plr_Banker.int_PointCount == 11)
            {
                bl_BkrRoundEnd = true;
                bl_SeeBkrCard = true;
                bl_GameOver = true;
                int_Result = 0;

                fn_Line();
                fn_CardDisplay(bl_SeeBkrCard);
                fn_CountPoint(plr_Main);
                fn_CountPoint(plr_Banker);

                std::cout<< "\n[system] The banker got 21 Points in the first round!\n\n";

                break;
            }
            else if(bl_FirstRound && plr_Main.bl_HaveAce && plr_Main.int_PointCount == 11)
            {
                bl_BkrRoundEnd = true;
                bl_SeeBkrCard = true;
                bl_GameOver = true;
                int_BetNum = 2;
                int_Result = 1;

                fn_Line();
                fn_CardDisplay(bl_SeeBkrCard);
                fn_CountPoint(plr_Main);
                fn_CountPoint(plr_Banker);

                std::cout<< "\n[system] You got 21 Points in the first round!\n\n";

                break;
            }
            else
            {
                fn_Line();
                fn_CardDisplay(bl_SeeBkrCard);
                fn_CountPoint(plr_Main);
                fn_CountPoint(plr_Banker);
            }

            if(plr_Main.int_PointCount > 21)
            {
                bl_BkrRoundEnd = true;
                bl_GameOver = true;
                int_Result = 0;

                std::cout<< "\n[system] Your points have exceed 21 points!\n\n";

                break;
            }
            else if(plr_Main.int_CardCount == 5)
            {
                bl_BkrRoundEnd = true;
                bl_GameOver = true;
                int_BetNum = 2;
                int_Result = 1;

                std::cout<< "\n[system] You got a \"Charlie\"!\n\n";

                break;
            }

            bl_FirstRound = false;

            std::cout<< "Add more cards or not?\n(1) Add a card\n(2) End up adding the card\n\n";
            std::cin>> int_Ans;

            switch(int_Ans)
            {
                case 1:
                    fn_SetCard(plr_Main.crd_Add[plr_Main.int_CardCount - 2], plr_Main.bl_HaveAce, intptr_UsedCard);

                    plr_Main.int_CardCount++;

                    std::cout<< "\n[system] You add a card\n\n";

                    break;

                case 2:
                    bl_SeeBkrCard = true;
                    bl_PlrRoundEnd = true;

                    if(plr_Main.bl_HaveAce && plr_Main.int_PointCount <= 11) plr_Main.int_PointCount += 10;

                    fn_Line();

                    break;
            }
        }

        if(bl_GameOver)
        {
            fn_GameOver(int_Result, int_BetMoney, int_BetNum);

            continue;
        }
        else
        {
            fn_Line();

            std::cout<< "\n[system] Banker\'s turn!\n\n";
        }

        while(bl_PlrRoundEnd)
        {
            fn_Line();
            fn_CountPoint(plr_Banker);
            fn_CardDisplay(bl_SeeBkrCard);
            fn_Delay(DelayTime * 1000);

            if(bl_BkrRoundEnd) break;

            int int_PlrSignboard = plr_Main.int_PointCount - plr_Main.crd_Invisible.int_Count;
            int int_Temp = plr_Banker.int_PointCount;

            if(plr_Banker.bl_HaveAce && plr_Banker.int_PointCount <= 11) int_Temp += 10;

            if(plr_Banker.int_CardCount >= 5)
            {
                bl_GameOver = true;
                bl_BkrRoundEnd = true;
                int_Result = 0;

                std::cout<< "\n[system] The banker got a \"Charlie\"!\n\n";

                break;
            }
            else if(int_Temp >= 18 || int_Temp >= int_PlrSignboard + 10)
            {
                std::cout<< "\n[system] The banker catch your cards\n\n";

                fn_Catch(bl_GameOver, int_Result);

                bl_BkrRoundEnd = true;

                break;
            }
            else
            {
                fn_SetCard(plr_Banker.crd_Add[plr_Banker.int_CardCount - 2], plr_Banker.bl_HaveAce, intptr_UsedCard);

                plr_Banker.int_CardCount++;

                std::cout<< "\n[system] The banker add a card\n\n";
            }

            fn_CountPoint(plr_Banker);

            int_Temp = plr_Banker.int_PointCount;

            if(plr_Banker.bl_HaveAce && plr_Banker.int_PointCount <= 11) int_Temp += 10;

            if(int_Temp > 21)
            {
                bl_GameOver = true;
                bl_BkrRoundEnd = true;
                int_Result = 1;

                fn_Line();
                fn_CardDisplay(bl_SeeBkrCard);

                std::cout<< "\n[system] The banker\'s points has exceed 21 points!\n\n";

                break;
            }
        }

        if(bl_GameOver) fn_GameOver(int_Result, int_BetMoney, int_BetNum);
    }

    return 0;
}

void Player::fn_Reset()
{
    this->int_CardCount = 2;
    this->int_PointCount = 0;
    this->bl_HaveAce = false;

    for(int i = 0; i < 3; i++)
    {
        this->crd_Add[i].int_Count = 0;
    }

    return;
}

bool  fn_CheckUsedCard(int int_Num1, int int_Num2, int* intarr_UsedCard)
{
    bool bl_UsedCard = false;

    if(*(intarr_UsedCard + int_Num1 * 13 + int_Num2) == 1) bl_UsedCard = true;
    else *(intarr_UsedCard + int_Num1 * 13 + int_Num2) = 1;

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

void  fn_Delay(int int_Time)
{
    clock_t now = clock();

    while(clock() - now < int_Time);

    return;
}

void  fn_CardDisplay(bool bl_SeeBkrCard)
{
    std::cout<< "\nBanker\'s Cards:\n\n    ";
    std::cout<< plr_Banker.crd_Visible.str_Suit << ' ' << plr_Banker.crd_Visible.str_Word << "\n    ";

    if(!bl_SeeBkrCard) std::cout<< "??????  ?\n";
    else std::cout<< plr_Banker.crd_Invisible.str_Suit << ' ' << plr_Banker.crd_Invisible.str_Word << "\n    ";

    for(int i = 0; i < plr_Banker.int_CardCount - 2; i++)
    {
        std::cout<< plr_Banker.crd_Add[i].str_Suit << ' ' << plr_Banker.crd_Add[i].str_Word << "\n    ";
    }

    std::cout<< "\nYour Cards:\n\n    ";
    std::cout<< plr_Main.crd_Visible.str_Suit << ' ' << plr_Main.crd_Visible.str_Word << "\n    ";
    std::cout<< plr_Main.crd_Invisible.str_Suit << ' ' << plr_Main.crd_Invisible.str_Word << " (covered)\n    ";

    for(int i = 0; i < plr_Main.int_CardCount - 2; i++)
    {
        std::cout<< plr_Main.crd_Add[i].str_Suit << ' ' << plr_Main.crd_Add[i].str_Word << "\n    ";
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

void  fn_Catch(bool &bl_GameOver, int &int_WinOrLose)
{
    bl_GameOver = true;

    if(plr_Banker.bl_HaveAce && plr_Banker.int_PointCount <= 11) plr_Banker.int_PointCount += 10;

    if(plr_Banker.int_PointCount > plr_Main.int_PointCount) int_WinOrLose = 0;
    else if(plr_Banker.int_PointCount == plr_Main.int_PointCount) int_WinOrLose = -1;
    else int_WinOrLose = 1;

    return;
}

void  fn_Intro()
{
    fn_Line();

    std::cout<< "\n                   Black Jack\n\n";

    fn_Line();

    return;
}

void  fn_GameOver(int int_WinOrLose, int int_BetMoney, int int_Num)
{
    fn_Line();

    switch(int_WinOrLose)
    {
        case -1:
            std::cout<< "\n                     Draw!  \n\n";

            break;

        case  0:
            std::cout<< "\n                   You Lose!\n\n";

            plr_Main.int_Money -= int_BetMoney;

            break;

        case  1:
            std::cout<< "\n                   You  Win!\n\n";

            plr_Main.int_Money += int_BetMoney * int_Num;
    }

    fn_Line();

    return;
}

void  fn_EndGame()
{
    fn_Line();

    std::cout<< "\n               See You Next Time!\n\n";

    fn_Line();

    return;
}

void  fn_SetCard(Card &crd_Poker, bool &bl_HaveAce, int* intarr_CheckUsedCard)
{
    int int_Num1, int_Num2;

    do
    {
        int_Num1 = rand() % 4;
        int_Num2 = rand() % 13;
    }
    while(fn_CheckUsedCard(int_Num1, int_Num2, intarr_CheckUsedCard));

    switch(int_Num1)
    {
        case 0: crd_Poker.str_Suit = "Spade  "; break;
        case 1: crd_Poker.str_Suit = "Heart  "; break;
        case 2: crd_Poker.str_Suit = "Clubs  "; break;
        case 3: crd_Poker.str_Suit = "Diamond"; break;
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
                crd_Poker.str_Word  = static_cast<char>((int_Num2 + 1) / 10 + 48);
                crd_Poker.str_Word += static_cast<char>((int_Num2 + 1) % 10 + 48);
            }
            else crd_Poker.str_Word = static_cast<char>(int_Num2 + 1 + 48);
    }

    return;
}
