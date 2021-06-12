#ifndef BIGNUM_H_INCLUDED
#define BIGNUM_H_INCLUDED

class BigNum
{
public:
    std::string str_Val;

    BigNum(std::string str_Input)
    {
        str_Val = str_Input;
    }

    std::string operator + (std::string str_Add)
    {
        std::string str_Result = "";

        return str_Result;
    }
};

#endif // BIGNUM_H_INCLUDED
