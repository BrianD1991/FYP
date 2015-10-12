//
//  Agent.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__Agent__
#define __SugarScape__Agent__

#include <iostream>
#include <vector>
#include <algorithm>

class World;
class Location;

enum Sex {
    male = 0,
    female = 1,
    unknown = 2
    };

enum affiliation {
    red = 0,
    blue = 1
    };


/*!  \class  Agent
 \brief entities that move and interact on the lattice.
 
 Agents move across the lattice and interact with each other and the location they reside in.
 */
class Agent{
    
    //immutable
    World* theWorld;/*!< The Class containing everything in the simulation*/
    Sex sex; /*!< Agents are either male or female */
    int vision; /*!< The number of locations that an agent can see out to */
    int maxAge; /*!< Maximum lifespan of an agent */
    int cultureLength; /*!< Length of culture bitstring */
    int immunityLength; /*!< Length of immunity bitstring */
    
    int diseaseLength; //!
    /*!
     Not mentioned in specification but we will assume all diseases are the same length!
     Otherwise code needs to change to use std::vector<bool> for diseases
     */
    
    //mutable
    int amountEaten;/*!< Store amount last eaten - required for Pollution Formation rule */
    bool done; /*!< True if agent has completed current action */
    bool killed;/*!< True if agent has is to be removed via combat rule */
    bool availableNeighbours[4];/*!< Used for rules where we apply rule to each neighbour e.g. AgentMating*/
    std::pair<int, int> currentPosition,newPosition; /*!< Position of agent on lattice */
    int currentAge,newAge; /*!< Number of steps agent has existed for */
    int currentMetabolism,newMetabolism; /*!< Amount of sugar agent consumes each turn/step  */
    int currentSpiceMetabolism, newSpiceMetabolism; /*!< Amount of spice agent consumes each turn/step  */
    int currentSugar,newSugar; /*!< Sugar reserves held by agent */
    int currentSpice,newSpice; /*!< Sugar reserves held by agent */

    std::vector<bool> currentCulture,newCulture; /*!< bitstring representing Culture of agent */
    std::vector<bool> currentImmunity,newImmunity; /*!< bitstring holding disease bit sequences that agent has immunity from  */
    std::vector<Agent*> currentChildren,newChildren; /*!< Offspring of agent */
    Agent *father, *mother;
    std::vector<std::pair<Agent*,std::pair<int, int>>> currentLoansOwed,newLoansOwed; /*!< Loans that the agent owes */
    std::vector<std::pair<Agent*,std::pair<int, int>>> currentLoansOwing,newLoansOwing; /*!< Loans the agent has given to other agents - amounts owed to him */
    std::vector<std::vector<bool>> currentDiseases,newDiseases; /*!< Set of diseases (bitstrings) that agent suffers from */
    
public:
    //Constructors
    Agent(World *sim=nullptr,Agent *dad=nullptr, Agent *mum=nullptr, std::pair<int,int> pos=std::make_pair (-1,-1));
    
    //getters
    bool getAvail(int);
    int getAmountEaten(void);
    bool isDone(void);
    std::pair<int, int> getPosition(void);
    Sex getSex(void);
    int getVision(void);
    int getAge(void);
    int getMaxAge(void);
    int getMetabolism(void);
    int getSpiceMetabolism(void);
    int getSugar(void);
    int getSpice(void);
    int getWealth(void);
    int getReward(void);
    int getCultureLength(void);
    int getImmunityLength(void);
    unsigned long getChildrenCount();
    Agent* getFather();
    Agent* getMother();
    std::vector<bool> getCulture(void);
    std::vector<bool> getImmunity(void);
    std::vector<Agent*> getChildren(void);
    std::vector<std::pair<Agent*,std::pair<int, int>>> getLoansOwed(void);
    std::vector<std::pair<Agent*,std::pair<int, int>>> getLoansOwing(void);
    std::vector<std::vector<bool>> getDiseases(void);
    Location* getLocation(void);
    
    //setters
    bool markNeighbour(int);
    std::pair<int, int> setPosition(std::pair<int, int>);
    Sex setSex(Sex);
    int setVision(int);
    int incAge(void);
    int setAge(int);
    int setMaxAge(int);
    int setMetabolism(int);
    int setSpiceMetabolism(int);
    int incSugar(int);
    int setSugar(int);
    int incSpice(int);
    int setSpice(int);
    int setCultureLength(int);
    int setImmunityLength(int);
    int setImmunityTag(bool,int);
    std::vector<bool> setCulture(std::vector<bool>);
    std::vector<bool> setImmunity(std::vector<bool>);
    std::vector<Agent*> setChildren(std::vector<Agent*>);
    std::vector<std::pair<Agent*,std::pair<int, int>>> setLoansOwed(std::vector<std::pair<Agent*,std::pair<int, int>>>);
    std::vector<std::pair<Agent*,std::pair<int, int>>> setLoansOwing(std::vector<std::pair<Agent*,std::pair<int, int>>>);
    std::vector<std::vector<bool>> setDiseases(std::vector<std::vector<bool>>);

    //helpers
    Agent* initialise(World *sim=nullptr,Agent *dad=nullptr, Agent *mum=nullptr);
    Agent* reincarnate(std::pair<int,int> pos);
    bool markDone(void);
    bool markKilled(void);
    affiliation getTribe(void);
    bool isImmune(std::vector<bool>);
    bool isChild(Agent*);
    unsigned long  addChild(Agent*);
    unsigned long  removeChild(Agent*);
    int totalOwed(void);
    int totalOwing(void);
    int OwedToday(void);
    int OwingToday(void);
    bool hasDisease(std::vector<bool>);
    unsigned long addDisease(std::vector<bool>);
    unsigned long  diseaseCount(void);
    bool setTag(int,bool);
    bool isDead(void);
    bool isKilled(void);
    bool isFertile(void);
    int removeDeadLoans(void);
    int removePaidLoans(void);
    bool removeDeadMother(void);
    bool removeDeadFather(void);
    int removeKilledLoans(void);
    bool removeKilledMother(void);
    bool removeKilledFather(void);
    bool canLoan(void);
    bool wantsLoan(void);
    int loanOffered(void);
    int loanRequired(void);
    int addLoanOwed(Agent*,int);
    int addLoanOwing(Agent*,int);
    bool allDone(void);
    bool resetNeighbours(void);
    bool makeUnavailable(void);
    bool sync(void);
};
#endif /* defined(__SugarScape__Agent__) */
