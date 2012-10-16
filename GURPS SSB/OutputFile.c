#include <stdio.h>
#include <stdlib.h>
#include "GURPS.h"
#include "GenericLibrary.h"

FILE    *systemFile,
        *starFile,
        *planetFile,
        *moonFile,
        *moonletFile,
        *fp;//pointer to file

//Different functions for different logical outputs
void print_CSV_file(struct solarSystem system);//Prints system to a CSV file to be opened with Excel
void print_DB_file(struct solarSystem system);//Prints system to a file series of text files to be used with Access

//Functions to allow generic printing of files
void print_system(struct solarSystem system, FILE *file);   //Only prints system info
void print_star(struct solarSystem system, FILE *file);     //Only prints star info
void print_planet(struct solarSystem system, FILE *file);   //Only prints planet info
void print_moon(struct solarSystem system, FILE *file);     //Only prints moon info
void print_moonlet(struct solarSystem system, FILE *file);  //Only prints moonlet info
void Open_Files(unsigned int choice);//Opens all files
void Close_Files();//Closes all open database files

void print_system(struct solarSystem system, FILE *file)
{
    //System ID
    fprintf(file, "%d,", system.uniqueID);

    //Number of Stars
    fprintf(file, "%d,", system.numberOfStars);

    //Stellar Age
    fprintf(file, "%0.2f,", system.stellarAge);

    //New record
    fprintf(file, "\n");

    return;
}

void print_star(struct solarSystem system, FILE *file)
{
    int star;

    //Loop over stars
    for(star = 0; star < system.numberOfStars; ++star)
    {
        //System ID
        fprintf(file, "%d,", system.uniqueID);

        //Star
        fprintf(file, "%d,", star + 1);

        //Primary Star
        if(star + 1 == system.primaryStar)
            fprintf(file,"Yes,");
        else
            fprintf(file,"No,");

        //Sequence
        switch(system.stars[star].sequence)
        {
            case 'm'://Main
                fprintf(file,"Main,");
                break;
            case 's'://Subgiant
                fprintf(file,"Subgiant,");
                break;
            case 'g'://Giant
                fprintf(file,"Giant,");
                break;
            case 'w'://White Dwarf
                fprintf(file,"White Dwarf,");
                break;
            default:
                break;
        }

        //Mass
        fprintf(file,"%0.2f,", system.stars[star].mass);

        //Radius
        fprintf(file,"%0.4f,", system.stars[star].radius);

        //Temperature
        fprintf(file,"%0.2f,", system.stars[star].temperature);

        //Luminosity
        fprintf(file,"%0.2f,", system.stars[star].luminosity);

        //Spectral Type
        fprintf(file,"%c%c,", system.stars[star].spectralType[0], system.stars[star].spectralType[1]);

        //Average Orbit
        if(testFloatEquality(system.stars[star].averageOrbit, 0.0, 0.1))
            fprintf(file,"N/A,");
        else
            fprintf(file,"%0.2f,", system.stars[star].averageOrbit);

        //Eccentricity
        if(testFloatEquality(system.stars[star].eccentricity, 0.0, 0.1))
            fprintf(file,"N/A,");
        else
            fprintf(file,"%0.2f,", system.stars[star].eccentricity);

        //Minimum Orbit
        if(testFloatEquality(system.stars[star].minOrbit, 0.0, 0.1))
            fprintf(file,"N/A,");
        else
            fprintf(file,"%0.2f,", system.stars[star].minOrbit);

        //Maximum Orbit
        if(testFloatEquality(system.stars[star].maxOrbit, 0.0, 0.1))
            fprintf(file,"N/A,");
        else
            fprintf(file,"%0.2f,", system.stars[star].maxOrbit);

        //Orbital Period
        if(testFloatEquality(system.stars[star].orbitalPeriod, 0.0, 0.1))
            fprintf(file,"N/A,");
        else
            fprintf(file,"%0.2f,", system.stars[star].orbitalPeriod);

        //Ungenerated Companion Star
        if(system.stars[star].companionFlag)
            fprintf(file,"Yes");
        else
            fprintf(file,"No");

        //New record
        fprintf(file, "\n");
    }
    return;
}

