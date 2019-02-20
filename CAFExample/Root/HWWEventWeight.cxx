#include "CAFExample/HWWEventWeight.h"
#include "QFramework/TQUtils.h"

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

// EDM includes:
#include "xAODEventInfo/EventInfo.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthParticleContainer.h"

// Tool includes:
#include "PileupReweighting/PileupReweightingTool.h"
//#include "NNLOReweighter/NNLOReweighter.h"

ClassImp(HWWEventWeight)

//______________________________________________________________________________________________

HWWEventWeight::HWWEventWeight():
  m_doMCWeight(true),
  m_doPRW(false),
  m_usePRWTool(false),
  m_isMuonEvent(false),
  m_isDFEvent(false),
  m_isVHEvent(false),
  m_isDiLeptonTrigger(false),
  m_indexWeight(0),
  m_pdfWeightName("")
{
  // default constructor
  DEBUGclass("default constructor called");
  DEBUGclass("Default is to only use the MC generator weight, please enable other weights as needed.");

}

//______________________________________________________________________________________________

HWWEventWeight::~HWWEventWeight(){
  // default destructor
  DEBUGclass("destructor called");

  if(m_eleSFDecor) {
    delete m_eleSFDecor;
    m_eleSFDecor = 0;
  }
  if(m_muonSFDecor) {
    delete m_muonSFDecor;
    m_muonSFDecor = 0;
  }
  if(m_muonSFDecorLowPt) {
    delete m_muonSFDecorLowPt;
    m_muonSFDecorLowPt = 0;
  }
  if(m_eleIDSFDecor) {
    delete m_eleIDSFDecor;
    m_eleIDSFDecor = 0;
  }
  if(m_eleIDSFDecorLowPt) {
    delete m_eleIDSFDecorLowPt;
    m_eleIDSFDecorLowPt = 0;
  }
  if(m_eleIsoSFDecor) {
    delete m_eleIsoSFDecor;
    m_eleIsoSFDecor = 0;
  }
  if(m_eleIsoSFDecorLowPt) {
    delete m_eleIsoSFDecorLowPt;
    m_eleIsoSFDecorLowPt = 0;
  }
  if(m_muonIsoSFDecor) {
    delete m_muonIsoSFDecor;
    m_muonIsoSFDecor = 0;
  }
  if(m_muonTTVASFDecor) {
    delete m_muonTTVASFDecor;
    m_muonTTVASFDecor = 0;
  }
  if(m_eleTrigSFDecor) {
    delete m_eleTrigSFDecor;
    m_eleTrigSFDecor = 0;
  }
  if(m_eleTrigSFDecorLowPt) {
    delete m_eleTrigSFDecorLowPt;
    m_eleTrigSFDecorLowPt = 0;
  }
  if(m_muonTrigSFDecor) {
    delete m_muonTrigSFDecor;
    m_muonTrigSFDecor = 0;
  }
  if(m_muonTrigSFDecorLowPt) {
    delete m_muonTrigSFDecorLowPt;
    m_muonTrigSFDecorLowPt = 0;
  }
  if(m_btagSFDecor) {
    delete m_btagSFDecor;
    m_btagSFDecor = 0;
  }
  if(m_btagTrackJetSFDecor) {
    delete m_btagTrackJetSFDecor;
    m_btagTrackJetSFDecor = 0;
  }
  if(m_TrigMatchDecorELE1) {
    delete m_TrigMatchDecorELE1;
    m_TrigMatchDecorELE1 = 0;
  }
  if(m_TrigMatchDecorELE2) {
    delete m_TrigMatchDecorELE2;
    m_TrigMatchDecorELE2 = 0;
  }
  if(m_TrigMatchDecorELE3) {
    delete m_TrigMatchDecorELE3;
    m_TrigMatchDecorELE3 = 0;
  }
  if(m_TrigMatchDecorMUON1) {
    delete m_TrigMatchDecorMUON1;
    m_TrigMatchDecorMUON1 = 0;
  }
  if(m_TrigMatchDecorMUON2) {
    delete m_TrigMatchDecorMUON2;
    m_TrigMatchDecorMUON2 = 0;
  }
  if(m_jetJVTSFDecor) {
    delete m_jetJVTSFDecor;
    m_jetJVTSFDecor = 0;
  }
  if(m_jetForwardJVTSFDecor) {
    delete m_jetForwardJVTSFDecor;
    m_jetForwardJVTSFDecor = 0;
  }
  if(m_muonTrigEffDecor) {
    delete m_muonTrigEffDecor;
    m_muonTrigEffDecor = 0;
  }
  if(m_muonTrigEffDecorLowPt) {
    delete m_muonTrigEffDecorLowPt;
    m_muonTrigEffDecorLowPt = 0;
  }
  if(m_eleTrigEffDecor) {
    delete m_eleTrigEffDecor;
    m_eleTrigEffDecor = 0;
  }
  if(m_eleTrigEffDecorLowPt) {
    delete m_eleTrigEffDecorLowPt;
    m_eleTrigEffDecorLowPt = 0;
  }
  if(m_ttbarNNLOSFDecor) {
    delete m_ttbarNNLOSFDecor;
    m_ttbarNNLOSFDecor = 0;
  }

}

//______________________________________________________________________________________________

void HWWEventWeight::setMuonIsoScaleFactors(TH1* hist, TH1* syshist){
  DEBUGclass("call this function to the the muon isolation scale factors from a histogram (as opposed to using the ones in the PxAOD, which is the default");

  this->m_muonIsoSFHisto = TQHistogramUtils::copyHistogram(hist);
  this->m_muonIsoSFHistoSys = TQHistogramUtils::copyHistogram(syshist);
  this->m_muonIsoSFHisto->SetDirectory(NULL);
  this->m_muonIsoSFHistoSys->SetDirectory(NULL);
}

//______________________________________________________________________________________________

bool HWWEventWeight::initializeSelf(){
  DEBUGclass("Initializing HWWEventWeight for sample with path '%s'",fSample->getPath().Data());
  TString candName = "";
  if(!this->fSample->getTagString("~cand",candName)) return false;
  this->m_candName = "Event"+candName;

  // Check if this is a DF event
  m_isDFEvent = (this->m_candName.Contains("EventME") || this->m_candName.Contains("EventEM") || this->m_candName.Contains("TruthME") || this->m_candName.Contains("TruthEM"));
  // Check if this is a VH event
  m_isVHEvent = (this->m_candName.Contains("EventWH") || this->m_candName.Contains("EventZH"));
  // Check if we are in a lepton channel with at least one muon, for VH we only have one Event object anyway
  m_isMuonEvent = (this->m_candName.Contains("EventM") || m_isDFEvent || m_isVHEvent);
  // For VH, defer the actual check for whether or not event has a muon until getting the muon trig weight.
  // But it's required to set it to true for now.

  //weight index
  this->m_indexWeight = 0;
  int weightindex = 0;
  if(this->fSample->getTagInteger("~weightIndex",weightindex)) {
    DEBUGclass("Check sample path : '%s'",fSample->getPath().Data());
    this->m_indexWeight = weightindex;
  }

  //name of PDF weight
  TString pdfweightname = "";
  if(this->fSample->getTagString("~pdfWeightName",pdfweightname)) {
    this->m_pdfWeightName = pdfweightname;
  }

  this->fExpressionInternal = TString::Format("%s:%s",this->GetName(),this->m_candName.Data());
  DEBUGclass("expression is '%s'",this->fExpression.Data());
  this->fCachedEntry = -999;
  this->fCachedValue = 1.0;
  // if(m_doPRW)                  this->preparePRW();
  if(m_doPRW && m_usePRWTool)    this->preparePRW();
  if(m_useLepWeight)             this->prepareLepWeight();
  if(m_useElectronIDWeight)      this->prepareElectronIDWeight();
  if(m_useElectronIsoWeight)     this->prepareElectronIsoWeight();
  if(m_useElectronTrigWeight)    this->prepareElectronTrigWeight();
  if(m_useMuonIsoWeight)         this->prepareMuonIsoWeight();
  if(m_useMuonTTVAWeight)        this->prepareMuonTTVAWeight();
  if(m_useMuonTrigWeight)        this->prepareMuonTrigWeight();
  if(m_useBtagWeight)            this->prepareBtagWeight();
  if(m_useJVTWeight)             this->prepareJVTWeight();
  if(m_useForwardJVTWeight)      this->prepareForwardJVTWeight();
  if(m_useMuonTrigEffWeight)     this->prepareMuonTrigEffWeight();
  if(m_useElectronTrigEffWeight) this->prepareElectronTrigEffWeight();
  if(m_useTTbarNNLOWeight)       this->prepareTTbarNNLOWeight();
  return true;
}

