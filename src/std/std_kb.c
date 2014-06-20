#include "std/kb.h"

char get_char()
{
	while(!kbhit()){};

	return U0RXD;
}