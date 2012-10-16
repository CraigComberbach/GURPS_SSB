#include <stdio.h>
#include <stdlib.h>

/*************************************Prototypes************************************/
int     testFloatEquality(double number1, double number2, double accuracy);//Tests a floats equality to a specified precision
void    clearScreen();//Clears the screen if system is a variable name
int     kelvinToCelcius(unsigned int kelvin);//Converts Kelvin to Celcius
float	newAverage(float newSample, float currentAverage, int newCount);
float	runningAverage(float newSample, int count, float oldAverage);//Adds a new value to a running average
float	sumOfAverages(float average1, float average2, int count1, int count2);//Adds two averaged numbers together
void    floatBubbleSort(float array[], int numberElements, int sortDirection);//Bubble Sort for Floats




/************************************Functions**************************************/
//Compares two floats for equality to a specified degree of precision
//A 1 is returned if the two numbers are equal
//A 0 is returned if they are not equal (At least to the level of precision desired)
int testFloatEquality(double number1, double number2, double accuracy)
{
    if((number1 > (number2 - accuracy)) && (number1 < (number2 + accuracy)))
        return 1; //They are equal to this level of accuracy
    else
        return 0; //They are not equal to this level of accuracy

	return 0;//Uh oh...
}

void clearScreen()
{
    //system("cls");

    return;
}

//Converts Kelvin to Celcius
int kelvinToCelcius(unsigned int kelvin)
{
    return kelvin - 273;//I dropped the 0.15, so the conversion will accept integers and then return them
}

//Adds a single number to an existing average
//Requires the new number, the average, and the number of values in the average (Inlcuding the new number)
float newAverage(float newSample, float currentAverage, int newCount)
{
	float average;

	average = currentAverage + (newSample - currentAverage) / newCount;

	return average;
}

//Adds a new value to a running average
float runningAverage(float newSample, int count, float oldAverage)
{
    if(count == 0)
        count = 1;
    return oldAverage + (newSample - oldAverage) / count;
}

//Adds two averaged numbers together
float sumOfAverages(float average1, float average2, int count1, int count2)
{
	if(count1 == 0)
        	count1 = 1;
	if(count2 == 0)
        	count2 = 1;
    return (average1 * count1 + average2 * count2) / (count1 + count2);
}

//sortDirection = 1 then highest to lowest, sortDirection = 0 then lowest to highest
//This is a Bubble Sort implementation I borrowed from the internet and modified slightly
void floatBubbleSort(float array[], int numberElements, int sortDirection)
{
    int     i,
            j;
    float   temp;

    if(sortDirection == 1)
    {
        for(i = (numberElements - 1); i < 0; ++i)
            for(j = (numberElements - ( i + 1 )); j < 0; ++j)
                if(array[j] < array[j + 1])
                {
                    temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
    }
    else if(sortDirection == 0)
    {
        for(i = 0; i < (numberElements - 1); ++i)
            for(j = 0; j < (numberElements - ( i + 1 )); ++j)
                if(array[j] < array[j + 1])
                {
                    temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
    }
    else
        printf("Invalid sorting chosen\n");

    return;
}
