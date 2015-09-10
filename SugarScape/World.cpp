//
//  World.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "World.h"
#include "group.h"
#include "Action.h"



//Constructor
World::World(int dimensionSize)
    :size(DIM),step(0),cultureCount(CultureCount),
    maxAge(MaxAge),maxVision(MaxVision),maxMetabolism(MaxMetabolism),
    minAge(MinAge),minMetabolism(MinMetabolism),sugarGrowth(SugarGrowth),
    duration(Duration),rate(Rate),initialPopulationSize(InitialPopulationSize),
    initialSugarMax(InitialSugarMax),initialSugarMin(InitialSugarMin),winterRate(WinterRate),
    initialSpiceMax(InitialSpiceMax),initialSpiceMin(InitialSpiceMin),spiceGrowth(SpiceGrowth),
    seasonLength(SeasonLength),production(Production),consumption(Consumption),
    combatLimit(CombatLimit),immunityLength(ImmunityLength),pollutionRate(PollutionRate),
    childAmount(ChildAmount),diseaseLength(DiseaseLength),initialPopulation(AGENTCOUNT)
{
    if (dimensionSize>0) {
        size=dimensionSize;
        initialPopulation=size*size/4;
    }
    rng.seed();
    }

//Destructor
World::~World(){
    delete [] Lattice;
    
}

//helpers
bool World::init(void)
{
    //Create Locations in Lattice
    Lattice=new Location[size*size];
    for (int i=0; i<size*size; ++i) {
        Lattice[i].setWorld(this);
        Lattice[i].setPosition(std::pair<int,int>(i/size,i%size));
        Lattice[i].setMaxSugar(getRnd(InitialSugarMin, InitialSugarMax));
        Lattice[i].setSugar(getRnd(InitialSugarMin, Lattice[i].getMaxSugar()));
    }
    
    //create agents and put in lattice
    std::pair<int,int> pos;
    for (int i=0; i<initialPopulation; ++i) {//quatar fill lattice
        Agent *anAgent= nullptr;
        do {
            pos.first=getRnd(0, size-1);
            pos.second=getRnd(0,size-1);
        } while (Lattice[pos.first*size+pos.second].hasAgent());
        anAgent=new Agent(this,nullptr,nullptr,pos);
        Lattice[pos.first*size+pos.second].initAgent(anAgent);
        population.push_back(anAgent);
    }
    return true;
}

int World::sync(void){
#pragma omp parallel for
    for (int i=0; i<size*size; ++i) {
        Lattice[i].sync();
        if (Lattice[i].hasAgent()) Lattice[i].getAgent()->sync();
    }
    return 0;
}

void World::sanityCeck(void){
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            if (Lattice[i*size+k].hasAgent()){
                std::cout << Lattice[i*size+k].getAgent()->getMetabolism()<<","<<Lattice[i*size+k].getAgent()->getSugar()<< ","
                <<Lattice[i*size+k].getAgent()->getAge() << ","<< Lattice[i*size+k].getAgent()->getMaxAge() <<std::endl;;
            }
        }
        
    }
    std::cout <<std::endl;
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            std::cout << Lattice[i*size+k].getSugar()<<" , ";
        }
        std::cout << std::endl;
    }
    std::cout <<std::endl;
}

int World::wrap(int x){
    if (x<0) {
         return size+x;
    } else if (x>=size){
        return x-size;
    }
    else {
        return x;
    }
}

int World::getAgentCount(void){
    int count=0;
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            if (Lattice[i*size+k].hasAgent()){
                ++count;
            }
        }
        
    }
    return count;
}

bool World::resetNeighbours(void){
#pragma omp parallel for
    for (int i=0; i<size*size; ++i) {
        if(Lattice[i].hasAgent()) Lattice[i].getAgent()->resetNeighbours();
    }
    return true;
}


//*************************Getters*************************


int World::getRnd(int start,int end){
    std::uniform_int_distribution<uint32_t> uint_dist(start,end);
    return uint_dist(rng);
}

/**
 Returns the step number
 @returns step
 @exception void
 */
int World::getStep(void){
    return step;
}
/**
 Returns the dimensions of the lattice
 @returns size
 @exception void
 */
int World::getSize(void){
    return size;
}
/**
 Returns the size of the culture string
 @returns cultureCount
 @exception void
 */