void HWWEventWeight::preparePRW(){
  if (!m_wasInitialized) {
    DEBUGclass("Using PRW weights from the PRW tool...");
    m_wasInitialized = true;

    std::vector<std::string> confFilesMC15a;
    confFilesMC15a.push_back(m_confFileMC15a);
    std::vector<std::string> confFilesMC15b;
    confFilesMC15b.push_back(m_confFileMC15b);

    std::vector<std::string> lCalcFiles;
    lCalcFiles.push_back(m_lCalcFile);

    TString nameSuffix = "_Nominal";
    if( m_variationType == PU ) {
      nameSuffix = "_"+m_variationName;
    }
    // MC15a PRW
    if( m_prwTool_mc15a.empty() ) {
      TString prwNameMC15a = "PRWToolMC15a"+nameSuffix;
      if( asg::ToolStore::contains<CP::PileupReweightingTool>(prwNameMC15a.Data()) ) {
        m_prwTool_mc15a = dynamic_cast<CP::IPileupReweightingTool*>(asg::ToolStore::get(prwNameMC15a.Data()));
      }
      else {
        CP::IPileupReweightingTool* tool = new CP::PileupReweightingTool(prwNameMC15a.Data());
        //        asg::ToolStore::put(tool);
        INFOclass("created new tool '%s'",tool->name().c_str());
        m_prwTool_mc15a = tool;
        asg::setProperty(tool, "ConfigFiles", confFilesMC15a);
        asg::setProperty(tool, "LumiCalcFiles", lCalcFiles);
        // This is needed to use the default PRW config file used in the python config! Eventually will have full set of configs for each DSID respectively.
        DEBUGclass("Setting DataScaleFactor in PRW tool to %f", m_dataScaleFactor);
        asg::setProperty(tool, "DefaultChannel", 1);
        asg::setProperty(tool, "DataScaleFactor", m_dataScaleFactor);

        if( !m_prwTool_mc15a->initialize() ) throw std::runtime_error("Failed to initialise mc15a PRW tool");
      }
    }
    else {
      throw std::runtime_error("Encountered non-empty MC15a PRW tool handle. Most likely this was already set, otherwise something went horribly wrong...");
    }

    if( m_prwTool_mc15b.empty() ) {
      TString prwNameMC15b = "PRWToolMC15b"+nameSuffix;
      if( asg::ToolStore::contains<CP::PileupReweightingTool>(prwNameMC15b.Data()) ) {
        m_prwTool_mc15b = dynamic_cast<CP::IPileupReweightingTool*>(asg::ToolStore::get(prwNameMC15b.Data()));
      }
      else {
        CP::IPileupReweightingTool* tool = new CP::PileupReweightingTool(prwNameMC15b.Data());
        //        asg::ToolStore::put(tool);
        INFOclass("created new tool '%s'",tool->name().c_str());
        m_prwTool_mc15b = tool;
        asg::setProperty(tool, "ConfigFiles", confFilesMC15b);
        asg::setProperty(tool, "LumiCalcFiles", lCalcFiles);
        // This is needed to use the default PRW config file used in the python config! Eventually will have full set of configs for each DSID respectively.
        DEBUGclass("Setting DataScaleFactor in PRW tool to %f", m_dataScaleFactor);
        asg::setProperty(tool, "DefaultChannel", 2);
        asg::setProperty(tool, "DataScaleFactor", m_dataScaleFactor);

        if( !m_prwTool_mc15b->initialize() ) throw std::runtime_error("Failed to initialise mc15b PRW tool");
      }
    }
    else {
      throw std::runtime_error("Encountered non-empty MC15b PRW tool handle. Most likely this was already set, otherwise something went horribly wrong...");
    }

    if (m_prwTool_mc15a.empty()) {
      throw std::runtime_error("Failed to obtain MC15a PRW tool");
    }

    if (m_prwTool_mc15b.empty()) {
      throw std::runtime_error("Failed to obtain MC15b PRW tool");
    }
  }
}

//______________________________________________________________________________________________

void HWWEventWeight::setVariation(VariationType type, const TString& name){

  if ( m_eleSFDecor!=0 || m_eleIDSFDecor!=0 || m_eleIsoSFDecor!=0 || m_muonIsoSFDecor!=0 || m_eleTrigSFDecor!=0 || m_muonTrigSFDecor!=0 || m_btagSFDecor!=0 || m_btagTrackJetSFDecor!=0) {
    ERRORclass(" one of the decorators is different from 0!!. This means that you set the variation AFTER setting the nominal values for the SF .... and this is not supported .... please provide a fix .... exiting.");
    exit(-1);
  }

  this->m_variationType = type;
  this->m_variationName = name;
}

//______________________________________________________________________________________________

void HWWEventWeight::doPRWWeight(const std::string& confFileMC15a, const std::string& confFileMC15b, const std::string& lCalcFile, const double& dataScaleFactor){

  //we cannot create the PRW tool instance here, since it has no streamer and hence, we it cannot be passed on to clones of the observable (needed for MultiChannelVisitor). Hence, we simply save all required information and use it later.
  m_confFileMC15a = confFileMC15a;
  m_confFileMC15b = confFileMC15b;
  m_lCalcFile = lCalcFile;
  m_dataScaleFactor = dataScaleFactor;
  m_doPRW = true;
  m_usePRWTool = true;
}

//______________________________________________________________________________________________

void HWWEventWeight::doPRWWeight(std::string prwVarName){
    DEBUGclass("Using PRW weights from the input file, with variable name %s ...", prwVarName.c_str());
  m_doPRW = true;
  m_prwVarName = prwVarName;
}

//______________________________________________________________________________________________

void HWWEventWeight::doMCWeight(bool doMCWeight){
  DEBUGclass("Setting doMCWeight to %i", doMCWeight);
  m_doMCWeight = doMCWeight;
}

//______________________________________________________________________________________________

void HWWEventWeight::doMCWeightOnly(bool doMCWeightOnly){
  DEBUGclass("Setting doMCWeightOnly to %i", doMCWeightOnly);
  std::cout << "Setting doMCWeightOnly to " << doMCWeightOnly << std::endl;
  m_doMCWeightOnly = doMCWeightOnly;
}

//______________________________________________________________________________________________

void HWWEventWeight::doLepWeight(const std::string& eleSFName, const std::string& muonSFName, const std::string& muonSFNameLow){
  INFOclass("Using lepton efficiency weights with electron SF name %s and muon SF name %s and low pt muon SF name %s", eleSFName.c_str(), muonSFName.c_str(), muonSFNameLow.c_str());
  if(m_eleSFDecor || m_muonSFDecor || m_muonSFDecorLowPt) {
    throw std::runtime_error("Encountered non-zero lepton efficiency decorator pointers. Most likely this was already set before, or something went horribly wrong...");
  }
  m_eleSFName = eleSFName;
  m_muonSFName = muonSFName;
  m_muonSFNameLow = muonSFNameLow;
  m_useLepWeight = true;
}
void HWWEventWeight::prepareLepWeight(){
  if(!m_eleSFDecor){
    if (m_variationType == EleReco)  m_eleSFDecor= new SG::AuxElement::Accessor<float>(m_eleSFName+"___"+m_variationName.Data());
    else                             m_eleSFDecor= new SG::AuxElement::Accessor<float>(m_eleSFName);
  }

  if (m_variationType == MuonReco) {
    if(!m_muonSFDecor) m_muonSFDecor      = new SG::AuxElement::Accessor<float>(m_muonSFName+"___"+m_variationName.Data());
    if(!m_muonSFDecorLowPt) m_muonSFDecorLowPt = new SG::AuxElement::Accessor<float>(m_muonSFNameLow+"___"+m_variationName.Data());
  } else {
    if(!m_muonSFDecor) m_muonSFDecor     = new SG::AuxElement::Accessor<float>(m_muonSFName);
    if(!m_muonSFDecorLowPt) m_muonSFDecorLowPt= new SG::AuxElement::Accessor<float>(m_muonSFNameLow);
  }
}

//______________________________________________________________________________________________

void HWWEventWeight::doBtagWeight(const bool& useOtherJets, const std::string& btagSFName,
                                  BtagType type) {
  if(m_btagSFDecor) {
    throw std::runtime_error("Encountered non-zero b-tag efficiency decorator pointers. Most likely this was already set before, or something went horribly wrong...");
  }
  if (type == CaloJet) {
    m_useOtherJets = useOtherJets;
    m_bTagSFName = btagSFName;
    m_useBtagWeight = true;
    INFOclass("Using b-tagging efficiency weights for calo jets from %s", btagSFName.c_str());
  }
  else if (type == TrackJet) {
    m_useBtagTrackJetWeight = true;
    m_bTagTrackJetSFName = btagSFName;
    INFOclass("Using b-tagging efficiency weights for track jets from %s", btagSFName.c_str());
  }
  else {
    INFOclass("No type %s for b-tagging available!", TString::Format("%d",type).Data());
  }
}

void HWWEventWeight::prepareBtagWeight(){
  if(!m_btagSFDecor){
    if (m_variationType == Btag) m_btagSFDecor= new SG::AuxElement::Accessor<float>(m_bTagSFName+"___"+m_variationName.Data());
    else m_btagSFDecor= new SG::AuxElement::Accessor<float>(m_bTagSFName);
  }
  if(m_useBtagTrackJetWeight) {
    if(!m_btagTrackJetSFDecor){
      if (m_variationType == BtagTrackJet) m_btagTrackJetSFDecor = new SG::AuxElement::Accessor<float>(m_bTagTrackJetSFName+"___"+m_variationName.Data());
      else m_btagTrackJetSFDecor = new SG::AuxElement::Accessor<float>(m_bTagTrackJetSFName);
    }
  }
}


//______________________________________________________________________________________________

double HWWEventWeight::getBtagTrackJetWeight() const {

  xAOD::JetContainer const * jets = 0;
  if(!this->fEvent->retrieve(jets, "AntiKt4PV0TrackJets").isSuccess()){
    DEBUGclass("failed to retrieve candidates!");
    return 0;
  }
  float btagTrackJetWeight = 1.;
  // loop over the jets in the container
  xAOD::JetContainer::const_iterator jet_itr = jets->begin();
  xAOD::JetContainer::const_iterator jet_end = jets->end();
  for( ; jet_itr != jet_end; ++jet_itr ) {
    if ( (*jet_itr)->type() != xAOD::Type::Jet) continue;
    if (fabs((*jet_itr)->eta())<2.5 && (*jet_itr)->pt() > 7000.) {
      btagTrackJetWeight *= (*m_btagTrackJetSFDecor)(**jet_itr);
    }
    else {
      DEBUGclass("(Btag SF) Not a jet (or not in acceptance)");
    }
  } // end for loop over jets

  //DEBUGclass("Btag track jet (in)efficiency weight = %f", retval);

  return btagTrackJetWeight;
}

