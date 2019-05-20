#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

/*
 * A species will be defined by a vector of genes; each gene will have
 * 	a static min and max set at creation 
 * 	a static attribute for coninuous vs discrete
 * 	a dynamic attribute for sensitivity
 * 	a constraint checker, to make sure that a new individual has a valid gene set
 * Each individual will have
 * 	a vector of gene values, one for each gene in the species
 * 	a fitness value, assigned by the survival function.  A zero indicates a 
 * 		"perfect" individual, larger values are worse.
 * 	a string for notes
 * New individuals may be created by
 * 	breeding 2 individuals
 * 		pick 2 parents from the livepool
 * 		continuous genes will pick a value between the parents'
 * 		discrete genes will pick one or the other parent's gene value
 * 	mutating an individual
 * 		pick an individual from the livepool
 * 		change one gene value a radom amount
 * 	creating an entirely new individual
 * There will be three populations
 * 	The testpool will be new individuals to be tested
 * 	The livepool will be the individuals with the top N fitness values, from whom 
 * 		new individuals are created
 * 	The deadpool will be the individuals with low fitness values, which testpool 
 * 		individuals are checked against	and duplicates killed off without 
 * 		having to run the survival test
 * There will be a survival test function, which accepts an individual, and calculates 
 * 	the fitness score
 * There will be an assessment function, which runs on the species every N generations
 * 	sets the sensitivity attribute for each gene, based on the range of values 
 * 		in the livepool
 * 	determines the genetic diversity in the livepool
 * 	if the only areas of high genetic diversity are in low sensitivity genes, then
 * 		returns a high confidence that a solution has been found
 * When finshed, report the value and sensitivity for each parameter in the gene for 
 * 	the top individual, plus the range of values in the live pool.
 */

// this class contains information about a specific indivudual, such as the
// value for each gene and the performance of the individual
class Individual
{
public:
	// the gene values for this individual
	vector<double> values;
	string notes;

	// the overall performance of this individual
	double failure;
};

// this class contains the parameters for the genes in the population, such
// as permissible ranges of each gene
class Species
{
public:
	vector<double> mins;		// minimum value a gene can posess
	vector<double> maxes;	// maximum value a gene can posess
	vector<bool> discrete;
	vector<double> sensitivity;
	
	// add any constraints to genes here; return false if constraints are violated
	virtual bool ValidateIndividual(const Individual &individual);

	// breed two individuals together to make a new individual
	virtual Individual Breed(const Individual &one, const Individual &two);

	// mutate a random gene from a given individual to make a new individual
	virtual Individual Mutate(const Individual &one);

	// create an all-new individual with random genes
	virtual Individual Randomize(void);
};

// this class owns the population, and handles the evolution
class Population
{
public:
	// init population with a reference to the species, and the livepool size
	Population(Species &s, int n = 10) : species(s), szLivepool(n) {};

	// these are the new individuals to be tested for fitness
	vector<Individual> testpool;
	// these are the fittest individuals from the past
	vector<Individual> livepool;
	// these are the unfit individuals
	vector<Individual> deadpool;

	Species &species;
	int generation;

	int szLivepool;

	// Generate a new population with random genetic values
	void InitializePopulation(int members);

	// For each generation:

	// run simulations on all members
	// sort individuals by performance
	// preserve the genes of the top performer(s) for breeding
	// To create next generation:
	// create some all-new individuals
	// mutate top performers of this generation
	// mix genes of this generation's top perfomers with genes of overall top performers
	
	// sets fitness on individuals in the testpool; this one must be filled in, there
	//  is no generic behvior
	virtual void RunIteration() = 0;

	// merges testpool into livepool, sorts by performance, moves high performing individuals 
	//  into the livepool, poor performers into the deadpool
	virtual void FilterPopulation();
	// creates new testpool by breeding and mutating livepool individuals, adding a few new 
	//  all-new individuals to keep the inbreeding down
	virtual void DiversifyPopulation();

};

