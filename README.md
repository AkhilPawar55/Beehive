SIMULATION OF BEEHIVE WITH MULTITHREADING IN C++

Author: Akhil Pawar
Date of Completion:- 05/01/2018

Aim:- Simulate a real world beehive, using modern C++ concepts like move semantics, smart pointers, and other C++ 11 and beyond features.
The project should be a multi-threaded application, and shoudl cater for thread synchronization to avoid race condition. 

Description:-
- Beehive is a collection of bees and stores resources i.e. pollen and nectar.
- There are 3 three types of Bees, namely Queen, Drones and Worker bees.
- Queen bee is responsible for giving birth to offsprings; which can be of type drone or worker bee.
- Drone bees are responsible for mating with queen bee; one at a time and they perish right after that.
- Worker bees can be responsible for either gathering pollens or nectars; thus worker bees are subcategorized as pollen worker bee and nectar worker bee.
- There are three resources which are shared among the bees termed as 'critical regions'; they are Beehive itself, Flower Field and Queens Chamber.
- Beehive as mentioned earlier stores the pollens and nectar; all bees need to consume one of each to survive. Bees access beehive in a synchronized fashion avoiding conflicts; i.e. race condition.
- Flower Field consists of 10 flowers which can be accessed by 10 bees at a time; also avoiding race condition.
- Queens chamber consists of a queue which has all the drones waiting to be summoned by queen bee so that they can fulfill their responsibility of mating with queen and then exiting the queue and perishing; also avaoding race condition.
- All bees are asssigned a unqiue id to identify them.
- Activity is printed out to console, also in a synchonized fashion to avaoid race condition.
- Print to console is preceeded by identifying tags:
	- *B; means bee is born
	- *BH; activity in beehive
	- *QC; activity in queens chamber
	- *FF; activity in flower field
	- *W; activity by worker bee
- The simulation runs for x number of seconds and after the simulation times out or when the beehive can no longer sustain itself (on an event of resources depleting) a statistics report is printed.
- The staistics consists of:
  - number of bees born
  - number of bees perished with the bee type and id
  - number of pollens remaining
  - number of nectar remaining
  - total number of pollen collected
  - total number of nectar collected 


Setup:-
- Use cmake to build the source files
	cd /src
	cmake --build .
	cd debug


Instructions:
- Run the program by passing arguments; 
	- First argument is seed value for random number generator (eg. 0)
	- second argument is simulation time in seconds (eg. 30)
	- third argument is number of drones (eg. 3)
	- fourth argument is number of nectar workers (eg. 5)
	- fifth argument is number of pollen workers (eg. 5)

- ./BeeHive.exe 0 30 3 5 5 
