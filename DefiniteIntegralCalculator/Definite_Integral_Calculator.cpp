#include <iostream>     //Definite Integral Calculator
#include <algorithm>
#include <cmath>

int   fn_GCD(int int_Num1, int int_Num2);   // �����
int   fn_LCM(int int_Num1, int int_Num2);   // ��С������

struct Coefficient  // �S���Y��
{
    int int_Numer = 0;      //����
    int int_Denom = 1;    //��ĸ

    void operator-= (Coefficient &coef_Num) //���x�˽Y�����}��ָ���p̖�\����
    {
        int int_TempNumer = coef_Num.int_Numer;
        int int_TempDenom = coef_Num.int_Denom;

        int int_LCM = fn_LCM(this->int_Denom, coef_Num.int_Denom);

        this->int_Numer *= int_LCM / this->int_Denom;         // ͨ���^��
        this->int_Denom = int_LCM;
        coef_Num.int_Numer *= int_LCM / coef_Num.int_Denom;
        coef_Num.int_Denom = int_LCM;

        this->int_Numer -= coef_Num.int_Numer; // �֔����p

        int int_GCD = fn_GCD(this->int_Numer, this->int_Denom);

        this->int_Numer /= int_GCD;     // �s���^��
        this->int_Denom /= int_GCD;

        coef_Num.int_Numer = int_TempNumer;
        coef_Num.int_Denom = int_TempDenom;
    }
};

int int_Deg;    // �˶��ʽ֮��ߴΔ�
Coefficient coef_MaxRes, coef_MinRes; // �Ϻ���ֵ, �º���ֵ

int   fn_Pow(int int_Num, int int_Times);
void  fn_Preset(Coefficient* coefptr_Max, Coefficient* coefptr_Min, Coefficient* coefptr_Arr);  // ��ֵݔ��
void  fn_Antiderivative(Coefficient* coefptr_Arr);  // �󷴌�����
void  fn_Calculate(Coefficient* coefptr_Num, Coefficient* coefptr_Arr, Coefficient* coefptr_Save); // ����ֵӋ��

int main()
{
    std::cout<< "deg f(x) = ";
    std::cin>> int_Deg;

    Coefficient* coefptr_Max = new Coefficient;     // ��ֵ
    Coefficient* coefptr_Min = new Coefficient;     // ��ֵ
    Coefficient* coefptr_Arr = new Coefficient[int_Deg + 2];    // ���S��

    fn_Preset(coefptr_Max, coefptr_Min, coefptr_Arr);
    fn_Antiderivative(coefptr_Arr);
    fn_Calculate(coefptr_Max, coefptr_Arr, &coef_MaxRes);
    fn_Calculate(coefptr_Min, coefptr_Arr, &coef_MinRes);

    delete coefptr_Max;
    delete coefptr_Min;
    delete [] coefptr_Arr;

    coef_MaxRes -= coef_MinRes; // �Ϻ���ֵ - �º���ֵ

    if(coef_MaxRes.int_Denom == 1) std::cout<< "Ans: " << coef_MaxRes.int_Numer;
    else std::cout<< "Ans: " << coef_MaxRes.int_Numer << '/' << coef_MaxRes.int_Denom;

    return 0;
}

int   fn_GCD(int int_Num1, int int_Num2)
{
    int_Num1 = std::abs(int_Num1);
    int_Num2 = std::abs(int_Num2);

    while(int_Num1 % int_Num2)
    {
        int_Num1 %= int_Num2;
        int_Num1 ^= int_Num2 ^= int_Num1 ^= int_Num2;
    }

    return int_Num2;
}

int   fn_LCM(int int_Num1, int int_Num2)
{
    int_Num1 = std::abs(int_Num1);
    int_Num2 = std::abs(int_Num2);

    return int_Num1 * int_Num2 / fn_GCD(int_Num1, int_Num2);
}

int   fn_Pow(int int_Num, int int_Times)
{
    int int_Result = int_Num;

    while(--int_Times) int_Result *= int_Num;

    return int_Result;
}

