#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

//Functions
extern unsigned int testRandomNum();
extern void entropy();
extern void defineSeed(int);
extern unsigned int randomNum();
extern unsigned int returnSeed();
extern unsigned int polyRollDice(int number, int die);
extern void randomTest();
extern unsigned long randomMT();
extern void initializeRandomMT();

#endif // RANDOM_H_INCLUDED
