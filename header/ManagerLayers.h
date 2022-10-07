
#ifndef INCLUDE_GUARD_MANAGERLAYERS_H
#define INCLUDE_GUARD_MANAGERLAYERS_H



#include <iostream>

#include "GlobalSettings.h"


class ManagerLayers {

public:

    static ManagerLayers * Instance() {                                       // MAKING THIS CLASS AS "SINGLETON"
        if( s_pInstance == 0 ){                                                 // ONLY IF THERE IS ANY INSTANCE
            s_pInstance = new ManagerLayers();                                // CREATE THE NEW INSTANCE
        }
        return s_pInstance;                                                     // IF NOT, RETURN THAT INSTANCE
    }


	~ManagerLayers();



private:

    ManagerLayers();
    
    static ManagerLayers* s_pInstance;







};



typedef ManagerLayers Instance_ManagerLayers;



#endif