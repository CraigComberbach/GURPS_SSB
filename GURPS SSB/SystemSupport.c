#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GURPS.h"
#include "random.h"
#include "System.h"
#include "GenericLibrary.h"

int		IDnumber;

struct  solarSystem initializeStars(struct solarSystem system);
float   nextOrbit(float currentOrbit, int direction);//Returns the next orbit, direction = 1 then going outward, direction = 0 then inward
char    planetoidType(float blackBodyTemp, char worldSize, char worldType, float massStar, float stellarAge);//Returns the world or moons type
int     atmosphereCheck(char worldSize, char worldType);//Checks to see if the planet or moon can support an atmosphere
struct  solarSystem orbitSort(struct solarSystem system);
struct  atmospheres atmosphericComposition(char size, char type);//Determines the type of atmosphere and its composition
char    marginalAtmosphere();//Determines the type of marginality
int     hydrographicCoverage(char type, char size);//Calculates the amount of liquid coverage
void    displayAtmosphere(struct solarSystem system, int star, int planet, int moon);
unsigned int averageTemperature(char size, char type, int hydro, float atmosphericMass, float blackbody);
char    climate(int surfaceTemperature);
float   worldDensity(char size, char type);
float   icyCore();
float   smallIronCore();
float   largeIronCore();
struct  solarSystem worldSizesGasGiant(struct solarSystem, int star, int planet);//Determines all of the Gas Giants unique elements
float   atmosphericPressure(char size, char type, float atmoMass, float gravity);
float   MMWR(float blackbody, float diameter, float density);
float   worldMass(float density, float diameter);
float   worldGravity(float diameter, float density);
float   worldDiameter(int blackbody, float density, char size);
float   orbitalPeriodDays(float distance, float mass);//Returns the orbital time in days
float   planetaryEccentricity(struct solarSystem system, int star, int planet);
float   satelliteOrbitalRadius(float planetDiameter, int moonType, char planetType, char moonSize, char planetSize);
struct  solarSystem moonOrbitFixer(struct solarSystem system, int star, int planet);
struct  solarSystem moonOrbitSort(struct solarSystem system, int star, int planet);
float   randomRotationalPeriod(char type, char size);
float   localCalendar(float sidereal, float period);//Calculates the apparent length of a day
struct  solarSystem volcanism(struct solarSystem system, int star, int planet, int moon);
char    tectonics(char size, char type, char volcanism, float hydro, int moons);
int     planetRVM(char volcanicActivity);
int	asteroidRVM();
int     habitability(struct solarSystem system, int star, int planet, int moon);
int     affinity(int RVM, int habitability);
struct  solarSystem generateSystem(struct solarSystem system, unsigned int address);

struct  solarSystem generateSystem(struct solarSystem system, unsigned int address)
{
//	defineSeed(9);
	defineSeed(address);
	initializeRandomMT();

	system.uniqueID = address;//Unique ID

	IDnumber = address;
    system = step15(system);//Number of stars
    system = step16(system);//Star Masses
    system = step17(system);//Stellar Age
    system = step18(system);//Stellar Characteristics
    system = step19(system);//Companion Star Orbits
    system = step20(system);//Companion Star Orbits
    system = step21(system);//Placing first planets
    system = step22(system);//Place Planetary Orbits
    system = step23(system);//Place Worlds
    system = step24(system);//Place Moons
    system = step25(system);//World Types
    system = step26(system);//Atmosphere
    system = step27(system);//Hydrographic Coverage
    system = step28(system);//Climate
    system = step29(system);//World Sizes
    system = step30(system);//Dynamic Properties
    system = step31(system);//Geological Activity
    system = step32(system);//Resources and Habitability

    return system;
}

struct solarSystem initializeStars(struct solarSystem system)
{
    int star,
        planet,
        moon,
        moonlet;

		//System
    system.uniqueID = 0;
    system.numberOfStars = 3;
    system.primaryStar = 0;
    system.stellarAge = 0;

		//Star
    for(star = 0; star < 3; ++star)
    {
        //Int
        system.stars[star].numberOfPlanets = 0;
        system.stars[star].gasGiantFlag = 0;
        system.stars[star].forbiddenFlag = 0;
        system.stars[star].companionFlag = 0;

        //float
        system.stars[star].mass = 0.0;
        system.stars[star].luminosity = 0.0;
        system.stars[star].temperature = 0.0;
        system.stars[star].radius = 0.0;
        system.stars[star].averageOrbit = 0.0;
        system.stars[star].minOrbit = 0.0;
        system.stars[star].maxOrbit = 0.0;
        system.stars[star].eccentricity = 0.0;
        system.stars[star].innerForbiddenZone = 0.0;
        system.stars[star].outerForbiddenZone = 0.0;
        system.stars[star].innerLimitRadius = 0.0;
        system.stars[star].outerLimitRadius = 0.0;
        system.stars[star].snowLine = 0.0;
        system.stars[star].firstGasGiant = 0.0;
        system.stars[star].lMin = 0.0;
        system.stars[star].orbitalPeriod = 0.0;

        //char
        system.stars[star].spectralType[0] = ' ';
        system.stars[star].spectralType[1] = ' ';
        system.stars[star].sequence = ' ';

				//Planets
        for(planet = 0; planet < 20; ++planet)
        {
            //int
            system.stars[star].planets[planet].innerMoonlets = 0;
            system.stars[star].planets[planet].majourMoons = 0;
            system.stars[star].planets[planet].outerMoonlets = 0;
            system.stars[star].planets[planet].hydrographicCoverage = 0;
            system.stars[star].planets[planet].temperature = 0;
            system.stars[star].planets[planet].axialTilt = 0;
            system.stars[star].planets[planet].RVM = 0;
            system.stars[star].planets[planet].habitability = 0;
            system.stars[star].planets[planet].affinity = 0;

            //float
            system.stars[star].planets[planet].orbit = 0.0;
            system.stars[star].planets[planet].blackbodyTemperature = 0.0;
            system.stars[star].planets[planet].minOrbit = 0.0;
            system.stars[star].planets[planet].maxOrbit = 0.0;
            system.stars[star].planets[planet].density = 0.0;
            system.stars[star].planets[planet].mass = 0.0;
            system.stars[star].planets[planet].diameter = 0.0;
            system.stars[star].planets[planet].gravity = 0.0;
            system.stars[star].planets[planet].MMWR = 0.0;
            system.stars[star].planets[planet].orbitalPeriod = 0.0;
            system.stars[star].planets[planet].eccentricity = 0.0;
            system.stars[star].planets[planet].tideFromSun = 0.0;
            system.stars[star].planets[planet].totalTide = 0.0;
            system.stars[star].planets[planet].rotationalPeriod = 0;
            system.stars[star].planets[planet].dayLength = 0;

            //char
            system.stars[star].planets[planet].type = ' ';
            system.stars[star].planets[planet].size = ' ';
            system.stars[star].planets[planet].rings = ' ';
            system.stars[star].planets[planet].volcanicActivity = ' ';
            system.stars[star].planets[planet].tectonicActivity = ' ';

            //struct atmospheres
            system.stars[star].planets[planet].atmosphere.marginality = ' ';
            system.stars[star].planets[planet].atmosphere.suffocating = ' ';
            system.stars[star].planets[planet].atmosphere.toxicity = ' ';
            system.stars[star].planets[planet].atmosphere.corrosivity = ' ';
            system.stars[star].planets[planet].atmosphere.climate = ' ';
            system.stars[star].planets[planet].atmosphere.nitrogen = 0;
            system.stars[star].planets[planet].atmosphere.ammonia = 0;
            system.stars[star].planets[planet].atmosphere.methane = 0;
            system.stars[star].planets[planet].atmosphere.carbonDioxide = 0;
            system.stars[star].planets[planet].atmosphere.oxygen = 0;
            system.stars[star].planets[planet].atmosphere.waterVapour = 0;
            system.stars[star].planets[planet].atmosphere.helium = 0;
            system.stars[star].planets[planet].atmosphere.hydrogen = 0;
            system.stars[star].planets[planet].atmosphere.nobleGases = 0;
            system.stars[star].planets[planet].atmosphere.pressure = 0.0;
            system.stars[star].planets[planet].atmosphere.mass = 0.0;

						//Moons
            for(moon = 0; moon < 7; ++moon)
            {
                //float
                system.stars[star].planets[planet].moons[moon].diameter = 0.0;
                system.stars[star].planets[planet].moons[moon].density = 0.0;
                system.stars[star].planets[planet].moons[moon].gravity = 0.0;
                system.stars[star].planets[planet].moons[moon].mass = 0.0;
                system.stars[star].planets[planet].moons[moon].MMWR = 0.0;
                system.stars[star].planets[planet].moons[moon].orbit = 0.0;
                system.stars[star].planets[planet].moons[moon].orbitalPeriod = 0.0;
                system.stars[star].planets[planet].moons[moon].tideOnPlanetFromMoon = 0.0;
                system.stars[star].planets[planet].moons[moon].tideOnMoonFromPlanet = 0.0;
                system.stars[star].planets[planet].moons[moon].totalTide = 0.0;
                system.stars[star].planets[planet].moons[moon].rotationalPeriod = 0.0;
                system.stars[star].planets[planet].moons[moon].dayLength = 0.0;
                system.stars[star].planets[planet].moons[moon].lunarCycle = 0.0;

                //char
                system.stars[star].planets[planet].moons[moon].size = ' ';
                system.stars[star].planets[planet].moons[moon].type = ' ';
                system.stars[star].planets[planet].moons[moon].volcanicActivity = ' ';
                system.stars[star].planets[planet].moons[moon].tectonicActivity = ' ';

                //Integer or unsigned integer
                system.stars[star].planets[planet].moons[moon].hydrographicCoverage = 0;
                system.stars[star].planets[planet].moons[moon].temperature = 0;
                system.stars[star].planets[planet].moons[moon].RVM = 0;
                system.stars[star].planets[planet].moons[moon].habitability = 0;
                system.stars[star].planets[planet].moons[moon].affinity = 0;

                //struct atmospheres
                system.stars[star].planets[planet].moons[moon].atmosphere.marginality = ' ';
                system.stars[star].planets[planet].moons[moon].atmosphere.suffocating = ' ';
                system.stars[star].planets[planet].moons[moon].atmosphere.toxicity = ' ';
                system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity = ' ';
                system.stars[star].planets[planet].moons[moon].atmosphere.climate = ' ';
                system.stars[star].planets[planet].moons[moon].atmosphere.nitrogen = 0;
                system.stars[star].planets[planet].moons[moon].atmosphere.ammonia = 0;
                system.stars[star].planets[planet].moons[moon].atmosphere.methane = 0;
                system.stars[star].planets[planet].moons[moon].atmosphere.carbonDioxide = 0;
                system.stars[star].planets[planet].moons[moon].atmosphere.oxygen = 0;
                system.stars[star].planets[planet].moons[moon].atmosphere.waterVapour = 0;
                system.stars[star].planets[planet].moons[moon].atmosphere.helium = 0;
                system.stars[star].planets[planet].moons[moon].atmosphere.hydrogen = 0;
                system.stars[star].planets[planet].moons[moon].atmosphere.nobleGases = 0;
                system.stars[star].planets[planet].moons[moon].atmosphere.pressure = 0.0;
                system.stars[star].planets[planet].moons[moon].atmosphere.mass = 0.0;
            }

						//Moonlets
            for(moonlet = 0; moonlet < (system.stars[star].planets[planet].innerMoonlets + system.stars[star].planets[planet].outerMoonlets); ++moonlet)
            {
                system.stars[star].planets[planet].moonlets[moonlet].type = ' ';
                system.stars[star].planets[planet].moonlets[moonlet].orbit = 0.0;
                system.stars[star].planets[planet].moonlets[moonlet].period = 0.0;
            }
        }
    }

