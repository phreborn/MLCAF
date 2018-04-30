#include "CAFExample/HWWTrigConfig.h"

// constructor
HWWTrigConfig::HWWTrigConfig(TString periodName) :
  period_name(periodName),
  // trig_prefix("pass_"),
  m_useDilepTriggers(false)
{

}

// destructor 
HWWTrigConfig::~HWWTrigConfig() {

}


