#include "Htautau/EventSelectionObs_base.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "Htautau/EventSelection_leplep_default.h"
#include "Htautau/EventSelection_leplep_fake.h"
#include "Htautau/EventSelection_leplep_tight.h"
#include "Htautau/EventSelection_lfv_leplep_default.h"

templateClassImp(EventSelectionObs_base)
ClassImp (EventSelectionObs_leplep_default)
ClassImp (EventSelectionObs_leplep_fake)
ClassImp (EventSelectionObs_lfv_leplep_default)

// default
EventSelectionObs_leplep_default::EventSelectionObs_leplep_default(const TString &expression):TQTreeObservable(expression){
    EventSelectionObs = new EventSelectionObs_base < EventSelection_leplep_default >(expression);
    this->SetName(TQObservable::makeObservableName(expression));
    this->setExpression(expression);
}

EventSelectionObs_leplep_default::~EventSelectionObs_leplep_default(){
    delete EventSelectionObs;
}

double EventSelectionObs_leplep_default::getValue() const {
    return EventSelectionObs->getValue();
}

bool EventSelectionObs_leplep_default::hasExpression() const {
    return true;
}

const TString& EventSelectionObs_leplep_default::getExpression() const {
    return fExpression;
}

void EventSelectionObs_leplep_default::setExpression(const TString& expr) {
    this->fExpression = expr;
}

TObjArray* EventSelectionObs_leplep_default::getBranchNames() const {
    TObjArray* bnames = new TObjArray();
    bnames->SetOwner(false);
    return bnames;
}

bool EventSelectionObs_leplep_default::parseExpression(const TString& expr){
    (void) expr;
    return true;
}

void EventSelectionObs_leplep_default::clearParsedExpression(){
}

TString EventSelectionObs_leplep_default::getActiveExpression() const {
    return this->getExpression();
}

bool EventSelectionObs_leplep_default::initializeSelf() {
    if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
        return false;
    }
    return true;
}

bool EventSelectionObs_leplep_default::finalizeSelf () {
    this->clearParsedExpression();
    return true;
}


// fake:
EventSelectionObs_leplep_fake::EventSelectionObs_leplep_fake(const TString &expression):TQTreeObservable(expression){
  EventSelectionObs = new EventSelectionObs_base < EventSelection_leplep_fake >(expression);
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
}

EventSelectionObs_leplep_fake::~EventSelectionObs_leplep_fake(){
  delete EventSelectionObs;
}

double EventSelectionObs_leplep_fake::getValue() const {
  return EventSelectionObs->getValue();
}

bool EventSelectionObs_leplep_fake::hasExpression() const {
  return true;
}

const TString& EventSelectionObs_leplep_fake::getExpression() const {
  return fExpression;
}

void EventSelectionObs_leplep_fake::setExpression(const TString& expr) {
  this->fExpression = expr;
}
TObjArray* EventSelectionObs_leplep_fake::getBranchNames() const {
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);
  return bnames;
}

bool EventSelectionObs_leplep_fake::parseExpression(const TString& expr){
    (void) expr;
    return true;
}

void EventSelectionObs_leplep_fake::clearParsedExpression(){
}

TString EventSelectionObs_leplep_fake::getActiveExpression() const {
  return this->getExpression();
}

bool EventSelectionObs_leplep_fake::initializeSelf() {
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }
  return true;
}

bool EventSelectionObs_leplep_fake::finalizeSelf () {
  this->clearParsedExpression();
  return true;
}

//tight:
EventSelectionObs_leplep_tight::EventSelectionObs_leplep_tight(const TString &expression):TQTreeObservable(expression){
  EventSelectionObs = new EventSelectionObs_base < EventSelection_leplep_tight >(expression);
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
}

EventSelectionObs_leplep_tight::~EventSelectionObs_leplep_tight(){
  delete EventSelectionObs;
}

double EventSelectionObs_leplep_tight::getValue() const {
  return EventSelectionObs->getValue();
}

bool EventSelectionObs_leplep_tight::hasExpression() const {
  return true;
}