    return system;
}

int hydrographicCoverage(char type, char size)
{
    int coverage;

    if((type == 'I') && (size == 'S'))//Small Ice Worlds
        coverage = (polyRollDice(1,6) + 2) * 10;
    else if((type == 'a') && ((size == 'M') || (size == 'L')))//Standard and Large size ammonia
        coverage = polyRollDice(2,6) * 10;
    else if((type == 'I') && ((size == 'M') || (size == 'L')))//Standard and large size Ice
    {
        coverage = (polyRollDice(2,6) - 10) * 10;
        if(coverage < 0)
            coverage = 0;
    }
    else if(((type == 'r') || (type == 'O')) && (size == 'M'))//Standard Gardens or Oceans
        coverage = (polyRollDice(1,6) + 4) * 10;
    else if(((type == 'r') || (type == 'O')) && (size == 'L'))//Large Gardens or Oceans
    {
        coverage = (polyRollDice(1,6) + 6) * 10;
        if(coverage > 100)
            coverage = 100;
    }
    else if((type == 'g') && ((size == 'M') || (size == 'L')))//Only applies to Wet Green house worlds, dry green houses have 0%
    {
        do
            coverage = (polyRollDice(2,6) - 7) * 10;
        while(coverage <= 0);//Sentinel to ensure that the hydrographic coverage is never less than or equal to 0
    }
    else//It has no liquid coverage
        coverage = 0;

    return coverage;
}

struct atmospheres atmosphericComposition(char size, char type)
{
    struct atmospheres atmosphere;

    if((type == 'I') && (size == 'S'))//Small Ice
    {
        atmosphere.marginality = 'P';
        atmosphere.suffocating = 'S';
        if(polyRollDice(3,6) <= 15)
            atmosphere.toxicity = 'M';
        else
            atmosphere.toxicity = 'H';
        atmosphere.corrosivity = 'N';
        atmosphere.nitrogen = 1;
        atmosphere.ammonia = 0;
        atmosphere.methane = 1;
        atmosphere.carbonDioxide = 0;
        atmosphere.oxygen = 0;
        atmosphere.waterVapour = 0;
        atmosphere.helium = 0;
        atmosphere.hydrogen = 0;
        atmosphere.nobleGases = 0;
    }
    else if((type == 'a') && (size == 'M'))//Standard Ammonia
    {
        atmosphere.marginality = 'N';
        atmosphere.suffocating = 'S';
        atmosphere.toxicity = 'L';
        atmosphere.corrosivity = 'C';
        atmosphere.nitrogen = 1;
        atmosphere.ammonia = 1;
        atmosphere.methane = 1;
        atmosphere.carbonDioxide = 0;
        atmosphere.oxygen = 0;
        atmosphere.waterVapour = 0;
        atmosphere.helium = 0;
        atmosphere.hydrogen = 0;
        atmosphere.nobleGases = 0;
    }
    else if((type == 'I') && (size == 'M'))//Standard ice
    {
        atmosphere.marginality = 'N';
        atmosphere.suffocating = 'S';
        if(polyRollDice(3,6) <= 12)
            atmosphere.toxicity = 'N';
        else
            atmosphere.toxicity = 'M';
        atmosphere.corrosivity = 'N';
        atmosphere.nitrogen = 1;
        atmosphere.ammonia = 0;
        atmosphere.methane = 0;
        atmosphere.carbonDioxide = 1;
        atmosphere.oxygen = 0;
        atmosphere.waterVapour = 0;
        atmosphere.helium = 0;
        atmosphere.hydrogen = 0;
        atmosphere.nobleGases = 0;
    }
    else if((type == 'O') && (size == 'M'))//Standard Ocean
    {
        atmosphere.marginality = 'N';
        atmosphere.suffocating = 'S';
        if(polyRollDice(3,6) <= 12)
            atmosphere.toxicity = 'N';
        else
            atmosphere.toxicity = 'M';
        atmosphere.corrosivity = 'N';
        atmosphere.nitrogen = 1;
        atmosphere.ammonia = 0;
        atmosphere.methane = 0;
        atmosphere.carbonDioxide = 1;
        atmosphere.oxygen = 0;
        atmosphere.waterVapour = 0;
        atmosphere.helium = 0;
        atmosphere.hydrogen = 0;
        atmosphere.nobleGases = 0;
    }
    else if((type == 'r') && (size == 'M'))//Standard Garden
    {
        if(polyRollDice(3,6) <= 11)
            atmosphere.marginality = 'N';
        else
            atmosphere.marginality = marginalAtmosphere();
        atmosphere.suffocating = 'N';
        atmosphere.toxicity = 'N';
        atmosphere.corrosivity = 'N';
        atmosphere.nitrogen = 1;
        atmosphere.ammonia = 0;
        atmosphere.methane = 0;
        atmosphere.carbonDioxide = 0;
        atmosphere.oxygen = 1;
        atmosphere.waterVapour = 0;
        atmosphere.helium = 0;
        atmosphere.hydrogen = 0;
        atmosphere.nobleGases = 0;
    }
    else if((type == 'g') && (size == 'M'))//Standard Greenhouse
    {
        if(polyRollDice(3,6) <= 10)//Wet Green House (I decided for a 50/50 split, the book gives no details)
        {
            atmosphere.nitrogen = 1;
            atmosphere.carbonDioxide = 0;
            atmosphere.waterVapour = 1;

            if(polyRollDice(3,6) <= 10)//Again I decided on a 50/50 split for the chance of Oxygen, the book gives no details
                atmosphere.oxygen = 1;
            else
                atmosphere.oxygen = 0;

        }
        else//Dry Green house
        {
            atmosphere.nitrogen = 0;
            atmosphere.carbonDioxide = 1;
            atmosphere.oxygen = 0;
            atmosphere.waterVapour = 0;
        }
        atmosphere.marginality = 'N';
        atmosphere.suffocating = 'S';
        atmosphere.toxicity = 'L';
        atmosphere.corrosivity = 'C';
        atmosphere.ammonia = 0;
        atmosphere.methane = 0;
        atmosphere.helium = 0;
        atmosphere.hydrogen = 0;
        atmosphere.nobleGases = 0;
    }
    else if((type == 'a') && (size == 'L'))//Large Ammonia
    {
        atmosphere.marginality = 'N';
        atmosphere.suffocating = 'S';
        atmosphere.toxicity = 'L';
        atmosphere.corrosivity = 'C';
        atmosphere.nitrogen = 0;
        atmosphere.ammonia = 1;
        atmosphere.methane = 1;
        atmosphere.carbonDioxide = 0;
        atmosphere.oxygen = 0;
        atmosphere.waterVapour = 0;
        atmosphere.helium = 1;
        atmosphere.hydrogen = 0;
        atmosphere.nobleGases = 0;
    }
    else if((type == 'I') && (size == 'L'))//Large Ice
    {
        atmosphere.marginality = 'N';
        atmosphere.suffocating = 'S';
        atmosphere.toxicity = 'H';
        atmosphere.corrosivity = 'N';
        atmosphere.nitrogen = 1;
        atmosphere.ammonia = 0;
        atmosphere.methane = 0;
        atmosphere.carbonDioxide = 0;
        atmosphere.oxygen = 0;
        atmosphere.waterVapour = 0;
        atmosphere.helium = 1;
        atmosphere.hydrogen = 0;
        atmosphere.nobleGases = 0;
    }
    else if((type == 'O') && (size == 'L'))//Large Ocean
    {
        atmosphere.marginality = 'N';
        atmosphere.suffocating = 'S';
        atmosphere.toxicity = 'H';
        atmosphere.corrosivity = 'N';
        atmosphere.nitrogen = 1;
        atmosphere.ammonia = 0;
        atmosphere.methane = 0;
        atmosphere.carbonDioxide = 0;
        atmosphere.oxygen = 0;
        atmosphere.waterVapour = 0;
        atmosphere.helium = 1;
        atmosphere.hydrogen = 0;
        atmosphere.nobleGases = 0;
    }
    else if((type == 'r') && (size == 'L'))//Large Garden
    {
        if(polyRollDice(3,6) >= 12)
            atmosphere.marginality = marginalAtmosphere();
        else
            atmosphere.marginality = 'N';
        atmosphere.suffocating = 'N';
        atmosphere.toxicity = 'N';
        atmosphere.corrosivity = 'N';
        atmosphere.nitrogen = 1;
        atmosphere.ammonia = 0;
        atmosphere.methane = 0;
        atmosphere.carbonDioxide = 0;
        atmosphere.oxygen = 1;
        atmosphere.waterVapour = 0;
        atmosphere.helium = 0;
        atmosphere.hydrogen = 0;
        atmosphere.nobleGases = 1;
    }
    else if((type == 'g') && (size == 'L'))//Large Greenhouse
    {
        if(polyRollDice(3,6) <= 10)//Wet Green House (I decided for a 50/50 split, the book gives no details)
        {
            atmosphere.nitrogen = 1;
            atmosphere.carbonDioxide = 0;
            atmosphere.waterVapour = 1;

            if(polyRollDice(3,6) <= 10)//Again I decided on a 50/50 split for the chance of Oxygen, the book gives no details
                atmosphere.oxygen = 1;
            else
                atmosphere.oxygen = 0;

        }
        else//Dry Green house
        {
            atmosphere.nitrogen = 0;
            atmosphere.carbonDioxide = 1;
            atmosphere.oxygen = 0;
            atmosphere.waterVapour = 0;
        }
        atmosphere.marginality = 'N';
        atmosphere.suffocating = 'S';
        atmosphere.toxicity = 'L';
        atmosphere.corrosivity = 'C';
        atmosphere.ammonia = 0;
        atmosphere.methane = 0;
        atmosphere.helium = 0;
        atmosphere.hydrogen = 0;
        atmosphere.nobleGases = 0;
    }
    else if(type == 'G')//Gas Giant
    {
        atmosphere.marginality = 'N';
        atmosphere.suffocating = 'S';
        atmosphere.toxicity = 'N';
        atmosphere.corrosivity = 'N';
        atmosphere.nitrogen = 0;
        atmosphere.ammonia = 0;
        atmosphere.methane = 0;
        atmosphere.carbonDioxide = 0;
        atmosphere.oxygen = 0;
        atmosphere.waterVapour = 0;
        atmosphere.helium = 1;
        atmosphere.hydrogen = 1;
        atmosphere.nobleGases = 0;
    }
    else//It has no atmosphere
    {
        atmosphere.marginality = 'V';
        atmosphere.suffocating = 'S';
        atmosphere.toxicity = 'N';
        atmosphere.corrosivity = 'N';
        atmosphere.nitrogen = 0;
        atmosphere.ammonia = 0;
        atmosphere.methane = 0;
        atmosphere.carbonDioxide = 0;
        atmosphere.oxygen = 0;
        atmosphere.waterVapour = 0;
        atmosphere.helium = 0;
        atmosphere.hydrogen = 0;
        atmosphere.nobleGases = 0;
    }

