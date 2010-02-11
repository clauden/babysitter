#include <stdio.h>
#include <string.h>
#include <iostream>

#include "honeycomb_config.h"
#include "c_ext.h"

void usage(const char *progname) {
  fprintf(stderr, "Usage: %s <filename\n", progname);
  exit(-1);
}

extern FILE *yyin;

int main (int argc, char const *argv[])
{
  if (!argv[1]) usage(argv[0]);
  
  char *filename = strdup(argv[1]);
  printf("----- parsing %s -----\n", filename);
  
  // open a file handle to a particular file:
	FILE *fd = fopen(filename, "r");
	// make sure it's valid:
	if (!fd) {
    fprintf(stderr, "Could not open the file: '%s'\nCheck the permissions and try again\n", filename);
		return -1;
	}
	// set lex to read from it instead of defaulting to STDIN:
	yyin = fd;
	
	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));

  printf("\n");
  return 0;
}