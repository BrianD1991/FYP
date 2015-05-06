//
//  group.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "group.h"


int group::getScore(void){
    return score;
}
std::vector<Location*> group::getMembers(void){
    return members;
}
int group::getSize(void){
    return size;
}

bool group::push_back(Location* location){
    members.push_back(location);
    return true;
}

bool group::compare(group *first, group *second){
    return first->getScore()<second->getScore();
}