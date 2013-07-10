#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// boolean type
#define bool int
#define true 1
#define false 0

char VigenreTable[26][26];

void initializeVigenreTable(){
	int row, col;
	char theChar;
	for(row=0; row<26; row++){
		for(col=0; col<26; col++){
			theChar = 'A' + row + col;
			if(theChar > 'Z')
				theChar -= 26;
			VigenreTable[row][col] = theChar;
		}
	}
}

void displayUsageThenExit(){
	printf("Usage: ./VigenereCipher -e plaintext.txt\n");
	printf("   or: ./VigenereCipher -d chiphertext.txt\n");
}

void displayFileErrorThenExit(){
	printf("The file does not exist or reading from it is denied.\n");
}

// test if the file exists and the program has the permission to read it
bool fileIsValid(char *fileName){
	if(access(fileName, F_OK | R_OK) != -1)
		return true;
	else
		return false;
/*
    FILE *file = fopen(fileName, "r");
    if(file){
        fclose(file);
        return true;
    }
    return false;
*/
}

// verify the input arguments are of correct format
bool argumentsFormatCorrect(int argc, char *mode){
	if(argc != 3)
		return false;
	if(strcmp(mode, "-e") && strcmp(mode, "-d"))
		return false;
	return true;
}

// determine whether it is to encrypt or to decrypt
char operation(char *mode){
	if(strcmp(mode, "-e") == 0)
		return 'e';
	else if(strcmp(mode, "-d") == 0)
		return 'd';
}

// do the encryption
char encrypt(char key, char plaintext){
	return VigenreTable[key-'A'][plaintext-'A'];
}

// do the decryption
char decrypt(char key, char ciphertext){
	int col;
	for(col=0; col<26; col++){
		if(VigenreTable[key-'A'][col] == ciphertext)
			return (col + 'A');
	}
}

// if the supplied char is a lowwer-case letter, convert it to upper-case
char convertToUpperCase(char letter){
	if(letter>='a' && letter<='z')
		letter -= ('a' - 'A');
	return letter;
}

// process the file and print out the converted text
void processFile(FILE *inputFile, char mode){
	int keyLength = 1000;
	char *keyString = (char*)malloc(keyLength);
	memset(keyString, 0, keyLength);
	// read the secret key
	keyLength = getline(&keyString, &keyLength, inputFile);
	// erase the '\n'
	keyString[--keyLength] = 0;
	int readingKey = 0;
	// convert the secret key string to all upper-case
	for(readingKey=0; readingKey<keyLength; readingKey++)
		keyString[readingKey] = convertToUpperCase(keyString[readingKey]);

	// encrypt or decrypt
	readingKey = 0;
	while(true){
		char key = keyString[readingKey];
		char oneChar = fgetc(inputFile);
		// treat lower-case letters as corresponding upper-case ones
		oneChar = convertToUpperCase(oneChar);

		if(oneChar == EOF)
			break;
		else if(oneChar>='A' && oneChar<='Z'){
			switch(mode){
				case 'e':
					printf("%c", encrypt(key, oneChar));
					break;
				case 'd':
					printf("%c", decrypt(key, oneChar));
			}

			readingKey = readingKey + 1;
			if(readingKey >= keyLength)
				readingKey = 0;
		}
		else
			printf("%c", oneChar);

	};
	free(keyString);
}

int main(int argc, char **const argv){
	if(!argumentsFormatCorrect(argc, argv[1])){
		displayUsageThenExit();
		exit(-1);
	}
	if(!fileIsValid(argv[2])){
		displayFileErrorThenExit();
		exit(-1);
	}

	initializeVigenreTable();

	FILE *inputFile = fopen(argv[2], "r");
	processFile(inputFile, operation(argv[1]));
	fclose(inputFile);

	return 0;
}
