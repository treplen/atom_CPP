//
// Created by svuatoslav on 3/15/17.
//

#include "Utils.h"

char* utils::getPadding(char symbol, int amount)
{
    char* padding;
    padding = new char[amount+1];
    for(int i = 0;i<amount;i++) padding[i]=symbol;
    padding[amount]=0;
    return padding;
}