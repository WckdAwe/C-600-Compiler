#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//int HexToInt(char*);
//int OctToInt(char*);
//int BinToInt(char*);
//int StrToInt(char*);
//int LengthToPosition(int);
//double BinToFloat(char*);
//double HexToFloat(char*);
//double OctToFloat(char*);



int HexToInt(char *str){
    int number;
    return number = (int)strtol(&str[2],NULL,16);
}

int OctToInt(char *str){
    int number;
    return number = (int)strtol(&str[2],NULL,8);
}

int BinToInt(char *str){
    int number;
    return number = (int)strtol(&str[2],NULL,2);
}


int StrToInt(char *str){
    int length = strlen(str)-2;
    printf("Length: %d\n",length);
    int index = 2;
    int base = 48;
    int number = 0;
    while(str[index] != NULL){
        number += ((int)str[index]-base)*LengthToPosition(length);
        index ++;
        length--;
    }
    return number;
}

//This function returns the position of a number based on the given length
//Example: length = 3 returns 100
//1 represents the position of the number
int LengthToPosition(int length){
    int number = 1;
    while(length-1 != 0){
        number = number * 10;
        length--;
    }
    return number;
}

double BinToFloat(char* str){
    double number = 0.0;
    int i,length_real;
    char *character;
    character = strchr(str,'.');
    length_real = strlen(character)-1;
    number = (int)strtol(&str[2],&character,2);
    for(i=1;i<length_real;i++){
        number += (character[i] - '0') * (1/pow(2,i));
    }
    return number;
}

double OctToFloat(char* str){
    double number = 0.0;
    int i,length_real;
    char *character;
    character = strchr(str,'.');
    length_real = strlen(character)-1;
    number = (int)strtol(&str[2],&character,8);
    for(i=1;i<length_real;i++){
        number += (character[i]) * (1/pow(8,i));
    }
    return number;
}

double HexToFloat(char*str){
    double number = 0.0;
    int i,length_real;
    char *character;
    character = strchr(str,'.');
    length_real = strlen(character)-1;
    number = (int)strtol(&str[2],&character,16);
    for(i=1;i<length_real;i++){
        number += (character[i]) * (1/pow(16,i));
    }
    return number;
}
