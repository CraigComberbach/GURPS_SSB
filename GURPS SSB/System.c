#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GURPS.h"
#include "random.h"
#include "GenericLibrary.h"
#include "SystemSupport.h"

struct  solarSystem step15(struct solarSystem system);//Number of stars
struct  solarSystem step16(struct solarSystem system);//Star Masses
struct  solarSystem step17(struct solarSystem system);//Stellar Age
struct  solarSystem step18(struct solarSystem system);//Stellar Characteristics
struct  solarSystem step19(struct solarSystem system);//Companion Star Orbits
struct  solarSystem step20(struct solarSystem system);//Companion Star Orbits
struct  solarSystem step21(struct solarSystem system);//Placing first planets
struct  solarSystem step22(struct solarSystem system);//Place Planetary Orbits
struct  solarSystem step23(struct solarSystem system);//Place Worlds
struct  solarSystem step24(struct solarSystem system);//Place Moons
struct  solarSystem step25(struct solarSystem system);//World Types
struct  solarSystem step26(struct solarSystem system);//Atmosphere
struct  solarSystem step27(struct solarSystem system);//Hydrographic Coverage
struct  solarSystem step28(struct solarSystem system);//Climate
struct  solarSystem step29(struct solarSystem system);//World Sizes
struct  solarSystem step30(struct solarSystem system);//Dynamic Properties
struct  solarSystem step31(struct solarSystem system);//Geologic Activity
struct  solarSystem step32(struct solarSystem system);//Resources and Habitability

struct solarSystem step15(struct solarSystem system)//Number of Stars
{
    unsigned int random;
    random = polyRollDice(3,6);

    if((random >= 3) && (random <= 10))
        system.numberOfStars = 1;
    else if((random >= 11) && (random <= 15))
        system.numberOfStars = 2;
    else if((random >= 16) && (random <= 18))
        system.numberOfStars = 3;
    else
        printf("\nFailure on line %d (random = %d)\n", __LINE__, random);

    return system;
}

struct solarSystem step16(struct solarSystem system)//Mass of stars
{
    unsigned int    firstRoll,
                    secondRoll;
    int             star;

    //Determine the mass of the stars
    for(star = system.numberOfStars - 1; star >= 0; --star)
    {
        firstRoll = polyRollDice(3,6);
        secondRoll = polyRollDice(3,6);

        //Determine mass of star x
        switch(firstRoll)
        {
            case 3:
                if((secondRoll >= 3) && (secondRoll <= 10))
                    system.stars[star].mass = 2.00;
                else if((secondRoll >= 11) && (secondRoll <= 18))
                    system.stars[star].mass = 1.90;
                else
                    printf("\nFailure on line %d\n", __LINE__);
                break;
            case 4:
                if((secondRoll >= 3) && (secondRoll <= 8))
                    system.stars[star].mass = 1.80;
                else if((secondRoll >= 9) && (secondRoll <= 11))
                    system.stars[star].mass = 1.70;
                else if((secondRoll >= 12) && (secondRoll <= 18))
                    system.stars[star].mass = 1.60;
                else
                    printf("\nFailure on line %d\n", __LINE__);
                break;
            case 5:
                if((secondRoll >= 3) && (secondRoll <= 7))
                    system.stars[star].mass = 1.50;
                else if((secondRoll >= 8) && (secondRoll <= 10))
                    system.stars[star].mass = 1.45;
                else if((secondRoll >= 11) && (secondRoll <= 12))
                    system.stars[star].mass = 1.40;
                else if((secondRoll >= 13) && (secondRoll <= 18))
                    system.stars[star].mass = 1.35;
                else
                    printf("\nFailure on line %d\n", __LINE__);
                break;
            case 6:
                if((secondRoll >= 3) && (secondRoll <= 7))
                    system.stars[star].mass = 1.30;
                else if((secondRoll >= 8) && (secondRoll <= 9))
                    system.stars[star].mass = 1.25;
                else if(secondRoll == 10)
                    system.stars[star].mass = 1.20;
                else if((secondRoll >= 11) && (secondRoll <= 12))
                    system.stars[star].mass = 1.15;
                else if((secondRoll >= 13) && (secondRoll <= 18))
                    system.stars[star].mass = 1.10;
                else
                    printf("\nFailure on line %d\n", __LINE__);
                break;
            case 7:
                if((secondRoll >= 3) && (secondRoll <= 7))
                    system.stars[star].mass = 1.05;
                else if((secondRoll >= 8) && (secondRoll <= 9))
                    system.stars[star].mass = 1.00;
                else if(secondRoll == 10)
                    system.stars[star].mass = 0.95;
                else if((secondRoll >= 11) && (secondRoll <= 12))
                    system.stars[star].mass = 0.90;
                else if((secondRoll >= 13) && (secondRoll <= 18))
                    system.stars[star].mass = 0.85;
                else
                    printf("\nFailure on line %d\n", __LINE__);
                break;
            case 8:
                if((secondRoll >= 3) && (secondRoll <= 7))
                    system.stars[star].mass = 0.80;
                else if((secondRoll >= 8) && (secondRoll <= 9))
                    system.stars[star].mass = 0.75;
                else if(secondRoll == 10)
                    system.stars[star].mass = 0.70;
                else if((secondRoll >= 11) && (secondRoll <= 12))
                    system.stars[star].mass = 0.65;
                else if((secondRoll >= 13) && (secondRoll <= 18))
                    system.stars[star].mass = 0.60;
                else
                    printf("\nFailure on line %d\n", __LINE__);
                break;
            case 9:
                if((secondRoll >= 3) && (secondRoll <= 8))
                    system.stars[star].mass = 0.55;
                else if((secondRoll >= 9) && (secondRoll <= 11))
                    system.stars[star].mass = 0.50;
                else if((secondRoll >= 12) && (secondRoll <= 18))
                    system.stars[star].mass = 0.45;
                else
                    printf("\nFailure on line %d\n", __LINE__);
                break;
            case 10:
                if((secondRoll >= 3) && (secondRoll <= 8))
                    system.stars[star].mass = 0.40;
                else if((secondRoll >= 9) && (secondRoll <= 11))
                    system.stars[star].mass = 0.35;
                else if((secondRoll >= 12) && (secondRoll <= 18))
                    system.stars[star].mass = 0.30;
                else
                    printf("\nFailure on line %d\n", __LINE__);
                break;
            case 11:
                system.stars[star].mass = 0.25;
                break;
            case 12:
                system.stars[star].mass = 0.20;
                break;
            case 13:
                system.stars[star].mass = 0.15;
                break;
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
                system.stars[star].mass = 0.10;
                break;
            default:
                printf("\nFailure on line %d (%d)\n", __LINE__, firstRoll);
                break;
        }
    }

    return system;
}

struct solarSystem step17(struct solarSystem system)//Stellar Age
{
    int temp;

    temp = polyRollDice(3,6);
    //Determines age of solar system
	switch(temp)
	{
        case 3:
            system.stellarAge = 0.0;
            break;
        case 4:
        case 5:
        case 6:
            system.stellarAge = 0.1 + (polyRollDice(1, 6) - 1) * 0.3 + (polyRollDice(1, 6) - 1) * 0.05;
            break;
        case 7:
        case 8:
        case 9:
        case 10:
            system.stellarAge = 2.0 + (polyRollDice(1, 6) - 1) * 0.6 + (polyRollDice(1, 6) - 1) * 0.1;
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            system.stellarAge = 5.6 + (polyRollDice(1, 6) - 1) * 0.6 + (polyRollDice(1, 6) - 1) * 0.1;
            break;
        case 15:
        case 16:
        case 17:
            system.stellarAge = 8.0 + (polyRollDice(1, 6) - 1) * 0.6 + (polyRollDice(1, 6) - 1) * 0.1;
            break;
        case 18:
            system.stellarAge = 10.0 + (polyRollDice(1, 6) - 1) * 0.6 + (polyRollDice(1, 6) - 1) * 0.1;
            break;
        default:
            printf("\nFailure on line %d(Not bounded by 3 to 18)\n", __LINE__);
            break;
	}
    return system;
}

struct solarSystem step18(struct solarSystem system)//Star metrics
{
    int     star,
            temp = 0,
            temperature;
    float   lMax,
            mSpan,
            sSpan,
            gSpan;

