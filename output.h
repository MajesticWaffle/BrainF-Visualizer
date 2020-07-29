//
// Created by tskup on 28-Jul-20.
//

#ifndef ZPLUSPLUS_OUTPUT_H
#define ZPLUSPLUS_OUTPUT_H


#include <list>

class output {
public:
    static void InitConsole();
    static void DisplayCells(int cells[], int cellCount);
    static void DisplayCursor(int cursorIndex);
    static void DisplayChar(char c);
    static void Debug(char *code, int interpreterPos, int cursorPos, int size);
};


#endif //ZPLUSPLUS_OUTPUT_H
