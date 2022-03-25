#include "BSMtautauCAF/LPXKfactor.h"

#include "QFramework/TQLibrary.h"

#include "TObjString.h"
#include <limits>
#include <iostream>

ClassImp(LPXKfactor)



LPXKfactor::LPXKfactor() {
  this->setExpression(this->GetName());
  DEBUGclass("default constructor called");
}



LPXKfactor::~LPXKfactor() {
  DEBUGclass("destructor called");
}



LPXKfactor::LPXKfactor(const TString& expression): LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  // LPX Kfactor
  // --- ALPHAS
  Condition lpx_kfactor_ALPHAS_down = registerVariation("LPX_KFACTOR_ALPHAS_Corr_1down");
  Condition lpx_kfactor_ALPHAS_up = registerVariation("LPX_KFACTOR_ALPHAS_Corr_1up");
  Condition lpx_kfactor_sys = lpx_kfactor_ALPHAS_down | lpx_kfactor_ALPHAS_up;
  
  // --- PI
  Condition lpx_kfactor_PI_down = registerVariation("LPX_KFACTOR_PI_Corr_1down");
  lpx_kfactor_sys |= lpx_kfactor_PI_down;
  Condition lpx_kfactor_PI_up = registerVariation("LPX_KFACTOR_PI_Corr_1up");
  lpx_kfactor_sys |= lpx_kfactor_PI_up;
  
  // --- BEAM_ENERGY
  Condition lpx_kfactor_BEAM_ENERGY_down = registerVariation("LPX_KFACTOR_BEAM_ENERGY_Corr_1down");
  lpx_kfactor_sys |= lpx_kfactor_BEAM_ENERGY_down;
  Condition lpx_kfactor_BEAM_ENERGY_up = registerVariation("LPX_KFACTOR_BEAM_ENERGY_Corr_1up");
  lpx_kfactor_sys |= lpx_kfactor_BEAM_ENERGY_up;

  // --- PDF
  Condition lpx_kfactor_PDF_down = registerVariation("LPX_KFACTOR_PDF_Corr_1down");
  lpx_kfactor_sys |= lpx_kfactor_PDF_down;
  Condition lpx_kfactor_PDF_up = registerVariation("LPX_KFACTOR_PDF_Corr_1up");
  lpx_kfactor_sys |= lpx_kfactor_PDF_up;
  Condition lpx_kfactor_PDF_EW_down = registerVariation("LPX_KFACTOR_PDF_EW_Corr_1down");
  lpx_kfactor_sys |= lpx_kfactor_PDF_EW_down;
  Condition lpx_kfactor_PDF_EW_up = registerVariation("LPX_KFACTOR_PDF_EW_Corr_1up");
  lpx_kfactor_sys |= lpx_kfactor_PDF_EW_up;
  Condition lpx_kfactor_PDF_epWZ16_down = registerVariation("LPX_KFACTOR_PDF_epWZ16_Corr_1down");
  lpx_kfactor_sys |= lpx_kfactor_PDF_epWZ16_down;
  Condition lpx_kfactor_PDF_epWZ16_up = registerVariation("LPX_KFACTOR_PDF_epWZ16_Corr_1up");
  lpx_kfactor_sys |= lpx_kfactor_PDF_epWZ16_up;
  Condition lpx_kfactor_PDF_EV1 = registerVariation("LPX_KFACTOR_PDF_EV1_Corr");
  lpx_kfactor_sys |= lpx_kfactor_PDF_EV1;
  Condition lpx_kfactor_PDF_EV2 = registerVariation("LPX_KFACTOR_PDF_EV2_Corr");
  lpx_kfactor_sys |= lpx_kfactor_PDF_EV2;
  Condition lpx_kfactor_PDF_EV3 = registerVariation("LPX_KFACTOR_PDF_EV3_Corr");
  lpx_kfactor_sys |= lpx_kfactor_PDF_EV3;
  Condition lpx_kfactor_PDF_EV4 = registerVariation("LPX_KFACTOR_PDF_EV4_Corr");
  lpx_kfactor_sys |= lpx_kfactor_PDF_EV4;
  Condition lpx_kfactor_PDF_EV5 = registerVariation("LPX_KFACTOR_PDF_EV5_Corr");
  lpx_kfactor_sys |= lpx_kfactor_PDF_EV5;
  Condition lpx_kfactor_PDF_EV6 = registerVariation("LPX_KFACTOR_PDF_EV6_Corr");
  lpx_kfactor_sys |= lpx_kfactor_PDF_EV6;
  Condition lpx_kfactor_PDF_EV7 = registerVariation("LPX_KFACTOR_PDF_EV7_Corr");
  lpx_kfactor_sys |= lpx_kfactor_PDF_EV7;
  
  // --- SCALE
  Condition lpx_kfactor_SCALE_W_down = registerVariation("LPX_KFACTOR_SCALE_W_Corr_1down");
  lpx_kfactor_sys |= lpx_kfactor_SCALE_W_down;
  Condition lpx_kfactor_SCALE_W_up = registerVariation("LPX_KFACTOR_SCALE_W_Corr_1up");
  lpx_kfactor_sys |= lpx_kfactor_SCALE_W_up; 
  Condition lpx_kfactor_SCALE_Z_down = registerVariation("LPX_KFACTOR_SCALE_Z_Corr_1down");
  lpx_kfactor_sys |= lpx_kfactor_SCALE_Z_down;
  Condition lpx_kfactor_SCALE_Z_up = registerVariation("LPX_KFACTOR_SCALE_Z_Corr_1up");
  lpx_kfactor_sys |= lpx_kfactor_SCALE_Z_up;
  
  // --- CHOICE
  Condition lpx_kfactor_CHOICE_HERAPDF20 = registerVariation("LPX_KFACTOR_CHOICE_HERAPDF20_Corr");
  lpx_kfactor_sys |= lpx_kfactor_CHOICE_HERAPDF20;
  Condition lpx_kfactor_CHOICE_NNPDF30 = registerVariation("LPX_KFACTOR_CHOICE_NNPDF30_Corr");
  lpx_kfactor_sys |= lpx_kfactor_CHOICE_NNPDF30;
  Condition lpx_kfactor_CHOICE_epWZ16 = registerVariation("LPX_KFACTOR_CHOICE_epWZ16_Corr");
  lpx_kfactor_sys |= lpx_kfactor_CHOICE_epWZ16;
  Condition lpx_kfactor_REDCHOICE_NNPDF30 = registerVariation("LPX_KFACTOR_REDCHOICE_NNPDF30_Corr");
  lpx_kfactor_sys |= lpx_kfactor_REDCHOICE_NNPDF30;

  addScaleFactor(none, lpx_kfactor_sys, "NOMINAL_lpx_kfactor");
  
  addScaleFactor(lpx_kfactor_ALPHAS_down, "LPX_KFACTOR_ALPHAS_1down_lpx_kfactor");
  addScaleFactor(lpx_kfactor_ALPHAS_up, "LPX_KFACTOR_ALPHAS_1up_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PI_down, "LPX_KFACTOR_PI_1down_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PI_up, "LPX_KFACTOR_PI_1up_lpx_kfactor");
  addScaleFactor(lpx_kfactor_BEAM_ENERGY_down, "LPX_KFACTOR_BEAM_ENERGY_1down_lpx_kfactor");
  addScaleFactor(lpx_kfactor_BEAM_ENERGY_up, "LPX_KFACTOR_BEAM_ENERGY_1up_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_down, "LPX_KFACTOR_PDF_1down_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_up, "LPX_KFACTOR_PDF_1up_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_EW_down, "LPX_KFACTOR_PDF_EW_1down_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_EW_up, "LPX_KFACTOR_PDF_EW_1up_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_epWZ16_down, "LPX_KFACTOR_PDF_epWZ16_1down_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_epWZ16_up, "LPX_KFACTOR_PDF_epWZ16_1up_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_EV1, "LPX_KFACTOR_PDF_EV1_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_EV2, "LPX_KFACTOR_PDF_EV2_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_EV3, "LPX_KFACTOR_PDF_EV3_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_EV4, "LPX_KFACTOR_PDF_EV4_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_EV5, "LPX_KFACTOR_PDF_EV5_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_EV6, "LPX_KFACTOR_PDF_EV6_lpx_kfactor");
  addScaleFactor(lpx_kfactor_PDF_EV7, "LPX_KFACTOR_PDF_EV7_lpx_kfactor");
  addScaleFactor(lpx_kfactor_SCALE_W_down, "LPX_KFACTOR_SCALE_W_1down_lpx_kfactor");
  addScaleFactor(lpx_kfactor_SCALE_W_up, "LPX_KFACTOR_SCALE_W_1up_lpx_kfactor");
  addScaleFactor(lpx_kfactor_SCALE_Z_down, "LPX_KFACTOR_SCALE_Z_1down_lpx_kfactor");
  addScaleFactor(lpx_kfactor_SCALE_Z_up, "LPX_KFACTOR_SCALE_Z_1up_lpx_kfactor");
  addScaleFactor(lpx_kfactor_CHOICE_HERAPDF20, "LPX_KFACTOR_CHOICE_HERAPDF20_lpx_kfactor");
  addScaleFactor(lpx_kfactor_CHOICE_NNPDF30, "LPX_KFACTOR_CHOICE_NNPDF30_lpx_kfactor");
  addScaleFactor(lpx_kfactor_CHOICE_epWZ16, "LPX_KFACTOR_CHOICE_epWZ16_lpx_kfactor");
  addScaleFactor(lpx_kfactor_REDCHOICE_NNPDF30, "LPX_KFACTOR_REDCHOICE_NNPDF30_lpx_kfactor");

  DEBUGclass("There are %d SFs registered.", m_branches.size());
  m_staticConditionsMask |= nominal;
}



