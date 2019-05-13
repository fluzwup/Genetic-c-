#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

//#include "Genetic.h"

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


// encrypt a text with the code, and return it
int main(int argc, char **argv)
{
	for(int i = 0; i < 100; ++i)
	{
		printf("%s\n", GenerateCode().c_str());
	}
	return 0;
}
