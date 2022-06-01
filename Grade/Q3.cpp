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
void showStudentStatus(std::ofstream& outFile, std::vector<Student*>& data);
void showSortedAverage(std::ofstream& outFile, std::vector<Student*>& data);
void printOptions(std::ofstream& outFile);

int main()
{
    int peopleCount = 0, scoreCount = 0;
    std::vector<Student*> data;
    std::ofstream outFile;

    fetchData(peopleCount, scoreCount, data);

    outFile.open("FinalGrade.txt", std::ios::out | std::ios::trunc);

    if(outFile.is_open()){
        int choise;
        bool shutDown = false;

        while(!shutDown){
            printOptions(outFile);

            std::cin>> choise;
            std::cout<< '\n';
            outFile<< choise << "\n\n";

            switch(choise){
                case 1: showStudentStatus(outFile, data); break;
                case 2: showSortedAverage(outFile, data); break;
                case 3: shutDown = !shutDown; break;
            }

            std::cout<< "\n\n";
            outFile<< "\n\n";
        }

        outFile.close();

        std::cout<< "The above avg, grades are shown in the FinalGrade.txt file. ";
        std::cout<< "The program is terminated.\n";
    }
    else std::cout<< "Fail to load the file\n";

    releaseData(data);

    return 0;
}

Student::Student(){
    average = 0;
    name = "";
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

void showStudentStatus(std::ofstream& outFile, std::vector<Student*>& data){
    std::string name;
    bool isExist = false;

    std::cout<< "Please type a name: ";
    outFile<< "Please type a name: ";

    std::cin>> name;
    std::cout<< '\n';
    outFile<< name << "\n\n";

    for(unsigned int i = 0; i < data.size(); i++){
        if(data[i]->name == name){
            isExist = true;

            for(unsigned int j = 0; j < data[i]->score.size(); j++){
                std::cout<< data[i]->score[j] << ';';
                outFile<< data[i]->score[j] << ';';
            }

            std::cout<< "\nAvg: " << data[i]->average << '\n';
            outFile<< "\nAvg: " << data[i]->average << '\n';
        }
    }

    if(!isExist){
        std::cout<< "No such student\n";
        outFile<< "No such student\n";
    }
}

void showSortedAverage(std::ofstream& outFile, std::vector<Student*>& data){
    for(unsigned int i = 0; i < data.size(); i++){
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
}

void printOptions(std::ofstream& outFile){
    std::cout<< "1. Show a student¡¦s grades from the highest to the lowest and the associated avg\n";
    outFile<< "1. Show a student¡¦s grades from the highest to the lowest and the associated avg\n";

    std::cout<< "2. Show the avg. for each student from the highest to the lowest\n";
    outFile<< "2. Show the avg. for each student from the highest to the lowest\n";

    std::cout<< "3. Exit and output a final report\n";
    outFile<< "3. Exit and output a final report\n";

    std::cout<< "Choose an option (1-3): ";
    outFile<< "Choose an option (1-3): ";
}
