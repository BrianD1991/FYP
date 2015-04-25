//
//  main.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 25/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[])
{

    // insert code here...
    if (argc>1) {
        std::cout << "Hello " << argv[1]<<std::endl;
    }
    else
        std::cout << "Hello, World!\n";
    return 0;
}

