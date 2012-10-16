extern  struct  solarSystem initializeStars(struct solarSystem system);
extern  float   nextOrbit(float currentOrbit, int direction);//Returns the next orbit, direction = 1 then going outward, direction = 0 then inward
extern  char    planetoidType(float blackBodyTemp, char worldSize, char worldType, float massStar, float stellarAge);//Returns the world or moons type
extern  int     atmosphereCheck(char worldSize, char worldType);//Checks to see if the planet or moon can support an atmosphere
extern  struct  solarSystem orbitSort(struct solarSystem system, int sortDirection);
extern  struct  atmospheres atmosphericComposition(char size, char type);//Determines the type of atmosphere and its composition
extern  char    marginalAtmosphere();//Determines the type of marginality
extern  int     hydrographicCoverage(char type, char size);//Calculates the amount of liquid coverage
extern  void    displayAtmosphere(struct solarSystem system, int star, int planet, int moon);
extern  unsigned int averageTemperature(char size, char type, int hydro, float atmosphericMass, float blackbody);
extern  char    climate(int surfaceTemperature);
extern  float   worldDensity(char size, char type);
extern  float   icyCore();
extern  float   smallIronCore();
extern  float   largeIronCore();
extern  struct  solarSystem worldSizesGasGiant(struct solarSystem, int star, int planet);//Determines all of the Gas Giants unique elements
extern  float   atmosphericPressure(char size, char type, float atmoMass, float gravity);
extern  float   MMWR(float blackbody, float diameter, float density);
extern  float   worldMass(float density, float diameter);
extern  float   worldGravity(float diameter, float density);
extern  float   worldDiameter(int blackbody, float density, char size);
extern  float   orbitalPeriodDays(float distance, float mass);//Returns the orbital time in days
extern  float   planetaryEccentricity(struct solarSystem system, int star, int planet);
extern  float   satelliteOrbitalRadius(float planetDiameter, int moonType, char planetType, char moonSize, char planetSize);
extern  struct  solarSystem moonOrbitFixer(struct solarSystem system, int star, int planet);
extern  struct  solarSystem moonOrbitSort(struct solarSystem system, int star, int planet);
extern  float   randomRotationalPeriod(char type, char size);
extern  float   localCalendar(float sidereal, float period);//Calculates the apparent length of a day
extern  struct  solarSystem volcanism(struct solarSystem system, int star, int planet, int moon);
extern  char    tectonics(char size, char type, char volcanism, float hydro, int moons);
extern  int     planetRVM(char volcanicActivity, char tectonicActivity);
extern  int		asteroidRVM();
extern  int     habitability(struct solarSystem system, int star, int planet, int moon);
extern  int     affinity(int RVM, int habitability);
extern  struct  solarSystem generateSystem(struct solarSystem system, unsigned int address);
