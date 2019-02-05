#include "Htautau/FakesMM.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(FakesMM)

//______________________________________________________________________________________________

FakesMM::FakesMM(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

FakesMM::~FakesMM(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* FakesMM::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));


  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("lep_1"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("lep_1_pt"));
  bnames->Add(new TObjString("lep_0_id_tight"));
  bnames->Add(new TObjString("lep_1_id_loose"));
  bnames->Add(new TObjString("lep_1_id_tight"));


  return bnames;
}

//______________________________________________________________________________________________

double FakesMM::getValue() const {
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

  int lep_0 = this->lep_0->EvalInstance();
  int lep_1 = this->lep_1->EvalInstance();
  int lep_0_pt = this->lep_0_pt->EvalInstance();
  int lep_1_pt = this->lep_1_pt->EvalInstance();
  int lep_0_id_tight = this->lep_0_id_tight->EvalInstance();
  int lep_1_id_loose = this->lep_1_id_loose->EvalInstance();
  int lep_1_id_tight = this->lep_1_id_tight->EvalInstance();

  double deltai = -1000.;

  if (lep_0_id_tight == 1 && lep_1_id_loose == 1) {
    deltai = 0.;
    if (lep_1_id_tight == 1) {
      deltai = 1.;
    }
  }
  else {
    //std::cout << "Event failed lepton selection! Return fake weight 0!!" << std::endl;
    return 0.;
  }

  double wFake = 0.;
  double effReal = 1.;
  double effFake = 0.;

  int binReal = -1;
  int binFake = -1;

  //std::cout << "Have pT lep1: " << lep_1_pt << std::endl;

  if (lep_1 == 1){
    //std::cout << "muon" << std::endl;
    //effReal = 0.96;
    //effFake = 0.65;
    binReal = h_eff_real_muon->FindBin(lep_1_pt);
    binFake = h_eff_fake_muon->FindBin(lep_1_pt);
    if (binReal!=0 && binFake!=0){
      effReal = h_eff_real_muon->GetBinContent(binReal);
      effFake = h_eff_fake_muon->GetBinContent(binFake);
    }
  }
  else if (lep_1 == 2){
    //std::cout << "electron" << std::endl;
    //effReal = 0.88;
    //effFake = 0.58;
    binReal = h_eff_real_elec->FindBin(lep_1_pt);
    binFake = h_eff_fake_elec->FindBin(lep_1_pt);
    if (binReal!=0 && binFake!=0){
      effReal = h_eff_real_elec->GetBinContent(binReal);
      effFake = h_eff_fake_elec->GetBinContent(binFake);
    }
  }
  else {
    std::cout << "No valid ID found for sublead lepton" << std::endl;
    return -1.;
  }

  //std::cout << "bin fake: " << binFake << "  -> eff: " << effFake << std::endl;
  //std::cout << "bin real: " << binReal << "  -> eff: " << effReal <<std::endl;

  if (effReal!=effFake && (effReal!=0. && effFake!=0.)){
    wFake = effFake/(effReal-effFake)*(effReal-deltai);
  }
  else wFake =0.;


  //std::cout << "fake weight: " << wFake << std::endl;
  DEBUGclass("Eff real = %s", effReal);
  DEBUGclass("Eff fake = %s", effFake);
  DEBUGclass("Fake weight = %s", wFake);
  DEBUGclass("returning");

  return wFake;
}
//______________________________________________________________________________________________

FakesMM::FakesMM(const TString& expression):
TQTreeObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);
}

//______________________________________________________________________________________________

