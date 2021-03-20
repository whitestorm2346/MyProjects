#include <iostream>

class Angle
{
    public: virtual float fn_GetAngle() = 0;
};

class Triangle: public Angle
{
public:
    float flt_InteriorAngle[3];

    float fn_GetAngle()
    {
        return static_cast<float>(180 * (3 - 2)) / 3;
    }

    Triangle()
    {
        for(int i = 0; i < 3; i++)
        {
            this->flt_InteriorAngle[i] = fn_GetAngle();
        }
    }
};

class Square: public Angle
{
public:
    float flt_InteriorAngle[4];

    float fn_GetAngle()
    {
        return static_cast<float>(180 * (4 - 2)) / 4;
    }

    Square()
    {
        for(int i = 0; i < 4; i++)
        {
            this->flt_InteriorAngle[i] = fn_GetAngle();
        }
    }
};

int main()
{
    Square sqr_1;
    Triangle tri_1;

    for(int i = 0; i < 3; i++)
    {
        std::cout<< tri_1.flt_InteriorAngle[i] << ' ';
    }

    std::cout<< '\n';

    for(int i = 0; i < 4; i++)
    {
        std::cout<< sqr_1.flt_InteriorAngle[i] << ' ';
    }

    std::cout<< '\n';

    return 0;
}
