#include "Field.hpp"

Field::Field(int width, int height)
{
    size = {width, height};
    obstacles = new List<Obstacle*>();
    matrix = new char*[height];

    for(int i = 0; i < height; i++)
    {
        matrix[i] = new char[width];

        for(int j = 0; j < width; j++)
        {
            matrix[i][j] = ' ';
        }
    }
}
Field::~Field()
{
    for(int i = 0; i < size.second; i++)
    {
        delete [] matrix[i];
    }

    delete [] matrix;
    delete obstacles;
}

void Field::setSize(int width, int height)
{
    size = {width, height};
}
void Field::addObstacle()
{
    obstacles->insert(new Obstacle(
                        rand() % size.first,
                        rand() % size.second,
                        rand() % (size.first / 10) + 1,
                        rand() % (size.second / 10) + 1));
}
void Field::generate()
{
    /**
        wait to be implemented
    */
}
void Field::print()
{
    for(int i = 0; i < size.second; i++)
    {
        for(int j = 0; j < size.second; j++)
        {
            std::cout<< matrix[i][j];
        }

        std::cout<< '\n';
    }
}
