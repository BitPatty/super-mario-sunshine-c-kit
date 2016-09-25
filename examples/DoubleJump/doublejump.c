#include "sms.h"

int doublejumped;
int preva;
int OnUpdate(MarDirector* director) {    
    int (*GameUpdate)(MarDirector* director) = GetObjectFunction(director, Director_GameUpdate);
    
    //Update
    MarioActor* mario = (MarioActor*)*gpMarioAddress;
	
	//Check if mario is in the air
    if (mario->status & STATE_AIRBORN)
    {
		//Check if mario has a double jump available and also if the user just pressed the A button this frame
        if (!doublejumped && ControllerOne->buttons & PRESS_A && !preva)
        {
            doublejumped = 1;
            **gpMarioSpeedY = 60.0f;
        }
    }
    else	//if mario isn't in the air give him another double jump to use.
        doublejumped = 0;

	//Save the current A press so it can be used to check if its pressed next frame (think of this as a 0.5 A press)
    preva = ControllerOne->buttons & PRESS_A;
    return GameUpdate(director);
}