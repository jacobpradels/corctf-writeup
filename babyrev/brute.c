#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char ASCII_UPPER[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char ASCII_LOWER[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};



int rot_n(int param_1,int param_2)
{
  char *pcVar1;
  int uVar2;
  
  pcVar1 = strchr(ASCII_UPPER,(int)(char)param_1);
  if (pcVar1 == (char *)0x0) {
    pcVar1 = strchr(ASCII_LOWER,(int)(char)param_1);
    if (pcVar1 == (char *)0x0) {
      uVar2 = param_1;
    }
    else {
      uVar2 = (int)ASCII_LOWER[((int)(char)param_1 + -0x61 + param_2) % 0x1a];
    }
  }
  else {
    uVar2 = (int)ASCII_UPPER[((int)(char)param_1 + -0x41 + param_2) % 0x1a];
  }
  return uVar2;
}

int check[20] = {0x5f,0x40,0x5a,0x15,0x75,0x45,0x62,0x53,0x75,0x46,0x52,0x43,0x5f,0x75,0x50,0x52,0x75,0x5f,0x5c,0x4f};

int primes[20] = {2, 5, 11, 13, 17, 23, 29, 29, 37, 37, 41, 47, 53, 53, 59, 61, 67, 71, 73, 79};
int test[20];// = {117,106,112,63,95,111,72,121,95,108,120,105,117,95,95,122,120,95,117,118};
int test_result[20];


int main()
{

    for (int i = 0; i < 20; i++)
    {
        test[i] = check[i] ^ 42;
    }

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 300; j++)
        {
            if (rot_n(j,primes[i]) == test[i])
            {
                test_result[i] = j;
                printf("%c",(char)j);
            }
        }
    }
    return 0;
}
