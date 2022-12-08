// Includes important C++ libraries and headers
#include "Engine.h"

void main(int argc, void** argv[])
{
	// bring in engine class to main
	Engine engine;

	while (!engine.GetWindow()->IsDone()) {
		engine.update();
		engine.draw();
		engine.LateUpdate();
	}
	system("PAUSE");
}