int World::getCultureCount(void){
    return cultureCount;
}
/**
 Returns the size of a disease string
 @returns cultureCount
 @exception void
 */
int World::getDiseaseLength(void){
    return diseaseLength;
}
/**
 Returns the maximum possible vision length of any agent
 @returns maxVision
 @exception void
 */
int World::getMaxVision(void){
    return maxVision;
}
/**
 Returns the minimum possible spice metabolism rate for any agent
 @returns minMetabolism
 @exception void
 */
int World::getMinSpiceMetabolism(void){
    return minSpiceMetabolism;
}
/**
 Returns the minimum possible metabolism rate for any agent
 @returns minMetabolism
 @exception void
 */
int World::getMinMetabolism(void){
    return minMetabolism;
}
/**
 Returns the maximum possible metbolism rate for any agent
 @returns maxMetabolism
 @exception void
 */
int World::getMaxMetabolism(void){
    return maxMetabolism;
}
/**
 Returns the maximum possible spice metbolism rate for any agent
 @returns maxMetabolism
 @exception void
 */
int World::getMaxSpiceMetabolism(void){
    return maxSpiceMetabolism;
}
/**
 Returns the growth rate for each location
 @returns sugarGrowth
 @exception void
 */
int World::getSugarGrowth(void){
    return sugarGrowth;
}
/**
 Returns the growth rate for each location
 @returns spiceGrowth
 @exception void
 */
int World::getSpiceGrowth(void){
return sugarGrowth;
}
/**
 Returns the minimum possible natural lifespan of an agent
 @returns minAge
 @exception void
 */
int World::getMinAge(void){
    return minAge;
}
/**
 Returns the maximum possible natural lifespan of an agent
 @returns maxAge
 @exception void
 */
int World::getMaxAge(void){
    return maxAge;
}
/**
 Returns the duraion of a loan
 @returns duration
 @exception void
 */
int World::getDuration(void){
    return duration;
}
/**
 Returns the rate of interest for a load
 @returns rate
 @exception void
 */
int World::getRate(void){
    return rate;
}
/**
 Returns the minimum possible initial sugar allocation assigned to an agent
 @returns initialSugarMin
 @exception void
 */
int World::getInitialSugarMin(void){
    return initialSugarMin;
}
/**
 Returns the maximum possible initial sugar allocation assigned to an agent
 @returns initialSugarMax
 @exception void
 */
int World::getInitialSugarMax(void){
    return initialSugarMax;
}
/**
 Returns the minimum possible initial sugar allocation assigned to an agent
 @returns initialSugarMin
 @exception void
 */
int World::getInitialSpiceMin(void){
    return initialSpiceMin;
}
/**
 Returns the maximum possible initial spice allocation assigned to an agent
 @returns initialSpiceMax
 @exception void
 */
int World::getInitialSpiceMax(void){
    return initialSpiceMax;
}
/**
 Returns the winter growth rate for each location
 @returns winterRate
 @exception void
 */
int World::getWinterRate(void){
    return winterRate;
}
/**
 Returns the length of each season
 @returns seasonLength
 @exception void
 */
int World::getSeasonLength(void){
    return seasonLength;
}
/**
 Returns the amount of pollution generated by activity
 @returns production :integer
 @exception void
 */
int World::getProduction(void){
    return production;
}
int World::getConsumption(void){
    return consumption;
}
int World::getCombatLimit(void){
    return combatLimit;
}
int World::getImmunityLength(void){
    return immunityLength;
}
int World::getInitialPopulationSize(void){
    return initialPopulationSize;
}
int World::getPollutionRate(void){
    return pollutionRate;
}
int World::getChildAmount(void){
    return childAmount;
}
Agent* World::getAgent(std::pair<int,int> pos){
    return Lattice[wrap(pos.first)*size+wrap(pos.second)].getAgent();
}


std::vector<Location*> World::getNeighbourhood(std::pair<int,int> pos,int range)
{
    std::vector<Location*> neighbourhood;
    for (int i=pos.first-range; i<=pos.first+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        if (i!=pos.first) {
            neighbourhood.push_back(&Lattice[wrap(i)*size+pos.second]);
        }//if
    }//for
    for (int i=pos.second-range; i<=pos.second+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        if (i!=pos.second) {
            neighbourhood.push_back(&Lattice[(pos.first*size)+wrap(i)]);
        }//if
    }//for
    return neighbourhood;
}