void print_planet(struct solarSystem system, FILE *file)
{
    int planet,
        star,
        loop;

    //Loop over stars
    for(star = 0; star < system.numberOfStars; ++star)
    {
        //Loop over Planet
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            //System ID
            fprintf(file, "%d,", system.uniqueID);

            //Star
            fprintf(file, "%d,", star + 1);

            //Planet
            fprintf(file, "%d,", planet);

            //Empty Orbits, Yay
            if(system.stars[star].planets[planet].type == 'E')//Empty Orbit
            {
                //Size
                fprintf(file,"N/A,");

                //Type
                fprintf(file,"Empty Orbit,");

                //Rings
                fprintf(file,"N/A,");

                //Orbit
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].orbit);

                //The rest
                for(loop = 0; loop < 36; ++loop)
                    fprintf(file,"N/A,");

                //Setup for next entry
                fprintf(file,"\n");

            }
            else if(system.stars[star].planets[planet].type == 'A')//Display differently for Asteroid Belts
            {
                //Size
                fprintf(file,"N/A,");

                //Type
                fprintf(file,"Asteroid Belt,");

                //Rings
                fprintf(file,"N/A,");

                //Orbit
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].orbit);

                //Minimum Orbit
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].minOrbit);

                //Maximum Orbit
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].maxOrbit);

                //Eccentricity
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].eccentricity);

                //Axial Tilt
                fprintf(file,"%d,", system.stars[star].planets[planet].axialTilt);

                //Orbital Period
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].orbitalPeriod);

                //Total Tide
                fprintf(file,"N/A,");

                //Rotational Period
                fprintf(file,"N/A,");

                //Temperature
                fprintf(file,"%d,", system.stars[star].planets[planet].temperature);

                //Blackbody Temperature
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].blackbodyTemperature);

                //Gravity
                fprintf(file,"N/A,");

                //Diameter
                fprintf(file,"N/A,");

                //Density
                fprintf(file,"N/A,");

                //Mass
                fprintf(file,"N/A,");

                //Day Length
                fprintf(file,"N/A,");

                //Hydrographic Coverage
                fprintf(file,"N/A,");

                //MMWR
                fprintf(file,"N/A,");

                //RVM
                fprintf(file,"%d,", system.stars[star].planets[planet].RVM);

                //Habitability
                fprintf(file,"%d,", system.stars[star].planets[planet].habitability);

                //Affinity
                fprintf(file,"%d,", system.stars[star].planets[planet].affinity);

                //Volcanic Activity
                fprintf(file,"N/A,");

                //Tectonic Activity
                fprintf(file,"N/A,");

                //Marginality
                fprintf(file,"N/A,");

                //Suffocating
                fprintf(file,"N/A,");

                //Toxicity
                fprintf(file,"N/A,");

                //Corrosivity
                fprintf(file,"N/A,");

                //Climate
                fprintf(file,"N/A,");

                //Atmospheric Pressure
                fprintf(file,"N/A,");

                //Atmospheric Composition
                //Nitrogen
                if(system.stars[star].planets[planet].atmosphere.nitrogen)
                    fprintf(file, "Nitrogen,");
                else
                    fprintf(file, "N/A,");

                //Ammonia
                if(system.stars[star].planets[planet].atmosphere.ammonia)
                    fprintf(file, "Ammonia,");
                else
                    fprintf(file, "N/A,");

                //Methane
                if(system.stars[star].planets[planet].atmosphere.methane)
                    fprintf(file, "Methane,");
                else
                    fprintf(file, "N/A,");

                //CO2
                if(system.stars[star].planets[planet].atmosphere.carbonDioxide)
                    fprintf(file, "CO2,");
                else
                    fprintf(file, "N/A,");

                //O2
                if(system.stars[star].planets[planet].atmosphere.oxygen)
                    fprintf(file, "O2,");
                else
                    fprintf(file, "N/A,");

                //Water Vapour
                if(system.stars[star].planets[planet].atmosphere.waterVapour)
                    fprintf(file, "Water Vapour,");
                else
                    fprintf(file, "N/A,");

                //Helium
                if(system.stars[star].planets[planet].atmosphere.helium)
                    fprintf(file, "Helium,");
                else
                    fprintf(file, "N/A,");

                //Hydrogen
                if(system.stars[star].planets[planet].atmosphere.hydrogen)
                    fprintf(file, "Hydrogen,");
                else
                    fprintf(file, "N/A,");

                //Noble Gases
                if(system.stars[star].planets[planet].atmosphere.nobleGases)
                    fprintf(file, "Noble Gases,");
                else
                    fprintf(file, "N/A,");

                //Formating for new lines
                fprintf(file, "\n");
            }
            else//Planets
            {
                //Size
                switch(system.stars[star].planets[planet].size)
                {
                    case 'T':
                        fprintf(file,"Tiny,");
                        break;
                    case 'S':
                        fprintf(file,"Small,");
                        break;
                    case 'M':
                        if(system.stars[star].planets[planet].type == 'G')
                            fprintf(file,"Medium,");//Gas Giant
                        else
                            fprintf(file,"Standard,");//Terrestrial
                        break;
                    case 'L':
                        fprintf(file,"Large,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in terminal window, not output file!
                        break;
                }

                //Type
                switch(system.stars[star].planets[planet].type)
                {
                    case 'I':
                        fprintf(file,"Ice,");
                        break;
                    case 'H':
                        fprintf(file,"Hadean,");
                        break;
                    case 'R':
                        fprintf(file,"Rock,");
                        break;
                    case 'S':
                        fprintf(file,"Sulfur,");
                        break;
                    case 'O':
                        fprintf(file,"Ocean,");
                        break;
                    case 'G':
                        fprintf(file,"Gas Giant,");
                        break;
                    case 'g':
                        fprintf(file,"Green House,");
                        break;
                    case 'r':
                        fprintf(file,"Garden,");
                        break;
                    case 'a':
                        fprintf(file,"Ammonia,");
                        break;
                    case 'C':
                        fprintf(file,"Cthonian,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in terminal window, not output file!
                        break;
                }

                //Rings
                switch(system.stars[star].planets[planet].rings)
                {
                    case 'F':
                        fprintf(file,"Faint,");
                        break;
                    case 'S':
                        fprintf(file,"Spectacular,");
                        break;
                    case 'N':
                        fprintf(file,"None,");
                        break;
                    default:
                        printf("\nFailure on line %d (%c), Planet = %d, star = %d\n", __LINE__, system.stars[star].planets[planet].rings, planet, star);//Displays in terminal window, not output file!
                        break;
                }

                //Orbit
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].orbit);

                //Minimum Orbit
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].minOrbit);

                //Maximum Orbit
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].maxOrbit);

                //Eccentricity
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].eccentricity);

                //Axial Tilt
                fprintf(file,"%d,", system.stars[star].planets[planet].axialTilt);

                //Orbital Period
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].orbitalPeriod);

                //Total Tide
                if(system.stars[star].planets[planet].totalTide > 50.0)
                    fprintf(file,"Tide Locked,");
                else
                    fprintf(file,"%0.2f,", system.stars[star].planets[planet].totalTide);

                //Rotational Period
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].rotationalPeriod);

                //Temperature
                fprintf(file,"%d,", system.stars[star].planets[planet].temperature);

                //Blackbody Temperature
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].blackbodyTemperature);

                //Gravity
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].gravity);

                //Diameter
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].diameter);

                //Density
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].density);

                //Mass
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].mass);

                //Day Length
                if(system.stars[star].planets[planet].dayLength > 4294967290.0)
                    fprintf(file,"Infinite,");
                else
                    fprintf(file,"%0.2f,", system.stars[star].planets[planet].dayLength);

                //Hydrographic Coverage
                fprintf(file,"%d %%, ", system.stars[star].planets[planet].hydrographicCoverage);

                //MMWR
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].MMWR);

                //RVM
                fprintf(file,"%d,", system.stars[star].planets[planet].RVM);

                //Habitability
                fprintf(file,"%d,", system.stars[star].planets[planet].habitability);

                //Affinity
                fprintf(file,"%d,", system.stars[star].planets[planet].affinity);

                //Volcanic Activity
                switch(system.stars[star].planets[planet].volcanicActivity)
                {
                    case 'N':
                        fprintf(file, "None,");
                        break;
                    case 'L':
                        fprintf(file, "Light,");
                        break;
                    case 'M':
                        fprintf(file, "Moderate,");
                        break;
                    case 'H':
                        fprintf(file, "Heavy,");
                        break;
                    case 'E':
                        fprintf(file, "Extreme,");
                        break;
                    default:
                        printf("\nFailure on line %d(%c)\n", __LINE__, system.stars[star].planets[planet].volcanicActivity);//Displays in the terminal window
                        break;
                }

                //Tectonic Activity
                switch(system.stars[star].planets[planet].tectonicActivity)
                {
                    case 'N':
                        fprintf(file, "None,");
                        break;
                    case 'L':
                        fprintf(file, "Light,");
                        break;
                    case 'M':
                        fprintf(file, "Moderate,");
                        break;
                    case 'H':
                        fprintf(file, "Heavy,");
                        break;
                    case 'E':
                        fprintf(file, "Extreme,");
                        break;
                    default:
                        printf("\nFailure on line %d(%c)\n", __LINE__, system.stars[star].planets[planet].tectonicActivity);//Displays in the terminal window
                        break;
                }

                //Marginality
                switch(system.stars[star].planets[planet].atmosphere.marginality)
                {
                    case 'P':
                        fprintf(file,"Poisonous,");
                        break;
                    case 'V':
                        fprintf(file,"Vacuum,");
                        break;
                    case 'N':
                        fprintf(file,"Not Marginal,");
                        break;
                    case 'o':
                        fprintf(file,"Low Oxygen,");
                        break;
                    case 'F':
                        fprintf(file,"Fluorine,");
                        break;
                    case 'S':
                        fprintf(file,"Sulphur Compounds,");
                        break;
                    case 'c':
                        fprintf(file,"Chlorine,");
                        break;
                    case 'T':
                        fprintf(file,"Organic Toxins,");
                        break;
                    case 'C':
                        fprintf(file,"High CO2,");
                        break;
                    case 'O':
                        fprintf(file,"High Oxygen,");
                        break;
                    case 'p':
                        fprintf(file,"Pollutants,");
                        break;
                    case 'I':
                        fprintf(file,"Inert Gases,");
                        break;
                    case 'n':
                        fprintf(file,"Nitrogen Compounds,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
                        break;
                }

                //Suffocating
                switch(system.stars[star].planets[planet].atmosphere.suffocating)
                {
                    case 'S':
                        fprintf(file,"Suffocating,");
                        break;
                    case 'N':
                        fprintf(file,"Non-Suffocating,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
                        break;
                }

                //Toxicity
                switch(system.stars[star].planets[planet].atmosphere.toxicity)
                {
                    case 'M':
                        fprintf(file,"Mild,");
                        break;
                    case 'H':
                        fprintf(file,"High,");
                        break;
                    case 'L':
                        fprintf(file,"Lethal,");
                        break;
                    case 'N':
                        fprintf(file,"Non-Toxic,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
                        break;
                }

                //Corrosivity
                switch(system.stars[star].planets[planet].atmosphere.corrosivity)
                {
                    case 'C':
                        fprintf(file,"Corrosive,");
                        break;
                    case 'N':
                        fprintf(file,"Non-Corrosive,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
                        break;
                }

                //Climate
                switch(system.stars[star].planets[planet].atmosphere.climate)
                {
                    case 'F':
                        fprintf(file,"Frozen,");
                        break;
                    case 'v':
                        fprintf(file,"Very Cold,");
                        break;
                    case 'c':
                        fprintf(file,"cold,");
                        break;
                    case 'y':
                        fprintf(file,"Chilly,");
                        break;
                    case 'C':
                        fprintf(file,"Cool,");
                        break;
                    case 'N':
                        fprintf(file,"Normal,");
                        break;
                    case 'W':
                        fprintf(file,"Warm,");
                        break;
                    case 'T':
                        fprintf(file,"Tropical,");
                        break;
                    case 'H':
                        fprintf(file,"Hot,");
                        break;
                    case 'V':
                        fprintf(file,"Very Hot,");
                        break;
                    case 'I':
                        fprintf(file,"Infernal,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
                        break;
                }

                //Atmospheric Pressure
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].atmosphere.pressure);

                //Atmospheric Composition
                //Nitrogen
                if(system.stars[star].planets[planet].atmosphere.nitrogen)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Ammonia
                if(system.stars[star].planets[planet].atmosphere.ammonia)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Methane
                if(system.stars[star].planets[planet].atmosphere.methane)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //CO2
                if(system.stars[star].planets[planet].atmosphere.carbonDioxide)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //O2
                if(system.stars[star].planets[planet].atmosphere.oxygen)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Water Vapour
                if(system.stars[star].planets[planet].atmosphere.waterVapour)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Helium
                if(system.stars[star].planets[planet].atmosphere.helium)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Hydrogen
                if(system.stars[star].planets[planet].atmosphere.hydrogen)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Noble Gases
                if(system.stars[star].planets[planet].atmosphere.nobleGases)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Formating for new lines
                fprintf(file, "\n");
            }
        }
    }

    return;
}
void print_moon(struct solarSystem system, FILE *file)
{
    int star,
        planet,
        moon;

    for(star = 0; star < system.numberOfStars; ++star)
    {
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
            {
                //System ID
                fprintf(file,"%d,", system.uniqueID);

                //Star
                fprintf(file,"%d,", star);

                //Planet
                fprintf(file,"%d,", planet);

                //Moon
                fprintf(file,"%d,", moon);

                //Size
                switch(system.stars[star].planets[planet].moons[moon].size)
                {
                    case 'T':
                        fprintf(file,"Tiny,");
                        break;
                    case 'S':
                        fprintf(file,"Small,");
                        break;
                    case 'M':
                        fprintf(file,"Standard,");
                        break;
                    case 'L':
                        fprintf(file,"Large,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in terminal window, not output file!
                        break;
                }

                //Type
                switch(system.stars[star].planets[planet].moons[moon].type)
                {
                    case 'I':
                        fprintf(file,"Ice,");
                        break;
                    case 'H':
                        fprintf(file,"Hadean,");
                        break;
                    case 'R':
                        fprintf(file,"Rock,");
                        break;
                    case 'S':
                        fprintf(file,"Sulfur,");
                        break;
                    case 'O':
                        fprintf(file,"Ocean,");
                        break;
                    case 'G':
                        fprintf(file,"Gas Giant,");
                        break;
                    case 'g':
                        fprintf(file,"Green House,");
                        break;
                    case 'r':
                        fprintf(file,"Garden,");
                        break;
                    case 'a':
                        fprintf(file,"Ammonia,");
                        break;
                    case 'C':
                        fprintf(file,"Cthonian,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in terminal window, not output file!
                        break;
                }

                //Orbit
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].moons[moon].orbit);

                //Obital Period
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].moons[moon].orbitalPeriod);

                //Total Tide
                if(system.stars[star].planets[planet].moons[moon].totalTide > 50.0)
                    fprintf(file,"Tide Locked,");
                else
                    fprintf(file,"%0.2f,", system.stars[star].planets[planet].moons[moon].totalTide);

                //Rotational Period
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].moons[moon].rotationalPeriod);

                //Temperature
                fprintf(file,"%d,", system.stars[star].planets[planet].temperature);//Same as the planets

                //Gravity
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].moons[moon].gravity);

                //Diameter
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].moons[moon].diameter);

                //Density
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].moons[moon].density);

                //Mass
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].moons[moon].mass);

                //Day Length
                if(system.stars[star].planets[planet].moons[moon].dayLength > 100000.0)
                    fprintf(file,"Infinite,");
                else
                    fprintf(file,"%0.2f,", system.stars[star].planets[planet].moons[moon].dayLength);

                //Lunar Cycle
                if(system.stars[star].planets[planet].moons[moon].lunarCycle > 100000.0)
                    fprintf(file,"Infinite,");
                else
                    fprintf(file,"%0.2f,", system.stars[star].planets[planet].moons[moon].lunarCycle);

                //Hydrographic Coverage
                fprintf(file,"%d %%,", system.stars[star].planets[planet].moons[moon].hydrographicCoverage);

                //MMWR
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].moons[moon].MMWR);

                //RVM
                fprintf(file,"%d,", system.stars[star].planets[planet].moons[moon].RVM);

                //Habitability
                fprintf(file,"%d,", system.stars[star].planets[planet].moons[moon].habitability);

                //Affinity
                fprintf(file,"%d,", system.stars[star].planets[planet].moons[moon].affinity);

                //Volcanic Activity
                switch(system.stars[star].planets[planet].moons[moon].volcanicActivity)
                {
                    case 'N':
                        fprintf(file, "None,");
                        break;
                    case 'L':
                        fprintf(file, "Light,");
                        break;
                    case 'M':
                        fprintf(file, "Moderate,");
                        break;
                    case 'H':
                        fprintf(file, "Heavy,");
                        break;
                    case 'E':
                        fprintf(file, "Extreme,");
                        break;
                    default:
                        printf("\nFailure on line %d(%c)\n", __LINE__, system.stars[star].planets[planet].moons[moon].volcanicActivity);//Displays in the terminal window
                        break;
                }

                //Tectonic Activity
                switch(system.stars[star].planets[planet].moons[moon].tectonicActivity)
                {
                    case 'N':
                        fprintf(file, "None,");
                        break;
                    case 'L':
                        fprintf(file, "Light,");
                        break;
                    case 'M':
                        fprintf(file, "Moderate,");
                        break;
                    case 'H':
                        fprintf(file, "Heavy,");
                        break;
                    case 'E':
                        fprintf(file, "Extreme,");
                        break;
                    default:
                        printf("\nFailure on line %d(%c)\n", __LINE__, system.stars[star].planets[planet].moons[moon].tectonicActivity);//Displays in the terminal window
                        break;
                }

                //Marginality
                switch(system.stars[star].planets[planet].moons[moon].atmosphere.marginality)
                {
                    case 'P':
                        fprintf(file,"Poisonous,");
                        break;
                    case 'V':
                        fprintf(file,"Vacuum,");
                        break;
                    case 'N':
                        fprintf(file,"Not Marginal,");
                        break;
                    case 'o':
                        fprintf(file,"Low Oxygen,");
                        break;
                    case 'F':
                        fprintf(file,"Fluorine,");
                        break;
                    case 'S':
                        fprintf(file,"Sulphur Compounds,");
                        break;
                    case 'c':
                        fprintf(file,"Chlorine,");
                        break;
                    case 'T':
                        fprintf(file,"Organic Toxins,");
                        break;
                    case 'C':
                        fprintf(file,"High CO2,");
                        break;
                    case 'O':
                        fprintf(file,"High Oxygen,");
                        break;
                    case 'p':
                        fprintf(file,"Pollutants,");
                        break;
                    case 'I':
                        fprintf(file,"Inert Gases,");
                        break;
                    case 'n':
                        fprintf(file,"Nitrogen Compounds,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
                        break;
                }

                //Suffocating
                switch(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating)
                {
                    case 'S':
                        fprintf(file,"Suffocating,");
                        break;
                    case 'N':
                        fprintf(file,"Non-Suffocating,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
                        break;
                }

                //Toxicity
                switch(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity)
                {
                    case 'M':
                        fprintf(file,"Mild,");
                        break;
                    case 'H':
                        fprintf(file,"High,");
                        break;
                    case 'L':
                        fprintf(file,"Lethal,");
                        break;
                    case 'N':
                        fprintf(file,"Non-Toxic,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
                        break;
                }

                //Corrosivity
                switch(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity)
                {
                    case 'C':
                        fprintf(file,"Corrosive,");
                        break;
                    case 'N':
                        fprintf(file,"Non-Corrosive,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
                        break;
                }

                //Climate
                switch(system.stars[star].planets[planet].moons[moon].atmosphere.climate)
                {
                    case 'F':
                        fprintf(file,"Frozen,");
                        break;
                    case 'v':
                        fprintf(file,"Very Cold,");
                        break;
                    case 'c':
                        fprintf(file,"cold,");
                        break;
                    case 'y':
                        fprintf(file,"Chilly,");
                        break;
                    case 'C':
                        fprintf(file,"Cool,");
                        break;
                    case 'N':
                        fprintf(file,"Normal,");
                        break;
                    case 'W':
                        fprintf(file,"Warm,");
                        break;
                    case 'T':
                        fprintf(file,"Tropical,");
                        break;
                    case 'H':
                        fprintf(file,"Hot,");
                        break;
                    case 'V':
                        fprintf(file,"Very Hot,");
                        break;
                    case 'I':
                        fprintf(file,"Infernal,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
                        break;
                }

                //Atmospheric Pressure
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].moons[moon].atmosphere.pressure);

                //Atmospheric Composition
                //Nitrogen
                if(system.stars[star].planets[planet].moons[moon].atmosphere.nitrogen)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Ammonia
                if(system.stars[star].planets[planet].moons[moon].atmosphere.ammonia)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Methane
                if(system.stars[star].planets[planet].moons[moon].atmosphere.methane)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //CO2
                if(system.stars[star].planets[planet].moons[moon].atmosphere.carbonDioxide)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //O2
                if(system.stars[star].planets[planet].moons[moon].atmosphere.oxygen)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Water Vapour
                if(system.stars[star].planets[planet].moons[moon].atmosphere.waterVapour)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Helium
                if(system.stars[star].planets[planet].moons[moon].atmosphere.helium)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Hydrogen
                if(system.stars[star].planets[planet].moons[moon].atmosphere.hydrogen)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Noble Gases
                if(system.stars[star].planets[planet].moons[moon].atmosphere.nobleGases)
                    fprintf(file, "Yes,");
                else
                    fprintf(file, "No,");

                //Next record
                fprintf(file, "\n");
            }
        }
    }

    return;
}
void print_moonlet(struct solarSystem system, FILE *file)
{
    int moonlet,
        planet,
        star;

    //Loop over stars
    for(star = 0; star < system.numberOfStars; ++star)
    {
        //Loop over Planet
        for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
        {
            //moonlet
            for(moonlet = 0; moonlet < (system.stars[star].planets[planet].innerMoonlets + system.stars[star].planets[planet].outerMoonlets); ++moonlet)
            {
                //System ID
                fprintf(file, "%d,", system.uniqueID);

                //Star
                fprintf(file, "%d,", star + 1);

                //Planet
                fprintf(file, "%d,", planet);

                //Location
                switch(system.stars[star].planets[planet].moonlets[moonlet].type)
                {
                    case 'I':
                        fprintf(file,"Inner Moonlet,");
                        break;
                    case 'O':
                        fprintf(file,"Outer Moonlet,");
                        break;
                    default:
                        printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
                        break;
                }

                //Orbit
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].moonlets[moonlet].orbit);

                //Period
                fprintf(file,"%0.2f,", system.stars[star].planets[planet].moonlets[moonlet].period);

                //Formating for new lines
                fprintf(file, "\n");
            }
        }
    }

    return;
}


