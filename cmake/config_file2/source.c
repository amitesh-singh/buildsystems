#include <stdio.h>
#include "config.h"

int main()
{
	printf("Project information: %d, %d, %d", VERSION_MAJOR,
		VERSION_MINOR, VERSION_PATCH);
	
	return 0;
}