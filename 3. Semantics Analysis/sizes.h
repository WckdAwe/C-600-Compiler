#ifndef __SIZES_H__
#define __SIZES_H__

#define CHAR_SIZE       sizeof(char)
#define INT_SIZE        sizeof(int)
#define FLOAT           sizeof(float)

#define ENUM_SIZE       INT_SIZE
#define MAX_STR_CONST 	256

#ifndef ASCII_CHARS
#define ASCII_CHARS

char ASCII[] = {
	'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
	'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
	'0','1','2','3','4','5','6','7','8','9'};		//to be continued...

	#define ASCII_size sizeof(ASCII)
#endif


#endif