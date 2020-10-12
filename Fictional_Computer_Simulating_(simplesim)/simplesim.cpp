#include <iostream>
#include <iomanip>
#include "simplesim.h"
using namespace std;

// *** Methods and Variables Description are Located at the simlesim.h ***

simplesim::simplesim()
{
	accumulator = 0;
	instruction_counter = 0;
	instruction_register = 0;
	operation_code = NONE;
	operand = 0;

	for (int i = 0; i < 100; ++i)
	{
		memory[i] = 4444;                            // the +4444 is a convention for initialized words of memory
	}

}


bool simplesim::load_program()
{
	int input;                                       // gets the the input value from cin.
	bool loadFlag = true;                            // it will be true until an error occurred.

	while (cin >> input)                             // if there is a input value, returns true and stores it at the input.
	{
		if (input == -99999)                         // -99999 is used at the input file to denote the end of program.
		{
			break;
		}
		else if (instruction_counter >= 100)         // checks size of the input file to be in range the memory capacity
		{
			cerr<<"*** ABEND: pgm load: pgm too large ***" << endl;
			loadFlag = false;
			break;
		}
		else if (input < -9999 || input > +9999)     // checks the input to be in range of the acceptable value  
		{
			cerr<<"*** ABEND: pgm load: invalid word ***" << endl;
			loadFlag = false;
			break;
		}
		else                                         // stores input into the memory
		{
			memory[instruction_counter] = input;
			instruction_counter++;
		}
	}

	return loadFlag;
}

