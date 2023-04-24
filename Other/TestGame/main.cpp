#include <Leviathan/application.h>
#include <Leviathan/game.h>

class testGame : public Game
{
protected:
	virtual void Load() override {}

};

int main()
{
	return Application::Run<testGame>();
}