bool LPXKfactor::initializeSelf() {
  if (!LepHadObservable::initializeSelf()) {
    ERROR("Initialization of LepHadObservable failed.");
    return false;
  }

  int sum = 0; 
  fSysName = this->fSample->replaceInTextRecursive("$(variation)","~");
  for (unsigned int i = 0; i < m_variations.size(); ++i) {
    if (fSysName.EndsWith(m_variations[i].first)) {
      m_variation = m_variations[i].second;
      ++sum;
    }
  }
  if ( 0 == sum ) {
    m_variation = nominal; 
    ++sum;
  } 

  if (1 != sum) {
    ERROR("%s triggers %d variations !", fSysName, sum);
    throw std::runtime_error("Strange systematic:" + fSysName); 
  }

  for (unsigned int i = 0; i < m_branches.size(); ++i) {
    Condition requirement = std::get<0>(m_branches[i]);
    Condition veto = std::get<1>(m_branches[i]);
    TString name = std::get<2>(m_branches[i]);
    std::get<3>(m_branches[i]) = NULL;

    // remove those, which are already impossible due to variation
    if ( (requirement & m_staticConditionsMask & ~m_variation).any() ) { continue; }
    if ( (veto & m_variation).any() ) { continue; }

    std::get<3>(m_branches[i]) = new TTreeFormula(name, name, this->fTree);
  }

  return true;
}



