#include"errors.h"
#include<iostream>
#include<string>
#include<SDL\SDL.h>

#include<cstdlib>

using namespace std;

void fatalError(string errorString)
{
	cout << errorString << endl;
	cout << "\n Enter any key to Quit...";
	int tmp;
	cin >> tmp;
	SDL_Quit();
	exit(69); //AYY LMAO
}