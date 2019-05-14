#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "Genetic.h"

// make sure the species is viable by enforcing any intra-gene constraints
bool Species::ValidateIndividual(const Individual &individual)
{
	// by default, anything goes
	return true;
}

// breed two individuals together to make a new individual
Individual Species::Breed(const Individual &one, const Individual &two)
{
	Individual child;
	child.failure = 1000000000;

	// continuous genes will be averaged together with random weight
	// discrete genes will pick randomly between parent values
	for(int i = 0; i < one.values.size(); ++i)
	{
		if(discrete[i])
		{
			if(1 == rand() % 2)
				child.values[i] = one.values[i];
			else
				child.values[i] = two.values[i];
		}
		else
		{
			if(1 == rand() % 2)
				child.values[i] = (2.0 * one.values[i] + two.values[i]) / 3.0;
			else
				child.values[i] = (2.0 * two.values[i] + one.values[i]) / 3.0;
		}
	}
	
	// make sure new individual is not a clone of a parent; if so, mutate
	bool clone = true;
	for(int i = 0; i < one.values.size(); ++i)
	{
		if(child.values[i] != one.values[i])
		{
			clone = false;
			break;
		}
		if(child.values[i] != two.values[i])
		{
			clone = false;
			break;
		}
	}
	if(clone)
		return Mutate(child);

	// make sure the individual is a valid member of the species, if not, create a new one
	if(ValidateIndividual(child))
		return child;

	return Randomize();
}

// mutate a random gene from a given individual to make a new individual
Individual Species::Mutate(const Individual &one)
{
	Individual two = one;
	int mutantGene = rand() % one.values.size();

	if(discrete[mutantGene])
	{
		two.values[mutantGene] = rand() % int(maxes[mutantGene] - mins[mutantGene]);
		two.values[mutantGene] + mins[mutantGene];
	}
	else
	{
		// set to value [0 .. 1)
		two.values[mutantGene] = (double)rand() / RAND_MAX;
		// scale to range
		two.values[mutantGene] = two.values[mutantGene] * (maxes[mutantGene] - mins[mutantGene]);
		// shift up by minimum values
		two.values[mutantGene] += mins[mutantGene];
	}

	// make sure result is a valid individual
	if(ValidateIndividual(two))
		return two;

	// if not, create a new individual with random genes
	return Randomize();
}

// create an all-new individual with random genes
// if there are any gene constraints (such as mutally exclusive values) then this will need to enforce them
Individual Species::Randomize(void)
{
	Individual newbie;

	for(int i = 0; i < discrete.size(); ++i)
	{
		if(discrete[i])
		{
			newbie.values[i] = rand() % int(maxes[i] - mins[i]);
			newbie.values[i] + mins[i];
		}
		else
		{
			// set to value [0 .. 1)
			newbie.values[i] = (double)rand() / RAND_MAX;
			// scale to range
			newbie.values[i] = newbie.values[i] * (maxes[i] - mins[i]);
			// shift up by minimum values
			newbie.values[i] += mins[i];
		}
	}

	if(ValidateIndividual(newbie))
		return newbie;

	throw "Species::Randomize() failed to generate a compliant individual!";
}

// Generate a new population with random genetic values
void Population::InitializePopulation(int members)
{
	testpool.resize(0);
	livepool.resize(0);
	deadpool.resize(0);

	for(int i = 0; i < members; ++i)
		testpool.push_back(species.Randomize());

}

// for sorting Individuals from least to greates failure
bool SortIndividuals(Individual &one, Individual &two)
{
	return one.failure < two.failure;
}

void Population::FilterPopulation()
{
	// add testpool to livepool
	// sort by fitness
	// keep top of livepool, move the rest to the deadpool
	for(int i = 0; i < testpool.size(); ++i)
		livepool.push_back(testpool[i]);

	sort(livepool.begin(), livepool.end(), SortIndividuals);

	for(int i = szLivepool; i < livepool.size(); ++i)
		deadpool.push_back(livepool[i]);

	livepool.resize(szLivepool);
}

void Population::DiversifyPopulation()
{
	// breed top of livepool with each of remainder of livepool
	// mutate all of livepool
	// add a new individual
	testpool.resize(0);

	for(int i = 1; i < livepool.size(); ++i)
		testpool.push_back(species.Breed(livepool[0], livepool[i]));

	for(int i = 0; i < livepool.size(); ++i)
		testpool.push_back(species.Mutate(livepool[i]));

	testpool.push_back(species.Randomize());
}
