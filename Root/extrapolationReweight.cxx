#include "BSMtautauCAF/extrapolationReweight.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "TFile.h"
#include "TMath.h"
#include <map>

ClassImp(extrapolationReweight)

//______________________________________________________________________________________________

extrapolationReweight::extrapolationReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

extrapolationReweight::~extrapolationReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* extrapolationReweight::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  bnames->Add(new TObjString("tau_0_phi"));
  bnames->Add(new TObjString("met_anti_iso_phi"));
  bnames->Add(new TObjString("lep_0_iso_Gradient"));
  bnames->Add(new TObjString("tau_0_n_charged_tracks"));
  bnames->Add(new TObjString("tau_0_pt"));
  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("n_bjets"));
  bnames->Add(new TObjString("lephad_met_lep0_cos_dphi"));
  bnames->Add(new TObjString("lephad_met_lep1_cos_dphi"));

  if (isData()) {
    bnames->Add(new TObjString("run_number"));
  } else {
    bnames->Add(new TObjString("NOMINAL_pileup_random_run_number"));
  }

  return bnames;
}

//______________________________________________________________________________________________
double extrapolationReweight::getValue() const {
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
  double f_tau_0_phi          = this->tau_0_phi->EvalInstance();
  //double f_met_anti_iso_phi   = this->met_anti_iso_phi->EvalInstance();
  double f_lep_0              = this->lep_0->EvalInstance();
  double f_lep_0_iso_Gradient   = this->lep_0_iso_Gradient->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  int    f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  double f_lephad_met_lep0_cos_dphi = this->lephad_met_lep0_cos_dphi->EvalInstance();
  double f_lephad_met_lep1_cos_dphi = this->lephad_met_lep1_cos_dphi->EvalInstance();

  ////////////////////////////
  //
  //  WJETS FF
  //
  ////////////////////////////
  // nominal pt parametrization
  if (f_tau_0_pt >= 300)  f_tau_0_pt = 299;
  if (f_n_bjets !=0) return 1.0;
  double weight(1.0), weight_err(0);
  TH1F * h_weight = 0;
  TH1F * h_weight_up = 0;
  TH1F * h_weight_down = 0;

  if (f_lep_0 == 1) {//muon
    if (f_tau_0_n_charged_tracks ==1) {// 1p 
      if (f_n_bjets ==0 ) { // bveto
        if (f_lephad_met_lep1_cos_dphi<1.) { 
          h_weight = h_all_vr_muhad_1p_dphi1_0tag;
          h_weight_up = h_all_vr_muhad_1p_dphi1_0tag_up;
          h_weight_down = h_all_vr_muhad_1p_dphi1_0tag_down;
        }
        else if (f_lephad_met_lep1_cos_dphi>=1. && f_lephad_met_lep1_cos_dphi<2) {
          h_weight = h_all_vr_muhad_1p_dphi2_0tag;
          h_weight_up = h_all_vr_muhad_1p_dphi2_0tag_up;
          h_weight_down = h_all_vr_muhad_1p_dphi2_0tag_down;
        }
        else if (f_lephad_met_lep1_cos_dphi>=2.) {
          h_weight = h_all_vr_muhad_1p_dphi34_0tag;
          h_weight_up = h_all_vr_muhad_1p_dphi34_0tag_up;
          h_weight_down = h_all_vr_muhad_1p_dphi34_0tag_down;
        }
      }
    }
    else if (f_tau_0_n_charged_tracks ==3) { //3p
      if (f_n_bjets ==0 ) { // bveto
        if (f_lephad_met_lep1_cos_dphi<1.) { 
          h_weight = h_all_vr_muhad_3p_dphi1_0tag;
          h_weight_up = h_all_vr_muhad_3p_dphi1_0tag_up;
          h_weight_down = h_all_vr_muhad_3p_dphi1_0tag_down;
        }
        else if (f_lephad_met_lep1_cos_dphi>=1. && f_lephad_met_lep1_cos_dphi<2) {
          h_weight = h_all_vr_muhad_3p_dphi2_0tag;
          h_weight_up = h_all_vr_muhad_3p_dphi2_0tag_up;
          h_weight_down = h_all_vr_muhad_3p_dphi2_0tag_down;
        }
        else if (f_lephad_met_lep1_cos_dphi>=2.) {
          h_weight = h_all_vr_muhad_3p_dphi34_0tag;
          h_weight_up = h_all_vr_muhad_3p_dphi34_0tag_up;
          h_weight_down = h_all_vr_muhad_3p_dphi34_0tag_down;
        }
      }
    }
  }
  else if (f_lep_0 == 2) {//electron
    if (f_tau_0_n_charged_tracks ==1) {// 1p 
      if (f_n_bjets ==0 ) { // bveto
        if (f_lephad_met_lep1_cos_dphi<1.) { 
          h_weight = h_all_vr_ehad_1p_dphi1_0tag;
          h_weight_up = h_all_vr_ehad_1p_dphi1_0tag_up;
          h_weight_down = h_all_vr_ehad_1p_dphi1_0tag_down;
        }
        else if (f_lephad_met_lep1_cos_dphi>=1. && f_lephad_met_lep1_cos_dphi<2) {
          h_weight = h_all_vr_ehad_1p_dphi2_0tag;
          h_weight_up = h_all_vr_ehad_1p_dphi2_0tag_up;
          h_weight_down = h_all_vr_ehad_1p_dphi2_0tag_down;
        }
        else if (f_lephad_met_lep1_cos_dphi>=2.) {
          h_weight = h_all_vr_ehad_1p_dphi34_0tag;
          h_weight_up = h_all_vr_ehad_1p_dphi34_0tag_up;
          h_weight_down = h_all_vr_ehad_1p_dphi34_0tag_down;
        }
      }
    }
    else if (f_tau_0_n_charged_tracks ==3) { //3p
      if (f_n_bjets ==0 ) { // bveto
        if (f_lephad_met_lep1_cos_dphi<1.) { 
          h_weight = h_all_vr_ehad_3p_dphi1_0tag;
          h_weight_up = h_all_vr_ehad_3p_dphi1_0tag_up;
          h_weight_down = h_all_vr_ehad_3p_dphi1_0tag_down;
        }
        else if (f_lephad_met_lep1_cos_dphi>=1. && f_lephad_met_lep1_cos_dphi<2) {
          h_weight = h_all_vr_ehad_3p_dphi2_0tag;
          h_weight_up = h_all_vr_ehad_3p_dphi2_0tag_up;
          h_weight_down = h_all_vr_ehad_3p_dphi2_0tag_down;
        }
        else if (f_lephad_met_lep1_cos_dphi>=2.) {
          h_weight = h_all_vr_ehad_3p_dphi34_0tag;
          h_weight_up = h_all_vr_ehad_3p_dphi34_0tag_up;
          h_weight_down = h_all_vr_ehad_3p_dphi34_0tag_down;
        }
      }
    }
  }

  if (h_weight!=0) {
    weight =  h_weight-> GetBinContent(h_weight->FindBin(f_tau_0_pt));
    weight_err = fabs(h_weight_up-> GetBinContent(h_weight_up->FindBin(f_tau_0_pt)) 
                     -h_weight_down-> GetBinContent(h_weight_down->FindBin(f_tau_0_pt)));
    weight_err /= 2.0;
  }
  ////////////////
  //
  // SYSTEMATICS
  //
  ////////////////
  // WFF
  if    ( (fSysName.Contains("ExtrapolationSFs_Btag_1up")    && f_n_bjets>0) ||
          (fSysName.Contains("ExtrapolationSFs_Btag1p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("ExtrapolationSFs_Btag3p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("ExtrapolationSFs_Bveto_1up")   && f_n_bjets==0 ) ||
          (fSysName.Contains("ExtrapolationSFs_Bveto1p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("ExtrapolationSFs_Bveto3p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    ) {
    //weight += weight_err;
    weight = 1.0+fabs(weight-1.0);
  }
  else if((fSysName.Contains("ExtrapolationSFs_Btag_1down")    && f_n_bjets>0) ||
          (fSysName.Contains("ExtrapolationSFs_Btag1p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("ExtrapolationSFs_Btag3p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("ExtrapolationSFs_Bveto_1down")   && f_n_bjets==0 ) ||
          (fSysName.Contains("ExtrapolationSFs_Bveto1p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("ExtrapolationSFs_Bveto3p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    ) {
    //weight -= weight_err;
    weight = 1.0-fabs(weight-1.0);
  }
  else
    weight = 1.0;
  DEBUGclass("returning");
  return weight;
}
//______________________________________________________________________________________________

extrapolationReweight::extrapolationReweight(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  fSysName = expression;

  // temporary pointer to ff files:
  TFile* tempFile=0;

  std::cout << "INFO: extrapolationReweight.cxx getting histograms from files. " << std::endl;
  ///////////////////////////////
  //
  //  Extrapolation
  //
  ///////////////////////////////
  // 2015+2016+2017
  // bveto ehad 1p
/*
  tempFile=TFile::Open("ExtrapolationSFs/WFFCorAllYearBveto1pehadBveto1pTauPt.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFFCorAllYearBveto1pehadBveto1pTauPt.root " << std::endl;
  else
  {
    h_151617_vr_ehad_1p_0tag = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_ehad_Bveto1pTauPt");            h_151617_vr_ehad_1p_0tag->SetDirectory(0);
    h_151617_vr_ehad_1p_0tag_up=(TH1F*)tempFile->Get("Bveto1pExtrapoSF_ehad_Bveto1pTauPt_up");        h_151617_vr_ehad_1p_0tag_up->SetDirectory(0);
    h_151617_vr_ehad_1p_0tag_down=(TH1F*)tempFile->Get("Bveto1pExtrapoSF_ehad_Bveto1pTauPt_down");    h_151617_vr_ehad_1p_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  // bveto ehad 3p
  tempFile=TFile::Open("ExtrapolationSFs/WFFCorAllYearBveto3pehadBveto3pTauPt.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pehadbvetoTauPt.root " << std::endl;
  else
  {
    h_151617_vr_ehad_3p_0tag = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_ehad_Bveto3pTauPt");            h_151617_vr_ehad_3p_0tag->SetDirectory(0);
    h_151617_vr_ehad_3p_0tag_up=(TH1F*)tempFile->Get("Bveto3pExtrapoSF_ehad_Bveto3pTauPt_up");        h_151617_vr_ehad_3p_0tag_up->SetDirectory(0);
    h_151617_vr_ehad_3p_0tag_down=(TH1F*)tempFile->Get("Bveto3pExtrapoSF_ehad_Bveto3pTauPt_down");    h_151617_vr_ehad_3p_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  // bveto muhad 1p
  tempFile=TFile::Open("ExtrapolationSFs/WFFCorAllYearBveto1pmuhadBveto1pTauPt.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto1pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_151617_vr_muhad_1p_0tag = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_muhad_Bveto1pTauPt");            h_151617_vr_muhad_1p_0tag->SetDirectory(0);
    h_151617_vr_muhad_1p_0tag_up=(TH1F*)tempFile->Get("Bveto1pExtrapoSF_muhad_Bveto1pTauPt_up");        h_151617_vr_muhad_1p_0tag_up->SetDirectory(0);
    h_151617_vr_muhad_1p_0tag_down=(TH1F*)tempFile->Get("Bveto1pExtrapoSF_muhad_Bveto1pTauPt_down");    h_151617_vr_muhad_1p_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  // bveto muhad 3p
  tempFile=TFile::Open("ExtrapolationSFs/WFFCorAllYearBveto3pmuhadBveto3pTauPt.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_151617_vr_muhad_3p_0tag = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_muhad_Bveto3pTauPt");            h_151617_vr_muhad_3p_0tag->SetDirectory(0);
    h_151617_vr_muhad_3p_0tag_up=(TH1F*)tempFile->Get("Bveto3pExtrapoSF_muhad_Bveto3pTauPt_up");        h_151617_vr_muhad_3p_0tag_up->SetDirectory(0);
    h_151617_vr_muhad_3p_0tag_down=(TH1F*)tempFile->Get("Bveto3pExtrapoSF_muhad_Bveto3pTauPt_down");    h_151617_vr_muhad_3p_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

}
*/
  // ehad bveto 1p
  tempFile=TFile::Open("ExtrapolationSFs/VRAllBveto1pehadTauPtFFBveto1pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_all_vr_ehad_1p_dphi1_0tag = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_ehad_TauPtFFBveto1pDphi1");        h_all_vr_ehad_1p_dphi1_0tag->SetDirectory(0);
    h_all_vr_ehad_1p_dphi1_0tag_up = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_ehad_TauPtFFBveto1pDphi1_up");        h_all_vr_ehad_1p_dphi1_0tag_up->SetDirectory(0);
    h_all_vr_ehad_1p_dphi1_0tag_down = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_ehad_TauPtFFBveto1pDphi1_down");        h_all_vr_ehad_1p_dphi1_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("ExtrapolationSFs/VRAllBveto1pehadTauPtFFBveto1pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_all_vr_ehad_1p_dphi2_0tag = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_ehad_TauPtFFBveto1pDphi2");        h_all_vr_ehad_1p_dphi2_0tag->SetDirectory(0);
    h_all_vr_ehad_1p_dphi2_0tag_up = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_ehad_TauPtFFBveto1pDphi2_up");        h_all_vr_ehad_1p_dphi2_0tag_up->SetDirectory(0);
    h_all_vr_ehad_1p_dphi2_0tag_down = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_ehad_TauPtFFBveto1pDphi2_down");        h_all_vr_ehad_1p_dphi2_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("ExtrapolationSFs/VRAllBveto1pehadTauPtFFBveto1pDphi34.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_all_vr_ehad_1p_dphi34_0tag = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_ehad_TauPtFFBveto1pDphi34");        h_all_vr_ehad_1p_dphi34_0tag->SetDirectory(0);
    h_all_vr_ehad_1p_dphi34_0tag_up = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_ehad_TauPtFFBveto1pDphi34_up");        h_all_vr_ehad_1p_dphi34_0tag_up->SetDirectory(0);
    h_all_vr_ehad_1p_dphi34_0tag_down = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_ehad_TauPtFFBveto1pDphi34_down");        h_all_vr_ehad_1p_dphi34_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  // ehad bveto 3p
  tempFile=TFile::Open("ExtrapolationSFs/VRAllBveto3pehadTauPtFFBveto3pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_all_vr_ehad_3p_dphi1_0tag = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_ehad_TauPtFFBveto3pDphi1");        h_all_vr_ehad_3p_dphi1_0tag->SetDirectory(0);
    h_all_vr_ehad_3p_dphi1_0tag_up = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_ehad_TauPtFFBveto3pDphi1_up");        h_all_vr_ehad_3p_dphi1_0tag_up->SetDirectory(0);
    h_all_vr_ehad_3p_dphi1_0tag_down = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_ehad_TauPtFFBveto3pDphi1_down");        h_all_vr_ehad_3p_dphi1_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("ExtrapolationSFs/VRAllBveto3pehadTauPtFFBveto3pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_all_vr_ehad_3p_dphi2_0tag = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_ehad_TauPtFFBveto3pDphi2");        h_all_vr_ehad_3p_dphi2_0tag->SetDirectory(0);
    h_all_vr_ehad_3p_dphi2_0tag_up = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_ehad_TauPtFFBveto3pDphi2_up");        h_all_vr_ehad_3p_dphi2_0tag_up->SetDirectory(0);
    h_all_vr_ehad_3p_dphi2_0tag_down = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_ehad_TauPtFFBveto3pDphi2_down");        h_all_vr_ehad_3p_dphi2_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("ExtrapolationSFs/VRAllBveto3pehadTauPtFFBveto3pDphi34.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_all_vr_ehad_3p_dphi34_0tag = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_ehad_TauPtFFBveto3pDphi34");        h_all_vr_ehad_3p_dphi34_0tag->SetDirectory(0);
    h_all_vr_ehad_3p_dphi34_0tag_up = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_ehad_TauPtFFBveto3pDphi34_up");        h_all_vr_ehad_3p_dphi34_0tag_up->SetDirectory(0);
    h_all_vr_ehad_3p_dphi34_0tag_down = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_ehad_TauPtFFBveto3pDphi34_down");        h_all_vr_ehad_3p_dphi34_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }


  // muhad bveto 1p
  tempFile=TFile::Open("ExtrapolationSFs/VRAllBveto1pmuhadTauPtFFBveto1pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_all_vr_muhad_1p_dphi1_0tag = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_muhad_TauPtFFBveto1pDphi1");        h_all_vr_muhad_1p_dphi1_0tag->SetDirectory(0);
    h_all_vr_muhad_1p_dphi1_0tag_up = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_muhad_TauPtFFBveto1pDphi1_up");        h_all_vr_muhad_1p_dphi1_0tag_up->SetDirectory(0);
    h_all_vr_muhad_1p_dphi1_0tag_down = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_muhad_TauPtFFBveto1pDphi1_down");        h_all_vr_muhad_1p_dphi1_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("ExtrapolationSFs/VRAllBveto1pmuhadTauPtFFBveto1pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_all_vr_muhad_1p_dphi2_0tag = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_muhad_TauPtFFBveto1pDphi2");        h_all_vr_muhad_1p_dphi2_0tag->SetDirectory(0);
    h_all_vr_muhad_1p_dphi2_0tag_up = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_muhad_TauPtFFBveto1pDphi2_up");        h_all_vr_muhad_1p_dphi2_0tag_up->SetDirectory(0);
    h_all_vr_muhad_1p_dphi2_0tag_down = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_muhad_TauPtFFBveto1pDphi2_down");        h_all_vr_muhad_1p_dphi2_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("ExtrapolationSFs/VRAllBveto1pmuhadTauPtFFBveto1pDphi34.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_all_vr_muhad_1p_dphi34_0tag = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_muhad_TauPtFFBveto1pDphi34");        h_all_vr_muhad_1p_dphi34_0tag->SetDirectory(0);
    h_all_vr_muhad_1p_dphi34_0tag_up = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_muhad_TauPtFFBveto1pDphi34_up");        h_all_vr_muhad_1p_dphi34_0tag_up->SetDirectory(0);
    h_all_vr_muhad_1p_dphi34_0tag_down = (TH1F*)tempFile->Get("Bveto1pExtrapoSF_muhad_TauPtFFBveto1pDphi34_down");        h_all_vr_muhad_1p_dphi34_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  // muhad bveto 3p
  tempFile=TFile::Open("ExtrapolationSFs/VRAllBveto3pmuhadTauPtFFBveto3pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_all_vr_muhad_3p_dphi1_0tag = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_muhad_TauPtFFBveto3pDphi1");        h_all_vr_muhad_3p_dphi1_0tag->SetDirectory(0);
    h_all_vr_muhad_3p_dphi1_0tag_up = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_muhad_TauPtFFBveto3pDphi1_up");        h_all_vr_muhad_3p_dphi1_0tag_up->SetDirectory(0);
    h_all_vr_muhad_3p_dphi1_0tag_down = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_muhad_TauPtFFBveto3pDphi1_down");        h_all_vr_muhad_3p_dphi1_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("ExtrapolationSFs/VRAllBveto3pmuhadTauPtFFBveto3pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_all_vr_muhad_3p_dphi2_0tag = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_muhad_TauPtFFBveto3pDphi2");        h_all_vr_muhad_3p_dphi2_0tag->SetDirectory(0);
    h_all_vr_muhad_3p_dphi2_0tag_up = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_muhad_TauPtFFBveto3pDphi2_up");        h_all_vr_muhad_3p_dphi2_0tag_up->SetDirectory(0);
    h_all_vr_muhad_3p_dphi2_0tag_down = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_muhad_TauPtFFBveto3pDphi2_down");        h_all_vr_muhad_3p_dphi2_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("ExtrapolationSFs/VRAllBveto3pmuhadTauPtFFBveto3pDphi34.root");
  if(!tempFile) std::cout << "ERROR cant open FF file VR15Bveto3pmuhadbvetoTauPt.root " << std::endl;
  else
  {
    h_all_vr_muhad_3p_dphi34_0tag = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_muhad_TauPtFFBveto3pDphi34");        h_all_vr_muhad_3p_dphi34_0tag->SetDirectory(0);
    h_all_vr_muhad_3p_dphi34_0tag_up = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_muhad_TauPtFFBveto3pDphi34_up");        h_all_vr_muhad_3p_dphi34_0tag_up->SetDirectory(0);
    h_all_vr_muhad_3p_dphi34_0tag_down = (TH1F*)tempFile->Get("Bveto3pExtrapoSF_muhad_TauPtFFBveto3pDphi34_down");        h_all_vr_muhad_3p_dphi34_0tag_down->SetDirectory(0);
    tempFile->Close(); delete tempFile; tempFile=0;
  }



}
//______________________________________________________________________________________________

const TString& extrapolationReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool extrapolationReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void extrapolationReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool extrapolationReweight::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void extrapolationReweight::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString extrapolationReweight::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool extrapolationReweight::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }

  if (!this->fSample->getTag("~isData", _isData)) {
    ERROR("tag isData missing");
    return false;
  }

  if (this->fTree->FindLeaf("NOMINAL_pileup_random_run_number")) this->x_run_number = new TTreeFormula("NOMINAL_pileup_random_run_number", "NOMINAL_pileup_random_run_number", this->fTree);
  else                                                           this->x_run_number = new TTreeFormula("run_number", "run_number", this->fTree);


  this->tau_0_phi               = new TTreeFormula( "tau_0_phi",     "tau_0_p4.Phi()",      this->fTree);
  this->tau_0_n_charged_tracks  = new TTreeFormula( "tau_0_n_charged_tracks","tau_0_n_charged_tracks", this->fTree);
  this->tau_0_pt                = new TTreeFormula( "tau_0_pt",     "tau_0_p4.Pt()",      this->fTree);
  this->lep_0_iso_Gradient      = new TTreeFormula( "lep_0_iso_Gradient",     "lep_0_iso_Gradient",      this->fTree);
  this->lephad_met_lep1_cos_dphi= new TTreeFormula( "lephad_met_lep1_cos_dphi", "lephad_met_lep1_cos_dphi", this->fTree);
  this->lephad_met_lep0_cos_dphi= new TTreeFormula( "lephad_met_lep0_cos_dphi", "lephad_met_lep0_cos_dphi", this->fTree);
  this->lep_0                   = new TTreeFormula( "lep_0",    "lep_0",      this->fTree);
  this->n_bjets                 = new TTreeFormula( "n_bjets",  "n_bjets",      this->fTree);
  //this->met_anti_iso_phi = new TTreeFormula( "met_anti_iso_phi", "met_anti_iso_phi", this->fTree);
  return true;
}

//______________________________________________________________________________________________

bool extrapolationReweight::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->lep_0;
  delete this->tau_0_phi;
  delete this->tau_0_pt;
  //delete this->met_anti_iso_phi;
  delete this->tau_0_n_charged_tracks;
  delete this->lephad_met_lep1_cos_dphi;
  delete this->lephad_met_lep0_cos_dphi;
  delete this->lep_0_iso_Gradient;
  delete this->n_bjets;

  return true;
}
