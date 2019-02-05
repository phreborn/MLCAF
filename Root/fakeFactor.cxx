#include "Htautau/fakeFactor.h"
#include <limits>
#include "TVector2.h"

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(fakeFactor)

//______________________________________________________________________________________________

fakeFactor::fakeFactor(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

fakeFactor::~fakeFactor(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* fakeFactor::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = LepHadObservable::getBranchNames();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("tau_0_n_tracks"));
  bnames->Add(new TObjString("tau_0_phi"));
  bnames->Add(new TObjString("met_reco_phi"));

  return bnames;
}

//______________________________________________________________________________________________

double fakeFactor::getValue() const {
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

  //std::cout<<" In getValue "<<std::endl;
  double tau_0_n_tracks = this->tau_0_n_tracks->EvalInstance();
  double tau_0_pt = this->tau_0_pt->EvalInstance();
  double tau_0_phi = this->tau_0_phi->EvalInstance();
  double met_reco_phi = this->met_reco_phi->EvalInstance();

  double dPhiTauMET = -99.;

  double FF_W = 0.;
  double FF_Top = 0.;
  double FF_Z = 0;
  double FF_QCD = 0.;

  double R_W = 0.;
  double R_Top = 0.;
  double R_Z = 0;
  double R_QCD = 0.;

  double factor = 1.;

  double FF_W_Err = 0.;
  double FF_Top_Err = 0.;
  double FF_Z_Err = 0;
  double FF_QCD_Err = 0.;

  double R_W_Err = 0.;
  double R_Top_Err = 0.;
  double R_Z_Err = 0;
  double R_QCD_Err = 0.;

  double factor_Err = 1.;

  Int_t binFF = 0;
  Int_t binR = 0;

  TAxis* xAxisFF = FF_W_1Prong_SLT_2015->GetXaxis();
  double maxBinFF = xAxisFF->GetBinUpEdge(xAxisFF->GetLast());

  TAxis* xAxisR = R_W_1Prong_SLT_2015->GetXaxis();
  double maxBinR = xAxisR->GetBinUpEdge(xAxisR->GetLast());

  TH1D* FF_W_Hist = NULL;
  TH1D* FF_Top_Hist = NULL;
  TH1D* FF_Z_Hist = NULL;
  TH1D* FF_QCD_Hist = NULL;

  TH1D* R_W_Hist = NULL;
  TH1D* R_Top_Hist = NULL;
  TH1D* R_Z_Hist = NULL;
  TH1D* R_QCD_Hist = NULL;

  dPhiTauMET = fabs(TVector2::Phi_mpi_pi(tau_0_phi - met_reco_phi));

  if (isSLT()) {
    if (tau_0_n_tracks == 1) {
      if (is2015()) {
	FF_W_Hist = FF_W_1Prong_SLT_2015;
	FF_Top_Hist = FF_Top_1Prong_SLT_2015;
	FF_Z_Hist = FF_Z_1Prong_SLT_2015;
	FF_QCD_Hist = FF_QCD_1Prong_SLT_2015;

	R_W_Hist = R_W_1Prong_SLT_2015;
	R_Top_Hist = R_Top_1Prong_SLT_2015;
	R_Z_Hist = R_Z_1Prong_SLT_2015;
	R_QCD_Hist = R_QCD_1Prong_SLT_2015;
      } else {
	FF_W_Hist = FF_W_1Prong_SLT_2016;
	FF_Top_Hist = FF_Top_1Prong_SLT_2016;
	FF_Z_Hist = FF_Z_1Prong_SLT_2016;
	FF_QCD_Hist = FF_QCD_1Prong_SLT_2016;

	R_W_Hist = R_W_1Prong_SLT_2016;
	R_Top_Hist = R_Top_1Prong_SLT_2016;
	R_Z_Hist = R_Z_1Prong_SLT_2016;
	R_QCD_Hist = R_QCD_1Prong_SLT_2016;
      }
    } else {
      if (is2015()) {
	FF_W_Hist = FF_W_3Prong_SLT_2015;
	FF_Top_Hist = FF_Top_3Prong_SLT_2015;
	FF_Z_Hist = FF_Z_3Prong_SLT_2015;
	FF_QCD_Hist = FF_QCD_3Prong_SLT_2015;

	R_W_Hist = R_W_3Prong_SLT_2015;
	R_Top_Hist = R_Top_3Prong_SLT_2015;
	R_Z_Hist = R_Z_3Prong_SLT_2015;
	R_QCD_Hist = R_QCD_3Prong_SLT_2015;
      } else {
	FF_W_Hist = FF_W_3Prong_SLT_2016;
	FF_Top_Hist = FF_Top_3Prong_SLT_2016;
	FF_Z_Hist = FF_Z_3Prong_SLT_2016;
	FF_QCD_Hist = FF_QCD_3Prong_SLT_2016;

	R_W_Hist = R_W_3Prong_SLT_2016;
	R_Top_Hist = R_Top_3Prong_SLT_2016;
	R_Z_Hist = R_Z_3Prong_SLT_2016;
	R_QCD_Hist = R_QCD_3Prong_SLT_2016;
      }
    }
  }

  if (tau_0_pt > maxBinFF) {
    binFF = FF_W_Hist->FindBin(maxBinFF - 0.0001);
  } else {
    binFF = FF_W_Hist->FindBin(tau_0_pt);
  }

  if (dPhiTauMET > maxBinR) {
    binR = R_W_Hist->FindBin(maxBinR - 0.0001);
  } else {
    binR = R_W_Hist->FindBin(dPhiTauMET);
  }

  FF_W = FF_W_Hist->GetBinContent(binFF);
  FF_Top = FF_Top_Hist->GetBinContent(binFF);
  FF_Z = FF_Z_Hist->GetBinContent(binFF);
  FF_QCD = FF_QCD_Hist->GetBinContent(binFF);

  FF_W_Err = FF_W_Hist->GetBinError(binFF);
  FF_Top_Err = FF_Top_Hist->GetBinError(binFF);
  FF_Z_Err = FF_Z_Hist->GetBinError(binFF);
  FF_QCD_Err = FF_QCD_Hist->GetBinError(binFF);

  R_W = R_W_Hist->GetBinContent(binR);
  R_Top = R_Top_Hist->GetBinContent(binR);
  R_Z = R_Z_Hist->GetBinContent(binR);
  R_QCD = R_QCD_Hist->GetBinContent(binR);

  R_W_Err = R_W_Hist->GetBinError(binR);
  R_Top_Err = R_Top_Hist->GetBinError(binR);
  R_Z_Err = R_Z_Hist->GetBinError(binR);
  R_QCD_Err = R_QCD_Hist->GetBinError(binR);

  if(Top.Contains("MC")){
    factor = FF_Top;
    factor_Err = FF_Top_Err;
  }
  else if(W.Contains("MC")){
    factor = FF_W;
    factor_Err = FF_W_Err;
  }
  else if(Z.Contains("MC")){
    factor = FF_Z;
    factor_Err = FF_Z_Err;
  }
  else{
    factor = FF_W*R_W + FF_Top*R_Top + FF_Z*R_Z + FF_QCD*R_QCD;

    factor_Err = pow(pow(R_W_Err*FF_W,2)+pow(R_W*FF_W_Err,2)
		     +pow(R_Top_Err*FF_Top,2)+pow(R_Top*FF_Top_Err,2)
		     +pow(R_Z_Err*FF_Z,2)+pow(R_Z*FF_Z_Err,2)
		     +pow(R_QCD_Err*FF_QCD,2)+pow(R_QCD*FF_QCD_Err,2),0.5);
  }

  if (var == "up") {
    factor += factor_Err;
  }
  else if (var == "down") {
    factor -= factor_Err;
  }

  if (SSvar == "doSSsystVBF") {
    if (dPhiTauMET > 0 && dPhiTauMET < 0.64) {
      factor *= 1.220675;
    }
    else if(dPhiTauMET > 0.64 && dPhiTauMET < 1.28) {
      factor *= 1.188086;
    }
    else if(dPhiTauMET > 1.28 && dPhiTauMET < 1.92) {
      factor *= 1.063025;
    }
    else if(dPhiTauMET > 1.92 && dPhiTauMET < 2.56) {
      factor *= 1.071482;
    }
    else if(dPhiTauMET > 2.56 && dPhiTauMET < 3.2) {
      factor *= 0.929276;
    }
  }
  else if (SSvar == "doSSsystBOOST") {
    if (dPhiTauMET > 0 && dPhiTauMET < 0.64) {
      factor *= 1.418737;
    }
    else if(dPhiTauMET > 0.64 && dPhiTauMET < 1.28) {
      factor *= 1.258495;
    }
    else if(dPhiTauMET > 1.28 && dPhiTauMET < 1.92) {
      factor *= 1.216517;
    }
    else if(dPhiTauMET > 1.92 && dPhiTauMET < 2.56) {
      factor *= 0.983063;
    }
    else if(dPhiTauMET > 2.56 && dPhiTauMET < 3.2) {
      factor *= 1.254246;
    }
  }


  // // "central values that go negative are put at 0.0001, while variations that
  // // go negative are set to 0.00005"
  // if (factor < 0) {
  //   if (var == "") {
  //     factor = NOMINAL_THRESHOLD;
  //   } else {
  //     factor = VARIATION_THRESHOLD;
  //   }
  // }

  DEBUGclass("tauPt: %f", tau_0_pt);
  DEBUGclass("dPhiTauMET: %f", dPhiTauMET);
  // DEBUGclass("leptonPt: %f", lep_0_pt->EvalInstance());
  // DEBUGclass("nProngs: %f", tau_0_n_tracks->EvalInstance());
  // DEBUGclass("bin: %i", binx->EvalInstance());
  DEBUGclass("FF_W: %f", FF_W);
  DEBUGclass("FF_Top: %f", FF_Top);
  DEBUGclass("FF_Z: %f", FF_Z);
  DEBUGclass("FF_QCD: %f", FF_QCD);
  DEBUGclass("R_W: %f", R_W);
  DEBUGclass("R_Top: %f", R_Top);
  DEBUGclass("R_Z: %f", R_Z);
  DEBUGclass("R_QCD: %f", R_QCD);
  DEBUGclass("FF: %f", factor);

  DEBUGclass("returning");

  return factor;
}
//______________________________________________________________________________________________