    for(star = system.numberOfStars - 1; star >= 0; --star)
    {
        if(system.stars[star].mass < 0.10)
        {
            system.stars[star].lMin = 0.0012;
            temperature = 3100;
            system.stars[star].luminosity = 0.0012;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.15)
        {
            system.stars[star].lMin = 0.0036;
            temperature = 3200;
            system.stars[star].luminosity = 0.0036;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.20)
        {
            system.stars[star].lMin = 0.0079;
            temperature = 3200;
            system.stars[star].luminosity = 0.0079;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.25)
        {
            system.stars[star].lMin = 0.015;
            temperature = 3300;
            system.stars[star].luminosity = 0.015;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.30)
        {
            system.stars[star].lMin = 0.024;
            temperature = 3300;
            system.stars[star].luminosity = 0.024;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.35)
        {
            system.stars[star].lMin = 0.037;
            temperature = 3400;
            system.stars[star].luminosity = 0.037;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.40)
        {
            system.stars[star].lMin = 0.054;
            temperature = 3500;
            system.stars[star].luminosity = 0.054;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.45)
        {
            temperature = 3600;
            system.stars[star].lMin = 0.07;
            lMax = 0.08;
            mSpan = 70;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.50)
        {
            temperature = 3800;
            system.stars[star].lMin = 0.09;
            lMax = 0.011;
            mSpan = 59;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.55)
        {
            temperature = 4000;
            system.stars[star].lMin = 0.11;
            lMax = 0.15;
            mSpan = 50;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.60)
        {
            temperature = 4200;
            system.stars[star].lMin = 0.13;
            lMax = 0.20;
            mSpan = 42;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.65)
        {
            temperature = 4400;
            system.stars[star].lMin = 0.15;
            lMax = 0.25;
            mSpan = 37;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.70)
        {
            temperature = 4600;
            system.stars[star].lMin = 0.19;
            lMax = 0.35;
            mSpan = 30;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.75)
        {
            temperature = 4900;
            system.stars[star].lMin = 0.23;
            lMax = 0.48;
            mSpan = 24;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.80)
        {
            temperature = 5200;
            system.stars[star].lMin = 0.28;
            lMax = 0.65;
            mSpan = 20;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.85)
        {
            temperature = 5400;
            system.stars[star].lMin = 0.36;
            lMax = 0.84;
            mSpan = 17;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.90)
        {
            temperature = 5500;
            system.stars[star].lMin = 0.45;
            lMax = 1.0;
            mSpan = 14;
            system.stars[star].sequence = 'm';
        }
        else if(system.stars[star].mass <= 0.95)
        {
            temperature = 5700;
            system.stars[star].lMin = 0.56;
            lMax = 1.3;
            mSpan = 12;
            sSpan = 1.8;
            gSpan = 1.1;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.00)
        {
            temperature = 5800;
            system.stars[star].lMin = 0.68;
            lMax = 1.6;
            mSpan = 10;
            sSpan = 1.6;
            gSpan = 1.0;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.05)
        {
            temperature = 5900;
            system.stars[star].lMin = 0.87;
            lMax = 1.9;
            mSpan = 8.8;
            sSpan = 1.4;
            gSpan = 0.8;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.10)
        {
            temperature = 6000;
            system.stars[star].lMin = 1.1;
            lMax = 2.2;
            mSpan = 7.7;
            sSpan = 1.2;
            gSpan = 0.7;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.15)
        {
            temperature = 6100;
            system.stars[star].lMin = 1.4;
            lMax = 2.6;
            mSpan = 6.7;
            sSpan = 1.0;
            gSpan = 0.6;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.20)
        {
            temperature = 6300;
            system.stars[star].lMin = 1.7;
            lMax = 3.0;
            mSpan = 5.9;
            sSpan = 0.9;
            gSpan = 0.6;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.25)
        {
            temperature = 6400;
            system.stars[star].lMin = 2.1;
            lMax = 3.5;
            mSpan = 5.2;
            sSpan = 0.8;
            gSpan = 0.5;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.30)
        {
            temperature = 6500;
            system.stars[star].lMin = 2.5;
            lMax = 3.9;
            mSpan = 4.6;
            sSpan = 0.7;
            gSpan = 0.4;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.35)
        {
            temperature = 6600;
            system.stars[star].lMin = 3.1;
            lMax = 4.5;
            mSpan = 4.1;
            sSpan = 0.6;
            gSpan = 0.4;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.40)
        {
            temperature = 6700;
            system.stars[star].lMin = 3.7;
            lMax = 5.1;
            mSpan = 3.7;
            sSpan = 0.6;
            gSpan = 0.3;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.45)
        {
            temperature = 6900;
            system.stars[star].lMin = 4.3;
            lMax = 5.7;
            mSpan = 3.3;
            sSpan = 0.5;
            gSpan = 0.3;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.50)
        {
            temperature = 7000;
            system.stars[star].lMin = 5.1;
            lMax = 6.5;
            mSpan = 3.0;
            sSpan = 0.5;
            gSpan = 0.3;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.60)
        {
            temperature = 7300;
            system.stars[star].lMin = 6.7;
            lMax = 8.2;
            mSpan = 2.5;
            sSpan = 0.4;
            gSpan = 0.2;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.70)
        {
            temperature = 7500;
            system.stars[star].lMin = 8.6;
            lMax = 10;
            mSpan = 2.1;
            sSpan = 0.3;
            gSpan = 0.2;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.80)
        {
            temperature = 7800;
            system.stars[star].lMin = 11.0;
            lMax = 13.0;
            mSpan = 1.8;
            sSpan = 0.3;
            gSpan = 0.2;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 1.90)
        {
            temperature = 8000;
            system.stars[star].lMin = 13.0;
            lMax = 16.0;
            mSpan = 1.5;
            sSpan = 0.2;
            gSpan = 0.1;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else if(system.stars[star].mass <= 2.00)
        {
            temperature = 8200;
            system.stars[star].lMin = 16;
            lMax = 20;
            mSpan = 1.3;
            sSpan = 0.2;
            gSpan = 0.1;
            if(system.stellarAge <= mSpan)
                system.stars[star].sequence = 'm';
            else if(system.stellarAge <= (mSpan + sSpan))
                system.stars[star].sequence = 's';
            else if(system.stellarAge <= (mSpan + sSpan + gSpan))
                system.stars[star].sequence = 'g';
            else
                system.stars[star].sequence = 'w';
        }
        else
            printf("\nFailure on THIS! line %d (%f (%d) on star %d)\n", __LINE__, system.stars[star].mass, temp, star);

        //Determin luminosity and temperature of the star based on the above switch statement
        if(system.stars[star].sequence == 'm')
        {
            if(system.stars[star].luminosity == 0)
                system.stars[star].luminosity = system.stars[star].lMin + ((system.stellarAge / mSpan) * (lMax - system.stars[star].lMin));
            system.stars[star].temperature = temperature;
        }
        else if(system.stars[star].sequence == 's')
        {
            system.stars[star].luminosity = lMax;
            system.stars[star].temperature = temperature - ((system.stellarAge - mSpan) / sSpan) * (temperature - 4800);
        }
        else if(system.stars[star].sequence == 'g')
        {
            system.stars[star].luminosity = lMax * 25;
            system.stars[star].temperature = (polyRollDice(2, 6) - 2) * 200 + 3000;
        }
        else if(system.stars[star].sequence == 'w')
        {
            system.stars[star].luminosity = 0.001;
            system.stars[star].mass = (polyRollDice(2, 6) - 2) * 0.05 + 0.9;
            system.stars[star].temperature = temperature;
            //system.stars[star].temperature = 10000;
        }
        else
            printf("\nFailure on line %d(system.stars[star].sequence = %c)\n", __LINE__, system.stars[star].sequence);

        //Determins spectral Type
        if(system.stars[star].sequence == 'w')
        {
            system.stars[star].spectralType[0] = 'W';
            system.stars[star].spectralType[1] = ' ';
        }
        else if(system.stars[star].temperature == 0.0)
            printf("\nFailure on line %d\n", __LINE__);
        else if(system.stars[star].temperature < 3000)
            printf("\nFailure on line %d (Temperature = %f)\n", __LINE__, system.stars[star].temperature);
        else if(system.stars[star].temperature < 3200)
        {
            system.stars[star].spectralType[0] = 'M';
            system.stars[star].spectralType[1] = '7';
        }
        else if((system.stars[star].temperature >= 3200) && (system.stars[star].temperature < 3300))
        {
            if(system.stars[star].mass < 0.15)
            {
                system.stars[star].spectralType[0] = 'M';
                system.stars[star].spectralType[1] = '6';
            }
            else if(system.stars[star].mass < 0.20)
            {
                system.stars[star].spectralType[0] = 'M';
                system.stars[star].spectralType[1] = '5';
            }
            else//This is for Giants
            {
                system.stars[star].spectralType[0] = 'M';
                system.stars[star].spectralType[1] = '5';
            }
        }
        else if((system.stars[star].temperature >= 3300) && (system.stars[star].temperature < 3400))
        {
            system.stars[star].spectralType[0] = 'M';
            system.stars[star].spectralType[1] = '4';
        }
        else if((system.stars[star].temperature >= 3400) && (system.stars[star].temperature < 3500))
        {
            system.stars[star].spectralType[0] = 'M';
            system.stars[star].spectralType[1] = '3';
        }
        else if((system.stars[star].temperature >= 3500) && (system.stars[star].temperature < 3600))
        {
            system.stars[star].spectralType[0] = 'M';
            system.stars[star].spectralType[1] = '2';
        }
        else if((system.stars[star].temperature >= 3600) && (system.stars[star].temperature < 3800))
        {
            system.stars[star].spectralType[0] = 'M';
            system.stars[star].spectralType[1] = '1';
        }
        else if((system.stars[star].temperature >= 3800) && (system.stars[star].temperature < 4000))
        {
            system.stars[star].spectralType[0] = 'M';
            system.stars[star].spectralType[1] = '0';
        }
        else if((system.stars[star].temperature >= 4000) && (system.stars[star].temperature < 4200))
        {
            system.stars[star].spectralType[0] = 'K';
            system.stars[star].spectralType[1] = '8';
        }
        else if((system.stars[star].temperature >= 4200) && (system.stars[star].temperature < 4400))
        {
            system.stars[star].spectralType[0] = 'K';
            system.stars[star].spectralType[1] = '6';
        }
        else if((system.stars[star].temperature >= 4400) && (system.stars[star].temperature < 4600))
        {
            system.stars[star].spectralType[0] = 'K';
            system.stars[star].spectralType[1] = '5';
        }
        else if((system.stars[star].temperature >= 4600) && (system.stars[star].temperature < 4900))
        {
            system.stars[star].spectralType[0] = 'K';
            system.stars[star].spectralType[1] = '4';
        }
        else if((system.stars[star].temperature >= 4900) && (system.stars[star].temperature < 5200))
        {
            system.stars[star].spectralType[0] = 'K';
            system.stars[star].spectralType[1] = '2';
        }
        else if((system.stars[star].temperature >= 5200) && (system.stars[star].temperature < 5400))
        {
            system.stars[star].spectralType[0] = 'K';
            system.stars[star].spectralType[1] = '0';
        }
        else if((system.stars[star].temperature >= 5400) && (system.stars[star].temperature < 5500))
        {
            system.stars[star].spectralType[0] = 'G';
            system.stars[star].spectralType[1] = '8';
        }
        else if((system.stars[star].temperature >= 5500) && (system.stars[star].temperature < 5700))
        {
            system.stars[star].spectralType[0] = 'G';
            system.stars[star].spectralType[1] = '6';
        }
        else if((system.stars[star].temperature >= 5700) && (system.stars[star].temperature < 5800))
        {
            system.stars[star].spectralType[0] = 'G';
            system.stars[star].spectralType[1] = '4';
        }
        else if((system.stars[star].temperature >= 5800) && (system.stars[star].temperature < 5900))
        {
            system.stars[star].spectralType[0] = 'G';
            system.stars[star].spectralType[1] = '2';
        }
        else if((system.stars[star].temperature >= 5900) && (system.stars[star].temperature < 6000))
        {
            system.stars[star].spectralType[0] = 'G';
            system.stars[star].spectralType[1] = '1';
        }
        else if((system.stars[star].temperature >= 6000) && (system.stars[star].temperature < 6100))
        {
            system.stars[star].spectralType[0] = 'G';
            system.stars[star].spectralType[1] = '0';
        }
        else if((system.stars[star].temperature >= 6100) && (system.stars[star].temperature < 6300))
        {
            system.stars[star].spectralType[0] = 'F';
            system.stars[star].spectralType[1] = '9';
        }
        else if((system.stars[star].temperature >= 6300) && (system.stars[star].temperature < 6400))
        {
            system.stars[star].spectralType[0] = 'F';
            system.stars[star].spectralType[1] = '8';
        }
        else if((system.stars[star].temperature >= 6400) && (system.stars[star].temperature < 6500))
        {
            system.stars[star].spectralType[0] = 'F';
            system.stars[star].spectralType[1] = '7';
        }
        else if((system.stars[star].temperature >= 6500) && (system.stars[star].temperature < 6700))
        {
            system.stars[star].spectralType[0] = 'F';
            system.stars[star].spectralType[1] = '5';
        }
        else if((system.stars[star].temperature >= 6700) && (system.stars[star].temperature < 6900))
        {
            system.stars[star].spectralType[0] = 'F';
            system.stars[star].spectralType[1] = '4';
        }
        else if((system.stars[star].temperature >= 6900) && (system.stars[star].temperature < 7000))
        {
            system.stars[star].spectralType[0] = 'F';
            system.stars[star].spectralType[1] = '3';
        }
        else if((system.stars[star].temperature >= 7000) && (system.stars[star].temperature < 7300))
        {
            system.stars[star].spectralType[0] = 'F';
            system.stars[star].spectralType[1] = '2';
        }
        else if((system.stars[star].temperature >= 7300) && (system.stars[star].temperature < 7500))
        {
            system.stars[star].spectralType[0] = 'F';
            system.stars[star].spectralType[1] = '0';
        }
        else if((system.stars[star].temperature >= 7500) && (system.stars[star].temperature < 7800))
        {
            system.stars[star].spectralType[0] = 'A';
            system.stars[star].spectralType[1] = '9';
        }
        else if((system.stars[star].temperature >= 7800) && (system.stars[star].temperature < 8000))
        {
            system.stars[star].spectralType[0] = 'A';
            system.stars[star].spectralType[1] = '7';
        }
        else if((system.stars[star].temperature >= 8000) && (system.stars[star].temperature < 8200))
        {
            system.stars[star].spectralType[0] = 'A';
            system.stars[star].spectralType[1] = '6';
        }
        else if(system.stars[star].temperature >= 8000)
        {
            system.stars[star].spectralType[0] = 'A';
            system.stars[star].spectralType[1] = '5';
        }
        else
        {
            printf("\nFailure on line %d(%f)\n", __LINE__, system.stars[star].temperature);
        }

        system.stars[star].radius = (155000 * sqrt(system.stars[star].luminosity)) / pow(system.stars[star].temperature, 2);
    }//End of star in the for star...Yeah "bass ackwards"

//Determine the primary star
    if((system.stars[0].mass >= system.stars[1].mass) && (system.stars[0].mass >= system.stars[2].mass))
        system.primaryStar = 1;
    else if((system.stars[1].mass >= system.stars[0].mass) && (system.stars[1].mass >= system.stars[2].mass))
        system.primaryStar = 2;
    else if((system.stars[2].mass >= system.stars[0].mass) && (system.stars[2].mass >= system.stars[1].mass))
        system.primaryStar = 3;
    else
        printf("\nFailure on line %d\n", __LINE__);

	return system;
}

struct solarSystem step19(struct solarSystem system)//Star Orbits
{
    int star,
        temp;