//______________________________________________________________________________________________

void HWWEventWeight::doElectronIDWeight(const std::string& eleIDSFName, const std::string& eleIDSFNameLow) {
  INFOclass("Using electron ID efficiency weights with SF name %s and for low pt %s",  eleIDSFName.c_str(), eleIDSFNameLow.c_str() );
  if(m_eleIDSFDecor || m_eleIDSFDecorLowPt ) {
    throw std::runtime_error("Encountered non-zero electron ID efficiency decorator pointers. Most likely this was already set before, or something went horribly wrong...");
  }
  m_eleIDSFName = eleIDSFName;
  m_eleIDSFNameLow = eleIDSFNameLow;
  m_useElectronIDWeight = true;
}
void HWWEventWeight::prepareElectronIDWeight(){
  if (m_variationType == EleID) {
    if(!m_eleIDSFDecor) m_eleIDSFDecor      = new SG::AuxElement::Accessor<float>(m_eleIDSFName+"___"+m_variationName.Data());
    if(!m_eleIDSFDecorLowPt) m_eleIDSFDecorLowPt = new SG::AuxElement::Accessor<float>(m_eleIDSFNameLow+"___"+m_variationName.Data());
  } else {
    if(!m_eleIDSFDecor) m_eleIDSFDecor     = new SG::AuxElement::Accessor<float>(m_eleIDSFName);
    if(!m_eleIDSFDecorLowPt) m_eleIDSFDecorLowPt= new SG::AuxElement::Accessor<float>(m_eleIDSFNameLow);
  }
}

//______________________________________________________________________________________________

void HWWEventWeight::doElectronIsoWeight(const std::string& eleIsoSFName, const std::string& eleIsoSFNameLow){
  INFOclass("Using electron isolation efficiency weights with SF name %s and for low pt %s", eleIsoSFName.c_str(), eleIsoSFNameLow.c_str() );
  if(m_eleIsoSFDecor || m_eleIsoSFDecorLowPt) {
    throw std::runtime_error("Encountered non-zero electron isolation efficiency decorator pointer. Most likely this was already set before, or something went horribly wrong...");
  }
  m_eleIsoSFName = eleIsoSFName;
  m_eleIsoSFNameLow = eleIsoSFNameLow;
  m_useElectronIsoWeight = true;
}
void HWWEventWeight::prepareElectronIsoWeight(){
  if (m_variationType == EleIso) {
    if(!m_eleIsoSFDecor) m_eleIsoSFDecor      = new SG::AuxElement::Accessor<float>(m_eleIsoSFName+"___"+m_variationName.Data());
    if(!m_eleIsoSFDecorLowPt) m_eleIsoSFDecorLowPt = new SG::AuxElement::Accessor<float>(m_eleIsoSFNameLow+"___"+m_variationName.Data());
  } else {
    if(!m_eleIsoSFDecor) m_eleIsoSFDecor      = new SG::AuxElement::Accessor<float>(m_eleIsoSFName);
    if(!m_eleIsoSFDecorLowPt) m_eleIsoSFDecorLowPt = new SG::AuxElement::Accessor<float>(m_eleIsoSFNameLow);
  }
}

//______________________________________________________________________________________________

void HWWEventWeight::doElectronTrigWeight(const std::string& eleTrigSFName, const std::string& eleTrigSFNameLow){
  INFOclass("Using electron trigger efficiency weights with SF name %s and for low pt %s", eleTrigSFName.c_str(), eleTrigSFNameLow.c_str());
  if(m_eleTrigSFDecor || m_eleTrigSFDecorLowPt) {
    throw std::runtime_error("Encountered non-zero electron trigger efficiency decorator pointer. Most likely this was already set before, or something went horribly wrong...");
  }
  m_eleTrigSFName = eleTrigSFName;
  m_eleTrigSFNameLow = eleTrigSFNameLow;
  m_useElectronTrigWeight = true;
}
void HWWEventWeight::prepareElectronTrigWeight(){
  const xAOD::EventInfo *evtInfo(0);
  if( !this->fEvent->retrieve(evtInfo, "EventInfo").isSuccess() ){
    ERRORclass("failed to retrieve event info!");
  }
  if (m_variationType == EleTrig) {
    if(!m_eleTrigSFDecor) m_eleTrigSFDecor = new SG::AuxElement::Accessor<float>(m_eleTrigSFName+"___"+m_variationName.Data());
    if(!m_eleTrigSFDecorLowPt) m_eleTrigSFDecorLowPt = new SG::AuxElement::Accessor<float>(m_eleTrigSFNameLow+"___"+m_variationName.Data());
  }
  else {
    if(!m_eleTrigSFDecor) m_eleTrigSFDecor = new SG::AuxElement::Accessor<float>(m_eleTrigSFName);
    if(!m_eleTrigSFDecorLowPt) m_eleTrigSFDecorLowPt = new SG::AuxElement::Accessor<float>(m_eleTrigSFNameLow);
  }
  if(!m_TrigMatchDecorELE1) m_TrigMatchDecorELE1 = new SG::AuxElement::Accessor<char>("trigMatch_HLT_e24_lhmedium_L1EM18VH");
  if(!m_TrigMatchDecorELE2) m_TrigMatchDecorELE2 = new SG::AuxElement::Accessor<char>("trigMatch_HLT_e60_lhmedium");
  if(!m_TrigMatchDecorELE3) m_TrigMatchDecorELE3 = new SG::AuxElement::Accessor<char>("trigMatch_HLT_e120_lhloose");
}

//______________________________________________________________________________________________

void HWWEventWeight::doMuonIsoWeight(const std::string& muonIsoSFName){
  INFOclass("Using muon isolation efficiency weights with SF name %s", muonIsoSFName.c_str());
  if(m_muonIsoSFDecor) {
    throw std::runtime_error("Encountered non-zero muon isolation efficiency decorator pointer. Most likely this was already set before, or something went horribly wrong...");
  }
  m_muonIsoSFName = muonIsoSFName;
  m_useMuonIsoWeight = true;
}
void HWWEventWeight::prepareMuonIsoWeight(){
  if(!m_muonIsoSFDecor){
    if (m_variationType == MuonIso)  m_muonIsoSFDecor = new SG::AuxElement::Accessor<float>(m_muonIsoSFName+"___"+m_variationName.Data());
    else                             m_muonIsoSFDecor = new SG::AuxElement::Accessor<float>(m_muonIsoSFName);
  }
}

//______________________________________________________________________________________________

void HWWEventWeight::doMuonTTVAWeight(const std::string& muonTTVASFName){
  INFOclass("Using muon TTVA efficiency weights with SF name %s", muonTTVASFName.c_str());
  if(m_muonTTVASFDecor) {
    throw std::runtime_error("Encountered non-zero muon TTVA efficiency decorator pointer. Most likely this was already set before, or something went horribly wrong...");
  }
  m_muonTTVASFName = muonTTVASFName;
  m_useMuonTTVAWeight = true;
}
void HWWEventWeight::prepareMuonTTVAWeight(){
  if(!m_muonTTVASFDecor){
    if (m_variationType == MuonTTVA) m_muonTTVASFDecor = new SG::AuxElement::Accessor<float>(m_muonTTVASFName+"___"+m_variationName.Data());
    else                             m_muonTTVASFDecor = new SG::AuxElement::Accessor<float>(m_muonTTVASFName);
  }
}

//______________________________________________________________________________________________

void HWWEventWeight::doTTbarNNLOWeight(const std::string& ttbarNNLOSFName){
  INFOclass("Using ttbar NNLO weights with SF name %s", ttbarNNLOSFName.c_str());
  if(m_ttbarNNLOSFDecor) {
    throw std::runtime_error("Encountered non-zero ttbar NNLO SF decorator pointer. Most likely this was already set before, or something went horribly wrong...");
  }
  m_ttbarNNLOSFName = ttbarNNLOSFName;
  m_useTTbarNNLOWeight = true;
}
void HWWEventWeight::prepareTTbarNNLOWeight(){
  if(!m_ttbarNNLOSFDecor){
    if (m_variationType == TTbarNNLO)  m_ttbarNNLOSFDecor = new SG::AuxElement::Accessor<float>(m_ttbarNNLOSFName+"___"+m_variationName.Data());
    else                             m_ttbarNNLOSFDecor = new SG::AuxElement::Accessor<float>(m_ttbarNNLOSFName);
  }

}

//______________________________________________________________________________________________

void HWWEventWeight::doMuonTrigWeight(const std::string& muonTrigSFName, const std::string& muonTrigSFNameLow){
  INFOclass("Using muon trigger efficiency weights with SF name %s and for low pt %s", muonTrigSFName.c_str(), muonTrigSFNameLow.c_str());
  if(m_muonTrigSFDecor || m_muonTrigSFDecorLowPt) {
    throw std::runtime_error("Encountered non-zero muon trigger efficiency decorator pointer. Most likely this was already set before, or something went horribly wrong...");
  }
  m_muonTrigSFName = muonTrigSFName;
  m_muonTrigSFNameLow = muonTrigSFNameLow;
  m_useMuonTrigWeight = true;
}
void HWWEventWeight::prepareMuonTrigWeight(){
  if (m_variationType == MuonTrig) {
    if(!m_muonTrigSFDecor) m_muonTrigSFDecor      = new SG::AuxElement::Accessor<float>(m_muonTrigSFName+"___"+m_variationName.Data());
    if(!m_muonTrigSFDecorLowPt) m_muonTrigSFDecorLowPt = new SG::AuxElement::Accessor<float>(m_muonTrigSFNameLow+"___"+m_variationName.Data());
  } else {
    if(!m_muonTrigSFDecor) m_muonTrigSFDecor     = new SG::AuxElement::Accessor<float>(m_muonTrigSFName);
    if(!m_muonTrigSFDecorLowPt) m_muonTrigSFDecorLowPt= new SG::AuxElement::Accessor<float>(m_muonTrigSFNameLow);
  }

  if(!m_TrigMatchDecorMUON1) m_TrigMatchDecorMUON1 = new SG::AuxElement::Accessor<char>("trigMatch_HLT_mu20_iloose_L1MU15");
  if(!m_TrigMatchDecorMUON2) m_TrigMatchDecorMUON2 = new SG::AuxElement::Accessor<char>("trigMatch_HLT_mu50");

}

