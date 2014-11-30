#include "../Main.h"

int main(int argc, const char * argv[])
{
	initializeMain();
	while(runMain());
	deinitializeMain();
	return 0;
}
