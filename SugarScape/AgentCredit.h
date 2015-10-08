//
//  AgentCredit.h
//  SScapeGUI
//
//  Created by Joseph kehoe on 08/10/2015.
//  Copyright (c) 2015 Joseph Kehoe. All rights reserved.
//

#ifndef __SScapeGUI__AgentCredit__
#define __SScapeGUI__AgentCredit__

#include <iostream>
#include "IterativeWriteAction.h"

/*!  \class  AgentCredit
 \brief Credit Rule
 
 Credit

- An agent is a potential lender if it is too old to have children, in which case the maximum amount it may lend is one-half of its current wealth;
- An agent is a potential lender if it is of childbearing age and has wealth in excess of the amount necessary to have children, in which case the maximum amount it may lend is the excess wealth;
- An agent is a potential borrower if it is of childbearing age and has insufficient wealth to have a child and has income (resources gathered, minus metabolism, minus other loan obligations) in the present period making it credit-worthy for a loan written at terms specified by the lender;
- If a potential borrower and a potential lender are neighbors then a loan is originated with a duration of d years at the rate of r percent, and the face value of the loan is transferred from the lender to the borrower;
- At the time of the loan due date, if the borrower has sufficient wealth to repay the loan then a transfer from the borrower to the lender is made; else the borrower is required to pay back half of its wealth and a new loan is originated for the remaining sum;
-  If the borrower on an active loan dies before the due date then the lender simply takes a loss;
- If the lender on an active loan dies before the due date then the borrower is not required to pay back the loan, unless inheritance rule $I$ is active, in which case the lender's children now become the borrower's creditors.

 */
class AgentCredit:public IterativeWriteAction{
protected:
    bool suitable(Location*);
public:
    AgentCredit(World*);
    virtual bool executeAction(Location *, group *);
    virtual group* formGroup(Location *);
    virtual int participantCount(int,int,int);
};



#endif /* defined(__SScapeGUI__AgentCredit__) */
