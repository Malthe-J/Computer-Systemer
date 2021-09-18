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
#define IsUTF8(Character) (((Character) & 0xC0) == 0x80)
  char* filename = argv[1];
  int c;
  // Open file
  fptr = fopen(filename, "rb");
  
  if (fptr == NULL)
  {
      printf("cannot open file: %s\n", strerror(errno));
      exit(0);
  }

  c = fgetc(fptr);
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

    else if (c >= 160) {
      int continuationByte = fgetc(fptr);

      if (IsUTF8(continuationByte))
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