/**
 * get all empty locations around us that are not marked done
 * @param pos :x,y-coordinates of index
 * @param range :vision - how far we can see in four directions
 * @return vector of Location pointers (all empty locations in our neighbourhood
 */
std::vector<Location*> World::getEmptyNeighbourhood(std::pair<int,int> pos,int range)
{
    std::vector<Location*> neighbourhood;
    Location *loc=nullptr; //&Lattice[pos.first*size+pos.second];
    for (int i=pos.first-range; i<=pos.first+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        //std::cout << i <<"," << pos.second << "=" << wrap(i) << "*"<<wrap(pos.second) << "*" << wrap(i)*size+wrap(pos.second) << std::endl;
        //pick location only if it !=identity (us) and is empty and is not marked done
        loc=&Lattice[wrap(i)*size+wrap(pos.second)];
        if (loc->hasAgent()==false && loc->isDone()==false) {
            neighbourhood.push_back(loc);
        }//if
    }//for
    for (int i=pos.second-range; i<=pos.second+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        //pick location only if it !=identity (us) and is empty and is not marked done
        loc=&Lattice[(pos.first*size)+wrap(i)];
        if (false==loc->hasAgent() && false==loc->isDone()) {
            neighbourhood.push_back(loc);
        }//if
    }//for
    return neighbourhood;
}


/**
 * get all empty or attackable locations around us that are not marked done
 * @param pos :x,y-coordinates of index
 * @param range :vision - how far we can see in four directions
 * @return vector of Location pointers (all empty locations in our neighbourhood
 */
std::vector<Location*> World::getCombatNeighbourhood(std::pair<int,int> pos,int range)
{
    std::vector<Location*> neighbourhood;
    Agent *me=Lattice[pos.first*size+pos.second].getAgent();
    Agent *other=nullptr;
    for (int i=pos.first-range; i<=pos.first+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        //pick location only if it !=identity (us) and is empty and is not marked done
        if (i!=pos.first && Lattice[wrap(i)*size+pos.second].isDone()==false) {
            if (Lattice[wrap(i)*size+pos.second].hasAgent()==false )
            {
                neighbourhood.push_back(&Lattice[wrap(i)*size+pos.second]);
            }else {
                other=Lattice[wrap(i)*size+pos.second].getAgent();
                if (me->getTribe()!=other->getTribe() && me->getWealth()>other->getWealth())
                {
                    neighbourhood.push_back(&Lattice[wrap(i)*size+pos.second]);
                }
            }
            
        }//if
    }//for
    
    for (int i=pos.second-range; i<=pos.second+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        //pick location only if it !=identity (us) and is empty and is not marked done
        if (i!=pos.second && false==Lattice[pos.first*size+wrap(i)].isDone())
        {
            if (false==Lattice[pos.first*size+wrap(i)].hasAgent()) {
                neighbourhood.push_back(&Lattice[pos.first*size+wrap(i)]);
            }else {
                other=Lattice[pos.first*size+wrap(i)].getAgent();
                if (me->getTribe()!=other->getTribe() && me->getWealth()>other->getWealth())
                {
                    neighbourhood.push_back(&Lattice[pos.first*size+wrap(i)]);
                }
            }
        }//if
    }//for
    return neighbourhood;
}



/**
 * Returns all agents in our neighbourhood who are not marked as done!
 * @param xPosition :x-xoordinate of index
 * @param yPosition :y-coordinate of index
 * @param range :vision - how far we can see in four directions
 * @return vector of pointers to agents who are neighbours and not marked done
 */
std::vector<Agent*> World::getNeighbours(std::pair<int,int> pos,int range)
{
    std::vector<Agent*> neighbourList;
    Agent* neighbour=nullptr;
    for (int i=pos.first-range; i<=pos.first+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        neighbour=Lattice[wrap(i)*size+pos.second].getAgent();
        if (neighbour!=nullptr && i!=pos.first && Lattice[wrap(i)*size+pos.second].isDone()==false) {
            neighbourList.push_back(neighbour);
        }//if
    }//for
    for (int i=pos.second-range; i<=pos.second+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        neighbour=Lattice[pos.first*size+wrap(i)].getAgent();
        if (neighbour!=nullptr && i!=pos.second && Lattice[pos.first*size+wrap(i)].isDone()==false) {
            neighbourList.push_back(neighbour);
        }//if
    }//for
    return neighbourList;
}
Location* World::getLattice(void)
{
    return Lattice;
}
Location* World::getLocation(std::pair<int, int> pos)
{
    return &Lattice[wrap(pos.first)*size+wrap(pos.second)];
}



