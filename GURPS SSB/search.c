#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "GURPS.h"
#include "OutputFile.h"
#include "System.h"
#include "SystemSupport.h"
#include "GenericLibrary.h"
int testFloaterEquality(float number1, float number2, float accuracy);
#define MAX_FOUND   500  //The maximum number of systems before the function ends early

//Things to sort by, have options for planet/moon as well as just planet, or just moon in the test loop
struct atmosphereSearch
{
//Atmosphere characteristics
    char    marginality,
            suffocating,
            toxicity,
            corrosivity,
            climate,
            nitrogen,//Yes or No
			ammonia,//Yes or No
			methane,//Yes or No
			carbonDioxide,//Yes or No
			oxygen,//Yes or No
			waterVapour,//Yes or No
			helium,//Yes or No
			hydrogen,//Yes or No
			nobleGases;//Yes or No
    float   pressure,
            mass;
};

struct moonSearch
{
//Moon Characteristics
    float   density,
            diameter,
            gravity,
            mass,
            MMWR,
            moonOrbit,
            moonOrbitalPeriod,
            totalTide,
            rotationalPeriod,
            dayLength,
            lunarCycle;
    char    size,
            type,
            tectonicActivity,
            volcanicActivity;
    int     hydrographicCoverage,
            RVM,
            habitability,
            affinity;
    unsigned int temperature;
};

struct planetSearch
{
//Planetary Characteristics
    float   planetOrbit,
            density,
            mass,
            diameter,
            gravity,
            MMWR,
            planetOrbitalPeriod,
            eccentricity,
            totalTide,
            rotationalPeriod,
            dayLength;
    char    size,
            type,
            rings,
            tectonicActivity,
            volcanicActivity;
    int     axialTilt,
            hydrographicCoverage,
            majourMoons,
            RVM,
            habitability,
            affinity;
    unsigned int temperature;
};

struct solarSearch
{
//Solar Characteristics
    int     numberOfPlanets;
    float   mass,
            luminosity,
            temperature,
            radius,
            averageOrbit,
            eccentricity,
            orbitalPeriod;
    char    spectralType[2],
            sequence;
};

struct systemSearch
{
	int   	numberOfStars;
    float   stellarAge;
	struct	solarSearch			solar;
	struct	planetSearch		planet;
	struct	moonSearch			moon;
	struct	atmosphereSearch	atmosphere;
};

int findSystem(struct solarSystem system);
int compareSystem(struct solarSystem system, struct systemSearch search);
int confirmation();
int sentinel();
struct systemSearch initializeSearch(struct systemSearch search);
void solarSelection(struct systemSearch search);
void planetSelection(struct systemSearch search);
void moonSelection(struct systemSearch search);
void planetoidSelection(struct systemSearch search);

int findSystem(struct solarSystem system)
{
    int systemsFound = 0;
    long int ID;
    char userInput;
	struct systemSearch	search;

	//For troubleshooting only
	int	star, planet, moon;

	//Initialize search variables
	search = initializeSearch(search);
/*Temporary measure
    //Begin by asking if you want to search or regenerate
    printf("Would you like to regenerate a specific system? (y/n) ");

    if(confirmation())
    {
    	//Get the address to be regenerated
    	printf("\nNumber: ");
    	scanf("%d", &address);//No need for sentinels, it can't be overrun, and I don't know how to check for letters

		//Regenerate the specific solar system
        system = generateSystem(system, address);
        return 1;
    }

	//Selection request
	printf("\n\n[S] Systems\n[P] Planets\n[M] Moons\n[B] Both Planets & Moons\n[F] Find the systems that meet your criteria");

	//Bypass until finished writing the search functions!
/*	//Fill the criteria
	while(userInput != 'F')
	{
		//Menu Sentinel
		do
		{
			printf("\nSelection: ");
			userInput = toupper(getche());
		} while((userInput != 'S') && (userInput != 'P') && (userInput != 'M') && (userInput != 'B') && (userInput != 'F'));

		switch(userInput)
		{
			case 'S'://System
				solarSelection(search);
				break;
			case 'P'://Planets only
				planetSelection(search);
				break;
			case 'M'://Moons only
				moonSelection(search);
				break;
			case 'B'://Both Planets & Moons
				planetoidSelection(search);
				break;
			case 'F'://Find
				break;
			default:
				printf("\nSorry that is not a valid input\n");
				break;
		}
	}*/

	//Find what is being looked for
    for(ID = 1; ID <= pow(2,(sizeof(int) * 8)); ++ID)//Goes until the end of the search space (system specific)
    {
    	//Clean it first
		system = initializeStars(system);

		//Generate the system to be compared with
		system = generateSystem(system, ID);

//search.solar.numberOfPlanets = 5;
//search.numberOfStars = 2;
//search.stellarAge = 3.5;
		//If it matches, write it to the output file
/*		if(compareSystem(system, search))
		{
			//Increment found systems
			++systemsFound;
*/
			//Print it to the O/P folder
			printFile(system);
/*		}//*/

		//Let the user know what we're up to
		printf("%3d Found\tCurrently checking system %d\n", systemsFound, ID);

        //Break out early if there are a lot of systems that meet the criteria
        if(systemsFound >= MAX_FOUND)//Found a lot of systems
            break;//Get out of the finite loop

    }

    return systemsFound;
}

