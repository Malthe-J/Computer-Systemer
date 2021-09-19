#include <stdio.h>  // fprintf, stdout, stderr.
#include <stdlib.h> // exit, EXIT_FAILURE, EXIT_SUCCESS.
#include <string.h> // strerror.
#include <errno.h>  // errno.
#include <assert.h>

int print_hello_world() {
  return fprintf(stdout, "Hello, world!\n");
}

int main(int argc, char *argv[]) {
  assert(argc == 2);
  int retval = EXIT_SUCCESS;
  FILE *fptr;
#define IsUTF8(Character) (((Character) & 0xC0) == 0x80) // Macro which has a variable called Character and if you & with 0xC0 it has to give 0x80 and then it is a UTF-8 character.
  char* filename = argv[1];
  int c;
  // Open file
  fptr = fopen(filename, "rb");
  
  if (fptr == NULL)
  {
      printf("cannot open file: %s\n", strerror(errno));
      exit(0);
  }

  c = fgetc(fptr); //we use fgetc because it reads 1 byte at a time
  if (c == EOF)
    {
      printf("%s: empty\n", filename);
      exit(0);
    }

  while (c != EOF)
  
  {
    if (c >= 7 && c <= 126)
    {
      
      printf("%s: ASCII text\n", filename);
      exit(0);
    }

    else if (c >= 160) { // In this case we dont check whether the value is below 255 since It's 8-bit
      int continuationByte = fgetc(fptr); //If the value is over 127, then It's either ISO or UTF-8 and to find out which we have to check the next byte which this variable does.

      if (IsUTF8(continuationByte)) //If the next byte checks out with our macro, then It's UTF-8, if not then Its ISO and if either, then It's data
      {
      printf("%s: UTF-8 Unicode text\n", filename);
      exit(0);
      }

      else {
      printf("%s: ISO text\n", filename);
      exit(0);
      }
    }

    else {
      printf("%s: data \n", filename);
      exit(0);
    }
  }
  
  fclose(fptr);

  return retval;
}
