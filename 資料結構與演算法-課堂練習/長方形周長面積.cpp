#include <iostream>
#include <cmath>

struct Rectangle
{
public:
    int int_Area;
    int int_Perimeter;
    int int_Length;
    int int_Width;

    Rectangle(int int_X1, int int_Y1, int int_X2, int int_Y2)
    {
        this->int_Length = std::abs(int_X1 - int_X2);
        this->int_Width  = std::abs(int_Y1 - int_Y2);

        if(this->int_Length < this->int_Width)
        {
            int int_Temp = this->int_Length;

            this->int_Length = this->int_Width;
            this->int_Width  = int_Temp;
        }

        this->int_Area = this->int_Length * this->int_Width;
        this->int_Perimeter = 2 * (this->int_Length + this->int_Width);
    }
};

int main()
{
    int int_XY[4];

    for(int i = 0; i < 4; i++)
    {
        std::cin>> int_XY[i];
    }

    Rectangle rec_1(int_XY[0], int_XY[1], int_XY[2], int_XY[3]);

    std::cout<< rec_1.int_Area << ' ' << rec_1.int_Perimeter << '\n';

    return 0;
}
