#include "Errors.h"

#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>
using namespace std;

namespace Bengine
{
	void fatalError(string errorString)
	{
		cout << errorString << endl;
		cout << "Enter any key to quit... ";
		int a;
		cin >> a;
		//quits all the SDL systems that we initialized with SDL in it.
		SDL_Quit();
		//0 indicates normal exit
		exit(1);
	}
}