//Prints to database files
void print_DB_file(struct solarSystem system)
{
    static int      born = 1;

    //Only do this on startup, these are row headers, which should appear exactly once per file!
    if(born == 1)
    {
        //Setup the headers of the various files
        fprintf(systemFile, "System ID,Number of Stars,Stellar Age\n");
        fprintf(starFile,"System ID,Star,Primary Star,Sequence,Mass,Radius,Temperature,Luminosity,Spectral Type,Average Orbit,Eccentricity,Minimum Orbit,Maximum Orbit,Orbital Period,Ungenerated Companion Star\n");
        fprintf(planetFile, "System ID,Star,Orbit,Size,Type,Rings,Orbital Distance,Minimum Orbit,Maximum Orbit,Eccentricity,Axial Tilt,Orbital Period,Total Tide,Rotational Period,Temperature,Blackbody Temperature,Gravity,Diameter,Density,Mass,Day Length,Hydrographic Coverage,MMWR,RVM,Habitability,Affinity,Volcanic Activity,Tectonic Activity,Marginality,Suffocating,Toxicity,Corrosivity,Climate,Atmospheric Pressure,Nitrogen,Ammonia,Methane,CO2,O2,Water Vapour,Helium,Hydrogen,Noble Gases\n");
        fprintf(moonFile, "System ID,Star,Planet,Moon,Size,Type,Orbit,Obital Period,Total Tide,Rotational Period,Temperature,Gravity,Diameter,Density,Mass,Day Length,Lunar Cycle,Hydrographic Coverage,MMWR,RVM,Habitability,Affinity,Volcanic Activity,Tectonic Activity,Marginality,Suffocating,Toxicity,Corrosivity,Climate,Atmospheric Pressure,Nitrogen,Ammonia,Methane,CO2,O2,Water Vapour,Helium,Hydrogen,Noble Gases\n");
        fprintf(moonletFile, "System ID,Star,Planet,Location,Orbit,Period\n");

        //Tell the world that you are no longer a baby
        born = 0;
    }

    //Save System
    print_system(system, systemFile);

    //Save Stars
    print_star(system, starFile);

    //Save Planets
    print_planet(system, planetFile);

    //Save Moons
    print_moon(system, moonFile);

    //Save Moonlets
    print_moonlet(system, moonletFile);

    return;
}