    for(star = system.numberOfStars - 1; star >= 0; --star)
    {
        //Average orbit around the primary star
        if((system.primaryStar - 1) == star)
        {
            system.stars[star].averageOrbit = 0.0;//The primary star does not orbit around itself
            system.stars[star].eccentricity = 0.0;//Primary star is not eccentric
            system.stars[star].minOrbit = 0.0;//Because its not eccentric and has no orbit
            system.stars[star].maxOrbit = 0.0;//Because its not eccentric and has no orbit
        }
        else
        {
            //The last star in a trinary system gets an additional +6
            temp = polyRollDice(3, 6);
            if(star == 2)
                temp += 6;

            //Ensures that the dice fall within a range, because it may go over(For trinary star systems)!
            if(temp > 18)
                temp = 18;

			//Determines if there is an ungenerated companion star for this star
			if(temp >= 11)
				system.stars[star].companionFlag = 1;//Oops, there was

            //If it is a trinary system, one of stars has a greater chance of being much further out from the primary
            switch(temp)
            {
                case 3:
                case 4:
                case 5:
                case 6:
                    system.stars[star].averageOrbit = polyRollDice(2, 6) * 0.05;
                    break;
                case 7:
                case 8:
                case 9:
                    system.stars[star].averageOrbit = polyRollDice(2, 6) * 0.5;
                    break;
                case 10:
                    system.stars[star].averageOrbit = polyRollDice(2, 6) * 2;
                    break;
                case 11:
                    system.stars[star].averageOrbit = polyRollDice(2, 6) * 2;
                    break;
                case 12:
                case 13:
                case 14:
                    system.stars[star].averageOrbit = polyRollDice(2, 6) * 10;
                    break;
                case 15:
                case 16:
                case 17:
                case 18:
                    system.stars[star].averageOrbit = polyRollDice(2, 6) * 50;
                    break;
                default:
                    printf("\nFailure on line %d\n", __LINE__);
                    break;

            }

            //Determines eccentricity of the star (0 is circular and the closer to 1 it is, the more elliptical it is
            if(temp <= 6)
                temp = polyRollDice(3, 6) - 6;
            else if((temp > 6) && (temp <= 9))
                temp = polyRollDice(3, 6) - 4;
            else if((temp > 9) && (temp <= 11))
                temp = polyRollDice(3, 6) - 2;

            //Ensures that the minimum is a 3
            if(temp < 3)
                temp = 3;

            //Sets the eccentricity
            switch(temp)
            {
                case 3:
                    system.stars[star].eccentricity = 0.0;
                    break;
                case 4:
                    system.stars[star].eccentricity = 0.1;
                    break;
                case 5:
                    system.stars[star].eccentricity = 0.2;
                    break;
                case 6:
                    system.stars[star].eccentricity = 0.3;
                    break;
                case 7:
                case 8:
                    system.stars[star].eccentricity = 0.4;
                    break;
                case 9:
                case 10:
                case 11:
                    system.stars[star].eccentricity = 0.5;
                    break;
                case 12:
                case 13:
                    system.stars[star].eccentricity = 0.6;
                    break;
                case 14:
                case 15:
                    system.stars[star].eccentricity = 0.7;
                    break;
                case 16:
                    system.stars[star].eccentricity = 0.8;
                    break;
                case 17:
                    system.stars[star].eccentricity = 0.9;
                    break;
                case 18:
                    system.stars[star].eccentricity = 0.95;
                    break;
                default:
                    printf("\nFailure on line %d\n", __LINE__);
                    break;
            }

            //Determines Min and Max orbits for the star based on the code above
            system.stars[star].minOrbit = (1 - system.stars[star].eccentricity) * system.stars[star].averageOrbit;
            system.stars[star].maxOrbit = (1 + system.stars[star].eccentricity) * system.stars[star].averageOrbit;
        }
    }
    return system;
}

struct solarSystem step20(struct solarSystem system)//Limits
{
    int     loop;
    float   temp;

