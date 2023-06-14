#include <Leviathan/Application.h>
#include "TestGame.h"

using Leviathan::Application;

int main(int argc, char* argv[])
{
	return Application::Run<TestGame>(argv);
}