    return atmosphere;
}

char    marginalAtmosphere()
{
    char type;
    switch(polyRollDice(3, 6))
    {
        case 3:
        case 4:
            if(polyRollDice(3,6) <= 16)//No rules on this, though it did say fluorine is extremely unlikely
                type = 'c';//Chlorine atmosphere
            else
                type = 'F';//Fluorine atmosphere
            break;
        case 5:
        case 6:
            type = 'S';//Sulfur compounds in the atmosphere
            break;
        case 7:
            type = 'n';//Nitrogen compounds in the atmosphere
            break;
        case 8:
        case 9:
            type = 'T';//Organic Toxins
            break;
        case 10:
        case 11:
            type = 'o';//Low Oxygen
            break;
        case 12:
        case 13:
            type = 'p';//pollutants
            break;
        case 14:
            type = 'C';//High Carbon Dioxide
            break;
        case 15:
        case 16:
            type = 'O';//High Oxygen
            break;
        case 17:
        case 18:
            type = 'I';//Inert Gases
            break;
        default:
            printf("\nFailure on line %d\n", __LINE__);
    break;
}

    return type;
}

void displayAtmosphere(struct solarSystem system, int star, int planet, int moon)
{
    if(moon == 0)//Its a planet
    {
        switch(system.stars[star].planets[planet].atmosphere.marginality)
        {
            case 'P'://Poisonous
                printf("Poisonous, ");
                break;
            case 'V'://Vacuum
                printf("Vacuum\n");
                return;
            case 'N'://Not Marginal
                printf("Non-Marginal, ");
                break;
            case 'o'://Low Oxygen
                printf("Low Oxygen, ");
                break;
            case 'F'://Fluorine
                printf("Fluorine, ");
                break;
            case 'S'://Sulphur Compounds
                printf("Sulphur Compounds, ");
                break;
            case 'c'://Chlorine
                printf("Chlorine, ");
                break;
            case 'T'://Organic Toxins
                printf("Organic Toxins, ");
                break;
            case 'C'://High Carbon Dioxide
                printf("High Carbon Dioxide, ");
                break;
            case 'O'://High Oxygen
                printf("High Oxygen, ");
                break;
            case 'p'://Pollutants
                printf("Pollutants, ");
                break;
            case 'I'://Inert Gases
                printf("Inert Gases, ");
                break;
            case 'n'://Nitrogen Compounds
                printf("Nitrogen Compounds, ");
                break;
            default:
                printf("\nFailure on line %d (%c)\n", __LINE__, system.stars[star].planets[planet].atmosphere.marginality);
                break;
        }

        if(system.stars[star].planets[planet].atmosphere.suffocating == 'S')
            printf("Suffocating, ");
        else
            printf("Non-Suffocating, ");

        switch(system.stars[star].planets[planet].atmosphere.toxicity)
        {
            case 'M'://Mildly Toxic
                printf("Mildly Toxic, ");
                break;
            case 'H'://Highly Toxic
                printf("Highly Toxic, ");
                break;
            case 'L'://Lethally Toxic
                printf("Lethaly Toxic, ");
                break;
            case 'N'://Not Toxic
                printf("Non-Toxic, ");
                break;
            default:
                printf("\nFailure on line %d\n", __LINE__);
                break;
        }

        if(system.stars[star].planets[planet].atmosphere.corrosivity == 'C')
            printf("Corrosive");
        else
            printf("Non-Corrosive");
    }
    else//Its a moon
    {
        switch(system.stars[star].planets[planet].moons[moon].atmosphere.marginality)
        {
            case 'P'://Poisonous
                printf("Poisonous, ");
                break;
            case 'V'://Vacuum
                printf("Vacuum\n");
                return;
            case 'N'://Not Marginal
                printf("Non-Marginal, ");
                break;
            case 'o'://Low Oxygen
                printf("Low Oxygen, ");
                break;
            case 'F'://Fluorine
                printf("Fluorine, ");
                break;
            case 'S'://Sulphur Compounds
                printf("Sulphur Compounds, ");
                break;
            case 'c'://Chlorine
                printf("Chlorine, ");
                break;
            case 'T'://Organic Toxins
                printf("Organic Toxins, ");
                break;
            case 'C'://High Carbon Dioxide
                printf("High Carbon Dioxide, ");
                break;
            case 'O'://High Oxygen
                printf("High Oxygen, ");
                break;
            case 'p'://Pollutants
                printf("Pollutants, ");
                break;
            case 'I'://Inert Gases
                printf("Inert Gases, ");
                break;
            case 'n'://Nitrogen Compounds
                printf("Nitrogen Compounds, ");
                break;
            default:
                printf("\nFailure on line %d (%c)\n", __LINE__, system.stars[star].planets[planet].moons[moon].atmosphere.marginality);
                break;
        }

        if(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'S')
            printf("Suffocating, ");
        else
            printf("Non-Suffocating, ");

        switch(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity)
        {
            case 'M'://Mildly Toxic
                printf("Mildly Toxic, ");
                break;
            case 'H'://Highly Toxic
                printf("Highly Toxic, ");
                break;
            case 'L'://Lethally Toxic
                printf("Lethaly Toxic, ");
                break;
            case 'N'://Not Toxic
                printf("Non-Toxic, ");
                break;
            default:
                printf("\nFailure on line %d (%c)\n", __LINE__, system.stars[star].planets[planet].moons[moon].atmosphere.toxicity);
                break;
        }

        if(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'C')
            printf("Corrosive");
        else
            printf("Non-Corrosive");
    }

    return;
}

//Returns a 1 if it is a planet that can support an atmosphere, a 0 if it can't
int atmosphereCheck(char worldSize, char worldType)
{
    //Planet Type then size,
    //[0], 'A' = Asteroid Belt, 'E' = Empty, 'I' = Ice, 'H' = Hadean, 'R' = Rock, 'S' = Sulfur,
    //'O' = Ocean, 'G' = Garden, 'g' = Green House, 'a' = Ammonia, 'C' = Chthonian
    //[1], 'T' = Tiny, 'S' = Small, 'M' = Medium or Standard, 'L' = Large

    if((worldSize == 'T') && ((worldType == 'I') || (worldType == 'R') || (worldType == 'S')))
        return 0;
    else if((worldSize == 'S') && ((worldType == 'H') || (worldType == 'R')))
        return 0;
    else if((worldSize == 'M') && ((worldType == 'H') || (worldType == 'C')))
        return 0;
    else if((worldSize == 'L') && (worldType == 'C'))
        return 0;
    else if((worldSize == 'B') || (worldSize == 'E'))
        return 0;
    else if(worldType == 'G')//Gas Giant
        return 0;

    return 1;//If it gets to this point then it is atmosphere generatable
}

struct  solarSystem orbitSort(struct solarSystem system)
{
    //sortDirection = 1 then highest to lowest, sortDirection = 0 then lowest to highest
    //This is a Bubble Sort implementation I borrowed from the internet and modified slightly

    int     loop = 0,
            planet = 0,
            star = 0,
            offset;
    float   temp = 0.0;

    for(loop = 0; loop < 3; ++loop)//Increments the number of planets, 0 is a bad place to start (Later decremented)
        system.stars[loop].numberOfPlanets++;//I don't like this at all!

