/**
 * C implementaion of Vigenère cipher
 *
 * This program encrypts and decrypts messages using the Vigenère cipher. 
 * The keyword must have at least one letter. The keyword is case-insensitive
 * and it must not contain non-alphabatic characters otherwise it's rejected.
 * When encrypting or decrypting, the case is preserved, and non-letters are 
 * kept unchanged.
 *
 * Author: Abu Sayeed Roni 
 * roni.abusayeed@gmail.com
 * 
 * Copyright (c) 2019
 * All rights reserved
 */


#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char caesar_core(char ch, int key);
int key_manager();
int intput_error();

string input(bool decrypt);
void ouput(bool decrypt, string value);


char* KEYWORD = NULL;	
const char* DECRYPT_OPTION = "-d";

bool DECRYPT;


int main(int argc, char const *argv[])
{
	// interpret command modes (encrypt/decrypt)

	if(argc == 2){
		DECRYPT = false;
	}
	else if(argc == 3){
		DECRYPT = true;
	}
	else{
		return intput_error();
	}

	// gather command details and validate

	if(DECRYPT){
		// validate decryption option (first command-line argument)
		if(strlen(argv[1]) != strlen(DECRYPT_OPTION))
			return intput_error();
		for(int i = 0, n = strlen(DECRYPT_OPTION); i < n; i++){
			if(DECRYPT_OPTION[i] != argv[1][i])
				return intput_error();
		}

		// in decryption mode the keyword is the second command-line argument
		// and in encryption mode it's the first command-line argument

		// get the keyword (second command-line argument)
		KEYWORD = malloc(sizeof(char) * (strlen(argv[2]) + 1));  // one extra Byte for null-terminator
		strcpy(KEYWORD, argv[2]);
	}
	else {
		// Get the keyword (first command-line argument)
		KEYWORD = malloc(sizeof(char) * (strlen(argv[1]) + 1));  // one extra Byte for null-terminator
		strcpy(KEYWORD, argv[1]);
	}
	// validate the keyword
	// keyword must not contain anything other than letters
	for(int i = 0, n = strlen(KEYWORD); i < n; i++)	{
		if(! isalpha(KEYWORD[i])) 
		{
			return intput_error();
		}
	}

	// get the input text
	string input_text = input(DECRYPT);

	// make translate (encrypt/decrypt)
	int modifier = DECRYPT ? -1 : 1; 	// modifies the caesar key to rotate backward/forward
	int text_size = strlen(input_text);
	char* output_text = malloc(sizeof(char) * (text_size + 1));	 // one extra Byte for null-terminator
	for(int i = 0; i < text_size; i++){
		char temp_c = input_text[i];
		if(isalpha(temp_c)){
			int key = key_manager();
			output_text[i] = caesar_core(temp_c, modifier * key);
		}
		else{
			output_text[i] = temp_c;
		}
	}
	output_text[text_size] = 0;	// null terminator

	// show output
	ouput(DECRYPT, output_text);

	// clean up
	free(KEYWORD);	
	free(output_text);
	return 0;
}


/**
 * Returns an integer key between 0 and 25 inclusive corresponding to each letter
 * of the keyword in cycle each time the function is called. 
 *
 * @param: keyword must not be changed between function calls. And keyword
 * must not contain anything other than letters.
 */
int key_manager()
{
	// Keep track of how many times this function is called.
	static int counter = 0;

	int pos = counter % strlen(KEYWORD);
	char char_key = KEYWORD[pos];
	++counter;	// Update the function call times.

	// char_key is each character of the keyword in cycle
	// every time the function is called.
	
	// Return 0 to 25 inclusive as key, if the character is a letter
	if(isupper(char_key))
		return char_key - 65;
	else if (islower(char_key))
		return char_key - 97;

	return -1;	//	-1 is invalid caesar key. If the corresponding character in
				// the keyword is not a letter, it's a way of showing the keyword
				// is not valid: that the keyword must not contain anything other 
				// than letters(alpha).
}


/**
 * Rotational cipher function around 26 letters of English alphabet.
 *
 * @param ch: plaintext character that's needed to be encrypted.
 * @param key: cipher key i.e. the number of steps rotated around the alphabets.
 * @return: encrypted character i.e. the letter in the English alphabet that is 
 * <key> steps around the alphabet.
 * This function preserves the case of the letters doesn't modify the character 
 * if it's not a letter.
 */
char caesar_core(char ch, int key)
{
	// Dont change if it's not an alpha
	if(! isalpha(ch))
		return ch;

	int offset = isupper(ch) ? 65 : 97;
	const int alphabet_size = 26;

	ch -= offset;
	// C's % operator doesn't work like python's for negative numbers
	// ((n % M) + M) % M same as (n % M) in python
	ch = (((ch + key) % alphabet_size) + alphabet_size) % alphabet_size;
	ch += offset;

	return ch;
}

string input(bool decrypt)
{
	string value;
	if(decrypt) value = get_string("ciphertext: ");
	else value = get_string("plaintext: ");
	return value;
}

void ouput(bool decrypt, string value)
{
	if(decrypt) printf("plaintext: ");
	else printf("ciphertext: ");
	printf("%s\n", value);
}

int intput_error()
{
	printf("Usage: ./vigenere keyword\n");
	printf("Usage: ./vigenere -d keyword\n");
	return 1;
}
