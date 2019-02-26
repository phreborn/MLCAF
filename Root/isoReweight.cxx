#include "BSMtautauCAF/isoReweight.h"
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

ClassImp(isoReweight)

//______________________________________________________________________________________________

isoReweight::isoReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

isoReweight::~isoReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* isoReweight::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("lep_0_phi"));
  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("lep_0_eta"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("lephad_met_lep0_cos_dphi"));
  bnames->Add(new TObjString("n_bjets"));

  if (isData()) {
    bnames->Add(new TObjString("run_number"));
  } else {
    bnames->Add(new TObjString("NOMINAL_pileup_random_run_number"));
  }



  return bnames;
}

//______________________________________________________________________________________________
double isoReweight::getValue() const {
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
  double f_lep_0_phi      = this->lep_0_phi->EvalInstance();
  int    f_lep_0          = this->lep_0->EvalInstance();
  float  f_lep_0_eta      = this->lep_0_eta->EvalInstance();
  float  f_lep_0_pt       = this->lep_0_pt->EvalInstance();
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  float  f_lephad_met_lep0_cos_dphi= this->lephad_met_lep0_cos_dphi->EvalInstance();

  // mean values:
  float ave_eta(1), ave_muon_bveto_eta(0),ave_muon_btag_eta(0);

  if(f_lep_0==2) ave_eta = f_n_bjets==0?ave_ele_bveto_eta : ave_ele_btag_eta;

  // FOR LEPTON ETA FF:
  float ff15_lep(0), errff15_lep(0);
  float ff17_lep(0), errff17_lep(0);
//  if( f_lep_0==1 && f_lep_0_pt<55. )//muon
//  {
//    ff_lep    = f_n_bjets==0?   h_ff_lfr_muhad_0tag_lowpt->GetBinContent( h_ff_lfr_muhad_0tag_lowpt->FindBin(fabs(f_lep_0_eta)) ):
//                                h_ff_lfr_muhad_1tag_lowpt->GetBinContent( h_ff_lfr_muhad_1tag_lowpt->FindBin(fabs(f_lep_0_eta)) );
//    errff_lep = f_n_bjets==0?   fabs( h_ff_lfr_muhad_0tag_lowpt_up->GetBinContent( h_ff_lfr_muhad_0tag_lowpt_up->FindBin(fabs(f_lep_0_eta)) ) -
//                                      h_ff_lfr_muhad_0tag_lowpt_down->GetBinContent( h_ff_lfr_muhad_0tag_lowpt_down->FindBin(fabs(f_lep_0_eta)) ) ) :
//                                fabs( h_ff_lfr_muhad_1tag_lowpt_up->GetBinContent( h_ff_lfr_muhad_1tag_lowpt_up->FindBin(fabs(f_lep_0_eta)) ) -
//                                      h_ff_lfr_muhad_1tag_lowpt_down->GetBinContent( h_ff_lfr_muhad_1tag_lowpt_down->FindBin(fabs(f_lep_0_eta)) ) );
//    errff_lep /= 2.;
//  }
//  else if( f_lep_0==1 && f_lep_0_pt>55. )
//  {
//    ff_lep    = f_n_bjets==0?   h_ff_lfr_muhad_0tag_highpt->GetBinContent( h_ff_lfr_muhad_0tag_highpt->FindBin(fabs(f_lep_0_eta)) ):
//                                h_ff_lfr_muhad_1tag_highpt->GetBinContent( h_ff_lfr_muhad_1tag_highpt->FindBin(fabs(f_lep_0_eta)) );
//    errff_lep = f_n_bjets==0?   fabs( h_ff_lfr_muhad_0tag_highpt_up->GetBinContent( h_ff_lfr_muhad_0tag_highpt_up->FindBin(fabs(f_lep_0_eta)) ) -
//                                      h_ff_lfr_muhad_0tag_highpt_down->GetBinContent( h_ff_lfr_muhad_0tag_highpt_down->FindBin(fabs(f_lep_0_eta)) ) ) :
//                                fabs( h_ff_lfr_muhad_1tag_highpt_up->GetBinContent( h_ff_lfr_muhad_1tag_highpt_up->FindBin(fabs(f_lep_0_eta)) ) -
//                                      h_ff_lfr_muhad_1tag_highpt_down->GetBinContent( h_ff_lfr_muhad_1tag_highpt_down->FindBin(fabs(f_lep_0_eta)) ) );
//    errff_lep /= 2.;
//  }
//  else if( f_lep_0==2 )
//  {
//    ff_lep    = f_n_bjets==0?   h_ff_lfr_ehad_0tag->GetBinContent( h_ff_lfr_ehad_0tag->FindBin(fabs(f_lep_0_eta)) ):
//                                h_ff_lfr_ehad_1tag->GetBinContent( h_ff_lfr_ehad_1tag->FindBin(fabs(f_lep_0_eta)) );
//    errff_lep = f_n_bjets==0?   fabs( h_ff_lfr_ehad_0tag_up->GetBinContent( h_ff_lfr_ehad_0tag_up->FindBin(fabs(f_lep_0_eta)) ) -
//                                      h_ff_lfr_ehad_0tag_down->GetBinContent( h_ff_lfr_ehad_0tag_down->FindBin(fabs(f_lep_0_eta)) ) ) :
//                                fabs( h_ff_lfr_ehad_1tag_up->GetBinContent( h_ff_lfr_ehad_1tag_up->FindBin(fabs(f_lep_0_eta)) ) -
//                                      h_ff_lfr_ehad_1tag_down->GetBinContent( h_ff_lfr_ehad_1tag_down->FindBin(fabs(f_lep_0_eta)) ) );
//    errff_lep /= 2.;
//  }

  // FOR LEPTON PT FF:
  // 2015+2016

  float ff15pt_lep(0), errff15pt_lep(0);
  if (f_lep_0_pt>=200) f_lep_0_pt=199;

  if( f_lep_0==1)//muon
  {
    ff15pt_lep    = f_n_bjets==0?   h_ff15_lfr_muhad_0tag_pt->GetBinContent( h_ff15_lfr_muhad_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                  h_ff15_lfr_muhad_1tag_pt->GetBinContent( h_ff15_lfr_muhad_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
    errff15pt_lep = f_n_bjets==0?   fabs( h_ff15_lfr_muhad_0tag_pt_up   ->GetBinContent( h_ff15_lfr_muhad_0tag_pt_up  ->FindBin(fabs(f_lep_0_pt)) ) -
                                        h_ff15_lfr_muhad_0tag_pt_down ->GetBinContent( h_ff15_lfr_muhad_0tag_pt_down->FindBin(fabs(f_lep_0_pt)) ) ) :
                                  fabs( h_ff15_lfr_muhad_1tag_pt_up   ->GetBinContent( h_ff15_lfr_muhad_1tag_pt_up  ->FindBin(fabs(f_lep_0_pt)) ) -
                                        h_ff15_lfr_muhad_1tag_pt_down ->GetBinContent( h_ff15_lfr_muhad_1tag_pt_down->FindBin(fabs(f_lep_0_pt)) ) );
    errff15pt_lep /= 2.;
  }
  else if( f_lep_0==2 )
  {
    ff15pt_lep    = f_n_bjets==0?   h_ff15_lfr_ehad_0tag_pt->GetBinContent( h_ff15_lfr_ehad_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                  h_ff15_lfr_ehad_1tag_pt->GetBinContent( h_ff15_lfr_ehad_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
    errff15pt_lep = f_n_bjets==0?   fabs( h_ff15_lfr_ehad_0tag_pt_up  ->GetBinContent( h_ff15_lfr_ehad_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                        h_ff15_lfr_ehad_0tag_pt_down->GetBinContent( h_ff15_lfr_ehad_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                  fabs( h_ff15_lfr_ehad_1tag_pt_up  ->GetBinContent( h_ff15_lfr_ehad_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                        h_ff15_lfr_ehad_1tag_pt_down->GetBinContent( h_ff15_lfr_ehad_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    errff15pt_lep /= 2.;
  }


  // 2017
  float ff17pt_lep(0), errff17pt_lep(0);
  if (f_lep_0_pt>=200) f_lep_0_pt=199;

  if( f_lep_0==1)//muon
  {
    ff17pt_lep    = f_n_bjets==0?   h_ff17_lfr_muhad_0tag_pt->GetBinContent( h_ff17_lfr_muhad_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                  h_ff17_lfr_muhad_1tag_pt->GetBinContent( h_ff17_lfr_muhad_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
    errff17pt_lep = f_n_bjets==0?   fabs( h_ff17_lfr_muhad_0tag_pt_up   ->GetBinContent( h_ff17_lfr_muhad_0tag_pt_up  ->FindBin(fabs(f_lep_0_pt)) ) -
                                        h_ff17_lfr_muhad_0tag_pt_down ->GetBinContent( h_ff17_lfr_muhad_0tag_pt_down->FindBin(fabs(f_lep_0_pt)) ) ) :
                                  fabs( h_ff17_lfr_muhad_1tag_pt_up   ->GetBinContent( h_ff17_lfr_muhad_1tag_pt_up  ->FindBin(fabs(f_lep_0_pt)) ) -
                                        h_ff17_lfr_muhad_1tag_pt_down ->GetBinContent( h_ff17_lfr_muhad_1tag_pt_down->FindBin(fabs(f_lep_0_pt)) ) );
    errff17pt_lep /= 2.;
  }
  else if( f_lep_0==2 )
  {
    ff17pt_lep    = f_n_bjets==0?   h_ff17_lfr_ehad_0tag_pt->GetBinContent( h_ff17_lfr_ehad_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                  h_ff17_lfr_ehad_1tag_pt->GetBinContent( h_ff17_lfr_ehad_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
    errff17pt_lep = f_n_bjets==0?   fabs( h_ff17_lfr_ehad_0tag_pt_up  ->GetBinContent( h_ff17_lfr_ehad_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                        h_ff17_lfr_ehad_0tag_pt_down->GetBinContent( h_ff17_lfr_ehad_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                  fabs( h_ff17_lfr_ehad_1tag_pt_up  ->GetBinContent( h_ff17_lfr_ehad_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                        h_ff17_lfr_ehad_1tag_pt_down->GetBinContent( h_ff17_lfr_ehad_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    errff17pt_lep /= 2.;
  }
  
  float dphi_lepmet = f_lephad_met_lep0_cos_dphi;

  float dphi15corr_lep(1), errdphi15corr_lep(0); // only for electron!!!
  float dphi17corr_lep(1), errdphi17corr_lep(0); // only for electron!!!
/*  if( f_lep_0==2 )
  {
    dphicorr_lep    = f_n_bjets==0?   h_dphicorr_lfr_ehad_0tag->GetBinContent( h_dphicorr_lfr_ehad_0tag->FindBin(fabs(dphi_lepmet)) ):
                                      h_dphicorr_lfr_ehad_1tag->GetBinContent( h_dphicorr_lfr_ehad_1tag->FindBin(fabs(dphi_lepmet)) );
    errdphicorr_lep = f_n_bjets==0?   fabs( h_dphicorr_lfr_ehad_0tag_up  ->GetBinContent( h_dphicorr_lfr_ehad_0tag_up   ->FindBin(fabs(dphi_lepmet)) ) -
                                            h_dphicorr_lfr_ehad_0tag_down->GetBinContent( h_dphicorr_lfr_ehad_0tag_down ->FindBin(fabs(dphi_lepmet)) ) ) :
                                      fabs( h_dphicorr_lfr_ehad_1tag_up  ->GetBinContent( h_dphicorr_lfr_ehad_1tag_up   ->FindBin(fabs(dphi_lepmet)) ) -
                                            h_dphicorr_lfr_ehad_1tag_down->GetBinContent( h_dphicorr_lfr_ehad_1tag_down ->FindBin(fabs(dphi_lepmet)) ) );
    errdphicorr_lep /= 2.;
  }
*/

  // FOR LEPTON PT * DPHI 2DFF:
  // 2015+2016
  float ff15ptdphi_lep(1), errff15ptdphi_lep(0);
  if (f_lep_0_pt>=200) f_lep_0_pt=199;

  if( f_lep_0==1 ) //muon
  {
    if(dphi_lepmet<0.5)
    {
      ff15ptdphi_lep    = f_n_bjets==0?   h_ff15_lfr_muhad_dphi1_0tag_pt->GetBinContent( h_ff15_lfr_muhad_dphi1_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff15_lfr_muhad_dphi1_1tag_pt->GetBinContent( h_ff15_lfr_muhad_dphi1_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff15ptdphi_lep = f_n_bjets==0?   fabs( h_ff15_lfr_muhad_dphi1_0tag_pt_up  ->GetBinContent( h_ff15_lfr_muhad_dphi1_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_muhad_dphi1_0tag_pt_down->GetBinContent( h_ff15_lfr_muhad_dphi1_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff15_lfr_muhad_dphi1_1tag_pt_up  ->GetBinContent( h_ff15_lfr_muhad_dphi1_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_muhad_dphi1_1tag_pt_down->GetBinContent( h_ff15_lfr_muhad_dphi1_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    if(dphi_lepmet>=0.5&&dphi_lepmet<1.)
    {
      ff15ptdphi_lep    = f_n_bjets==0?   h_ff15_lfr_muhad_dphi2_0tag_pt->GetBinContent( h_ff15_lfr_muhad_dphi2_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff15_lfr_muhad_dphi2_1tag_pt->GetBinContent( h_ff15_lfr_muhad_dphi2_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff15ptdphi_lep = f_n_bjets==0?   fabs( h_ff15_lfr_muhad_dphi2_0tag_pt_up  ->GetBinContent( h_ff15_lfr_muhad_dphi2_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_muhad_dphi2_0tag_pt_down->GetBinContent( h_ff15_lfr_muhad_dphi2_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff15_lfr_muhad_dphi2_1tag_pt_up  ->GetBinContent( h_ff15_lfr_muhad_dphi2_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_muhad_dphi2_1tag_pt_down->GetBinContent( h_ff15_lfr_muhad_dphi2_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    if(dphi_lepmet>=1.&&dphi_lepmet<2.)
    {
      ff15ptdphi_lep    = f_n_bjets==0?   h_ff15_lfr_muhad_dphi3_0tag_pt->GetBinContent( h_ff15_lfr_muhad_dphi3_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff15_lfr_muhad_dphi3_1tag_pt->GetBinContent( h_ff15_lfr_muhad_dphi3_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff15ptdphi_lep = f_n_bjets==0?   fabs( h_ff15_lfr_muhad_dphi3_0tag_pt_up  ->GetBinContent( h_ff15_lfr_muhad_dphi3_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_muhad_dphi3_0tag_pt_down->GetBinContent( h_ff15_lfr_muhad_dphi3_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff15_lfr_muhad_dphi3_1tag_pt_up  ->GetBinContent( h_ff15_lfr_muhad_dphi3_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_muhad_dphi3_1tag_pt_down->GetBinContent( h_ff15_lfr_muhad_dphi3_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    if(dphi_lepmet>=2.)
    {
      ff15ptdphi_lep    = f_n_bjets==0?   h_ff15_lfr_muhad_dphi4_0tag_pt->GetBinContent( h_ff15_lfr_muhad_dphi4_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff15_lfr_muhad_dphi3_1tag_pt->GetBinContent( h_ff15_lfr_muhad_dphi3_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff15ptdphi_lep = f_n_bjets==0?   fabs( h_ff15_lfr_muhad_dphi4_0tag_pt_up  ->GetBinContent( h_ff15_lfr_muhad_dphi4_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_muhad_dphi4_0tag_pt_down->GetBinContent( h_ff15_lfr_muhad_dphi4_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff15_lfr_muhad_dphi3_1tag_pt_up  ->GetBinContent( h_ff15_lfr_muhad_dphi3_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_muhad_dphi3_1tag_pt_down->GetBinContent( h_ff15_lfr_muhad_dphi3_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    errff15ptdphi_lep /= 2.;
  }
  else if( f_lep_0==2 ) //electron
  {
    if(dphi_lepmet<0.5)
    {
      ff15ptdphi_lep    = f_n_bjets==0?   h_ff15_lfr_ehad_dphi1_0tag_pt->GetBinContent( h_ff15_lfr_ehad_dphi1_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff15_lfr_ehad_dphi1_1tag_pt->GetBinContent( h_ff15_lfr_ehad_dphi1_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff15ptdphi_lep = f_n_bjets==0?   fabs( h_ff15_lfr_ehad_dphi1_0tag_pt_up  ->GetBinContent( h_ff15_lfr_ehad_dphi1_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_ehad_dphi1_0tag_pt_down->GetBinContent( h_ff15_lfr_ehad_dphi1_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff15_lfr_ehad_dphi1_1tag_pt_up  ->GetBinContent( h_ff15_lfr_ehad_dphi1_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_ehad_dphi1_1tag_pt_down->GetBinContent( h_ff15_lfr_ehad_dphi1_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    if(dphi_lepmet>=0.5&&dphi_lepmet<1.)
    {
      ff15ptdphi_lep    = f_n_bjets==0?   h_ff15_lfr_ehad_dphi2_0tag_pt->GetBinContent( h_ff15_lfr_ehad_dphi2_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff15_lfr_ehad_dphi2_1tag_pt->GetBinContent( h_ff15_lfr_ehad_dphi2_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff15ptdphi_lep = f_n_bjets==0?   fabs( h_ff15_lfr_ehad_dphi2_0tag_pt_up  ->GetBinContent( h_ff15_lfr_ehad_dphi2_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_ehad_dphi2_0tag_pt_down->GetBinContent( h_ff15_lfr_ehad_dphi2_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff15_lfr_ehad_dphi2_1tag_pt_up  ->GetBinContent( h_ff15_lfr_ehad_dphi2_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_ehad_dphi2_1tag_pt_down->GetBinContent( h_ff15_lfr_ehad_dphi2_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    if(dphi_lepmet>=1.&&dphi_lepmet<2.)
    {
      ff15ptdphi_lep    = f_n_bjets==0?   h_ff15_lfr_ehad_dphi3_0tag_pt->GetBinContent( h_ff15_lfr_ehad_dphi3_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff15_lfr_ehad_dphi3_1tag_pt->GetBinContent( h_ff15_lfr_ehad_dphi3_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff15ptdphi_lep = f_n_bjets==0?   fabs( h_ff15_lfr_ehad_dphi3_0tag_pt_up  ->GetBinContent( h_ff15_lfr_ehad_dphi3_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_ehad_dphi3_0tag_pt_down->GetBinContent( h_ff15_lfr_ehad_dphi3_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff15_lfr_ehad_dphi3_1tag_pt_up  ->GetBinContent( h_ff15_lfr_ehad_dphi3_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_ehad_dphi3_1tag_pt_down->GetBinContent( h_ff15_lfr_ehad_dphi3_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    if(dphi_lepmet>=2.)
    {
      ff15ptdphi_lep    = f_n_bjets==0?   h_ff15_lfr_ehad_dphi4_0tag_pt->GetBinContent( h_ff15_lfr_ehad_dphi4_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff15_lfr_ehad_dphi3_1tag_pt->GetBinContent( h_ff15_lfr_ehad_dphi3_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff15ptdphi_lep = f_n_bjets==0?   fabs( h_ff15_lfr_ehad_dphi4_0tag_pt_up  ->GetBinContent( h_ff15_lfr_ehad_dphi4_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_ehad_dphi4_0tag_pt_down->GetBinContent( h_ff15_lfr_ehad_dphi4_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff15_lfr_ehad_dphi3_1tag_pt_up  ->GetBinContent( h_ff15_lfr_ehad_dphi3_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff15_lfr_ehad_dphi3_1tag_pt_down->GetBinContent( h_ff15_lfr_ehad_dphi3_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    errff15ptdphi_lep /= 2.;
  }



  // lep ff15 sys
  if      ( (fSysName.Contains("FakeFactor_LepElBveto_1up") && f_lep_0==2 && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_LepElBtag_1up") && f_lep_0==2 && f_n_bjets>0) ||
            (fSysName.Contains("FakeFactor_LepMuBveto_1up") && f_lep_0==1 && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_LepMuBtag_1up") && f_lep_0==1 && f_n_bjets>0) ) {
    ff15_lep += errff15_lep;
    ff15pt_lep += errff15pt_lep;
    ff15ptdphi_lep += errff15ptdphi_lep;
  }
  else if(  (fSysName.Contains("FakeFactor_LepElBveto_1down") && f_lep_0==2 && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_LepElBtag_1down") && f_lep_0==2 && f_n_bjets>0) ||
            (fSysName.Contains("FakeFactor_LepMuBveto_1down") && f_lep_0==1 && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_LepMuBtag_1down") && f_lep_0==1 && f_n_bjets>0) ) {
    ff15_lep -= errff15_lep;
    ff15pt_lep -= errff15pt_lep;
    ff15ptdphi_lep -= errff15ptdphi_lep;
  }

  if( (fSysName.Contains("FakeLep_DphiElBvetoSysUp") && f_lep_0==2 && f_n_bjets==0) ||
      (fSysName.Contains("FakeLep_DphiElBtagSysUp") && f_lep_0==2 && f_n_bjets>0)  ) {
    dphi15corr_lep += errdphi15corr_lep;
  }
  else if(  (fSysName.Contains("FakeLep_DphiElBvetoSysDo") && f_lep_0==2 && f_n_bjets==0) ||
            (fSysName.Contains("FakeLep_DphiElBtagSysDo") && f_lep_0==2 && f_n_bjets>0) ) {
    dphi15corr_lep -= errdphi15corr_lep;
  }

  // 2017

  float ff17ptdphi_lep(1), errff17ptdphi_lep(0);
  if (f_lep_0_pt>=200) f_lep_0_pt=199;

  if( f_lep_0==1 ) //muon
  {
    if(dphi_lepmet<0.5)
    {
      ff17ptdphi_lep    = f_n_bjets==0?   h_ff17_lfr_muhad_dphi1_0tag_pt->GetBinContent( h_ff17_lfr_muhad_dphi1_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff17_lfr_muhad_dphi1_1tag_pt->GetBinContent( h_ff17_lfr_muhad_dphi1_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff17ptdphi_lep = f_n_bjets==0?   fabs( h_ff17_lfr_muhad_dphi1_0tag_pt_up  ->GetBinContent( h_ff17_lfr_muhad_dphi1_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_muhad_dphi1_0tag_pt_down->GetBinContent( h_ff17_lfr_muhad_dphi1_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff17_lfr_muhad_dphi1_1tag_pt_up  ->GetBinContent( h_ff17_lfr_muhad_dphi1_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_muhad_dphi1_1tag_pt_down->GetBinContent( h_ff17_lfr_muhad_dphi1_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    if(dphi_lepmet>=0.5&&dphi_lepmet<1.)
    {
      ff17ptdphi_lep    = f_n_bjets==0?   h_ff17_lfr_muhad_dphi2_0tag_pt->GetBinContent( h_ff17_lfr_muhad_dphi2_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff17_lfr_muhad_dphi2_1tag_pt->GetBinContent( h_ff17_lfr_muhad_dphi2_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff17ptdphi_lep = f_n_bjets==0?   fabs( h_ff17_lfr_muhad_dphi2_0tag_pt_up  ->GetBinContent( h_ff17_lfr_muhad_dphi2_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_muhad_dphi2_0tag_pt_down->GetBinContent( h_ff17_lfr_muhad_dphi2_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff17_lfr_muhad_dphi2_1tag_pt_up  ->GetBinContent( h_ff17_lfr_muhad_dphi2_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_muhad_dphi2_1tag_pt_down->GetBinContent( h_ff17_lfr_muhad_dphi2_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    if(dphi_lepmet>=1.&&dphi_lepmet<2.)
    {
      ff17ptdphi_lep    = f_n_bjets==0?   h_ff17_lfr_muhad_dphi3_0tag_pt->GetBinContent( h_ff17_lfr_muhad_dphi3_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff17_lfr_muhad_dphi3_1tag_pt->GetBinContent( h_ff17_lfr_muhad_dphi3_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff17ptdphi_lep = f_n_bjets==0?   fabs( h_ff17_lfr_muhad_dphi3_0tag_pt_up  ->GetBinContent( h_ff17_lfr_muhad_dphi3_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_muhad_dphi3_0tag_pt_down->GetBinContent( h_ff17_lfr_muhad_dphi3_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff17_lfr_muhad_dphi3_1tag_pt_up  ->GetBinContent( h_ff17_lfr_muhad_dphi3_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_muhad_dphi3_1tag_pt_down->GetBinContent( h_ff17_lfr_muhad_dphi3_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    if(dphi_lepmet>=2.)
    {
      ff17ptdphi_lep    = f_n_bjets==0?   h_ff17_lfr_muhad_dphi4_0tag_pt->GetBinContent( h_ff17_lfr_muhad_dphi4_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff17_lfr_muhad_dphi3_1tag_pt->GetBinContent( h_ff17_lfr_muhad_dphi3_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff17ptdphi_lep = f_n_bjets==0?   fabs( h_ff17_lfr_muhad_dphi4_0tag_pt_up  ->GetBinContent( h_ff17_lfr_muhad_dphi4_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_muhad_dphi4_0tag_pt_down->GetBinContent( h_ff17_lfr_muhad_dphi4_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff17_lfr_muhad_dphi3_1tag_pt_up  ->GetBinContent( h_ff17_lfr_muhad_dphi3_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_muhad_dphi3_1tag_pt_down->GetBinContent( h_ff17_lfr_muhad_dphi3_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    errff17ptdphi_lep /= 2.;
  }
  else if( f_lep_0==2 ) //electron
  {
    if(dphi_lepmet<0.5)
    {
      ff17ptdphi_lep    = f_n_bjets==0?   h_ff17_lfr_ehad_dphi1_0tag_pt->GetBinContent( h_ff17_lfr_ehad_dphi1_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff17_lfr_ehad_dphi1_1tag_pt->GetBinContent( h_ff17_lfr_ehad_dphi1_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff17ptdphi_lep = f_n_bjets==0?   fabs( h_ff17_lfr_ehad_dphi1_0tag_pt_up  ->GetBinContent( h_ff17_lfr_ehad_dphi1_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_ehad_dphi1_0tag_pt_down->GetBinContent( h_ff17_lfr_ehad_dphi1_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff17_lfr_ehad_dphi1_1tag_pt_up  ->GetBinContent( h_ff17_lfr_ehad_dphi1_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_ehad_dphi1_1tag_pt_down->GetBinContent( h_ff17_lfr_ehad_dphi1_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    if(dphi_lepmet>=0.5&&dphi_lepmet<1.)
    {
      ff17ptdphi_lep    = f_n_bjets==0?   h_ff17_lfr_ehad_dphi2_0tag_pt->GetBinContent( h_ff17_lfr_ehad_dphi2_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff17_lfr_ehad_dphi2_1tag_pt->GetBinContent( h_ff17_lfr_ehad_dphi2_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff17ptdphi_lep = f_n_bjets==0?   fabs( h_ff17_lfr_ehad_dphi2_0tag_pt_up  ->GetBinContent( h_ff17_lfr_ehad_dphi2_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_ehad_dphi2_0tag_pt_down->GetBinContent( h_ff17_lfr_ehad_dphi2_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff17_lfr_ehad_dphi2_1tag_pt_up  ->GetBinContent( h_ff17_lfr_ehad_dphi2_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_ehad_dphi2_1tag_pt_down->GetBinContent( h_ff17_lfr_ehad_dphi2_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    if(dphi_lepmet>=1.&&dphi_lepmet<2.)
    {
      ff17ptdphi_lep    = f_n_bjets==0?   h_ff17_lfr_ehad_dphi3_0tag_pt->GetBinContent( h_ff17_lfr_ehad_dphi3_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff17_lfr_ehad_dphi3_1tag_pt->GetBinContent( h_ff17_lfr_ehad_dphi3_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff17ptdphi_lep = f_n_bjets==0?   fabs( h_ff17_lfr_ehad_dphi3_0tag_pt_up  ->GetBinContent( h_ff17_lfr_ehad_dphi3_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_ehad_dphi3_0tag_pt_down->GetBinContent( h_ff17_lfr_ehad_dphi3_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff17_lfr_ehad_dphi3_1tag_pt_up  ->GetBinContent( h_ff17_lfr_ehad_dphi3_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_ehad_dphi3_1tag_pt_down->GetBinContent( h_ff17_lfr_ehad_dphi3_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    if(dphi_lepmet>=2.)
    {
      ff17ptdphi_lep    = f_n_bjets==0?   h_ff17_lfr_ehad_dphi4_0tag_pt->GetBinContent( h_ff17_lfr_ehad_dphi4_0tag_pt->FindBin(fabs(f_lep_0_pt)) ):
                                        h_ff17_lfr_ehad_dphi3_1tag_pt->GetBinContent( h_ff17_lfr_ehad_dphi3_1tag_pt->FindBin(fabs(f_lep_0_pt)) );
      errff17ptdphi_lep = f_n_bjets==0?   fabs( h_ff17_lfr_ehad_dphi4_0tag_pt_up  ->GetBinContent( h_ff17_lfr_ehad_dphi4_0tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_ehad_dphi4_0tag_pt_down->GetBinContent( h_ff17_lfr_ehad_dphi4_0tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) ) :
                                        fabs( h_ff17_lfr_ehad_dphi3_1tag_pt_up  ->GetBinContent( h_ff17_lfr_ehad_dphi3_1tag_pt_up   ->FindBin(fabs(f_lep_0_pt)) ) -
                                              h_ff17_lfr_ehad_dphi3_1tag_pt_down->GetBinContent( h_ff17_lfr_ehad_dphi3_1tag_pt_down ->FindBin(fabs(f_lep_0_pt)) ) );
    }
    errff17ptdphi_lep /= 2.;
  }



  // lep ff17 sys
  if      ( (fSysName.Contains("FakeFactor_LepElBveto_1up") && f_lep_0==2 && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_LepElBtag_1up") && f_lep_0==2 && f_n_bjets>0) ||
            (fSysName.Contains("FakeFactor_LepMuBveto_1up") && f_lep_0==1 && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_LepMuBtag_1up") && f_lep_0==1 && f_n_bjets>0) ) {
    ff17_lep += errff17_lep;
    ff17pt_lep += errff17pt_lep;
    ff17ptdphi_lep += errff17ptdphi_lep;
  }
  else if(  (fSysName.Contains("FakeFactor_LepElBveto_1down") && f_lep_0==2 && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_LepElBtag_1down") && f_lep_0==2 && f_n_bjets>0) ||
            (fSysName.Contains("FakeFactor_LepMuBveto_1down") && f_lep_0==1 && f_n_bjets==0) ||
            (fSysName.Contains("FakeFactor_LepMuBtag_1down") && f_lep_0==1 && f_n_bjets>0) ) {
    ff17_lep -= errff17_lep;
    ff17pt_lep -= errff17pt_lep;
    ff17ptdphi_lep -= errff17ptdphi_lep;
  }

  if( (fSysName.Contains("FakeLep_DphiElBvetoSysUp") && f_lep_0==2 && f_n_bjets==0) ||
      (fSysName.Contains("FakeLep_DphiElBtagSysUp") && f_lep_0==2 && f_n_bjets>0)  ) {
    dphi17corr_lep += errdphi17corr_lep;
  }
  else if(  (fSysName.Contains("FakeLep_DphiElBvetoSysDo") && f_lep_0==2 && f_n_bjets==0) ||
            (fSysName.Contains("FakeLep_DphiElBtagSysDo") && f_lep_0==2 && f_n_bjets>0) ) {
    dphi17corr_lep -= errdphi17corr_lep;
  }
  DEBUGclass("returning");
  double retval=1.;

  TString ff="";
  if(!this->fSample->getTag("~myLeptonFF",ff)) std::cout<<"Why cant I get ff name!!!\n";
  if(ff=="FFPT")  
  {
    if(this->x_run_number->EvalInstance() <= LIMIT_2016) retval = ff15pt_lep;
    else if(this->x_run_number->EvalInstance() > LIMIT_2016 && this->x_run_number->EvalInstance() <= LIMIT_2017) retval = ff17pt_lep;
  }
  else if(ff=="FF2DPTDPHI") 
  {
//    if(this->x_run_number->EvalInstance() <= LIMIT_2016) retval = f_lep_0==2? ff15ptdphi_lep : ff15pt_lep;  
//    else if(this->x_run_number->EvalInstance() > LIMIT_2016 && this->x_run_number->EvalInstance() <= LIMIT_2017) retval = f_lep_0==2? ff17ptdphi_lep : ff17pt_lep;
    if(this->x_run_number->EvalInstance() <= LIMIT_2016) retval = ff15ptdphi_lep;  
    else if(this->x_run_number->EvalInstance() > LIMIT_2016 && this->x_run_number->EvalInstance() <= LIMIT_2017) retval = ff17ptdphi_lep;
  }
//  else if(ff=="FFPTDPHI")
//  {
//    retval = ffpt_lep * dphicorr_lep;
    //std::cout<<"returning ff= " << ffpt_lep << "   corr= " << dphicorr_lep << std::endl;
//  }
//  else if(ff=="FFETA")  retval = ff_lep;
//  else if(ff=="FFETAPTDPHI")  retval =  ffpt_lep * (f_lep_0==2?ff_lep / ave_eta * dphicorr_lep:1);
//  else if(ff=="FF2DPTDPHI") retval = f_lep_0==2? ffptdphi_lep : ffpt_lep;
//  if (f_lep_0==2)
//  {
//  std::cout<<"dphi lepmet = " << dphi_lepmet << std::endl;
//  std::cout<<"returning ff= " << retval << std::endl;
//  std::cout<<"returning ff= " << (f_lep_0==2? ffptdphi_lep : ffpt_lep) << std::endl;
//}


  return retval;
}
//______________________________________________________________________________________________

isoReweight::isoReweight(const TString& expression) : LepHadObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  fSysName = expression;

  // when files are closed histograms also dissapear, so detatch them and keep in this directory:
  m_histoDir = new TDirectory("ffhistoDir","ffhistoDir");
  // temporary pointer to ff files:
  TFile* tempFile=0;

  std::cout << "INFO: isoReweight.cxx getting histograms from files. " << std::endl;
  ///////////////////////////////
  //
  //  Lepton FF
  //
  ///////////////////////////////

  /*tempFile=TFile::Open("FakeFactors/LFRBvetoehadLeptonEtaELEFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFRBvetoehadLeptonEtaELEFF.root " << std::endl;
  else
  {
    h_ff_lfr_ehad_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_LeptonEtaELEFF");             h_ff_lfr_ehad_0tag->SetDirectory(m_histoDir);
    h_ff_lfr_ehad_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonEtaELEFF_up");         h_ff_lfr_ehad_0tag_up->SetDirectory(m_histoDir);
    h_ff_lfr_ehad_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonEtaELEFF_down");     h_ff_lfr_ehad_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFRBtagehadLeptonEtaELEFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFRBtagehadLeptonEtaELEFF.root " << std::endl;
  else
  {
    h_ff_lfr_ehad_1tag = (TH1F*)tempFile->Get("BtagFF_ehad_LeptonEtaELEFF");            h_ff_lfr_ehad_1tag->SetDirectory(m_histoDir);
    h_ff_lfr_ehad_1tag_up=(TH1F*)tempFile->Get("BtagFF_ehad_LeptonEtaELEFF_up");        h_ff_lfr_ehad_1tag_up->SetDirectory(m_histoDir);
    h_ff_lfr_ehad_1tag_down=(TH1F*)tempFile->Get("BtagFF_ehad_LeptonEtaELEFF_down");    h_ff_lfr_ehad_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFRBvetomuhadLeptonEtaMUONLOWFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFRBvetomuhadLeptonEtaMUONLOWFF.root " << std::endl;
  else
  {
    h_ff_lfr_muhad_0tag_lowpt = (TH1F*)tempFile->Get("BvetoFF_muhad_LeptonEtaMUONLOWFF");            h_ff_lfr_muhad_0tag_lowpt->SetDirectory(m_histoDir);
    h_ff_lfr_muhad_0tag_lowpt_up=(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonEtaMUONLOWFF_up");        h_ff_lfr_muhad_0tag_lowpt_up->SetDirectory(m_histoDir);
    h_ff_lfr_muhad_0tag_lowpt_down=(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonEtaMUONLOWFF_down");    h_ff_lfr_muhad_0tag_lowpt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFRBvetomuhadLeptonEtaMUONHIGHBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFRBvetomuhadLeptonEtaMUONHIGHBVETOFF.root " << std::endl;
  else
  {
    h_ff_lfr_muhad_0tag_highpt = (TH1F*)tempFile->Get("BvetoFF_muhad_LeptonEtaMUONHIGHBVETOFF");            h_ff_lfr_muhad_0tag_highpt->SetDirectory(m_histoDir);
    h_ff_lfr_muhad_0tag_highpt_up=(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonEtaMUONHIGHBVETOFF_up");        h_ff_lfr_muhad_0tag_highpt_up->SetDirectory(m_histoDir);
    h_ff_lfr_muhad_0tag_highpt_down=(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonEtaMUONHIGHBVETOFF_down");    h_ff_lfr_muhad_0tag_highpt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFRBtagmuhadLeptonEtaMUONLOWFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFRBtagmuhadLeptonEtaMUONLOWFF.root " << std::endl;
  else
  {
    h_ff_lfr_muhad_1tag_lowpt = (TH1F*)tempFile->Get("BtagFF_muhad_LeptonEtaMUONLOWFF");            h_ff_lfr_muhad_1tag_lowpt->SetDirectory(m_histoDir);
    h_ff_lfr_muhad_1tag_lowpt_up=(TH1F*)tempFile->Get("BtagFF_muhad_LeptonEtaMUONLOWFF_up");        h_ff_lfr_muhad_1tag_lowpt_up->SetDirectory(m_histoDir);
    h_ff_lfr_muhad_1tag_lowpt_down=(TH1F*)tempFile->Get("BtagFF_muhad_LeptonEtaMUONLOWFF_down");    h_ff_lfr_muhad_1tag_lowpt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFRBtagmuhadLeptonEtaMUONHIGHBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFRBtagmuhadLeptonEtaMUONHIGHBTAGFF.root " << std::endl;
  else
  {
    h_ff_lfr_muhad_1tag_highpt = (TH1F*)tempFile->Get("BtagFF_muhad_LeptonEtaMUONHIGHBTAGFF");            h_ff_lfr_muhad_1tag_highpt->SetDirectory(m_histoDir);
    h_ff_lfr_muhad_1tag_highpt_up=(TH1F*)tempFile->Get("BtagFF_muhad_LeptonEtaMUONHIGHBTAGFF_up");        h_ff_lfr_muhad_1tag_highpt_up->SetDirectory(m_histoDir);
    h_ff_lfr_muhad_1tag_highpt_down=(TH1F*)tempFile->Get("BtagFF_muhad_LeptonEtaMUONHIGHBTAGFF_down");    h_ff_lfr_muhad_1tag_highpt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }*/


  ///////////////////////////////
  //
  //  Lepton FF in lepton pt
  //
  ///////////////////////////////
  //2015+2016
  tempFile=TFile::Open("FakeFactors/LFR15BvetoehadLeptonPtELEBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BvetoehadLeptonPtELEBVETOFF.root " << std::endl;
  else
  {
    h_ff15_lfr_ehad_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtELEBVETOFF");              h_ff15_lfr_ehad_0tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtELEBVETOFF_up");           h_ff15_lfr_ehad_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtELEBVETOFF_down");         h_ff15_lfr_ehad_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BtagehadLeptonPtELEBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BtagehadLeptonPtELEBTAGFF.root " << std::endl;
  else
  {
    h_ff15_lfr_ehad_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtELEBTAGFF");             h_ff15_lfr_ehad_1tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtELEBTAGFF_up");          h_ff15_lfr_ehad_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtELEBTAGFF_down");        h_ff15_lfr_ehad_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BvetomuhadLeptonPtMUONFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BvetomuhadLeptonPtMUONFF.root " << std::endl;
  else
  {
    h_ff15_lfr_muhad_0tag_pt      =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtMUONFF");            h_ff15_lfr_muhad_0tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_0tag_pt_up   =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtMUONFF_up");            h_ff15_lfr_muhad_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_0tag_pt_down =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtMUONFF_down");          h_ff15_lfr_muhad_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BtagmuhadLeptonPtMUONFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BtagmuhadLeptonPtMUONFF.root " << std::endl;
  else
  {
    h_ff15_lfr_muhad_1tag_pt      =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtMUONFF");            h_ff15_lfr_muhad_1tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_1tag_pt_up   =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtMUONFF_up");         h_ff15_lfr_muhad_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_1tag_pt_down =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtMUONFF_down");       h_ff15_lfr_muhad_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  // 2017
  tempFile=TFile::Open("FakeFactors/LFR17BvetoehadLeptonPtELEBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BvetoehadLeptonPtELEBVETOFF.root " << std::endl;
  else
  {
    h_ff17_lfr_ehad_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtELEBVETOFF");              h_ff17_lfr_ehad_0tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtELEBVETOFF_up");           h_ff17_lfr_ehad_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtELEBVETOFF_down");         h_ff17_lfr_ehad_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BtagehadLeptonPtELEBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BtagehadLeptonPtELEBTAGFF.root " << std::endl;
  else
  {
    h_ff17_lfr_ehad_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtELEBTAGFF");             h_ff17_lfr_ehad_1tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtELEBTAGFF_up");          h_ff17_lfr_ehad_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtELEBTAGFF_down");        h_ff17_lfr_ehad_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BvetomuhadLeptonPtMUONFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BvetomuhadLeptonPtMUONFF.root " << std::endl;
  else
  {
    h_ff17_lfr_muhad_0tag_pt      =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtMUONFF");            h_ff17_lfr_muhad_0tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_0tag_pt_up   =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtMUONFF_up");            h_ff17_lfr_muhad_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_0tag_pt_down =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtMUONFF_down");          h_ff17_lfr_muhad_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BtagmuhadLeptonPtMUONFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BtagmuhadLeptonPtMUONFF.root " << std::endl;
  else
  {
    h_ff17_lfr_muhad_1tag_pt      =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtMUONFF");            h_ff17_lfr_muhad_1tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_1tag_pt_up   =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtMUONFF_up");         h_ff17_lfr_muhad_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_1tag_pt_down =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtMUONFF_down");       h_ff17_lfr_muhad_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }


  ///////////////////////////////
  //
  // Dhi Correction for Lepton FF in lepton pt
  //
  ///////////////////////////////
/*  tempFile=TFile::Open("FakeFactors/LFRdphiBvetoehadLepMETDphiBvetoCorrectionELE.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFRdphiBvetoehadLepMETDphiBvetoCorrectionELE.root " << std::endl;
  else
  {
    h_dphicorr_lfr_ehad_0tag     =(TH1F*)tempFile->Get("dphicorr_Bveto_ehad_LepMETDphiBvetoCorrectionELE");              h_dphicorr_lfr_ehad_0tag     ->SetDirectory(m_histoDir);
    h_dphicorr_lfr_ehad_0tag_up  =(TH1F*)tempFile->Get("dphicorr_Bveto_ehad_LepMETDphiBvetoCorrectionELE_up");           h_dphicorr_lfr_ehad_0tag_up  ->SetDirectory(m_histoDir);
    h_dphicorr_lfr_ehad_0tag_down=(TH1F*)tempFile->Get("dphicorr_Bveto_ehad_LepMETDphiBvetoCorrectionELE_down");         h_dphicorr_lfr_ehad_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFRdphiBvetomuhadLepMETDphiBvetoCorrectionMUON.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFRdphiBvetomuhadLepMETDphiBvetoCorrectionMUON.root " << std::endl;
  else
  {
    h_dphicorr_lfr_muhad_0tag     =(TH1F*)tempFile->Get("dphicorr_Bveto_muhad_LepMETDphiBvetoCorrectionMUON");             h_dphicorr_lfr_muhad_0tag      ->SetDirectory(m_histoDir);
    h_dphicorr_lfr_muhad_0tag_up  =(TH1F*)tempFile->Get("dphicorr_Bveto_muhad_LepMETDphiBvetoCorrectionMUON_up");          h_dphicorr_lfr_muhad_0tag_up   ->SetDirectory(m_histoDir);
    h_dphicorr_lfr_muhad_0tag_down=(TH1F*)tempFile->Get("dphicorr_Bveto_muhad_LepMETDphiBvetoCorrectionMUON_down");        h_dphicorr_lfr_muhad_0tag_down ->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFRdphiBtagehadLepMETDphiBtagCorrectionELE.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFRdphiBtagehadLepMETDphiBtagCorrectionELE.root " << std::endl;
  else
  {
    h_dphicorr_lfr_ehad_1tag      =(TH1F*)tempFile->Get("dphicorr_Btag_ehad_LepMETDphiBtagCorrectionELE");               h_dphicorr_lfr_ehad_1tag      ->SetDirectory(m_histoDir);
    h_dphicorr_lfr_ehad_1tag_up   =(TH1F*)tempFile->Get("dphicorr_Btag_ehad_LepMETDphiBtagCorrectionELE_up");            h_dphicorr_lfr_ehad_1tag_up   ->SetDirectory(m_histoDir);
    h_dphicorr_lfr_ehad_1tag_down =(TH1F*)tempFile->Get("dphicorr_Btag_ehad_LepMETDphiBtagCorrectionELE_down");          h_dphicorr_lfr_ehad_1tag_down ->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFRdphiBtagmuhadLepMETDphiBtagCorrectionMUON.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFRdphiBtagmuhadLepMETDphiBtagCorrectionMUON.root " << std::endl;
  else
  {
    h_dphicorr_lfr_muhad_1tag      =(TH1F*)tempFile->Get("dphicorr_Btag_muhad_LepMETDphiBtagCorrectionMUON");            h_dphicorr_lfr_muhad_1tag     ->SetDirectory(m_histoDir);
    h_dphicorr_lfr_muhad_1tag_up   =(TH1F*)tempFile->Get("dphicorr_Btag_muhad_LepMETDphiBtagCorrectionMUON_up");         h_dphicorr_lfr_muhad_1tag_up  ->SetDirectory(m_histoDir);
    h_dphicorr_lfr_muhad_1tag_down =(TH1F*)tempFile->Get("dphicorr_Btag_muhad_LepMETDphiBtagCorrectionMUON_down");       h_dphicorr_lfr_muhad_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  ave_ele_bveto_eta=0;
  for(int bin=1; bin<=h_ff_lfr_ehad_0tag->GetNbinsX();++bin)
    ave_ele_bveto_eta += h_ff_lfr_ehad_0tag->GetBinContent(bin);
  ave_ele_bveto_eta /= h_ff_lfr_ehad_0tag->GetNbinsX();
  ave_ele_btag_eta=0;
  for(int bin=1; bin<=h_ff_lfr_ehad_1tag->GetNbinsX();++bin)
    ave_ele_btag_eta += h_ff_lfr_ehad_1tag->GetBinContent(bin);
  ave_ele_btag_eta /= h_ff_lfr_ehad_1tag->GetNbinsX();

*/


  ///////////////////////////////
  //
  //  2D ff pt * dphi parametrization for ehad and muhad (new)
  //
  ///////////////////////////////

  //2015+2016 first, Bveto, ehad
  tempFile=TFile::Open("FakeFactors/LFR15BvetoehadLeptonPtDphi1ELEBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BvetoehadLeptonPtDphi1ELEBVETOFF.root " << std::endl;
  else
  {
    h_ff15_lfr_ehad_dphi1_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi1ELEBVETOFF");              h_ff15_lfr_ehad_dphi1_0tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi1_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi1ELEBVETOFF_up");           h_ff15_lfr_ehad_dphi1_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi1_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi1ELEBVETOFF_down");         h_ff15_lfr_ehad_dphi1_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BvetoehadLeptonPtDphi2ELEBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BvetoehadLeptonPtDphi2ELEBVETOFF.root " << std::endl;
  else
  {
    h_ff15_lfr_ehad_dphi2_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi2ELEBVETOFF");              h_ff15_lfr_ehad_dphi2_0tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi2_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi2ELEBVETOFF_up");           h_ff15_lfr_ehad_dphi2_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi2_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi2ELEBVETOFF_down");         h_ff15_lfr_ehad_dphi2_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BvetoehadLeptonPtDphi3ELEBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BvetoehadLeptonPtDphi3ELEBVETOFF.root " << std::endl;
  else
  {
    h_ff15_lfr_ehad_dphi3_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi3ELEBVETOFF");              h_ff15_lfr_ehad_dphi3_0tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi3_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi3ELEBVETOFF_up");           h_ff15_lfr_ehad_dphi3_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi3_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi3ELEBVETOFF_down");         h_ff15_lfr_ehad_dphi3_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BvetoehadLeptonPtDphi4ELEBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BvetoehadLeptonPtDphi4ELEBVETOFF.root " << std::endl;
  else
  {
    h_ff15_lfr_ehad_dphi4_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi4ELEBVETOFF");              h_ff15_lfr_ehad_dphi4_0tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi4_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi4ELEBVETOFF_up");           h_ff15_lfr_ehad_dphi4_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi4_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi4ELEBVETOFF_down");         h_ff15_lfr_ehad_dphi4_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

   //2015+2016, Bveto, muhad
  tempFile=TFile::Open("FakeFactors/LFR15BvetomuhadLeptonPtDphi1MUONBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BvetomuhadLeptonPtDphi1MUONBVETOFF.root " << std::endl;
  else
  {
    h_ff15_lfr_muhad_dphi1_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi1MUONBVETOFF");              h_ff15_lfr_muhad_dphi1_0tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi1_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi1MUONBVETOFF_up");           h_ff15_lfr_muhad_dphi1_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi1_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi1MUONBVETOFF_down");         h_ff15_lfr_muhad_dphi1_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BvetomuhadLeptonPtDphi2MUONBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BvetomuhadLeptonPtDphi2MUONBVETOFF.root " << std::endl;
  else
  {
    h_ff15_lfr_muhad_dphi2_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi2MUONBVETOFF");              h_ff15_lfr_muhad_dphi2_0tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi2_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi2MUONBVETOFF_up");           h_ff15_lfr_muhad_dphi2_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi2_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi2MUONBVETOFF_down");         h_ff15_lfr_muhad_dphi2_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BvetomuhadLeptonPtDphi3MUONBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BvetomuhadLeptonPtDphi3MUONBVETOFF.root " << std::endl;
  else
  {
    h_ff15_lfr_muhad_dphi3_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi3MUONBVETOFF");              h_ff15_lfr_muhad_dphi3_0tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi3_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi3MUONBVETOFF_up");           h_ff15_lfr_muhad_dphi3_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi3_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi3MUONBVETOFF_down");         h_ff15_lfr_muhad_dphi3_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BvetomuhadLeptonPtDphi4MUONBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BvetomuhadLeptonPtDphi4MUONBVETOFF.root " << std::endl;
  else
  {
    h_ff15_lfr_muhad_dphi4_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi4MUONBVETOFF");              h_ff15_lfr_muhad_dphi4_0tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi4_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi4MUONBVETOFF_up");           h_ff15_lfr_muhad_dphi4_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi4_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi4MUONBVETOFF_down");         h_ff15_lfr_muhad_dphi4_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  //2015+2016, Btag, ehad
  tempFile=TFile::Open("FakeFactors/LFR15BtagehadLeptonPtDphi1ELEBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BtagehadLeptonPtDphi1ELEBTAGFF.root " << std::endl;
  else
  {
    h_ff15_lfr_ehad_dphi1_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi1ELEBTAGFF");              h_ff15_lfr_ehad_dphi1_1tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi1_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi1ELEBTAGFF_up");           h_ff15_lfr_ehad_dphi1_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi1_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi1ELEBTAGFF_down");         h_ff15_lfr_ehad_dphi1_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BtagehadLeptonPtDphi2ELEBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BtagehadLeptonPtDphi2ELEBTAGFF.root " << std::endl;
  else
  {
    h_ff15_lfr_ehad_dphi2_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi2ELEBTAGFF");              h_ff15_lfr_ehad_dphi2_1tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi2_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi2ELEBTAGFF_up");           h_ff15_lfr_ehad_dphi2_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi2_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi2ELEBTAGFF_down");         h_ff15_lfr_ehad_dphi2_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BtagehadLeptonPtDphi3ELEBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BtagehadLeptonPtDphi3ELEBTAGFF.root " << std::endl;
  else
  {
    h_ff15_lfr_ehad_dphi3_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi3ELEBTAGFF");              h_ff15_lfr_ehad_dphi3_1tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi3_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi3ELEBTAGFF_up");           h_ff15_lfr_ehad_dphi3_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_ehad_dphi3_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi3ELEBTAGFF_down");         h_ff15_lfr_ehad_dphi3_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }


  //2015+2016, Btag, muhad
  tempFile=TFile::Open("FakeFactors/LFR15BtagmuhadLeptonPtDphi1MUONBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BtagmuhadLeptonPtDphi1MUONBTAGFF.root " << std::endl;
  else
  {
    h_ff15_lfr_muhad_dphi1_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi1MUONBTAGFF");              h_ff15_lfr_muhad_dphi1_1tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi1_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi1MUONBTAGFF_up");           h_ff15_lfr_muhad_dphi1_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi1_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi1MUONBTAGFF_down");         h_ff15_lfr_muhad_dphi1_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BtagmuhadLeptonPtDphi2MUONBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BtagmuhadLeptonPtDphi2MUONBTAGFF.root " << std::endl;
  else
  {
    h_ff15_lfr_muhad_dphi2_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi2MUONBTAGFF");              h_ff15_lfr_muhad_dphi2_1tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi2_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi2MUONBTAGFF_up");           h_ff15_lfr_muhad_dphi2_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi2_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi2MUONBTAGFF_down");         h_ff15_lfr_muhad_dphi2_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR15BtagmuhadLeptonPtDphi3MUONBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR15BtagmuhadLeptonPtDphi3MUONBTAGFF.root " << std::endl;
  else
  {
    h_ff15_lfr_muhad_dphi3_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi3MUONBTAGFF");              h_ff15_lfr_muhad_dphi3_1tag_pt->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi3_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi3MUONBTAGFF_up");           h_ff15_lfr_muhad_dphi3_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff15_lfr_muhad_dphi3_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi3MUONBTAGFF_down");         h_ff15_lfr_muhad_dphi3_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }



  //now 2017! Bveto, ehad
  tempFile=TFile::Open("FakeFactors/LFR17BvetoehadLeptonPtDphi1ELEBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BvetoehadLeptonPtDphi1ELEBVETOFF.root " << std::endl;
  else
  {
    h_ff17_lfr_ehad_dphi1_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi1ELEBVETOFF");              h_ff17_lfr_ehad_dphi1_0tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi1_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi1ELEBVETOFF_up");           h_ff17_lfr_ehad_dphi1_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi1_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi1ELEBVETOFF_down");         h_ff17_lfr_ehad_dphi1_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BvetoehadLeptonPtDphi2ELEBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BvetoehadLeptonPtDphi2ELEBVETOFF.root " << std::endl;
  else
  {
    h_ff17_lfr_ehad_dphi2_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi2ELEBVETOFF");              h_ff17_lfr_ehad_dphi2_0tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi2_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi2ELEBVETOFF_up");           h_ff17_lfr_ehad_dphi2_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi2_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi2ELEBVETOFF_down");         h_ff17_lfr_ehad_dphi2_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BvetoehadLeptonPtDphi3ELEBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BvetoehadLeptonPtDphi3ELEBVETOFF.root " << std::endl;
  else
  {
    h_ff17_lfr_ehad_dphi3_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi3ELEBVETOFF");              h_ff17_lfr_ehad_dphi3_0tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi3_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi3ELEBVETOFF_up");           h_ff17_lfr_ehad_dphi3_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi3_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi3ELEBVETOFF_down");         h_ff17_lfr_ehad_dphi3_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BvetoehadLeptonPtDphi4ELEBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BvetoehadLeptonPtDphi4ELEBVETOFF.root " << std::endl;
  else
  {
    h_ff17_lfr_ehad_dphi4_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi4ELEBVETOFF");              h_ff17_lfr_ehad_dphi4_0tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi4_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi4ELEBVETOFF_up");           h_ff17_lfr_ehad_dphi4_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi4_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_ehad_LeptonPtDphi4ELEBVETOFF_down");         h_ff17_lfr_ehad_dphi4_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

   //2017, Bveto, muhad
  tempFile=TFile::Open("FakeFactors/LFR17BvetomuhadLeptonPtDphi1MUONBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BvetomuhadLeptonPtDphi1MUONBVETOFF.root " << std::endl;
  else
  {
    h_ff17_lfr_muhad_dphi1_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi1MUONBVETOFF");              h_ff17_lfr_muhad_dphi1_0tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi1_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi1MUONBVETOFF_up");           h_ff17_lfr_muhad_dphi1_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi1_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi1MUONBVETOFF_down");         h_ff17_lfr_muhad_dphi1_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BvetomuhadLeptonPtDphi2MUONBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BvetomuhadLeptonPtDphi2MUONBVETOFF.root " << std::endl;
  else
  {
    h_ff17_lfr_muhad_dphi2_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi2MUONBVETOFF");              h_ff17_lfr_muhad_dphi2_0tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi2_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi2MUONBVETOFF_up");           h_ff17_lfr_muhad_dphi2_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi2_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi2MUONBVETOFF_down");         h_ff17_lfr_muhad_dphi2_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BvetomuhadLeptonPtDphi3MUONBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BvetomuhadLeptonPtDphi3MUONBVETOFF.root " << std::endl;
  else
  {
    h_ff17_lfr_muhad_dphi3_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi3MUONBVETOFF");              h_ff17_lfr_muhad_dphi3_0tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi3_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi3MUONBVETOFF_up");           h_ff17_lfr_muhad_dphi3_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi3_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi3MUONBVETOFF_down");         h_ff17_lfr_muhad_dphi3_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BvetomuhadLeptonPtDphi4MUONBVETOFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BvetomuhadLeptonPtDphi4MUONBVETOFF.root " << std::endl;
  else
  {
    h_ff17_lfr_muhad_dphi4_0tag_pt     =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi4MUONBVETOFF");              h_ff17_lfr_muhad_dphi4_0tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi4_0tag_pt_up  =(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi4MUONBVETOFF_up");           h_ff17_lfr_muhad_dphi4_0tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi4_0tag_pt_down=(TH1F*)tempFile->Get("BvetoFF_muhad_LeptonPtDphi4MUONBVETOFF_down");         h_ff17_lfr_muhad_dphi4_0tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  //2017, Btag, ehad
  tempFile=TFile::Open("FakeFactors/LFR17BtagehadLeptonPtDphi1ELEBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BtagehadLeptonPtDphi1ELEBTAGFF.root " << std::endl;
  else
  {
    h_ff17_lfr_ehad_dphi1_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi1ELEBTAGFF");              h_ff17_lfr_ehad_dphi1_1tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi1_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi1ELEBTAGFF_up");           h_ff17_lfr_ehad_dphi1_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi1_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi1ELEBTAGFF_down");         h_ff17_lfr_ehad_dphi1_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BtagehadLeptonPtDphi2ELEBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BtagehadLeptonPtDphi2ELEBTAGFF.root " << std::endl;
  else
  {
    h_ff17_lfr_ehad_dphi2_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi2ELEBTAGFF");              h_ff17_lfr_ehad_dphi2_1tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi2_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi2ELEBTAGFF_up");           h_ff17_lfr_ehad_dphi2_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi2_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi2ELEBTAGFF_down");         h_ff17_lfr_ehad_dphi2_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BtagehadLeptonPtDphi3ELEBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BtagehadLeptonPtDphi3ELEBTAGFF.root " << std::endl;
  else
  {
    h_ff17_lfr_ehad_dphi3_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi3ELEBTAGFF");              h_ff17_lfr_ehad_dphi3_1tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi3_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi3ELEBTAGFF_up");           h_ff17_lfr_ehad_dphi3_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_ehad_dphi3_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_ehad_LeptonPtDphi3ELEBTAGFF_down");         h_ff17_lfr_ehad_dphi3_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }


  //2017, Btag, muhad
  tempFile=TFile::Open("FakeFactors/LFR17BtagmuhadLeptonPtDphi1MUONBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BtagmuhadLeptonPtDphi1MUONBTAGFF.root " << std::endl;
  else
  {
    h_ff17_lfr_muhad_dphi1_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi1MUONBTAGFF");              h_ff17_lfr_muhad_dphi1_1tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi1_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi1MUONBTAGFF_up");           h_ff17_lfr_muhad_dphi1_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi1_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi1MUONBTAGFF_down");         h_ff17_lfr_muhad_dphi1_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BtagmuhadLeptonPtDphi2MUONBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BtagmuhadLeptonPtDphi2MUONBTAGFF.root " << std::endl;
  else
  {
    h_ff17_lfr_muhad_dphi2_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi2MUONBTAGFF");              h_ff17_lfr_muhad_dphi2_1tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi2_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi2MUONBTAGFF_up");           h_ff17_lfr_muhad_dphi2_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi2_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi2MUONBTAGFF_down");         h_ff17_lfr_muhad_dphi2_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/LFR17BtagmuhadLeptonPtDphi3MUONBTAGFF.root");
  if(!tempFile) std::cout << "ERROR cant open FF file LFR17BtagmuhadLeptonPtDphi3MUONBTAGFF.root " << std::endl;
  else
  {
    h_ff17_lfr_muhad_dphi3_1tag_pt     =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi3MUONBTAGFF");              h_ff17_lfr_muhad_dphi3_1tag_pt->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi3_1tag_pt_up  =(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi3MUONBTAGFF_up");           h_ff17_lfr_muhad_dphi3_1tag_pt_up->SetDirectory(m_histoDir);
    h_ff17_lfr_muhad_dphi3_1tag_pt_down=(TH1F*)tempFile->Get("BtagFF_muhad_LeptonPtDphi3MUONBTAGFF_down");         h_ff17_lfr_muhad_dphi3_1tag_pt_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

}

//______________________________________________________________________________________________

const TString& isoReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool isoReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void isoReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool isoReweight::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void isoReweight::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString isoReweight::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool isoReweight::initializeSelf(){
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


  this->lep_0_phi      = new TTreeFormula( "lep_0_phi",     "lep_0_p4.Phi()",      this->fTree);
  this->lep_0      = new TTreeFormula( "lep_0",     "lep_0",      this->fTree);
  this->lep_0_eta      = new TTreeFormula( "lep_0_eta",     "lep_0_p4.Eta()",      this->fTree);
  this->lep_0_pt      = new TTreeFormula( "lep_0_pt",     "lep_0_p4.Pt()",      this->fTree);
  this->lephad_met_lep0_cos_dphi      = new TTreeFormula( "lephad_met_lep0_cos_dphi",     "lephad_met_lep0_cos_dphi",      this->fTree);

  this->n_bjets      = new TTreeFormula( "n_bjets",      "n_bjets",      this->fTree);

  return true;
}

//______________________________________________________________________________________________

bool isoReweight::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();


  delete this->lep_0_phi;
  delete this->lep_0;
  delete this->lep_0_eta;
  delete this->lep_0_pt;
  delete this->lephad_met_lep0_cos_dphi;

  delete this->n_bjets;

  return true;
}