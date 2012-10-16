/**************************************************************************************************
Authour:            Craig Comberbach
IDE:                CodeBlocks v10.05
Computer:           Intel Core2 Quad 2.4GHz, 2 GB RAM, Windows 7 64 bit Professional SP1
Compiler:           GNU GCC Compiler
Target Platform:    Windows
Purpose:            Procedurally generate a complete solar system using the GURPS Space rules

Unresolved issues (that may never be resolved):
1)The primary star of a binary or trinary system SHOULD have a forbidden zone, but at this time it is not factored in
2)Some forbidden zone schemes allow for planets to circle multiple suns, instead of just one of them. This is not implemented

Version History:
v1.1    May 20, 2012    -   Craig Comberbach
    World Diameter wasn't being calculated correctly (in worldDiameter() in SystemSupport.h), it was allowing ranges outside of it its range. It was sloppy math
    Corrected the spelling of marginality (was Magrinality...) throughout the comments and titles
    Fixed some issues of code ignorning forbidden zones and generating planets where there shouldn't have been
        The forbidden range was calculated and forbidden flags were set, but none of it was referenced again
    Fixed an issue where planets weren't being generated but should have been
        Primary star has a forbidden radius of 0.0, which is always less than the inner limit radius, therefore, it doesn't get planets
    Changed how planets align in  their arrays, they now align on the 0 instead of the 1
        This means all the loops that assumed 1 needed updating (and they are all pervading)
        This was a kludge at the time, but I ignored early in the project. Later when it was understood what was happening, I could have fixed it (but that would have been a lot of work, so I had left it as is)
    RVM was modified to no longer factor in tectonics when determining an RVM score (Was minorily affecting the output when it shouldn't have)
    Changed how files were opened/closed giving what looks like a 3x speed boost (opens before and after all generation is done, not both on each record)
        In addition to this, I was forgetting to close the main file, so it was never being closed, though constantly being opened to write to
        This meant that corruption was bound to happen, and this was the cause of the half written records that were overlapping the previous record

v1.0    Oct/14/2011 -    Craig Comberbach
    -First version
**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GURPS.h"
#include "random.h"
#include "GenericLibrary.h"
#include "OutputFile.h"
#include "System.h"
#include "SystemSupport.h"

#define REVISION    1.1
void displaySystem(struct solarSystem system);

int main()
{
    struct          solarSystem system;
    unsigned int    ID = 0,//Starting ID and current ID
                    maxID = 0,//Maximum ID to generate
                    choice = 0;//Output selection

    printf("Written by Craig Comberbach.\nCreated in 2011\nVersion %0.1f\n\n", REVISION);


    //Start ID Sentry
    while(ID < 1)//0 is an illegal ID
    {
        //Gather the starting ID from the user
        printf("Generate from ID: ");
        scanf("%d", &ID);
    }

    //Max ID Sentry
    while(maxID < ID)//The value has to be at least equal to the minimum ID, but also, not below it!
    {
        //Gather the maximum starting ID from the user
        printf("Generate to ID: ");
        scanf("%d", &maxID);
    }

    //Choice Sentry
    while((choice < 1) || (choice > 3))//It has to be either a 1, 2 or a 3
    {
        //Gather the user O/P choice
        printf("\n1: Database capable output (*.csv)");
        printf("\n2: Single spreadsheet output (*.csv)");
        printf("\n3: Onscreen display\n");
        printf("\nChoose output format: ");
        scanf("%d", &choice);
    }//*/

    //Formating
    printf("\n\n\n\n");

    //Open the files for edditing
    Open_Files(choice);

    for(; ID <= maxID; ++ID)
    {
        //Create the system from scratch
        system = initializeStars(system);//Remove any previous data
        system = generateSystem(system, ID);//Create new data

        //How to display the newly created system
        switch(choice)
        {
            case 1:
                print_DB_file(system);
                break;
            case 2:
                print_CSV_file(system);
                break;
            case 3:
                displaySystem(system);
                getch();//Pause for the user to preview the output
                break;
            default:
                printf("Whoops, I need to fix that!\n");
        }

        //Display the currently finished ID of the
        printf("ID = %d\r",ID);
    }

    //Close all open files
    Close_Files();

    //Sign off for now
    printf("\n\n\n\nThanks for using the GURPS Solar System Builder\n\n\n");

    //Bye for now
	return 0;
}