const TString& EventSelectionObs_leplep_tight::getExpression() const {
  return fExpression;
}

void EventSelectionObs_leplep_tight::setExpression(const TString& expr) {
  this->fExpression = expr;
}
TObjArray* EventSelectionObs_leplep_tight::getBranchNames() const {
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);
  return bnames;
}

bool EventSelectionObs_leplep_tight::parseExpression(const TString& expr){
    (void) expr;
    return true;
}

void EventSelectionObs_leplep_tight::clearParsedExpression(){
}

TString EventSelectionObs_leplep_tight::getActiveExpression() const {
  return this->getExpression();
}

bool EventSelectionObs_leplep_tight::initializeSelf() {
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }
  return true;
}

bool EventSelectionObs_leplep_tight::finalizeSelf () {
  this->clearParsedExpression();
  return true;
}

//lfv
EventSelectionObs_lfv_leplep_default::EventSelectionObs_lfv_leplep_default(const TString &expression):TQTreeObservable(expression){
  EventSelectionObs = new EventSelectionObs_base < EventSelection_lfv_leplep_default >(expression);
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
}

EventSelectionObs_lfv_leplep_default::~EventSelectionObs_lfv_leplep_default(){
  delete EventSelectionObs;
}

double EventSelectionObs_lfv_leplep_default::getValue() const {
  return EventSelectionObs->getValue();
}

bool EventSelectionObs_lfv_leplep_default::hasExpression() const {
  return true;
}

const TString& EventSelectionObs_lfv_leplep_default::getExpression() const {
  return fExpression;
}

void EventSelectionObs_lfv_leplep_default::setExpression(const TString& expr) {
  this->fExpression = expr;
}
TObjArray* EventSelectionObs_lfv_leplep_default::getBranchNames() const {
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);
  return bnames;
}

bool EventSelectionObs_lfv_leplep_default::parseExpression(const TString& expr){
    (void) expr;
    return true;
}

void EventSelectionObs_lfv_leplep_default::clearParsedExpression(){
}

TString EventSelectionObs_lfv_leplep_default::getActiveExpression() const {
  return this->getExpression();
}

bool EventSelectionObs_lfv_leplep_default::initializeSelf() {
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }
  return true;
}

bool EventSelectionObs_lfv_leplep_default::finalizeSelf () {
  this->clearParsedExpression();
  return true;
}

//______________________________________________________________________________________________

template < typename selection>
EventSelectionObs_base<selection>::EventSelectionObs_base(){
  // default constructor
}

//______________________________________________________________________________________________

template < typename selection>
EventSelectionObs_base<selection>::~EventSelectionObs_base<selection>(){
  // default destructor
  delete ovl;
}


//______________________________________________________________________________________________

