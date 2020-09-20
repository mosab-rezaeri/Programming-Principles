#include <iostream>
#include <iomanip>
#include <vector>
using std::cin;
using std::cout;
using std::cerr;
using std::setw;
using std::endl;
using std::setfill;
using std::vector;


//************************************************************
//                       Bubble Sort
// This function is one of the well-known sorting algorithms.
// Here there is an optimized Bubble sort by saving the last
// swap in each iteration to avoiding useless comparison.
//
//  @array[] : the array that need to be sorted.
//  @n       : the number of the element of the array
//
//************************************************************
void Bubble_Sort(int array[], int n)
{
	int swap;
	int last_swap= 0;	//save the position of the last swap at each loop to make next loop more faster.

	for(int i=n-1; i>0; i--)
	{
		for(int j=0; j<i; j++)
			if(array[j]>array[j+1])		// swapping if it is required
				{
					swap= array[j];
					array[j]= array[j+1];
					array[j+1]= swap;

					last_swap= j;
				}
		i = last_swap + 1;
		last_swap = 0;
	}
}


//************************************************************
//                     Print Sorted Array
// This function prints sorted array based on standard output.
// There are 8 numbers per line that nicely aligned in columns.
// 
//  @array[] : the array that need to be sorted.
//  @n       : the number of the element of the array
//
//************************************************************
void Print_Array(int array[], int n)
{
	// Calculates the digit of the biggest Number to specify enough space for each number.
	int digit = 0;						// digit counter for the largest number 
	int Bigest_Number = array[n-1];		// Given that the array is sorted, array[n-1] is the largest number 
	while (Bigest_Number != 0)
	{
		Bigest_Number = Bigest_Number/10;
		++digit;
	}

	// Prints array in aligned colums:
	for(int i=0; i<n; i++)
	{
		if(i!=0 && i%8==0)
			cout<< endl;
		if(i%8==0)
			cout<< "Row " <<  setfill(' ') << setw(digit) << (i/8)+1 << ":";

		cout<< " " << setfill('0') << setw(digit) << array[i];
	}
	cout<<endl;
}


int main()
{
	int Error = 0;		// It is a flag to check, is there any error in input Data.
	int Check = 0;		// If there is an error in input data Check shows the location of that.
	int Get_Input;
	vector<int> Vec;	// To avoid the problem of "Initializing An Array With Unknown Size" the vector was used. 

	// Get Data from text file:       ./bubble_sort < text1.txt
	// Get Data from user manually :  After inputing the data please press Ctrl+D
	while (cin >> Get_Input)
	{
		Vec.push_back(Get_Input);
		Check++;
	}
	
	// If there is any error, the location of the error will be determined.
	if (!cin.eof())
	{
		Error = 1;
		cerr<<"\n ERROR: Please Enter An Integer (Check Input Number with the \""<< Check <<" Index\") \n";
	}

	// If there is NOT an error, for simplicity, the Vector's data will copied in an array.
	if (Error==0)
	{
		int n = Vec.size();
		int array[n];

		for(int i=0; i<n; i++)
		{
			array[i] = Vec[i];
			cout<< array[i] << endl;
		}

		if (n>0)
		{
			cout<<"You Inputted " << n << " Numbers Correctly.";
			cout<<"\nThe result of the Bubble Sort on your Data is:\n";


			Bubble_Sort (array, n);

			Print_Array (array, n);
		}
		else
			cout<<"Unfortunately, You Don't Have Any Input Data.\n";
	}

	return 0;
}