void Open_Files(unsigned int choice)
{
    switch(choice)
    {
        case 1://DB output
            systemFile = fopen("System.csv","a");   //Name of file, for append
            starFile = fopen("Star.csv","a");       //Name of file, for append
            planetFile = fopen("Planet.csv","a");   //Name of file, for append
            moonFile = fopen("Moon.csv","a");       //Name of file, for append
            moonletFile = fopen("Moonlet.csv","a"); //Name of file, for append
            break;
        case 2://Single output
            fp = fopen("Generated Solar System.csv","a");//Name of file, for append
            break;
        default://Onscreen or error
            break;
    }

    return;
}
//Close the open files
void Close_Files()
{
    //Database files
    fclose(systemFile);
    fclose(starFile);
    fclose(planetFile);
    fclose(moonFile);
    fclose(moonletFile);

    //Close single file output
    fclose(fp);
    return;
}

void print_CSV_file(struct solarSystem system)
{
	int	star,
		planet,
		moon,
		moonlet;

	//Give the reference ID
	fprintf(fp,"Unique ID (%d)\n", system.uniqueID);


	//Displays age of system
	fprintf(fp,"System Age = %0.2f billion years old\n\n", system.stellarAge);

	//Alert the user to companion stars
	if(system.stars[0].companionFlag)
		fprintf(fp,"Star 1 has an ungenerated companion star\n");
	if(system.stars[1].companionFlag)
		fprintf(fp,"Star 2 has an ungenerated companion star\n");
	if(system.stars[2].companionFlag)
		fprintf(fp,"Star 3 has an ungenerated companion star\n");

	//Header for the Stars stats
	fprintf(fp,"Star,Sequence,Mass,Radius,Temperature,Luminosity,Spectral Type,Average Orbit,Eccentricity,Minimum Orbit,Maximum Orbit,Orbital Period\n");

	//Star
	for(star = 0; star < system.numberOfStars; ++star)
	{
		//Header for the star, displays if its the Primary Star
		if(system.primaryStar == star + 1)
			fprintf(fp,"Star %d (Primary Star),", star + 1);
		else
			fprintf(fp,"Star %d,", star + 1);

		//Sequence
		switch(system.stars[star].sequence)
		{
			case 'm'://Main
				fprintf(fp,"Main,");
				break;
			case 's'://Subgiant
				fprintf(fp,"Subgiant,");
				break;
			case 'g'://Giant
				fprintf(fp,"Giant,");
				break;
			case 'w'://White Dwarf
				fprintf(fp,"White Dwarf,");
				break;
			default:
				break;
		}

		//Mass
		fprintf(fp,"%0.2f,", system.stars[star].mass);

		//Radius
		fprintf(fp,"%0.2f,", system.stars[star].radius);

		//Temperature
		fprintf(fp,"%0.2f,", system.stars[star].temperature);

		//Luminosity
		fprintf(fp,"%0.2f,", system.stars[star].luminosity);

		//Spectral Type
		fprintf(fp,"%c", system.stars[star].spectralType[0]);
		fprintf(fp,"%c,", system.stars[star].spectralType[1]);

		//Average Orbit
		fprintf(fp,"%0.2f,", system.stars[star].averageOrbit);

		//Eccentricity
		fprintf(fp,"%0.2f,", system.stars[star].eccentricity);

		//Minimum Orbit
		fprintf(fp,"%0.2f,", system.stars[star].minOrbit);

		//Maximum Orbit
		fprintf(fp,"%0.2f,", system.stars[star].maxOrbit);

		//Orbital Period\n
		fprintf(fp,"%0.2f\n", system.stars[star].orbitalPeriod);
        }

        for(star = 0; star < system.numberOfStars; ++star)
		{
		//Headers for the planets
		fprintf(fp, "\nStar %d\n", star + 1);
		fprintf(fp, "Size,Type,Rings,Orbit,Minimum Orbit,Maximum Orbit,Eccentricity,Axial Tilt,Orbital Period,Total Tide,");
		fprintf(fp, "Rotational Period,Temperature,Blackbody Temperature,Gravity,Diameter,Density,Mass,Day Length,");
		fprintf(fp, "Hydrographic Coverage,MMWR,RVM,Habitability,Affinity,Volcanic Activity,Tectonic Activity,");
		fprintf(fp, "Marginality,Suffocating,Toxicity,Corrosivity,Climate,Atmospheric Pressure,Atmospheric Composition\n");

		//Planets
		for(planet = 0; planet < system.stars[star].numberOfPlanets; ++planet)
		{
			//Empty Orbits, Yay
			if(system.stars[star].planets[planet].type == 'E')
            {
                            //Size
				fprintf(fp,"N/A,");

				//Type
				fprintf(fp,"Empty Orbit,");

				//Ring
				fprintf(fp,"N/A,");

				//Orbit
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].orbit);

				//Minimum Orbit
				fprintf(fp,"N/A,");

				//Maximum Orbit
				fprintf(fp,"N/A,");

				//Eccentricity of Orbit
				fprintf(fp,"N/A,");

				//Axial Tilt wrt orbit
				fprintf(fp,"N/A,");

				//Orbital period around its star
				fprintf(fp,"N/A,");

				//Total Tide due to all of its moons and the star
				fprintf(fp,"N/A,");

				//Rotational Period (Not the same as length of day!
				fprintf(fp,"N/A,");

				//Average Surface Temperature
				fprintf(fp,"N/A,");

				//Blackbody temperature (Maximum possible temperature)
				fprintf(fp,"N/A,");

				//Surface Gravity
				fprintf(fp,"N/A,");

				//Planet Diameter
				fprintf(fp,"N/A,");

				//Planet Density
				fprintf(fp,"N/A,");

				//Mass of planet
				fprintf(fp,"N/A,");

				//Length of the day
				fprintf(fp,"N/A,");

				//liquid coverage (not nessecarily water!)
				fprintf(fp,"N/A,");

				//Minimum Molecular Weight Retained
				fprintf(fp,"N/A,");

				//Resource Value Modifier
				fprintf(fp,"N/A,");

				//Habitability Rating
				fprintf(fp,"N/A,");

				//Total affinity (RVM + habitability)
				fprintf(fp,"N/A,");

				//Volcanic Activity
				fprintf(fp,"N/A,");

				//Tectonic Activity
				fprintf(fp,"N/A,");

				//Marginalty
				fprintf(fp,"N/A,");

				//Suffocating
				fprintf(fp,"N/A,");

				//Toxicity
				fprintf(fp,"N/A,");

				//Corrosivity
				fprintf(fp,"N/A,");

				//Climate
				fprintf(fp,"N/A,");

				//Atmospheric Pressure
				fprintf(fp,"N/A,");

				//Atmospheric Composition
				fprintf(fp,"N/A\n");
            }

			//Display differently for Asteroid Belts
            else if(system.stars[star].planets[planet].type == 'A')
			{
				//Size
				fprintf(fp,"N/A,");

				//Type
				fprintf(fp,"Asteroid Belt,");

				//Ring
				fprintf(fp,"N/A,");

				//Orbit
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].orbit);

				//Minimum Orbit
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].minOrbit);

				//Maximum Orbit
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].maxOrbit);

				//Eccentricity of Orbit
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].eccentricity);

				//Axial Tilt wrt orbit
				fprintf(fp,"%d,", system.stars[star].planets[planet].axialTilt);

				//Orbital period around its star
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].orbitalPeriod);

				//Total Tide due to all of its moons and the star
				fprintf(fp,"N/A,");

				//Rotational Period (Not the same as length of day!
				fprintf(fp,"N/A,");

				//Average Surface Temperature
				fprintf(fp,"%d,", system.stars[star].planets[planet].temperature);

				//Blackbody temperature (Maximum possible temperature)
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].blackbodyTemperature);

				//Surface Gravity
				fprintf(fp,"N/A,");

				//Planet Diameter
				fprintf(fp,"N/A,");

				//Planet Density
				fprintf(fp,"N/A,");

				//Mass of planet
				fprintf(fp,"N/A,");

				//Length of the day
				fprintf(fp,"N/A,");

				//liquid coverage (not nessecarily water!)
				fprintf(fp,"N/A,");

				//Minimum Molecular Weight Retained
				fprintf(fp,"N/A,");

				//Resource Value Modifier
				fprintf(fp,"%d,", system.stars[star].planets[planet].RVM);

				//Habitability Rating
				fprintf(fp,"%d,", system.stars[star].planets[planet].habitability);

				//Total affinity (RVM + habitability)
				fprintf(fp,"%d,", system.stars[star].planets[planet].affinity);

				//Volcanic Activity
				fprintf(fp,"N/A,");

				//Tectonic Activity
				fprintf(fp,"N/A,");

				//Marginalty
				fprintf(fp,"N/A,");

				//Suffocating
				fprintf(fp,"N/A,");

				//Toxicity
				fprintf(fp,"N/A,");

				//Corrosivity
				fprintf(fp,"N/A,");

				//Climate
				fprintf(fp,"N/A,");

				//Atmospheric Pressure
				fprintf(fp,"N/A,");

				//Atmospheric Composition
				fprintf(fp,"N/A\n");
			}
			else
			{
				//Size
				switch(system.stars[star].planets[planet].size)
				{
					case 'T':
						fprintf(fp,"Tiny,");
						break;
					case 'S':
						fprintf(fp,"Small,");
						break;
					case 'M':
						if(system.stars[star].planets[planet].type == 'G')
							fprintf(fp,"Medium,");//Gas Giant
						else
							fprintf(fp,"Standard,");//Terrestrial
						break;
					case 'L':
						fprintf(fp,"Large,");
						break;
					default:
						printf("\nFailure on line %d (system.stars[%d].planets[%d].size = %c)\n", __LINE__, star, planet, system.stars[star].planets[planet].size);//Displays in terminal window, not output file!
						break;
				}

				//Type
				switch(system.stars[star].planets[planet].type)
				{
					case 'I':
						fprintf(fp,"Ice,");
						break;
					case 'H':
						fprintf(fp,"Hadean,");
						break;
					case 'R':
						fprintf(fp,"Rock,");
						break;
					case 'S':
						fprintf(fp,"Sulfur,");
						break;
					case 'O':
						fprintf(fp,"Ocean,");
						break;
					case 'G':
						fprintf(fp,"Gas Giant,");
						break;
					case 'g':
						fprintf(fp,"Green House,");
						break;
					case 'r':
						fprintf(fp,"Garden,");
						break;
					case 'a':
						fprintf(fp,"Ammonia,");
						break;
					case 'C':
						fprintf(fp,"Cthonian,");
						break;
					default:
						printf("\nFailure on line %d\n", __LINE__);//Displays in terminal window, not output file!
						break;
				}

				//Ring
				switch(system.stars[star].planets[planet].rings)
				{
					case 'F':
						fprintf(fp,"Faint,");
						break;
					case 'S':
						fprintf(fp,"Spectacular,");
						break;
					case 'N':
						fprintf(fp,"None,");
						break;
					default:
						printf("\nFailure on line %d (%c), Planet = %d, star = %d\n", __LINE__, system.stars[star].planets[planet].rings, planet, star);//Displays in terminal window, not output file!
						break;
				}

				//Orbit
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].orbit);

				//Minimum Orbit
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].minOrbit);

				//Maximum Orbit
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].maxOrbit);

				//Eccentricity of Orbit
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].eccentricity);

				//Axial Tilt wrt orbit
				fprintf(fp,"%d,", system.stars[star].planets[planet].axialTilt);

				//Orbital period around its star
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].orbitalPeriod);

				//Total Tide due to all of its moons and the star
				if(system.stars[star].planets[planet].totalTide > 50.0)
					fprintf(fp,"Tide Locked,");
				else
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].totalTide);

				//Rotational Period (Not the same as length of day!
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].rotationalPeriod);

				//Average Surface Temperature
				fprintf(fp,"%d,", system.stars[star].planets[planet].temperature);

				//Blackbody temperature (Maximum possible temperature)
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].blackbodyTemperature);

				//Surface Gravity
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].gravity);

				//Planet Diameter
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].diameter);

				//Planet Density
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].density);

				//Mass of planet
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].mass);

				//Length of the day
				if(system.stars[star].planets[planet].dayLength > 4294967290.0)
					fprintf(fp,"Infinite,");
				else
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].dayLength);

				//liquid coverage (not nessecarily water!)
				fprintf(fp,"%d,", system.stars[star].planets[planet].hydrographicCoverage);

				//Minimum Molecular Weight Retained
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].MMWR);

				//Resource Value Modifier
				fprintf(fp,"%d,", system.stars[star].planets[planet].RVM);

				//Habitability Rating
				fprintf(fp,"%d,", system.stars[star].planets[planet].habitability);

				//Total affinity (RVM + habitability)
				fprintf(fp,"%d,", system.stars[star].planets[planet].affinity);

				//Volcanic Activity
				switch(system.stars[star].planets[planet].volcanicActivity)
				{
					case 'N':
						fprintf(fp, "None,");
						break;
					case 'L':
						fprintf(fp, "Light,");
						break;
					case 'M':
						fprintf(fp, "Moderate,");
						break;
					case 'H':
						fprintf(fp, "Heavy,");
						break;
					case 'E':
						fprintf(fp, "Extreme,");
						break;
					default:
						printf("\nFailure on line %d(%c)\n", __LINE__, system.stars[star].planets[planet].volcanicActivity);//Displays in the terminal window
						break;
				}

				//Tectonic Activity
				switch(system.stars[star].planets[planet].tectonicActivity)
				{
					case 'N':
						fprintf(fp, "None,");
						break;
					case 'L':
						fprintf(fp, "Light,");
						break;
					case 'M':
						fprintf(fp, "Moderate,");
						break;
					case 'H':
						fprintf(fp, "Heavy,");
						break;
					case 'E':
						fprintf(fp, "Extreme,");
						break;
					default:
						printf("\nFailure on line %d(%c)\n", __LINE__, system.stars[star].planets[planet].tectonicActivity);//Displays in the terminal window
						break;
				}

				//Marginalty
				switch(system.stars[star].planets[planet].atmosphere.marginality)
				{
					case 'P':
						fprintf(fp,"Poisonous,");
						break;
					case 'V':
						fprintf(fp,"Vacuum,");
						break;
					case 'N':
						fprintf(fp,"Not Marginal,");
						break;
					case 'o':
						fprintf(fp,"Low Oxygen,");
						break;
					case 'F':
						fprintf(fp,"Fluorine,");
						break;
					case 'S':
						fprintf(fp,"Sulphur Compounds,");
						break;
					case 'c':
						fprintf(fp,"Chlorine,");
						break;
					case 'T':
						fprintf(fp,"Organic Toxins,");
						break;
					case 'C':
						fprintf(fp,"High CO2,");
						break;
					case 'O':
						fprintf(fp,"High Oxygen,");
						break;
					case 'p':
						fprintf(fp,"Pollutants,");
						break;
					case 'I':
						fprintf(fp,"Inert Gases,");
						break;
					case 'n':
						fprintf(fp,"Nitrogen Compounds,");
						break;
					default:
						printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
						break;
				}

				//Suffocating
				switch(system.stars[star].planets[planet].atmosphere.suffocating)
				{
					case 'S':
						fprintf(fp,"Suffocating,");
						break;
					case 'N':
						fprintf(fp,"Non-Suffocating,");
						break;
					default:
						printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
						break;
				}

				//Toxicity
				switch(system.stars[star].planets[planet].atmosphere.toxicity)
				{
					case 'M':
						fprintf(fp,"Mild,");
						break;
					case 'H':
						fprintf(fp,"High,");
						break;
					case 'L':
						fprintf(fp,"Lethal,");
						break;
					case 'N':
						fprintf(fp,"Non-Toxic,");
						break;
					default:
						printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
						break;
				}

				//Corrosivity
				switch(system.stars[star].planets[planet].atmosphere.corrosivity)
				{
					case 'C':
						fprintf(fp,"Corrosive,");
						break;
					case 'N':
						fprintf(fp,"Non-Corrosive,");
						break;
					default:
						printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
						break;
				}

				switch(system.stars[star].planets[planet].atmosphere.climate)
				{
					case 'F':
						fprintf(fp,"Frozen,");
						break;
					case 'v':
						fprintf(fp,"Very Cold,");
						break;
					case 'c':
						fprintf(fp,"cold,");
						break;
					case 'y':
						fprintf(fp,"Chilly,");
						break;
					case 'C':
						fprintf(fp,"Cool,");
						break;
					case 'N':
						fprintf(fp,"Normal,");
						break;
					case 'W':
						fprintf(fp,"Warm,");
						break;
					case 'T':
						fprintf(fp,"Tropical,");
						break;
					case 'H':
						fprintf(fp,"Hot,");
						break;
					case 'V':
						fprintf(fp,"Very Hot,");
						break;
					case 'I':
						fprintf(fp,"Infernal,");
						break;
					default:
						printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
						break;
				}

				//Atmospheric Pressure
				fprintf(fp,"%0.2f,", system.stars[star].planets[planet].atmosphere.pressure);

				//Nitrogen
				if(system.stars[star].planets[planet].atmosphere.nitrogen)
					fprintf(fp, "Nitrogen,");

				//Ammonia
				if(system.stars[star].planets[planet].atmosphere.ammonia)
					fprintf(fp, "Ammonia,");

				//Methane
				if(system.stars[star].planets[planet].atmosphere.methane)
					fprintf(fp, "Methane,");

				//CO2
				if(system.stars[star].planets[planet].atmosphere.carbonDioxide)
					fprintf(fp, "CO2,");

				//O2
				if(system.stars[star].planets[planet].atmosphere.oxygen)
					fprintf(fp, "O2,");

				//Water Vapour
				if(system.stars[star].planets[planet].atmosphere.waterVapour)
					fprintf(fp, "Water Vapour,");

				//Helium
				if(system.stars[star].planets[planet].atmosphere.helium)
					fprintf(fp, "Helium,");

				//Hydrogen
				if(system.stars[star].planets[planet].atmosphere.hydrogen)
					fprintf(fp, "Hydrogen,");

				//Noble Gases
				if(system.stars[star].planets[planet].atmosphere.nobleGases)
					fprintf(fp, "Noble Gases,");

				//Formating for new lines
				fprintf(fp, "\n");

				//Moons
				for(moon = 1; moon <= system.stars[star].planets[planet].majourMoons; ++moon)
				{
					//Size
					switch(system.stars[star].planets[planet].moons[moon].size)
					{
						case 'T':
							fprintf(fp,"Tiny,");
							break;
						case 'S':
							fprintf(fp,"Small,");
							break;
						case 'M':
							fprintf(fp,"Standard,");//Terrestrial
							break;
						case 'L':
							fprintf(fp,"Large,");
							break;
						default:
							printf("\nFailure on line %d\n", __LINE__);//Displays in terminal window, not output file!
							break;
					}

					//Type
					switch(system.stars[star].planets[planet].moons[moon].type)
					{
						case 'I':
							fprintf(fp," Ice Moon,");
							break;
						case 'H':
							fprintf(fp," Hadean Moon,");
							break;
						case 'R':
							fprintf(fp," Rock Moon,");
							break;
						case 'S':
							fprintf(fp," Sulfur Moon,");
							break;
						case 'O':
							fprintf(fp," Ocean Moon,");
							break;
						case 'G':
							printf("\nFailure on line %d\n", __LINE__);//Displays in terminal window, not output file!
							break;
						case 'g':
							fprintf(fp," Green House Moon,");
							break;
						case 'r':
							fprintf(fp," Garden Moon,");
							break;
						case 'a':
							fprintf(fp," Ammonia Moon,");
							break;
						case 'C':
							fprintf(fp," Cthonian Moon,");
							break;
						default:
							printf("\nFailure on line %d (%c)\n", __LINE__, system.stars[star].planets[planet].moons[moon].type);//Displays in terminal window, not output file!
							break;
					}

					//Ring
					fprintf(fp,"N/A,");

					//Orbit
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moons[moon].orbit);

					//Minimum Orbit
					fprintf(fp,"N/A,");

					//Maximum Orbit
					fprintf(fp,"N/A,");

					//Eccentricity of Orbit
					fprintf(fp,"N/A,");

					//Axial Tilt wrt orbit
					fprintf(fp,"N/A,");

					//Orbital period around its star
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moons[moon].orbitalPeriod);

					//Total Tide due to all of its moons and the star
					if(system.stars[star].planets[planet].moons[moon].totalTide > 50.0)
						fprintf(fp,"Tide Locked,");
					else
						fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moons[moon].totalTide);

					//Rotational Period (Not the same as length of day!
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moons[moon].rotationalPeriod);

					//Average Surface Temperature
					fprintf(fp,"%d,", system.stars[star].planets[planet].moons[moon].temperature);

					//Blackbody temperature (Maximum possible temperature)
					fprintf(fp,"N/A,");

					//Surface Gravity
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moons[moon].gravity);

					//Planet Diameter
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moons[moon].diameter);

					//Planet Density
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moons[moon].density);

					//Mass of planet
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moons[moon].mass);

					//Length of the day
                    if(system.stars[star].planets[planet].moons[moon].dayLength > 4294967290.0)
                        fprintf(fp,"Infinite,");
                    else
                        fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moons[moon].dayLength);

					//liquid coverage (not nessecarily water!)
					fprintf(fp,"%d,", system.stars[star].planets[planet].moons[moon].hydrographicCoverage);

					//Minimum Molecular Weight Retained
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moons[moon].MMWR);

					//Resource Value Modifier
					fprintf(fp,"%d,", system.stars[star].planets[planet].moons[moon].RVM);

					//Habitability Rating
					fprintf(fp,"%d,", system.stars[star].planets[planet].moons[moon].habitability);

					//Total affinity (RVM + habitability)
					fprintf(fp,"%d,", system.stars[star].planets[planet].moons[moon].affinity);

					//Volcanic Activity
					switch(system.stars[star].planets[planet].moons[moon].volcanicActivity)
					{
						case 'N':
							fprintf(fp, "None,");
							break;
						case 'L':
							fprintf(fp, "Light,");
							break;
						case 'M':
							fprintf(fp, "Moderate,");
							break;
						case 'H':
							fprintf(fp, "Heavy,");
							break;
						case 'E':
							fprintf(fp, "Extreme,");
							break;
						default:
							printf("\nFailure on line %d(%c)\n", __LINE__, system.stars[star].planets[planet].moons[moon].volcanicActivity);//Displays in the terminal window
							break;
					}

					//Tectonic Activity
					switch(system.stars[star].planets[planet].moons[moon].tectonicActivity)
					{
						case 'N':
							fprintf(fp, "None,");
							break;
						case 'L':
							fprintf(fp, "Light,");
							break;
						case 'M':
							fprintf(fp, "Moderate,");
							break;
						case 'H':
							fprintf(fp, "Heavy,");
							break;
						case 'E':
							fprintf(fp, "Extreme,");
							break;
						default:
							printf("\nFailure on line %d(%c)\n", __LINE__, system.stars[star].planets[planet].moons[moon].tectonicActivity);//Displays in the terminal window
							break;
					}

					//Marginalty
					switch(system.stars[star].planets[planet].moons[moon].atmosphere.marginality)
					{
						case 'P':
							fprintf(fp,"Poisonous,");
							break;
						case 'V':
							fprintf(fp,"Vacuum,");
							break;
						case 'N':
							fprintf(fp,"Not Marginal,");
							break;
						case 'o':
							fprintf(fp,"Low Oxygen,");
							break;
						case 'F':
							fprintf(fp,"Fluorine,");
							break;
						case 'S':
							fprintf(fp,"Sulphur Compounds,");
							break;
						case 'c':
							fprintf(fp,"Chlorine,");
							break;
						case 'T':
							fprintf(fp,"Organic Toxins,");
							break;
						case 'C':
							fprintf(fp,"High CO2,");
							break;
						case 'O':
							fprintf(fp,"High Oxygen,");
							break;
						case 'p':
							fprintf(fp,"Pollutants,");
							break;
						case 'I':
							fprintf(fp,"Inert Gases,");
							break;
						case 'n':
							fprintf(fp,"Nitrogen Compounds,");
							break;
						default:
							printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
							break;
					}

					//Suffocating
					switch(system.stars[star].planets[planet].moons[moon].atmosphere.suffocating)
					{
						case 'S':
							fprintf(fp,"Suffocating,");
							break;
						case 'N':
							fprintf(fp,"Non-Suffocating,");
							break;
						default:
							printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
							break;
					}

					//Toxicity
					switch(system.stars[star].planets[planet].moons[moon].atmosphere.toxicity)
					{
						case 'M':
							fprintf(fp,"Mild,");
							break;
						case 'H':
							fprintf(fp,"High,");
							break;
						case 'L':
							fprintf(fp,"Lethal,");
							break;
						case 'N':
							fprintf(fp,"Non-Toxic,");
							break;
						default:
							printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
							break;
					}

					//Corrosivity
					switch(system.stars[star].planets[planet].moons[moon].atmosphere.corrosivity)
					{
						case 'C':
							fprintf(fp,"Corrosive,");
							break;
						case 'N':
							fprintf(fp,"Non-Corrosive,");
							break;
						default:
							printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
							break;
					}

					//Climate
					switch(system.stars[star].planets[planet].moons[moon].atmosphere.climate)
					{
						case 'F':
							fprintf(fp,"Frozen,");
							break;
						case 'v':
							fprintf(fp,"Very Cold,");
							break;
						case 'c':
							fprintf(fp,"cold,");
							break;
						case 'y':
							fprintf(fp,"Chilly,");
							break;
						case 'C':
							fprintf(fp,"Cool,");
							break;
						case 'N':
							fprintf(fp,"Normal,");
							break;
						case 'W':
							fprintf(fp,"Warm,");
							break;
						case 'T':
							fprintf(fp,"Tropical,");
							break;
						case 'H':
							fprintf(fp,"Hot,");
							break;
						case 'V':
							fprintf(fp,"Very Hot,");
							break;
						case 'I':
							fprintf(fp,"Infernal,");
							break;
						default:
							printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
							break;
					}

					//Atmospheric Pressure
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moons[moon].atmosphere.pressure);

					//Nitrogen
					if(system.stars[star].planets[planet].moons[moon].atmosphere.nitrogen)
						fprintf(fp, "Nitrogen,");

					//Ammonia
					if(system.stars[star].planets[planet].moons[moon].atmosphere.ammonia)
						fprintf(fp, "Ammonia,");

					//Methane
					if(system.stars[star].planets[planet].moons[moon].atmosphere.methane)
						fprintf(fp, "Methane,");

					//CO2
					if(system.stars[star].planets[planet].moons[moon].atmosphere.carbonDioxide)
						fprintf(fp, "CO2,");

					//O2
					if(system.stars[star].planets[planet].moons[moon].atmosphere.oxygen)
						fprintf(fp, "O2,");

					//Water Vapour
					if(system.stars[star].planets[planet].moons[moon].atmosphere.waterVapour)
						fprintf(fp, "Water Vapour,");

					//Helium
					if(system.stars[star].planets[planet].moons[moon].atmosphere.helium)
						fprintf(fp, "Helium,");

					//Hydrogen
					if(system.stars[star].planets[planet].moons[moon].atmosphere.hydrogen)
						fprintf(fp, "Hydrogen,");

					//Noble Gases
					if(system.stars[star].planets[planet].moons[moon].atmosphere.nobleGases)
						fprintf(fp, "Noble Gases,");

					//Formating for new lines
					fprintf(fp, "\n");
				}

				//Moonlets
				for(moonlet = 0; moonlet < (system.stars[star].planets[planet].innerMoonlets + system.stars[star].planets[planet].outerMoonlets); ++moonlet)
				{
					//Size
					fprintf(fp,"N/A,");

					//Type
					switch(system.stars[star].planets[planet].moonlets[moonlet].type)
					{
						case 'I':
							fprintf(fp," Inner Moonlet,");
							break;
						case 'O':
							fprintf(fp," Outer Moonlet,");
							break;
						default:
							printf("\nFailure on line %d\n", __LINE__);//Displays in the terminal window
							break;
					}

					//Rings
					fprintf(fp,"N/A,");

					//Orbit
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moonlets[moonlet].orbit);

					//Minimum Orbit,Maximum Orbit,Eccentricity,Axial Tilt,
					fprintf(fp,"N/A,N/A,N/A,N/A,");

					//Orbital Period
					fprintf(fp,"%0.2f,", system.stars[star].planets[planet].moonlets[moonlet].period);

					//Total Tide,Rotational Period,Temperature,Blackbody Temperature,Gravity
					fprintf(fp,"N/A,N/A,N/A,N/A,N/A,");

					//Diameter,Density,Mass,Day Length,Hydrographic Coverage
					fprintf(fp,"N/A,N/A,N/A,N/A,N/A,");

					//MMWR,RVM,Habitability,Affinity,Volcanic Activity
					fprintf(fp,"N/A,N/A,N/A,N/A,N/A,");

					//Tectonic Activity,Marginality,Suffocating,Toxicity,Corrosivity
					fprintf(fp,"N/A,N/A,N/A,N/A,N/A,");

					//Climate,Atmospheric Pressure,Atmospheric Composition
					fprintf(fp,"N/A,N/A,N/A,");

					//Formating for new lines
					fprintf(fp, "\n");
				}
			}

		}
		//Formating for new star entries
		fprintf(fp, "\n\n");
	}

	return;
}