//______________________________________________________________________________________________

void HWWEventWeight::doJVTWeight(const std::string& jetJVTSFName) {
  INFOclass("Using JVT efficiency weights with SF name %s", jetJVTSFName.c_str());
  if(m_jetJVTSFDecor) {
    throw std::runtime_error("Encountered non-zero JVT efficiency decorator pointer. Most likely this was already set before, or something went horribly wrong...");
  }
  m_jetJVTSFName = jetJVTSFName;
  m_useJVTWeight = true;
  // if (!jetForwardJVTSFName.empty()) {
  // 	m_jetForwardJVTSFName = jetForwardJVTSFName;
  // 	m_useForwardJVTWeight = true;
  // 	INFOclass("Using Forward JVT efficiency weights with SF name %s", jetForwardJVTSFName.c_str());
  // }
}

//______________________________________________________________________________________________

void HWWEventWeight::doForwardJVTWeight(const std::string& jetForwardJVTSFName) {
  INFOclass("Using JVT efficiency weights with SF name %s", jetForwardJVTSFName.c_str());
  if(m_jetForwardJVTSFDecor) {
    throw std::runtime_error("Encountered non-zero JVT efficiency decorator pointer. Most likely this was already set before, or something went horribly wrong...");
  }
  m_jetForwardJVTSFName = jetForwardJVTSFName;
  m_useForwardJVTWeight = true;
}

//______________________________________________________________________________________________

void HWWEventWeight::prepareJVTWeight() {
  if(m_variationType == JVT) {
    if(!m_jetJVTSFDecor) m_jetJVTSFDecor = new SG::AuxElement::Accessor<float>(m_jetJVTSFName+"___"+m_variationName.Data());
  }
  else {
    if(!m_jetJVTSFDecor) m_jetJVTSFDecor = new SG::AuxElement::Accessor<float>(m_jetJVTSFName);
  }
  // if (m_useForwardJVTWeight) {
  // 	if(m_variationType == JVT) {
  // 		if(!m_jetForwardJVTSFDecor) m_jetForwardJVTSFDecor = new SG::AuxElement::Accessor<float>(m_jetForwardJVTSFName+"___"+m_variationName.Data());
  // 	}
  // 	else {
  // 		if(!m_jetForwardJVTSFDecor) m_jetForwardJVTSFDecor = new SG::AuxElement::Accessor<float>(m_jetForwardJVTSFName);
  // 	}
  // }
}

//______________________________________________________________________________________________

void HWWEventWeight::prepareForwardJVTWeight(){
  if(m_variationType == FJVT) {
    if(!m_jetForwardJVTSFDecor) m_jetForwardJVTSFDecor = new SG::AuxElement::Accessor<float>(m_jetForwardJVTSFName+"___"+m_variationName.Data());
  }
  else {
    if(!m_jetForwardJVTSFDecor) m_jetForwardJVTSFDecor = new SG::AuxElement::Accessor<float>(m_jetForwardJVTSFName);
  }
}

//______________________________________________________________________________________________

void HWWEventWeight::doAllWeights(const std::string& confFileMC15a, const std::string& confFileMC15b, const std::string& lCalcFile, const double& dataScaleFactor){
  INFOclass("Using ALL event weights (with default SF names)!");
  doMCWeight(true);
  doMCWeightOnly(false);
  doPRWWeight(confFileMC15a, confFileMC15b, lCalcFile, dataScaleFactor);
  doLepWeight();
  doElectronIDWeight();
  doElectronIsoWeight();
  doElectronTrigWeight();
  doMuonIsoWeight();
  doMuonTTVAWeight();
  doMuonTrigWeight();
  doJVTWeight();
  doTTbarNNLOWeight();
  // This shouldn't be activated in general, if you have a branch in your cutflow, which is not using b-tagging you also shouldn't apply the respective weights at the very beginning
  // doBtagWeight();
}

//______________________________________________________________________________________________

void HWWEventWeight::doMuonTrigEffWeight(const std::string& muonTrigEffName, const std::string& muonTrigEffNameLow, const std::string& muonTrigSFName, const std::string& muonTrigSFNameLow,const std::string& muonTrigEffName_D4, const std::string& muonTrigEffNameLow_D4, const std::string& muonTrigSFName_D4, const std::string& muonTrigSFNameLow_D4){
  INFOclass("Using muon trigger weights evaluated from trigger efficiency");
  INFOclass("Muon trigger MC efficiency variable name: %s", muonTrigEffName.c_str());
  INFOclass("Muon trigger MC efficiency variable name for low pt: %s", muonTrigEffNameLow.c_str());
  INFOclass("Muon trigger SF variable name: %s", muonTrigSFName.c_str());
  INFOclass("Muon trigger SF variable name for low pt: %s", muonTrigSFNameLow.c_str());

  INFOclass("D4 Muon trigger MC efficiency variable name: %s", muonTrigEffName_D4.c_str());
  INFOclass("D4 Muon trigger MC efficiency variable name for low pt: %s", muonTrigEffNameLow_D4.c_str());
  INFOclass("D4 Muon trigger SF variable name: %s", muonTrigSFName_D4.c_str());
  INFOclass("D4 Muon trigger SF variable name for low pt: %s", muonTrigSFNameLow_D4.c_str());

  m_muonTrigEffName = muonTrigEffName;
  m_muonTrigEffNameLow = muonTrigEffNameLow;
  m_muonTrigSFName = muonTrigSFName;
  m_muonTrigSFNameLow = muonTrigSFNameLow;
  m_muonTrigEffName_D4 = muonTrigEffName_D4;
  m_muonTrigEffNameLow_D4 = muonTrigEffNameLow_D4;
  m_muonTrigSFName_D4 = muonTrigSFName_D4;
  m_muonTrigSFNameLow_D4 = muonTrigSFNameLow_D4;


  m_useMuonTrigEffWeight = true;
}
void HWWEventWeight::prepareMuonTrigEffWeight(){
  /*
    if (m_variationType == MuonTrig) {
      //     if(!m_muonTrigEffDecor) m_muonTrigEffDecor = new SG::AuxElement::Accessor<float>(m_muonTrigEffName+"___"+m_variationName.Data());
      //     if(!m_muonTrigEffDecorLowPt) m_muonTrigEffDecorLowPt = new SG::AuxElement::Accessor<float>(m_muonTrigEffNameLow+"___"+m_variationName.Data());
      if(!m_muonTrigSFDecor) m_muonTrigSFDecor = new SG::AuxElement::Accessor<float>(m_muonTrigSFName+"___"+m_variationName.Data());
      if(!m_muonTrigSFDecorLowPt) m_muonTrigSFDecorLowPt = new SG::AuxElement::Accessor<float>(m_muonTrigSFNameLow+"___"+m_variationName.Data());
    }
    else {
      //     if(!m_muonTrigEffDecor) m_muonTrigEffDecor = new SG::AuxElement::Accessor<float>(m_muonTrigEffName);
      //     if(!m_muonTrigEffDecorLowPt) m_muonTrigEffDecorLowPt = new SG::AuxElement::Accessor<float>(m_muonTrigEffNameLow);
      if(!m_muonTrigSFDecor) m_muonTrigSFDecor = new SG::AuxElement::Accessor<float>(m_muonTrigSFName);
      if(!m_muonTrigSFDecorLowPt) m_muonTrigSFDecorLowPt = new SG::AuxElement::Accessor<float>(m_muonTrigSFNameLow);
    }
    if(!m_muonTrigEffDecor) m_muonTrigEffDecor = new SG::AuxElement::Accessor<float>(m_muonTrigEffName);
    if(!m_muonTrigEffDecorLowPt) m_muonTrigEffDecorLowPt = new SG::AuxElement::Accessor<float>(m_muonTrigEffNameLow);

  */
}

//______________________________________________________________________________________________