bool LPXKfactor::finalizeSelf(){

  for (unsigned int i = 0; i < m_branches.size(); i++) {
    TTreeFormula* formula = std::get<3>(m_branches[i]);
    if (formula != NULL) {
      delete formula;
      formula = NULL;
    }
  }

  return true;
}



Condition LPXKfactor::registerVariation(TString name) {
  Condition variation;
  variation.set(m_nextBitPosition);
  m_staticConditionsMask.set(m_nextBitPosition);
  m_nextBitPosition++;

  std::pair<TString, Condition> pair(name, variation);
  m_variations.push_back(pair);

  return variation;
}



void LPXKfactor::addScaleFactor(Condition requirement, TString branch) {
  addScaleFactor(requirement, none, branch);
}



void LPXKfactor::addScaleFactor(Condition requirement, Condition veto, TString branch) {
  std::tuple<Condition, Condition, TString, TTreeFormula*> sf;

  std::get<0>(sf) = requirement;
  std::get<1>(sf) = veto;
  std::get<2>(sf) = branch;
  std::get<3>(sf) = NULL;

  m_branches.push_back(sf);
}



TObjArray* LPXKfactor::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  for (unsigned int i = 0; i < m_branches.size(); i++) {
    TString name = std::get<2>(m_branches[i]);
    bnames->Add(new TObjString(name.Data()));
  }

  return bnames;
}



double LPXKfactor::getValue() const {

  double kfactor = 1.;

  Condition status(m_variation);

  DEBUGclass("******************************************");
  // apply branches
  for (unsigned int i = 0; i < m_branches.size(); i++) {
    Condition requirement = std::get<0>(m_branches[i]);
    Condition veto = std::get<1>(m_branches[i]);
    
    // some requirements are not met
    if ((requirement & ~status).any()) { continue; }

    // some vetos are triggered
    if ((veto & status ).any()) { continue; }

    TString name = std::get<2>(m_branches[i]);
    TTreeFormula* formula = std::get<3>(m_branches[i]);
    DEBUGclass("%s: %f", name.Data(), formula->EvalInstance());

    kfactor *= formula->EvalInstance();
  }

  return kfactor;
}
