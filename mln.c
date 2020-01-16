#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include <assert.h>

void printP(const int*p, const unsigned int size) 
{
	int bLeading0 = 1;
	for(const int *i = p + size - 1; i >= p; i--)
	{
		if (bLeading0 && *i == 0) continue;
		bLeading0 = 0;
		printf("%d", *i);
	}
	
	if (bLeading0) printf("0");
	printf("\n");
}

void multiply(char *a, const int aSize, char *b, const int bSize, int *p, unsigned int pSize) 
{
	int *cursor = p;
	for(char *pa = a + aSize-1; pa >= a; pa--) 
	{
		assert(cursor < &(p[pSize]));
		int *karet = cursor;
		cursor++;
		if (*pa == '0') continue;

		for(char *pb = b + bSize-1; pb >= b; pb--)
		{
			assert(karet < &(p[pSize]));
			const int product = (*pa - '0') * (*pb - '0');
			*karet += product;
			karet++;
		}
	}

	int carry = 0;
	for(int i = 0; i < pSize; i++)
	{
		p[i] += carry;
		int digit = p[i] % 10;
		carry = p[i] / 10;
		p[i] = digit;
	}
}

int mln(char *a, char *b) {
	const int aSize = strlen(a);
	const int bSize = strlen(b);
	const int pSize = aSize + bSize;

	int *p = alloca(pSize * sizeof(int));
	memset(p, 0, pSize * sizeof(int));

	multiply(a, aSize, b, bSize, p, pSize);

	printP(p, pSize);

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 3 ) {
		fprintf(stderr, "Please give me two numbers.\n");
		return 1;
	}
	return mln(argv[1], argv[2]);
}

