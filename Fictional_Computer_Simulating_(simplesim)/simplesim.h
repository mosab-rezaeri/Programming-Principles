#ifndef SIMPLESIM_H
#define SIMPLESIM_H

#include <iostream>
#include <iomanip>
using namespace std;

/**
 * Header for Simplesim Class
 *
 * @note The class structure contains an array as memory and five variables as regester.
 *		 All information in the Simplesim is handled in terms of words. A word is a signed
 *		 four-digit decimal (base 10) number.
 *
 *********************************************************************************************/
class simplesim
{

	public:

		// SML instructions that will store at the operation_code register:
		enum insn
		{
			//Initializing:
			NONE		= 00,                    // Initializes with zero after running simplesim() method. 
			//Input and Output Operations:
			READ		= 01,                    // Read a word into a specific memory location.
			WRITE		= 02,                    // Print a word from a specific memory location.
			//Store and Load Operations:
			STORE		= 11,                    // Store the word in the accumulator into a specific memory location.
			LOAD		= 12,                    // Load a word from a specific memory location into the accumulator.
			//Arithmetic Operations:
			ADD			= 21,                    // Add a word in a specific memory location to the word in the accumulator (leave result in accumulator).
			SUBTRACT	= 22,                    // Subtract a word in a specific memory location from the word in the accumulator (leave result in accumulator).
			MULTIPLY	= 23,                    // Multiply a word in a specific memory location by the word in the accumulator (leave result in accumulator).
			DIVIDE		= 24,                    // Divide a word in a specific memory location into the word in the accumulator (leave result in accumulator).
			//Transfer of Control Operations:
			BRANCH		= 31,                    // Branch to a specific memory location.
			BRANCHZERO	= 32,                    // Branch to a specific memory location if the accumulator is zero.
			BRANCHNEG	= 33,                    // Branch to a specific memory location if the accumulator is negative.
			HALT		= 34                     // Halt, i.e., the program has completed its task.
		};


	private:

		int memory[100];            // contains signed four-digit decimal (base 10) words. valid words are between -9999 and 9999, inclusive.
		int accumulator;            // words from memory placed into the accumulator.  
		int instruction_counter;    // holds the memory location of the next instruction to be executed. valid locations are between 0 and 99, inclusive.
		int instruction_register;   // holds a copy of the instruction (a word that was pulled out of memory) that is currently being executed.
		int operand;                // the 2 leftmost digits and sign of the instruction_register.
		insn operation_code;        // the 2 rightmost digits of the instruction_register.


	public:

		/**
		 * Constructors Method:
		 * The default constructor for the simplesim class simulates.
		 *
		 * @note Initializs all five registers with 0 and all 100 words of memory with +4444
		 *
		 *********************************************************************************************/
		simplesim();

		/**
		 * Mutator Method:
		 * loads the SML program into the Simplesim's memory
		 *
		 * @return True for the successful loading and False if there was any error at the loading time.
		 *
		 *********************************************************************************************/
		bool load_program();

		/**
		 * Executes the SML program:
		 * The code for this member function is essentially a loop that executes one instruction at a time.
		 * 
		 * @note Executing an instruction is a two step process; instruction fetch and instruction execute.
		 *       Instruction Fetch: After testing the instruction_counter, splits it by placing its leftmost
		 *       two digits into the operation_code and its rightmost two digits into the operand register.
		 *       Instruction Execute: Recalls the instruction that is in the operation_code register and the
		 *       operand that is in the operand register.
		 *
		 *********************************************************************************************/
		void execute_program();

		/**
		 * Accessor Method:
		 * prints the contents of all five registers and the contents of all 100 words of memory.
		 *
		 *********************************************************************************************/
		void dump() const;

};

#endif /* SIMPLESIM_H */