    for(star = 0; star < 3; ++star)
    {
        for(loop = 0; loop < (system.stars[star].numberOfPlanets - 1); ++loop)
        {
            for(planet = 0; planet < (20 - ( loop + 1)); ++planet)
            {
                if(system.stars[star].planets[planet].orbit > system.stars[star].planets[planet + 1].orbit)
                {
                    temp = system.stars[star].planets[planet].orbit;
                    system.stars[star].planets[planet].orbit = system.stars[star].planets[planet + 1].orbit;
                    system.stars[star].planets[planet + 1].orbit = temp;
                }
            }
        }

        //Top align the sort
        offset = 0;
        for(planet = 0; planet < MAX_PLANETS; ++planet)
        {
            //Test for blank orbit
            if(testFloatEquality(system.stars[star].planets[planet].orbit, 0.0, 0.0001))
                ++offset;//Count it as a blank orbit
            else
            {
                system.stars[star].planets[planet-offset].orbit = system.stars[star].planets[planet].orbit;
                system.stars[star].planets[planet].orbit = 0;
            }
        }
   }

    for(loop = 0; loop < 3; ++loop)//Decrements the number of planets, returns the values to what they should be
        system.stars[loop].numberOfPlanets--;//I don't like this at all!

    return system;
}

float nextOrbit(float currentOrbit, int direction)//Returns the next orbit, direction = 1 then going outward, direction = 0 then inward
{
    int     dieRoll;
    float   multiplier;

    dieRoll = polyRollDice(3,6);

    switch(dieRoll)
    {
        case 3:
        case 4:
            multiplier = 1.4;
            break;
        case 5:
        case 6:
            multiplier = 1.5;
            break;
        case 7:
        case 8:
            multiplier = 1.6;
            break;
        case 9:
        case 10:
        case 11:
        case 12:
            multiplier = 1.7;
            break;
        case 13:
        case 14:
            multiplier = 1.8;
            break;
        case 15:
        case 16:
            multiplier = 1.9;
            break;
        case 17:
        case 18:
            multiplier = 2.0;
            break;
        default:
            printf("\nFailure on line %d (%d)\n", __LINE__, dieRoll);
            break;
    }

    if(direction == 1)
        currentOrbit *= multiplier;
    else if(direction == 0)
        currentOrbit /= multiplier;
    else
        printf("\nFailure on line %d\n", __LINE__);

    return currentOrbit;
}

//Returns the planet or moon type
char planetoidType(float blackbodyTemp, char worldSize, char worldType, float mass, float stellarAge)//Returns the world or moons type
{
    int     bonus;

    //Tiny Planets
    if((worldSize == 'T') && (blackbodyTemp < 140))
    {
        if(worldType == 'G')//Only a Gas giant can have a sulphur moon and even then only sometimes!
            if(polyRollDice(1,6) < 4)
                return 'S';//Sulphur
            else
                return 'I';//Ice planet
        else
            return 'I';//Ice planet
    }
    else if(worldSize == 'T')
        return 'R';//Rock

    //Small Planets
    if((worldSize == 'S') && (blackbodyTemp < 80))
        return 'H';//Hadean
    else if((worldSize == 'S') && (blackbodyTemp > 80) && (blackbodyTemp < 141))
        return 'I';//Ice
    else if(worldSize == 'S')
        return 'R';//Rock

    //Medium or Standard Planets
    if((worldSize == 'M') && (blackbodyTemp < 80))
        return 'H';//Hadean
    else if((worldSize == 'M') && (blackbodyTemp > 80) && (blackbodyTemp < 150))
        return 'I';//Ice
    else if((worldSize == 'M') && (blackbodyTemp > 150) && (blackbodyTemp < 230))
    {
        if(mass < 0.65)
            return 'a';//Ammonia
        else
            return 'I';//ice
    }
    else if((worldSize == 'M') && (blackbodyTemp > 230) && (blackbodyTemp < 240))
        return 'I';//Ice
    else if((worldSize == 'M') && (blackbodyTemp > 240) && (blackbodyTemp < 320))
    {
        bonus = stellarAge / 0.5;
        if(bonus > 10)
            bonus = 10;

        if((polyRollDice(3,6) + bonus) > 18)//Add one to the roll for every 500 million years the age of the star system is
            return 'r';//Garden
        else
            return 'O';//Ocean
    }
    else if((worldSize == 'M') && (blackbodyTemp > 320) && (blackbodyTemp < 500))
        return 'g';//Greenhouse
    else if(worldSize == 'M')
        return 'C';//Chthonian

    //Large Planets
    if((worldSize == 'L') && (blackbodyTemp < 150))
        return 'I';//Ice
    else if((worldSize == 'L') && (blackbodyTemp > 150) && (blackbodyTemp < 230))
        if(mass < 0.65)
            return 'a';//Ammonia
        else
            return 'I';//ice
    else if((worldSize == 'L') && (blackbodyTemp > 230) && (blackbodyTemp < 240))
        return 'I';//Ice
    else if((worldSize == 'L') && (blackbodyTemp > 240) && (blackbodyTemp < 320))
    {
        bonus = stellarAge / 0.5;
        if(bonus > 5)
            bonus = 5;

        if((polyRollDice(3,6) + bonus) > 18)//Add one to the roll for every 500 million years the age of the star system is
            return 'r';//Garden
        else
            return 'O';//Ocean
    }
    else if((worldSize == 'L') && (blackbodyTemp > 320) && (blackbodyTemp < 500))
        return 'g';//Greenhouse
    else if(worldSize == 'L')
        return 'C';//Chthonian

    return 0;//Something has gone wrong!
}

char climate(int temperature)
{
    if(temperature < 244)//Frozen
        return 'F';
    else if(temperature < 255)//Very Cold
        return 'v';
    else if(temperature < 266)//Cold
        return 'c';
    else if(temperature < 278)//Chilly
        return 'y';
    else if(temperature < 289)//Cool
        return 'C';
    else if(temperature < 300)//Normal
        return 'N';
    else if(temperature < 311)//Warm
        return 'W';
    else if(temperature < 322)//Tropical
        return 'T';
    else if(temperature < 333)//Hot
        return 'H';
    else if(temperature < 344)//Very Hot
        return 'V';
    else//the temperature is above 344k, Infernal
        return 'I';
}

//Returns the average temperature in kelvins
unsigned int averageTemperature(char size, char type, int hydro, float atmosphericMass, float blackbody)
{
    float   absorbtion,
            greenHouse;

    if(type == 'A')//Asteroid Belts
    {
        absorbtion = 0.97;
        greenHouse = 0;
    }
    else if((type == 'I') && (size == 'T'))//Tiny Ice
    {
        absorbtion = 0.86;
        greenHouse = 0;
    }
    else if((type == 'R') && (size == 'T'))//Tiny Rock
    {
        absorbtion = 0.97;
        greenHouse = 0;
    }
    else if((type == 'S') && (size == 'T'))//Tiny Sulphur
    {
        absorbtion = 0.77;
        greenHouse = 0;
    }
    else if((type == 'H') && (size == 'S'))//Small Hadean
    {
        absorbtion = 0.67;
        greenHouse = 0;
    }
    else if((type == 'I') && (size == 'S'))//Small Ice
    {
        absorbtion = 0.93;
        greenHouse = 0.1;
    }
    else if((type == 'R') && (size == 'S'))//Small Rock
    {
        absorbtion = 0.96;
        greenHouse = 0;
    }
    else if((type == 'H') && (size == 'M'))//Standard Hadean
    {
        absorbtion = 0.67;
        greenHouse = 0;
    }
    else if((type == 'a') && ((size == 'M') || (size == 'L')))// Standard or Large Ammonia
    {
        absorbtion = 0.84;
        greenHouse = 0.2;
    }
    else if((type == 'I') && ((size == 'M') || (size == 'L')))// Standard or Large Ice
    {
        absorbtion = 0.86;
        greenHouse = 0.2;
    }
    else if((((type == 'O') || (type == 'r')) && ((size == 'M') || (size == 'L'))) && (hydro <= 20))// Standard or Large Ocean/Garden with hydrographic coverage of 20% or less
    {
        absorbtion = 0.95;
        greenHouse = 0.16;
    }
    else if((((type == 'O') || (type == 'r')) && ((size == 'M') || (size == 'L'))) && (hydro <= 50))// Standard or Large Ocean/Garden with hydrographic coverage of 21-50 %
    {
        absorbtion = 0.92;
        greenHouse = 0.16;
    }
    else if((((type == 'O') || (type == 'r')) && ((size == 'M') || (size == 'L'))) && (hydro <= 90))// Standard or Large Ocean/Garden with hydrographic coverage of 51-90%
    {
        absorbtion = 0.88;
        greenHouse = 0.16;
    }
    else if(((type == 'O') || (type == 'r')) && ((size == 'M') || (size == 'L')))// Standard or Large Ocean/Garden with hydrographic coverage of 91%+
    {
        absorbtion = 0.84;
        greenHouse = 0.16;
    }
    else if((type == 'g') && ((size == 'M') || (size == 'L')))// Standard or Large Greenhouse
    {
        absorbtion = 0.77;
        greenHouse = 2.0;
    }
    else if((type == 'C') && ((size == 'M') || (size == 'L')))// Standard or Large Cthonian
    {
        absorbtion = 0.97;
        greenHouse = 0;
    }

    return (blackbody * absorbtion * (1 + (atmosphericMass * greenHouse)));

/*
    //If creating just a world then making a system around it, then use the following code.
    //Otherwise if your building a generic solar system, use the above code
    if(type == 'A')//Asteroid Belt
        return 140 + (polyRollDice(3,6) - 3) * 24;
    else if((size == 'T') && ((type == 'I') || (type == 'S')))//Tiny Ice or Sulfur
        return 80 + (polyRollDice(3,6) - 3) * 4;
    else if((size == 'T') && (type == 'R'))//Tiny Rock
        return 140 + (polyRollDice(3,6) - 3) * 24;
    else if((size == 'S') && (type == 'H'))//Small Hadean
        return 50 + (polyRollDice(3,6) - 3) * 2;
    else if((size == 'S') && (type == 'I'))//Small Ice
        return 80 + (polyRollDice(3,6) - 3) * 4;
    else if((size == 'S') && (type == 'R'))//Small Rock
        return 140 + (polyRollDice(3,6) - 3) * 24;
    else if((size == 'S') && (type == 'H'))//Standard Hadean
        return 50 + (polyRollDice(3,6) - 3) * 2;
    else if((size == 'S') && (type == 'a'))//Standard Ammonia
        return 140 + (polyRollDice(3,6) - 3) * 5;
    else if((size == 'S') && (type == 'I'))//Standard Ice
        return 80 + (polyRollDice(3,6) - 3) * 10;
    else if((size == 'S') && ((type == 'O') || (type == 'r')))//Standard Ocean or Garden
        return 250 + (polyRollDice(3,6) - 3) * 6;
    else if((size == 'S') && ((type == 'g') || (type == 'C')))//Standard Greenhouse or Chthonian
        return 500 + (polyRollDice(3,6) - 3) * 30;
    else if((size == 'L') && (type == 'a'))//Large Ammonia
        return 140 + (polyRollDice(3,6) - 3) * 5;
    else if((size == 'L') && (type == 'I'))//Large Ice
        return 80 + (polyRollDice(3,6) - 3) * 10;
    else if((size == 'L') && ((type == 'O') || (type == 'r')))//Large Ocean or Garden
        return 250 + (polyRollDice(3,6) - 3) * 6;
    else if((size == 'L') && ((type == 'g') || (type == 'C')))//Large Greenhouse or Chthonian
        return 500 + (polyRollDice(3,6) - 3) * 30;
*/
}

