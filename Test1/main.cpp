#include<iostream>
#include<GL\glew.h>

#include"game.h"
#include"sprite.h"

#include<SDL\SDL.h>

using namespace std;


//SDL works only if main function has the following arguments.

int main(int argc, char** argv)
{
	game g1; //Object for the Game Class.

	g1.run();//The Function that starts everything.


	/**cout << "\n Enter any Key to Continue";
	int tmp;
	cin >> tmp;
	**/
	return 0;
}