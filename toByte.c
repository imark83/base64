#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char base[64] = {
 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
 'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
 'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
 'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'};

unsigned char invBase(char c) {
  unsigned rop =0;
  while (base[rop]!=c) rop++;
  return rop;
}

int main(int argc, char const *argv[]) {
  int i;

  int len = 20;
  char test[20] = {
  'T','W','F','u','I','G','l','z','I','G',
  'R','p','c','3','R','p','T','W','E','='
  };
  const char *chunk = test;

  if (argc > 1) {
    chunk = argv[1];
    len=strlen(argv[1]);
  }

  int fullTetras = (len)/4;

  const char *tetra = chunk;
  unsigned char v0, v1, v2, v3;
  for(i=0; i<fullTetras; ++i){

    if(tetra[3] != '=') 
      v3 = invBase(tetra[3]);
    else
      v3 = 0;
    if(tetra[2] != '=')
      v2 = invBase(tetra[2]);
    else 
      v2 = 0;

    v1 = invBase(tetra[1]);
    v0 = invBase(tetra[0]);

    printf("%c",(v0<<2) | ((v1 & 0x30)>>4));
    if(tetra[2] != '=') {
      printf("%c",((v1 &0x0F)<<4) | ((v2 & 0x3C)>>2));
    } 
    if(tetra[3] != '=') {
      printf("%c",((v2 &0x03)<<6) | ((v3 & 0x3F)));
    } 

    tetra += 4;
  }

  printf("\n");


  return 0;
}