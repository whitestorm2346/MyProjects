#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

const int ctint_N = 23;

struct Point
{
    int int_X;
    int int_Y;

    void fn_Set(int int_X, int int_Y)
    {
        this->int_X = int_X;
        this->int_Y = int_Y;
    }
};

HANDLE hdl_In, hdl_Out;     // I/O 控制器
Point  pnt_Body[ctint_N * (ctint_N * 2 + 4)];
Point  pnt_Cookie, pnt_Vector = {-2, 0};    //體塊, 食物, 移動向量
char   chrarr_Room[ctint_N][ctint_N * 2 + 4];   //房間
int    int_DelayTime = 100;     //延遲時間
int    int_X1 = 2, int_Y1 = 1;
int    int_X2 = (ctint_N-1) * 2, int_Y2 = ctint_N-1;  //房間邊界
int    int_Len = 2;  //身長
bool   bl_Exit = false;    //是否持續遊戲

void  fn_GoToXY(int int_X, int int_Y);
void  fn_Draw(int int_X, int int_Y, char* chr_S);
void  fn_PutCookie();
void  fn_Init();
void  fn_KeyControl();
void  fn_MoveSnack();

void fn_DrawList(char* chr_A, char* chr_B, char* chr_C, int int_W, int h=1)
{
    static char* stchr_P = chrarr_Room[0];

    for(int i; h--; *stchr_P++ = *chr_C, *stchr_P++ = chr_C[1], *stchr_P++ = 0, stchr_P++)
    {
        for(*stchr_P++ = '\n', *stchr_P++ = *chr_A,
            *stchr_P++ = chr_A[1], *stchr_P++ = chr_A[2],
            i = int_W-2; i--;)
        {
            *stchr_P++ = *chr_B, *stchr_P++ = chr_B[1];
        }
    }

    return;
}

int main()
{
    fn_Init();
    fn_Draw(10, 10, "Press \"Enter\" To Start Game");
    getch();
    fn_Draw(10, 10, "                           ");

    while(!bl_Exit)
    {
        Sleep(int_DelayTime);

        if(kbhit())
        {
            fn_KeyControl();
        }

        fn_Draw(pnt_Cookie.int_X, pnt_Cookie.int_Y, "◎");
        fn_MoveSnack();
        Sleep(int_DelayTime);

        if(kbhit())
        {
            fn_KeyControl();
        }

        fn_GoToXY(10,24);

        printf("cookie: (%2d,%2d)  head: (%2d,%2d)",
            pnt_Cookie.int_X, pnt_Cookie.int_Y, pnt_Body[0].int_X, pnt_Body[0].int_Y);
    }

    return 0;
}

void fn_GoToXY(int int_X, int int_Y)
{
    static COORD stcor_C;

    stcor_C.X = int_X;
	stcor_C.Y = int_Y;

    SetConsoleCursorPosition(hdl_Out, stcor_C);

    return;
}

void fn_Draw(int int_X, int int_Y, char* chr_S)
{
    fn_GoToXY(int_X, int_Y);

    std::cout<<chr_S;

    return;
}

void fn_PutCookie()
{
    pnt_Cookie.int_X = 3 + rand()%(ctint_N-2) * 2;
    pnt_Cookie.int_Y = 2 + rand()%(ctint_N-3);

    return;
}

void fn_Init()
{
    srand(time(0));

    hdl_Out = GetStdHandle(STD_OUTPUT_HANDLE);
    hdl_In  = GetStdHandle(STD_INPUT_HANDLE);

    HANDLE hdl_Err = INVALID_HANDLE_VALUE;

    if (hdl_In == hdl_Err || hdl_Out == hdl_Err)
    {
        std::cout<<"handle failed";

        getch();
        exit(1);
    }

    fn_DrawList(" ┌", "─", "┐", ctint_N);
    fn_DrawList(" │", "  ", "│", ctint_N, ctint_N-2);
    fn_DrawList(" └", "─", "┘", ctint_N);

    fn_GoToXY(0, 0);

    for(int i=0; i<ctint_N; i++)
    {
        std::cout<<chrarr_Room[i];
    }

    fn_PutCookie();

    pnt_Body[0].fn_Set((int_X2 - int_X1)/2, (int_Y2 - int_Y1)/2);
    pnt_Body[1].fn_Set(pnt_Body[0].int_X + 1, pnt_Body[0].int_Y);

    return;
}

void fn_KeyControl()
{
    static DWORD stdw_Count;
    static INPUT_RECORD stir_IR;

    ReadConsoleInput(hdl_In, &stir_IR, 1, &stdw_Count);

    if(!stir_IR.Event.KeyEvent.bKeyDown)
    {
        return;
    }

    switch(stir_IR.Event.KeyEvent.wVirtualKeyCode)
    {
        case VK_UP:
            if(pnt_Vector.int_Y != 1)
            {
                pnt_Vector.fn_Set(0, -1);
            }

            break;

        case VK_DOWN:
            if(pnt_Vector.int_Y != -1)
            {
                pnt_Vector.fn_Set(0, 1);
            }

            break;

        case VK_LEFT:
            if(pnt_Vector.int_X != 2)
            {
                pnt_Vector.fn_Set(-2, 0);
            }

            break;

        case VK_RIGHT:
            if(pnt_Vector.int_X != -2)
            {
                pnt_Vector.fn_Set(2, 0);
            }

            break;

        case VK_ESCAPE:
            bl_Exit = true;

            break;
    }

    return;
}

void fn_MoveSnack()
{
    int i;
    int& int_X = pnt_Body[0].int_X;
    int& int_Y = pnt_Body[0].int_Y;

    for(i=1; i<int_Len; i++)                  //檢查自身碰撞
    {
        if(pnt_Body[0].int_X == pnt_Body[i].int_X &&
           pnt_Body[0].int_Y == pnt_Body[i].int_Y )
        {
            break;
        }
    }

    if(i != int_Len || int_X <= int_X1 || int_X > int_X2 ||
       int_Y <= int_Y1 || int_Y > int_Y2)
    {
        fn_Draw(14, 10, "G a m e    O v e r");
        getch();
        bl_Exit = true;

        return;
    }

    if(int_X == pnt_Cookie.int_X && int_Y == pnt_Cookie.int_Y)   //吃到食物
    {
        int_DelayTime -= 2;
        int_Len++;
/*
        if(int_Len > ctint_N * (ctint_N * 2 + 4))     //限制長度
        {
            fn_Draw(16, 10, "Y o u    W i n");
            getch();
            bl_Exit = true;

            return;
        }
*/
        fn_PutCookie();
    }
    else
    {
        fn_Draw(pnt_Body[int_Len-1].int_X, pnt_Body[int_Len-1].int_Y, "  ");
    }

    for(i = int_Len-1; i>0; --i)
    {
        pnt_Body[i] = pnt_Body[i-1];
    }

    int_X += pnt_Vector.int_X;
    int_Y += pnt_Vector.int_Y;

    for(i=0; i<int_Len; ++i)
    {
        fn_Draw(pnt_Body[i].int_X, pnt_Body[i].int_Y, "█");
    }

    return;
}