template < typename selection>
double EventSelectionObs_base<selection>::getValue() const {
  // in the rest of this function, you should retrieve the data and calculate your return value
  // here is the place where most of your custom code should go
  // a couple of comments should guide you through the process
  // when writing your code, please keep in mind that this code can be executed several times on every event
  // make your code efficient. catch all possible problems. when in doubt, contact experts!

  // here, you should calculate your return value
  // of course, you can use other data members of your observable at any time
  /* example block for TTreeFormula method:
  const double retval = this->fFormula->Eval(0.);
  */
  /* exmple block for TTree::SetBranchAddress method:
  const double retval = this->fBranch1 + this->fBranch2;
  */

  double retval=-999;
  bool debug = false;


  if (jetIndexMode) {
      retval=ovl->getJetIdx(jetIndex);
  } else if (elIndexMode) {
      retval=ovl->getElIdx(elIndex);
      //std::cout << "elidx "<<elIndex << ": " <<retval << std::endl;
  } else if (muIndexMode) {
      retval=ovl->getMuIdx(muIndex);
      //std::cout << "muidx "<< muIndex << ":"<< retval << std::endl;
  } else if (tauIndexMode) {
      retval=ovl->getTauIdx(tauIndex);
  } else if (leptonIndexMode) {
      retval=ovl->getLeptonIdx(leptonIndex);
      //std::cout << "leptonidx "<< leptonIndex << ":"<< retval << std::endl;
  }

  if (jetNMode) retval         = ovl->getNJet();
  else if (elNMode) retval     = ovl->getNEl();
  else if (muNMode) retval     = ovl->getNMu();
  else if (tauNMode) retval    = ovl->getNTau();
  else if (leptonNMode) retval = ovl->getNLepton();

  if(leptonSelectMode){
    retval=0;
    int idx0 = ovl->getLeptonIdx(0);
    int idx1 = ovl->getLeptonIdx(1);
    if(idx0 >=0 && idx1>=0) retval=1;
  }
  if(leptonSelectMode_Lep0Tight){
    retval = ovl->getLepTight(0);
  }
  if(leptonSelectMode_Lep1Tight){
    retval = ovl->getLepTight(1);
  }
  else if(leptonPt0Mode){
    retval = ovl->getLepPt(0);
  }
  else if(leptonPt1Mode) retval = ovl->getLepPt(1);
  else if(leptonEta0Mode) retval = ovl->getLepEta(0);
  else if(leptonEta1Mode) retval = ovl->getLepEta(1);


  if(lep0MatchMode) retval = ovl->getLep0Match();
  else if (lep1MatchMode) retval = ovl->getLep1Match();


  if(lep0jetdRMode) retval = ovl->getDRminLepJet(0);
  else if (lep1jetdRMode) retval = ovl->getDRminLepJet(1);


  if (triggerWeightMode) retval = ovl->getTriggerWeight();
  else if (leptonWeightMode) retval = ovl->getScaleFactor();
  else if (isTriggeredMCMode) {
      retval = ovl->getTriggered_MC(); //std::cout << "retval=" << retval << std::endl;
  }
  else if (isTriggeredDataMode) {
      retval = ovl->getTriggered_data();
  }
  else if (isTriggerTypeMode)   retval = ovl->getTriggerType();

  if (SpecialtriggerWeightMode) retval = ovl->getSpecialTriggerWeight();
  else if (isSpecialTriggeredMCMode) {
    retval = ovl->getSpecialTriggered_MC();
  }
  else if (isSpecialTriggeredDataMode) {
    retval = ovl->getSpecialTriggered_data();
  }
  else if (isSpecialTriggerTypeMode)   retval = ovl->getSpecialTriggerType();

  if (leptonMVisMode) retval = ovl->getMvis();
  else if (leptonMtMode)    retval = ovl->getMt();
  else if (leptonMMCmaxwMode) retval = ovl->getMMC_maxw();
  else if (leptonMMCmlmMode) retval = ovl->getMMC_mlm();
  else if (leptonMMCmlnu3pMode) retval = ovl->getMMC_mlnu3p();
  else if (leptonSumPtMode) retval = ovl->getSumPtLep();
  else if (leptonDphiLLMode)retval = ovl->getDphiLL();
  else if (leptonDphiL0METMode) retval = ovl->getDphiL0MET();
  else if (leptonDphiL1METMode) retval = ovl->getDphiL1MET();
  else if (leptonDEtaLLMode) retval = ovl->getDEtaLL();
  else if (leptonMLLMode) retval = ovl->getMLL();
  else if (leptonMCollASymMode) retval = ovl->getMCollASym();
  else if (leptonSignMode) retval = ovl->getLepLepSign();
  else if (leptonXCollAppMode) retval = (ovl->getLepX0CollApp()>= 0.1 && ovl->getLepX0CollApp()<=1.0 && ovl->getLepX1CollApp()>=0.1 && ovl->getLepX1CollApp()<=0.8 );
  else if (leptonMCollMode) retval = (ovl->getLepMCollApp());
  else if (leptonX0CollMode) retval =ovl->getLepX0CollApp();
  else if (leptonX1CollMode) retval =ovl->getLepX1CollApp();

  if (PtLLMode) {
      retval=ovl->getPtLL();
      //std::cout << retval << std::endl;
  }
  if (PtTauTauMode){
      retval=ovl->getPtTauTau();
      //std::cout << retval << std::endl;
  }
  if (PtCollPtMode) {
      retval=ovl->getPtCollPt();
      //std::cout << retval << std::endl;
  }

  if(jetPt0Mode) retval = ovl->getJet0Pt();
  if(jetPt1Mode) retval = ovl->getJet1Pt();
  else if(jetJVTWeightMode) retval = ovl->getJVTWeight();
  else if(jetMVXWeightMode) retval = ovl->getMVXWeight();
  else if(jetBtagMode)      retval = ovl->getBtagged();


  if(metHptoMode) retval = ovl->getHPTO();

  if (hptoEtxMode) {
      retval=ovl->getHPTO_etx();
  }

  if (hptoEtyMode) {
      retval=ovl->getHPTO_ety();
  }
  if (hptoPhiMode) {
      retval=ovl->getHPTO_phi();
  }
  if (hptoX0Mode) {
      retval=ovl->getHPTO_x0();
  }
  if (hptoX1Mode) {
      retval=ovl->getHPTO_x1();
  }
  if (hptoCollmMode) {
      retval=ovl->gethpto_coll_m();
  }
  if (higgsPtMode) {
      retval=ovl->getHiggs_pt();
  }
  if (leptonCentralityMode) {
      retval=ovl->getLepton_centrality();
  }

  if (jetN25PtMode) {
      retval=ovl->getNJetPt25();
  }

  if (jetN2p4Eta25PtMode) {
      retval=ovl->getNJetEta2p4Pt25();
  }

  if (MtLep0mode) {
      retval=ovl->getMtLep0();
  }
  if (MtLep1mode) {
      retval=ovl->getMtLep1();
  }

  if (PtLep0METmode) {
      retval=ovl->getPtLep0MET();
  }

  if (PtLep1METmode) {
      retval=ovl->getPtLep1MET();
  }

  if (leptonDphiLep0METMode) retval = ovl->getDphiLep0MET();
  if (leptonDphiLep1METMode) retval = ovl->getDphiLep1MET();

  if (centralJetVetoMode) {
      retval=ovl->getCentral_jet_veto();
  }

  if (mJetJetMode) {
      retval=ovl->getJet_mjj();
  }

  if (DetaJetJetMode) {
      retval=ovl->getJet_deta();
  }

  if (VBFcatMode) {
      retval=ovl->getVBF_cat();
  }
  if (VBFcat_ZttCRMode) {
      retval=ovl->getVBF_cat_ZttCR();
  }
  if (boostedcatMode) {
      retval=ovl->getboosted_cat();
  }
  if (boostedcat_ZttCRMode) {
      retval=ovl->getboosted_cat_ZttCR();
  }

  if (d0l0Mode){
      retval=ovl->getd0l0();
  }
  if (d0l1Mode){
      retval=ovl->getd0l1();
  }
  if (d0sigl0Mode){
      retval=ovl->getd0sigl0();
  }
  if (d0sigl1Mode){
      retval=ovl->getd0sigl1();
  }

  if(runnumberMode){
    retval=ovl->getRunNumber();
  }


  if (debug ) {
      std::cout << "retval " ;
      //  std::cout << " " << TString(expression(expression.First("_")+1,2).String()).Atoi();
      //  std::cout << " " << TString(expression(expression.First("_")+1,2));
      //  std::cout << " " << expression.First("_")+1;
      std::cout << " " << jetIndexMode << " " << jetIndex;
      std::cout << " " << elIndexMode << " " << elIndex;
      std::cout << " " << muIndexMode << " " << muIndex;
      std::cout << " " << tauIndexMode << " " << tauIndex;
      std::cout << " " << leptonIndexMode << " " << leptonIndex;
      std::cout << " " << jetNMode << " " << elNMode << " " << muNMode << " " << tauNMode << " " << leptonNMode;
      std::cout << " " << triggerWeightMode << " " << leptonWeightMode << " " << isTriggeredMCMode << " " << isTriggeredDataMode  << std::endl;
  }

  return retval;
}
//______________________________________________________________________________________________