fakeFactor::fakeFactor(TString expression, TString ffFilePath, TString rFilePath, TString category, TString region, TString mc):
    LepHadObservable(expression) {
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  if(expression.Contains("fake_stat_high")){
    DEBUGclass("up variation");
    var = "up";
  } else if(expression.Contains("fake_stat_low")){
    DEBUGclass("down variation");
    var = "down";
  } else var = "";

  if(mc.Contains("MC")){
    if(mc.Contains("TopMC")){
      Top = "TopMC";
    }
    else if(mc.Contains("WMC")){
      W = "WMC";
    }
    else if(mc.Contains("ZMC")){
      Z = "ZMC";
    }
  }

  ffFile = TFile::Open(ffFilePath, "READ");
  if (!ffFile) {
    ERROR("Can't open FF file");
  }

  //std::cout<<"FF START GETTING\n";

  FF_W_1Prong_SLT_2015 = (TH1D*)ffFile->Get(W+"_"+category+"_1Prong_SLT_2015");
  FF_W_3Prong_SLT_2015 = (TH1D*)ffFile->Get(W+"_"+category+"_3Prong_SLT_2015");
  FF_W_1Prong_SLT_2016 = (TH1D*)ffFile->Get(W+"_"+category+"_1Prong_SLT_2016");
  FF_W_3Prong_SLT_2016 = (TH1D*)ffFile->Get(W+"_"+category+"_3Prong_SLT_2016");

  FF_Top_1Prong_SLT_2015 = (TH1D*)ffFile->Get(Top+"_"+category+"_1Prong_SLT_2015");
  FF_Top_3Prong_SLT_2015 = (TH1D*)ffFile->Get(Top+"_"+category+"_3Prong_SLT_2015");
  FF_Top_1Prong_SLT_2016 = (TH1D*)ffFile->Get(Top+"_"+category+"_1Prong_SLT_2016");
  FF_Top_3Prong_SLT_2016 = (TH1D*)ffFile->Get(Top+"_"+category+"_3Prong_SLT_2016");

  FF_Z_1Prong_SLT_2015 = (TH1D*)ffFile->Get(Z+"_"+category+"_1Prong_SLT_2015");
  FF_Z_3Prong_SLT_2015 = (TH1D*)ffFile->Get(Z+"_"+category+"_3Prong_SLT_2015");
  FF_Z_1Prong_SLT_2016 = (TH1D*)ffFile->Get(Z+"_"+category+"_1Prong_SLT_2016");
  FF_Z_3Prong_SLT_2016 = (TH1D*)ffFile->Get(Z+"_"+category+"_3Prong_SLT_2016");

  FF_QCD_1Prong_SLT_2015 = (TH1D*)ffFile->Get("QCD_"+category+"_1Prong_SLT_2015");
  FF_QCD_3Prong_SLT_2015 = (TH1D*)ffFile->Get("QCD_"+category+"_3Prong_SLT_2015");
  FF_QCD_1Prong_SLT_2016 = (TH1D*)ffFile->Get("QCD_"+category+"_1Prong_SLT_2016");
  FF_QCD_3Prong_SLT_2016 = (TH1D*)ffFile->Get("QCD_"+category+"_3Prong_SLT_2016");

  //std::cout<<"FF END GETTING\n";

  rFile = TFile::Open(rFilePath, "READ");
  if (!rFile) {
    ERROR("Can't open R file");
  }

  TString Rvar = "";

  if(expression.Contains("Rvar_high")) {
    Rvar = "_up";
  } else if(expression.Contains("Rvar_low")) {
    Rvar = "_dn";
  }

  if(expression.Contains("SS_syst")) {
    if(expression.Contains("VBF")) {
      SSvar = "doSSsystVBF";
    } else if(expression.Contains("BOOST")) {
      SSvar = "doSSsystBOOST";
    }
  }

  // std::cout<<"PRE REGION "<<category<<"\n";
  // if(category.Contains("Pre")) {
  //   category = "VBFCB";
  // }
  // std::cout<<"AFTER REGION "<<category<<"\n";
  //std::cout<<"R START GETTING\n";

  R_W_1Prong_SLT_2015 = (TH1D*)rFile->Get("W_"+category+"_1Prong_SLT_"+region+"_2015"+Rvar);
  R_W_3Prong_SLT_2015 = (TH1D*)rFile->Get("W_"+category+"_3Prong_SLT_"+region+"_2015"+Rvar);
  R_W_1Prong_SLT_2016 = (TH1D*)rFile->Get("W_"+category+"_1Prong_SLT_"+region+"_2016"+Rvar);
  R_W_3Prong_SLT_2016 = (TH1D*)rFile->Get("W_"+category+"_3Prong_SLT_"+region+"_2016"+Rvar);

  R_Top_1Prong_SLT_2015 = (TH1D*)rFile->Get("Top_"+category+"_1Prong_SLT_"+region+"_2015"+Rvar);
  R_Top_3Prong_SLT_2015 = (TH1D*)rFile->Get("Top_"+category+"_3Prong_SLT_"+region+"_2015"+Rvar);
  R_Top_1Prong_SLT_2016 = (TH1D*)rFile->Get("Top_"+category+"_1Prong_SLT_"+region+"_2016"+Rvar);
  R_Top_3Prong_SLT_2016 = (TH1D*)rFile->Get("Top_"+category+"_3Prong_SLT_"+region+"_2016"+Rvar);

  R_Z_1Prong_SLT_2015 = (TH1D*)rFile->Get("Z_"+category+"_1Prong_SLT_"+region+"_2015"+Rvar);
  R_Z_3Prong_SLT_2015 = (TH1D*)rFile->Get("Z_"+category+"_3Prong_SLT_"+region+"_2015"+Rvar);
  R_Z_1Prong_SLT_2016 = (TH1D*)rFile->Get("Z_"+category+"_1Prong_SLT_"+region+"_2016"+Rvar);
  R_Z_3Prong_SLT_2016 = (TH1D*)rFile->Get("Z_"+category+"_3Prong_SLT_"+region+"_2016"+Rvar);

  R_QCD_1Prong_SLT_2015 = (TH1D*)rFile->Get("QCD_"+category+"_1Prong_SLT_"+region+"_2015"+Rvar);
  R_QCD_3Prong_SLT_2015 = (TH1D*)rFile->Get("QCD_"+category+"_3Prong_SLT_"+region+"_2015"+Rvar);
  R_QCD_1Prong_SLT_2016 = (TH1D*)rFile->Get("QCD_"+category+"_1Prong_SLT_"+region+"_2016"+Rvar);
  R_QCD_3Prong_SLT_2016 = (TH1D*)rFile->Get("QCD_"+category+"_3Prong_SLT_"+region+"_2016"+Rvar);

  //std::cout<<"R END GETTING\n";


  FF_W_1Prong_SLT_2015->SetDirectory(0);
  FF_W_3Prong_SLT_2015->SetDirectory(0);
  FF_W_1Prong_SLT_2016->SetDirectory(0);
  FF_W_3Prong_SLT_2016->SetDirectory(0);

  FF_Top_1Prong_SLT_2015->SetDirectory(0);
  FF_Top_3Prong_SLT_2015->SetDirectory(0);
  FF_Top_1Prong_SLT_2016->SetDirectory(0);
  FF_Top_3Prong_SLT_2016->SetDirectory(0);

  FF_Z_1Prong_SLT_2015->SetDirectory(0);
  FF_Z_3Prong_SLT_2015->SetDirectory(0);
  FF_Z_1Prong_SLT_2016->SetDirectory(0);
  FF_Z_3Prong_SLT_2016->SetDirectory(0);

  FF_QCD_1Prong_SLT_2015->SetDirectory(0);
  FF_QCD_3Prong_SLT_2015->SetDirectory(0);
  FF_QCD_1Prong_SLT_2016->SetDirectory(0);
  FF_QCD_3Prong_SLT_2016->SetDirectory(0);

  R_W_1Prong_SLT_2015->SetDirectory(0);
  R_W_3Prong_SLT_2015->SetDirectory(0);
  R_W_1Prong_SLT_2016->SetDirectory(0);
  R_W_3Prong_SLT_2016->SetDirectory(0);

  R_Top_1Prong_SLT_2015->SetDirectory(0);
  R_Top_3Prong_SLT_2015->SetDirectory(0);
  R_Top_1Prong_SLT_2016->SetDirectory(0);
  R_Top_3Prong_SLT_2016->SetDirectory(0);

  R_Z_1Prong_SLT_2015->SetDirectory(0);
  R_Z_3Prong_SLT_2015->SetDirectory(0);
  R_Z_1Prong_SLT_2016->SetDirectory(0);
  R_Z_3Prong_SLT_2016->SetDirectory(0);

  R_QCD_1Prong_SLT_2015->SetDirectory(0);
  R_QCD_3Prong_SLT_2015->SetDirectory(0);
  R_QCD_1Prong_SLT_2016->SetDirectory(0);
  R_QCD_3Prong_SLT_2016->SetDirectory(0);

  ffFile->Close();
  rFile->Close();

}

//______________________________________________________________________________________________

bool fakeFactor::initializeSelf(){
  if (!LepHadObservable::initializeSelf()) {
      return false;
  }

  // this->bla = new TTreeFormula( "name", "formula", this->fTree);
  this->tau_0_n_tracks = new TTreeFormula( "tau_0_n_tracks", "tau_0_n_tracks", this->fTree);
  this->tau_0_phi = new TTreeFormula( "tau_0_phi", "tau_0_phi", this->fTree);
  this->met_reco_phi = new TTreeFormula( "met_reco_phi", "met_reco_phi", this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool fakeFactor::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->tau_0_n_tracks;
  delete this->tau_0_phi;
  delete this->met_reco_phi;

  return true;
}
