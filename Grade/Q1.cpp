#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

class Student{
public:
    std::string name;
    std::vector<int> score;
    int average;

    Student();
};

bool score_cmp(int score1, int score2);
void fetchData(int& peopleCount, int& scoreCount, std::vector<Student*>& data);
void releaseData(std::vector<Student*>& data);

int main()
{
    int peopleCount = 0, scoreCount = 0;
    std::vector<Student*> data;

    fetchData(peopleCount, scoreCount, data);

    std::string name;
    bool studentExist = false;

    std::cout<< "Please type a name: ";
    std::cin>> name;

    for(int i = 0; i < data.size(); i++){
        if(data[i]->name == name){
            studentExist = true;

            for(int j = 0; j < scoreCount; j++){
                std::cout<< data[i]->score[j] << ';';
            }

            std::cout<< "\nAvg: " << data[i]->average << '\n';
        }
    }

    if(!studentExist) std::cout<< "No such student\n";

    releaseData(data);

    return 0;
}

Student::Student(): average(0), name(""){

}

bool score_cmp(int score1, int score2){
    return score1 >= score2;
}

void fetchData(int& peopleCount, int& scoreCount, std::vector<Student*>& data){
    std::ifstream inFile;

    inFile.open("grade.txt");

    if(inFile.is_open()){
        std::string temp;

        getline(inFile, temp, ';');
        peopleCount = std::stoi(temp);

        getline(inFile, temp, ';');
        scoreCount = std::stoi(temp);

        getline(inFile, temp, '\n'); // to avoid catching '\n'

        for(int i = 0; i < peopleCount; i++){
            data.push_back(new Student());

            getline(inFile, temp, ';');
            data[i]->name = temp;

            double sum = 0.0;

            for(int j = 0; j < scoreCount; j++){
                getline(inFile, temp, ';');
                data[i]->score.push_back(stoi(temp));

                sum += data[i]->score.back();
            }

            data[i]->average = sum / scoreCount + 0.5; // for rounding

            getline(inFile, temp, '\n'); // to avoid catching '\n'

            std::sort(data[i]->score.begin(), data[i]->score.end(), score_cmp);
        }

        inFile.close();
    }
    else std::cout<< "Fail to load the file\n";
}

void releaseData(std::vector<Student*>& data){
    while(!data.empty()){
        delete data.back();

        data.pop_back();
    }
}