//void HWWEventWeight::doElectronTrigEffWeight(const std::string& eleTrigEffName, const std::string& eleTrigEffNameLow, const std::string& eleTrigSFName, const std::string& eleTrigSFNameLow){
  void HWWEventWeight::doElectronTrigEffWeight(const std::string& eleTrigEffName, const std::string& eleTrigEffNameLow, const std::string& eleTrigSFName, const std::string& eleTrigSFNameLow, const std::string& eleTrigEffName_D4, const std::string& eleTrigEffNameLow_D4, const std::string& eleTrigSFName_D4, const std::string& eleTrigSFNameLow_D4){
  INFOclass("Using electron trigger weights evaluated from trigger efficiency");
  INFOclass("Electron trigger MC efficiency variable name: %s", eleTrigEffName.c_str());
  INFOclass("Electron trigger MC efficiency variable name for low pt: %s", eleTrigEffNameLow.c_str());
  INFOclass("Electron trigger SF variable name: %s", eleTrigSFName.c_str());
  INFOclass("Electron trigger SF variable name for low pt: %s", eleTrigSFNameLow.c_str());

  INFOclass("D4 Electron trigger MC efficiency variable name: %s", eleTrigEffName_D4.c_str());
  INFOclass("D4 Electron trigger MC efficiency variable name for low pt: %s", eleTrigEffNameLow_D4.c_str());
  INFOclass("D4 Electron trigger SF variable name: %s", eleTrigSFName_D4.c_str());
  INFOclass("D4 Electron trigger SF variable name for low pt: %s", eleTrigSFNameLow_D4.c_str());

  m_eleTrigEffName = eleTrigEffName;
  m_eleTrigEffNameLow = eleTrigEffNameLow;
  m_eleTrigSFName = eleTrigSFName;
  m_eleTrigSFNameLow = eleTrigSFNameLow;
  m_eleTrigEffName_D4 = eleTrigEffName_D4;
  m_eleTrigEffNameLow_D4 = eleTrigEffNameLow_D4;
  m_eleTrigSFName_D4 = eleTrigSFName_D4;
  m_eleTrigSFNameLow_D4 = eleTrigSFNameLow_D4;
  m_useElectronTrigEffWeight = true;
}
void HWWEventWeight::prepareElectronTrigEffWeight(){
  /*
    if (m_variationType == EleTrig) {
      //     if(!m_eleTrigEffDecor) m_eleTrigEffDecor = new SG::AuxElement::Accessor<float>(m_eleTrigEffName+"___"+m_variationName.Data());
      //     if(!m_eleTrigEffDecorLowPt) m_eleTrigEffDecorLowPt = new SG::AuxElement::Accessor<float>(m_eleTrigEffNameLow+"___"+m_variationName.Data());
      if(!m_eleTrigSFDecor) m_eleTrigSFDecor = new SG::AuxElement::Accessor<float>(m_eleTrigSFName+"___"+m_variationName.Data());
      if(!m_eleTrigSFDecorLowPt) m_eleTrigSFDecorLowPt = new SG::AuxElement::Accessor<float>(m_eleTrigSFNameLow+"___"+m_variationName.Data());
    }
    else{
      //     if(!m_eleTrigEffDecor) m_eleTrigEffDecor = new SG::AuxElement::Accessor<float>(m_eleTrigEffName);
      //     if(!m_eleTrigEffDecorLowPt) m_eleTrigEffDecorLowPt = new SG::AuxElement::Accessor<float>(m_eleTrigEffNameLow);
      if(!m_eleTrigSFDecor) m_eleTrigSFDecor = new SG::AuxElement::Accessor<float>(m_eleTrigSFName);
      if(!m_eleTrigSFDecorLowPt) m_eleTrigSFDecorLowPt = new SG::AuxElement::Accessor<float>(m_eleTrigSFNameLow);
    }
    if(!m_eleTrigEffDecor) m_eleTrigEffDecor = new SG::AuxElement::Accessor<float>(m_eleTrigEffName);
    if(!m_eleTrigEffDecorLowPt) m_eleTrigEffDecorLowPt = new SG::AuxElement::Accessor<float>(m_eleTrigEffNameLow);
  */
}

//______________________________________________________________________________________________

double HWWEventWeight::getLeptonWeight(const xAOD::IParticle* p) const {
  DEBUGclass("retrieving lepton weight for particle %p",p);
  double retval = 1.;
  if( p->type() == xAOD::Type::Electron ) {
    retval = (*m_eleSFDecor)(*p);
  }
  else if( p->type() == xAOD::Type::Muon ) {
//     retval = (*m_muonSFDecor)(*p);
    if( p->pt() > 25e3 ) retval = (*m_muonSFDecor)(*p);
    else retval = (*m_muonSFDecorLowPt)(*p);
  }
  DEBUGclass("Lepton weight = %f", retval);
  return retval;
}

//______________________________________________________________________________________________

double HWWEventWeight::getElectronIDWeight(const xAOD::IParticle* p) const {
  DEBUGclass("retrieving electron ID weight for particle %p",p);
  double retval = 1.;
  if( p->type() == xAOD::Type::Electron ){
    if ( p->pt()>25e3 ) retval = (*m_eleIDSFDecor)(*p);
    else                retval = (*m_eleIDSFDecorLowPt)(*p);
    DEBUGclass("Electron ID weight = %f", retval);
  }
  else {
    DEBUGclass("(Electron ID) Not an electron, will return %f", retval);
  }
  return retval;
}

//______________________________________________________________________________________________

double HWWEventWeight::getElectronIsoWeight(const xAOD::IParticle* p) const {
  DEBUGclass("retrieving electron isolation weight for particle %p",p);
  double retval = 1.;
  if( p->type() == xAOD::Type::Electron ){
    if ( p->pt()>25e3 ) retval = (*m_eleIsoSFDecor)(*p);
    else                retval = (*m_eleIsoSFDecorLowPt)(*p);
    DEBUGclass("Electron isolation weight = %f", retval);
  }
  else {
    DEBUGclass("(Electron isolation) Not an electron, will return %f", retval);
  }
  return retval;
}

//______________________________________________________________________________________________

double HWWEventWeight::getBtagWeight(const xAOD::IParticle* p) const {
  DEBUGclass("retrieving btag weight for particle %p",p);
  double retval = 1.;
  if( p->type() == xAOD::Type::Jet && fabs(p->eta())<2.5 ) {
    retval = (*m_btagSFDecor)(*p);
    DEBUGclass("Btag (in)efficiency weight = %f", retval);
  }
  else {
    DEBUGclass("(Btag SF) Not a jet (or not in acceptance), will return %f", retval);
  }
  return retval;
}

//______________________________________________________________________________________________

double HWWEventWeight::getElectronTrigWeight(const xAOD::IParticle* p) const {
  DEBUGclass("retrieving electron trigger weight for particle %p",p);
  double retval = 1.;
  if( p->type() == xAOD::Type::Electron ){
    double eleTrigSF = 1.0;
    if( p->pt() > 25e3 ) eleTrigSF = (*m_eleTrigSFDecor)(*p);
    else eleTrigSF = (*m_eleTrigSFDecorLowPt)(*p);
    // Some entries return nan, which probably only happens when the respective trigger selection was not done before applying the SFs, still not very clean...
    if( !TQUtils::isNum(eleTrigSF) ) {
      ERRORclass("Encountered non-numeric electron trigger weight, will return 1.0 instead");
    }
    else {
      retval = eleTrigSF;
    }
    DEBUGclass("Electron trigger weight = %f", retval);
  }
  else {
    DEBUGclass("(Electron trigger) Not an electron, will return %f", retval);
  }

  if( !(retval > 0.) ) {
    DEBUGclass("Got electron trigger SF of 0, will return 1 instead");
    return 1.0;
  }

  return retval;
}

//______________________________________________________________________________________________

double HWWEventWeight::getMuonIsoWeight(const xAOD::IParticle* p) const {
  DEBUGclass("retrieving muon isolation weight for particle %p",p);
  double retval = 1.;
  if( p->type() == xAOD::Type::Muon ){
    if(this->m_muonIsoSFHisto){ // this is a hacky implementation to allow overriding the PxAOD-based muon SFs with ones provided in the histograms
      DEBUGclass("this is a hacky implementation to allow overriding the PxAOD-based muon SFs");
      const int bin = m_muonIsoSFHisto->FindBin(p->pt()/1000.);
      if(m_variationType == MuonIso){
	//	std::cout<<"  m_variationName[0] "<< m_variationName[0]<<std::endl;
	//        double direction = ( m_variationName[0] == 'u' ? 1. : -1.); // efficiently distinguish between "Up" and "Down"
	double direction = (	m_variationName.Contains("up")  ? 1. : -1.);
	if (m_variationName.Contains("STAT"))
	  retval = ( m_muonIsoSFHisto->GetBinContent(bin) + direction * m_muonIsoSFHisto->GetBinError(bin) ) ; // absolute
	else if (m_variationName.Contains("SYS"))
	//        retval = ( 1. + direction * m_muonIsoSFHistoSys->GetBinContent(bin) ) * m_muonIsoSFHisto->GetBinContent(bin); //Relative
	  retval = ( m_muonIsoSFHisto->GetBinContent(bin) + direction * m_muonIsoSFHistoSys->GetBinContent(bin) ) ; // absolute
      } else {
        retval = m_muonIsoSFHisto->GetBinContent(bin);
      }
    } else {
      retval = (*m_muonIsoSFDecor)(*p);
    }
    DEBUGclass("Muon isolation weight = %f", retval);
  }
  else {
    DEBUGclass("(Muon isolation) Not a muon, will return %f", retval);
  }
  return retval;
}

//______________________________________________________________________________________________

double HWWEventWeight::getMuonTTVAWeight(const xAOD::IParticle* p) const {
  DEBUGclass("retrieving muon TTVA weight for particle %p",p);
  double retval = 1.;
  if( p->type() == xAOD::Type::Muon ){
    retval = (*m_muonTTVASFDecor)(*p);
    DEBUGclass("Muon TTVA weight = %f", retval);
  }
  else {
    DEBUGclass("(Muon TTVA) Not a muon, will return %f", retval);
  }
  return retval;
}

//______________________________________________________________________________________________

