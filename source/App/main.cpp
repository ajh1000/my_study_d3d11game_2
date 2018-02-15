#include "GameApp.h"

void main()
{
	unique_ptr< GameApp > game = make_unique<GameApp>();

	#ifdef _DEBUG
	bool isConsoleOpend = false;

	if (AllocConsole() == TRUE) {
		isConsoleOpend = true;

		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		cout << std::fixed;
		
	}
	#endif

	try {
		game->run(800,600);
	}
	catch (const std::exception& error) {
		MessageBox(0, error.what(), "Error", MB_OK);
	}

	#ifdef _DEBUG
	if (isConsoleOpend == true) {
		FreeConsole();
	}
	#endif
}