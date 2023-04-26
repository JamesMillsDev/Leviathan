#include <Leviathan/Application.h>
#include "TestGame.h"

int main(int argc, char* argv[])
{
	return Application::Run<TestGame>(argv);
}