void  fn_Preset(Coefficient* coefptr_Max, Coefficient* coefptr_Min, Coefficient* coefptr_Arr)
{
    std::cout<< "\n\n�e����ֵ(����)��";
    std::cin>> coefptr_Max->int_Numer;
    std::cout<< "�e����ֵ(��ĸ)��";
    std::cin>> coefptr_Max->int_Denom;

    std::cout<< "\n�e������(����)��";
    std::cin>> coefptr_Min->int_Numer;
    std::cout<< "�e������(��ĸ)��";
    std::cin>> coefptr_Min->int_Denom;

    std::cout<< "\n\n";

    for(int i = int_Deg; i >= 0; i--)
    {
        std::cout<< "x " << i << "�η���ϵ��(����)��";
        std::cin>> (coefptr_Arr + i)->int_Numer;

        std::cout<< "x " << i << "�η���ϵ��(��ĸ)��";
        std::cin>> (coefptr_Arr + i)->int_Denom;

        std::cout<< '\n';
    }

    return;
}

void  fn_Antiderivative(Coefficient* coefptr_Arr)
{
    for(int i = int_Deg++; i >= 0; i--)
    {
        (coefptr_Arr + i)->int_Denom *= i + 1;

        if((coefptr_Arr + i)->int_Denom < 0)
        {
            (coefptr_Arr + i)->int_Denom *= -1;
            (coefptr_Arr + i)->int_Numer *= -1;
        }

        int int_GCD = fn_GCD((coefptr_Arr + i)->int_Numer, (coefptr_Arr + i)->int_Denom);

        (coefptr_Arr + i)->int_Numer /= int_GCD;
        (coefptr_Arr + i)->int_Denom /= int_GCD;

        std::swap(*(coefptr_Arr + i), *(coefptr_Arr + i + 1));
    }

    return;
}

void  fn_Calculate(Coefficient* coefptr_Num, Coefficient* coefptr_Arr, Coefficient* coefptr_Save)
{
    int int_TempNumer, int_TempDenom;
    int int_GCD, int_LCM;

    for(int i = int_Deg; i >= 1; i--)
    {
        if((coefptr_Arr + i)->int_Denom < 0)
        {
            (coefptr_Arr + i)->int_Denom *= -1;
            (coefptr_Arr + i)->int_Numer *= -1;
        }

        int_TempNumer = (coefptr_Arr + i)->int_Numer;
        int_TempDenom = (coefptr_Arr + i)->int_Denom;

        (coefptr_Arr + i)->int_Numer *= fn_Pow(coefptr_Num->int_Numer, i);
        (coefptr_Arr + i)->int_Denom *= fn_Pow(coefptr_Num->int_Denom, i);

        int_GCD = fn_GCD((coefptr_Arr + i)->int_Numer, (coefptr_Arr + i)->int_Denom);

        (coefptr_Arr + i)->int_Numer /= int_GCD;
        (coefptr_Arr + i)->int_Denom /= int_GCD;

        int_LCM = fn_LCM(coefptr_Save->int_Denom, (coefptr_Arr + i)->int_Denom);

        coefptr_Save->int_Numer *= int_LCM / coefptr_Save->int_Denom;
        coefptr_Save->int_Denom  = int_LCM;
        (coefptr_Arr + i)->int_Numer *= int_LCM / (coefptr_Arr + i)->int_Denom;
        (coefptr_Arr + i)->int_Denom  = int_LCM;

        coefptr_Save->int_Numer += (coefptr_Arr + i)->int_Numer;

        (coefptr_Arr + i)->int_Numer = int_TempNumer;
        (coefptr_Arr + i)->int_Denom = int_TempDenom;

        int_GCD = fn_GCD(coefptr_Save->int_Numer, coefptr_Save->int_Denom);

        coefptr_Save->int_Numer /= int_GCD;
        coefptr_Save->int_Denom /= int_GCD;
    }

    return;
}
