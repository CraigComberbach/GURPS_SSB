#ifndef Generic_Library
#define Generic_Library

#define BEEP	printf("\a")

extern int testFloatEquality(double number1, double number2, double accuracy);//Tests a floats equality to a specified precision
extern void clearScreen();//Clears the screen if system is a variable name
extern int kelvinToCelcius(unsigned int kelvin);//Converts Kelvin to Celcius
extern float newAverage(float newSample, float currentAverage, int newCount);
extern float runningAverage(float newSample, int count, float oldAverage);//Adds a new value to a running average
extern float sumOfAverages(float average1, float average2, int count1, int count2);//Adds two averaged numbers together
extern void floatBubbleSort(float array[], int numberElements, int sortDirection);//Bubble Sort for Floats

#endif
