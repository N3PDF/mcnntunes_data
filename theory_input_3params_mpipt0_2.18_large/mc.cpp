#include <iostream>
#include <cstdlib>
#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/Pythia8Rivet.h"

using namespace Pythia8;

int main(int argc, char * argv[])
{

	//Checking command line arguments
	if(argc<5)
	{
		std::cerr << "Usage: ./main runcard output seed analysis_name ... analysis_name"
				  << std::endl;
		return -1;
	}

	//Checking whether runcard exists
	ifstream runcard(argv[1]);
	if(!runcard)
	{
		std::cerr << "File " << argv[1] << " not found! Run stopped." << std::endl;
		return -1;
	}
	runcard.close();

	Pythia pythia;

	//Reading runcard
	pythia.readFile(argv[1]);

	//Setting seed
	pythia.readString("Random:setSeed = on");
	const unsigned int seed_index = std::atoi(argv[3]);
	if(seed_index >= 10)
	{
		std::cerr << "Seed index out of range!" << std::endl;
		return -1;
	}
	const unsigned int seeds[10]={442826010, 159427356,
				      754863591, 103247016,
				      24150321, 32652,
				      75624, 659,
				      3334875, 414124};
	pythia.readString("Random:seed = " + std::to_string(seeds[seed_index]));

/*
	pythia.readString("Main:runRivet = on");
	pythia.readString("Main:analyses = ATLAS_2014_I1300647");
	pythia.readString("Main:writeHepMC = on");
*/
	pythia.init();

	//Setting up Rivet interface
	Pythia8Rivet rivet(pythia, argv[2] + std::string("_")  + std::to_string(seeds[seed_index]) + ".yoda");
	for(unsigned int i=4; i<argc; i++)
		rivet.addAnalysis(argv[i]);

	//Event cycle
	unsigned int nEvent = pythia.mode("Main:numberOfEvents");
	unsigned int maxErrors = pythia.mode("Main:timesAllowErrors");
	unsigned int nErrors = 0;
	for(unsigned int iEvent = 0; iEvent < nEvent; ++iEvent)
	{
		//Running the event and checking for errors
		if(!pythia.next())
		{
			nErrors++;
			if(nErrors >= maxErrors)
			{
				std::cerr << "Too many errors! Run stopped." << std::endl;
				return -1;
			}
			continue;
		}

		//Pushing event to Rivet
		rivet();
	}

	pythia.stat();

	//Finalising the run
	rivet.done();

	return 0;
}
