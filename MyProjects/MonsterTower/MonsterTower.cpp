#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>

#define int_SkillNum 4

struct Monster
{
    int int_LV;
    int int_Number;
    int int_CurrHP;
    int int_HP;
    int int_CurrATK;
    int int_ATK;
    int int_FrezTime = 0;
};

struct Player
{
    int int_LV;
    int int_SkillPoint;
    int int_CurrEXP;
    int int_MaxEXP;
    int int_CurrHP;
    int int_HP;
    int int_CurrSP;
    int int_SP;
    int int_CurrATK;
    int int_ATK;
    int int_BuffTime;

    Player()
    {
        int_LV = 1;
        int_SkillPoint = 0;
        int_CurrEXP = 0;
        int_MaxEXP = 10;
        int_CurrHP = int_HP = 100;
        int_CurrSP = int_SP = 100;
        int_CurrATK = int_ATK = 10;
        int_BuffTime = 0;
    }
};

struct Skill
{
    std::string str_Name;
    bool bl_Usable;
    bool bl_Unlocked;
    int  int_LV;
    int  int_CurrCD = 0;
    int  int_CD;
    int  int_SPCost;
    int  int_Count;
};

//****************************************************

//  Global Object's Declarations

Player  plr_Main;
Skill   skl_Main[int_SkillNum];
bool    bl_Action;

//****************************************************

//  Sub-Function's Declarations

bool  fn_Alive();
bool  fn_CheckEnoughSP(int int_SPCost);

void  fn_Line();
void  fn_InputToNum(char chr_Input, int &int_Num);
void  fn_Display(int int_Num, int int_Stage, int int_Round, Monster mon_Main);
void  fn_Fight(Monster &mon_Main);
void  fn_SklInfoDisplay(int int_Num);
void  fn_UsableSklDisplay(int int_Num, int int_Count);

void  fn_MonLV(int &mon_LV);
void  fn_MonHP(Monster &mon_Main);
void  fn_MonATK(Monster &mon_Main);

void  fn_PlrEXP(Monster &mon_Main);
void  fn_PlrATK();
void  fn_PlrRegainSP();

void  fn_PresetSkill();
void  fn_ResetSklCount();
void  fn_SklMethod(std::string str_Name, Monster &mon_Main);
void  fn_ExeSkill(int int_Count, Monster &mon_Main);
void  fn_CheckUsableSkl(bool &bl_NoUsableSkl, int &int_Count);
void  fn_CheckUnlocked(bool &bl_NoUnlockedSkl);
void  fn_UpgradeSkl();

void  fn_SubtractSklCD();
void  fn_SubtractMonFrezTime(Monster &mon_Main);
void  fn_SubtractPlrBuffTime();
void  fn_UpgradeSklDisplay();
void  fn_ExeUpgradeSkl(int int_Num);

void  fn_Introduce();

//****************************************************

//  Main Function Part

int main()
{
    int int_Stage = 1, int_CountStage;

    srand(time(NULL));

    fn_PresetSkill();
    fn_Introduce();

    Sleep(500);

    while(true)
    {
        int int_Round = 1;
        int int_RandNum = rand() % int_Stage + 1;
        Monster mon_Main[int_RandNum];

        for(int i = 0; i < int_RandNum; i++)
        {
            mon_Main[i].int_Number = i + 1;

            fn_MonLV(mon_Main[i].int_LV);
            fn_MonHP(mon_Main[i]);
            fn_MonATK(mon_Main[i]);

            do
            {
                fn_SubtractPlrBuffTime();
                fn_SubtractSklCD();
                fn_SubtractMonFrezTime(mon_Main[i]);
                fn_PlrRegainSP();

                fn_Display(i + 1, int_Stage, int_Round, mon_Main[i]);
                fn_Fight(mon_Main[i]);

                int_Round++;
            }
            while(fn_Alive() && mon_Main[i].int_CurrHP > 0);

            if(!fn_Alive())
            {
                std::cout<< "[system] You are dead!\n\n";

                fn_Line();

                break;
            }

            if(mon_Main[i].int_CurrHP <= 0)
            {
                std::cout<< "[system] Monster"
                         << mon_Main[i].int_Number
                         << " has been slain!\n";

                fn_PlrEXP(mon_Main[i]);
            }
        }

        int_CountStage = int_Stage;

        if(!fn_Alive()) break;

        int_Stage++;
    }

    fn_Line();

    std::cout<< "\n                   "
             << "Game Over!!\n\n"
             << "                    "
             << "Stage: " << int_CountStage << "\n\n";

    fn_Line();
    fn_Line();

    return 0;
}

