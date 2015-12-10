#ifndef __CAMERAGLOBALS
#define __CAMERAGLOBALS

#include <string>
#include "raspicam/src/raspicam_still.h"
#include "raspicam/src/raspicam.h"
#include "raspicam/src/raspicamtypes.h"

//------------------------------------------------------------------
// These are globals to be used in other files
// These are to pass information or to save universal information
std::string adminAddress; //the address of the admin station
raspicam::RaspiCam cam;   //the camera system that we take pictures with

#endif