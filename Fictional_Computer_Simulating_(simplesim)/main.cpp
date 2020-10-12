#include <iostream>
#include <iomanip>
#include "simplesim.h"
using namespace std;

/**
 * Main function:
 * Simplesim simulates a computer, one that is capable of executing machine language programs.
 *
 *********************************************************************************************/
int main()
{
	simplesim SLM;                // Creates the SLM object of the simplesim class and initializes it by simplesim method.

	if (SLM.load_program())       // Loads input files into the memory and returns true if the loading was successful.
		SLM.execute_program();    // Runs the SLM program.

	SLM.dump();                   // Print the contents of all five registers and printing the contents of all 100 words of memory.

	return 0;
}