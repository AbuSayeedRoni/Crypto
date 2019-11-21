#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char caesar_core(char ch, int key);

int main(int argc, string argv[])
{
	if(argc == 2)
	{
		// argv[1] is the key

		// Validate the key: each character is a digit
		for(int i = 0, n = strlen(argv[1]); i < n; i++)
		{
			if(! isdigit(argv[1][i]))
			{
				printf("Usage: %s key\n", argv[0]);
				return 1;
			}
		}

		// By this point we have one single command-line argument to the program
		// And the key is valid i.e. comprised of only digits 0 to 9.

		// Convert the key to int type
		int key = atoi(argv[1]);


		// Get the plain text
		string plain_text = get_string("plaintext: ");

		// Make cipher
		int size = strlen(plain_text);
		char* cipher_text = malloc(sizeof(char) * (size + 1));
		for(int i = 0; i < size; i++)
		{
			cipher_text[i] = caesar_core(plain_text[i], key);
		}
		cipher_text[size] = 0;	// Null termination

		// Show cipher output
		printf("ciphertext: %s\n", cipher_text);

		// Clean up
		free(cipher_text);
	} 
	else
	{
		printf("Usage: %s key\n", argv[0]);
		return 1;
	}
}

char caesar_core(char ch, int key)
{
	// Dont change if it's not an alpha
	if(! isalpha(ch))
		return ch;

	int offset = isupper(ch) ? 65 : 97;
	const int alphabet_size = 26;

	ch -= offset;
	ch = (ch + key) % alphabet_size;
	ch += offset;

	return ch;
}