    for(loop = 0; loop < system.numberOfStars; ++loop)
    {
        //Inner Limit Radius
        system.stars[loop].innerLimitRadius = 0.1 * system.stars[loop].mass;
        temp = 0.01 * sqrt((double)system.stars[loop].luminosity);
        if(temp > system.stars[loop].innerLimitRadius)
            system.stars[loop].innerLimitRadius = temp;

        //Ouster limit radius
        system.stars[loop].outerLimitRadius = 40 * system.stars[loop].mass;

        //Forbidden zones
        system.stars[loop].innerForbiddenZone = system.stars[loop].minOrbit / 3;
        system.stars[loop].outerForbiddenZone = system.stars[loop].maxOrbit * 3;
        if(system.stars[loop].innerForbiddenZone < system.stars[loop].innerLimitRadius)
        {
            if(!testFloatEquality(system.stars[loop].innerForbiddenZone, 0.0, 0.01))
                system.stars[loop].forbiddenFlag = 1; //No planets
        }
        else if(system.stars[loop].innerForbiddenZone > system.stars[loop].innerLimitRadius)
            system.stars[loop].forbiddenFlag = 2; //Planets for each sun
        else if(system.stars[loop].outerForbiddenZone < system.stars[loop].outerLimitRadius)
            system.stars[loop].forbiddenFlag = 3; //Planets circle this one and its companion
        else if(system.stars[loop].outerForbiddenZone > system.stars[loop].outerLimitRadius)
            system.stars[loop].forbiddenFlag = 4; //Planets for both suns

        //Snow line
        system.stars[loop].snowLine = 4.85 * sqrt((double)system.stars[loop].lMin);
    }

    return system;
}

struct solarSystem step21(struct solarSystem system)//Placing first planets
{
    int roll,
        star;

    for(star = 0; star < system.numberOfStars; ++star)
    {
        //Check for forbiddeness first
        if(system.stars[star].forbiddenFlag == 1)
        {
            system.stars[star].gasGiantFlag = 1;
            continue;//No planets for you, or at least gas giants as of yet
        }

        //Determine Gas Giant setup
        if((system.stars[star].snowLine > system.stars[star].innerForbiddenZone) && (system.stars[star].snowLine < system.stars[star].outerForbiddenZone))
            system.stars[star].gasGiantFlag = 1;
        else
        {
            roll = polyRollDice(3,6);
            switch(roll)
            {
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                    system.stars[star].gasGiantFlag = 1;
                    break;
                case 11:
                case 12:
                    system.stars[star].gasGiantFlag = 2;
                    break;
                case 13:
                case 14:
                    system.stars[star].gasGiantFlag = 3;
                    break;
                case 15:
                case 16:
                case 17:
                case 18:
                    system.stars[star].gasGiantFlag = 4;
                    break;
                default:
                    printf("\nFailure on line %d\n", __LINE__);
                    break;
            }
        }

        //t laying the gas giant layout
        switch(system.stars[star].gasGiantFlag)
        {
            case 0://It should not be in an initialized state, this is a failure
                printf("\nInitialized failure on line %d\n", __LINE__);
                break;
            case 1://No Gas Giants
                break;
            case 2://Conventional Arrangement
                system.stars[star].planets[0].orbit = (((polyRollDice(2,6) - 2) * 0.05) + 1.0) * system.stars[star].snowLine;
                break;
            case 3://Eccentric Arrangement
                  system.stars[star].planets[0].orbit = (polyRollDice(1,6) * 0.125) * system.stars[star].snowLine;
                break;
            case 4://Epistellar Arrangement
                system.stars[star].planets[0].orbit = (polyRollDice(3,6) * 0.1) * system.stars[star].innerLimitRadius;
                break;
            default:
                printf("\nFailure on line %d\n", __LINE__);
                break;
        }
        if((system.stars[star].planets[1].orbit > system.stars[star].innerForbiddenZone) && (system.stars[star].planets[1].orbit < system.stars[star].outerForbiddenZone))
                    system.stars[star].planets[1].orbit = 0;//Oops, it appears it was illegal, oh well, revoke the orbit!

        //Assign the first gas giant orbit, this has significance later on as to which was the first gas giant!
        system.stars[star].firstGasGiant = system.stars[star].planets[1].orbit;
    }
    return system;
}

struct solarSystem step22(struct solarSystem system)//Place Planetary Orbits
{
    int     planetLoop,
            star;
    float   previousOrbit;

    //Produce results for each star
    for(star = 0; star < system.numberOfStars; ++star)
    {
        if(system.stars[star].forbiddenFlag == 1)
        {
            system.stars[star].numberOfPlanets = 0;
            continue;//No planets for you
        }

        switch(system.stars[star].gasGiantFlag)
        {
            //1 = No Gas Giants, 2 = Conventional Gas Giant, 3 = Eccentric Gas Giant, 4 = Epistellar Gas Giant
            case 1://With no Gas Giants, the orbit radii is specially determined
                //Special outermost location
                planetLoop = 0;//Initializes where to t from
                if((system.stars[star].outerLimitRadius < system.stars[star].innerForbiddenZone) || (system.stars[star].outerLimitRadius > system.stars[star].outerForbiddenZone))
                    previousOrbit = system.stars[star].outerLimitRadius / ((polyRollDice(1,6) * 0.05) + 1);//Start at a point close to the outer legal limit
                else
                    previousOrbit = system.stars[star].innerForbiddenZone / ((polyRollDice(1,6) * 0.05) + 1);//Start at a point close to the inner forbidden limit

                 system.stars[star].planets[planetLoop].orbit = previousOrbit;//Assign this as the first orbit
                ++planetLoop;

                //Work inward until either the inner limit radius or a forbidden zone is encountered
                for(;; ++planetLoop)
                {
                    previousOrbit = nextOrbit(previousOrbit, 0);//Generate the next orbit inwards

                    if(previousOrbit > system.stars[star].innerLimitRadius)//If we aren't too close to the sun
                    {
                        if((previousOrbit > system.stars[star].outerForbiddenZone) || (previousOrbit < system.stars[star].innerForbiddenZone))//And we aren't in a forbidden zone
                            system.stars[star].planets[planetLoop].orbit = previousOrbit;//Assign the orbit and get ready to go again
                    }
                    else
                        break;//Get out once we are too close too the sun
                }
                break;
            case 2:
            case 3:
            case 4://If the system has Gas giants then it can use the following
                //Going outwards. But from what?! From this -> system.planets[star].orbit[0]
                previousOrbit = system.stars[star].planets[0].orbit;//The ting point for going either way

                //Move Outwards
                for(planetLoop = 1; planetLoop < MAX_PLANETS; ++planetLoop)//0 is already taken by a Gas giant, don't test it
                {
                    previousOrbit = nextOrbit(previousOrbit, 1);//Generate the next legal orbit outwards

                    if(previousOrbit < system.stars[star].outerLimitRadius)//If we aren't too far from the sun
                    {
                        if((previousOrbit > system.stars[star].outerForbiddenZone) || (previousOrbit < system.stars[star].innerForbiddenZone))//And we aren't in a forbidden zone
                            system.stars[star].planets[planetLoop].orbit = previousOrbit;//Assign the orbit and get ready to go again
                    }
                    else
                        break;//Get out once we are too close too the sun
                }

                //Going inwards, DO NOT set planetLoop, keep using the last number produced from the previous step!
                previousOrbit = system.stars[star].planets[1].orbit;//The ting point for going either way

                for(;planetLoop < MAX_PLANETS; ++planetLoop)
                {
                    previousOrbit = nextOrbit(previousOrbit, 0);//Generate the next legal orbit outwards

                    if(previousOrbit > system.stars[star].innerLimitRadius)//If we aren't too close to the sun
                    {
                        if((previousOrbit > system.stars[star].outerForbiddenZone) || (previousOrbit < system.stars[star].innerForbiddenZone))//And we aren't in a forbidden zone
                            system.stars[star].planets[planetLoop].orbit = previousOrbit;//Assign the orbit and get ready to go again
                    }
                    else
                        break;//Get out once we are too close too the sun
                }
                break;
            default:
                printf("\nFailure on line %d\n", __LINE__);
                break;
        }

        //Initialize (Just in case)
        system.stars[star].numberOfPlanets = 0;

        //Count the valid orbits for the total number of planets
        for(planetLoop = 0; planetLoop < MAX_PLANETS; ++planetLoop)
        {
            if(system.stars[star].planets[planetLoop].orbit > 0.0)
                system.stars[star].numberOfPlanets++;
        }
    }

    //Function sorts the orbits so that they are in order
    system = orbitSort(system);

    return system;
}

struct solarSystem step23(struct solarSystem system)//Place Worlds
{
    int orbit,
        planet,
        pastSnowLineFlag,
        roll;