struct solarSystem worldSizesGasGiant(struct solarSystem system, int star, int planet)//Determines all of the Gas Giants unique elements
{
    //Mass and Density of a planet
    switch(system.stars[star].planets[planet].size)
    {
        case 'S':
            switch(polyRollDice(3, 6))
            {
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                    system.stars[star].planets[planet].mass = 10;
                    system.stars[star].planets[planet].density = 0.42;
                    break;
                case 9:
                case 10:
                    system.stars[star].planets[planet].mass = 15;
                    system.stars[star].planets[planet].density = 0.26;
                    break;
                case 11:
                    system.stars[star].planets[planet].mass = 20;
                    system.stars[star].planets[planet].density = 0.22;
                    break;
                case 12:
                    system.stars[star].planets[planet].mass = 30;
                    system.stars[star].planets[planet].density = 0.19;
                    break;
                case 13:
                    system.stars[star].planets[planet].mass = 40;
                    system.stars[star].planets[planet].density = 0.17;
                    break;
                case 14:
                    system.stars[star].planets[planet].mass = 50;
                    system.stars[star].planets[planet].density = 0.17;
                    break;
                case 15:
                    system.stars[star].planets[planet].mass = 60;
                    system.stars[star].planets[planet].density = 0.17;
                    break;
                case 16:
                    system.stars[star].planets[planet].mass = 70;
                    system.stars[star].planets[planet].density = 0.17;
                    break;
                case 17:
                case 18:
                    system.stars[star].planets[planet].mass = 80;
                    system.stars[star].planets[planet].density = 0.17;
                    break;
                default:
                    printf("\nFailure on line %d\n", __LINE__);
                    break;
            }
            break;
        case 'M':
            switch(polyRollDice(3, 6))
                        {
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                    system.stars[star].planets[planet].mass = 100;
                    system.stars[star].planets[planet].density = 0.18;
                    break;
                case 9:
                case 10:
                    system.stars[star].planets[planet].mass = 150;
                    system.stars[star].planets[planet].density = 0.19;
                    break;
                case 11:
                    system.stars[star].planets[planet].mass = 200;
                    system.stars[star].planets[planet].density = 0.2;
                    break;
                case 12:
                    system.stars[star].planets[planet].mass = 250;
                    system.stars[star].planets[planet].density = 0.22;
                    break;
                case 13:
                    system.stars[star].planets[planet].mass = 300;
                    system.stars[star].planets[planet].density = 0.24;
                    break;
                case 14:
                    system.stars[star].planets[planet].mass = 350;
                    system.stars[star].planets[planet].density = 0.25;
                    break;
                case 15:
                    system.stars[star].planets[planet].mass = 400;
                    system.stars[star].planets[planet].density = 0.26;
                    break;
                case 16:
                    system.stars[star].planets[planet].mass = 450;
                    system.stars[star].planets[planet].density = 0.27;
                    break;
                case 17:
                case 18:
                    system.stars[star].planets[planet].mass = 500;
                    system.stars[star].planets[planet].density = 0.29;
                    break;
                default:
                    printf("\nFailure on line %d\n", __LINE__);
                    break;
            }
            break;
        case 'L':
            switch(polyRollDice(3, 6))
                        {
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                    system.stars[star].planets[planet].mass = 600;
                    system.stars[star].planets[planet].density = 0.31;
                    break;
                case 9:
                case 10:
                    system.stars[star].planets[planet].mass = 800;
                    system.stars[star].planets[planet].density = 0.35;
                    break;
                case 11:
                    system.stars[star].planets[planet].mass = 1000;
                    system.stars[star].planets[planet].density = 0.4;
                    break;
                case 12:
                    system.stars[star].planets[planet].mass = 1500;
                    system.stars[star].planets[planet].density = 0.6;
                    break;
                case 13:
                    system.stars[star].planets[planet].mass = 2000;
                    system.stars[star].planets[planet].density = 0.8;
                    break;
                case 14:
                    system.stars[star].planets[planet].mass = 2500;
                    system.stars[star].planets[planet].density = 1.0;
                    break;
                case 15:
                    system.stars[star].planets[planet].mass = 3000;
                    system.stars[star].planets[planet].density = 1.2;
                    break;
                case 16:
                    system.stars[star].planets[planet].mass = 3500;
                    system.stars[star].planets[planet].density = 1.4;
                    break;
                case 17:
                case 18:
                    system.stars[star].planets[planet].mass = 4000;
                    system.stars[star].planets[planet].density = 1.6;
                    break;
                default:
                    printf("\nFailure on line %d\n", __LINE__);
                    break;
            }
            break;
        default:
            printf("\nFailure on line %d\n", __LINE__);
    }

    //Diameter
    system.stars[star].planets[planet].diameter = cbrt(system.stars[star].planets[planet].mass / system.stars[star].planets[planet].density);

    //Gravity at the cloud tops
    system.stars[star].planets[planet].gravity = worldGravity(system.stars[star].planets[planet].diameter, system.stars[star].planets[planet].density);

    //MMWR
    system.stars[star].planets[planet].MMWR = MMWR(system.stars[star].planets[planet].blackbodyTemperature, system.stars[star].planets[planet].diameter, system.stars[star].planets[planet].density);

    //Atmospheric Pressure
    system.stars[star].planets[planet].atmosphere.pressure = 0;//There is no //No what, what was I thinking?!

    return system;
}

float atmosphericPressure(char size, char type, float atmoMass, float gravity)
{
    float pressureFactor;

    if(type == 'A')//Asteroid Belt
        return 0;
    else if(type == 'E')
        return 0;
    else if((size == 'T') && (type == 'I'))//Tiny Ice
        return 0;
    else if((size == 'T') && (type == 'S'))//Tiny Sulfur
        return 0;
    else if((size == 'T') && (type == 'R'))//Tiny Rock
        return 0;
    else if((size == 'S') && (type == 'H'))//Small Hadean
        return 0;
    else if((size == 'S') && (type == 'I'))//Small Ice
        pressureFactor = 10;
    else if((size == 'S') && (type == 'R'))//Small Rock
        return 0.01;//Trace Atmosphere
    else if((size == 'M') && (type == 'H'))//Standard Hadean
        return 0;
    else if((size == 'M') && (type == 'a'))//Standard Ammonia
        pressureFactor = 1;
    else if((size == 'M') && (type == 'I'))//Standard Ice
        pressureFactor = 1;
    else if((size == 'M') && (type == 'O'))//Standard Ocean
        pressureFactor = 1;
    else if((size == 'M') && (type == 'r'))//Standard Garden
        pressureFactor = 1;
    else if((size == 'M') && (type == 'g'))//Standard Greenhouse
        pressureFactor = 100;
    else if((size == 'M') && (type == 'C'))//Large Chthonian
        return 0.01;//Trace Atmosphere
    else if((size == 'L') && (type == 'a'))//Large Ammonia
        pressureFactor = 5;
    else if((size == 'L') && (type == 'I'))//Large Ice
        pressureFactor = 5;
    else if((size == 'L') && (type == 'O'))//Large Ocean
        pressureFactor = 5;
    else if((size == 'L') && (type == 'r'))//Large Garden
        pressureFactor = 5;
    else if((size == 'L') && (type == 'g'))//Large Greenhouse
        pressureFactor = 500;
    else if((size == 'L') && (type == 'C'))//Large Chthonian
        return 0.01;//Trace Atmosphere
    else
        printf("\nFailure on line %d(size = %c, type = %c, ID = %d)\n", __LINE__, size, type, IDnumber);

    return (pressureFactor * atmoMass * gravity);
}

//Returns the minimum molecular weight of the molecules that can be retained by a planet, lower is better
float MMWR(float blackbody, float diameter, float density)
{
/*
        In effect, every world has a  minimum molecular weight retained
    (MMWR) that indicates what volatile substances can be held onto
    across billion-year time scales. Volatiles with molecular weight higher
    than the MMWR will stay in the world�s atmosphere and on its surface.
    Volatiles with lower molecular weight will be lost to space in a relative-
    ly short time after the world is formed.
        A world�s physical parameters will fit its selected World Type if its
    MMWR is legal for its size class. A Large world must have MMWR
    greater than 2, but less than or equal to 4. A Standard world must have
    MMWR greater than 4, but less than or equal to 18. A Small world must
    have MMWR greater than 18, but less than or equal to 28. A Tiny world
    must have MMWR greater than 28.
        For comparison, some of the more important molecular weights are:
    hydrogen 2, helium 4, methane 16, ammonia 17, water vapor 18, neon
    20, carbon monoxide 28, nitrogen 28, nitric oxide 30, oxygen 32, hydro-
    gen sulfide 34, argon 40, and carbon dioxide 44.
*/
    if((diameter == 0) || (density == 0))
        return 0;

    return (blackbody / (60 * density * diameter * diameter));
}

