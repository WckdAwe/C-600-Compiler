#ifndef __SIZES_H__
#define __SIZES_H__

#define CHAR_SIZE       sizeof(char)
#define INT_SIZE        sizeof(int)
#define FLOAT_SIZE      sizeof(float)

#define ENUM_SIZE       INT_SIZE
#define MAX_STR_CONST 	256

#ifndef __ASCII_CHARS__
#define __ASCII_CHARS__
	extern char ASCII_TABLE[];
	#define ASCII_size sizeof(ASCII_TABLE)
#endif

#endif