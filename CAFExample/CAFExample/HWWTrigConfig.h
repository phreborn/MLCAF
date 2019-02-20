//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __HWWTRIGCONFIG__
#define __HWWTRIGCONFIG__

#include "TString.h"
#include <vector>

// #include "CAFxAODUtils/TQEventObservable.h"
// #include "xAODParticleEvent/CompositeParticleContainer.h"
// #include "xAODParticleEvent/ParticleContainer.h"

/*** This class holds some variables which are settings
     for HWW triggers, like trigger names and corresponding data periods.
     An object of this class can then be bassed to constructors
     of trigger-related observables, such that these settings can
     easily be shared among observables. 
     ***/

class HWWTrigConfig  {
public:
  unsigned int runNumberLow = 0;
  unsigned int runNumberUp = 0;

  std::vector<TString> trigSingleEl_Data;
  std::vector<TString> trigSingleMu_Data;
  std::vector<TString> trigDilep_Data;

  std::vector<TString> trigSingleEl_MC;
  std::vector<TString> trigSingleMu_MC;
  std::vector<TString> trigDilep_MC;

  TString period_name;
  // const TString trig_prefix;
  bool m_useDilepTriggers;

  double ptcut_singleel;
  double ptcut_singlemu;
  double ptcut_dilep_elleg;
  double ptcut_dilep_muleg;

public:
  // virtual double getValue() const override;
  // virtual bool initializeSelf() override;
  // TString m_candName = "";
public:
  HWWTrigConfig(TString periodName);
  HWWTrigConfig() {} // seems a default argument-less constructor is needed by ROOT?
  // HWWTrigConfig(const TString& name, const unsigned int which_lepton,
  //                         const unsigned int indexLeadLep = 0, const unsigned int indexSubleadLep = 1,
  //                          const unsigned int indexOtherLepton = 0);
  virtual ~HWWTrigConfig();
  // ClassDefOverride(HWWTrigConfig, 1);

  void setRunNumbers(unsigned int low, unsigned int up) { runNumberLow = low; runNumberUp = up; }

  // set trigger lists
  // data
  void setTriggersSingleEl_Data(std::vector<TString>& triggers, double ptcut = 0.) {
    for (auto& trigname : triggers) trigSingleEl_Data.push_back(trigname);
    ptcut_singleel = ptcut;
  }
  void setTriggersSingleMu_Data(std::vector<TString>& triggers, double ptcut = 0.) { 
    for (auto& trigname : triggers) trigSingleMu_Data.push_back(trigname);
    ptcut_singlemu = ptcut;
  } //trigSingleMu_Data = triggers; }
  void setTriggersDilep_Data(std::vector<TString>& triggers, double ptcut_ele = 0., double ptcut_mu = 0.)    { 
    for (auto& trigname : triggers) trigDilep_Data.push_back(trigname);
    m_useDilepTriggers = true;
    ptcut_dilep_elleg = ptcut_ele;
    ptcut_dilep_muleg = ptcut_mu;
  }
  
  // mc
  void setTriggersSingleEl_MC(std::vector<TString>& triggers, double ptcut = 0.) { 
    for (auto& trigname : triggers) trigSingleEl_MC.push_back(trigname);
    ptcut_singleel = ptcut;
  }
  void setTriggersSingleMu_MC(std::vector<TString>& triggers, double ptcut = 0.) { 
    for (auto& trigname : triggers) trigSingleMu_MC.push_back(trigname);
    ptcut_singlemu = ptcut;
  }//trigSingleMu_MC = triggers; }
  void setTriggersDilep_MC(std::vector<TString>& triggers, double ptcut_ele = 0., double ptcut_mu = 0.)    { 
    for (auto& trigname : triggers) trigDilep_MC.push_back(trigname);
    m_useDilepTriggers = true;
    ptcut_dilep_elleg = ptcut_ele;
    ptcut_dilep_muleg = ptcut_mu;
  }

  // set both MC and data (if MC and data triggers are the same)
  void setTriggersSingleEl(std::vector<TString>& triggers, double ptcut = 0.) { 
    for (auto& trigname : triggers) { trigSingleEl_Data.push_back(trigname); trigSingleEl_MC.push_back(trigname); }
    ptcut_singleel = ptcut;
  }
  void setTriggersSingleMu(std::vector<TString>& triggers, double ptcut = 0.) { 
    for (auto& trigname : triggers) { trigSingleMu_Data.push_back(trigname); trigSingleMu_MC.push_back(trigname); }
    ptcut_singlemu = ptcut;
  }
  void setTriggersDilep(std::vector<TString>& triggers, double ptcut_ele = 0., double ptcut_mu = 0.)    { 
    for (auto& trigname : triggers) { trigDilep_Data.push_back(trigname); trigDilep_MC.push_back(trigname); }
    m_useDilepTriggers = true;
    ptcut_dilep_elleg = ptcut_ele;
    ptcut_dilep_muleg = ptcut_mu;
  }

  // debug fcn
  // void dumpTriggers() const;


};
#endif
