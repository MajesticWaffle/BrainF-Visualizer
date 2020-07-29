#include <iostream>
#include "output.h"
#include <cstdlib>
#include <list>
#include <windows.h>
#include <fstream>
#include <algorithm>

using namespace std;

void OutputChar(int charIndex);

int LoopExitLocation(int startingIndex, char array[], int size);

int LoopStartLocation(int startingIndex, char array[]);

int inputChar();

void DisplayHelp();

int ExecuteBFCode(char memblock[], int count, int location, int micro, int i);

bool my_predicate(char c);

int main(int argc, char *argv[]) { //File location, Delay (MS), Cell Count, Starting Cell
int cellCount = 8;
int pointerLocation = 0;
int delayMicro = 50;
std::string filePath;

if(argc == 1){
    DisplayHelp();
    return 0;
}

if(argc >= 2){
    filePath = argv[1];
}
if(argc >= 3){
    delayMicro = atoi(argv[2]);
}
if(argc >= 4){
    cellCount = atoi(argv[3]);
}
if(argc >= 5){
    pointerLocation = atoi(argv[4]);
}

string s;
string line;
ifstream file (filePath);

if(!file.is_open()){
    cout << "Failed to open file: " << filePath;
    return -1;
}

while(getline(file, line)){
    s = s + line;
}
file.close();

s.erase(std::remove_if(s.begin(), s.end(), my_predicate), s.end());

int n = s.length();
char char_array[n+1];
strcpy(char_array, s.c_str());

ExecuteBFCode(char_array, cellCount, pointerLocation, delayMicro, n);

system("pause");
system("cls");
}

bool my_predicate(char c){
    return !(c == '>' || c == '<' || c == '+' || c == '-' || c == '[' || c == ']' || c == '.' || c == ',');
}

void DisplayHelp() {
    std::cout << "bfv.exe {File Path} [Delay] [Cell Count] [Starting Cell]" << "\n" << "{} = Required" << "\n" << "[] = Optional";
}

int ExecuteBFCode(char code[], int cellCount, int pointerLocation, int Delay, int size){
    int cells[cellCount];
    int interpreterLocation = 0; //The current char being interpreted by the compiler

    for (int i = 0; i < cellCount; i++) {
        cells[i] = 0;
    }

    output::InitConsole();
    //Update Display
    output::DisplayCells(cells, cellCount);
    output::DisplayCursor(pointerLocation);

    while (interpreterLocation < size) {
        //Interpret Instruction
        switch (code[interpreterLocation]) {
            case '>':
                pointerLocation++;
                interpreterLocation++;
                break;
            case '<':
                pointerLocation--;
                interpreterLocation++;
                break;
            case '+':
                cells[pointerLocation]++;
                interpreterLocation++;
                break;
            case '-':
                cells[pointerLocation]--;
                interpreterLocation++;
                break;
            case '.':
                OutputChar(cells[pointerLocation]);
                interpreterLocation++;
                break;
            case ',':
                cells[pointerLocation] = inputChar();
                interpreterLocation++;
                break;
            case '[':
                //If the cell is zero
                if (cells[pointerLocation] == 0) {
                    interpreterLocation = LoopExitLocation(interpreterLocation, code, size);
                }
                interpreterLocation++;
                break;

            case ']':
                interpreterLocation = LoopStartLocation(interpreterLocation, code);
                break;
        }


        //Update Display
        Sleep(Delay);

        output::DisplayCells(cells, cellCount);
        output::DisplayCursor(pointerLocation);
        output::Debug(code, interpreterLocation, pointerLocation, size);
        if (pointerLocation < 0) {
            return -1;
        }

    }
    return 0;
}



int LoopExitLocation(int startingIndex, char array[], int size) {
    bool ignoreNext = false; //Set if enters a new loop
    for (int i = startingIndex + 1; i <= size; i++) {
        if (array[i] == '[')
            ignoreNext = true;
        if (array[i] == ']')
            if (ignoreNext) {
                ignoreNext = false;
            } else {
                return i;
            }
    }

    //Could not find matching index
    return -1;
}

int LoopStartLocation(int startingIndex, char array[]) {
    bool ignoreNext = false; //Set if encounters a nested loop from behind
    for (int i = startingIndex - 1; i >= 0; i--) {
        if (array[i] == ']')
            ignoreNext = true;
        if (array[i] == '[')
            if (ignoreNext) {
                ignoreNext = false;
            } else {
                return i;
            }

    }

    //Could not find matching index
    return -1;
}

void OutputChar(int charIndex) {
    output::DisplayChar((char)charIndex);
}

int inputChar() {
    char x;
    std::cin >> x;
    return (int) x;
}