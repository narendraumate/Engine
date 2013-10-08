#include "../Main.h"

void initializeWindow(const int& width, const int& height, const char* applicationName)
{
}

int main(int argc, const char * argv[])
{
	initializeWindow(800, 600, "Renderer");
	return 0;
}

int main(int argc, const char * argv[])
{
	initializeMain();
	while(runMain());
	deinitializeMain();
	return 0;
}
