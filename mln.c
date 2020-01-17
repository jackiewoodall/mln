#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include <assert.h>

void carryAndPrint(int *p, const unsigned int size) {
    // moving forward calculate carry
    int *k = p;
    int carry = 0;
    for(;k < p + size; k++) {
        *k += carry;
        if( *k > 9) {
            carry = *k / 10;
            *k %= 10;
        } else carry = 0;
    }
    assert(carry==0);
    k--;

    // moving back, print
    // skip leading zeros
    for(;k>p;k--) {
        if(*k!=0) break;
    }
    for(;k>=p;k--) printf("%d",*k);
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
            *karet += (*pa - '0') * (*pb - '0');
            karet++;
        }
    }
}

int mln(char *a, char *b) {
    const int aSize = strlen(a);
    const int bSize = strlen(b);
    const int pSize = aSize + bSize;

    int *p = alloca(pSize * sizeof(int));
    memset(p, 0, pSize * sizeof(int));

    multiply(a, aSize, b, bSize, p, pSize);

    carryAndPrint(p, pSize);

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

