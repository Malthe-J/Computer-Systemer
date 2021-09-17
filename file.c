#include <stdio.h>  // fprintf, stdout, stderr.
#include <stdlib.h> // exit, EXIT_FAILURE, EXIT_SUCCESS.
#include <string.h> // strerror.
#include <errno.h>  // errno.

int print_hello_world() {
  return fprintf(stdout, "Hello, world!\n");
}

int main(int argc, char *argv[]) {
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
    printf("%i\n", c);
    if (c >= 7 && c <= 126)
    {
      
      printf("%s: ASCII\n", filename);
      exit(0);
    }
    int continuationByte = fgetc(fptr);
    if (IsUTF8(continuationByte)){
      printf("%s: UTF-8\n", filename);
      exit(0);
    }
    else
    {
        ungetc(continuationByte, fptr);
    }
    
    if (c > 127 || c <= 255) 
    {
      printf("%s: ISO\n", filename);
      exit(0);
    }
    
    
    printf ("%02x\n", c);
    c = fgetc(fptr);
  }
  
  fclose(fptr);

  return retval;
}