//****************************************************

//  Sub-Function's Definitions

bool  fn_Alive()
{
    return plr_Main.int_CurrHP > 0;
}

bool  fn_CheckEnoughSP(int int_SPCost)
{
    bool bl_EnoughSP;

    bl_EnoughSP = (plr_Main.int_CurrSP - int_SPCost) >= 0 ? true : false;

    if(!bl_EnoughSP)
    {
        std::cout<< "\n[system] You don\'t have enough SP!\n\n";

        fn_Line();
    }

    return bl_EnoughSP;
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

void  fn_InputToNum(char chr_Input, int &int_Num)
{
    while(std::cin>> chr_Input)
    {
        if(chr_Input >= 48 && chr_Input <= 57)
        {
            int_Num = chr_Input - '0';

            break;
        }
        else
        {
            std::cout<< "\n[system] Illigal Inputation!"
                     << " Please Input again!\n\n"
                     << "Select an action:";
        }
    }

    return;
}

void  fn_Display(int int_Num, int int_Stage, int int_Round, Monster mon_Main)
{
    std::cout<< '\n';

    fn_Line();

    std::cout<< "                    "
             << "Stage " << int_Stage << '\n';

    fn_Line();

    std::cout<< "                    "
             << "Round " << int_Round << '\n';

    fn_Line();

    std::cout<< "Monster" << int_Num << ":\n    ";
    std::cout<< "Level:" << mon_Main.int_LV << "\n    ";
    std::cout<< "HP:" << mon_Main.int_CurrHP << '/'
             << mon_Main.int_HP << "\n    ";
    std::cout<< "ATK:" << mon_Main.int_CurrATK << '\n';

    std::cout<< "\nPlayer:\n    ";
    std::cout<< "Level:" << plr_Main.int_LV << "\n    ";
    std::cout<< "EXP:" << plr_Main.int_CurrEXP << '/'
             << plr_Main.int_MaxEXP << "\n    ";
    std::cout<< "HP:" << plr_Main.int_CurrHP << '/'
             << plr_Main.int_HP << "\n    ";
    std::cout<< "SP:" << plr_Main.int_CurrSP << '/'
             << plr_Main.int_SP << "\n    ";
    std::cout<< "ATK:" << plr_Main.int_CurrATK << "\n\n";

    return;
}

void  fn_Fight(Monster &mon_Main)
{
    char chr_Input;
    bool bl_NoUnlockedSkl = true;
    bool bl_NoUsableSkl = true;
    int int_PlrChoice;
    int int_MonChoice;
    int int_Count;

    do
    {
        if(mon_Main.int_FrezTime > 0) int_MonChoice = 3;
        else int_MonChoice = (rand() % 3 +1);

        std::cout<< "\n(1) Attack the monster\n"
                 << "(2) Defend\n"
                 << "(3) Skills\n\n"
                 << "Select an action:";

        while(true)
        {
            fn_InputToNum(chr_Input, int_PlrChoice);

            if(int_PlrChoice > 0 && int_PlrChoice <= 3) break;
            else
            {
                std::cout<< "\n[system] Illigal Inputation!"
                         << " Please Input again!\n\n"
                         << "Select an action:";
            }
        }

        std::cout<< '\n';

        fn_Line();

        switch(int_PlrChoice)
        {
            case 1: //Attack
                bl_Action = true;

                switch(int_MonChoice)
                {
                    case 1: //Attack
                        std::cout<< "\n[system] You both attack each other.\n";

                        mon_Main.int_CurrHP -= plr_Main.int_CurrATK;

                        if(mon_Main.int_CurrHP <= 0) break;

                        plr_Main.int_CurrHP -= mon_Main.int_CurrATK + 3;

                        break;

                    case 2: //Defend
                        std::cout<< "\n[system] The monster defended your attack!\n";

                        mon_Main.int_CurrHP -= 1;

                        break;

                    case 3: //Standstill
                        std::cout<< "\n[system] You attacked the monster!\n";

                        mon_Main.int_CurrHP -= plr_Main.int_CurrATK;
                }

                break;

            case 2: //Defend
                bl_Action = true;

                switch(int_MonChoice)
                {
                    case 1: //Attack
                        std::cout<< "\n[system] You defended monster\'s attack!\n";

                        plr_Main.int_CurrHP -= 1;

                        break;

                    case 2: //Defend
                    case 3: //Standstill
                        std::cout<< "\n[system] No one is attacking.\n";
                }

                break;

            case 3: //Skill
                bl_Action = false;

                fn_CheckUnlocked(bl_NoUnlockedSkl);

                if(!bl_NoUnlockedSkl) fn_CheckUsableSkl(bl_NoUsableSkl, int_Count);

                if(!bl_NoUsableSkl) fn_ExeSkill(int_Count, mon_Main);
        }
    }
    while(!bl_Action);

    return;
}

void  fn_SklInfoDisplay(int int_Num)
{
    std::cout<< skl_Main[int_Num].str_Name << ":\n    ";
    std::cout<< "Level:" << skl_Main[int_Num].int_LV << "\n    ";

    if(skl_Main[int_Num].str_Name == "Attack")
    {
        std::cout<< "Damage:" << 15 * skl_Main[int_Num].int_LV << "\n    ";
    }

    std::cout<< "CoolDown:" << skl_Main[int_Num].int_CurrCD
             << '/' << skl_Main[int_Num].int_CD << "\n    ";
    std::cout<< "SP Cost:" << skl_Main[int_Num].int_SPCost << "\n    ";

    if(skl_Main[int_Num].bl_Usable) std::cout<< "> Usable\n";
    else std::cout<< "> Unusable\n";

    return;
}

void  fn_UsableSklDisplay(int int_Num, int int_Count)
{
    if(skl_Main[int_Num].bl_Unlocked)
    {
        std::cout<< '(' << int_Count << ") " << skl_Main[int_Num].str_Name << "\n    ";

        skl_Main[int_Num].int_Count = int_Count;
    }

    return;
}

void  fn_MonLV(int &mon_LV)
{
    int int_RandNum;

    int_RandNum = (rand() % plr_Main.int_LV) + 1;
    mon_LV = int_RandNum;

    return;
}

void  fn_MonHP(Monster &mon_Main)
{
    if(mon_Main.int_LV >= 5) mon_Main.int_HP = mon_Main.int_LV * 10 * (rand() % 5 + 1);
    else mon_Main.int_HP = mon_Main.int_LV * 20;

    mon_Main.int_CurrHP = mon_Main.int_HP;

    return;
}

void  fn_MonATK(Monster &mon_Main)
{
    mon_Main.int_ATK = mon_Main.int_LV * (rand() % 10 +1);
    mon_Main.int_CurrATK = mon_Main.int_ATK;

    return;
}

void  fn_PlrEXP(Monster &mon_Main)
{
    bool bl_Upgraded = false;

    plr_Main.int_CurrEXP += mon_Main.int_LV * 30;

    while(plr_Main.int_CurrEXP >= plr_Main.int_MaxEXP && plr_Main.int_LV < 100)
    {
        bl_Upgraded = true;

        plr_Main.int_LV++;

        std::cout<< "\n[system] Level up!\n";

        plr_Main.int_SkillPoint++;

        std::cout<< "[system] SkillPoint +1\n";

        plr_Main.int_CurrEXP -= plr_Main.int_MaxEXP;
        plr_Main.int_MaxEXP *= 2;

        fn_PlrATK();

    }

    std::cout<< '\n';

    if(bl_Upgraded) fn_UpgradeSkl();

    return;
}

void  fn_PlrATK()
{
    plr_Main.int_ATK += 5 * (rand() % 3 + 1);
    plr_Main.int_CurrATK = plr_Main.int_ATK;

    return;
}

void  fn_PlrRegainSP()
{
    plr_Main.int_CurrSP += 2 * plr_Main.int_LV;

    if(plr_Main.int_CurrSP > plr_Main.int_SP) plr_Main.int_CurrSP = plr_Main.int_SP;

    return;
}

void  fn_PresetSkill()
{
    skl_Main[0].str_Name = "Heal";
    skl_Main[0].int_LV = 1;
    skl_Main[0].int_CD = 10;
    skl_Main[0].int_SPCost = 25;
    skl_Main[0].bl_Usable = false;
    skl_Main[0].bl_Unlocked = false;

    skl_Main[1].str_Name = "Buff";
    skl_Main[1].int_LV = 1;
    skl_Main[1].int_CD = 5;
    skl_Main[1].int_SPCost = 10;
    skl_Main[1].bl_Usable = false;
    skl_Main[1].bl_Unlocked = false;

    skl_Main[2].str_Name = "Attack";
    skl_Main[2].int_LV = 1;
    skl_Main[2].int_CD = 5;
    skl_Main[2].int_SPCost = 15;
    skl_Main[2].bl_Usable = false;
    skl_Main[2].bl_Unlocked = false;

    skl_Main[3].str_Name = "Freeze";
    skl_Main[3].int_LV = 1;
    skl_Main[3].int_CD = 15;
    skl_Main[3].int_SPCost = 35;
    skl_Main[3].bl_Usable = false;
    skl_Main[3].bl_Unlocked = false;

    return;
}

void  fn_ResetSklCount()
{
    for(int i = 0; i < int_SkillNum; i++)
        skl_Main[i].int_Count = 0;

    return;
}

void  fn_SklMethod(std::string str_Name, Monster &mon_Main)
{
    for(int i = 0; i < int_SkillNum; i++)
    {
        if(skl_Main[i].str_Name == str_Name)
        {
            if(str_Name == "Heal")
            {
                if(!fn_CheckEnoughSP(skl_Main[i].int_SPCost)) break;

                plr_Main.int_CurrHP += skl_Main[i].int_LV * 5;

                if(plr_Main.int_CurrHP > plr_Main.int_HP)
                    plr_Main.int_CurrHP = plr_Main.int_HP;

                plr_Main.int_CurrSP -= skl_Main[i].int_SPCost;
                skl_Main[i].int_CurrCD = skl_Main[i].int_CD;
                skl_Main[i].bl_Usable = false;

                std::cout<< "\n[system] You use the skill \"Heal\"!\n";

                fn_Line();
            }
            else if(str_Name == "Buff")
            {
                if(!fn_CheckEnoughSP(skl_Main[i].int_SPCost)) break;

                plr_Main.int_CurrATK += 10 * skl_Main[i].int_LV;
                plr_Main.int_BuffTime = 3;
                plr_Main.int_CurrSP -= skl_Main[i].int_SPCost;
                skl_Main[i].int_CurrCD = skl_Main[i].int_CD;
                skl_Main[i].bl_Usable = false;

                std::cout<< "\n[system] You use the skill \"Buff\"!\n";

                fn_Line();
            }
            else if(str_Name == "Attack")
            {
                if(!fn_CheckEnoughSP(skl_Main[i].int_SPCost)) break;

                mon_Main.int_CurrHP -= 15 * skl_Main[i].int_LV;
                plr_Main.int_CurrSP -= skl_Main[i].int_SPCost;
                skl_Main[i].int_CurrCD = skl_Main[i].int_CD;
                skl_Main[i].bl_Usable = false;

                std::cout<< "\n[system] You use the skill \"Attack\"!\n";

                if(mon_Main.int_CurrHP <= 0) bl_Action = true;
            }
            else if(str_Name == "Freeze")
            {
                if(!fn_CheckEnoughSP(skl_Main[i].int_SPCost)) break;

                mon_Main.int_FrezTime = 3;
                plr_Main.int_CurrSP -= skl_Main[i].int_SPCost;
                skl_Main[i].int_CurrCD = skl_Main[i].int_CD;
                skl_Main[i].bl_Usable = false;

                std::cout<< "\n[system] You use the skill \"Freeze\"!\n";

                fn_Line();
            }
        }
    }

    fn_ResetSklCount();

    return;
}

void  fn_ExeSkill(int int_Count, Monster &mon_Main)
{
    char chr_Input;
    int int_OptChoice;

    std::cout<< "\nSelect an option:";

    while(true)
    {
        fn_InputToNum(chr_Input, int_OptChoice);

        if(int_OptChoice > 0 && int_OptChoice <= int_Count) break;
        else
        {
            std::cout<< "\n[system] Illigal Inputation!"
                     << " Please Input again!\n\n"
                     << "Select an option:";
        }
    }

    std::cout<< '\n';

    fn_Line();

    for(int i = 0; i < int_SkillNum; i++)
    {
        if(skl_Main[i].int_Count == int_OptChoice)
        {
            fn_SklMethod(skl_Main[i].str_Name, mon_Main);
        }
    }

    return;
}

void  fn_CheckUsableSkl(bool &bl_NoUsableSkl, int &int_Count)
{
    bl_NoUsableSkl = true;
    int_Count = 1;

    for(int i = 0; i < int_SkillNum; i++)
    {
        if(skl_Main[i].bl_Usable)
        {
            fn_UsableSklDisplay(i, int_Count);
            bl_NoUsableSkl = false;
            int_Count++;
        }
    }

    if(bl_NoUsableSkl) std::cout<< "\n[system] No usable skills!\n";
    else std::cout<< "\n    " << '(' << int_Count << ") Go back to action selection\n";

    return;
}

void  fn_CheckUnlocked(bool &bl_NoUnlockedSkl)
{
    bl_NoUnlockedSkl = true;

    for(int i = 0; i < int_SkillNum; i++)
    {
        if(skl_Main[i].bl_Unlocked)
        {
            std::cout<< '\n';

            fn_SklInfoDisplay(i);
            bl_NoUnlockedSkl = false;
        }
    }

    if(bl_NoUnlockedSkl)
    {
        std::cout<< "\n[system] No unlocked skills!\n\n";

        fn_Line();
    }
    else
    {
        std::cout<< '\n';

        fn_Line();

        std::cout<< "\nUsable Skills:\n    ";
    }

    return;
}

void  fn_UpgradeSkl()
{
    char chr_Input;
    int int_OptChoice;

    while(plr_Main.int_SkillPoint > 0)
    {
        fn_Line();

        std::cout<< "\nSkill Point:" << plr_Main.int_SkillPoint << "\n\n";

        fn_UpgradeSklDisplay();

        std::cout<< "\nSelect an option:";

        while(true)
        {
            fn_InputToNum(chr_Input, int_OptChoice);

            if(int_OptChoice > 0 && int_OptChoice <= int_SkillNum) break;
            else
            {
                std::cout<< "\n[system] Illigal Inputation!"
                         << " Please Input again!\n\n"
                         << "Select an option:";
            }
        }

        std::cout<< '\n';

        fn_Line();
        fn_ExeUpgradeSkl(int_OptChoice - 1);
    }

    return;
}

void  fn_SubtractSklCD()
{
    for(int i = 0; i < int_SkillNum; i++)
    {
        if(skl_Main[i].bl_Unlocked == true && skl_Main[i].int_CurrCD > 0)
        {
            skl_Main[i].int_CurrCD--;

            if(skl_Main[i].int_CurrCD == 0) skl_Main[i].bl_Usable = true;
        }
    }

    return;
}

void  fn_SubtractMonFrezTime(Monster &mon_Main)
{
    if(mon_Main.int_FrezTime > 0) mon_Main.int_FrezTime--;

    return;
}

void  fn_SubtractPlrBuffTime()
{
    if(plr_Main.int_BuffTime > 0) plr_Main.int_BuffTime--;

    return;
}

void  fn_UpgradeSklDisplay()
{
    for(int i = 0; i < int_SkillNum; i++)
    {
        if(skl_Main[i].bl_Unlocked == false)
        {
            std::cout<< '(' << i + 1 << ") Unlock "
                     << skl_Main[i].str_Name << '\n';
        }
        else
        {
            std::cout<< '(' << i + 1 << ") Upgrade "
                     << skl_Main[i].str_Name << '\n';
        }
    }

    return;
}

void  fn_ExeUpgradeSkl(int int_Num)
{
    if(skl_Main[int_Num].bl_Unlocked)
    {
        skl_Main[int_Num].int_LV++;

        std::cout<< "\n[system] " << skl_Main[int_Num].str_Name
                 << " has upgraded to level "
                 << skl_Main[int_Num].int_LV << "!\n";
    }
    else
    {
        skl_Main[int_Num].bl_Unlocked = true;
        skl_Main[int_Num].bl_Usable = true;

        std::cout<< "\n[system] " << skl_Main[int_Num].str_Name
                 << " has unlocked!\n";
    }

    if(plr_Main.int_SkillPoint != 1) std::cout<< '\n';

    plr_Main.int_SkillPoint--;

    return;
}

void  fn_Introduce()
{
    fn_Line();

    std::cout<< "\n                 "
             << "歡迎來到無限怪塔\n\n";

    Sleep(2000);

    std::cout<< "遊戲說明：\n\n    "
             << "玩家要擊殺每一層的怪物，不斷往上征服\n    "
             << "玩家死後遊戲結束！\n\n";

    Sleep(3000);

    std::cout<< "規則說明：\n\n    "
             << "玩家每回合都有三個選擇\n\n    "
             << "Attack 攻擊怪物\n    "
             << "Defend 防禦怪物的攻擊\n    "
             << "Skills 技能(必須靠玩家升級以解鎖)\n\n    ";

    Sleep(3000);

    std::cout<< "怪物每回合也有三個狀態\n\n    "
             << "Attack 攻擊玩家\n    "
             << "Defend 防禦玩家的攻擊\n    "
             << "Staystill 停滯(發呆)\n\n    ";

    Sleep(3000);

    std::cout<< "當玩家與怪物同時攻擊彼此時\n    "
             << "怪物會受到玩家攻擊力的傷害\n    "
             << "玩家則會受到怪物攻擊力額外+10點的傷害\n    "
             << "因此同時攻擊時，對玩家相對不利\n\n    ";

    Sleep(3000);

    std::cout<< "不過慶幸的是\n    "
             << "雙方同時攻擊時是玩家先手\n    "
             << "因此當怪物血量已經到達玩家的斬殺線時\n    "
             << "就果斷攻擊怪物吧！\n\n    ";

    Sleep(3000);

    std::cout<< "當其中一方防禦另一方的攻擊時\n    "
             << "防禦的一方只會受到1點的傷害\n    "
             << "因此遇到高攻擊力的怪物時\n    "
             << "要慎用防禦來維持血線\n\n    ";

    Sleep(3000);

    std::cout<< "當沒有人攻擊時\n    "
             << "則安然度過這一回合\n\n";

    Sleep(2000);

    std::cout<< "\n                   "
             << "說明結束！\n\n";

    fn_Line();

    Sleep(3000);

    std::cout<< "\n                  "
             << "Game Start!\n";

    return;
}