//Setters
int World::setSize(int newSize){
    size=newSize;
    return size;
}
int World::setCultureCount(int newCultureCount){
    cultureCount=newCultureCount;
    return cultureCount;
}
int World::setDiseaseLength(int newDiseaseLength){
    diseaseLength=newDiseaseLength;
    return diseaseLength;
}
int World::setMaxVision(int newMaxVision){
    maxVision=newMaxVision;
    return maxVision;
}
int World::setMinMetabolism(int newMinMetabolism){
    minMetabolism=newMinMetabolism;
    return minMetabolism;
}
int World::setMaxMetabolism(int newMaxMetabolism){
    maxMetabolism=newMaxMetabolism;
    return maxMetabolism;
}
int World::setSugarGrowth(int newSugarGrowth){
    sugarGrowth=newSugarGrowth;
    return sugarGrowth;
}
int World::setSpiceGrowth(int newSpiceGrowth){
    spiceGrowth=newSpiceGrowth;
    return spiceGrowth;
}
int World::setMinAge(int newMinAge){
    minAge=newMinAge;
    return minAge;
}
int World::setMaxAge(int newMaxAge){
    maxAge=newMaxAge;
    return maxAge;
}
int World::setDuration(int newDuration){
    duration=newDuration;
    return duration;
}
int World::setRate(int newRate){
    rate=newRate;
    return rate;
}
int World::setInitialSugarMin(int newInitialSugarMin){
    initialSugarMin=newInitialSugarMin;
    return initialSugarMin;
}
int World::setInitialSugarMax(int newInitialSugarMax){
    initialSugarMax=newInitialSugarMax;
    return initialSugarMax;
}
int World::setInitialSpiceMin(int newInitialSpiceMin){
    initialSpiceMin=newInitialSpiceMin;
    return initialSpiceMin;
}
int World::setInitialSpiceMax(int newInitialSpiceMax){
    initialSpiceMax=newInitialSpiceMax;
    return initialSpiceMax;
}
int World::setWinterRate(int newWinterRate){
    winterRate=newWinterRate;
    return winterRate;
}
int World::setSeasonLength(int newSeasonLength){
    seasonLength=newSeasonLength;
    return seasonLength;
}
int World::setProduction(int newProduction){
    production=newProduction;
    return production;
}
int World::setConsumption(int newConsumption){
    consumption=newConsumption;
    return consumption;
}
int World::setCombatLimit(int newCombatLimit){
    combatLimit=newCombatLimit;
    return combatLimit;
}
int World::setImmunityLength(int newImmunityLength){
    immunityLength=newImmunityLength;
    return immunityLength;
}
int World::setInitialPopulationSize(int newInitialPopulationSize){
    initialPopulationSize=newInitialPopulationSize;
    return initialPopulationSize;
}
int World::setPollutionRate(int newPollutionRate){
    pollutionRate=newPollutionRate;
    return pollutionRate;
}
int World::setChildAmount(int newChildAmount){
    childAmount=newChildAmount;
    return childAmount;
}
Agent* World::setAgent(std::pair<int,int> pos, Agent *newAgent){
    return Lattice[wrap(pos.first)*size+wrap(pos.second)].setAgent(newAgent);
}
Agent* World::killAgent(std::pair<int,int> pos)
{
    if (Lattice[wrap(pos.first)*size+wrap(pos.second)].hasAgent()) {
        return Lattice[wrap(pos.first)*size+wrap(pos.second)].killAgent();
    }
    else
    {
        return nullptr;
    }
}
//Rule Application

/**
 * Add a rule to the list of active rules
 * @param rule
 * @return number of rules  that are active
 * @exception none
 */
int World::addRule(Action* rule){
    activeRules.push_back(rule);
    return (int)activeRules.size();
}

/**
 * apply each active rule in turn
 * @return number of rules applied
 * @exception none
 */
int World::applyRules(){
    int ruleCount=0;
    for(auto rule:activeRules){
        ruleCount+=rule->concurrentRun();//run(0,0,size);
        sync();
    }
    return ruleCount;
}