int compareSystem(struct solarSystem system, struct systemSearch search)
{
	int star,
		planet,
		moon,
		success;

/*	//Number of stars
	if((search.numberOfStars > 0) && (search.numberOfStars != system.numberOfStars))
		return 0;//Doesn't Match

	//Stellar Age
	if((search.stellarAge > 0.0) && (!testFloatEquality(search.stellarAge, system.stellarAge, 0.001)))
		return 0;//Doesn't Match
/*
	success = 0;
    for(star = 0; star < system.numberOfStars; ++star)//Number of planets
		if((search.solar.numberOfPlanets >= 0) && (search.solar.numberOfPlanets == system.stars[star].numberOfPlanets))
			success++;
	if(success == 0)
		return 0;


/*Solar Characteristics
	search.solar.numberOfPlanets = 200;
	search.solar.mass = 0.0;
	search.solar.luminosity = 0.0;
	search.solar.temperature = -65500;
	search.solar.radius = 0.0;
	search.solar.averageOrbit = 0.0;
	search.solar.eccentricity = -65500;
	search.solar.orbitalPeriod = 0.0;
	search.solar.stellarAge = 0.0;
	search.solar.spectralType[0] = ' ';
	search.solar.spectralType[1] = ' ';
	search.solar.sequence = ' ';
	search.solar.numberOfStars = 0;

    int     numberOfPlanets;
    float   mass,
            luminosity,
            temperature,
            radius,
            averageOrbit,
            eccentricity,
            orbitalPeriod;
    char    spectralType[2],
            sequence;
    int     uniqueID,
            numberOfStars;
    float   stellarAge;*//*

        for(planet = 1; planet <= system.stars[star].numberOfPlanets; ++planet)
        {
            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
            {
            }
		}
    }
*/
	return 1;//System matches!!!
}
void solarSelection(struct systemSearch search)
{
	int userInput;

	//Selection request
	printf("\n\n");
	printf("[0] Back one menu\n");
	printf("[1] Number of planets\n");
	printf("[2] Star Mass\n");
	printf("[3] \n");
	printf("[4] \n");
	printf("[5] \n");
	printf("[6] \n");
	printf("[7] \n");
	printf("[8] \n");
	printf("[9] \n");
	printf("[10] \n");
	printf("[11] \n");
	printf("[12] \n");
	printf("[13] \n");

	//Menu Sentinel
	do
	{
		printf("\nSolar Selection: ");
		fflush(stdin);
		scanf("%d", &userInput);
	} while((userInput > 13) || (userInput < 0));

/*//Solar variables
	search.solar.numberOfPlanets;
	search.solar.mass;
	search.solar.luminosity;
	search.solar.temperature;
	search.solar.radius;
	search.solar.averageOrbit;
	search.solar.eccentricity;
	search.solar.orbitalPeriod;
	search.solar.stellarAge;
	search.solar.spectralType[0];
	search.solar.spectralType[1];
	search.solar.sequence;
	search.solar.numberOfStars;*/
	return;
}

void planetSelection(struct systemSearch search)
{return;}
void moonSelection(struct systemSearch search)
{return;}
void planetoidSelection(struct systemSearch search)
{return;}

