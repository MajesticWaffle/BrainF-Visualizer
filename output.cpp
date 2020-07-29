//
// Created by tskup on 28-Jul-20.
//

#include "output.h"
#include <windows.h>
#include <iostream>
#include <list>
#include <stdlib.h>

HANDLE hConsole;
COORD pos;

static short outputIndex = 0;

void output::InitConsole(){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    pos = {0, 0};
    SetConsoleCursorPosition(hConsole, pos);
    system("cls");

}
void output::DisplayCells(int cells[], int cellCount){
    pos = {0,0};
    SetConsoleCursorPosition(hConsole, pos);
    for(int i = 0; i < cellCount; i++){
        std::cout << "[" << cells[i] << "] ";
    }
}

void output::DisplayCursor(int pointerLocation){
    short xcoord = (1 + (pointerLocation * 4));
    pos = {1, 1};
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << "                                                                                                                        ";

    pos = {xcoord, 1};
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << '^';
}

void output::Debug(char code[], int interpreterPos, int cursorPos, int codeSize){
    pos = {0, 25};
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << "Output: ";

    pos = {0, 27};
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << "                                                                                                                        ";

    std::string s_code = code;

    int endingPos = 0;

    if(interpreterPos + 90 > codeSize){
        endingPos = codeSize;
    }else{
        endingPos = interpreterPos + 90;
    }

    if(interpreterPos >= 10){
        pos = {0, 27};
        SetConsoleCursorPosition(hConsole, pos);
        std::cout << s_code.substr(interpreterPos - 10, endingPos);
    }else{
        pos = {(short)(10 - interpreterPos), 27};
        SetConsoleCursorPosition(hConsole, pos);
        std::cout << s_code.substr(interpreterPos, endingPos);
    }

    pos = {10, 28};
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << '^';

    pos = {0, 29};
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << "reading instruction: " << interpreterPos;

    pos = {30, 29};
    SetConsoleCursorPosition(hConsole, pos);
}

void output::DisplayChar(char c){
    pos = {outputIndex, 26};
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << c;
    outputIndex++;
}