    for(orbit = 0; orbit < system.numberOfStars; ++orbit)
    {
        //Labels the first Gas Giant as a gas giant
        if(system.stars[orbit].gasGiantFlag != 1)
        {
            for(planet = 0; ; ++planet)
            {
                if(testFloatEquality(system.stars[orbit].planets[planet].orbit, system.stars[orbit].firstGasGiant, 0.001))
                {
                    system.stars[orbit].planets[planet].type = 'G';
                    break;
                }
                else if(planet > MAX_PLANETS)
                {
                    printf("\nFailure on line %d (system.stars[%d].firstGasGiant = %0.2f)", __LINE__, orbit, system.stars[orbit].firstGasGiant);
                    break;
                }
            }

            //Now to generate Gas Giants beyond the snow line
            pastSnowLineFlag = 0;//Resets the flag for each orbit, used to determine size of gas giants in a later step

			//Ends when it enters a non valid orbit
			for(planet = 0; system.stars[orbit].planets[planet].orbit > system.stars[orbit].planets[planet-1].orbit; ++planet)//As long as the current orbit is greater than the previous orbit, keep going
            {
                if(system.stars[orbit].planets[planet].orbit > system.stars[orbit].snowLine)//for each orbit past snowline, increment by 1
                    ++pastSnowLineFlag;

                //Don't delete this AGAIN!!! It is what is used to determine if an orbit is a gas giant or not
                roll = polyRollDice(3,6);//Roll 3d6

                if(system.stars[orbit].planets[planet].orbit < system.stars[orbit].snowLine)//Gas Giants inside the snowline
                {
                    //Chance for Epistellar and Epicentric gas giants inside the snowline
                    switch(system.stars[orbit].gasGiantFlag)
                    {
                        case 1:
                        case 2:
                            break;
                        case 3://Eccentric
                            if(roll <= 8)
                                system.stars[orbit].planets[planet].type = 'G';//Its a Gas Giant
                            break;
                        case 4://Epistellar
                            if(roll <= 6)
                                system.stars[orbit].planets[planet].type = 'G';//Its a Gas Giant
                            break;
                        default:
                            printf("\nFailure on line %d\n", __LINE__);
                            break;
                    }
                }
                else//Gas giants beyond the snowline
                {
                    switch(system.stars[orbit].gasGiantFlag)
                    {
                        case 1:
                            break;
                        case 2:
                            if(roll <= 15)
                                system.stars[orbit].planets[planet].type = 'G';
                            break;
                        case 3:
                        case 4://Same for flags 3 & 4
                            if(roll <= 14)
                                system.stars[orbit].planets[planet].type = 'G';//Its a Gas Giant
                            break;
                        default:
                            printf("\nFailure on line %d\n", __LINE__);
                            break;
                    }
                }

                //If it is a gas giant as determined in the last few lines of code, then assign a size to it
                if(system.stars[orbit].planets[planet].type == 'G')
                {
                    //This ts the die rolling toward determining the size of the gas giants
                    roll = polyRollDice(3,6);//Roll 3d6

                    //Only gas giants just past the snow line or inside the snow line recieve a +4 size bonus
                    if(pastSnowLineFlag <= 1)//A 1 is just past the snowline, a 0 means before it. Higher numbers are well beyond the snow line
                        roll += 4;

                    //Size selector
                    switch(roll)
                    {
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                        case 10:
                            system.stars[orbit].planets[planet].size = 'S';//Small sized
                            break;
                        case 11:
                        case 12:
                        case 13:
                        case 14:
                        case 15:
                        case 16:
                            system.stars[orbit].planets[planet].size = 'M';//Medium Sized
                            break;
                        case 17:
                        case 18:
                        case 19:
                        case 20:
                        case 21:
                        case 22:
                            system.stars[orbit].planets[planet].size = 'L';//Large sized
                            break;
                        default:
                            printf("\nFailure on line %d\n", __LINE__);
                            break;
                    }
                }
            }
        }
    }

    //Now assign a type and size to each orbit
    for(orbit = 0; orbit < system.numberOfStars; ++orbit)
    {
        //Place everything else into the orbits!
        for(planet = 0; planet < system.stars[orbit].numberOfPlanets; ++planet)
        {
            if(system.stars[orbit].planets[planet].type != 'G')//If its not a Gas Giant, then determine what it is
            {

                //Base roll, modifiers to follow
                roll = polyRollDice(3, 6);

                //-6 if adjacent to a forbidden zone
                if(!testFloatEquality(system.stars[orbit].innerForbiddenZone, 0.0, 0.01) || !testFloatEquality(system.stars[orbit].outerForbiddenZone, 0.0, 0.01))//Precludes primary star
                    if((planet == 1) || (planet == system.stars[orbit].numberOfPlanets))//First and last planets only
                        if((system.stars[orbit].outerForbiddenZone < system.stars[orbit].outerLimitRadius) || (system.stars[orbit].innerForbiddenZone > system.stars[orbit].innerLimitRadius))
                            roll -= 6;

                //-6 if the inside orbit is a gas giant
                if(system.stars[orbit].planets[planet-1].type == 'G')
                    roll -= 6;

                //-3 if the outside orbit is a gas giant
                if((system.stars[orbit].planets[planet+1].type == 'G') && ((planet + 1) <= system.stars[orbit].numberOfPlanets))
                    roll -= 3;

                //-3 if adjacent to either an inner or outer limit radius
                if(planet == 1)//Inner Limit
                    roll -= 3;
                if(planet == system.stars[orbit].numberOfPlanets)//Outer Limits: Please Standby
                    roll -= 3;

                //With a potential minimum of -15 still being valid, its time to bound it to manageable numbers
                if(roll < 3)
                    roll = 3;

                //Orbital contents table!
                switch(roll)
                {
                    case 3://Empty Orbit
                        system.stars[orbit].planets[planet].type = 'E';
                        system.stars[orbit].planets[planet].size = 'E';
                        break;
                    case 4:
                    case 5:
                    case 6:
                        system.stars[orbit].planets[planet].type = 'A';//Asteroid Belt
                        system.stars[orbit].planets[planet].size = 'B';//N/A
                        break;
                    case 7:
                    case 8:
                        system.stars[orbit].planets[planet].size = 'T';//Tiny
                        break;
                    case 9:
                    case 10:
                    case 11:
                        system.stars[orbit].planets[planet].size = 'S';//Small
                        break;
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                        system.stars[orbit].planets[planet].size = 'M';//Medium or standard
                        break;
                    case 16:
                    case 17:
                    case 18:
                        system.stars[orbit].planets[planet].size = 'L';//Large
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);
                        break;
                }
            }
        }
    }

    return system;
}

struct solarSystem step24(struct solarSystem system)//Place Moons
{
    int orbit,
        planet,
        roll,
        loop;

