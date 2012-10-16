#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "GenericLibrary.h"

#define MT_LEN 			624
#define MT_IA           397
#define MT_IB           (MT_LEN - MT_IA)
#define UPPER_MASK      0x80000000
#define LOWER_MASK      0x7FFFFFFF
#define MATRIX_A        0x9908B0DF
#define TWIST(b,i,j)    ((b)[i] & UPPER_MASK) | ((b)[j] & LOWER_MASK)
#define MAGIC(s)        (((s)&1)*MATRIX_A)

static union
{
    //For using
    unsigned int value;//Probably good for 2^32 unique combos

    //For taps, assumes a 2 byte integer (most likely at least 4 bytes, but I'm being safe)
    struct
    {
        unsigned int bit0 : 1;
        unsigned int bit1 : 1;
        unsigned int bit2 : 1;
        unsigned int bit3 : 1;
        unsigned int bit4 : 1;
        unsigned int bit5 : 1;
        unsigned int bit6 : 1;
        unsigned int bit7 : 1;
        unsigned int bit8 : 1;
        unsigned int bit9 : 1;
        unsigned int bit10 : 1;
        unsigned int bit11 : 1;
        unsigned int bit12 : 1;
        unsigned int bit13 : 1;
        unsigned int bit14 : 1;
        unsigned int bit15 : 1;
    } tap;
} seed;

unsigned int testRandomNum();
void entropy();
void defineSeed(int);
unsigned int randomNum();
unsigned int returnSeed();
unsigned int polyRollDice(int number, int die);
void randomTest();
unsigned long randomMT();
void initializeRandomMT();



//Global variables
int mt_index;
unsigned long mt_buffer[MT_LEN];

void initializeRandomMT()
{
    int i;
    for (i = 0; i < MT_LEN; i++)
        mt_buffer[i] = randomNum();
    mt_index = 0;

    //Cleans out the seed and starts fresh using the Mersenne Twister generated numbers
	for(i = 0; i <= MT_LEN; ++i)
		randomMT();

	return;
}

unsigned long randomMT()
{
    unsigned long * b = mt_buffer;
    int idx = mt_index;
    unsigned long s;
    int i;

    if (idx == MT_LEN*sizeof(unsigned long))
    {
        idx = 0;
        i = 0;
        for (; i < MT_IB; i++) {
            s = TWIST(b, i, i+1);
            b[i] = b[i + MT_IA] ^ (s >> 1) ^ MAGIC(s);
        }
        for (; i < MT_LEN-1; i++) {
            s = TWIST(b, i, i+1);
            b[i] = b[i - MT_IB] ^ (s >> 1) ^ MAGIC(s);
        }

        s = TWIST(b, MT_LEN-1, 0);
        b[MT_LEN-1] = b[MT_IA-1] ^ (s >> 1) ^ MAGIC(s);
    }
    mt_index = idx + sizeof(unsigned long);

    return *(unsigned long *)((unsigned char *)b + idx);
}

unsigned int testRandomNum()
{
    return ++seed.value;
}

unsigned int randomNum()
{
/*
This is an implementation of the Fibinooci Psuedo-Random number generator
Seed needs to be an unsigned Int (Don't ask me why, I'm still a little shakey on the reason myself)
Taps should be bits that are prime numbers for the full 2^n combinations
the number of taps is irrelevant
Bits 0,2,3,5 are the taps for the following Linear Feedback Shift Register
This code is portable between systems as it checks for the size of the int on the current system
*/
    //If seed is 0, set it to this random looking number, cough cough
    //A seed of 0 will not work on the system!
    if(seed.value == 0)
        seed.value = 0x1984;//My birth year, yays

	//Creates a random number
	seed.value =((seed.value >> 1) | ( (seed.tap.bit0 ^ seed.tap.bit2 ^ seed.tap.bit3 ^ seed.tap.bit5) << (sizeof(int)*8-1)));

	//Return psuedo randomly generated number
	return seed.value;
}

//Reseeds from a chaotic source
void entropy()
{
    //replace with a source of entropy, and no, the number of seconds since the epoch does not count
    //I'm looking for a source of unpredictability, a floating A2D port, or temperature readings, etc
    seed.value = 0;//Place holder
    return;
}

//Allows program defined seed for the random number generator
void defineSeed(int s)
{
    seed.value = s;//Seeds my random number generator
    srand(s);//Seeds the compilers random number generator

    return;
}

unsigned int returnSeed()
{
    return seed.value;
}

unsigned int polyRollDice(int number, int die)
{
    unsigned int 	result = 0,
					random;
    static int tally = 0;

    for(;number > 0; --number)
    {
    	random = randomMT();
		if(random == 0)
		{
			printf("Uh oh, PRNG returned a zero!!!");
			BEEP;
		}
		result += (random % die) + 1;
//		result += (randomMT() % die) + 1;
    }

/*********************************************************
    result = seed.value % (number * die + 1);
    ++seed.value;

    if(result < number)
        result = number;

    ++tally;
    printf("Result = %d (Tally = %d)\n", result, tally);

//*********************************************************/
	return result;
}

void randomTest()
{
/*
3	1
4	3
5	6
6	10
7	15
8	21
9	25
10	27
11	27
12	25
13	21
14	15
15	10
16	6
17	3
18	1
216 total rolls needed
*/
    int frequency[19],
        loop;

    for(loop = 0; loop < 19; ++loop)
        frequency[loop] = 0;

    for(loop = 1; loop < 216; ++loop)
    {
        defineSeed(loop);
        frequency[polyRollDice(3,6)]++;
    }
    for(loop = 3; loop < 19; ++loop)
        printf("%d\t%d\n", loop, frequency[loop]);

    scanf("%d", &loop);

    return;
}
