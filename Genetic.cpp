#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

#include "Genetic.h"

// make sure the species is viable by enforcing any intra-gene constraints
virtual bool Species::ValidateIndividual(vector<double> values)
{
	// by default, anything goes
	return true;
}

// breed two individuals together to make a new individual
virtual Individual Species::Breed(const Individual &one, const Individual &two)
{
	Individual child;
	child.failure = 1000000000;

	// continuous genes will be averaged together with random weight
	// discrete genes will pick randomly between parent values
	for(int i = 0; i < values.size(); ++i)
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
	for(int i = 0; i < values.size(); ++i)
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
virtual Individual Species::Mutate(const Individual &one)
{
	int mutantGene = rand() % one.values.size();

	if(discrete[mutantGene])
	{
		one.value[mutantGene] = rand() % (maxes[mutantGene] - mins[mutantGene]);
		one.value[mutantGene] + mins[mutantGene];
	}
	else
	{
		// set to value [0 .. 1)
		one.value[mutantGene] = (double)rand() / RAND_MAX;
		// scale to range
		one.value[mutantGene] = one.value[mutantGene] * (maxes[mutantGene] - mins[mutantGene]);
		// shift up by minimum value
		one.value[mutantGene] += mins[mutantGene];
	}

	// make sure result is a valid individual
	if(ValidateIndividual(one))
		return one;

	// if not, create a new individual with random genes
	return Randomize();
}

// create an all-new individual with random genes
// if there are any gene constraints (such as mutally exclusive values) then this will need to enforce them
virtual Individual Species::Randomize(void)
{
	Individual newbie;

	for(int i = 0; i < discrete.size(); ++i)
	{
		if(discrete[i])
		{
			newbie.value[i] = rand() % (maxes[i] - mins[i]);
			newbie.value[i] + mins[i];
		}
		else
		{
			// set to value [0 .. 1)
			newbie.value[i] = (double)rand() / RAND_MAX;
			// scale to range
			newbie.value[i] = newbie.value[i] * (maxes[mutantGene] - mins[i]);
			// shift up by minimum value
			newbie.value[i] += mins[i];
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