    for(orbit = 0; orbit < system.numberOfStars; ++orbit)
    {
        for(planet = 0; planet < system.stars[orbit].numberOfPlanets; ++planet)
        {
            if(system.stars[orbit].planets[planet].type == 'G')
            {
                //First class of moon
                roll = polyRollDice(2,6);
                if(system.stars[orbit].planets[planet].orbit < 0.1)//Determine number of moons
                    roll -= 10;
                else if(system.stars[orbit].planets[planet].orbit < 0.5)
                    roll -= 8;
                else if(system.stars[orbit].planets[planet].orbit < 0.75)
                    roll -= 6;
                else if(system.stars[orbit].planets[planet].orbit < 1.5)
                    roll -= 3;
                else
                    roll +=0;

                //Determine rings
                if(roll < 6)
                    system.stars[orbit].planets[planet].rings = 'N';//There are no rings
                else if((roll >= 6) && (roll < 10))
                    system.stars[orbit].planets[planet].rings = 'F';//Yes there are faint rings
                else if(roll >= 10)
                    system.stars[orbit].planets[planet].rings = 'S';//There are spectacular rings!

                if(roll < 0)
                    roll = 0;

                system.stars[orbit].planets[planet].innerMoonlets = roll;

                //Second class of moon
                roll = polyRollDice(1,6);
                //Determine number of moons, if less than 0.1, don't bother making a second moon group
                if(system.stars[orbit].planets[planet].orbit < 0.1)
                    roll -= 20;
                else if(system.stars[orbit].planets[planet].orbit < 0.5)
                    roll -= 5;
                else if(system.stars[orbit].planets[planet].orbit < 0.75)
                    roll -= 4;
                else if(system.stars[orbit].planets[planet].orbit < 1.5)
                    roll -= 1;
                else
                    roll += 0;

                if(roll < 0)
                    roll = 0;

                system.stars[orbit].planets[planet].majourMoons = roll;

                //Third class of moon
                roll = polyRollDice(1,6);
                //Determine number of moons, if less than 0.5, don't bother making a second moon group
                if(system.stars[orbit].planets[planet].orbit < 0.5)
                    roll -= 20;
                else if(system.stars[orbit].planets[planet].orbit < 0.75)
                    roll -= 5;
                else if(system.stars[orbit].planets[planet].orbit < 1.5)
                    roll -= 4;
                else if(system.stars[orbit].planets[planet].orbit < 3.0)
                    roll -= 1;
                else
                    roll += 0;

                if(roll < 0)
                    roll = 0;

                system.stars[orbit].planets[planet].outerMoonlets = roll;
            }
            else if((system.stars[orbit].planets[planet].type == 'A') || (system.stars[orbit].planets[planet].type == 'E'))
                continue;
            else//This is where terrestrial moons are generated!
            {
                //Ensures that all planets get assigned this
                system.stars[orbit].planets[planet].rings = 'N';//There are no rings

                if(system.stars[orbit].planets[planet].orbit > 0.5)//Don't bother with planets with orbits less than 0.5
                {
                    roll = polyRollDice(1,6) - 4;//Majour Moons

                    //Orbital radius affects how many moons it can have
                    if(system.stars[orbit].planets[planet].orbit < 0.75)
                        roll -= 3;
                    else if(system.stars[orbit].planets[planet].orbit < 1.5)
                        roll -= 1;

                    //Size of the planet affects how many moons it can have
                    if(system.stars[orbit].planets[planet].size == 'T')
                        roll -= 2;
                    else if(system.stars[orbit].planets[planet].size == 'S')
                        roll -= 1;
                    else if(system.stars[orbit].planets[planet].size == 'L')
                        roll += 1;
                    else if(system.stars[orbit].planets[planet].size == 'M')
                        roll = roll;
                    else
                        printf("\nFailure on line %d (system.stars[%d].planets[%d].size = %c)\n", __LINE__, orbit, planet, system.stars[orbit].planets[planet].size);

                    //If no moons then moonlets, or other way around!
                    if(roll <= 0)
                    {
                        system.stars[orbit].planets[planet].majourMoons = 0;//Sorry no moons for you

                        roll = polyRollDice(1,6) - 2;//Moonlets
                        //Orbital radius affects how many moonlets it can have
                        if(system.stars[orbit].planets[planet].orbit < 0.75)
                            roll -= 3;
                        else if((system.stars[orbit].planets[planet].orbit > 0.75) && (system.stars[orbit].planets[planet].orbit < 1.5))
                            roll -= 1;

                        //Size of the planet affects how many moons it can have
                        if(system.stars[orbit].planets[planet].size == 'T')
                            roll -= 2;
                        else if(system.stars[orbit].planets[planet].size == 'S')
                            roll -= 1;
                        else if(system.stars[orbit].planets[planet].size == 'L')
                            roll += 1;
                        else if(system.stars[orbit].planets[planet].size == 'M')
                            roll = roll;
                        else
                            printf("\nFailure on line %d(system.stars[%d].planets[%d].size = %c)\n", __LINE__, orbit, planet, system.stars[orbit].planets[planet].size);

                        if(roll < 0)
                            roll = 0;

                        system.stars[orbit].planets[planet].innerMoonlets = roll;
                    }
                    else//There are moons!
                        system.stars[orbit].planets[planet].majourMoons = roll;//I guess you have moons, but no moonlets :)
                }
                else
                    system.stars[orbit].planets[planet].majourMoons = 0;//No moons for you!
            }

            //Determine the sizes of the moons just determined for the planets
            for(loop = system.stars[orbit].planets[planet].majourMoons; loop > 0; --loop)//Loops over each majour moon
            {
                roll = polyRollDice(3,6);
                if(system.stars[orbit].planets[planet].size == 'T')
                {
                    system.stars[orbit].planets[planet].moons[loop].size = 'T';//Minimum allowable size
                }
                else if(system.stars[orbit].planets[planet].size == 'S')
                {
                    system.stars[orbit].planets[planet].moons[loop].size = 'T';//Can only be tiny
                }
                else if(system.stars[orbit].planets[planet].size == 'M')
                {
                    //Tiny or Small only
                    if(roll <= 14)
                        system.stars[orbit].planets[planet].moons[loop].size = 'T';
                    else if(roll >= 15)
                        system.stars[orbit].planets[planet].moons[loop].size = 'S';
                }
                else if((system.stars[orbit].planets[planet].size == 'L') || (system.stars[orbit].planets[planet].type == 'G'))//Large planets or Gas Giants
                {
                    //Tiny, Small and Medium
                    if(roll <= 11)
                        system.stars[orbit].planets[planet].moons[loop].size = 'T';
                    else if((roll >= 12) && (roll <= 14))
                        system.stars[orbit].planets[planet].moons[loop].size = 'S';
                    else if(roll >= 15)
                        system.stars[orbit].planets[planet].moons[loop].size = 'M';
                }
            }
        }
    }

    return system;
}

struct solarSystem step25(struct solarSystem system)//World Types
{
    int orbit,
        planet,
        moon;

    //Sets blackbody temperature and world type
    for(orbit = 0; orbit < system.numberOfStars; ++orbit)
    {
        for(planet = 0; planet < system.stars[orbit].numberOfPlanets; ++planet)
        {
            //Black Body Temperature of each planet and moon (Moons are the same as planets)
            system.stars[orbit].planets[planet].blackbodyTemperature = (278 * sqrt(sqrt(system.stars[orbit].luminosity))) / sqrt(system.stars[orbit].planets[planet].orbit);

            //Assigns a type to the world
            if(system.stars[orbit].planets[planet].type == ' ')
                system.stars[orbit].planets[planet].type = planetoidType(system.stars[orbit].planets[planet].blackbodyTemperature, system.stars[orbit].planets[planet].size, system.stars[orbit].planets[planet].type, system.stars[orbit].mass, system.stellarAge);

			//If a failure occured, here is the recourse
            if(system.stars[orbit].planets[planet].type == 0)
                printf("\nFailure on line %d (system.stars[%d].planets[%d].type = 0)\n", __LINE__, orbit, planet);

            for(moon = system.stars[orbit].planets[planet].majourMoons; moon > 0; --moon)
            {
                system.stars[orbit].planets[planet].moons[moon].type = planetoidType(system.stars[orbit].planets[planet].blackbodyTemperature, system.stars[orbit].planets[planet].moons[moon].size, system.stars[orbit].planets[planet].size, system.stars[orbit].mass, system.stellarAge);

                if(system.stars[orbit].planets[planet].moons[moon].type == 0)
                    printf("\nFailure on line %d (star = %d, Planet = %d, moon = %d)\n", __LINE__, system.stars[orbit].planets[planet].type, orbit, planet, moon);
            }
        }
    }

    return system;
}

struct solarSystem step26(struct solarSystem system)//Atmosphere
{
    int star,
        planet,
        moon;
    struct atmospheres tempAtmosphere;

    for(star = 0; star < system.numberOfStars; ++star)
    {
        for(planet = 0; system.stars[star].numberOfPlanets >= planet; ++planet)
        {
            //Planets first
            if(atmosphereCheck(system.stars[star].planets[planet].size, system.stars[star].planets[planet].type))
                system.stars[star].planets[planet].atmosphere.mass = polyRollDice(3,6) / 10.0;
            else
                system.stars[star].planets[planet].atmosphere.mass = 0;

            for(moon = system.stars[star].planets[planet].majourMoons; moon > 0; --moon)
            {
                //Now Moons
                if(atmosphereCheck(system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type))
                    system.stars[star].planets[planet].moons[moon].atmosphere.mass = polyRollDice(3,6) / 10;
                else
                    system.stars[star].planets[planet].moons[moon].atmosphere.mass = 0;
            }
        }
    }

    for(star = 0; star < system.numberOfStars; ++star)
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            //Determine the atmosphere specifics
            tempAtmosphere = atmosphericComposition(system.stars[star].planets[planet].size, system.stars[star].planets[planet].type);//For planets

            //Assign the atmosphere characteristics
            system.stars[star].planets[planet].atmosphere.marginality = tempAtmosphere.marginality;
            system.stars[star].planets[planet].atmosphere.suffocating = tempAtmosphere.suffocating;
            system.stars[star].planets[planet].atmosphere.toxicity = tempAtmosphere.toxicity;
            system.stars[star].planets[planet].atmosphere.corrosivity = tempAtmosphere.corrosivity;
            system.stars[star].planets[planet].atmosphere.nitrogen = tempAtmosphere.nitrogen;
            system.stars[star].planets[planet].atmosphere.ammonia = tempAtmosphere.ammonia;
            system.stars[star].planets[planet].atmosphere.methane = tempAtmosphere.methane;
            system.stars[star].planets[planet].atmosphere.carbonDioxide = tempAtmosphere.carbonDioxide;
            system.stars[star].planets[planet].atmosphere.oxygen = tempAtmosphere.oxygen;
            system.stars[star].planets[planet].atmosphere.waterVapour = tempAtmosphere.waterVapour;
            system.stars[star].planets[planet].atmosphere.helium = tempAtmosphere.helium;
            system.stars[star].planets[planet].atmosphere.nobleGases = tempAtmosphere.nobleGases;

            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
            {
                //Determine the atmosphere specifics
                tempAtmosphere = atmosphericComposition(system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type);//For moons

                //Assign the atmosphere characteristics
                system.stars[star].planets[planet].moons[moon].atmosphere.marginality = tempAtmosphere.marginality;
                system.stars[star].planets[planet].moons[moon].atmosphere.suffocating = tempAtmosphere.suffocating;
                system.stars[star].planets[planet].moons[moon].atmosphere.toxicity = tempAtmosphere.toxicity;
                system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity = tempAtmosphere.corrosivity;
                system.stars[star].planets[planet].moons[moon].atmosphere.nitrogen = tempAtmosphere.nitrogen;
                system.stars[star].planets[planet].moons[moon].atmosphere.ammonia = tempAtmosphere.ammonia;
                system.stars[star].planets[planet].moons[moon].atmosphere.methane = tempAtmosphere.methane;
                system.stars[star].planets[planet].moons[moon].atmosphere.carbonDioxide = tempAtmosphere.carbonDioxide;
                system.stars[star].planets[planet].moons[moon].atmosphere.oxygen = tempAtmosphere.oxygen;
                system.stars[star].planets[planet].moons[moon].atmosphere.waterVapour = tempAtmosphere.waterVapour;
                system.stars[star].planets[planet].moons[moon].atmosphere.helium = tempAtmosphere.helium;
                system.stars[star].planets[planet].moons[moon].atmosphere.nobleGases = tempAtmosphere.nobleGases;

            }
        }

    return system;
}

