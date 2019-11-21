/**
 * C implementaion Vigenère cipher
 *
 * Author: Abu Sayeed Roni 
 * roni.abusayeed@gmail.com
 * 
 * Copyright (c) 2019
 * All rights reserved
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 */


#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char caesar_core(char ch, int key);
int key_manager();
int intput_error();

// Keyword is not case sensitive i.e. A and a means same thing and so on...
char* KEYWORD = NULL;	
const char* DECRYPT_OPTION = "-d";


int main(int argc, char const *argv[])
{
	// Make sure there is exactly one (for encryption) 
	// or two (for decryption) commandline argument.

	if(argc == 2)	// for one command-line argument
	{
		// Get the keyword
		KEYWORD = malloc(sizeof(char) * (strlen(argv[1]) + 1)); 	// One extra Byte for null-terminator
		strcpy(KEYWORD, argv[1]);

		// Make sure the argument i.e. the keyword contains only letters
		for(int i = 0, n = strlen(KEYWORD); i < n; i++)	
		{
			if(! isalpha(KEYWORD[i])) 
			{
				return intput_error();
			}
		}

		// Get the plaintext
		string plain_text = get_string("plaintext: ");

		// Make cipher
		int size = strlen(plain_text);
		char* cipher_text = malloc(sizeof(char) * (size + 1));	// One extra Byte for null terminator

		for(int i = 0; i < size; i++) {
			char plain_char = plain_text[i];

			// Don't call the key_manager function if we are not intending to use the key
			// because each function call will update the counter inside key_manager. And
			// we only need to use the key to cipher a character if it's a letter.
			if(isalpha(plain_char))
			{
				int key = key_manager();	// We already made sure the keyword only contains letters.
											// So there won't be any surprising behaviour. Like returning -1.
				char cipher_letter = caesar_core(plain_text[i], key);
				cipher_text[i] = cipher_letter;
			}
			else
			{
				cipher_text[i] = plain_char;
			}		
		}
		cipher_text[size] = 0;	// NULL terminator.

		// Show output
		printf("ciphertext: %s\n", cipher_text);

		// Clean Up
		free(cipher_text);
		free(KEYWORD);
		return 0;
	}

	else if(argc == 3)	// for two command-line argument
	{
		// Make sure the first argument (decryption option) is valid
		if(strlen(argv[1]) != strlen(DECRYPT_OPTION)){
			return intput_error();
		}
		for(int i = 0, n = strlen(DECRYPT_OPTION); i < n; i++)
		{
			if(DECRYPT_OPTION[i] != argv[1][i]){
				return intput_error();
			}
		}

		// Get the keyword (second argument)
		KEYWORD = malloc(sizeof(char) * (strlen(argv[2]) + 1)); 	// One extra Byte for null-terminator
		strcpy(KEYWORD, argv[2]);

		// Make sure the argument i.e. the keyword contains only letters
		for(int i = 0, n = strlen(KEYWORD); i < n; i++)	
		{
			if(! isalpha(KEYWORD[i])) 
			{
				return intput_error();
			}
		}

		// Get the cipher text
		string cipher_text = get_string("ciphertext: ");

		// Decrypt
		int size = strlen(cipher_text);
		char* plain_text = malloc(sizeof(char) * (size + 1));	// One extra Byte for null-terminator
		for(int i = 0; i < size; i++)
		{
			char cipher_char = cipher_text[i];
			if(isalpha(cipher_char))
			{
				// Negative caesar key will rotate in the oposite direction.
				char plain_char = caesar_core(cipher_char, ( - key_manager()));				
				plain_text[i] = plain_char;
			}
			else
			{
				plain_text[i] = cipher_char;
			}
		}
		plain_text[size] = 0;	// Null terminator

		// Show output
		printf("plaintext: %s\n", plain_text);

		// Clean Up
		free(plain_text);
		free(KEYWORD);
		return 0;
	}
	else 
	{
		return intput_error();
	}
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
	ch = (((ch + key) % alphabet_size) + 26) % 26;
	ch += offset;

	return ch;
}

int intput_error()
{
	printf("Usage: ./vigenere keyword\n");
	printf("Usage: ./vigenere -d keyword\n");
	return 1;
}
