#include <Leviathan/application.h>
#include <Leviathan/game.h>

class testGame : public game
{
protected:
	virtual void load() override {}

};

int main()
{
	return application::run<testGame>();
}