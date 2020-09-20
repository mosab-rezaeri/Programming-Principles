#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::setw;



/**
 * swaps array[A] with array[B]
 *
 * @param array The array of input numbers.
 * @param A The index of the element A at the array
 * @param B The index of the element B at the array
 ***********************************************************************************/
void Swap(int array[], int A, int B)  
{
	int temp;

	temp     = array[A];
	array[A] = array[B];
	array[B] = temp;
}

/**
 * Finds the correct location of the pivot, Then it will be repeated again on both sides of the pivot.
 *
 * @param array The array of input numbers.
 * @param left  The index of the first element af the array
 * @param right The index of the last element af the array
 ***********************************************************************************/
void Quick_Sort(int array[], int left, int right) 
{
	if (left < right)
	{
		int pivot = array[right];
		int L = (left - 1);

		for (int R = left; R <= right - 1; R++)
		{
			if (array[R] < pivot)
			{
				L++;
				Swap(array, L, R);
			}
		}

		Swap(array, L+1, right);

		// Sort left side of the pivot:
		Quick_Sort(array, left, L);

		// Sort right side of the pivot:
		Quick_Sort(array, L+2, right);
	}
}


/**
 * Calculates the digit.
 * By considering negative numbers, it's possible min had more digit compare to max.
 *
 * @param min The first element at the sorted array.
 * @param max The last  element at the sorted array.
 *
 * @return digit Number of digits of maximum(abs(min) , abs(max).
 ***********************************************************************************/
int Find_Biggest_Digit(int min, int max)
{
	// Calculates the maximum digit at the array:
	int digit = 0;
	int bigest_digit=0;
		
	if (abs(min) > abs(max))
		bigest_digit = min*(-1);
	else
		bigest_digit = max;

	while (bigest_digit != 0)
	{
		bigest_digit = bigest_digit/10;
		++digit;
	}
	return digit;
}


/**
 * Prints sorted array, nicely aligned in columns.
 *
 * @param array The array of input numbers.
 * @param array_length The length of the array (The number of the element at array). 
 *
 * @note  Print the elements of the array in 8 colume.
 ***********************************************************************************/
void Print_Array(int array[], int array_length)
{
	int digit;
	digit = Find_Biggest_Digit(array[0], array[array_length-1]);

	if(array_length<1000)
		cout<<endl;
	
	for(int i=0; i<array_length; i++)
	{
		if(i!=0 && i%8==0)
			cout<< endl;

		cout<< setw(digit+1) << array[i];
	}
	cout<<endl;
}


/**
 * The main function for the Quick Sort algorithm.
 *
 * @note There are 2 error message. (1: Input more than array size, 2: wrong input)
 **********************************************************************************/
int main()
{
	int error = 0;  // error will be equal to 0 if there is no error.
	int input;
	int array_size = 1000;
	int array_index = 0;
	int array[array_size] ;

	while (cin >> input)  // Is there any input?
	{
		if (array_index < array_size)
		{
			array[array_index] = input;
			array_index++;
		}
		else
		{
			error = 1;
			cerr<<"\nERROR: The Maximum Length for the Array is " << array_size << " Numbers.\n";
			break;
		}
	}

	if (!cin.eof() && error!=1) // Is there any wrong input?
	{
		error = 2;
		cerr<<"\nERROR: Please Enter An Integer. Check Input Number with the "<< array_index <<" Index.\n";
	}

	if (error==0 && array_index>0) // Run quick sort if there is no error.
	{

		Quick_Sort(array, 0, array_index-1);
		Print_Array(array, array_index);

	}
	return 0;
}