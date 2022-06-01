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

bool student_cmp(Student* student1, Student* student2);
bool score_cmp(int score1, int score2);
void fetchData(int& peopleCount, int& scoreCount, std::vector<Student*>& data);
void releaseData(std::vector<Student*>& data);

int main()
{
    int peopleCount = 0, scoreCount = 0;
    std::vector<Student*> data;
    std::ofstream outFile;

    fetchData(peopleCount, scoreCount, data);

    outFile.open("FinalGrade.txt", std::ios::out | std::ios::trunc);

    if(outFile.is_open()){
        for(int i = 0; i < peopleCount; i++){
            std::cout<< data[i]->name << "'s avg: " << data[i]->average;
            outFile<< data[i]->name << "'s avg: " << data[i]->average;

            if(data[i]->average >= 60){
                std::cout<< " (pass)\n";
                outFile<< " (pass)\n";
            }
            else{
                std::cout<< " (fail)\n";
                outFile<< " (fail)\n";
            }
        }

        outFile.close();
    }
    else std::cout<< "Fail to load the file\n";

    releaseData(data);

    return 0;
}

Student::Student(): average(0), name(""){

}

bool student_cmp(Student* student1, Student* student2){
    return student1->average >= student2->average;
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

        std::sort(data.begin(), data.end(), student_cmp);

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
