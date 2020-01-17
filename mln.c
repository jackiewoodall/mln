#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include <assert.h>

void print(int *p, const unsigned int size) {
    // skip leading zeros
    const int *k = p + size-1;
    for(;k>p && !*k;k--) ;
    for(;k>=p;k--) printf("%d",*k);
    printf("\n");
}

void multiply(char *a, const int aSize, char *b, const int bSize, int *p, unsigned int pSize) 
{
    int *cursor = p, *karet;
    int carry = 0;
    for(char *pa = a + aSize-1; pa >= a; pa--) 
    {
        assert(cursor < &(p[pSize]));
        karet = cursor;
        cursor++;
        if (*pa == '0') continue;

        for(char *pb = b + bSize-1; pb >= b; pb--,karet++)
        {
            assert(karet < &(p[pSize]));
            *karet += (*pa - '0') * (*pb - '0');

            // process carry if first digit from b or last digit from a
            if(pb == b+bSize-1 || pa == a) {
                *karet += carry;
                if(*karet>9) {
                    carry = *karet / 10;
                    *karet %= 10;
                } else carry = 0;
            }
        }
    }
    if(carry) {
        assert(karet < &(p[pSize]));
        *karet = carry;
    }
}

int mln(char *a, char *b) {
    const int aSize = strlen(a);
    const int bSize = strlen(b);
    const int pSize = aSize + bSize;

    int *p = alloca(pSize * sizeof(int));
    memset(p, 0, pSize * sizeof(int));

    multiply(a, aSize, b, bSize, p, pSize);

    print(p, pSize);

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