template <typename selection>
EventSelectionObs_base<selection>::EventSelectionObs_base(const TString& expression) {
  // constructor with expression argument
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable

  bool found=false;

  //gstd::cout << "In OBS code" << std::endl;

  if (expression.Contains("JetIdx_")){
      jetIndexMode=true;
      jetIndex=TString(expression(expression.First("_")+1,2)).Atoi();
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("ElIdx_")){
      elIndexMode=true;
      elIndex=TString(expression(expression.First("_")+1,2)).Atoi();
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("MuIdx_")){
      muIndexMode=true;
      muIndex=TString(expression(expression.First("_")+1,2)).Atoi();
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("TauIdx_")){
      tauIndexMode=true;
      tauIndex=TString(expression(expression.First("_")+1,2)).Atoi();
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("LeptonIdx_")){
      leptonIndexMode=true;
      leptonIndex=TString(expression(expression.First("_")+1,2)).Atoi();
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if(expression.Contains("SelectLep")){
      leptonSelectMode=true;
      if(expression.Contains("_Lep0Tight")){
          leptonSelectMode_Lep0Tight=true;
          if (found) std::cout << "WARNING observable already found "<< expression << std::endl; else found=true;
      }
      else if(expression.Contains("_Lep1Tight")){
          leptonSelectMode_Lep1Tight=true;
          if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
      }
      else {
          if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
      }
  } else if(expression.Contains("Lep0Pt")){
      leptonPt0Mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("Lep1Pt")){
      leptonPt1Mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("Lep0Eta")){
      leptonEta0Mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("Lep1Eta")){
      leptonEta1Mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if(expression.Contains("Lep0Match")){
      lep0MatchMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("Lep1Match")){
      lep1MatchMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if(expression.Contains("dRminLep0Jet")){
      lep0jetdRMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if(expression.Contains("dRminLep1Jet")){
      lep1jetdRMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if (expression.Contains("JetN")){
      jetNMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("ElN")){
      elNMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("MuN")){
      muNMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("TauN")){
      tauNMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("LeptonN")){
      leptonNMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if (expression.Contains("TriggerWeight")){
      triggerWeightMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("LeptonWeight")){
      leptonWeightMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("TriggeredMC")){
    isTriggeredMCMode=true; //std::cout << "isTriggeredMCmode " << std::endl;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("TriggeredData")){
      isTriggeredDataMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("TriggerType")){
      isTriggerTypeMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  //if (expression.Contains("specialTriggerWeight")){
  //  SpecialtriggerWeightMode=true;
  //  if (found) std::cout << "WARNING observable already found" << std::endl; else found=true;
  //} else if (expression.Contains("specialTriggeredMC")){
  //  isSpecialTriggeredMCMode=true;
  //  if (found) std::cout << "WARNING observable already found" << std::endl; else found=true;
  //} else if (expression.Contains("specialTriggeredData")){
  //  isSpecialTriggeredDataMode=true;
  //  if (found) std::cout << "WARNING observable already found" << std::endl; else found=true;
  //} else if (expression.Contains("specialTriggerType")){
  //  isSpecialTriggerTypeMode=true;
  //  if (found) std::cout << "WARNING observable already found" << std::endl; else found=true;
  //}

  if(expression.Contains("MVis")){
      leptonMVisMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if(expression.Contains("Mt_new")){
      leptonMtMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if(expression.Contains("MMC_maxw")){
      leptonMMCmaxwMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if(expression.Contains("MMC_mlm")){
      leptonMMCmlmMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("MMC_mlnu3p")){
      leptonMMCmlnu3pMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("SumPtLep")){
      leptonSumPtMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("DphiLL")){
      leptonDphiLLMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("DphiL0MET")){
      leptonDphiL0METMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("DphiL1MET")){
      leptonDphiL1METMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("DEtaLL")){
      leptonDEtaLLMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("MLL")){
      leptonMLLMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("MCollASym")){
      leptonMCollASymMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  else if(expression.Contains("LepLepSign")){
      leptonSignMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if(expression.Contains("LepXCollApp")){
      leptonXCollAppMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if(expression.Contains("LepMColl")){
      leptonMCollMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if(expression.Contains("LepX0Coll")){
      leptonX0CollMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if(expression.Contains("LepX1Coll")){
      leptonX1CollMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if (expression.Contains("PtLL")){
          PtLLMode=true;
          if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
          }
  if (expression.Contains("PtTauTau")){
          PtTauTauMode=true;
          if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
          }
  if (expression.Contains("PtCollPt")){
          PtCollPtMode=true;
          if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
          }

  if(expression.Contains("Jet0Pt")){
      jetPt0Mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }  if(expression.Contains("Jet1Pt")){
      jetPt1Mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if(expression.Contains("JVTWeight")){
      jetJVTWeightMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if(expression.Contains("MVXWeight")){
      jetMVXWeightMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if(expression.Contains("Btag")){
      jetBtagMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if(expression.Contains("MetHPTO_et")){
      metHptoMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("MetHPTO_ex")) {
      hptoEtxMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("MetHPTO_ey")) {
      hptoEtyMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("MetHPTO_phi")) {
      hptoPhiMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("MetHPTO_x0")) {
      hptoX0Mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("MetHPTO_x1")) {
      hptoX1Mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("MetHPTO_MColl")) {
      hptoCollmMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("HiggsPt")) {
      higgsPtMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if (expression.Contains("LeptonCentrality")) {
      leptonCentralityMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("CentralJetVeto")) {
      centralJetVetoMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("MJetJet")) {
      mJetJetMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("DEtaJetJet")) {
      DetaJetJetMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if (expression.Contains("Jet_NPt25")){
      jetN25PtMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("Jet_N2p4Eta25Pt")){
      jetN2p4Eta25PtMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("MtLep0")){
      MtLep0mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("MtLep1")){
      MtLep1mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("DphiLep0MET")){
      leptonDphiLep0METMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  } else if (expression.Contains("DphiLep1MET")){
      leptonDphiLep1METMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if (expression.Contains("PtLep0MET")) {
      PtLep0METmode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if (expression.Contains("PtLep1MET")) {
      PtLep1METmode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if (expression.Contains("d0Lep0")) {
      d0l0Mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("d0Lep1")) {
      d0l1Mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("d0SigLep0")) {
      d0sigl0Mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("d0SigLep1")) {
      d0sigl1Mode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if (expression.Contains("VBFcat")) {
      VBFcatMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("VBFZttCRcat")) {
      VBFcat_ZttCRMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("Boostedcat")) {
      boostedcatMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }
  if (expression.Contains("BoostedZttCRcat")) {
      boostedcat_ZttCRMode=true;
      if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if (expression.Contains("RunNumber")){
    runnumberMode=true;
    if (found) std::cout << "WARNING observable already found " << expression << std::endl; else found=true;
  }

  if (debug) {
      std::cout << "constructor " << expression.Data();
      //  std::cout << " " << TString(expression(expression.First("_")+1,2).String()).Atoi();
      //  std::cout << " " << TString(expression(expression.First("_")+1,2));
      //  std::cout << " " << expression.First("_")+1;
      std::cout << " " << jetIndexMode << " " << jetIndex;
      std::cout << " " << elIndexMode << " " << elIndex;
      std::cout << " " << muIndexMode << " " << muIndex;
      std::cout << " " << tauIndexMode << " " << tauIndex;
      std::cout << " " << leptonIndexMode << " " << leptonIndex;
      std::cout << " " << jetNMode << " " << elNMode << " " << muNMode << " " << tauNMode << " " << leptonNMode;
      std::cout << " " << triggerWeightMode << " " << leptonWeightMode << " " << isTriggeredMCMode << " " << isTriggeredDataMode  << std::endl;
  }
  if (!found) {
      std::cout << "WARNING! EventSelectionObs_base does not recognize " << expression << std::endl;
  }

  ovl = new selection();
  //ovl = new EventSelection_leplep_default();
}


//______________________________________________________________________________________________