const TString& FakesMM::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool FakesMM::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void FakesMM::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool FakesMM::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void FakesMM::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString FakesMM::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool FakesMM::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);

  this->lep_0 = new TTreeFormula( "lep_0", "lep_0", this->fTree);
  this->lep_1 = new TTreeFormula( "lep_1", "lep_1", this->fTree);
  this->lep_0_pt = new TTreeFormula( "lep_0_pt", "lep_0_pt", this->fTree);
  this->lep_1_pt = new TTreeFormula( "lep_1_pt", "lep_1_pt", this->fTree);
  this->lep_0_id_tight = new TTreeFormula( "lep_0_id_tight", "lep_0_id_tight", this->fTree);
  this->lep_1_id_loose = new TTreeFormula( "lep_1_id_loose", "lep_1_id_loose", this->fTree);
  this->lep_1_id_tight = new TTreeFormula( "lep_1_id_tight", "lep_1_id_tight", this->fTree);


  FileEff_real_elec = TFile::Open("../share/fakesMM/Efficiency_vs_LeptonPt1_Real_ee.root","READ");
  FileEff_real_muon = TFile::Open("../share/fakesMM/Efficiency_vs_LeptonPt1_Real_mm.root","READ");
  FileEff_fake_elec = TFile::Open("../share/fakesMM/Efficiency_vs_LeptonPt1_Fake_me.root","READ");
  FileEff_fake_muon = TFile::Open("../share/fakesMM/Efficiency_vs_LeptonPt1_Fake_em.root","READ");
  //FileEff_fake_elec = TFile::Open("/home/al1033/analysis/Htautau/share/fakesMM/Efficiency_vs_FakeElecPt_Fake_ee.root","READ");
  //FileEff_fake_muon = TFile::Open("/home/al1033/analysis/Htautau/share/fakesMM/Efficiency_vs_FakeMuonPt_Fake_ee.root","READ");

  if (!FileEff_real_elec || !FileEff_real_elec->IsOpen()) {
    std::cout << "Failed to open file for electron real efficiency!" << std::endl;
  }
  if (!FileEff_fake_elec || !FileEff_fake_elec->IsOpen()) {
    std::cout << "Failed to open file for electron fake efficiency!" << std::endl;
  }
  if (!FileEff_real_muon || !FileEff_real_muon->IsOpen()) {
    std::cout << "Failed to open file for muon real efficiency!" << std::endl;
  }
  if (!FileEff_fake_muon || !FileEff_fake_muon->IsOpen()) {
    std::cout << "Failed to open file for muon fake efficiency!" << std::endl;
  }


  h_eff_real_elec = (TH1F*)FileEff_real_elec->Get("h_eff_tf")->Clone("h_eff_real_elec");
  h_eff_real_muon = (TH1F*)FileEff_real_muon->Get("h_eff_tf")->Clone("h_eff_real_muon");
  h_eff_fake_elec = (TH1F*)FileEff_fake_elec->Get("h_eff_tf")->Clone("h_eff_fake_elec");
  h_eff_fake_muon = (TH1F*)FileEff_fake_muon->Get("h_eff_tf")->Clone("h_eff_fake_muon");

  h_eff_real_elec->SetDirectory(0);
  h_eff_real_muon->SetDirectory(0);
  h_eff_fake_elec->SetDirectory(0);
  h_eff_fake_muon->SetDirectory(0);

  //std::cout << "CHECK: Histos" << std::endl;
  //std::cout << "       " << h_eff_real_elec << std::endl;
  //std::cout << "       " << h_eff_real_muon << std::endl;
  //std::cout << "       " << h_eff_fake_elec << std::endl;
  //std::cout << "       " << h_eff_fake_muon << std::endl;

  FileEff_real_elec->Close();
  FileEff_real_muon->Close();
  FileEff_fake_elec->Close();
  FileEff_fake_muon->Close();

  return true;
}

//______________________________________________________________________________________________

bool FakesMM::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  //delete FileEff;

  delete this->lep_0;
  delete this->lep_1;
  delete this->lep_0_pt;
  delete this->lep_1_pt;
  delete this->lep_0_id_tight;
  delete this->lep_1_id_loose;
  delete this->lep_1_id_tight;

  return true;
}