void displaySystem(struct solarSystem system)
{
    int     testLoop,
            star,
            planet,
            moon,
            moonlet;
    char    stopTest = ' ';


    //The rest of the following prints to the terminal window for inspection
    printf("Star\tMass\tRadius\tTemperature\tLuminosity\tSpectral Type\n");
    printf("----\t----\t------\t-----------\t----------\t-------------\n");

    for(star = 0; star < system.numberOfStars; ++star)
    {
        printf("%d(%c)\t%0.2f\t%0.4f\t%0.1f\t\t", star + 1, toupper(system.stars[star].sequence), system.stars[star].mass, system.stars[star].radius, system.stars[star].temperature);
        if(system.stars[star].luminosity >= 1.0)
            printf("%0.2f\t\t", system.stars[star].luminosity);
        else
            printf("%0.4f\t\t", system.stars[star].luminosity);
        //If its a white dwarf, display White Dwarf as its spectral type, otherwise display normally
        if((system.stars[star].spectralType[0] == 'W') && (system.stars[star].spectralType[1] == ' '))
            printf("W. Dwarf");
        else
            printf("%c%c", system.stars[star].spectralType[0], system.stars[star].spectralType[1]);

        //If its the primary star, say so
        if(system.primaryStar == star + 1)
            printf(" (Primary Star)");

        putchar('\n');
    }

    printf("\n\nOrbits of the suns\n");
    printf("Star\tAvg Orbit\teccentricity\tMin Orbit\tMax Orbit\n");
    printf("----\t---------\t------------\t---------\t---------\n");

    for(star = 0; star < system.numberOfStars; ++star)
        if(system.primaryStar == star +1)
            printf("%d\t-\t\t-\t\t-\t\t-\n", star + 1);
        else
            printf("%d\t%0.2f\t\t%0.2f\t\t%0.2f\t\t%0.2f\n", star + 1, system.stars[star].averageOrbit, system.stars[star].eccentricity, system.stars[star].minOrbit, system.stars[star].maxOrbit);

    //Planetary Formation Limits
    printf("\n\nLimits of the solar system\n");
    printf("Star\tIn lmt\tOut Lmt\tSnow Line\tIn Frb Zn\tOut Frb Zn\n");
    printf("----\t------\t-------\t---------\t---------\t----------\n");
    for(star = 0; star < system.numberOfStars; ++star)
    {
        printf("%d\t%0.2f\t%0.2f\t%0.2f\t\t", star + 1, system.stars[star].innerLimitRadius, system.stars[star].outerLimitRadius, system.stars[star].snowLine);
        if(system.primaryStar == (star + 1))
            printf("-\t\t-\n");
        else
            printf("%0.4f\t\t%0.2f\n", system.stars[star].innerForbiddenZone, system.stars[star].outerForbiddenZone);
    }

    //Planetary Orbits
    for(star = 0; star < system.numberOfStars; ++star)
    {
        printf("\n\nPlanetary Orbits of star %d\n", star + 1);
        printf("Orbit\tRadius\tType\tSize\tBlckBdy\tIn Mnlt\tOut Mnlt\tRings\n");
        printf("-----\t------\t----\t----\t-------\t-------\t--------\t-----\n");

        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            printf("%d\t%0.2f\t%c\t%c\t%0.1f\t", planet, system.stars[star].planets[planet].orbit, system.stars[star].planets[planet].type, system.stars[star].planets[planet].size, system.stars[star].planets[planet].blackbodyTemperature);

            //Moonlets
            if(system.stars[star].planets[planet].innerMoonlets == 0)
                printf("-\t");
            else
                printf("%d\t", system.stars[star].planets[planet].innerMoonlets);

            if(system.stars[star].planets[planet].outerMoonlets == 0)
                printf("-\t\t");
            else
                printf("%d\t\t", system.stars[star].planets[planet].outerMoonlets);

            if(system.stars[star].planets[planet].type == 'G')
                switch(system.stars[star].planets[planet].rings)
                {
                    case 'N':
                        printf("-\n");
                        break;
                    case 'F':
                        printf("Faint\n");
                        break;
                    case 'S':
                        printf("Spectacular\n");
                        break;
                    case ' ':
                        printf("\nInitializtion failure on line %d\n", __LINE__);
                    default:
                        printf("\nFailure on line %d\n", __LINE__);
                        break;
                }
            else
                printf("-\n");
        }
    }

    printf("\n\nPlanets & Moons\n");
    for(star = 0; star < system.numberOfStars; ++star)
    {
        printf("Sun %d\n", star + 1);
        printf("------\n");
        printf("Body\tAtmo Mass\n");
        printf("----\t---------\n");
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            //Size and type of planet
            printf("%c%c\t", system.stars[star].planets[planet].size, system.stars[star].planets[planet].type);

            //Atmospheric Mass
            printf("%0.2f\t", system.stars[star].planets[planet].atmosphere.mass);

            //Atmospheric Properties
            displayAtmosphere(system, star, planet, 0);

            //Majour Moons
            if(system.stars[star].planets[planet].majourMoons > 0)
            {
                for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
                {
                    //Size and type of moon
                    printf(" %c%c\t", system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type);

                    //Atmospheric Mass
                    printf("%0.2f\t", system.stars[star].planets[planet].moons[moon].atmosphere.mass);

                    //Atmospheric Properties
                    displayAtmosphere(system, star, planet, moon);
                }
            }
            putchar('\n');
        }
        putchar('\n');
    }

    printf("\n\nPlanets & Moons Composition\n");
    for(star = 0; star < system.numberOfStars; ++star)
    {
        printf("Sun %d\n", star + 1);
        printf("------\n");
        printf("Body\tNtrgen\tAmmonia\tMethane\tCO2\tO2\tWtr Vpr\tHelium\tHydrgn\tNbl Gas\n");
        printf("----\t------\t-------\t-------\t---\t--\t-------\t------\t------\t-------\n");
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            printf("%c%c\t", system.stars[star].planets[planet].size, system.stars[star].planets[planet].type);

            if(system.stars[star].planets[planet].atmosphere.nitrogen == 0)
                printf("-\t");
            else
                printf("%d\t", system.stars[star].planets[planet].atmosphere.nitrogen);

            if(system.stars[star].planets[planet].atmosphere.ammonia == 0)
                printf("-\t");
            else
                printf("%d\t", system.stars[star].planets[planet].atmosphere.ammonia);

            if(system.stars[star].planets[planet].atmosphere.methane == 0)
                printf("-\t");
            else
                printf("%d\t", system.stars[star].planets[planet].atmosphere.methane);

            if(system.stars[star].planets[planet].atmosphere.carbonDioxide == 0)
                printf("-\t");
            else
                printf("%d\t", system.stars[star].planets[planet].atmosphere.carbonDioxide);

            if(system.stars[star].planets[planet].atmosphere.oxygen == 0)
                printf("-\t");
            else
                printf("%d\t", system.stars[star].planets[planet].atmosphere.oxygen);

            if(system.stars[star].planets[planet].atmosphere.waterVapour == 0)
                printf("-\t");
            else
                printf("%d\t", system.stars[star].planets[planet].atmosphere.waterVapour);

            if(system.stars[star].planets[planet].atmosphere.helium == 0)
                printf("-\t");
            else
                printf("%d\t", system.stars[star].planets[planet].atmosphere.helium);

            if(system.stars[star].planets[planet].atmosphere.hydrogen == 0)
                printf("-\t");
            else
                printf("%d\t", system.stars[star].planets[planet].atmosphere.hydrogen);

            if(system.stars[star].planets[planet].atmosphere.nobleGases == 0)
                printf("-\t");
            else
                printf("%d\n", system.stars[star].planets[planet].atmosphere.nobleGases);

            //Majour Moons
            if(system.stars[star].planets[planet].majourMoons > 0)
            {
                for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
                {
                    printf(" %c%c\t", system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type);

                    if(system.stars[star].planets[planet].moons[moon].atmosphere.nitrogen == 0)
                        printf("-\t");
                    else
                        printf("%d\t", system.stars[star].planets[planet].moons[moon].atmosphere.nitrogen);

                    if(system.stars[star].planets[planet].moons[moon].atmosphere.ammonia == 0)
                        printf("-\t");
                    else
                        printf("%d\t", system.stars[star].planets[planet].moons[moon].atmosphere.ammonia);

                    if(system.stars[star].planets[planet].moons[moon].atmosphere.methane == 0)
                        printf("-\t");
                    else
                        printf("%d\t", system.stars[star].planets[planet].moons[moon].atmosphere.methane);

                    if(system.stars[star].planets[planet].moons[moon].atmosphere.carbonDioxide == 0)
                        printf("-\t");
                    else
                        printf("%d\t", system.stars[star].planets[planet].moons[moon].atmosphere.carbonDioxide);

                    if(system.stars[star].planets[planet].moons[moon].atmosphere.oxygen == 0)
                        printf("-\t");
                    else
                        printf("%d\t", system.stars[star].planets[planet].moons[moon].atmosphere.oxygen);

                    if(system.stars[star].planets[planet].moons[moon].atmosphere.waterVapour == 0)
                        printf("-\t");
                    else
                        printf("%d\t", system.stars[star].planets[planet].moons[moon].atmosphere.waterVapour);

                    if(system.stars[star].planets[planet].moons[moon].atmosphere.helium == 0)
                        printf("-\t");
                    else
                        printf("%d\t", system.stars[star].planets[planet].moons[moon].atmosphere.helium);

                    if(system.stars[star].planets[planet].moons[moon].atmosphere.hydrogen == 0)
                        printf("-\t");
                    else
                        printf("%d\t", system.stars[star].planets[planet].moons[moon].atmosphere.hydrogen);

                    if(system.stars[star].planets[planet].moons[moon].atmosphere.nobleGases == 0)
                        printf("-\t");
                    else
                        printf("%d\n", system.stars[star].planets[planet].moons[moon].atmosphere.nobleGases);

                }
            }
        }
        putchar('\n');
    }

    //Local Conditions
    printf("Local Condiditons");
    for(star = 0; star < system.numberOfStars; ++star)
    {
        printf("\nSun %d\n", star + 1);
        printf("------\n");
        printf("Body\tHydro %%\tSurf Temp\tClimate\n");
        printf("----\t-------\t---------\t-------\n");
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            //Size and type of planet
            printf("%c%c\t", system.stars[star].planets[planet].size, system.stars[star].planets[planet].type);

            //Hydrographic Coverage
            printf("%d\t", system.stars[star].planets[planet].hydrographicCoverage);

            //Average Surface Temperature
            printf("%9d\t", system.stars[star].planets[planet].temperature);

            //Climate
            switch(system.stars[star].planets[planet].atmosphere.climate)
            {
                case 'F'://Frozen
                    printf("Frozen\t");
                    break;
                case 'v'://Very Cold
                    printf("Very Cold\t");
                    break;
                case 'c'://Cold
                    printf("Cold\t");
                    break;
                case 'y'://Chilly
                    printf("Chilly\t");
                    break;
                case 'C'://Cool
                    printf("Cool\t");
                    break;
                case 'N'://Normal
                    printf("Normal\t");
                    break;
                case 'W'://Warm
                    printf("Warm\t");
                    break;
                case 'T'://Tropical
                    printf("Tropical\t");
                    break;
                case 'H'://Hot
                    printf("Hot\t");
                    break;
                case 'V'://Very Hot
                    printf("Very Hot\t");
                    break;
                case 'I'://Infernal
                    printf("Infernal\t");
                    break;
                default:
                    if(system.stars[star].planets[planet].size != 'E');
                        printf("\nFailure on line %d (system.stars[%d].planets[%d].atmosphere.climate = %c)\n", __LINE__, star, planet, system.stars[star].planets[planet].atmosphere.climate);
                    break;
            }

            putchar('\n');
            //Majour Moons
            if(system.stars[star].planets[planet].majourMoons > 0)
            {
                for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
                {
                    //Size and type of moon
                    printf(" %c%c\t", system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type);

                    //Hydrographic Coverage
                    printf("%d\t", system.stars[star].planets[planet].moons[moon].hydrographicCoverage);

                    //Average Surface Temperature
                    printf("%9d\t", system.stars[star].planets[planet].moons[moon].temperature);

                    //Climate
                    switch(system.stars[star].planets[planet].moons[moon].atmosphere.climate)
                    {
                        case 'F'://Frozen
                            printf("Frozen\t");
                            break;
                        case 'v'://Very Cold
                            printf("Very Cold\t");
                            break;
                        case 'c'://Cold
                            printf("Cold\t");
                            break;
                        case 'y'://Chilly
                            printf("Chilly\t");
                            break;
                        case 'C'://Cool
                            printf("Cool\t");
                            break;
                        case 'N'://Normal
                            printf("Normal\t");
                            break;
                        case 'W'://Warm
                            printf("Warm\t");
                            break;
                        case 'T'://Tropical
                            printf("Tropical\t");
                            break;
                        case 'H'://Hot
                            printf("Hot\t");
                            break;
                        case 'V'://Very Hot
                            printf("Very Hot\t");
                            break;
                        case 'I'://Infernal
                            printf("Infernal\t");
                            break;
                        default:
                            printf("\nFailure on line %d\n", __LINE__);
                            break;
                    }

                    putchar('\n');
                }
            }
        }
    }

    printf("Planetary Stats");
    for(star = 0; star < system.numberOfStars; ++star)
    {
        printf("\nSun %d\n", star + 1);
        printf("------\n");
        printf("Body\tDensity\tMass\tDiamter\tGravity\tMMWR\tAtmospheric Pressure\n");
        printf("----\t-------\t----\t-------\t-------\t----\t--------------------\n");

        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            //Size and type of planet
            printf("%c%c\t", system.stars[star].planets[planet].size, system.stars[star].planets[planet].type);

            if((system.stars[star].planets[planet].type == 'A') || (system.stars[star].planets[planet].type == 'E'))
                printf("-\t-\t-\t-\t-\t-\t");
            else
            {
                //density
                printf("%0.2f\t", system.stars[star].planets[planet].density);

                //mass
                printf("%0.2f\t", system.stars[star].planets[planet].mass);

                //diameter
                printf("%0.2f\t", system.stars[star].planets[planet].diameter);

                //gravity
                printf("%0.2f\t", system.stars[star].planets[planet].gravity);

                //MMWR
                printf("%0.2f\t", system.stars[star].planets[planet].MMWR);

                //atmospheric Pressure
                printf("%0.2f\t", system.stars[star].planets[planet].atmosphere.pressure);
            }

            //Newline
            putchar('\n');

            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
            {
                //Size and type of moon
                printf(" %c%c\t", system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type);

                if((system.stars[star].planets[planet].type == 'A') || (system.stars[star].planets[planet].type == 'E'))
                    printf("-\t-\t-\t-\t-\t-\t");
                else
                {
                    //density
                    printf("%0.2f\t", system.stars[star].planets[planet].moons[moon].density);

                    //mass
                    printf("%0.2f\t", system.stars[star].planets[planet].moons[moon].mass);

                    //diameter
                    printf("%0.2f\t", system.stars[star].planets[planet].moons[moon].diameter);

                    //gravity
                    printf("%0.2f\t", system.stars[star].planets[planet].moons[moon].gravity);

                    //MMWR
                    printf("%0.2f\t", system.stars[star].planets[planet].moons[moon].MMWR);

                    //atmospheric Pressure
                    printf("%0.2f\t", system.stars[star].planets[planet].moons[moon].atmosphere.pressure);
                }

                //Newline
                putchar('\n');
            }
        }
    }

    printf("\nMoon(let) Parameters\n");
    for(star = 0; star < system.numberOfStars; ++star)
    {
        printf("Sun %d (%0.1f days)\n", star + 1, system.stars[star].orbitalPeriod);
        printf("------\n");
        printf("Body\tType\tm.Orbit\tM.Orbit\tPeriod\tTide\n");
        printf("----\t----\t-------\t-------\t------\t----\n");

        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            //Size and type of planet
            printf("%d-%c%c\tPlanet\t", planet, system.stars[star].planets[planet].size, system.stars[star].planets[planet].type);

            //Min + Max orbit
            printf("%0.2f\t", system.stars[star].planets[planet].minOrbit);
            printf("%0.2f\t", system.stars[star].planets[planet].maxOrbit);

            //Orbital period in days
            if(system.stars[star].planets[planet].orbitalPeriod > 1000.0)
                printf("%6.0f\t", system.stars[star].planets[planet].orbitalPeriod);
            else if(system.stars[star].planets[planet].orbitalPeriod > 100.0)
                printf("%6.1f\t", system.stars[star].planets[planet].orbitalPeriod);
            else
                printf("%6.2f\t", system.stars[star].planets[planet].orbitalPeriod);

            //total tide
            if((system.stars[star].planets[planet].type == 'A') || (system.stars[star].planets[planet].type == 'E'))
                printf("-\t\t");
            else if(system.stars[star].planets[planet].totalTide > 50.0)
                printf("Tide Locked\t");
            else if(system.stars[star].planets[planet].totalTide > 0.05)
                printf("%0.2f\t\t", system.stars[star].planets[planet].totalTide);
            else if(system.stars[star].planets[planet].totalTide > 0.005)
                printf("%0.3f\t\t", system.stars[star].planets[planet].totalTide);
            else
                printf("%0.4f\t\t", system.stars[star].planets[planet].totalTide);

            //New line
            putchar('\n');

            //Moonlets
            for(moonlet = 0; moonlet < (system.stars[star].planets[planet].innerMoonlets + system.stars[star].planets[planet].outerMoonlets); ++moonlet)
            {
                printf(" mnlt\t");

                //Type
                if(system.stars[star].planets[planet].moonlets[moonlet].type == 'I')
                    printf("Inner\t");
                else if(system.stars[star].planets[planet].moonlets[moonlet].type == 'O')
                    printf("Outer\t");
                else
                    printf("\nFailure on line %d (%c)\n", __LINE__, system.stars[star].planets[planet].moonlets[moonlet].type);

                //Average Orbit
                printf("%0.2f\t\t", system.stars[star].planets[planet].moonlets[moonlet].orbit);

                //Orbital period
                printf("%6.2f\t", system.stars[star].planets[planet].moonlets[moonlet].period);

                putchar('\n');
            }

            //Majour Moons
            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
            {
                //Size and type of moon
                printf(" %c%c\tM. Moon\t", system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type);

                //Average Orbit
                printf("%0.2f\t\t", system.stars[star].planets[planet].moons[moon].orbit);

                //Orbital period in days
                printf("%6.1f\t", system.stars[star].planets[planet].moons[moon].orbitalPeriod);

                //Total Tide
                if(system.stars[star].planets[planet].moons[moon].totalTide > 50.0)
                    printf("Tide Locked\t");
                else if(system.stars[star].planets[planet].moons[moon].totalTide > 0.05)
                    printf("%0.2f\t", system.stars[star].planets[planet].moons[moon].totalTide);
                else if(system.stars[star].planets[planet].moons[moon].totalTide > 0.005)
                    printf("%0.3f\t", system.stars[star].planets[planet].moons[moon].totalTide);
                else if(system.stars[star].planets[planet].moons[moon].totalTide > 0.0005)
                    printf("%0.4f\t", system.stars[star].planets[planet].moons[moon].totalTide);
                else
                    printf("%f\t", system.stars[star].planets[planet].moons[moon].totalTide);

                //New Line
                putchar('\n');
            }
        }
    }


    printf("\nPlanetary Properties\n");
    for(star = 0; star < system.numberOfStars; ++star)
    {
        printf("Sun %d\n", star + 1);
        printf("------\n");
        printf("Body\tPeriod\tday\tL.Period\tAxial Tilt\n");
        printf("----\t------\t---\t--------\t----------\n");

        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            //Size and type of planet
            printf("%c%c\t", system.stars[star].planets[planet].size, system.stars[star].planets[planet].type);

            //Rotational Period
            if((system.stars[star].planets[planet].type == 'A') || (system.stars[star].planets[planet].type == 'E'))
                printf("-\t");
            else
                if((system.stars[star].planets[planet].rotationalPeriod > 10000.0) || (system.stars[star].planets[planet].rotationalPeriod < -1000.0))
                    printf("%0.1f\t", system.stars[star].planets[planet].rotationalPeriod);
                else
                    printf("%0.2f\t", system.stars[star].planets[planet].rotationalPeriod);

            //Length of day
            if((system.stars[star].planets[planet].type == 'A') || (system.stars[star].planets[planet].type == 'E'))
                printf("-\t");
            else
                if(system.stars[star].planets[planet].dayLength > 10000)
                    if(system.stars[star].planets[planet].dayLength > 100000)
                        printf("%0.0f\t", system.stars[star].planets[planet].dayLength);
                    else
                        printf("%0.1f\t", system.stars[star].planets[planet].dayLength);
                else
                    printf("%0.2f\t", system.stars[star].planets[planet].dayLength);

            //Lunar Cycle
            printf("-\t\t");

            //Axial Tilt
            printf("%d\t", system.stars[star].planets[planet].axialTilt);

            //New Line
            putchar('\n');

            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
            {
                //Size and type of moon
                printf(" %c%c\t", system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type);

                //Rotational Period
                if((system.stars[star].planets[planet].moons[moon].type == 'A') || (system.stars[star].planets[planet].moons[moon].type == 'E'))
                    printf("-\t");
                else
                    printf("%0.2f\t", system.stars[star].planets[planet].moons[moon].rotationalPeriod);

                //Length of a day on the moon
                printf("%0.2f\t", system.stars[star].planets[planet].moons[moon].dayLength);

                //Lunar Period
                if(system.stars[star].planets[planet].moons[moon].lunarCycle > 340282346)
                    printf("Infinite\t");
                else
                    printf("%0.2f\t", system.stars[star].planets[planet].moons[moon].lunarCycle);

                //New Line
                putchar('\n');
            }
        }
    }

    printf("\nGeological Activity\n");
    for(star = 0; star < system.numberOfStars; ++star)
    {
      printf("Sun %d\n", star + 1);
      printf("------\n");
      printf("Body\tVolcanism\tTectonics\tRVM\t\tAffinity\n");
      printf("----\t---------\t---------\t---\t\t--------\n");

      for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
      {
        //Size and type of planet
        printf("%c%c\t", system.stars[star].planets[planet].size, system.stars[star].planets[planet].type);

        if(system.stars[star].planets[planet].type == 'E')//Empty orbits
          printf("-\t\t-\t\t-\t\t-");
        else
        {
          //Volcanic Activity
          switch(system.stars[star].planets[planet].volcanicActivity)
          {
            case 'N':
              printf("None\t\t");
              break;
            case 'L':
              printf("Light\t\t");
              break;
            case 'M':
              printf("Moderate\t");
              break;
            case 'H':
              printf("Heavy\t\t");
              break;
            case 'E':
              printf("Extreme\t\t");
              break;
            default:
              if(system.stars[star].planets[planet].size != 'E')
                printf("\nFailure on line %d(system.stars[%d].planets[%d].volcanicActivity = %c)\n", __LINE__, star, planet, system.stars[star].planets[planet].volcanicActivity);
              break;
          }

          //Tectonics
          switch(system.stars[star].planets[planet].tectonicActivity)
          {
            case 'N':
              printf("None\t\t");
              break;
            case 'L':
              printf("Light\t\t");
              break;
            case 'M':
              printf("Moderate\t");
              break;
            case 'H':
              printf("Heavy\t\t");
              break;
            case 'E':
              printf("Extreme\t\t");
              break;
            default:
              printf("\nFailure on line %d(%c)\n", __LINE__, system.stars[star].planets[planet].tectonicActivity);
              break;
          }

          //RVM
          switch(system.stars[star].planets[planet].RVM)
          {
            case -5:
              printf("Worthless\t");
              break;
            case -4:
              printf("Very Scant\t");
              break;
            case -3:
              printf("Scant\t\t");
              break;
            case -2:
              printf("Very Poor\t");
              break;
            case -1:
              printf("Poor\t\t");
              break;
            case 0:
              printf("Average\t\t");
              break;
            case 1:
              printf("Abundant\t");
              break;
            case 2:
              printf("Very Abundant\t");
              break;
            case 3:
              printf("Rich\t\t");
              break;
            case 4:
              printf("Very Rich\t");
              break;
            case 5:
              printf("Motherlode\t");
              break;
            default:
              printf("\nFailure on line %d\n", __LINE__);
              break;
          }

        //Affinity
        printf("%d\t", system.stars[star].planets[planet].affinity);

        }

        //New Line
        putchar('\n');

        for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
        {
          //Size and type of moon
          printf(" %c%c\t", system.stars[star].planets[planet].moons[moon].size, system.stars[star].planets[planet].moons[moon].type);

          //Volcanic Activity
          switch(system.stars[star].planets[planet].moons[moon].volcanicActivity)
          {
            case 'N':
              printf("None\t\t");
              break;
            case 'L':
              printf("Light\t\t");
              break;
            case 'M':
              printf("Moderate\t");
              break;
            case 'H':
              printf("Heavy\t\t");
              break;
            case 'E':
              printf("Extreme\t\t");
              break;
            default:
              printf("\nFailure on line %d(%c)\n", __LINE__, system.stars[star].planets[planet].moons[moon].volcanicActivity);
              break;
          }

          //Tectonics
          switch(system.stars[star].planets[planet].moons[moon].tectonicActivity)
          {
            case 'N':
              printf("None\t\t");
              break;
            case 'L':
              printf("Light\t\t");
              break;
            case 'M':
              printf("Moderate\t");
              break;
            case 'H':
              printf("Heavy\t\t");
              break;
            case 'E':
              printf("Extreme\t\t");
              break;
            default:
              printf("\nFailure on line %d(%c)\n", __LINE__, system.stars[star].planets[planet].moons[moon].volcanicActivity);
              break;
          }

          //RVM
          switch(system.stars[star].planets[planet].moons[moon].RVM)
          {
            case -3:
            printf("Scant\t\t");
            break;
          case -2:
            printf("Very Poor\t");
            break;
          case -1:
            printf("Poor\t\t");
            break;
          case 0:
            printf("Average\t\t");
            break;
          case 1:
            printf("Abundant\t");
            break;
          case 2:
            printf("Very Abundant\t");
            break;
          case 3:
            printf("Rich\t\t");
            break;
            default:
              printf("\nFailure on line %d(%d)\n", __LINE__, system.stars[star].planets[planet].moons[moon].RVM);
              break;
          }

          //Affinity
          printf("%d\t", system.stars[star].planets[planet].moons[moon].affinity);

          //New Line
          putchar('\n');
        }
      }
    }

    printf("\nUnique ID is %d\n", system.uniqueID);
    printf("The solar system is %0.1f billion years old\n", system.stellarAge);

    return;

}
