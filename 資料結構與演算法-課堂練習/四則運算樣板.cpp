#include <iostream>

template<typename Type>
    class Calculate
    {
    private:
        Type type_Num1;
        Type type_Num2;

    public:
        Calculate(Type type_Num1, Type type_Num2)
        {
            this->type_Num1 = type_Num1;
            this->type_Num2 = type_Num2;
        }

        Type fn_GetRes(char chr_Operator)
        {
            switch(chr_Operator)
            {
                case '+': return this->type_Num1 + this->type_Num2;
                case '-': return this->type_Num1 - this->type_Num2;
                case '*': return this->type_Num1 * this->type_Num2;
                case '/': return this->type_Num1 / this->type_Num2;
            }
        }
    };

int main()
{
    Calculate<int> obj_int(1, 2);
    Calculate<float> obj_flt(1.0, 2.0);
    Calculate<double> obj_db(1.0, 2.0);

    std::cout<< obj_int.fn_GetRes('+') << '\n';
    std::cout<< obj_int.fn_GetRes('-') << '\n';
    std::cout<< obj_int.fn_GetRes('*') << '\n';
    std::cout<< obj_int.fn_GetRes('/') << '\n';

    std::cout<< obj_flt.fn_GetRes('+') << '\n';
    std::cout<< obj_flt.fn_GetRes('-') << '\n';
    std::cout<< obj_flt.fn_GetRes('*') << '\n';
    std::cout<< obj_flt.fn_GetRes('/') << '\n';

    std::cout<< obj_db.fn_GetRes('+') << '\n';
    std::cout<< obj_db.fn_GetRes('-') << '\n';
    std::cout<< obj_db.fn_GetRes('*') << '\n';
    std::cout<< obj_db.fn_GetRes('/') << '\n';

    return 0;
}
