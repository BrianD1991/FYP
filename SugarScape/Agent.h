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


class Agent{
    
    //immutable
    World* theWorld;/*!< The Class containing everything in the simulation*/
    Sex sex; /*!< Agents are either male or female */
    int vision; /*!< The number of locations that an agent can see out to */
    int maxAge; /*!< Maximum lifespan of an agent */
    int cultureLength; /*!< Length of culture bitstring */
    int immunityLength; /*!< Length of immunity bitstring */
    
    //mutable
    int amountEaten;/*!< Store amount last eaten - required for Pollution Formation rule */
    bool done; /*!< True if agent has completed current action */
    std::pair<int, int> currentPosition,newPosition; /*!< Position or agent on lattice */
    int currentAge,newAge; /*!< Number of steps agent has existed for */
    int currentMetabolism,newMetabolism; /*!< Amount of suygar agent consumes each turn/step  */
    int currentSugar,newSugar; /*!< Sugar reserves held by agent */

    bool *currentCulture,*newCulture; /*!< bitstring represetnting Culture of agent */
    bool *currentImmunity,*newImmunity; /*!< bitstring holding disease bit sequences that agent has immunity from  */
    std::vector<Agent*> currentChildren,newChildren; /*!< Offspring of agent */
    std::vector<std::pair<Agent*,std::pair<int, int>>> currentLoansOwed,newLoansOwed; /*!< Loans that the agent owes */
    std::vector<std::pair<Agent*,std::pair<int, int>>> currentLoansOwing,newLoansOwing; /*!< Loans the agent has given to other agents - amounts owed to him */
    std::vector<bool*> currentDiseases,newDiseases; /*!< Set of diseases (bitstrings) that agent suffers from */
    
public:
    //Constructors
    Agent(World*sim);
    
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
    bool *getCulture(void);
    bool *getImmunity(void);
    std::vector<Agent*> getChildren(void);
    std::vector<std::pair<Agent*,std::pair<int, int>>> getLoansOwed(void);
    std::vector<std::pair<Agent*,std::pair<int, int>>> getLoansOwing(void);
    std::vector<bool*> getDiseases(void);
    
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
    bool *setCulture(bool*);
    bool *setImmunity(bool*);
    std::vector<Agent*> setChildren(std::vector<Agent*>);
    std::vector<std::pair<Agent*,std::pair<int, int>>> setLoansOwed(std::vector<std::pair<Agent*,std::pair<int, int>>>);
    std::vector<std::pair<Agent*,std::pair<int, int>>> setLoansOwing(std::vector<std::pair<Agent*,std::pair<int, int>>>);
    std::vector<bool*> setDiseases(std::vector<bool*>);

    //helpers
    bool markDone(void);
    affiliation getTribe(void);
    bool isImmune(bool*,int);
    bool isChild(Agent*);
    unsigned long  addChild(Agent*);
    unsigned long  removeChild(Agent*);
    int totalOwed(void);
    int totalOwing(void);
    int OwedToday(void);
    int OwingToday(void);
    bool hasDisease(bool*);
    unsigned long addDisease(bool*);
    bool sync(void);
};
#endif /* defined(__SugarScape__Agent__) */