float worldMass(float density, float diameter)
{
    return (density * diameter * diameter * diameter);
}

float worldGravity(float diameter, float density)
{
    return (diameter * density);
}

float worldDiameter(int blackbody, float density, char size)
{
    float   min,
            max;

    if((size == 'E') || (size == 'B'))//Empty Orbit or asteroid belt
        return 0;

    if(size == 'T')//Tiny
    {
        min = 0.004;
        max = 0.024;
    }
    else if(size == 'S')//Small
    {
        min = 0.024;
        max = 0.03;
    }
    else if(size == 'M')//Medium
    {
        min = 0.03;
        max = 0.065;
    }
    else if(size == 'L')//Large
    {
        min = 0.065;
        max = 0.091;
    }
    else
        printf("\nFailure on line %d(size = %c\n", __LINE__, size);

    min *= sqrt(blackbody / density);
    max *= sqrt(blackbody / density);

    //Multiply by 7930 to get this number in miles
    return (((max - min)/10) * (polyRollDice(2,6) - 2) + min);
}

float worldDensity(char size, char type)
{
    if(type == 'A')//Asteroid Belt
        return 0;
    else if(type == 'E')
        return 0;
    else if((size == 'T') && (type == 'I'))//Tiny Ice
        return icyCore();
    else if((size == 'T') && (type == 'S'))//Tiny Sulfur
        return icyCore();
    else if((size == 'T') && (type == 'R'))//Tiny Rock
        return smallIronCore();
    else if((size == 'S') && (type == 'H'))//Small Hadean
        return icyCore();
    else if((size == 'S') && (type == 'I'))//Small Ice
        return icyCore();
    else if((size == 'S') && (type == 'R'))//Small Rock
        return smallIronCore();
    else if((size == 'M') && (type == 'H'))//Standard Hadean
        return icyCore();
    else if((size == 'M') && (type == 'a'))//Standard Ammonia
        return icyCore();
    else if((size == 'M') && (type == 'I'))//Standard Ice
        return largeIronCore();
    else if((size == 'M') && (type == 'O'))//Standard Ocean
        return largeIronCore();
    else if((size == 'M') && (type == 'r'))//Standard Garden
        return largeIronCore();
    else if((size == 'M') && (type == 'g'))//Standard Greenhouse
        return largeIronCore();
    else if((size == 'M') && (type == 'C'))//Standard Chthonian
        return largeIronCore();
    else if((size == 'L') && (type == 'a'))//Large Ammonia
        return icyCore();
    else if((size == 'L') && (type == 'I'))//Large Ice
        return largeIronCore();
    else if((size == 'L') && (type == 'O'))//Large Ocean
        return largeIronCore();
    else if((size == 'L') && (type == 'r'))//Large Garden
        return largeIronCore();
    else if((size == 'L') && (type == 'g'))//Large Greenhouse
        return largeIronCore();
    else if((size == 'L') && (type == 'C'))//Large Chthonian
        return largeIronCore();
    else
        printf("\nFailure on line %d (Size = %c and Type = %c, ID = %d)\n", __LINE__, size, type, IDnumber);

    return 0;
}

float icyCore()
{
    switch(polyRollDice(3, 6))
    {
        case 3:
        case 4:
        case 5:
        case 6:
            return 0.3;
            break;
        case 7:
        case 8:
        case 9:
        case 10:
            return 0.4;
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            return 0.5;
            break;
        case 15:
        case 16:
        case 17:
            return 0.6;
            break;
        case 18:
            return 0.7;
            break;
        default:
            printf("\nFailure on line %d\n", __LINE__);
            break;
    }

    return 0;//Failure condition
}

float smallIronCore()
{
    switch(polyRollDice(3, 6))
    {
        case 3:
        case 4:
        case 5:
        case 6:
            return 0.6;
            break;
        case 7:
        case 8:
        case 9:
        case 10:
            return 0.7;
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            return 0.8;
            break;
        case 15:
        case 16:
        case 17:
            return 0.9;
            break;
        case 18:
            return 1.0;
            break;
        default:
            printf("\nFailure on line %d\n", __LINE__);
            break;
    }

    return 0;//Failure condition
}

float largeIronCore()
{
    switch(polyRollDice(3, 6))
    {
        case 3:
        case 4:
        case 5:
        case 6:
            return 0.8;
            break;
        case 7:
        case 8:
        case 9:
        case 10:
            return 0.9;
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            return 1.0;
            break;
        case 15:
        case 16:
        case 17:
            return 1.1;
            break;
        case 18:
            return 1.2;
            break;
        default:
            printf("\nFailure on line %d\n", __LINE__);
            break;
    }

    return 0;//Failure condition
}

float localCalendar(float sidereal, float period)
{
    if(testFloatEquality(sidereal, period, 0.0001))
        return 34028234700000000000000000000000.0;//Since infinite is hard to do, return a very large number
    else
        return ((sidereal * period) / (sidereal - period));
}

//Returns the rotational period in days
float randomRotationalPeriod(char type, char size)
{
    int     roll,
            modifier;
    float   period;

    if((size == 'B') || (size == 'E'))//Empty orbits and Asteroid belts don't rotate, they do orbit however
        return 0;

    roll = polyRollDice(3,6);

    if(type == 'G')//Gass giants are different
        if(size == 'S')
            modifier = 6;
        else
            modifier = 0;
    else
        if(size == 'L')
            modifier = 6;
        else if(size == 'M')
            modifier = 10;
        else if(size == 'S')
            modifier = 14;
        else if(size == 'T')
            modifier = 18;
        else
            printf("\nFailure on line %d (%c)\n", __LINE__, size);

    period = (roll + modifier) / 24.0;//Converts the result to days

    if((roll > 16) || ( period > 36))//Special rules apply
        switch(polyRollDice(2,6))
        {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                break;//Don't modify the original roll
            case 7:
                period = polyRollDice(1,6) * 2;
                break;
            case 8:
                period = polyRollDice(1,6) * 5;
                break;
            case 9:
                period = polyRollDice(1,6) * 10;
                break;
            case 10:
                period = polyRollDice(1,6) * 20;
                break;
            case 11:
                period = polyRollDice(1,6) * 50;
                break;
            case 12:
                period = polyRollDice(1,6) * 100;
                break;
            default:
                printf("\nFailure on line %d\n", __LINE__);
                break;
        }

    return period;//Returns the number in days, not hours
}

struct solarSystem moonOrbitSort(struct solarSystem system, int star, int planet)
{
	int		moon;
	float	array[8];