double HWWEventWeight::getMuonTrigWeight(const xAOD::CompositeParticle* p) const {
  DEBUGclass("retrieving muon trigger weight for particle %p",p);
  double retval = 1.;
  if( m_isMuonEvent ){
    double muPt = 0.;
    // This is a workaround since m_isMuonEvent doesn't cover VH containers
    bool eventHasMuonVH = false;
    for( unsigned int i=0; i<p->nLeptons(); ++i ) {
      if( p->part(i)->type() != xAOD::Type::Muon ) continue;
      eventHasMuonVH = true;
      muPt = p->part(i)->pt();
    }
    if (!eventHasMuonVH) return 1.;
    if( !(muPt > 0.) ) ERRORclass("(Muon trigger) No muon in event object found (please check)...");
    if( muPt > 25e3 ) retval = (*m_muonTrigSFDecor)(*p);
    else retval = (*m_muonTrigSFDecorLowPt)(*p);
//     retval = (*m_muonTrigSFDecor)(*p);
    DEBUGclass("Muon trigger weight = %f for muon pt = %f", retval, muPt);
  }
  else {
    DEBUGclass("(Muon trigger) Not an event with a muon, will return %f", retval);
  }
  return retval;
}

//______________________________________________________________________________________________

double HWWEventWeight::getJVTWeight(const xAOD::IParticle* p) const {
  DEBUGclass("retrieving JVT weight for particle %p",p);
  double retval = 1.;
  if( p->type() == xAOD::Type::Jet ){
    retval = (*m_jetJVTSFDecor)(*p);
    DEBUGclass("JVT weight = %f", retval);
  }
  else {
    DEBUGclass("(JVT) Not a jet, will return %f", retval);
  }
  return retval;
}

//______________________________________________________________________________________________

double HWWEventWeight::getTriggerSF_DF_singLep(const xAOD::CompositeParticle* compPart) const {
  double retVal=1;
  unsigned int nLeptons = compPart->nLeptons();
  float muonSF= this->getMuonTrigWeight(compPart);
  float eleSF = 1;
  bool muonMatch=false;
  bool eleMatch =false;
  for( unsigned int i=0; i<nLeptons; ++i ) {
    if ( compPart->part(i)->type() == xAOD::Type::Electron ) {
      eleSF*= this->getElectronTrigWeight(compPart->part(i));
      int tmpVal1=(*m_TrigMatchDecorELE1)(*(compPart->part(i)));
      int tmpVal2=(*m_TrigMatchDecorELE2)(*(compPart->part(i)));
      int tmpVal3=(*m_TrigMatchDecorELE3)(*(compPart->part(i)));
      double elePt = compPart->part(i)->pt();
      DEBUGclass( " ele with pt: %f  with Match1: %i , Match2: %i, Match3: %i ", compPart->part(i)->pt(), tmpVal1, tmpVal2, tmpVal3 );
      eleMatch= ( ((tmpVal1+tmpVal2+tmpVal3)>0) && (elePt > 25000.) );
    } else if (  compPart->part(i)->type() == xAOD::Type::Muon ) {
      int tmpVal1=(*m_TrigMatchDecorMUON1)(*(compPart->part(i)));
      int tmpVal2=(*m_TrigMatchDecorMUON2)(*(compPart->part(i)));
      double muPt = compPart->part(i)->pt();
      DEBUGclass( " muon with pt: %f  with Match1: %i , Match2: %i ", compPart->part(i)->pt(), tmpVal1, tmpVal2 );
      muonMatch= ( ((tmpVal1+tmpVal2)>0) && (muPt > 21000.) );
    }
  }
  if ( muonMatch && !eleMatch )     retVal=muonSF;
  else if (!muonMatch && eleMatch ) retVal=eleSF;
  else if (muonMatch && eleMatch  ) retVal=eleSF+muonSF-eleSF*muonSF;
  DEBUGclass( " for this event: muSF= %f, eleSF= %f, matchMu= %i, matchEle= %i, TRIGGERsf= %f", muonSF, eleSF, muonMatch, eleMatch, retVal);
  return retVal;
}

//______________________________________________________________________________________________

double HWWEventWeight::getTriggerSF_VH_singLep(const xAOD::CompositeParticle* compPart) const {
  unsigned int nLeptons = compPart->nLeptons();
  float muonSF = 1.0;
  if( m_muonTrigSFDecor ) {
    muonSF = this->getMuonTrigWeight(compPart);
  }
  float eleNom = 1.0;
  float eleDeNom = 1.0;
  int muonMatch = 0;
  int eleMatch = 0;

  for( unsigned int i=0; i<nLeptons; ++i ) {
    if ( compPart->part(i)->type() == xAOD::Type::Electron ) {

      float eleSFTmp = 1.0;
      if( m_eleTrigSFDecor ) {
        eleSFTmp = this->getElectronTrigWeight(compPart->part(i));
      }

      float eleEffTmp = compPart->part(i)->auxdata<float>("effiTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_MediumLHIsoGradient");
      // Only do this if efficiency is not 0
      if( eleEffTmp > 0. ) {
        eleNom *= (1. - eleEffTmp*eleSFTmp);
        eleDeNom *= (1. - eleEffTmp);
      }
      int tmpVal1=(*m_TrigMatchDecorELE1)(*(compPart->part(i)));
      int tmpVal2=(*m_TrigMatchDecorELE2)(*(compPart->part(i)));
      int tmpVal3=(*m_TrigMatchDecorELE3)(*(compPart->part(i)));
      double elePt = compPart->part(i)->pt();
      DEBUGclass( " ele with pt: %f  with Match1: %i , Match2: %i, Match3: %i ", compPart->part(i)->pt(), tmpVal1, tmpVal2, tmpVal3 );
      if( ((tmpVal1+tmpVal2+tmpVal3)>0) && (elePt > 25000.) ) {
        eleMatch++;
      }
    } else if (  compPart->part(i)->type() == xAOD::Type::Muon ) {
      int tmpVal1=(*m_TrigMatchDecorMUON1)(*(compPart->part(i)));
      int tmpVal2=(*m_TrigMatchDecorMUON2)(*(compPart->part(i)));
      double muPt = compPart->part(i)->pt();
      DEBUGclass( " muon with pt: %f  with Match1: %i , Match2: %i ", compPart->part(i)->pt(), tmpVal1, tmpVal2 );
      if( ((tmpVal1+tmpVal2)>0) && (muPt > 21000.) ) {
        muonMatch++;
      }
    }
  }

  // Calculate overall electron SF
  float eleSF = (1. - eleNom)/(1. - eleDeNom);

  double retVal = 1.;

  if( (muonMatch>0) && (eleMatch==0) ) retVal = muonSF;
  else if( (muonMatch==0) && (eleMatch>0) ) retVal = eleSF;
  else if( (muonMatch>0) && (eleMatch>0)  ) retVal=eleSF+muonSF-eleSF*muonSF;
  DEBUGclass( " for this event: muSF= %f, eleSF= %f, matchMu= %i, matchEle= %i, TRIGGERsf= %f", muonSF, eleSF, muonMatch, eleMatch, retVal);

  return retVal;
}

