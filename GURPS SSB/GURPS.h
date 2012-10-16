#ifndef GURPS_H_INCLUDED
#define GURPS_H_INCLUDED

#define MAX_PLANETS     20
#define MAX_STARS       3
#define MAX_MOONS       8
#define MAX_MOONLETS    18

struct atmospheres
{
    //Atmosphere consistency
    char    marginality,
            suffocating,
            toxicity,
            corrosivity,
            climate;
/*
marginality
    'P' = Poisonous       'V' = Vacuum            'N' = Not Marginal
    'o' = Low Oxygen      'F' = Fluorine          'S' = Sulphur Compounds
    'c' = Chlorine        'T' = Organic Toxins    'C' = High Carbon Dioxide
    'O' = High Oxygen     'p' = Pollunants        'I' = Inert Gases
    'n' = Nitrogen Compounds
suffocating
    'S' = Suffocating     'N' = Non-suffocating
toxicity
    'M' = Mildly          'H' = Highly            'L' = Lethal    'N' = Not Toxic
corrosivity
    'C' = Corrosive       'N' = Non-corrosive
Climate
    'F'	Frozen            'v'	Very Cold         'c'	Cold      'y'	Chilly
    'C'	Cool              'N'	Normal            'W'	Warm      'T'	Tropical
    'H'	Hot               'V'	Very Hot          'I'	Infernal
*/
    //Atmosphere composition
    unsigned char   nitrogen : 1,
                    ammonia : 1,
                    methane : 1,
                    carbonDioxide : 1,
                    oxygen : 1,
                    waterVapour : 1,
                    helium : 1,
                    hydrogen : 1,
                    nobleGases : 1;

    float   pressure,
            mass;
};

struct moonlet
{
    char    type;//I = inner moonlet, O = outer moonlet
    float   orbit,
            period;
};

struct moon
{//7 Moons
    float   density,
            diameter,
            gravity,
            mass,
            MMWR,
            orbit,
            orbitalPeriod,
            tideOnPlanetFromMoon,//The total tide this moon exerts on its planet
            tideOnMoonFromPlanet,//The tidal force the planet exerts on this moon
            totalTide,
            rotationalPeriod,//In 24 hour days, Negative is retrograde
            dayLength,//In 24 hour days, Negative is retrograde
            lunarCycle;//How long the moon takes to complete one cycle as seen from the planet

    char    size,
            type,
            tectonicActivity,//'N' = None, 'L' = Light, 'M' = Moderate, 'H' = Heavy, 'E' = Extreme
            volcanicActivity;//'N' = None, 'L' = Light, 'M' = Moderate, 'H' = Heavy, 'E' = Extreme

    struct  atmospheres atmosphere;

    int     hydrographicCoverage,
            RVM,//Resource Value Modifier
            habitability,
            affinity;

    unsigned int temperature;
};

struct  planet
{//Twenty Planets
    float   orbit,
            minOrbit,
            maxOrbit,
            blackbodyTemperature,//Moons share this number as well!
            density,
            mass,
            diameter,
            gravity,
            MMWR,//Minimum Molecular weight retained
            orbitalPeriod,
            eccentricity,//How eccentric the orbit is
            tideFromSun,
            totalTide,
            rotationalPeriod,//In 24 hour days, Negative is retrograde
            dayLength;//Length of the apparent day

    char    size,//'T' = Tiny, 'S' = Small, 'M' = Medium or Standard, 'L' = Large
            type,//'A' = Asteroid Belt, 'E' = Empty, 'I' = Ice, 'H' = Hadean, 'R' = Rock, 'S' = Sulfur,
                 //'O' = Ocean, 'G' = Gas Giant, 'g' = Green House, 'r' = Garden, 'a' = Ammonia, 'C' = Chthonian
            rings,//F if it has faint rings, N if it does not, S for spectacular Rings
            tectonicActivity,//'N' = None, 'L' = Light, 'M' = Moderate, 'H' = Heavy, 'E' = Extreme
            volcanicActivity;//'N' = None, 'L' = Light, 'M' = Moderate, 'H' = Heavy, 'E' = Extreme

    int     axialTilt,//Degrees that the planet rotates out of true with the sun, note not orbit, but rotate!
            hydrographicCoverage,
            innerMoonlets,//Number of inner Moonlets
            majourMoons,//Number of Majour moons
            outerMoonlets,//Number of outer Moonlets
            RVM,//Resource Value Modifier
            habitability,
            affinity;

    unsigned int temperature;

    struct  atmospheres atmosphere;

    struct  moon moons[MAX_MOONS];

    struct  moonlet moonlets[MAX_MOONLETS];
};

struct star
{//Three Stars
    int     numberOfPlanets,
            gasGiantFlag,//1 = No Gas Giants, 2 = Conventional Gas Giant, 3 = Eccentric Gas Giant, 4 = Epistellar Gas Giant
            forbiddenFlag,//1 = No planets, 2 = Planets for each sun, 3 = Planets circle this one and its companion, 4 = Planets for both suns
			companionFlag;//1 = ungenerated companion star, 0 = no companion star

    float   mass,
            luminosity,
            temperature,
            radius,
            averageOrbit,
            minOrbit,
            maxOrbit,
            eccentricity,
            innerForbiddenZone,
            outerForbiddenZone,
            innerLimitRadius,
            outerLimitRadius,
            snowLine,
            firstGasGiant,
            lMin,
            orbitalPeriod;

    char    spectralType[2],
            sequence;//'m' for main sequence, 's' for sub-giant, 'g' for giant

    struct  planet planets[MAX_PLANETS];
};

struct solarSystem
{
    unsigned int uniqueID;//The initial seed to allow regeneration of the system (Procedurally generated)

    int     numberOfStars,
            primaryStar;

    float   stellarAge;

    struct star stars[MAX_STARS];
};

#endif // GURPS_H_INCLUDED
