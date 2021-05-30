#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char base[64] = {
 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
 'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
 'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
 'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'};

int main(int argc, char const *argv[]) {
  int i;

  int len = 14;
  char test[14] = {'M','a','n',' ','i','s',' ','d','i','s','t','i','M','a'};
  const char *chunk = test;

  if (argc > 1) {
    chunk = argv[1];
    len=strlen(argv[1]);
  }

  int fullTriplets = (len)/3;
  int rem = (len)%3;
  const char *triplet = chunk;

  for(i=0; i<fullTriplets; ++i){
    unsigned char value = (triplet[0] & 0xFC)>>2;
    printf("%c",base[value]);
    value = ((triplet[0] & 0x03)<<4) | ((triplet[1] & 0xF0)>>4);
    printf("%c",base[value]);
    value = ((triplet[1] & 0x0F)<<2) | ((triplet[2] & 0xC0)>>6);
    printf("%c",base[value]);
    value = (triplet[2] & 0x3F);
    printf("%c",base[value]);
    triplet += 3;
  }
  if(rem) {
    char lastTriplet[3]={0,0,0};
    lastTriplet[0]=triplet[0];
    if (rem==2) lastTriplet[1]=triplet[1];

    unsigned char value = (lastTriplet[0] & 0xFC)>>2;
    printf("%c",base[value]);
    value = ((lastTriplet[0] & 0x03)<<4) | ((lastTriplet[1] & 0xF0)>>4);
    value = ((lastTriplet[0] & 0x03)<<4) | ((lastTriplet[1] & 0xF0)>>4);
    printf("%c",base[value]);

    if(rem==2) {
      value = ((lastTriplet[1] & 0x0F)<<2) | ((lastTriplet[2] & 0xC0)>>6);
      printf("%c",base[value]);
    } else
      printf("=");
    
    printf("=");

  }

  printf("\n\ntrip=%i, rem=%i\n", fullTriplets,rem);

  return 0;
}