//______________________________________________________________________________________________
double HWWEventWeight::getTriggerSF_singLep(const xAOD::CompositeParticle* compPart) const {

  float nom = 1.0;
  float deNom = 1.0;
  unsigned int nLeptons = compPart->nLeptons();
  const xAOD::EventInfo *evtInfo(0);
  int m_RunNumber;
  if( !this->fEvent->retrieve(evtInfo, "EventInfo").isSuccess() ){
    ERRORclass("failed to retrieve event info!");
  }
  if( evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION) )
    m_RunNumber = evtInfo->auxdata<unsigned int> ("RandomRunNumber");
  else m_RunNumber = evtInfo->runNumber();
  DEBUGclass("RunNumber is  %i",m_RunNumber);
  DEBUGclass("nLeptons %i", nLeptons);
  for( unsigned int i=0; i<nLeptons; ++i ) {
    const xAOD::IParticle* part = compPart->part(i);
    if(!part) {
      throw std::runtime_error("Encountered zero-pointer for one of the leptons, abort...");
    }
    DEBUGclass(" m_useElectronTrigEffWeight %i ",m_useElectronTrigEffWeight);
    if( (part->type() == xAOD::Type::Electron) && m_useElectronTrigEffWeight ) {
      DEBUGclass(" ELe index %i", i);
      float trigEff = 1.0;
      float trigSF = 1.0;
      DEBUGclass(" Assign Decoreation for part with pT %f",part->pt());
      if (m_RunNumber< 302919){
  DEBUGclass(" RunNumber is  %i so we are P<D4",m_RunNumber);
  if( part->pt() > 25e3 ) {
    trigEff =  part->auxdata<float>(m_eleTrigEffName);
    if (m_variationType == EleTrig)   trigSF =   part->auxdata<float>(m_eleTrigSFName+"___"+m_variationName.Data());
    else                              trigSF =   part->auxdata<float>(m_eleTrigSFName);
  } else {
    trigEff =  part->auxdata<float>(m_eleTrigEffNameLow);
    if (m_variationType == EleTrig)   trigSF =   part->auxdata<float>(m_eleTrigSFNameLow+"___"+m_variationName.Data());
    else                              trigSF =   part->auxdata<float>(m_eleTrigSFNameLow);
  }
      } else {
  DEBUGclass(" RunNumber is  %i so we are P>D3",m_RunNumber);
  if( part->pt() > 25e3 ) {
    DEBUGclass(" Ele pT is %f .. using Nominal SF/Eff",part->pt());
    trigEff =  part->auxdata<float>(m_eleTrigEffName_D4);
    if (m_variationType == EleTrig)   trigSF =   part->auxdata<float>(m_eleTrigSFName_D4+"___"+m_variationName.Data());
    else                              trigSF =   part->auxdata<float>(m_eleTrigSFName_D4);
  } else {
    DEBUGclass(" Ele pT is %f .. using LowpT SF/Eff",part->pt());
    trigEff =  part->auxdata<float>(m_eleTrigEffNameLow_D4);
    if (m_variationType == EleTrig)   trigSF =   part->auxdata<float>(m_eleTrigSFNameLow_D4+"___"+m_variationName.Data());
    else                              trigSF =   part->auxdata<float>(m_eleTrigSFNameLow_D4);
  } //else pT
      }   // else RunNumber

      float trigDataEff = trigEff*trigSF;

      DEBUGclass("Electron trigger MC efficiency: %f", trigEff);
      DEBUGclass("Electron trigger SF: %f", trigSF);
      DEBUGclass("Resulting electron trigger data efficiency: %f", trigDataEff);

      nom *= (1. - trigDataEff);
      deNom *= (1. - trigEff);
    }
    else if( (part->type() == xAOD::Type::Muon) && m_useMuonTrigEffWeight ) {
      DEBUGclass(" Muon index %i", i);
      DEBUGclass("m_useMuonTrigEffWeight %i",i);
      float trigEff = 1.0;
      float trigSF = 1.0;

      if (m_RunNumber< 302919){
  DEBUGclass(" RunNumber is  %i so we are P<D4",m_RunNumber);
  if( part->pt() > 25e3 ) {
    DEBUGclass(" Muon pT is %f .. using Nominal SF/Eff",part->pt());
    trigEff =  part->auxdata<float>(m_muonTrigEffName);
    if (m_variationType == MuonTrig)   trigSF =   part->auxdata<float>(m_muonTrigSFName+"___"+m_variationName.Data());
    else                              trigSF =   part->auxdata<float>(m_muonTrigSFName);
  } else {
    DEBUGclass(" Muon pT is %f .. using LowpT SF/Eff",part->pt());
    trigEff =  part->auxdata<float>(m_muonTrigEffNameLow);
    if (m_variationType == MuonTrig)   trigSF =   part->auxdata<float>(m_muonTrigSFNameLow+"___"+m_variationName.Data());
    else                              trigSF =   part->auxdata<float>(m_muonTrigSFNameLow);
  }
      } else {
  DEBUGclass(" RunNumber is  %i so we are P>D3",m_RunNumber);
  if( part->pt() > 25e3 ) {
    DEBUGclass(" Muon pT is %f .. using Nominal SF/Eff",part->pt());
    trigEff =  part->auxdata<float>(m_muonTrigEffName_D4);
    if (m_variationType == MuonTrig)   trigSF =   part->auxdata<float>(m_muonTrigSFName_D4+"___"+m_variationName.Data());
    else                              trigSF =   part->auxdata<float>(m_muonTrigSFName_D4);
  } else {
    DEBUGclass(" Muon pT is %f .. using LowpT SF/Eff",part->pt());
    trigEff =  part->auxdata<float>(m_muonTrigEffNameLow_D4);
    if (m_variationType == MuonTrig)   trigSF =   part->auxdata<float>(m_muonTrigSFNameLow_D4+"___"+m_variationName.Data());
    else                              trigSF =   part->auxdata<float>(m_muonTrigSFNameLow_D4);
  } // else pT
      } // else RunNumber

      /*

 if( part->pt() > 25e3 ) {
        trigEff = (*m_muonTrigEffDecor)(*part);
        trigSF = (*m_muonTrigSFDecor)(*part);
      }
      else {
        trigEff = (*m_muonTrigEffDecorLowPt)(*part);
        trigSF = (*m_muonTrigSFDecorLowPt)(*part);
      }*/
      float trigDataEff = trigEff*trigSF;

      DEBUGclass("Muon trigger MC efficiency: %f", trigEff);
      DEBUGclass("Muon trigger SF: %f", trigSF);
      DEBUGclass("Resulting muon trigger data efficiency: %f", trigDataEff);

      nom *= (1. - trigDataEff);
      deNom *= (1. - trigEff);
    }
  }

  double retVal = 1.0;
  // Overall trigger SF
  if( (1. - deNom) > 0. ) {
    retVal = (1. - nom)/(1. - deNom);
  }
  else {
    DEBUGclass("Found denominator of %f for overall trigger SF, will return SF of 1.0", (1. - deNom));
  }

  return retVal;
}

//______________________________________________________________________________________________

double HWWEventWeight::getTTbarNNLOWeight(const xAOD::EventInfo* evtInfo) const {
  //INFOclass("Doing TTbar NNLO reweighting ...");
  double retval = 1.;

  int DSID = evtInfo->mcChannelNumber();
  //double tTTbarPt = 0;
  double tTopPt = 0;

  // NNLOReweighter* gNNLOReweighter;
  // gNNLOReweighter = new NNLOReweighter(DSID);
  // gNNLOReweighter->Init();

  #ifdef _DEBUG_
  if(!this->fEvent){
    ERRORclass("failed to access xAOD::TEvent member!");
    return 1.;
  }
  #endif

  // if( evtInfo->isAvailable<float>("truth_toppt")){ // && evtInfo->isAvailable<float>("truth_ttbarpt") ){
  //   tTopPt = evtInfo->auxdata<float>("truth_toppt");
  //   // sequential weights
  //   //tTTbarPt = evtInfo->auxdata<float>("truth_ttbarpt");
  //   //retval = gNNLOReweighter->GetTtbarAndTopPtWeight(tTTbarPt, tTopPt);
  //   // extended binning
  //   retval = gNNLOReweighter->GetExtendedTopPtWeight(tTopPt);
  // }

  //INFOclass("Event:: DSID: %i", DSID);
  //INFOclass("Event:: Truth ttbar pt: %.2f", tTTbarPt);
  //INFOclass("Event:: Truth top pt: %.2f", tTopPt);
  //INFOclass("TTbar NNLO weight: %.2f", retval);

  // gNNLOReweighter->~NNLOReweighter();

  return retval;
}

//______________________________________________________________________________________________

