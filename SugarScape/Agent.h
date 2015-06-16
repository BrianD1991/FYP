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


class World;


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
    std::pair<int, int> currentPosition,newPosition; /*!< Position or agent on lattice */
    int currentAge; /*!< Number of steps agent has existed for, newAge is simply currentAge+1 */
    int currentMetabolism,newMetabolism; /*!< Amount of suygar agent consumes each turn/step  */
    int currentSugar,newSugar; /*!< Sugar reserves held by agent */

    bool *currentCulture,*newCulture; /*!< bitstring representing Culture of agent */
    std::vector<bool> currentImmunity,newImmunity; /*!< bitstring holding disease bit sequences that agent has immunity from  */
    std::vector<Agent*> currentChildren,newChildren; /*!< Offspring of agent */
    Agent *father, *mother;
    std::vector<std::pair<Agent*,std::pair<int, int>>> currentLoansOwed,newLoansOwed; /*!< Loans that the agent owes */
    std::vector<std::pair<Agent*,std::pair<int, int>>> currentLoansOwing,newLoansOwing; /*!< Loans the agent has given to other agents - amounts owed to him */
    std::vector<std::vector<bool>> currentDiseases,newDiseases; /*!< Set of diseases (bitstrings) that agent suffers from */
    
public:
    //Constructors
    Agent(World *sim=nullptr,Agent *dad=nullptr, Agent *mum=nullptr);
    
    //getters
    int getAmountEaten(void);
    bool isDone(void);
    std::pair<int, int> getPosition(void);
    Sex getSex(void);
    int getVision(void);
    int getAge(void);
    int getMaxAge(void);
    int getMetabolism(void);
    int getSugar(void);
    int getCultureLength(void);
    int getImmunityLength(void);
    unsigned long getChildrenCount();
    Agent* getFather();
    Agent* getMother();
    bool *getCulture(void);
    std::vector<bool> getImmunity(void);
    std::vector<Agent*> getChildren(void);
    std::vector<std::pair<Agent*,std::pair<int, int>>> getLoansOwed(void);
    std::vector<std::pair<Agent*,std::pair<int, int>>> getLoansOwing(void);
    std::vector<std::vector<bool>> getDiseases(void);
    
    //setters
    std::pair<int, int> setPosition(std::pair<int, int>);
    Sex setSex(Sex);
    int setVision(int);
    int incAge(void);
    int setAge(int);
    int setMaxAge(int);
    int setMetabolism(int);
    int incSugar(int);
    int setSugar(int);
    int setCultureLength(int);
    int setImmunityLength(int);
    int setImmunityTag(bool,int);
    bool *setCulture(bool*);
    std::vector<bool> setImmunity(std::vector<bool>);
    std::vector<Agent*> setChildren(std::vector<Agent*>);
    std::vector<std::pair<Agent*,std::pair<int, int>>> setLoansOwed(std::vector<std::pair<Agent*,std::pair<int, int>>>);
    std::vector<std::pair<Agent*,std::pair<int, int>>> setLoansOwing(std::vector<std::pair<Agent*,std::pair<int, int>>>);
    std::vector<std::vector<bool>> setDiseases(std::vector<std::vector<bool>>);

    //helpers
    bool markDone(void);
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
    int removeDeadLoans(void);
    bool removeDeadMother(void);
    bool removeDeadFather(void);
    bool sync(void);
};
#endif /* defined(__SugarScape__Agent__) */
