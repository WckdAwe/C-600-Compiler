#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



int HexToInt(char*);
int OctToInt(char*);
int BinToInt(char*);
int StrToInt(char*);
int LengthToPosition(int);
float BinToFloat(char*);
float HexToFloat(char*);
float OctToFloat(char*);

void assertConv(int (*f)(char*), char* input, int predict);
void assertFloatConv(float (*f)(char*), char* input, float predict);

int error_count = 0;

int main(){
	
	assertConv(HexToInt, "0X3fca", 16330);
	assertConv(HexToInt, "0Xffff", 65535);
	assertConv(OctToInt, "0O37712", 16330);
	assertConv(OctToInt, "0O177777", 65535);
	assertConv(BinToInt, "0B10110", 22);
	assertConv(BinToInt, "0B10011", 19);
	
	assertFloatConv(HexToFloat, "0XA.9", 0); //? How do we calc these (Floats ->)
	//assertFloat(HexToFloat, "",  );
	assertFloatConv(OctToFloat, "0O3.617",  0);
	//assertFloat(OctToFloat, "",  );
	assertFloatConv(BinToFloat, "0B1.0010", 0);
	//assertFloat(BinToFloat, "",  );
	
	
	if(!error_count){
		printf("SUCCESS! No errors were found.");
		return EXIT_SUCCESS;
	}
	printf("Test unsuccessful with %d errors!\n", error_count);
	
	// Optional support for the developer.
	printf("Don't worry bud. You can do it. It will take just a bit more time and effort. Good luck!\n");
}

void assertConv(int (*f)(char*), char* input, int predict){
	printf("Calculating %s || Expecting %d || ", input, predict);
	int res = (*f)(input);
	printf("Result: %d\n", res);
	if(res != predict){
		printf("Error in calculation!\n");
		error_count++;
	}
}

void assertFloatConv(float (*f)(char*), char* input, float predict){
	printf("Calculating %s || Expecting %f || ", input, predict);
	float res = (*f)(input);
	printf("Result: %f\n", res);
	if(res != predict){
		printf("Error in calculation!\n");
		error_count++;
	}
}

int HexToInt(char *str){
    return (int)strtol(&str[2],NULL,16);
}

int OctToInt(char *str){
    return (int)strtol(&str[2],NULL,8);
}

int BinToInt(char *str){
    return (int)strtol(&str[2],NULL,2);
}

int StrToInt(char *str){
    int length = strlen(str)-2;
    printf("Length: %d\n",length);
    int index = 2;
    int base = 48;
    int number = 0;
    while(str[index] != '\0'){
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

float BinToFloat(char* str){
    float number = 0.0;
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

float OctToFloat(char* str){
    float number = 0.0;
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

float HexToFloat(char*str){
    float number = 0.0;
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