	//Fill the array
	for(moon = 0; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
		array[moon] = system.stars[star].planets[planet].moons[moon].orbit;

	//Sort the array
	floatBubbleSort(array, moon, 0);

	//Reinput the array back into system
	for(moon = 0; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
		system.stars[star].planets[planet].moons[moon].orbit = array[moon];

	return system;
}

struct solarSystem moonOrbitFixer(struct solarSystem system, int star, int planet)
{
//can't let these moons be too close to each other in their orbits
//gas giants differ from terrestrials!
    int moon;

    //Sort the moons first, according to orbit, inner to outer
    for(moon = 1; moon < system.stars[star].planets[planet].majourMoons; ++moon)//Less than (instead of <= ) so that this doesn't run on the last moon, which as a result is guaranteed to be located correctly
        if(system.stars[star].planets[planet].type == 'G')//Its a gas Giants
            if((system.stars[star].planets[planet].moons[moon].orbit + system.stars[star].planets[planet].diameter) < system.stars[star].planets[planet].moons[moon+1].orbit)//If there is a moon farther out but within 1 planetary diameter of this moon
                continue;//All is well
            else
                system.stars[star].planets[planet].moons[moon+1].orbit = system.stars[star].planets[planet].diameter + system.stars[star].planets[planet].moons[moon].orbit;//Bump it out to the next legal orbit
        else//Its a terrestrial planet
            if((system.stars[star].planets[planet].moons[moon].orbit + system.stars[star].planets[planet].diameter * 5) < system.stars[star].planets[planet].moons[moon+1].orbit)//If there is a moon farther out but within 1 planetary diameter of this moon
                continue;//All is well
            else
                system.stars[star].planets[planet].moons[moon+1].orbit = system.stars[star].planets[planet].diameter * 5 + system.stars[star].planets[planet].moons[moon].orbit;//Bump it out to the next legal orbit

    return system;
}

float satelliteOrbitalRadius(float planetDiameter, int moonType, char planetType, char moonSize, char planetSize)
{
    //Moon Types: 1 = Inner Moonlets, 2 = Majour Moon, 3 = outer Moonlets
    //Run differently for Gas Giants vs terrestrials
    int dieRoll;

    if(moonType == 1)//Inner Moonlets
        return (polyRollDice(1,6) / 4.0 * planetDiameter);
    else if((moonType == 2) && (planetType == 'G'))//Gas Giant Majour moons
    {
        dieRoll = polyRollDice(3,6);
        if(dieRoll >= 15)
            dieRoll += polyRollDice(2,6);
        dieRoll /= 2;
        return (dieRoll * planetDiameter);
    }
    else if(moonType == 2)//Terrestrial Majour Moons
    {
        dieRoll = polyRollDice(2,6);

        //Two size classes smaller
        if((planetSize == 'L') && ((moonSize == 'T') || (moonSize == 'S')))
            dieRoll += 2;
        else if((planetSize == 'M') && (moonSize == 'T'))
            dieRoll += 2;

        //One size catergory Smaller
        if((planetSize == 'L') && (moonSize == 'M'))
            dieRoll += 4;
        else if((planetSize == 'M') && (moonSize == 'S'))
            dieRoll += 4;
        else if((planetSize == 'S') && (moonSize == 'T'))
            dieRoll += 4;

        dieRoll *= 2.5;

        return dieRoll;
    }
    else if(moonType == 3)//Outer Moonlets
    {
        //I am told to select radii based on if I need to or not, this is unacceptable so I am improvising
        dieRoll = planetDiameter * 180 / polyRollDice(3,6) + 20;
        return dieRoll;
    }
    else
        printf("\nFailure on line %d\n", __LINE__);

    return 0;
}

float orbitalPeriodDays(float distance, float mass)//Returns the orbital time in days
{
    return (365.24 * sqrt(pow(distance,3) / mass));
}

//Computes the minimum and maximum orbits of a planet
float planetaryEccentricity(struct solarSystem system, int star, int planet)//Determines the eccentricity of a planets orbit
{
    int     dieRoll,
            orbit;
    float   eccentricity;

    dieRoll = polyRollDice(3,6);//Base Roll

    if(system.stars[star].planets[planet].type == 'E')//Empty orbits don't have eccentric orbits
        return 0;

    //Modifiers
    if(system.stars[star].gasGiantFlag == 3)//Its an eccentric arrangement
        for(orbit = 1; system.stars[star].planets[orbit].orbit < system.stars[star].snowLine; orbit++)//While inside the snow line
            if(system.stars[star].planets[planet].type == 'G')//AND its a gas giant
                dieRoll += 4;//It is more likely to have a higher eccentric orbit than normal

    if(system.stars[star].gasGiantFlag == 4)//Epistellar arrangemnent
    {
        for(orbit = 1; (system.stars[star].planets[orbit].orbit < (system.stars[star].innerLimitRadius * 1.8)) && (orbit <= system.stars[star].numberOfPlanets); ++orbit)//While inside epistellar range
            if(system.stars[star].planets[planet].type == 'G')//AND its a gas giant
                dieRoll -= 6;
    }

    if(system.stars[star].gasGiantFlag == 2)//Conventional arrangement
        dieRoll -= 6;//Unlikely to have eccentric orbits

    //Confine to the table
    if(dieRoll > 18)
        dieRoll = 18;
    if(dieRoll < 3)
        dieRoll = 3;

    //The eccentricity table
    switch(dieRoll)
    {
        case 3:
            eccentricity = 0;
            break;
        case 4:
        case 5:
        case 6:
            eccentricity = 0.05;
            break;
        case 7:
        case 8:
        case 9:
            eccentricity = 0.1;
            break;
        case 10:
        case 11:
            eccentricity = 0.15;
            break;
        case 12:
            eccentricity = 0.2;
            break;
        case 13:
            eccentricity = 0.3;
            break;
        case 14:
            eccentricity = 0.4;
            break;
        case 15:
            eccentricity = 0.5;
            break;
        case 16:
            eccentricity = 0.6;
            break;
        case 17:
            eccentricity = 0.7;
            break;
        case 18:
            eccentricity = 0.8;
            break;
        default:
            printf("\nFailure on line %d\n", __LINE__);
            break;
    }

    return eccentricity;
}

char  tectonics(char size, char type, char volcanism, float hydro, int moons)
{
  char  activity;
  int   modifier = 0;
  unsigned int result,
        roll;

  //Asteroid Belts and empty rings have no tectonics
  if((type == 'E') || (type == 'A'))
    return 'N';

  //Small and Tiny planets are tectonically dead
  if((size == 'T') || (size == 'S'))
    return 'N';

  //Volcanism plays a big part
  switch(volcanism)
  {
    case 'N':
      modifier -= 8;
      break;
    case 'L':
      modifier -= 4;
      break;
    case 'M':
      break;
    case 'H':
      modifier += 4;
      break;
    case 'E':
      modifier += 8;
      break;
    default:
      printf("\nFailure on line %d\n", __LINE__);
      break;
  }

  //Hydrographic coverage is also important
  if(hydro == 0)
    modifier -= 4;
  else if(hydro <= 50)
    modifier -= 2;

  //Having a moon also helps
  if((type != 'G') && (moons == 1))
    modifier += 2;
  else if((type != 'G') && (moons > 1))
    modifier += 4;

  //Roll the dice and add the modifiers
  roll = polyRollDice(3,6);
  result = roll + modifier;

  if(result <= 6)
    activity = 'N';
  else if(result <= 10)
    activity = 'L';
  else if(result <= 14)
    activity = 'M';
  else if(result <= 18)
    activity = 'H';
  else if(result >= 19)
    activity = 'E';
  else
    printf("\nFailure on line %d(%d)\n", __LINE__, result);

  return activity;
}

struct solarSystem volcanism(struct solarSystem system, int star, int planet, int moon)
{
  char  activity;
  int   modifier = 0,
        result,
        roll;

  if(moon == 0)//If it is a planet
  {
    //Asteroids and empty orbits have no volcanic activity
    if((system.stars[star].planets[planet].type == 'E') || (system.stars[star].planets[planet].type == 'A'))
    {
      system.stars[star].planets[planet].volcanicActivity = 'N';
      return system;
    }

    //+5 for terrestrial planets with a single moon ((exclude Gas Giants)
    if((system.stars[star].planets[planet].majourMoons == 1) && (system.stars[star].planets[planet].type != 'G'))
      modifier += 5;

    //+10 for terrestrial planets more than one moon ((exclude Gas Giants)
    if((system.stars[star].planets[planet].majourMoons > 1) && (system.stars[star].planets[planet].type != 'G'))
      modifier += 10;

    //+60 for Tiny Sulfur planets
    if((system.stars[star].planets[planet].size == 'T') && (system.stars[star].planets[planet].type == 'S'))
      modifier += 60;
  }
  else//This is the moon section
  {
    if(system.stars[star].planets[planet].type == 'G')//If its a moon around a gas giant
      modifier += 5;
    else//Otherwise its a terrestrial Moon, if its a tiny sulfur than keep going
      if((system.stars[star].planets[planet].size == 'T') && (system.stars[star].planets[planet].type == 'S'))
        modifier += 60;

    //This moon has a "moon" of its own, known as a planet
    modifier += 5;
  }

  //Roll the dice, add the modifiers and do a calculation :)
  roll = polyRollDice(3,6);
  result = (system.stars[star].planets[planet].gravity / system.stellarAge) * 40 + roll + modifier;

  //A switch case would be too much work for this next section
  if(result <= 16)
    activity = 'N';
  else if(result <= 20)
    activity = 'L';
  else if(result <= 26)
    activity = 'M';
  else if(result <= 70)
    activity = 'H';
  else if(result >= 71)
    activity = 'E';

  //Assign activity level to planet/moon
  if(moon != 0)//Its a planet
    system.stars[star].planets[planet].moons[moon].volcanicActivity = activity;
  else//Its a moon
    system.stars[star].planets[planet].volcanicActivity = activity;

  //May change the atmosphere
  if(((system.stars[star].planets[planet].type == 'r') && (system.stars[star].planets[planet].size == 'M')) ||//Standard Garden planet
    ((system.stars[star].planets[planet].type == 'g') && (system.stars[star].planets[planet].size == 'L')) ||//Large Green House planet
    ((system.stars[star].planets[planet].moons[moon].type == 'r') && (system.stars[star].planets[planet].moons[moon].size == 'M')) ||//Standard Garden moon
    ((system.stars[star].planets[planet].moons[moon].type == 'g') && (system.stars[star].planets[planet].moons[moon].size == 'L')))//Large Green House moon
    {
      roll = polyRollDice(3,6);
      if((roll <= 8) && (activity == 'H'))//Heavy activity
      {
        if(moon == 0)//Its a planet
        {
          if(polyRollDice(1,2) == 1)//50% chance of either pollutants or sulfur componets in the atmosphere
            system.stars[star].planets[planet].atmosphere.marginality = 'S';
          else
            system.stars[star].planets[planet].atmosphere.marginality = 'p';
        }
        else//Its a moon
        {
            if(polyRollDice(1,2) == 1)//50% chance of either pollutants or sulfur componets in the atmosphere
                system.stars[star].planets[planet].moons[moon].atmosphere.marginality = 'S';
            else
                system.stars[star].planets[planet].moons[moon].atmosphere.marginality = 'p';
        }
      }
      else if((roll <= 14) && (activity == 'E'))//Extreme activity
      {
        if(moon == 0)//Its a planet
        {
          if(polyRollDice(1,2) == 1)//50% chance of either pollutants or sulfur componets in the atmosphere
            system.stars[star].planets[planet].atmosphere.marginality = 'S';
          else
            system.stars[star].planets[planet].atmosphere.marginality = 'p';
        }
        else//Its a moon
        {
            if(polyRollDice(1,2) == 1)//50% chance of either pollutants or sulfur componets in the atmosphere
                system.stars[star].planets[planet].moons[moon].atmosphere.marginality = 'S';
            else
                system.stars[star].planets[planet].moons[moon].atmosphere.marginality = 'p';
        }
      }
    }

  return system;
}

int habitability(struct solarSystem system, int star, int planet, int moon)
{
	int modifier = 0;

	if(moon == 0)//planets
	{
		//No atmosphere or Trace atmosphere
		if((system.stars[star].planets[planet].atmosphere.marginality == 'V') ||
			(system.stars[star].planets[planet].atmosphere.pressure < 0.01))
				modifier += 0;

		//Non-breathable atmosphere, Very Thin or above, Suffocating, Toxic, and Corrosive
		if((system.stars[star].planets[planet].atmosphere.pressure >= 0.01) &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'S') &&
			(system.stars[star].planets[planet].atmosphere.toxicity != 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'C'))
				modifier -= 2;

		//Non-breathable atmosphere, Very Thin or above, Suffocating and Toxic only
		if((system.stars[star].planets[planet].atmosphere.pressure >= 0.01) &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'S') &&
			(system.stars[star].planets[planet].atmosphere.toxicity != 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'N'))
				modifier -= 1;

                //Non-breathable atmosphere, Very Thin or above, Suffocating only
		if((system.stars[star].planets[planet].atmosphere.pressure >= 0.01) &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'S') &&
			(system.stars[star].planets[planet].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'N'))
				modifier += 0;