struct systemSearch initializeSearch(struct systemSearch search)
{
//Atmosphere characteristics
    search.atmosphere.marginality = ' ';
    search.atmosphere.suffocating = ' ';
	search.atmosphere.toxicity = ' ';
	search.atmosphere.corrosivity = ' ';
	search.atmosphere.climate = ' ';
	search.atmosphere.nitrogen = ' ';//Yes or No (y/n)
	search.atmosphere.ammonia = ' ';//Yes or No (y/n)
	search.atmosphere.methane = ' ';//Yes or No (y/n)
	search.atmosphere.carbonDioxide = ' ';//Yes or No (y/n)
	search.atmosphere.oxygen = ' ';//Yes or No (y/n)
	search.atmosphere.waterVapour = ' ';//Yes or No (y/n)
	search.atmosphere.helium = ' ';//Yes or No (y/n)
	search.atmosphere.hydrogen = ' ';//Yes or No (y/n)
	search.atmosphere.nobleGases = ' ';//Yes or No (y/n)
	search.atmosphere.pressure = 0.0;//Equal to or greater than
	search.atmosphere.mass = 0.0;//Equal to or greater than

//Moon Characteristics
	search.moon.density = 0.0;
	search.moon.diameter = 0.0;
	search.moon.gravity = 0.0;
	search.moon.mass = 0.0;
	search.moon.MMWR = 0.0;
	search.moon.moonOrbit = 0.0;
	search.moon.moonOrbitalPeriod = 0.0;
	search.moon.totalTide = 0.0;
	search.moon.rotationalPeriod = 0.0;
	search.moon.dayLength = 0.0;
	search.moon.lunarCycle = 0.0;
	search.moon.size = ' ';
	search.moon.type = ' ';
	search.moon.tectonicActivity = ' ';
	search.moon.volcanicActivity = ' ';
	search.moon.hydrographicCoverage = 0;
	search.moon.RVM = 0;
	search.moon.habitability = 0;
	search.moon.affinity = 0;
    search.moon.temperature = -65500;

//Planetary Characteristics
	search.planet.planetOrbit = 0.0;
	search.planet.density = 0.0;
	search.planet.mass = 0.0;
	search.planet.diameter = 0.0;
	search.planet.gravity = 0.0;
	search.planet.MMWR = 0.0;
	search.planet.planetOrbitalPeriod = 0.0;
	search.planet.eccentricity = 0.0;
	search.planet.totalTide = 0.0;
	search.planet.rotationalPeriod = 0.0;
	search.planet.dayLength = 0.0;
	search.planet.size = ' ';
	search.planet.type = ' ';
	search.planet.rings = ' ';
	search.planet.tectonicActivity = ' ';
	search.planet.volcanicActivity = ' ';
    search.planet.axialTilt = 0;
	search.planet.hydrographicCoverage = 0;
	search.planet.majourMoons = 0;
	search.planet.RVM = 0;
	search.planet.habitability = 0;
	search.planet.affinity = 0;
	search.planet.temperature = -65500;

//Solar Characteristics
	search.solar.numberOfPlanets = -1;
	search.solar.mass = 0.0;
	search.solar.luminosity = 0.0;
	search.solar.temperature = -65500;
	search.solar.radius = 0.0;
	search.solar.averageOrbit = 0.0;
	search.solar.eccentricity = -65500;
	search.solar.orbitalPeriod = 0.0;
	search.solar.spectralType[0] = ' ';
	search.solar.spectralType[1] = ' ';
	search.solar.sequence = ' ';

//System characteristics
	search.numberOfStars = 0;
	search.stellarAge = 0.0;

	//Return successfully ;)
	return search;
}

int confirmation()
{
    char answer;

    //Get user input
    answer = getche();

    //Check and ensure it meets the confirmation criteria
    while((answer != 'y') && (answer != 'Y') && (answer != 'n') && (answer != 'N'))
    {
        //Please kindly restate the nature of the inquiry
        printf("\nPlease answer with a 'y' or an 'n': ");
        answer = getche();
    }

    //Return a 1 for yes or a 0 for no
    if((answer == 'Y') || (answer == 'y'))
        return 1;
    else
        return 0;
}