void simplesim::execute_program()
{
	bool done = false;                              // it will be false until the program execution finished without any error.
	bool branching = false;                         // it will be false until one of the three branchin occur.
	instruction_counter = 0;

	while (!done)                                   // run until the program execution finished
	{
		// instruction fetch step:

		if(instruction_counter < 0 && instruction_counter > 99)    // checks the instruction counter to be in range the memory capacity
		{
			cerr<<"*** ABEND: addressability error ***" << endl;
			dump();
			exit(0);
		}

		instruction_register = memory[instruction_counter];

		operation_code = static_cast<insn>(instruction_register / 100); // placs leftmost two digits of the instruction_register into the operation_code.
		
		operand = instruction_register % 100;                           // placs rightmost two digits of the instruction_register into the operation_code.
		if(operand < 0 && operand > 99)
		{
			cerr<<"*** ABEND: addressability error ***" << endl;        // checks the operand to be in range the memory capacity
			dump();
			exit(0);
		}


		// instruction execute step:

		int input;                                                      // gets the the input value from cin.
		int checkResult;                                                // checks the result of the arithmetic operations
		branching = false;
		switch (operation_code)
		{
			case READ:                                                  // Read a word into a specific memory location.
				cin >> input;
				if (input < -9999 || input > +9999)                     // checks the input to be in range of the acceptable value
				{
					cerr<<"*** ABEND: illegal input ***" << endl;
					dump();
					exit(0);
				}
				memory[operand]=input;
				cout << "READ: " << showpos << internal << setfill('0') << setw(5) << memory[operand] << endl;
				break;

			case WRITE:                                                 // Print a word from a specific memory location.
				cout << showpos << internal << setfill('0') << setw(5) << memory[operand] << endl;
				break;

			case STORE:                                                 // Store the word in the accumulator into a specific memory location.
				memory[operand]=accumulator;
				break;

			case LOAD:                                                  // Load a word from a specific memory location into the accumulator.
				accumulator = memory[operand];
				break;

			case ADD:                                                   // Add a word in a specific memory location to the word in the accumulator (leave result in accumulator).
				checkResult = accumulator + memory[operand];
				if (checkResult > +9999)                                // checks the result to be less than the maximum of acceptable value     
				{
					cerr<<"*** ABEND: overflow ***" << endl;
					dump();
					exit(0);
				}
				else if (checkResult < -9999)                           // checks the result to be more than the minimum of acceptable value
				{
					cerr<<"*** ABEND: underflow ***" << endl;
					dump();
					exit(0);
				}
				else
				accumulator = checkResult;
				break;

			case SUBTRACT:                                              // Subtract a word in a specific memory location from the word in the accumulator (leave result in accumulator).
				checkResult = accumulator - memory[operand];
				if (checkResult > +9999)                                // checks the result to be less than the maximum of acceptable value
				{
					cerr<<"*** ABEND: overflow ***" << endl;
					dump();
					exit(0);
				}
				else if (checkResult < -9999)                           // checks the result to be more than the minimum of acceptable value
				{
					cerr<<"*** ABEND: underflow ***" << endl;
					dump();
					exit(0);
				}
				else
				accumulator = checkResult;
				break;

			case MULTIPLY:                                              // Multiply a word in a specific memory location by the word in the accumulator (leave result in accumulator).
				checkResult = accumulator * memory[operand];
				if (checkResult > +9999)                                // checks the result to be less than the maximum of acceptable value
				{
					cerr<<"*** ABEND: overflow ***" << endl;
					dump();
					exit(0);
				}
				else if (checkResult < -9999)                          // checks the result to be more than the minimum of acceptable value
				{
					cerr<<"*** ABEND: underflow ***" << endl;
					dump();
					exit(0);
				}
				else
				accumulator = checkResult;
				break;

			case DIVIDE:                                               // Divide a word in a specific memory location into the word in the accumulator (leave result in accumulator).
				if ( memory[operand] == 0)                             // checks for division by zero
				{
					cerr<<"*** ABEND: attempted division by 0 ***" << endl;
					dump();
					exit(0);
				}
				else
					accumulator = accumulator / memory[operand];
				break;

			case BRANCH:                                               // Branch to a specific memory location.
				instruction_counter = operand;
				branching = true;
				break;

			case BRANCHZERO:                                           // Branch to a specific memory location if the accumulator is zero.
				if (accumulator == 0)
				{
					instruction_counter = operand;
					branching = true;
				}
				break;

			case BRANCHNEG:                                            // Branch to a specific memory location if the accumulator is negative.
				if (accumulator < 0)
				{
					instruction_counter = operand;
					branching = true;
				}
				break;

			case HALT:                                                 // Halt, i.e., the program has completed its task.
				cout << "*** Simplesim execution terminated ***" << endl;
				done = true;
				break;

			default:                                                  // runs just for invalid operand.
				cerr << "*** ABEND: invalid opcode ***" << endl;
				dump();
				exit(0);
				break;
		}

		if (!branching && !done)
			instruction_counter ++;
	}
}

void simplesim::dump() const
{
	cout << "REGISTERS:" << endl;
	cout << "accumulator:            " << showpos   << internal << setfill('0') << setw(5) << accumulator          << endl;   // output example:  +0000
	cout << "instruction_counter:    " << noshowpos << internal << setfill('0') << setw(2) << instruction_counter  << endl;   // output example:  00
	cout << "instruction_register:   " << showpos   << internal << setfill('0') << setw(5) << instruction_register << endl;   // output example:  +0000
	cout << "operation_code:         " << noshowpos << internal << setfill('0') << setw(2) << operation_code       << endl;   // output example:  00
	cout << "operand:                " << noshowpos << internal << setfill('0') << setw(2) << operand              << endl;   // output example:  00

	cout << "\nMEMORY:" << endl;
	cout <<"       0     1     2     3     4     5     6     7     8     9";  // columns header 
	for (int i = 0; i < 100; ++i) // prints all memory words in output.
	{
		if(i%10==0)  // create 10 columns for displaying memory words in output.
		{
			cout << endl;
			cout << noshowpos << setfill('0') << left << setw(2) << i/10;
		}
		cout << " " << showpos << internal << setfill('0') << setw(5) << memory[i];
	}
}