		//Breathable atmosphere (Very Thin)
		if((system.stars[star].planets[planet].atmosphere.pressure >= 0.01) &&
			(system.stars[star].planets[planet].atmosphere.pressure <= 0.5) &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'N'))
				modifier += 1;

		//Breathable atmosphere (Thin)
		if((system.stars[star].planets[planet].atmosphere.pressure >= 0.51) &&
			(system.stars[star].planets[planet].atmosphere.pressure <= 0.8) &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'N'))
				modifier += 2;

		//Breathable atmosphere (Standard or Dense)
		if((system.stars[star].planets[planet].atmosphere.pressure >= 0.81) &&
			(system.stars[star].planets[planet].atmosphere.pressure <= 1.5) &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'N'))
				modifier += 3;

		//Breathable atmosphere (Very Dense or Superdense)
		if((system.stars[star].planets[planet].atmosphere.pressure >= 1.51) &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'N'))
				modifier += 1;

		//Breathable atmosphere is not Marginal
		if((system.stars[star].planets[planet].atmosphere.marginality == 'N') &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'N'))
				modifier += 1;

		//No liquid-water oceans, or Hydrographic Coverage 0%
		if(system.stars[star].planets[planet].hydrographicCoverage == 0)
			modifier += 0;

		//Liquid-water oceans, Hydrographic Coverage 1% to 59%
		if(system.stars[star].planets[planet].hydrographicCoverage <= 59)
			modifier += 1;

		//Liquid-water oceans, Hydrographic Coverage 60% to 90%
		if((system.stars[star].planets[planet].hydrographicCoverage >= 60) &&
			(system.stars[star].planets[planet].hydrographicCoverage <= 90))
			modifier += 2;

		//Liquid-water oceans, Hydrographic Coverage 91% to 99%
		if((system.stars[star].planets[planet].hydrographicCoverage >= 91) &&
			(system.stars[star].planets[planet].hydrographicCoverage <= 99))
			modifier += 1;

		//Liquid-water oceans, Hydrographic Coverage 100%
		if(system.stars[star].planets[planet].hydrographicCoverage == 100)
			modifier += 0;

		//Breathable atmosphere, climate type is Frozen or Very Cold
		if(((system.stars[star].planets[planet].atmosphere.climate == 'F') ||
			(system.stars[star].planets[planet].atmosphere.climate == 'v')) &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'N'))
				modifier += 0;

		//Breathable atmosphere, climate type is Cold
		if((system.stars[star].planets[planet].atmosphere.climate == 'c') &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'N'))
				modifier += 1;

		//Breathable atmosphere, climate type is Chilly, Cool, Normal, Warm, or Tropical
		if(((system.stars[star].planets[planet].atmosphere.climate == 'y') ||
			(system.stars[star].planets[planet].atmosphere.climate == 'C') ||
			(system.stars[star].planets[planet].atmosphere.climate == 'N') ||
			(system.stars[star].planets[planet].atmosphere.climate == 'W') ||
			(system.stars[star].planets[planet].atmosphere.climate == 'T')) &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'N'))
				modifier += 2;

		//Breathable atmosphere, climate type is Hot
		if((system.stars[star].planets[planet].atmosphere.climate == 'H') &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'N'))
				modifier += 1;

		//Breathable atmosphere, climate type is Very Hot or Infernal
		if(((system.stars[star].planets[planet].atmosphere.climate == 'V') ||
			(system.stars[star].planets[planet].atmosphere.climate == 'I')) &&
			(system.stars[star].planets[planet].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].atmosphere.corrosivity == 'N'))
				modifier += 0;
	}
	else//Its a moon
	{
		//No atmosphere or Trace atmosphere
		if((system.stars[star].planets[planet].moons[moon].atmosphere.marginality == 'V') ||
			(system.stars[star].planets[planet].moons[moon].atmosphere.pressure < 0.01))
				modifier += 0;

                //Non-breathable atmosphere, Very Thin or above, Suffocating, Toxic, and Corrosive
		if((system.stars[star].planets[planet].moons[moon].atmosphere.pressure >= 0.01) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'S') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity != 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'C'))
				modifier -= 2;

		//Non-breathable atmosphere, Very Thin or above, Suffocating and Toxic only
		if((system.stars[star].planets[planet].moons[moon].atmosphere.pressure >= 0.01) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'S') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity != 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'N'))
				modifier -= 1;

		//Non-breathable atmosphere, Very Thin or above, Suffocating only
		if((system.stars[star].planets[planet].moons[moon].atmosphere.pressure >= 0.01) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'S') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'N'))
				modifier += 0;

		//Breathable atmosphere (Very Thin)
		if((system.stars[star].planets[planet].moons[moon].atmosphere.pressure >= 0.01) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.pressure <= 0.5) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'N'))
				modifier += 1;

		//Breathable atmosphere (Thin)
		if((system.stars[star].planets[planet].moons[moon].atmosphere.pressure >= 0.51) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.pressure <= 0.8) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'N'))
				modifier += 2;

		//Breathable atmosphere (Standard or Dense)
		if((system.stars[star].planets[planet].moons[moon].atmosphere.pressure >= 0.81) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.pressure <= 1.5) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'N'))
				modifier += 3;

		//Breathable atmosphere (Very Dense or Superdense)
		if((system.stars[star].planets[planet].moons[moon].atmosphere.pressure >= 1.51) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'N'))
				modifier += 1;

		//Breathable atmosphere is not Marginal
		if((system.stars[star].planets[planet].moons[moon].atmosphere.marginality == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'N'))
				modifier += 1;

		//No liquid-water oceans, or Hydrographic Coverage 0%
		if(system.stars[star].planets[planet].moons[moon].hydrographicCoverage == 0)
			modifier += 0;

		//Liquid-water oceans, Hydrographic Coverage 1% to 59%
		if(system.stars[star].planets[planet].moons[moon].hydrographicCoverage <= 59)
			modifier += 1;

		//Liquid-water oceans, Hydrographic Coverage 60% to 90%
		if((system.stars[star].planets[planet].moons[moon].hydrographicCoverage >= 60) &&
			(system.stars[star].planets[planet].moons[moon].hydrographicCoverage <= 90))
			modifier += 2;

		//Liquid-water oceans, Hydrographic Coverage 91% to 99%
		if((system.stars[star].planets[planet].moons[moon].hydrographicCoverage >= 91) &&
			(system.stars[star].planets[planet].moons[moon].hydrographicCoverage <= 99))
			modifier += 1;

		//Liquid-water oceans, Hydrographic Coverage 100%
		if(system.stars[star].planets[planet].moons[moon].hydrographicCoverage == 100)
			modifier += 0;

		//Breathable atmosphere, climate type is Frozen or Very Cold
		if(((system.stars[star].planets[planet].moons[moon].atmosphere.climate == 'F') ||
			(system.stars[star].planets[planet].moons[moon].atmosphere.climate == 'v')) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'N'))
				modifier += 0;

		//Breathable atmosphere, climate type is Cold
		if((system.stars[star].planets[planet].moons[moon].atmosphere.climate == 'c') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'N'))
				modifier += 1;

		//Breathable atmosphere, climate type is Chilly, Cool, Normal, Warm, or Tropical
		if(((system.stars[star].planets[planet].moons[moon].atmosphere.climate == 'y') ||
			(system.stars[star].planets[planet].moons[moon].atmosphere.climate == 'C') ||
			(system.stars[star].planets[planet].moons[moon].atmosphere.climate == 'N') ||
			(system.stars[star].planets[planet].moons[moon].atmosphere.climate == 'W') ||
			(system.stars[star].planets[planet].moons[moon].atmosphere.climate == 'T')) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'N'))
				modifier += 2;

		//Breathable atmosphere, climate type is Hot
		if((system.stars[star].planets[planet].moons[moon].atmosphere.climate == 'H') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'N'))
				modifier += 1;

		//Breathable atmosphere, climate type is Very Hot or Infernal
		if(((system.stars[star].planets[planet].moons[moon].atmosphere.climate == 'V') ||
			(system.stars[star].planets[planet].moons[moon].atmosphere.climate == 'I')) &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity == 'N') &&
			(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity == 'N'))
				modifier += 0;
	}

  return modifier;
}

int affinity(int RVM, int habitability)
{
  return RVM + habitability;
}

int planetRVM(char volcanicActivity)
{
  int RVM,
      modifier;

	modifier = 0;

  //Determine the modifier for the planets RVM
  switch(volcanicActivity)
  {
    case 'N':
      modifier = -2;
      break;
    case 'L':
      modifier = -1;
      break;
    case 'M':
      modifier = 0;
      break;
    case 'H':
      modifier = 1;
      break;
    case 'E':
      modifier = 2;
      break;
    default:
      printf("\nFailure on line %d\n", __LINE__);
      break;
  }

  //Determine the RVM
  RVM = polyRollDice(3,6) + modifier;

  //Determine the random part of the RVM score
  if(RVM <= 2)
    RVM = -3;
  else if(RVM <= 4)
    RVM = -2;
  else if(RVM <= 7)
    RVM = -1;
  else if(RVM <= 13)
    RVM = 0;
  else if(RVM <= 16)
    RVM = 1;
  else if(RVM <= 18)
    RVM = 2;
  else if(RVM >= 19)
    RVM = 3;

  return RVM;
}

int asteroidRVM()
{
  int RVM;

  switch(polyRollDice(3, 6))
  {
    case 3:
      RVM = -5;
      break;
    case 4:
      RVM = -4;
      break;
    case 5:
      RVM = -3;
      break;
    case 6:
    case 7:
      RVM = -2;
      break;
    case 8:
    case 9:
      RVM = -1;
      break;
    case 10:
    case 11:
      RVM = 0;
      break;
    case 12:
    case 13:
      RVM = 1;
      break;
    case 14:
    case 15:
      RVM = 2;
      break;
    case 16:
      RVM = 3;
      break;
    case 17:
      RVM = 4;
      break;
    case 18:
      RVM = 5;
      break;
    default:
      printf("\nFailure on line %d\n", __LINE__);
      break;
  }

  return RVM;
}
