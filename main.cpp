#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

#include "dictionary.h"

#include "Genetic.h"

// generate a random letter substitution code
// the result will be a 26 string with one instance each of each capital letter
// this will be used as a lookup table for encryption and decryption
string GenerateCode()
{
	string table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	FILE *fp = fopen("/dev/urandom", "r");
	
	// get a bunch of random numbers
	const int bufsize = 1024;
	unsigned char buffer[bufsize];
	fread(buffer, bufsize, 1, fp);

	fclose(fp);

	// swap each charater for a random other character
	// lots of swaps means any artifacts of the 256 % 26 operation wrapping
	// around will be diluted
	for(int i = 0; i < bufsize; ++i)
	{
		char temp = table[i % 26];
		table[i % 26] = table[buffer[i] % 26];
		table[buffer[i] % 26] = temp;
	}
	
	return table;
};

string Encrypt(string &code, string &text)
{
	string output = text;

	// create output by converting input characters into offsets into the code table
	for(int i = 0; i < text.length(); ++i)
	{
		if(text[i] >= 'A' && text[i] <= 'Z')
		{
			int j = (int)text[i] - 'A';
			output[i] = code[j];
		}
	}
	return output;
}

int CountWords(string &text)
{
	int count = 0;
	int start = 0;
	int end = 0;

	for(int i = 0; i < text.length(); ++i)
	{
		if(text[i] == ' ')
		{
			end = i;
			if(end > start)
			{
				printf("Looking up %s\n", text.substr(start, end - start).c_str());
				if(IsAWord(text.substr(start, end - start ).c_str()))
				{
					printf("Found\n");
					 ++count;
				}

			}
			start = end + 1;
		}
	}
	return count;
}

// random quote from Snow Crash
string text = "WE ARE ALL SUSCEPTIBLE TO THE PULL OF VIRAL IDEAS LIKE MASS HYSTERIA OR A TUNE THAT GETS INTO YOUR HEAD THAT YOU KEEP HUMMING ALL DAY UNTIL YOU SPREAD IT TO SOMEONE ELSE JOKES URBAN LEGENDS CRACKPOT RELIGIONS MARXISM NO MATTER HOW SMART WE GET THERE IS ALWAYS THIS DEEP IRRATIONAL PART THAT MAKES US POTENTIAL HOSTS FOR SELF REPLICATING INFORMATION";

int main(int argc, char **argv)
{
	printf("Text:  %s\n", text.c_str());
	printf("Recognized words: %i\n", CountWords(text));

	string code = GenerateCode();
	printf("Code:  %s\n", code.c_str());
	string cipher = Encrypt(code, text);
	printf("Cipher:  %s\n", cipher.c_str());
	printf("Recognized words: %i\n", CountWords(cipher));
	
	return 0;
}