struct solarSystem step27(struct solarSystem system)//Hydrographic Coverage
{
    int star,
        planet,
        moon;

    for(star = 0; star < system.numberOfStars; ++star)
    {
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            //Wet and Dry Greenhouse planets need special attention
            if((system.stars[star].planets[planet].type == 'g') && (system.stars[star].planets[planet].atmosphere.carbonDioxide == 1))//Its a
                system.stars[star].planets[planet].hydrographicCoverage = 0;
            else
                system.stars[star].planets[planet].hydrographicCoverage = hydrographicCoverage(system.stars[star].planets[planet].type, system.stars[star].planets[planet].size);
            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
            {
                //Wet and Dry Greenhouse planets need special attention
                if((system.stars[star].planets[planet].moons[moon].type == 'g') && (system.stars[star].planets[planet].moons[moon].atmosphere.carbonDioxide == 1))//Its a
                    system.stars[star].planets[planet].moons[moon].hydrographicCoverage = 0;
                else
                    system.stars[star].planets[planet].moons[moon].hydrographicCoverage = hydrographicCoverage(system.stars[star].planets[planet].moons[moon].type, system.stars[star].planets[planet].moons[moon].size);
            }
        }
    }

    return system;
}

struct solarSystem step28(struct solarSystem system)//Climate
{
    int star,
        planet,
        moon;

    //0 degrees Celsius = 273.15 kelvin
    for(star = 0; star < system.numberOfStars; ++star)
    {
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            //Average Surface temperature
            system.stars[star].planets[planet].temperature = averageTemperature(system.stars[star].planets[planet].size, system.stars[star].planets[planet].type, system.stars[star].planets[planet].hydrographicCoverage, system.stars[star].planets[planet].atmosphere.mass, system.stars[star].planets[planet].blackbodyTemperature);

            //Climate Type
            system.stars[star].planets[planet].atmosphere.climate = climate(system.stars[star].planets[planet].temperature);

            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
            {
                //Average Surface temperature
                system.stars[star].planets[planet].moons[moon].temperature = averageTemperature(system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type, system.stars[star].planets[planet].moons[moon].hydrographicCoverage, system.stars[star].planets[planet].moons[moon].atmosphere.mass, system.stars[star].planets[planet].blackbodyTemperature);

                //Climate Type
                system.stars[star].planets[planet].moons[moon].atmosphere.climate = climate(system.stars[star].planets[planet].moons[moon].temperature);
            }
        }
    }

    return system;
}

struct solarSystem step29(struct solarSystem system)//World Sizes
{
//Planets and Moons are similar and follow step 6
//Gas giants follow a proprietary procedure found in step29
//Skip empty orbits and asteroid belts
    int star,
        planet,
        moon;

    for(star = 0; star < system.numberOfStars; ++star)
    {
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            if(system.stars[star].planets[planet].type == 'G')
                system = worldSizesGasGiant(system, star, planet);
            else
            {
                system.stars[star].planets[planet].density = worldDensity(system.stars[star].planets[planet].size, system.stars[star].planets[planet].type);
                system.stars[star].planets[planet].diameter = worldDiameter(system.stars[star].planets[planet].blackbodyTemperature, system.stars[star].planets[planet].density, system.stars[star].planets[planet].size);
                system.stars[star].planets[planet].gravity = worldGravity(system.stars[star].planets[planet].diameter, system.stars[star].planets[planet].density);
                system.stars[star].planets[planet].mass = worldMass(system.stars[star].planets[planet].density, system.stars[star].planets[planet].diameter);
                system.stars[star].planets[planet].MMWR = MMWR(system.stars[star].planets[planet].blackbodyTemperature, system.stars[star].planets[planet].diameter, system.stars[star].planets[planet].density);
                system.stars[star].planets[planet].atmosphere.pressure = atmosphericPressure(system.stars[star].planets[planet].size, system.stars[star].planets[planet].type, system.stars[star].planets[planet].atmosphere.mass, system.stars[star].planets[planet].gravity);
            }

            //Now process any moons surrounding the planet
            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
            {
                system.stars[star].planets[planet].moons[moon].density = worldDensity(system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type);;
                system.stars[star].planets[planet].moons[moon].diameter = worldDiameter(system.stars[star].planets[planet].blackbodyTemperature, system.stars[star].planets[planet].moons[moon].density, system.stars[star].planets[planet].moons[moon].size);
                system.stars[star].planets[planet].moons[moon].gravity = worldGravity(system.stars[star].planets[planet].moons[moon].diameter, system.stars[star].planets[planet].moons[moon].density);
                system.stars[star].planets[planet].moons[moon].mass = worldMass(system.stars[star].planets[planet].moons[moon].density, system.stars[star].planets[planet].moons[moon].diameter);
                system.stars[star].planets[planet].moons[moon].MMWR = MMWR(system.stars[star].planets[planet].blackbodyTemperature, system.stars[star].planets[planet].moons[moon].diameter, system.stars[star].planets[planet].moons[moon].density);
                system.stars[star].planets[planet].moons[moon].atmosphere.pressure = atmosphericPressure(system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type, system.stars[star].planets[planet].moons[moon].atmosphere.mass, system.stars[star].planets[planet].moons[moon].gravity);
            }
        }
    }

    return system;
}

struct solarSystem step30(struct solarSystem system)//Dynamic Properties
{
    int     star,
            planet,
            moon;

    for(star = 0; star < system.numberOfStars; ++star)
    {
        //Orbital Period
        switch(system.numberOfStars)
        {
            case 1:
                system.stars[star].orbitalPeriod = 0;//Doesn't orbit around anything, so this is zero
                break;
            case 2://Use the mass of both stars
                system.stars[star].orbitalPeriod = orbitalPeriodDays(system.stars[star].averageOrbit, system.stars[0].mass + system.stars[1].mass);
                break;
            case 3://Use the mass of all three stars
                system.stars[star].orbitalPeriod = orbitalPeriodDays(system.stars[star].averageOrbit, system.stars[0].mass + system.stars[1].mass + system.stars[2].mass);
                break;
            default://There more stars than 3? or less than 1!?
                printf("\nFailure on line %d\n", __LINE__);
                break;
        }

        //Orbital period of a planet in days
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
            system.stars[star].planets[planet].orbitalPeriod = orbitalPeriodDays(system.stars[star].planets[planet].orbit, system.stars[star].mass + 0.000003 * system.stars[star].planets[planet].mass);

        //Planetary eccentricity, minimum orbit and maximum orbit
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            system.stars[star].planets[planet].eccentricity = planetaryEccentricity(system, star, planet);
            system.stars[star].planets[planet].minOrbit = (1 - system.stars[star].planets[planet].eccentricity) * system.stars[star].planets[planet].orbit;
            system.stars[star].planets[planet].maxOrbit = (1 + system.stars[star].planets[planet].eccentricity) * system.stars[star].planets[planet].orbit;
        }

