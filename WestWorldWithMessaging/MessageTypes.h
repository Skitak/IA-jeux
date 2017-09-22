#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_Fight,
  Msg_BobLeavingMine,
  Msg_SherifComing,
  Msg_Ambush,
  Msg_EndAmbush,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case Msg_Fight:

	  return "Fight";

  case Msg_BobLeavingMine:

	  return "LeavingMine";

  case Msg_SherifComing:

	  return "SherifHere";

  case Msg_Ambush:
	  
	  return"HoldUp";

  case Msg_EndAmbush:

	  return"WeDone";

  default:

    return "Not recognized!";
  }
}

#endif