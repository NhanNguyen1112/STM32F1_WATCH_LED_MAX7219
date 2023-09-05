
#include "String.h"

unsigned char str_cmp(const unsigned char *S1, const unsigned char *S2)
{
  unsigned char Flag_Check=1;
  unsigned char count=0;
  
  while (S1[count] != '\0') 
  {
    if(S1[count] != S2[count]) 
    {
      Flag_Check = 0;
      break;
    }
    count++;
  }
  return Flag_Check;
}

int str_len(const char *src)
{
  int count=0;
  while(src[count] != '\0')
  {
    if(src[count]=='\0') break;
    else count++;
  }
  return count;
}

void str_cpy(char *dest, const char *src, const char len)
{
  int i=0;
  for(i=0; i<len; i++)
  {
    dest[i] = src[i];
  }
}

void str_cat(char *dest, const char *src)
{
  int i=0;
  int j=0;
  for(i=str_len(dest); i<(str_len(dest)+str_len(src)); i++)
  {
    dest[i] = src[j];
    j++;
  }
}

void str_lwr(char *s) /* Hoa ve thuong */
{
  int i=0;
  for(i=0; i<str_len(s); i++)
  {
    if(s[i]>=65 && s[i]<=90) s[i]+=32;
    else continue;
  }
}

void str_upr(char *s) /* Thuong ve hoa */
{
  int i=0;
  for(i=0; i<str_len(s); i++)
  {
    if(s[i]>=97 && s[i]<=122) s[i]-=32;
    else continue;
  }
}

void BufferClear(unsigned char *Buffer, unsigned int Length)
{
  unsigned int i=0;
  for(i=0; i<=Length; i++)
  {
    *Buffer = 0;
    Buffer++;
  }
}