        //satelite orbital radius
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
                system.stars[star].planets[planet].moons[moon].orbit = satelliteOrbitalRadius(system.stars[star].planets[planet].diameter, 2, system.stars[star].planets[planet].type, system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].size);

        //sort and reorganize the orbits that were just created
        system = moonOrbitSort(system, star, planet);
        system = moonOrbitFixer(system, star, planet);

        //Orbital Period
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
                system.stars[star].planets[planet].moons[moon].orbitalPeriod = 0.0588 * orbitalPeriodDays(system.stars[star].planets[planet].moons[moon].orbit, system.stars[star].planets[planet].moons[moon].mass + system.stars[star].planets[planet].mass);

        //Moon Tidal properties
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
            {
                system.stars[star].planets[planet].moons[moon].tideOnPlanetFromMoon = 17800000.0 * system.stars[star].planets[planet].moons[moon].mass * system.stars[star].planets[planet].diameter / pow(system.stars[star].planets[planet].moons[moon].orbit, 3.0);
                system.stars[star].planets[planet].moons[moon].tideOnMoonFromPlanet = 17800000.0 * system.stars[star].planets[planet].mass * system.stars[star].planets[planet].moons[moon].diameter / pow(system.stars[star].planets[planet].moons[moon].orbit, 3.0);
                system.stars[star].planets[planet].moons[moon].totalTide = system.stars[star].planets[planet].moons[moon].tideOnMoonFromPlanet * system.stellarAge / system.stars[star].planets[planet].mass;
            }

        //Planetary Tidal properties
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            //Total tidal effects on planet
            if((system.stars[star].planets[planet].type == 'E') || (system.stars[star].planets[planet].type == 'A'))//If its an Asteroid Belt or empty orbit, they have no tidal effects
                system.stars[star].planets[planet].totalTide = 0.0;//No tidal effects, as nothing affects them!
            else
            {
                //Tidal effects from the Sun
                system.stars[star].planets[planet].tideFromSun = 0.46 * system.stars[star].mass * system.stars[star].planets[planet].diameter / pow(system.stars[star].planets[planet].orbit, 3);

                //Quick Initialization
                system.stars[star].planets[planet].totalTide = 0.0;

                //Sums all of the effects from the moons
                for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
                    system.stars[star].planets[planet].totalTide += system.stars[star].planets[planet].moons[moon].tideOnPlanetFromMoon;

                //Adds in the tide from the sun
                system.stars[star].planets[planet].totalTide += system.stars[star].planets[planet].tideFromSun;

                //Computes the final tide based off of all majour effects
                system.stars[star].planets[planet].totalTide *= system.stellarAge / system.stars[star].planets[planet].mass;
            }
        }

        //Planetary Rotational Period
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            if(system.stars[star].planets[planet].totalTide > 50.0)//Over 50 leads to tide locking
                if(system.stars[star].planets[planet].majourMoons > 0)//If it has moons then it is tidelocked to the innermost moon
                    system.stars[star].planets[planet].rotationalPeriod = system.stars[star].planets[planet].moons[1].orbitalPeriod;
                else
                    system.stars[star].planets[planet].rotationalPeriod = system.stars[star].planets[planet].orbit;
            else//Its not tide locked, determine rotational period at random
            {
                //Randomly determines the period in days
                system.stars[star].planets[planet].rotationalPeriod = randomRotationalPeriod(system.stars[star].planets[planet].type, system.stars[star].planets[planet].size);

                //This nested if, check to see if the random period is longer than if it was tide locked, if so it reduces it to a tidelocked period
                if(system.stars[star].planets[planet].majourMoons > 0)//If it has moons then it is tidelocked to the innermost moon
                {
                    if(system.stars[star].planets[planet].rotationalPeriod > system.stars[star].planets[planet].moons[1].orbitalPeriod)
                        system.stars[star].planets[planet].rotationalPeriod = system.stars[star].planets[planet].moons[1].orbitalPeriod;
                }
                else
                {
                    if(system.stars[star].planets[planet].rotationalPeriod > system.stars[star].planets[planet].orbit)
                        system.stars[star].planets[planet].rotationalPeriod = system.stars[star].planets[planet].orbit;
                }
            }

            //Planetary Retrograde
            if(polyRollDice(3,6) >= 13)
                system.stars[star].planets[planet].rotationalPeriod *= -1;//Negative rotation, or retrograde ;)
        }

        //Moon Rotational Period
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
            {
                if(system.stars[star].planets[planet].moons[moon].totalTide > 50.0)//Over 50 leads to tide locking
                    system.stars[star].planets[planet].moons[moon].rotationalPeriod = system.stars[star].planets[planet].moons[moon].orbit;
                else//Its not tide locked, determine rotational period at random
                {
                    system.stars[star].planets[planet].moons[moon].rotationalPeriod = randomRotationalPeriod(system.stars[star].planets[planet].moons[moon].type, system.stars[star].planets[planet].moons[moon].size);
                    if(system.stars[star].planets[planet].moons[moon].rotationalPeriod > system.stars[star].planets[planet].orbit)
                        system.stars[star].planets[planet].moons[moon].rotationalPeriod = system.stars[star].planets[planet].orbit;
                }

                //Moon Retrograde
                if(polyRollDice(3,6) >= 17)
                    system.stars[star].planets[planet].moons[moon].rotationalPeriod *= -1.0;//Negative rotation, or retrograde ;)
            }

            //Planetary Local Calenadar (Length of apparent day)
            for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
            {
                //Length of an apparent day on the planet
                system.stars[star].planets[planet].dayLength = localCalendar(system.stars[star].planets[planet].orbitalPeriod, system.stars[star].planets[planet].rotationalPeriod);

                //Majour Moons
                for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
                {
                    //Local Calenadar (Length of apparent day) on the moon
                    system.stars[star].planets[planet].moons[moon].dayLength = localCalendar(system.stars[star].planets[planet].orbitalPeriod, system.stars[star].planets[planet].moons[moon].rotationalPeriod);

                    //Apparent time for complete cycle of moon as seen from the planet
                    system.stars[star].planets[planet].moons[moon].lunarCycle = localCalendar(system.stars[star].planets[planet].moons[moon].orbitalPeriod, system.stars[star].planets[planet].rotationalPeriod);
                }
            }

            //Axial Tilt
            for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
            {
                    switch(polyRollDice(3, 6))
                    {
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                            system.stars[star].planets[planet].axialTilt = polyRollDice(2,6) - 2;//5 +/- 5 degrees
                            break;
                        case 7:
                        case 8:
                        case 9:
                            system.stars[star].planets[planet].axialTilt = polyRollDice(2,6) + 8;//15 +/- 5 degrees
                            break;
                        case 10:
                        case 11:
                        case 12:
                            system.stars[star].planets[planet].axialTilt = polyRollDice(2,6) + 18;//25 +/- 5 degrees
                            break;
                        case 13:
                        case 14:
                            system.stars[star].planets[planet].axialTilt = polyRollDice(2,6) + 28;//35 +/- 5 degrees
                            break;
                        case 15:
                        case 16:
                            system.stars[star].planets[planet].axialTilt = polyRollDice(2,6) + 38;//45 +/- 5 degrees
                            break;
                        case 17:
                        case 18:
                            switch(polyRollDice(1,6))
                            {
                                case 1:
                                case 2:
                                    system.stars[star].planets[planet].axialTilt = polyRollDice(2,6) + 48;//55 +/- 5 degrees
                                    break;
                                case 3:
                                case 4:
                                    system.stars[star].planets[planet].axialTilt = polyRollDice(2,6) + 58;//65 +/- 5 degrees
                                    break;
                                case 5:
                                    system.stars[star].planets[planet].axialTilt = polyRollDice(2,6) + 68;//75 +/- 5 degrees
                                    break;
                                case 6:
                                    system.stars[star].planets[planet].axialTilt = polyRollDice(2,6) + 78;//85 +/- 5 degrees
                                    break;
                                default:
                                    printf("\nFailure on line %d\n", __LINE__);
                                    break;
                            }
                            break;
                        default:
                            printf("\nFailure on line %d\n", __LINE__);
                            break;
                    }
            }

            //Moonlets!
            for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
            {
                //Inner Moonlets
                for(moon = 0; moon < system.stars[star].planets[planet].innerMoonlets; ++moon)
                {
                    //Type
                    system.stars[star].planets[planet].moonlets[moon].type = 'I';//Sets the moonlets as an inner moonlet

                    //Orbit
                    system.stars[star].planets[planet].moonlets[moon].orbit = satelliteOrbitalRadius(system.stars[star].planets[planet].diameter, 1, 'm', 'm', system.stars[star].planets[planet].size);

                    //Period
                    system.stars[star].planets[planet].moonlets[moon].period = 0.0588 * orbitalPeriodDays(system.stars[star].planets[planet].moonlets[moon].orbit, system.stars[star].planets[planet].mass);
                }

                //Outer Moonlets
                for(; moon < (system.stars[star].planets[planet].innerMoonlets + system.stars[star].planets[planet].outerMoonlets); ++moon)
                {
                    //Type
                    system.stars[star].planets[planet].moonlets[moon].type = 'O';//Sets the moonlets as an outer moonlet

                    //Orbit
                    system.stars[star].planets[planet].moonlets[moon].orbit = satelliteOrbitalRadius(system.stars[star].planets[planet].diameter, 3, 'm', 'm', system.stars[star].planets[planet].size);

                    //Orbital Period
                    system.stars[star].planets[planet].moonlets[moon].period = 0.0588 * orbitalPeriodDays(system.stars[star].planets[planet].moonlets[moon].orbit, system.stars[star].planets[planet].mass);
                }
            }
        }

    return system;
}

struct solarSystem step31(struct solarSystem system)//Geologic Activity
{
  int star,
      planet,
      moon;

  for(star = 0; star < system.numberOfStars; ++star)
  {
    for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
    {
      //Volcanic Activity
      system = volcanism(system, star, planet, 0);

      //Tectonics
      system.stars[star].planets[planet].tectonicActivity = tectonics(system.stars[star].planets[planet].size, system.stars[star].planets[planet].type, system.stars[star].planets[planet].volcanicActivity, system.stars[star].planets[planet].hydrographicCoverage, system.stars[star].planets[planet].majourMoons);

      for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
      {
        //Volcanic Activity
        system = volcanism(system, star, planet, moon);

        //Tectonics
        system.stars[star].planets[planet].moons[moon].tectonicActivity = tectonics(system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type, system.stars[star].planets[planet].moons[moon].volcanicActivity, system.stars[star].planets[planet].moons[moon].hydrographicCoverage, 1);
      }
    }
  }

  return system;
}

struct solarSystem step32(struct solarSystem system)//Resources and Habitability
{
    int star,
        planet,
        moon;

    for(star = 0; star < system.numberOfStars; ++star)
    {
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            //RVM
            if(system.stars[star].planets[planet].type == 'A')//Asteroid belts
                system.stars[star].planets[planet].RVM = asteroidRVM();
            else if(system.stars[star].planets[planet].type != 'E')//Non-Empty orbits
                system.stars[star].planets[planet].RVM = planetRVM(system.stars[star].planets[planet].volcanicActivity);

            //Habitability
            system.stars[star].planets[planet].habitability = habitability(system, star, planet, 0);

            //Affinity
            system.stars[star].planets[planet].affinity = affinity(system.stars[star].planets[planet].RVM, system.stars[star].planets[planet].habitability);

            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
            {
                //RVM
                system.stars[star].planets[planet].moons[moon].RVM = planetRVM(system.stars[star].planets[planet].moons[moon].volcanicActivity);

                //Habitability
                system.stars[star].planets[planet].moons[moon].habitability = habitability(system, star, planet, moon);

                //Affinity
                system.stars[star].planets[planet].moons[moon].affinity = affinity(system.stars[star].planets[planet].moons[moon].RVM, system.stars[star].planets[planet].moons[moon].habitability);
            }
        }
    }

    return system;
}