double HWWEventWeight::getValue() const {
  // value retrieval function, called on every event for every cut and histogram
  DEBUGclass("entering function");
  // the following protective if-block should NEVER evaluate true
  // for performance reasons, we disable it per preprocessor directive unless in debugging mode
  #ifdef _DEBUG_
  if(!this->fEvent){
    ERRORclass("failed to access xAOD::TEvent member!");
    return 0;
  }
  #endif

  DEBUGclass("retrieving container");


  // Retrieve the event candidates
  const xAOD::CompositeParticleContainer *cand(0);
  if( !this->fEvent->retrieve(cand, this->m_candName.Data()).isSuccess() ){
    ERRORclass("failed to retrieve candidates!");
    return 0;
  }

  DEBUGclass("retrieving event candidate from container");
  if(cand->size() == 0){
    ERRORclass("in %s: event '%d' in '%s' has no candidate of type '%s'!",this->GetName(),(int)(this->getCurrentEntry()),this->fSample->getPath().Data(),this->m_candName.Data());
    return 0.;
  }
  const xAOD::CompositeParticle *evt = cand->at(0);

  // Retrieve the EventInfo container
  const xAOD::EventInfo *evtInfo(0);
  if( !this->fEvent->retrieve(evtInfo, "EventInfo").isSuccess() ){
    ERRORclass("failed to retrieve event info!");
    return 0;
  }

  // Don't do anything for data
  if( !evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION) ){
    DEBUGclass("returning unity weight for data");
    return 1.;
  }

  const int entry = this->getCurrentEntry();
  if(entry == this->fCachedEntry) {
    DEBUGclass("skipping reevalution for event %d, returning %f",entry, this->fCachedValue);
    return this->fCachedValue;
  }
  this->fCachedEntry=entry;

  // Get MC generator weight, if requested
  double mcWeight = 1.0;
  if( m_doMCWeight ) {
    DEBUGclass("retrieving MC event weight");
    mcWeight = evtInfo->mcEventWeight(0);
    if(m_indexWeight != 0) {
      DEBUGclass("Using event weight index = %d",m_indexWeight);
      mcWeight = evtInfo->mcEventWeight(m_indexWeight);
      DEBUGclass("Original weight = %f",evtInfo->mcEventWeight(0));
      //some special case for NNLOPS
      if(evtInfo->mcChannelNumber() == 345324) {
        //check if weight is NAN, only for uncertainty weights
        if(!std::isfinite(mcWeight) && m_indexWeight != 151) mcWeight = evtInfo->mcEventWeight(150);
        if(mcWeight > 100.0) mcWeight=100.0;
        if(mcWeight < -100.0) mcWeight=-100.0;
      }

    }
    if ( m_variationType == ggFQCDscale) {
      if(evtInfo->mcChannelNumber() == 345324) {
        DEBUGclass("Using uncertainty = %s",m_variationName.Data());
        mcWeight = evtInfo->auxdata<float>(m_variationName.Data());
      }
    }
    if(m_pdfWeightName != "") {
      DEBUGclass("Using event pdf weight = %s",m_pdfWeightName.Data());
      mcWeight = evtInfo->auxdata<float>(m_pdfWeightName.Data());
      DEBUGclass("Original weight = %f",evtInfo->mcEventWeight(0));
    }
    DEBUGclass("MC event weight = %f", mcWeight);
  }

  if (m_doMCWeightOnly) {  // should only be used for truth samples
    // Calculate and return the overall event weight
    const double weight = mcWeight;
    DEBUGclass("Overall event weight = %f", weight);
    if(!TQUtils::isNum(weight)){
      ERRORclass("Encountered non-numeric event weight for event %d",this->getCurrentEntry());
      return 0;
    }

    this->fCachedValue = weight;
    return weight;

  }

  // Get pile-up re-weighting weight, if requested
  double prwWeight = 1.0;
  if( m_doPRW ) {
    bool success=false;
    if( m_usePRWTool ) {
      if ( evtInfo->runNumber()==222525 ) {
        success=m_prwTool_mc15a->apply( *evtInfo ).isSuccess();
      } else {
        success=m_prwTool_mc15b->apply( *evtInfo ).isSuccess();
      }
    }
    else {
      success = true;
    }

    if(success) prwWeight = evtInfo->auxdata<float>(m_prwVarName);
    else ERRORclass("Something went wrong with the pile-up re-weighting");

    DEBUGclass("Pileup weight = %f for var name %s", prwWeight, m_prwVarName.c_str());
  }

  // Get number of leptons in the event
  unsigned int nLeptons = evt->nLeptons();

  // Get lepton efficiency weights, if requested
  double lepWeight = 1.0;
  if( m_eleSFDecor && m_muonSFDecor ) {
    for( unsigned int i=0; i<nLeptons; ++i ) {
      DEBUGclass("lepton weights: index %d",(int)i);
      lepWeight *= this->getLeptonWeight(evt->part(i));
    }
    DEBUGclass("Total lepton weight = %f", lepWeight);
  }

  // Get electron ID efficiency weights, if requested
  double eleIDWeight = 1.0;
  if( m_eleIDSFDecor ) {
    for( unsigned int i=0; i<nLeptons; ++i ) {
      DEBUGclass("electron ID weights: index %d",(int)i);
      eleIDWeight *= this->getElectronIDWeight(evt->part(i));
    }
    DEBUGclass("Total electron ID weight = %f", eleIDWeight);
  }

  // Get electron isolation efficiency weights, if requested
  double eleIsoWeight = 1.0;
  if( m_eleIsoSFDecor ) {
    for( unsigned int i=0; i<nLeptons; ++i ) {
      DEBUGclass("electron isolation weights: index %d",(int)i);
      eleIsoWeight *= this->getElectronIsoWeight(evt->part(i));
    }
    DEBUGclass("Total electron isolation weight = %f", eleIsoWeight);
  }

  // Get muon isolation efficiency weights, if requested
  double muonIsoWeight = 1.0;
  DEBUGclass("Muon Iso SF");
  if( m_muonIsoSFDecor ) {
      DEBUGclass("m_muonIsoSFDecor True");
    for( unsigned int i=0; i<nLeptons; ++i ) {
      DEBUGclass("muon isolation weights: index %d",(int)i);
      muonIsoWeight *= this->getMuonIsoWeight(evt->part(i));
    }
    DEBUGclass("Total muon isolation weight = %f", muonIsoWeight);
  }

  // Get muon TTVA efficiency weights, if requested
  double muonTTVAWeight = 1.0;
  if( m_muonTTVASFDecor ) {
    for( unsigned int i=0; i<nLeptons; ++i ) {
      DEBUGclass("muon TTVA weights: index %d",(int)i);
      muonTTVAWeight *= this->getMuonTTVAWeight(evt->part(i));
    }
    DEBUGclass("Total muon TTVA weight = %f", muonTTVAWeight);
  }

  // Get ttbar NNLO weights, if requested
  const xAOD::TruthEventContainer *tEvtCtn = NULL;
  if( !this->fEvent->retrieve(tEvtCtn, "TruthEvents").isSuccess() ){
    ERRORclass("failed to retrieve TruthEvents!");
    return 0;
  }
  double ttbarNNLOWeight = 1.0;
  if( m_ttbarNNLOSFDecor ) {
    ttbarNNLOWeight = this->getTTbarNNLOWeight(evtInfo);
    DEBUGclass("TTbar NNLO weight = %f", ttbarNNLOWeight);
  }

  double DFTrigWeight   = 1.0;
  double eleTrigWeight  = 1.0;
  double muonTrigWeight = 1.0;
  double VHTrigWeight = 1.0;

  double singleTrigWeight = 1.0;

  DEBUGclass("m_useMuonTrigEffWeight %i, m_useElectronTrigEffWeight %i, m_isDFEvent %i",m_useMuonTrigEffWeight,m_useElectronTrigEffWeight,m_isDFEvent);
  if(m_useMuonTrigEffWeight || m_useElectronTrigEffWeight) {
    DEBUGclass("Retrieving total single trigger weight ");
    singleTrigWeight = this->getTriggerSF_singLep(evt);
    DEBUGclass("Total single trigger weight = %f", singleTrigWeight);
  }
  /// if the event is not DF or VH, keep the old code
  else if ( (!m_isDFEvent && !m_isVHEvent)  || m_isDiLeptonTrigger ) {
    // Get electron trigger efficiency weights, if requested
    if( m_eleTrigSFDecor && m_useElectronTrigWeight ) {
      for( unsigned int i=0; i<nLeptons; ++i ) {
        DEBUGclass("electron trigger weights: index %d",(int)i);
        eleTrigWeight *= this->getElectronTrigWeight(evt->part(i));
      }
      DEBUGclass("Total electron trigger weight = %f", eleTrigWeight);
    }
    // Get muon trigger efficiency weights, if requested
    if( m_muonTrigSFDecor && m_useMuonTrigWeight ) {
      muonTrigWeight *= this->getMuonTrigWeight(evt);
      DEBUGclass("Total muon trigger weight = %f", muonTrigWeight);
    }
  }
  else if( m_isDFEvent ) {
    if ( (m_eleTrigSFDecor && m_useElectronTrigWeight) && (m_muonTrigSFDecor && m_useMuonTrigWeight) ) {
      DFTrigWeight = this->getTriggerSF_DF_singLep(evt);
      DEBUGclass("Total DF trigger weight = %f", DFTrigWeight);
    }
  }
  else if( m_isVHEvent ) {
    if ( (m_eleTrigSFDecor && m_useElectronTrigWeight) || (m_muonTrigSFDecor && m_useMuonTrigWeight) ) {
      VHTrigWeight = this->getTriggerSF_VH_singLep(evt);
      DEBUGclass("Total VH trigger weight = %f", VHTrigWeight);
    }
  }

  double bTagWeight = 1.;
  if (m_btagSFDecor) {
    for( unsigned int i=0; i<evt->nParts(); ++i ) {
      bTagWeight *= this->getBtagWeight(evt->part(i));
    }
    if (m_useOtherJets) {
      for( unsigned int i=0; i<evt->nOtherParts(); ++i ) {
        bTagWeight *= this->getBtagWeight(evt->otherPart(i));
      }
    }
    DEBUGclass("Total btag weight = %f", bTagWeight);
  }

  double bTagTrackJetWeight = 1.;
  if (m_btagTrackJetSFDecor) {
    bTagTrackJetWeight = getBtagTrackJetWeight();
     DEBUGclass("Total btag track jet weight = %f", bTagTrackJetWeight);
  }

  double jetJVTWeight = 1.;
  if(m_jetJVTSFDecor) {
    if ((*m_jetJVTSFDecor).isAvailable(*evtInfo)) {
      jetJVTWeight = (*m_jetJVTSFDecor)(*evtInfo);
    }
    // this is just for backwards compatibility, if you are using v16 PxAODs or higher this should never execute
    else {
      for( unsigned int i=0; i<evt->nParts(); ++i ) {
        jetJVTWeight *= this->getJVTWeight(evt->part(i));
      }
      // if(m_useOtherJets) {
      //   for( unsigned int i=0; i<evt->nOtherParts(); ++i ) {
      //     jetJVTWeight*= this->getJVTWeight(evt->otherPart(i));
      //   }
      // }
      DEBUGclass("JVT weight = %f", jetJVTWeight);
    }
  }
  double jetForwardJVTWeight = 1.;
  if(m_jetForwardJVTSFDecor) {
     jetForwardJVTWeight = (*m_jetForwardJVTSFDecor)(*evtInfo);
    DEBUGclass("Forward JVT weight = %f", jetForwardJVTWeight);
  }

  // Calculate and return the overall event weight
  const double weight = mcWeight * prwWeight * lepWeight * eleIDWeight * eleIsoWeight * eleTrigWeight * muonIsoWeight * muonTTVAWeight * muonTrigWeight * DFTrigWeight * VHTrigWeight * bTagWeight * bTagTrackJetWeight *jetJVTWeight * jetForwardJVTWeight * singleTrigWeight * ttbarNNLOWeight;
  DEBUGclass("Overall event weight = %f", weight);
  if(!TQUtils::isNum(weight)){
    ERRORclass("Encountered non-numeric event weight for event %d",this->getCurrentEntry());
    return 0;
  }

  // evt->auxdecor<float>("weight_PU") = prwWeight;
  // evt->auxdecor<float>("weight_Reco") = lepWeight;
  // evt->auxdecor<float>("weight_Trig") = DFTrigWeight;
  // evt->auxdecor<float>("weight_MuIso") = muonIsoWeight;
  // evt->auxdecor<float>("weight_ElID") = eleIDWeight;
  // evt->auxdecor<float>("weight_ElIso") = eleIsoWeight;
  // evt->auxdecor<float>("weight_bTag") = bTagWeight;
  // evt->auxdecor<float>("weight_bTagTrackJet") = bTagTrackJetWeight;

  this->fCachedValue = weight;
  return weight;
}

//______________________________________________________________________________________________

HWWEventWeight::HWWEventWeight(const TString& expression):
  TQEventObservable(expression),
  m_doMCWeight(true),
  m_doPRW(false),
  m_usePRWTool(false),
  m_isMuonEvent(false),
  m_isDFEvent(false),
  m_isVHEvent(false),
  m_isDiLeptonTrigger(false),
  m_indexWeight(0)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->setExpression(expression);
  //this->SetName(TQObservable::makeObservableName(expression)); //this is pointless, since the same line is in the ctor of TQObservable.

  DEBUGclass("Default is to only use the MC generator weight, please enable other weights as needed.");
}

//______________________________________________________________________________________________

const TString& HWWEventWeight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

void HWWEventWeight::setExpression(const TString& expression) {
  this->fExpression = expression;
}

//______________________________________________________________________________________________

bool HWWEventWeight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}
