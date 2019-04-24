#include "BSMtautauCAF/ptReweight.h"
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

ClassImp(ptReweight)

//______________________________________________________________________________________________

ptReweight::ptReweight(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

ptReweight::~ptReweight(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* ptReweight::getBranchNames() const {
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
  bnames->Add(new TObjString("lephad_met_lep1_cos_dphi"));

  if (isData()) {
    bnames->Add(new TObjString("run_number"));
  } else {
    bnames->Add(new TObjString("NOMINAL_pileup_random_run_number"));
  }

  return bnames;
}

//______________________________________________________________________________________________
double ptReweight::getValue() const {
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
  int    f_lephad_met_lep1_cos_dphi = this->lephad_met_lep1_cos_dphi->EvalInstance();
/*
  TH1F * h_ff_mj_1p_0tag     = h_2015ff_mj_1p_0tag   ;
  TH1F * h_ff_mj_3p_0tag     = h_2015ff_mj_3p_0tag   ;

  TH1F * h_ff_mj_1p_0tag_up  = h_2015ff_mj_1p_0tag_up;
  TH1F * h_ff_mj_3p_0tag_up  = h_2015ff_mj_3p_0tag_up;

  TH1F * h_ff_mj_1p_0tag_do  = h_2015ff_mj_1p_0tag_do;
  TH1F * h_ff_mj_3p_0tag_do  = h_2015ff_mj_3p_0tag_do;

  TH1F * h_ff_mj_1p_1tag     = h_2015ff_mj_1p_1tag   ;
  TH1F * h_ff_mj_3p_1tag     = h_2015ff_mj_3p_1tag   ;

  TH1F * h_ff_mj_1p_1tag_up  = h_2015ff_mj_1p_1tag_up;
  TH1F * h_ff_mj_3p_1tag_up  = h_2015ff_mj_3p_1tag_up;

  TH1F * h_ff_mj_1p_1tag_do  = h_2015ff_mj_1p_1tag_do;
  TH1F * h_ff_mj_3p_1tag_do  = h_2015ff_mj_3p_1tag_do;
*/
/*  if( is2016() ) {
    h_ff_mj_1p_0tag     = h_2016ff_mj_1p_0tag   ;
    h_ff_mj_3p_0tag     = h_2016ff_mj_3p_0tag   ;

    h_ff_mj_1p_0tag_up  = h_2016ff_mj_1p_0tag_up;
    h_ff_mj_3p_0tag_up  = h_2016ff_mj_3p_0tag_up;

    h_ff_mj_1p_0tag_do  = h_2016ff_mj_1p_0tag_do;
    h_ff_mj_3p_0tag_do  = h_2016ff_mj_3p_0tag_do;

    h_ff_mj_1p_1tag     = h_2016ff_mj_1p_1tag   ;
    h_ff_mj_3p_1tag     = h_2016ff_mj_3p_1tag   ;

    h_ff_mj_1p_1tag_up  = h_2016ff_mj_1p_1tag_up;
    h_ff_mj_3p_1tag_up  = h_2016ff_mj_3p_1tag_up;

    h_ff_mj_1p_1tag_do  = h_2016ff_mj_1p_1tag_do;
    h_ff_mj_3p_1tag_do  = h_2016ff_mj_3p_1tag_do;
  }
*/
/*  if( h_ff_mj_1p_0tag    == 0 ) std::cout<<" h_ff_mj_1p_0tag    is empty!! " <<std::endl;
  if( h_ff_mj_3p_0tag    == 0 ) std::cout<<" h_ff_mj_3p_0tag    is empty!! " <<std::endl;

  if( h_ff_mj_1p_0tag_up == 0 ) std::cout<<" h_ff_mj_1p_0tag_up is empty!! " <<std::endl;
  if( h_ff_mj_3p_0tag_up == 0 ) std::cout<<" h_ff_mj_3p_0tag_up is empty!! " <<std::endl;

  if( h_ff_mj_1p_0tag_do == 0 ) std::cout<<" h_ff_mj_1p_0tag_do is empty!! " <<std::endl;
  if( h_ff_mj_3p_0tag_do == 0 ) std::cout<<" h_ff_mj_3p_0tag_do is empty!! " <<std::endl;

  if( h_ff_mj_1p_1tag    == 0 ) std::cout<<" h_ff_mj_1p_1tag    is empty!! " <<std::endl;
  if( h_ff_mj_3p_1tag    == 0 ) std::cout<<" h_ff_mj_3p_1tag    is empty!! " <<std::endl;

  if( h_ff_mj_1p_1tag_up == 0 ) std::cout<<" h_ff_mj_1p_1tag_up is empty!! " <<std::endl;
  if( h_ff_mj_3p_1tag_up == 0 ) std::cout<<" h_ff_mj_3p_1tag_up is empty!! " <<std::endl;

  if( h_ff_mj_1p_1tag_do == 0 ) std::cout<<" h_ff_mj_1p_1tag_do is empty!! " <<std::endl;
  if( h_ff_mj_3p_1tag_do == 0 ) std::cout<<" h_ff_mj_3p_1tag_do is empty!! " <<std::endl;

  if( h_2015ff_mj_1p_0tag    == 0 ) std::cout<<" h_2015ff_mj_1p_0tag    is empty!! " <<std::endl;
  if( h_2015ff_mj_3p_0tag    == 0 ) std::cout<<" h_2015ff_mj_3p_0tag    is empty!! " <<std::endl;

  if( h_2015ff_mj_1p_0tag_up == 0 ) std::cout<<" h_2015ff_mj_1p_0tag_up is empty!! " <<std::endl;
  if( h_2015ff_mj_3p_0tag_up == 0 ) std::cout<<" h_2015ff_mj_3p_0tag_up is empty!! " <<std::endl;

  if( h_2015ff_mj_1p_0tag_do == 0 ) std::cout<<" h_2015ff_mj_1p_0tag_do is empty!! " <<std::endl;
  if( h_2015ff_mj_3p_0tag_do == 0 ) std::cout<<" h_2015ff_mj_3p_0tag_do is empty!! " <<std::endl;

  if( h_2015ff_mj_1p_1tag    == 0 ) std::cout<<" h_2015ff_mj_1p_1tag    is empty!! " <<std::endl;
  if( h_2015ff_mj_3p_1tag    == 0 ) std::cout<<" h_2015ff_mj_3p_1tag    is empty!! " <<std::endl;

  if( h_2015ff_mj_1p_1tag_up == 0 ) std::cout<<" h_2015ff_mj_1p_1tag_up is empty!! " <<std::endl;
  if( h_2015ff_mj_3p_1tag_up == 0 ) std::cout<<" h_2015ff_mj_3p_1tag_up is empty!! " <<std::endl;

  if( h_2015ff_mj_1p_1tag_do == 0 ) std::cout<<" h_2015ff_mj_1p_1tag_do is empty!! " <<std::endl;
  if( h_2015ff_mj_3p_1tag_do == 0 ) std::cout<<" h_2015ff_mj_3p_1tag_do is empty!! " <<std::endl;

  if( h_2016ff_mj_1p_0tag    == 0 ) std::cout<<" h_2016ff_mj_1p_0tag    is empty!! " <<std::endl;
  if( h_2016ff_mj_3p_0tag    == 0 ) std::cout<<" h_2016ff_mj_3p_0tag    is empty!! " <<std::endl;

  if( h_2016ff_mj_1p_0tag_up == 0 ) std::cout<<" h_2016ff_mj_1p_0tag_up is empty!! " <<std::endl;
  if( h_2016ff_mj_3p_0tag_up == 0 ) std::cout<<" h_2016ff_mj_3p_0tag_up is empty!! " <<std::endl;

  if( h_2016ff_mj_1p_0tag_do == 0 ) std::cout<<" h_2016ff_mj_1p_0tag_do is empty!! " <<std::endl;
  if( h_2016ff_mj_3p_0tag_do == 0 ) std::cout<<" h_2016ff_mj_3p_0tag_do is empty!! " <<std::endl;

  if( h_2016ff_mj_1p_1tag    == 0 ) std::cout<<" h_2016ff_mj_1p_1tag    is empty!! " <<std::endl;
  if( h_2016ff_mj_3p_1tag    == 0 ) std::cout<<" h_2016ff_mj_3p_1tag    is empty!! " <<std::endl;

  if( h_2016ff_mj_1p_1tag_up == 0 ) std::cout<<" h_2016ff_mj_1p_1tag_up is empty!! " <<std::endl;
  if( h_2016ff_mj_3p_1tag_up == 0 ) std::cout<<" h_2016ff_mj_3p_1tag_up is empty!! " <<std::endl;

  if( h_2016ff_mj_1p_1tag_do == 0 ) std::cout<<" h_2016ff_mj_1p_1tag_do is empty!! " <<std::endl;
  if( h_2016ff_mj_3p_1tag_do == 0 ) std::cout<<" h_2016ff_mj_3p_1tag_do is empty!! " <<std::endl;
*/

  ////////////////////////////
  //
  //  rQCD
  //
  ////////////////////////////
  //* rQCD factor valid range up to 250GeV
  /*if(f_tau_0_pt>250) f_tau_0_pt = 249;

  double f_rqcd(1),errf_rqcd(0);
  if( f_lep_0==1 )// muon
  {
    f_rqcd    = f_n_bjets==0?   h_rqcd_mu_bveto->GetBinContent( h_rqcd_mu_bveto->FindBin(f_tau_0_pt) ):
                                h_rqcd_mu_btag->GetBinContent( h_rqcd_mu_btag->FindBin(f_tau_0_pt) );
    errf_rqcd = f_n_bjets==0?   fabs( h_rqcd_mu_bveto_up->GetBinContent( h_rqcd_mu_bveto_up->FindBin(f_tau_0_pt) ) -
                                      h_rqcd_mu_bveto_do->GetBinContent( h_rqcd_mu_bveto_do->FindBin(f_tau_0_pt) ) ) :
                                fabs( h_rqcd_mu_btag_up->GetBinContent( h_rqcd_mu_btag_up->FindBin(f_tau_0_pt) ) -
                                      h_rqcd_mu_btag_do->GetBinContent( h_rqcd_mu_btag_do->FindBin(f_tau_0_pt) ) );
    errf_rqcd /= 2.;
  }
  else if( f_lep_0==2 )
  {
    f_rqcd    = f_n_bjets==0?   h_rqcd_el_bveto->GetBinContent( h_rqcd_el_bveto->FindBin(f_tau_0_pt) ):
                                h_rqcd_el_btag->GetBinContent( h_rqcd_el_btag->FindBin(f_tau_0_pt) );
    errf_rqcd = f_n_bjets==0?   fabs( h_rqcd_el_bveto_up->GetBinContent( h_rqcd_el_bveto_up->FindBin(f_tau_0_pt) ) -
                                      h_rqcd_el_bveto_do->GetBinContent( h_rqcd_el_bveto_do->FindBin(f_tau_0_pt) ) ) :
                                fabs( h_rqcd_el_btag_up->GetBinContent( h_rqcd_el_btag_up->FindBin(f_tau_0_pt) ) -
                                      h_rqcd_el_btag_do->GetBinContent( h_rqcd_el_btag_do->FindBin(f_tau_0_pt) ) );
    errf_rqcd /= 2.;
  }
*/




  ////////////////////////////
  //
  //  QCD FF
  //
  ////////////////////////////
  //* fake factor valid range up to 200GeV
  /*if(f_tau_0_pt>200) f_tau_0_pt = 199;

  double ff_mj(1),errff_mj(0);
  if( f_tau_0_n_charged_tracks==1 )
  {
    ff_mj    = f_n_bjets==0?  h_ff_mj_1p_0tag->GetBinContent( h_ff_mj_1p_0tag->FindBin(f_tau_0_pt) ):
                              h_ff_mj_1p_1tag->GetBinContent( h_ff_mj_1p_1tag->FindBin(f_tau_0_pt) );
    errff_mj = f_n_bjets==0?  fabs( h_ff_mj_1p_0tag_up->GetBinContent( h_ff_mj_1p_0tag_up->FindBin(f_tau_0_pt) ) -
                                    h_ff_mj_1p_0tag_do->GetBinContent( h_ff_mj_1p_0tag_do->FindBin(f_tau_0_pt) ) ) :
                              fabs( h_ff_mj_1p_1tag_up->GetBinContent( h_ff_mj_1p_1tag_up->FindBin(f_tau_0_pt) ) -
                                    h_ff_mj_1p_1tag_do->GetBinContent( h_ff_mj_1p_1tag_do->FindBin(f_tau_0_pt) ) );
    errff_mj /= 2.;
  }
  else if( f_tau_0_n_charged_tracks==3 )
  {
    ff_mj    = f_n_bjets==0?  h_ff_mj_3p_0tag->GetBinContent( h_ff_mj_3p_0tag->FindBin(f_tau_0_pt) ):
                              h_ff_mj_3p_1tag->GetBinContent( h_ff_mj_3p_1tag->FindBin(f_tau_0_pt) );
    errff_mj = f_n_bjets==0?  fabs( h_ff_mj_3p_0tag_up->GetBinContent( h_ff_mj_3p_0tag_up->FindBin(f_tau_0_pt) ) -
                                    h_ff_mj_3p_0tag_do->GetBinContent( h_ff_mj_3p_0tag_do->FindBin(f_tau_0_pt) ) ) :
                              fabs( h_ff_mj_3p_1tag_up->GetBinContent( h_ff_mj_3p_1tag_up->FindBin(f_tau_0_pt) ) -
                                    h_ff_mj_3p_1tag_do->GetBinContent( h_ff_mj_3p_1tag_do->FindBin(f_tau_0_pt) ) );
    errff_mj /= 2.;
  }
*/

  ////////////////////////////
  //
  //  WJETS FF
  //
  ////////////////////////////

  // nominal pt parametrization

  // fake factor valid range up to 200GeV
  if(f_tau_0_pt>300) f_tau_0_pt = 299;

  double ff15_ew(1),errff15_ew(0);
  if( f_lep_0==1 )//muon
  {
    if( f_tau_0_n_charged_tracks==1 )
    {
      ff15_ew    = f_n_bjets==0?  h_ff15_wfr_muhad_1p_0tag->GetBinContent( h_ff15_wfr_muhad_1p_0tag->FindBin(f_tau_0_pt) ):
                                h_ff15_wfr_muhad_1p_1tag->GetBinContent( h_ff15_wfr_muhad_1p_1tag->FindBin(f_tau_0_pt) );
      errff15_ew = f_n_bjets==0?  fabs(h_ff15_wfr_muhad_1p_0tag_up->GetBinContent( h_ff15_wfr_muhad_1p_0tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff15_wfr_muhad_1p_0tag_down->GetBinContent( h_ff15_wfr_muhad_1p_0tag_down->FindBin(f_tau_0_pt) ) ) :
                                fabs(h_ff15_wfr_muhad_1p_1tag_up->GetBinContent( h_ff15_wfr_muhad_1p_1tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff15_wfr_muhad_1p_1tag_down->GetBinContent( h_ff15_wfr_muhad_1p_1tag_down->FindBin(f_tau_0_pt) ) );
      errff15_ew /= 2.;
    }
    else if( f_tau_0_n_charged_tracks==3 )
    {
      ff15_ew    = f_n_bjets==0?  h_ff15_wfr_muhad_3p_0tag->GetBinContent( h_ff15_wfr_muhad_3p_0tag->FindBin(f_tau_0_pt) ):
                                h_ff15_wfr_muhad_3p_1tag->GetBinContent( h_ff15_wfr_muhad_3p_1tag->FindBin(f_tau_0_pt) );
      errff15_ew = f_n_bjets==0?  fabs(h_ff15_wfr_muhad_3p_0tag_up->GetBinContent(   h_ff15_wfr_muhad_3p_0tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff15_wfr_muhad_3p_0tag_down->GetBinContent( h_ff15_wfr_muhad_3p_0tag_down->FindBin(f_tau_0_pt) ) ) :
                                fabs(h_ff15_wfr_muhad_3p_1tag_up->GetBinContent(   h_ff15_wfr_muhad_3p_1tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff15_wfr_muhad_3p_1tag_down->GetBinContent( h_ff15_wfr_muhad_3p_1tag_down->FindBin(f_tau_0_pt) ) );
      errff15_ew /= 2.;
    }
  }
  else if( f_lep_0==2 )//electron
  {
    if( f_tau_0_n_charged_tracks==1 )
    {
      ff15_ew    = f_n_bjets==0?  h_ff15_wfr_ehad_1p_0tag->GetBinContent( h_ff15_wfr_ehad_1p_0tag->FindBin(f_tau_0_pt) ):
                                h_ff15_wfr_ehad_1p_1tag->GetBinContent( h_ff15_wfr_ehad_1p_1tag->FindBin(f_tau_0_pt) );
      errff15_ew = f_n_bjets==0?  fabs(h_ff15_wfr_ehad_1p_0tag_up->GetBinContent( h_ff15_wfr_ehad_1p_0tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff15_wfr_ehad_1p_0tag_down->GetBinContent( h_ff15_wfr_ehad_1p_0tag_down->FindBin(f_tau_0_pt) ) ) :
                                fabs(h_ff15_wfr_ehad_1p_1tag_up->GetBinContent( h_ff15_wfr_ehad_1p_1tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff15_wfr_ehad_1p_1tag_down->GetBinContent( h_ff15_wfr_ehad_1p_1tag_down->FindBin(f_tau_0_pt) ) );
      errff15_ew /= 2.;
    }
    else if( f_tau_0_n_charged_tracks==3 )
    {
      ff15_ew    = f_n_bjets==0?  h_ff15_wfr_ehad_3p_0tag->GetBinContent( h_ff15_wfr_ehad_3p_0tag->FindBin(f_tau_0_pt) ):
                                h_ff15_wfr_ehad_3p_1tag->GetBinContent( h_ff15_wfr_ehad_3p_1tag->FindBin(f_tau_0_pt) );
      errff15_ew = f_n_bjets==0?  fabs(h_ff15_wfr_ehad_3p_0tag_up->GetBinContent(   h_ff15_wfr_ehad_3p_0tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff15_wfr_ehad_3p_0tag_down->GetBinContent( h_ff15_wfr_ehad_3p_0tag_down->FindBin(f_tau_0_pt) ) ) :
                                fabs(h_ff15_wfr_ehad_3p_1tag_up->GetBinContent(   h_ff15_wfr_ehad_3p_1tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff15_wfr_ehad_3p_1tag_down->GetBinContent( h_ff15_wfr_ehad_3p_1tag_down->FindBin(f_tau_0_pt) ) );
      errff15_ew /= 2.;
    }
  }

  double ff17_ew(1),errff17_ew(0);
  if( f_lep_0==1 )//muon
  {
    if( f_tau_0_n_charged_tracks==1 )
    {
      ff17_ew    = f_n_bjets==0?  h_ff17_wfr_muhad_1p_0tag->GetBinContent( h_ff17_wfr_muhad_1p_0tag->FindBin(f_tau_0_pt) ):
                                h_ff17_wfr_muhad_1p_1tag->GetBinContent( h_ff17_wfr_muhad_1p_1tag->FindBin(f_tau_0_pt) );
      errff17_ew = f_n_bjets==0?  fabs(h_ff17_wfr_muhad_1p_0tag_up->GetBinContent( h_ff17_wfr_muhad_1p_0tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff17_wfr_muhad_1p_0tag_down->GetBinContent( h_ff17_wfr_muhad_1p_0tag_down->FindBin(f_tau_0_pt) ) ) :
                                fabs(h_ff17_wfr_muhad_1p_1tag_up->GetBinContent( h_ff17_wfr_muhad_1p_1tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff17_wfr_muhad_1p_1tag_down->GetBinContent( h_ff17_wfr_muhad_1p_1tag_down->FindBin(f_tau_0_pt) ) );
      errff17_ew /= 2.;
    }
    else if( f_tau_0_n_charged_tracks==3 )
    {
      ff17_ew    = f_n_bjets==0?  h_ff17_wfr_muhad_3p_0tag->GetBinContent( h_ff17_wfr_muhad_3p_0tag->FindBin(f_tau_0_pt) ):
                                h_ff17_wfr_muhad_3p_1tag->GetBinContent( h_ff17_wfr_muhad_3p_1tag->FindBin(f_tau_0_pt) );
      errff17_ew = f_n_bjets==0?  fabs(h_ff17_wfr_muhad_3p_0tag_up->GetBinContent(   h_ff17_wfr_muhad_3p_0tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff17_wfr_muhad_3p_0tag_down->GetBinContent( h_ff17_wfr_muhad_3p_0tag_down->FindBin(f_tau_0_pt) ) ) :
                                fabs(h_ff17_wfr_muhad_3p_1tag_up->GetBinContent(   h_ff17_wfr_muhad_3p_1tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff17_wfr_muhad_3p_1tag_down->GetBinContent( h_ff17_wfr_muhad_3p_1tag_down->FindBin(f_tau_0_pt) ) );
      errff17_ew /= 2.;
    }
  }
  else if( f_lep_0==2 )//electron
  {
    if( f_tau_0_n_charged_tracks==1 )
    {
      ff17_ew    = f_n_bjets==0?  h_ff17_wfr_ehad_1p_0tag->GetBinContent( h_ff17_wfr_ehad_1p_0tag->FindBin(f_tau_0_pt) ):
                                h_ff17_wfr_ehad_1p_1tag->GetBinContent( h_ff17_wfr_ehad_1p_1tag->FindBin(f_tau_0_pt) );
      errff17_ew = f_n_bjets==0?  fabs(h_ff17_wfr_ehad_1p_0tag_up->GetBinContent( h_ff17_wfr_ehad_1p_0tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff17_wfr_ehad_1p_0tag_down->GetBinContent( h_ff17_wfr_ehad_1p_0tag_down->FindBin(f_tau_0_pt) ) ) :
                                fabs(h_ff17_wfr_ehad_1p_1tag_up->GetBinContent( h_ff17_wfr_ehad_1p_1tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff17_wfr_ehad_1p_1tag_down->GetBinContent( h_ff17_wfr_ehad_1p_1tag_down->FindBin(f_tau_0_pt) ) );
      errff17_ew /= 2.;
    }
    else if( f_tau_0_n_charged_tracks==3 )
    {
      ff17_ew    = f_n_bjets==0?  h_ff17_wfr_ehad_3p_0tag->GetBinContent( h_ff17_wfr_ehad_3p_0tag->FindBin(f_tau_0_pt) ):
                                h_ff17_wfr_ehad_3p_1tag->GetBinContent( h_ff17_wfr_ehad_3p_1tag->FindBin(f_tau_0_pt) );
      errff17_ew = f_n_bjets==0?  fabs(h_ff17_wfr_ehad_3p_0tag_up->GetBinContent(   h_ff17_wfr_ehad_3p_0tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff17_wfr_ehad_3p_0tag_down->GetBinContent( h_ff17_wfr_ehad_3p_0tag_down->FindBin(f_tau_0_pt) ) ) :
                                fabs(h_ff17_wfr_ehad_3p_1tag_up->GetBinContent(   h_ff17_wfr_ehad_3p_1tag_up->FindBin(f_tau_0_pt) ) -
                                   h_ff17_wfr_ehad_3p_1tag_down->GetBinContent( h_ff17_wfr_ehad_3p_1tag_down->FindBin(f_tau_0_pt) ) );
      errff17_ew /= 2.;
    }
  }

  //if(f_lep_0_iso_Gradient==0)
  //{
  //  f_lephad_met_lep1_cos_dphi = fabs(f_tau_0_phi - f_met_anti_iso_phi);
  //  if(f_lephad_met_lep1_cos_dphi > TMath::Pi()) f_lephad_met_lep1_cos_dphi = TMath::TwoPi() - f_lephad_met_lep1_cos_dphi;
  //}

  // pt * dphi parametrization, using only for bveto, because btag didn't exhibit dphi dependence.
  double ff15_ptdphi_ew(1),errff15_ptdphi_ew(0);
  if ( f_lep_0==1 )//muon
  {
    if( f_tau_0_n_charged_tracks==1 )
    {
      if (f_lephad_met_lep1_cos_dphi<1.)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_muhad_1p_dphi1_0tag->GetBinContent(      h_ff15_wfr_muhad_1p_dphi1_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_muhad_1p_dphi1_0tag_up->GetBinContent(   h_ff15_wfr_muhad_1p_dphi1_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_muhad_1p_dphi1_0tag_down->GetBinContent( h_ff15_wfr_muhad_1p_dphi1_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=1.&&f_lephad_met_lep1_cos_dphi<2.)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_muhad_1p_dphi2_0tag->GetBinContent(      h_ff15_wfr_muhad_1p_dphi2_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_muhad_1p_dphi2_0tag_up->GetBinContent(   h_ff15_wfr_muhad_1p_dphi2_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_muhad_1p_dphi2_0tag_down->GetBinContent( h_ff15_wfr_muhad_1p_dphi2_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.&&f_lephad_met_lep1_cos_dphi<2.5)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_muhad_1p_dphi3_0tag->GetBinContent(      h_ff15_wfr_muhad_1p_dphi3_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_muhad_1p_dphi3_0tag_up->GetBinContent(   h_ff15_wfr_muhad_1p_dphi3_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_muhad_1p_dphi3_0tag_down->GetBinContent( h_ff15_wfr_muhad_1p_dphi3_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.5)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_muhad_1p_dphi4_0tag->GetBinContent(      h_ff15_wfr_muhad_1p_dphi4_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_muhad_1p_dphi4_0tag_up->GetBinContent(   h_ff15_wfr_muhad_1p_dphi4_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_muhad_1p_dphi4_0tag_down->GetBinContent( h_ff15_wfr_muhad_1p_dphi4_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      errff15_ptdphi_ew /= 2.;
    }

    else if( f_tau_0_n_charged_tracks==3 )
    {
      if (f_lephad_met_lep1_cos_dphi<1.)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_muhad_3p_dphi1_0tag->GetBinContent(      h_ff15_wfr_muhad_3p_dphi1_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_muhad_3p_dphi1_0tag_up->GetBinContent(   h_ff15_wfr_muhad_3p_dphi1_0tag_up->FindBin(f_tau_0_pt) ) -
                              h_ff15_wfr_muhad_3p_dphi1_0tag_down->GetBinContent( h_ff15_wfr_muhad_3p_dphi1_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=1.&&f_lephad_met_lep1_cos_dphi<2.)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_muhad_3p_dphi2_0tag->GetBinContent(      h_ff15_wfr_muhad_3p_dphi2_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_muhad_3p_dphi2_0tag_up->GetBinContent(   h_ff15_wfr_muhad_3p_dphi2_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_muhad_3p_dphi2_0tag_down->GetBinContent( h_ff15_wfr_muhad_3p_dphi2_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.&&f_lephad_met_lep1_cos_dphi<2.5)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_muhad_3p_dphi3_0tag->GetBinContent(      h_ff15_wfr_muhad_3p_dphi3_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_muhad_3p_dphi3_0tag_up->GetBinContent(   h_ff15_wfr_muhad_3p_dphi3_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_muhad_3p_dphi3_0tag_down->GetBinContent( h_ff15_wfr_muhad_3p_dphi3_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.5)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_muhad_3p_dphi4_0tag->GetBinContent(      h_ff15_wfr_muhad_3p_dphi4_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_muhad_3p_dphi4_0tag_up->GetBinContent(   h_ff15_wfr_muhad_3p_dphi4_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_muhad_3p_dphi4_0tag_down->GetBinContent( h_ff15_wfr_muhad_3p_dphi4_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      errff15_ptdphi_ew /= 2.;
    }
  }
  else if ( f_lep_0==2 )//electron
  {
    if( f_tau_0_n_charged_tracks==1 )
    {
      if (f_lephad_met_lep1_cos_dphi<1.)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_ehad_1p_dphi1_0tag->GetBinContent(      h_ff15_wfr_ehad_1p_dphi1_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_ehad_1p_dphi1_0tag_up->GetBinContent(   h_ff15_wfr_ehad_1p_dphi1_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_ehad_1p_dphi1_0tag_down->GetBinContent( h_ff15_wfr_ehad_1p_dphi1_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=1.&&f_lephad_met_lep1_cos_dphi<2.)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_ehad_1p_dphi2_0tag->GetBinContent(      h_ff15_wfr_ehad_1p_dphi2_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_ehad_1p_dphi2_0tag_up->GetBinContent(   h_ff15_wfr_ehad_1p_dphi2_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_ehad_1p_dphi2_0tag_down->GetBinContent( h_ff15_wfr_ehad_1p_dphi2_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.&&f_lephad_met_lep1_cos_dphi<2.5)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_ehad_1p_dphi3_0tag->GetBinContent(      h_ff15_wfr_ehad_1p_dphi3_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_ehad_1p_dphi3_0tag_up->GetBinContent(   h_ff15_wfr_ehad_1p_dphi3_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_ehad_1p_dphi3_0tag_down->GetBinContent( h_ff15_wfr_ehad_1p_dphi3_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.5)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_ehad_1p_dphi4_0tag->GetBinContent(      h_ff15_wfr_ehad_1p_dphi4_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_ehad_1p_dphi4_0tag_up->GetBinContent(   h_ff15_wfr_ehad_1p_dphi4_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_ehad_1p_dphi4_0tag_down->GetBinContent( h_ff15_wfr_ehad_1p_dphi4_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      errff15_ptdphi_ew /= 2.;
    }

    else if( f_tau_0_n_charged_tracks==3 )
    {
      if (f_lephad_met_lep1_cos_dphi<1.)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_ehad_3p_dphi1_0tag->GetBinContent(      h_ff15_wfr_ehad_3p_dphi1_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_ehad_3p_dphi1_0tag_up->GetBinContent(   h_ff15_wfr_ehad_3p_dphi1_0tag_up->FindBin(f_tau_0_pt) ) -
                              h_ff15_wfr_ehad_3p_dphi1_0tag_down->GetBinContent( h_ff15_wfr_ehad_3p_dphi1_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=1.&&f_lephad_met_lep1_cos_dphi<2.)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_ehad_3p_dphi2_0tag->GetBinContent(      h_ff15_wfr_ehad_3p_dphi2_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_ehad_3p_dphi2_0tag_up->GetBinContent(   h_ff15_wfr_ehad_3p_dphi2_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_ehad_3p_dphi2_0tag_down->GetBinContent( h_ff15_wfr_ehad_3p_dphi2_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.&&f_lephad_met_lep1_cos_dphi<2.5)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_ehad_3p_dphi3_0tag->GetBinContent(      h_ff15_wfr_ehad_3p_dphi3_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_ehad_3p_dphi3_0tag_up->GetBinContent(   h_ff15_wfr_ehad_3p_dphi3_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_ehad_3p_dphi3_0tag_down->GetBinContent( h_ff15_wfr_ehad_3p_dphi3_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.5)
      {
        ff15_ptdphi_ew  =         h_ff15_wfr_ehad_3p_dphi4_0tag->GetBinContent(      h_ff15_wfr_ehad_3p_dphi4_0tag->FindBin(f_tau_0_pt) );
        errff15_ptdphi_ew = fabs( h_ff15_wfr_ehad_3p_dphi4_0tag_up->GetBinContent(   h_ff15_wfr_ehad_3p_dphi4_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff15_wfr_ehad_3p_dphi4_0tag_down->GetBinContent( h_ff15_wfr_ehad_3p_dphi4_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      errff15_ptdphi_ew /= 2.;
    }
  }
  double ff17_ptdphi_ew(1),errff17_ptdphi_ew(0);
  if ( f_lep_0==1 )//muon
  {
    if( f_tau_0_n_charged_tracks==1 )
    {
      if (f_lephad_met_lep1_cos_dphi<1.)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_muhad_1p_dphi1_0tag->GetBinContent(      h_ff17_wfr_muhad_1p_dphi1_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_muhad_1p_dphi1_0tag_up->GetBinContent(   h_ff17_wfr_muhad_1p_dphi1_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_muhad_1p_dphi1_0tag_down->GetBinContent( h_ff17_wfr_muhad_1p_dphi1_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=1.&&f_lephad_met_lep1_cos_dphi<2.)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_muhad_1p_dphi2_0tag->GetBinContent(      h_ff17_wfr_muhad_1p_dphi2_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_muhad_1p_dphi2_0tag_up->GetBinContent(   h_ff17_wfr_muhad_1p_dphi2_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_muhad_1p_dphi2_0tag_down->GetBinContent( h_ff17_wfr_muhad_1p_dphi2_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.&&f_lephad_met_lep1_cos_dphi<2.5)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_muhad_1p_dphi3_0tag->GetBinContent(      h_ff17_wfr_muhad_1p_dphi3_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_muhad_1p_dphi3_0tag_up->GetBinContent(   h_ff17_wfr_muhad_1p_dphi3_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_muhad_1p_dphi3_0tag_down->GetBinContent( h_ff17_wfr_muhad_1p_dphi3_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.5)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_muhad_1p_dphi4_0tag->GetBinContent(      h_ff17_wfr_muhad_1p_dphi4_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_muhad_1p_dphi4_0tag_up->GetBinContent(   h_ff17_wfr_muhad_1p_dphi4_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_muhad_1p_dphi4_0tag_down->GetBinContent( h_ff17_wfr_muhad_1p_dphi4_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      errff17_ptdphi_ew /= 2.;
    }

    else if( f_tau_0_n_charged_tracks==3 )
    {
      if (f_lephad_met_lep1_cos_dphi<1.)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_muhad_3p_dphi1_0tag->GetBinContent(      h_ff17_wfr_muhad_3p_dphi1_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_muhad_3p_dphi1_0tag_up->GetBinContent(   h_ff17_wfr_muhad_3p_dphi1_0tag_up->FindBin(f_tau_0_pt) ) -
                              h_ff17_wfr_muhad_3p_dphi1_0tag_down->GetBinContent( h_ff17_wfr_muhad_3p_dphi1_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=1.&&f_lephad_met_lep1_cos_dphi<2.)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_muhad_3p_dphi2_0tag->GetBinContent(      h_ff17_wfr_muhad_3p_dphi2_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_muhad_3p_dphi2_0tag_up->GetBinContent(   h_ff17_wfr_muhad_3p_dphi2_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_muhad_3p_dphi2_0tag_down->GetBinContent( h_ff17_wfr_muhad_3p_dphi2_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.&&f_lephad_met_lep1_cos_dphi<2.5)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_muhad_3p_dphi3_0tag->GetBinContent(      h_ff17_wfr_muhad_3p_dphi3_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_muhad_3p_dphi3_0tag_up->GetBinContent(   h_ff17_wfr_muhad_3p_dphi3_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_muhad_3p_dphi3_0tag_down->GetBinContent( h_ff17_wfr_muhad_3p_dphi3_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.5)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_muhad_3p_dphi4_0tag->GetBinContent(      h_ff17_wfr_muhad_3p_dphi4_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_muhad_3p_dphi4_0tag_up->GetBinContent(   h_ff17_wfr_muhad_3p_dphi4_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_muhad_3p_dphi4_0tag_down->GetBinContent( h_ff17_wfr_muhad_3p_dphi4_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      errff17_ptdphi_ew /= 2.;
    }
  }
  else if ( f_lep_0==2 )//electron
  {
    if( f_tau_0_n_charged_tracks==1 )
    {
      if (f_lephad_met_lep1_cos_dphi<1.)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_ehad_1p_dphi1_0tag->GetBinContent(      h_ff17_wfr_ehad_1p_dphi1_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_ehad_1p_dphi1_0tag_up->GetBinContent(   h_ff17_wfr_ehad_1p_dphi1_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_ehad_1p_dphi1_0tag_down->GetBinContent( h_ff17_wfr_ehad_1p_dphi1_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=1.&&f_lephad_met_lep1_cos_dphi<2.)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_ehad_1p_dphi2_0tag->GetBinContent(      h_ff17_wfr_ehad_1p_dphi2_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_ehad_1p_dphi2_0tag_up->GetBinContent(   h_ff17_wfr_ehad_1p_dphi2_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_ehad_1p_dphi2_0tag_down->GetBinContent( h_ff17_wfr_ehad_1p_dphi2_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.&&f_lephad_met_lep1_cos_dphi<2.5)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_ehad_1p_dphi3_0tag->GetBinContent(      h_ff17_wfr_ehad_1p_dphi3_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_ehad_1p_dphi3_0tag_up->GetBinContent(   h_ff17_wfr_ehad_1p_dphi3_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_ehad_1p_dphi3_0tag_down->GetBinContent( h_ff17_wfr_ehad_1p_dphi3_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.5)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_ehad_1p_dphi4_0tag->GetBinContent(      h_ff17_wfr_ehad_1p_dphi4_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_ehad_1p_dphi4_0tag_up->GetBinContent(   h_ff17_wfr_ehad_1p_dphi4_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_ehad_1p_dphi4_0tag_down->GetBinContent( h_ff17_wfr_ehad_1p_dphi4_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      errff17_ptdphi_ew /= 2.;
    }

    else if( f_tau_0_n_charged_tracks==3 )
    {
      if (f_lephad_met_lep1_cos_dphi<1.)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_ehad_3p_dphi1_0tag->GetBinContent(      h_ff17_wfr_ehad_3p_dphi1_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_ehad_3p_dphi1_0tag_up->GetBinContent(   h_ff17_wfr_ehad_3p_dphi1_0tag_up->FindBin(f_tau_0_pt) ) -
                              h_ff17_wfr_ehad_3p_dphi1_0tag_down->GetBinContent( h_ff17_wfr_ehad_3p_dphi1_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=1.&&f_lephad_met_lep1_cos_dphi<2.)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_ehad_3p_dphi2_0tag->GetBinContent(      h_ff17_wfr_ehad_3p_dphi2_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_ehad_3p_dphi2_0tag_up->GetBinContent(   h_ff17_wfr_ehad_3p_dphi2_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_ehad_3p_dphi2_0tag_down->GetBinContent( h_ff17_wfr_ehad_3p_dphi2_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.&&f_lephad_met_lep1_cos_dphi<2.5)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_ehad_3p_dphi3_0tag->GetBinContent(      h_ff17_wfr_ehad_3p_dphi3_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_ehad_3p_dphi3_0tag_up->GetBinContent(   h_ff17_wfr_ehad_3p_dphi3_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_ehad_3p_dphi3_0tag_down->GetBinContent( h_ff17_wfr_ehad_3p_dphi3_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      else if (f_lephad_met_lep1_cos_dphi>=2.5)
      {
        ff17_ptdphi_ew  =         h_ff17_wfr_ehad_3p_dphi4_0tag->GetBinContent(      h_ff17_wfr_ehad_3p_dphi4_0tag->FindBin(f_tau_0_pt) );
        errff17_ptdphi_ew = fabs( h_ff17_wfr_ehad_3p_dphi4_0tag_up->GetBinContent(   h_ff17_wfr_ehad_3p_dphi4_0tag_up->FindBin(f_tau_0_pt) ) -
                                h_ff17_wfr_ehad_3p_dphi4_0tag_down->GetBinContent( h_ff17_wfr_ehad_3p_dphi4_0tag_down->FindBin(f_tau_0_pt) ) );
      }
      errff17_ptdphi_ew /= 2.;
    }
  }


  double nonclosure_W(1), nonclosure_W_err(0);
/*  if(f_n_bjets==0)
  {
    nonclosure_W    = h_dphi_cor ->GetBinContent( h_dphi_cor ->FindBin(f_lephad_met_lep1_cos_dphi) );
    nonclosure_W_err= h_dphi_cor ->GetBinError( h_dphi_cor ->FindBin(f_lephad_met_lep1_cos_dphi) );
  }
*/
  ////////////////
  //
  // SYSTEMATICS
  //
  ////////////////

  // WFF
  if    ( (fSysName.Contains("FakeFactor_WjetsBtag_1up")    && f_n_bjets>0) ||
          (fSysName.Contains("FakeFactor_WjetsBtag1p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBtag3p_1up")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBveto_1up")   && f_n_bjets==0 ) ||
          (fSysName.Contains("FakeFactor_WjetsBveto1p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBveto3p_1up") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    ) {
    ff15_ew += errff15_ew;
    ff15_ptdphi_ew += errff15_ptdphi_ew;
    ff17_ew += errff17_ew;
    ff17_ptdphi_ew += errff17_ptdphi_ew;
  }
  else if((fSysName.Contains("FakeFactor_WjetsBtag_1down")    && f_n_bjets>0) ||
          (fSysName.Contains("FakeFactor_WjetsBtag1p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBtag3p_1down")  && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBveto_1down")   && f_n_bjets==0 ) ||
          (fSysName.Contains("FakeFactor_WjetsBveto1p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBveto3p_1down") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3)    ) {
    ff15_ew -= errff15_ew;
    ff15_ptdphi_ew -= errff15_ptdphi_ew;
    ff17_ew -= errff17_ew;
    ff17_ptdphi_ew -= errff17_ptdphi_ew;
  }

  // WFF DPHI CORR BVETO
  if( fSysName.Contains("FakeDphi_WjetsSysUp") && f_n_bjets==0 ) {
    nonclosure_W += nonclosure_W_err;
  }
  else if( fSysName.Contains("FakeDphi_WjetsSysDo") && f_n_bjets==0 ) {
    nonclosure_W -= nonclosure_W_err;
  }


  DEBUGclass("returning");
  //return 0;
  double retval=ff15_ew;
  TString fflabel="";
  if(!this->fSample->getTag("~myWjetsFF",fflabel)) std::cout<<"Why cant I get process name!!!\n";
  if(fflabel=="FFW"){
      if(this->x_run_number->EvalInstance() <= LIMIT_2016) retval = ff15_ew;
      else if(this->x_run_number->EvalInstance() > LIMIT_2016 && this->x_run_number->EvalInstance() <= LIMIT_2017) retval = ff17_ew;
  }
  //else if (fflabel=="FFWDPHI")  retval = ff_ew * nonclosure_W;
  else if (fflabel=="FFWPTDPHI"){
      if(this->x_run_number->EvalInstance() <= LIMIT_2016) retval = f_n_bjets==0? ff15_ptdphi_ew : ff15_ew;
      else if(this->x_run_number->EvalInstance() > LIMIT_2016 && this->x_run_number->EvalInstance() <= LIMIT_2017) retval = f_n_bjets==0? ff17_ptdphi_ew : ff17_ew;
  }
  //else if (fflabel=="FFQCD")    retval = ff_mj;
  //else if (fflabel=="FFQCDR")   retval = ff_mj * f_rqcd;
  //else if (fflabel=="FFWDPHIR") retval = ff_ew * nonclosure_W * (1-f_rqcd);
  //else if (fflabel=="FFCOMB")   retval = ff_ew * nonclosure_W * (1-f_rqcd) + ff_mj * f_rqcd * nonclosure_W;
  return retval;
}
//______________________________________________________________________________________________

ptReweight::ptReweight(const TString& expression) : LepHadObservable(expression)
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

  std::cout << "INFO: ptReweight.cxx getting histograms from files. " << std::endl;
  ///////////////////////////////
  //
  //  Wjets FF
  //
  ///////////////////////////////
  // 2015+2016
  // nominal pt parametrization
  // lephad
/*
  tempFile=TFile::Open("FakeFactors/WFR15BvetolephadTauPtFFBveto1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetolephadTauPtFFBveto1p.root " << std::endl;
  else
  {
    h_ff15_wfr_1p_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1p");            h_ff15_wfr_1p_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_1p_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1p_up");        h_ff15_wfr_1p_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_1p_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1p_down");    h_ff15_wfr_1p_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetolephadTauPtFFBveto3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetolephadTauPtFFBveto3p.root " << std::endl;
  else
  {
    h_ff15_wfr_3p_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3p");            h_ff15_wfr_3p_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_3p_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3p_up");        h_ff15_wfr_3p_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_3p_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3p_down");    h_ff15_wfr_3p_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
*/
  // ehad
  tempFile=TFile::Open("FakeFactors/WFR15BvetoehadTauPtFFBveto1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetoehadTauPtFFBveto1p.root " << std::endl;
  else
  {
    h_ff15_wfr_ehad_1p_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1p");            h_ff15_wfr_ehad_1p_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_1p_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1p_up");        h_ff15_wfr_ehad_1p_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_1p_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1p_down");    h_ff15_wfr_ehad_1p_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetoehadTauPtFFBveto3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetoehadTauPtFFBveto3p.root " << std::endl;
  else
  {
    h_ff15_wfr_ehad_3p_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3p");            h_ff15_wfr_ehad_3p_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_3p_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3p_up");        h_ff15_wfr_ehad_3p_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_3p_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3p_down");    h_ff15_wfr_ehad_3p_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  // muhad
  tempFile=TFile::Open("FakeFactors/WFR15BvetomuhadTauPtFFBveto1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetomuhadTauPtFFBveto1p.root " << std::endl;
  else
  {
    h_ff15_wfr_muhad_1p_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1p");            h_ff15_wfr_muhad_1p_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_1p_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1p_up");        h_ff15_wfr_muhad_1p_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_1p_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1p_down");    h_ff15_wfr_muhad_1p_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetomuhadTauPtFFBveto3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetomuhadTauPtFFBveto3p.root " << std::endl;
  else
  {
    h_ff15_wfr_muhad_3p_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3p");            h_ff15_wfr_muhad_3p_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_3p_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3p_up");        h_ff15_wfr_muhad_3p_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_3p_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3p_down");    h_ff15_wfr_muhad_3p_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  // 2017
  // lephad
/*
  tempFile=TFile::Open("FakeFactors/WFR17BvetolephadTauPtFFBveto1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetolephadTauPtFFBveto1p.root " << std::endl;
  else
  {
    h_ff17_wfr_1p_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1p");            h_ff17_wfr_1p_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_1p_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1p_up");        h_ff17_wfr_1p_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_1p_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1p_down");    h_ff17_wfr_1p_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetolephadTauPtFFBveto3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetolephadTauPtFFBveto3p.root " << std::endl;
  else
  {
    h_ff17_wfr_3p_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3p");            h_ff17_wfr_3p_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_3p_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3p_up");        h_ff17_wfr_3p_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_3p_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3p_down");    h_ff17_wfr_3p_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
*/
  // ehad
  tempFile=TFile::Open("FakeFactors/WFR17BvetoehadTauPtFFBveto1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetoehadTauPtFFBveto1p.root " << std::endl;
  else
  {
    h_ff17_wfr_ehad_1p_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1p");            h_ff17_wfr_ehad_1p_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_1p_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1p_up");        h_ff17_wfr_ehad_1p_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_1p_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1p_down");    h_ff17_wfr_ehad_1p_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetoehadTauPtFFBveto3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetoehadTauPtFFBveto3p.root " << std::endl;
  else
  {
    h_ff17_wfr_ehad_3p_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3p");            h_ff17_wfr_ehad_3p_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_3p_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3p_up");        h_ff17_wfr_ehad_3p_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_3p_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3p_down");    h_ff17_wfr_ehad_3p_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  // muhad
  tempFile=TFile::Open("FakeFactors/WFR17BvetomuhadTauPtFFBveto1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetomuhadTauPtFFBveto1p.root " << std::endl;
  else
  {
    h_ff17_wfr_muhad_1p_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1p");            h_ff17_wfr_muhad_1p_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_1p_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1p_up");        h_ff17_wfr_muhad_1p_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_1p_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1p_down");    h_ff17_wfr_muhad_1p_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetomuhadTauPtFFBveto3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetomuhadTauPtFFBveto3p.root " << std::endl;
  else
  {
    h_ff17_wfr_muhad_3p_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3p");            h_ff17_wfr_muhad_3p_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_3p_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3p_up");        h_ff17_wfr_muhad_3p_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_3p_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3p_down");    h_ff17_wfr_muhad_3p_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }


  ///////////////////////////////
  //
  //  2015/16 BTAG
  //
  ///////////////////////////////
  // lephad
/*  tempFile=TFile::Open("FakeFactors/SSWFR15BtaglephadTauPtFFBtag1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWFR15BtaglephadTauPtFFBtag1p.root" << std::endl;
  else
  {
    h_ff15_wfr_lephad_1p_1tag = (TH1F*)tempFile->Get("BtagFF_lephad_TauPtFFBtag1p");            h_ff15_wfr_lephad_1p_1tag->SetDirectory(m_histoDir);
    h_ff15_wfr_lephad_1p_1tag_up=(TH1F*)tempFile->Get("BtagFF_lephad_TauPtFFBtag1p_up");        h_ff15_wfr_lephad_1p_1tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_lephad_1p_1tag_down=(TH1F*)tempFile->Get("BtagFF_lephad_TauPtFFBtag1p_down");    h_ff15_wfr_lephad_1p_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/SSWFR15BtaglephadTauPtFFBtag3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWFR15BtaglephadTauPtFFBtag3p.root " << std::endl;
  else
  {
    h_ff15_wfr_lephad_3p_1tag = (TH1F*)tempFile->Get("BtagFF_lephad_TauPtFFBtag3p");            h_ff15_wfr_lephad_3p_1tag->SetDirectory(m_histoDir);
    h_ff15_wfr_lephad_3p_1tag_up=(TH1F*)tempFile->Get("BtagFF_lephad_TauPtFFBtag3p_up");        h_ff15_wfr_lephad_3p_1tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_lephad_3p_1tag_down=(TH1F*)tempFile->Get("BtagFF_lephad_TauPtFFBtag3p_down");    h_ff15_wfr_lephad_3p_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
*/
  // ehad
  tempFile=TFile::Open("FakeFactors/SSWFR15BtagehadTauPtFFBtag1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWFR15BtagehadTauPtFFBtag1p.root" << std::endl;
  else
  {
    h_ff15_wfr_ehad_1p_1tag = (TH1F*)tempFile->Get("BtagFF_ehad_TauPtFFBtag1p");            h_ff15_wfr_ehad_1p_1tag->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_1p_1tag_up=(TH1F*)tempFile->Get("BtagFF_ehad_TauPtFFBtag1p_up");        h_ff15_wfr_ehad_1p_1tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_1p_1tag_down=(TH1F*)tempFile->Get("BtagFF_ehad_TauPtFFBtag1p_down");    h_ff15_wfr_ehad_1p_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/SSWFR15BtagehadTauPtFFBtag3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWFR15BtagehadTauPtFFBtag3p.root " << std::endl;
  else
  {
    h_ff15_wfr_ehad_3p_1tag = (TH1F*)tempFile->Get("BtagFF_ehad_TauPtFFBtag3p");            h_ff15_wfr_ehad_3p_1tag->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_3p_1tag_up=(TH1F*)tempFile->Get("BtagFF_ehad_TauPtFFBtag3p_up");        h_ff15_wfr_ehad_3p_1tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_3p_1tag_down=(TH1F*)tempFile->Get("BtagFF_ehad_TauPtFFBtag3p_down");    h_ff15_wfr_ehad_3p_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  // muhad
  tempFile=TFile::Open("FakeFactors/SSWFR15BtagmuhadTauPtFFBtag1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWFR15BtagmuhadTauPtFFBtag1p.root" << std::endl;
  else
  {
    h_ff15_wfr_muhad_1p_1tag = (TH1F*)tempFile->Get("BtagFF_muhad_TauPtFFBtag1p");            h_ff15_wfr_muhad_1p_1tag->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_1p_1tag_up=(TH1F*)tempFile->Get("BtagFF_muhad_TauPtFFBtag1p_up");        h_ff15_wfr_muhad_1p_1tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_1p_1tag_down=(TH1F*)tempFile->Get("BtagFF_muhad_TauPtFFBtag1p_down");    h_ff15_wfr_muhad_1p_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/SSWFR15BtagmuhadTauPtFFBtag3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWFR15BtagmuhadTauPtFFBtag3p.root " << std::endl;
  else
  {
    h_ff15_wfr_muhad_3p_1tag = (TH1F*)tempFile->Get("BtagFF_muhad_TauPtFFBtag3p");            h_ff15_wfr_muhad_3p_1tag->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_3p_1tag_up=(TH1F*)tempFile->Get("BtagFF_muhad_TauPtFFBtag3p_up");        h_ff15_wfr_muhad_3p_1tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_3p_1tag_down=(TH1F*)tempFile->Get("BtagFF_muhad_TauPtFFBtag3p_down");    h_ff15_wfr_muhad_3p_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }


  ///////////////////////////////
  //
  //  2017 BTAG
  //
  ///////////////////////////////
  // lephad
/*  tempFile=TFile::Open("FakeFactors/SSWFR17BtaglephadTauPtFFBtag1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWFR17BtaglephadTauPtFFBtag1p.root" << std::endl;
  else
  {
    h_ff17_wfr_1p_1tag = (TH1F*)tempFile->Get("BtagFF_lephad_TauPtFFBtag1p");            h_ff17_wfr_1p_1tag->SetDirectory(m_histoDir);
    h_ff17_wfr_1p_1tag_up=(TH1F*)tempFile->Get("BtagFF_lephad_TauPtFFBtag1p_up");        h_ff17_wfr_1p_1tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_1p_1tag_down=(TH1F*)tempFile->Get("BtagFF_lephad_TauPtFFBtag1p_down");    h_ff17_wfr_1p_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/SSWFR17BtaglephadTauPtFFBtag3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWFR17BtaglephadTauPtFFBtag3p.root " << std::endl;
  else
  {
    h_ff17_wfr_3p_1tag = (TH1F*)tempFile->Get("BtagFF_lephad_TauPtFFBtag3p");            h_ff17_wfr_3p_1tag->SetDirectory(m_histoDir);
    h_ff17_wfr_3p_1tag_up=(TH1F*)tempFile->Get("BtagFF_lephad_TauPtFFBtag3p_up");        h_ff17_wfr_3p_1tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_3p_1tag_down=(TH1F*)tempFile->Get("BtagFF_lephad_TauPtFFBtag3p_down");    h_ff17_wfr_3p_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
*/
  // ehad
  tempFile=TFile::Open("FakeFactors/SSWFR17BtagehadTauPtFFBtag1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWFR17BtagehadTauPtFFBtag1p.root" << std::endl;
  else
  {
    h_ff17_wfr_ehad_1p_1tag = (TH1F*)tempFile->Get("BtagFF_ehad_TauPtFFBtag1p");            h_ff17_wfr_ehad_1p_1tag->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_1p_1tag_up=(TH1F*)tempFile->Get("BtagFF_ehad_TauPtFFBtag1p_up");        h_ff17_wfr_ehad_1p_1tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_1p_1tag_down=(TH1F*)tempFile->Get("BtagFF_ehad_TauPtFFBtag1p_down");    h_ff17_wfr_ehad_1p_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/SSWFR17BtagehadTauPtFFBtag3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWFR17BtagehadTauPtFFBtag3p.root " << std::endl;
  else
  {
    h_ff17_wfr_ehad_3p_1tag = (TH1F*)tempFile->Get("BtagFF_ehad_TauPtFFBtag3p");            h_ff17_wfr_ehad_3p_1tag->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_3p_1tag_up=(TH1F*)tempFile->Get("BtagFF_ehad_TauPtFFBtag3p_up");        h_ff17_wfr_ehad_3p_1tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_3p_1tag_down=(TH1F*)tempFile->Get("BtagFF_ehad_TauPtFFBtag3p_down");    h_ff17_wfr_ehad_3p_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  // muhad
  tempFile=TFile::Open("FakeFactors/SSWFR17BtagmuhadTauPtFFBtag1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWFR17BtagmuhadTauPtFFBtag1p.root" << std::endl;
  else
  {
    h_ff17_wfr_muhad_1p_1tag = (TH1F*)tempFile->Get("BtagFF_muhad_TauPtFFBtag1p");            h_ff17_wfr_muhad_1p_1tag->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_1p_1tag_up=(TH1F*)tempFile->Get("BtagFF_muhad_TauPtFFBtag1p_up");        h_ff17_wfr_muhad_1p_1tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_1p_1tag_down=(TH1F*)tempFile->Get("BtagFF_muhad_TauPtFFBtag1p_down");    h_ff17_wfr_muhad_1p_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/SSWFR17BtagmuhadTauPtFFBtag3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWFR17BtagmuhadTauPtFFBtag3p.root " << std::endl;
  else
  {
    h_ff17_wfr_muhad_3p_1tag = (TH1F*)tempFile->Get("BtagFF_muhad_TauPtFFBtag3p");            h_ff17_wfr_muhad_3p_1tag->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_3p_1tag_up=(TH1F*)tempFile->Get("BtagFF_muhad_TauPtFFBtag3p_up");        h_ff17_wfr_muhad_3p_1tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_3p_1tag_down=(TH1F*)tempFile->Get("BtagFF_muhad_TauPtFFBtag3p_down");    h_ff17_wfr_muhad_3p_1tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  //////////////////////////////////////
  //////////////////////////////////////
  //
  // Pt * Dphi parametrization
  //
  //////////////////////////////////////
  //
  // 2015/2016
  //
  //////////////////////////////////////
  // lephad
/*  tempFile=TFile::Open("FakeFactors/WFR15BvetolephadTauPtFFBveto1pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetolephadTauPtFFBveto1pDphi1.root " << std::endl;
  else
  {
    h_ff15_wfr_1p_dphi1_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi1");            h_ff15_wfr_1p_dphi1_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_1p_dphi1_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi1_up");        h_ff15_wfr_1p_dphi1_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_1p_dphi1_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi1_down");    h_ff15_wfr_1p_dphi1_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetolephadTauPtFFBveto1pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetolephadTauPtFFBveto1pDphi2.root " << std::endl;
  else
  {
    h_ff15_wfr_1p_dphi2_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi2");            h_ff15_wfr_1p_dphi2_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_1p_dphi2_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi2_up");        h_ff15_wfr_1p_dphi2_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_1p_dphi2_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi2_down");    h_ff15_wfr_1p_dphi2_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetolephadTauPtFFBveto1pDphi3.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetolephadTauPtFFBveto1pDphi3.root " << std::endl;
  else
  {
    h_ff15_wfr_1p_dphi3_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi3");            h_ff15_wfr_1p_dphi3_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_1p_dphi3_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi3_up");        h_ff15_wfr_1p_dphi3_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_1p_dphi3_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi3_down");    h_ff15_wfr_1p_dphi3_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetolephadTauPtFFBveto3pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetolephadTauPtFFBveto3pDphi1.root " << std::endl;
  else
  {
    h_ff15_wfr_3p_dphi1_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi1");            h_ff15_wfr_3p_dphi1_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_3p_dphi1_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi1_up");        h_ff15_wfr_3p_dphi1_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_3p_dphi1_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi1_down");    h_ff15_wfr_3p_dphi1_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetolephadTauPtFFBveto3pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetolephadTauPtFFBveto3pDphi2.root " << std::endl;
  else
  {
    h_ff15_wfr_3p_dphi2_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi2");            h_ff15_wfr_3p_dphi2_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_3p_dphi2_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi2_up");        h_ff15_wfr_3p_dphi2_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_3p_dphi2_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi2_down");    h_ff15_wfr_3p_dphi2_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetolephadTauPtFFBveto3pDphi3.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetolephadTauPtFFBveto3pDphi3.root " << std::endl;
  else
  {
    h_ff15_wfr_3p_dphi3_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi3");            h_ff15_wfr_3p_dphi3_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_3p_dphi3_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi3_up");        h_ff15_wfr_3p_dphi3_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_3p_dphi3_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi3_down");    h_ff15_wfr_3p_dphi3_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
*/
  // ehad
  tempFile=TFile::Open("FakeFactors/WFR15BvetoehadTauPtFFBveto1pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetoehadTauPtFFBveto1pDphi1.root " << std::endl;
  else
  {
    h_ff15_wfr_ehad_1p_dphi1_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi1");            h_ff15_wfr_ehad_1p_dphi1_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_1p_dphi1_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi1_up");        h_ff15_wfr_ehad_1p_dphi1_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_1p_dphi1_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi1_down");    h_ff15_wfr_ehad_1p_dphi1_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetoehadTauPtFFBveto1pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetoehadTauPtFFBveto1pDphi2.root " << std::endl;
  else
  {
    h_ff15_wfr_ehad_1p_dphi2_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi2");            h_ff15_wfr_ehad_1p_dphi2_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_1p_dphi2_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi2_up");        h_ff15_wfr_ehad_1p_dphi2_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_1p_dphi2_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi2_down");    h_ff15_wfr_ehad_1p_dphi2_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetoehadTauPtFFBveto1pDphi3.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetoehadTauPtFFBveto1pDphi3.root " << std::endl;
  else
  {
    h_ff15_wfr_ehad_1p_dphi3_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi3");            h_ff15_wfr_ehad_1p_dphi3_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_1p_dphi3_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi3_up");        h_ff15_wfr_ehad_1p_dphi3_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_1p_dphi3_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi3_down");    h_ff15_wfr_ehad_1p_dphi3_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  tempFile=TFile::Open("FakeFactors/WFR15BvetoehadTauPtFFBveto1pDphi4.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetoehadTauPtFFBveto1pDphi4.root " << std::endl;
  else
  {
    h_ff15_wfr_ehad_1p_dphi4_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi4");            h_ff15_wfr_ehad_1p_dphi4_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_1p_dphi4_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi4_up");        h_ff15_wfr_ehad_1p_dphi4_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_1p_dphi4_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi4_down");    h_ff15_wfr_ehad_1p_dphi4_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetoehadTauPtFFBveto3pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetoehadTauPtFFBveto3pDphi1.root " << std::endl;
  else
  {
    h_ff15_wfr_ehad_3p_dphi1_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi1");            h_ff15_wfr_ehad_3p_dphi1_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_3p_dphi1_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi1_up");        h_ff15_wfr_ehad_3p_dphi1_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_3p_dphi1_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi1_down");    h_ff15_wfr_ehad_3p_dphi1_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetoehadTauPtFFBveto3pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetoehadTauPtFFBveto3pDphi2.root " << std::endl;
  else
  {
    h_ff15_wfr_ehad_3p_dphi2_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi2");            h_ff15_wfr_ehad_3p_dphi2_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_3p_dphi2_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi2_up");        h_ff15_wfr_ehad_3p_dphi2_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_3p_dphi2_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi2_down");    h_ff15_wfr_ehad_3p_dphi2_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetoehadTauPtFFBveto3pDphi3.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetoehadTauPtFFBveto3pDphi3.root " << std::endl;
  else
  {
    h_ff15_wfr_ehad_3p_dphi3_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi3");            h_ff15_wfr_ehad_3p_dphi3_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_3p_dphi3_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi3_up");        h_ff15_wfr_ehad_3p_dphi3_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_3p_dphi3_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi3_down");    h_ff15_wfr_ehad_3p_dphi3_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  tempFile=TFile::Open("FakeFactors/WFR15BvetoehadTauPtFFBveto3pDphi4.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetoehadTauPtFFBveto3pDphi4.root " << std::endl;
  else
  {
    h_ff15_wfr_ehad_3p_dphi4_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi4");            h_ff15_wfr_ehad_3p_dphi4_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_3p_dphi4_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi4_up");        h_ff15_wfr_ehad_3p_dphi4_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_ehad_3p_dphi4_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi4_down");    h_ff15_wfr_ehad_3p_dphi4_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  // muhad
  tempFile=TFile::Open("FakeFactors/WFR15BvetomuhadTauPtFFBveto1pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetomuhadTauPtFFBveto1pDphi1.root " << std::endl;
  else
  {
    h_ff15_wfr_muhad_1p_dphi1_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi1");            h_ff15_wfr_muhad_1p_dphi1_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_1p_dphi1_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi1_up");        h_ff15_wfr_muhad_1p_dphi1_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_1p_dphi1_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi1_down");    h_ff15_wfr_muhad_1p_dphi1_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetomuhadTauPtFFBveto1pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetomuhadTauPtFFBveto1pDphi2.root " << std::endl;
  else
  {
    h_ff15_wfr_muhad_1p_dphi2_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi2");            h_ff15_wfr_muhad_1p_dphi2_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_1p_dphi2_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi2_up");        h_ff15_wfr_muhad_1p_dphi2_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_1p_dphi2_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi2_down");    h_ff15_wfr_muhad_1p_dphi2_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetomuhadTauPtFFBveto1pDphi3.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetomuhadTauPtFFBveto1pDphi3.root " << std::endl;
  else
  {
    h_ff15_wfr_muhad_1p_dphi3_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi3");            h_ff15_wfr_muhad_1p_dphi3_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_1p_dphi3_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi3_up");        h_ff15_wfr_muhad_1p_dphi3_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_1p_dphi3_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi3_down");    h_ff15_wfr_muhad_1p_dphi3_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  tempFile=TFile::Open("FakeFactors/WFR15BvetomuhadTauPtFFBveto1pDphi4.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetomuhadTauPtFFBveto1pDphi4.root " << std::endl;
  else
  {
    h_ff15_wfr_muhad_1p_dphi4_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi4");            h_ff15_wfr_muhad_1p_dphi4_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_1p_dphi4_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi4_up");        h_ff15_wfr_muhad_1p_dphi4_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_1p_dphi4_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi4_down");    h_ff15_wfr_muhad_1p_dphi4_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetomuhadTauPtFFBveto3pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetomuhadTauPtFFBveto3pDphi1.root " << std::endl;
  else
  {
    h_ff15_wfr_muhad_3p_dphi1_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi1");            h_ff15_wfr_muhad_3p_dphi1_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_3p_dphi1_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi1_up");        h_ff15_wfr_muhad_3p_dphi1_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_3p_dphi1_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi1_down");    h_ff15_wfr_muhad_3p_dphi1_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetomuhadTauPtFFBveto3pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetomuhadTauPtFFBveto3pDphi2.root " << std::endl;
  else
  {
    h_ff15_wfr_muhad_3p_dphi2_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi2");            h_ff15_wfr_muhad_3p_dphi2_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_3p_dphi2_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi2_up");        h_ff15_wfr_muhad_3p_dphi2_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_3p_dphi2_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi2_down");    h_ff15_wfr_muhad_3p_dphi2_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR15BvetomuhadTauPtFFBveto3pDphi3.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetomuhadTauPtFFBveto3pDphi3.root " << std::endl;
  else
  {
    h_ff15_wfr_muhad_3p_dphi3_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi3");            h_ff15_wfr_muhad_3p_dphi3_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_3p_dphi3_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi3_up");        h_ff15_wfr_muhad_3p_dphi3_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_3p_dphi3_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi3_down");    h_ff15_wfr_muhad_3p_dphi3_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  tempFile=TFile::Open("FakeFactors/WFR15BvetomuhadTauPtFFBveto3pDphi4.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFRBvetomuhadTauPtFFBveto3pDphi4.root " << std::endl;
  else
  {
    h_ff15_wfr_muhad_3p_dphi4_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi4");            h_ff15_wfr_muhad_3p_dphi4_0tag->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_3p_dphi4_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi4_up");        h_ff15_wfr_muhad_3p_dphi4_0tag_up->SetDirectory(m_histoDir);
    h_ff15_wfr_muhad_3p_dphi4_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi4_down");    h_ff15_wfr_muhad_3p_dphi4_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  //////////////////////////////////////
  //
  // 2017
  //
  //////////////////////////////////////
/*  tempFile=TFile::Open("FakeFactors/WFR17BvetolephadTauPtFFBveto1pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetolephadTauPtFFBveto1pDphi1.root " << std::endl;
  else
  {
    h_ff17_wfr_1p_dphi1_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi1");            h_ff17_wfr_1p_dphi1_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_1p_dphi1_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi1_up");        h_ff17_wfr_1p_dphi1_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_1p_dphi1_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi1_down");    h_ff17_wfr_1p_dphi1_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetolephadTauPtFFBveto1pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetolephadTauPtFFBveto1pDphi2.root " << std::endl;
  else
  {
    h_ff17_wfr_1p_dphi2_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi2");            h_ff17_wfr_1p_dphi2_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_1p_dphi2_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi2_up");        h_ff17_wfr_1p_dphi2_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_1p_dphi2_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi2_down");    h_ff17_wfr_1p_dphi2_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetolephadTauPtFFBveto1pDphi3.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetolephadTauPtFFBveto1pDphi3.root " << std::endl;
  else
  {
    h_ff17_wfr_1p_dphi3_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi3");            h_ff17_wfr_1p_dphi3_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_1p_dphi3_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi3_up");        h_ff17_wfr_1p_dphi3_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_1p_dphi3_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto1pDphi3_down");    h_ff17_wfr_1p_dphi3_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetolephadTauPtFFBveto3pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetolephadTauPtFFBveto3pDphi1.root " << std::endl;
  else
  {
    h_ff17_wfr_3p_dphi1_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi1");            h_ff17_wfr_3p_dphi1_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_3p_dphi1_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi1_up");        h_ff17_wfr_3p_dphi1_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_3p_dphi1_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi1_down");    h_ff17_wfr_3p_dphi1_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetolephadTauPtFFBveto3pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetolephadTauPtFFBveto3pDphi2.root " << std::endl;
  else
  {
    h_ff17_wfr_3p_dphi2_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi2");            h_ff17_wfr_3p_dphi2_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_3p_dphi2_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi2_up");        h_ff17_wfr_3p_dphi2_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_3p_dphi2_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi2_down");    h_ff17_wfr_3p_dphi2_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetolephadTauPtFFBveto3pDphi3.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetolephadTauPtFFBveto3pDphi3.root " << std::endl;
  else
  {
    h_ff17_wfr_3p_dphi3_0tag = (TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi3");            h_ff17_wfr_3p_dphi3_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_3p_dphi3_0tag_up=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi3_up");        h_ff17_wfr_3p_dphi3_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_3p_dphi3_0tag_down=(TH1F*)tempFile->Get("BvetoFF_lephad_TauPtFFBveto3pDphi3_down");    h_ff17_wfr_3p_dphi3_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
*/
  // ehad
  tempFile=TFile::Open("FakeFactors/WFR17BvetoehadTauPtFFBveto1pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetoehadTauPtFFBveto1pDphi1.root " << std::endl;
  else
  {
    h_ff17_wfr_ehad_1p_dphi1_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi1");            h_ff17_wfr_ehad_1p_dphi1_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_1p_dphi1_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi1_up");        h_ff17_wfr_ehad_1p_dphi1_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_1p_dphi1_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi1_down");    h_ff17_wfr_ehad_1p_dphi1_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetoehadTauPtFFBveto1pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetoehadTauPtFFBveto1pDphi2.root " << std::endl;
  else
  {
    h_ff17_wfr_ehad_1p_dphi2_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi2");            h_ff17_wfr_ehad_1p_dphi2_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_1p_dphi2_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi2_up");        h_ff17_wfr_ehad_1p_dphi2_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_1p_dphi2_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi2_down");    h_ff17_wfr_ehad_1p_dphi2_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetoehadTauPtFFBveto1pDphi3.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetoehadTauPtFFBveto1pDphi3.root " << std::endl;
  else
  {
    h_ff17_wfr_ehad_1p_dphi3_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi3");            h_ff17_wfr_ehad_1p_dphi3_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_1p_dphi3_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi3_up");        h_ff17_wfr_ehad_1p_dphi3_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_1p_dphi3_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi3_down");    h_ff17_wfr_ehad_1p_dphi3_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  tempFile=TFile::Open("FakeFactors/WFR17BvetoehadTauPtFFBveto1pDphi4.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetoehadTauPtFFBveto1pDphi4.root " << std::endl;
  else
  {
    h_ff17_wfr_ehad_1p_dphi4_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi4");            h_ff17_wfr_ehad_1p_dphi4_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_1p_dphi4_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi4_up");        h_ff17_wfr_ehad_1p_dphi4_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_1p_dphi4_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto1pDphi4_down");    h_ff17_wfr_ehad_1p_dphi4_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetoehadTauPtFFBveto3pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetoehadTauPtFFBveto3pDphi1.root " << std::endl;
  else
  {
    h_ff17_wfr_ehad_3p_dphi1_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi1");            h_ff17_wfr_ehad_3p_dphi1_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_3p_dphi1_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi1_up");        h_ff17_wfr_ehad_3p_dphi1_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_3p_dphi1_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi1_down");    h_ff17_wfr_ehad_3p_dphi1_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetoehadTauPtFFBveto3pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetoehadTauPtFFBveto3pDphi2.root " << std::endl;
  else
  {
    h_ff17_wfr_ehad_3p_dphi2_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi2");            h_ff17_wfr_ehad_3p_dphi2_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_3p_dphi2_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi2_up");        h_ff17_wfr_ehad_3p_dphi2_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_3p_dphi2_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi2_down");    h_ff17_wfr_ehad_3p_dphi2_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetoehadTauPtFFBveto3pDphi3.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetoehadTauPtFFBveto3pDphi3.root " << std::endl;
  else
  {
    h_ff17_wfr_ehad_3p_dphi3_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi3");            h_ff17_wfr_ehad_3p_dphi3_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_3p_dphi3_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi3_up");        h_ff17_wfr_ehad_3p_dphi3_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_3p_dphi3_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi3_down");    h_ff17_wfr_ehad_3p_dphi3_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  tempFile=TFile::Open("FakeFactors/WFR17BvetoehadTauPtFFBveto3pDphi4.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetoehadTauPtFFBveto3pDphi4.root " << std::endl;
  else
  {
    h_ff17_wfr_ehad_3p_dphi4_0tag = (TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi4");            h_ff17_wfr_ehad_3p_dphi4_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_3p_dphi4_0tag_up=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi4_up");        h_ff17_wfr_ehad_3p_dphi4_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_ehad_3p_dphi4_0tag_down=(TH1F*)tempFile->Get("BvetoFF_ehad_TauPtFFBveto3pDphi4_down");    h_ff17_wfr_ehad_3p_dphi4_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  // muhad
  tempFile=TFile::Open("FakeFactors/WFR17BvetomuhadTauPtFFBveto1pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetomuhadTauPtFFBveto1pDphi1.root " << std::endl;
  else
  {
    h_ff17_wfr_muhad_1p_dphi1_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi1");            h_ff17_wfr_muhad_1p_dphi1_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_1p_dphi1_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi1_up");        h_ff17_wfr_muhad_1p_dphi1_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_1p_dphi1_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi1_down");    h_ff17_wfr_muhad_1p_dphi1_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetomuhadTauPtFFBveto1pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetomuhadTauPtFFBveto1pDphi2.root " << std::endl;
  else
  {
    h_ff17_wfr_muhad_1p_dphi2_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi2");            h_ff17_wfr_muhad_1p_dphi2_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_1p_dphi2_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi2_up");        h_ff17_wfr_muhad_1p_dphi2_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_1p_dphi2_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi2_down");    h_ff17_wfr_muhad_1p_dphi2_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetomuhadTauPtFFBveto1pDphi3.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetomuhadTauPtFFBveto1pDphi3.root " << std::endl;
  else
  {
    h_ff17_wfr_muhad_1p_dphi3_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi3");            h_ff17_wfr_muhad_1p_dphi3_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_1p_dphi3_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi3_up");        h_ff17_wfr_muhad_1p_dphi3_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_1p_dphi3_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi3_down");    h_ff17_wfr_muhad_1p_dphi3_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  tempFile=TFile::Open("FakeFactors/WFR17BvetomuhadTauPtFFBveto1pDphi4.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetomuhadTauPtFFBveto1pDphi4.root " << std::endl;
  else
  {
    h_ff17_wfr_muhad_1p_dphi4_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi4");            h_ff17_wfr_muhad_1p_dphi4_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_1p_dphi4_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi4_up");        h_ff17_wfr_muhad_1p_dphi4_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_1p_dphi4_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto1pDphi4_down");    h_ff17_wfr_muhad_1p_dphi4_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetomuhadTauPtFFBveto3pDphi1.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetomuhadTauPtFFBveto3pDphi1.root " << std::endl;
  else
  {
    h_ff17_wfr_muhad_3p_dphi1_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi1");            h_ff17_wfr_muhad_3p_dphi1_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_3p_dphi1_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi1_up");        h_ff17_wfr_muhad_3p_dphi1_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_3p_dphi1_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi1_down");    h_ff17_wfr_muhad_3p_dphi1_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetomuhadTauPtFFBveto3pDphi2.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetomuhadTauPtFFBveto3pDphi2.root " << std::endl;
  else
  {
    h_ff17_wfr_muhad_3p_dphi2_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi2");            h_ff17_wfr_muhad_3p_dphi2_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_3p_dphi2_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi2_up");        h_ff17_wfr_muhad_3p_dphi2_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_3p_dphi2_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi2_down");    h_ff17_wfr_muhad_3p_dphi2_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetomuhadTauPtFFBveto3pDphi3.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetomuhadTauPtFFBveto3pDphi3.root " << std::endl;
  else
  {
    h_ff17_wfr_muhad_3p_dphi3_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi3");            h_ff17_wfr_muhad_3p_dphi3_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_3p_dphi3_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi3_up");        h_ff17_wfr_muhad_3p_dphi3_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_3p_dphi3_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi3_down");    h_ff17_wfr_muhad_3p_dphi3_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WFR17BvetomuhadTauPtFFBveto3pDphi4.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WFR17BvetomuhadTauPtFFBveto3pDphi4.root " << std::endl;
  else
  {
    h_ff17_wfr_muhad_3p_dphi4_0tag = (TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi4");            h_ff17_wfr_muhad_3p_dphi4_0tag->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_3p_dphi4_0tag_up=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi4_up");        h_ff17_wfr_muhad_3p_dphi4_0tag_up->SetDirectory(m_histoDir);
    h_ff17_wfr_muhad_3p_dphi4_0tag_down=(TH1F*)tempFile->Get("BvetoFF_muhad_TauPtFFBveto3pDphi4_down");    h_ff17_wfr_muhad_3p_dphi4_0tag_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  ///////////////////////////////
  //
  //  rQCD
  //
  ///////////////////////////////
/*  tempFile=TFile::Open("FakeFactors/AntiIDBvetoehadTauPtRQCD.root");
  if(!tempFile) std::cout << "ERROR cant open FF file AntiIDBvetoehadTauPtRQCD.root " << std::endl;
  else
  {
    h_rqcd_el_bveto = (TH1F*)tempFile->Get("rqcd_Bveto_ehad_TauPtRQCD");            h_rqcd_el_bveto->SetDirectory(m_histoDir);
    h_rqcd_el_bveto_up=(TH1F*)tempFile->Get("rqcd_Bveto_ehad_TauPtRQCD_up");        h_rqcd_el_bveto_up->SetDirectory(m_histoDir);
    h_rqcd_el_bveto_do=(TH1F*)tempFile->Get("rqcd_Bveto_ehad_TauPtRQCD_down");      h_rqcd_el_bveto_do->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/AntiIDBtagehadTauPtRQCD.root");
  if(!tempFile) std::cout << "ERROR cant open FF file AntiIDBtagehadTauPtRQCD.root " << std::endl;
  else
  {
    h_rqcd_el_btag = (TH1F*)tempFile->Get("rqcd_Btag_ehad_TauPtRQCD");            h_rqcd_el_btag->SetDirectory(m_histoDir);
    h_rqcd_el_btag_up=(TH1F*)tempFile->Get("rqcd_Btag_ehad_TauPtRQCD_up");        h_rqcd_el_btag_up->SetDirectory(m_histoDir);
    h_rqcd_el_btag_do=(TH1F*)tempFile->Get("rqcd_Btag_ehad_TauPtRQCD_down");      h_rqcd_el_btag_do->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/AntiIDBvetomuhadTauPtRQCD.root");
  if(!tempFile) std::cout << "ERROR cant open FF file AntiIDBvetomuhadTauPtRQCD.root " << std::endl;
  else
  {
    h_rqcd_mu_bveto = (TH1F*)tempFile->Get("rqcd_Bveto_muhad_TauPtRQCD");            h_rqcd_mu_bveto->SetDirectory(m_histoDir);
    h_rqcd_mu_bveto_up=(TH1F*)tempFile->Get("rqcd_Bveto_muhad_TauPtRQCD_up");        h_rqcd_mu_bveto_up->SetDirectory(m_histoDir);
    h_rqcd_mu_bveto_do=(TH1F*)tempFile->Get("rqcd_Bveto_muhad_TauPtRQCD_down");       h_rqcd_mu_bveto_do->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/AntiIDBtagmuhadTauPtRQCD.root");
  if(!tempFile) std::cout << "ERROR cant open FF file AntiIDBtagmuhadTauPtRQCD.root " << std::endl;
  else
  {
    h_rqcd_mu_btag = (TH1F*)tempFile->Get("rqcd_Btag_muhad_TauPtRQCD");            h_rqcd_mu_btag->SetDirectory(m_histoDir);
    h_rqcd_mu_btag_up=(TH1F*)tempFile->Get("rqcd_Btag_muhad_TauPtRQCD_up");        h_rqcd_mu_btag_up->SetDirectory(m_histoDir);
    h_rqcd_mu_btag_do=(TH1F*)tempFile->Get("rqcd_Btag_muhad_TauPtRQCD_down");      h_rqcd_mu_btag_do->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  ///////////////////////////////
  //
  //  QCD FF
  //
  ///////////////////////////////
  tempFile=TFile::Open("FakeFactors/QCDCRBveto1plephad.root");
  if(!tempFile) std::cout << "ERROR cant open FF file QCDCRBveto1plephad.root " << std::endl;
  else
  {
    h_ff_mj_1p_0tag = (TH1F*)tempFile->Get("Bveto1pFF_lephad_TauPtFFBveto1p");            h_ff_mj_1p_0tag->SetDirectory(m_histoDir);
    h_ff_mj_1p_0tag_up=(TH1F*)tempFile->Get("Bveto1pFF_lephad_TauPtFFBveto1p_up");        h_ff_mj_1p_0tag_up->SetDirectory(m_histoDir);
    h_ff_mj_1p_0tag_do=(TH1F*)tempFile->Get("Bveto1pFF_lephad_TauPtFFBveto1p_down");    h_ff_mj_1p_0tag_do->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/QCDCRBveto3plephad.root");
  if(!tempFile) std::cout << "ERROR cant open FF file QCDCRBveto3plephad.root " << std::endl;
  else
  {
    h_ff_mj_3p_0tag = (TH1F*)tempFile->Get("Bveto3pFF_lephad_TauPtFFBveto3p");            h_ff_mj_3p_0tag->SetDirectory(m_histoDir);
    h_ff_mj_3p_0tag_up=(TH1F*)tempFile->Get("Bveto3pFF_lephad_TauPtFFBveto3p_up");        h_ff_mj_3p_0tag_up->SetDirectory(m_histoDir);
    h_ff_mj_3p_0tag_do=(TH1F*)tempFile->Get("Bveto3pFF_lephad_TauPtFFBveto3p_down");    h_ff_mj_3p_0tag_do->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/QCDCRBtag1plephad.root");
  if(!tempFile) std::cout << "ERROR cant open FF file QCDCRBtag1plephad.root " << std::endl;
  else
  {
    h_ff_mj_1p_1tag = (TH1F*)tempFile->Get("Btag1pFF_lephad_TauPtFFBtag1p");            h_ff_mj_1p_1tag->SetDirectory(m_histoDir);
    h_ff_mj_1p_1tag_up=(TH1F*)tempFile->Get("Btag1pFF_lephad_TauPtFFBtag1p_up");        h_ff_mj_1p_1tag_up->SetDirectory(m_histoDir);
    h_ff_mj_1p_1tag_do=(TH1F*)tempFile->Get("Btag1pFF_lephad_TauPtFFBtag1p_down");    h_ff_mj_1p_1tag_do->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/QCDCRBtag3plephad.root");
  if(!tempFile) std::cout << "ERROR cant open FF file QCDCRBtag3plephad.root " << std::endl;
  else
  {
    h_ff_mj_3p_1tag = (TH1F*)tempFile->Get("Btag3pFF_lephad_TauPtFFBtag3p");            h_ff_mj_3p_1tag->SetDirectory(m_histoDir);
    h_ff_mj_3p_1tag_up=(TH1F*)tempFile->Get("Btag3pFF_lephad_TauPtFFBtag3p_up");        h_ff_mj_3p_1tag_up->SetDirectory(m_histoDir);
    h_ff_mj_3p_1tag_do=(TH1F*)tempFile->Get("Btag3pFF_lephad_TauPtFFBtag3p_down");    h_ff_mj_3p_1tag_do->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
*/

   // /afs/cern.ch/user/v/vmuckhof/public/tag_00_02_26_05/dphi_correction_qcd_bveto_jbp70.root
   // /afs/cern.ch/user/v/vmuckhof/public/tag_00_02_26_05/hist_fakefactors_qcdCR_yearSplit_data.root
   // /afs/cern.ch/user/v/vmuckhof/public/tag_00_02_26_05/hist_lepton_fake_factor_nom_and_unc.root
   // /afs/cern.ch/user/v/vmuckhof/public/tag_00_02_26_05/hist_r_qcd_nom_and_unc.root


  //TFile *infile_rqcd_fixed = new TFile( "/afs/cern.ch/user/k/kluonas/public/BSMtautauCAFStuff/rQCD_Mar10_tag-26-05.root" );
  //h_rqcd_mu_bveto_fixed     = (TH1D*)infile_rqcd_fixed->Get("rQCD_CutFlowMUhadBveto");

  //TFile *infile_rqcd = new TFile( "/afs/cern.ch/user/v/vmuckhof/public/tag_00_02_26_05/hist_r_qcd_nom_and_unc.root" );
  //h_rqcd_el_bveto     = (TH1D*)infile_rqcd->Get("r_qcd_bveto_ehad_nom");
  //h_rqcd_el_bveto_up  = (TH1D*)infile_rqcd->Get("r_qcd_bveto_ehad_up");
  //h_rqcd_el_bveto_do  = (TH1D*)infile_rqcd->Get("r_qcd_bveto_ehad_down");
  //h_rqcd_mu_bveto     = (TH1D*)infile_rqcd->Get("r_qcd_bveto_muhad_nom");
  //h_rqcd_mu_bveto_up  = (TH1D*)infile_rqcd->Get("r_qcd_bveto_muhad_up");
  //h_rqcd_mu_bveto_do  = (TH1D*)infile_rqcd->Get("r_qcd_bveto_muhad_down");
  //h_rqcd_el_btag      = (TH1D*)infile_rqcd->Get("r_qcd_btag_ehad_nom");
  //h_rqcd_el_btag_up   = (TH1D*)infile_rqcd->Get("r_qcd_btag_ehad_up");
  //h_rqcd_el_btag_do   = (TH1D*)infile_rqcd->Get("r_qcd_btag_ehad_down");
  //h_rqcd_mu_btag      = (TH1D*)infile_rqcd->Get("r_qcd_btag_muhad_nom");
  //h_rqcd_mu_btag_up   = (TH1D*)infile_rqcd->Get("r_qcd_btag_muhad_up");
  //h_rqcd_mu_btag_do   = (TH1D*)infile_rqcd->Get("r_qcd_btag_muhad_down");
/*
  TFile *infile_ff_qcd = new TFile( "/afs/cern.ch/user/v/vmuckhof/public/tag_00_02_26_05/hist_fakefactors_qcdCR_yearSplit_data.root" );

  h_2015ff_mj_1p_0tag    = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_bveto_antiIso_1prong_2015_nom");
  h_2015ff_mj_3p_0tag    = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_bveto_antiIso_3prong_2015_nom");

  h_2015ff_mj_1p_0tag_up = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_bveto_antiIso_1prong_2015_simUp");
  h_2015ff_mj_3p_0tag_up = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_bveto_antiIso_3prong_2015_simUp");

  h_2015ff_mj_1p_0tag_do = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_bveto_antiIso_1prong_2015_simDown");
  h_2015ff_mj_3p_0tag_do = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_bveto_antiIso_3prong_2015_simDown");

  h_2015ff_mj_1p_1tag    = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_btag_antiIso_1prong_2015_nom");
  h_2015ff_mj_3p_1tag    = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_btag_antiIso_3prong_2015_nom");

  h_2015ff_mj_1p_1tag_up = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_btag_antiIso_1prong_2015_simUp");
  h_2015ff_mj_3p_1tag_up = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_btag_antiIso_3prong_2015_simUp");

  h_2015ff_mj_1p_1tag_do = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_btag_antiIso_1prong_2015_simDown");
  h_2015ff_mj_3p_1tag_do = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_btag_antiIso_3prong_2015_simDown");

  h_2016ff_mj_1p_0tag    = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_bveto_antiIso_1prong_2016_nom");
  h_2016ff_mj_3p_0tag    = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_bveto_antiIso_3prong_2016_nom");

  h_2016ff_mj_1p_0tag_up = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_bveto_antiIso_1prong_2016_simUp");
  h_2016ff_mj_3p_0tag_up = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_bveto_antiIso_3prong_2016_simUp");

  h_2016ff_mj_1p_0tag_do = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_bveto_antiIso_1prong_2016_simDown");
  h_2016ff_mj_3p_0tag_do = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_bveto_antiIso_3prong_2016_simDown");

  h_2016ff_mj_1p_1tag    = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_btag_antiIso_1prong_2016_nom");
  h_2016ff_mj_3p_1tag    = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_btag_antiIso_3prong_2016_nom");

  h_2016ff_mj_1p_1tag_up = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_btag_antiIso_1prong_2016_simUp");
  h_2016ff_mj_3p_1tag_up = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_btag_antiIso_3prong_2016_simUp");

  h_2016ff_mj_1p_1tag_do = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_btag_antiIso_1prong_2016_simDown");
  h_2016ff_mj_3p_1tag_do = (TH1F*)infile_ff_qcd->Get("h_ff_qcdCR_after_btag_antiIso_3prong_2016_simDown");
*/
/*  TFile* file = NULL;

  file = TFile::Open( "FakeFactors/WFRBveto1p.root" );
  h_ff_wfr_1p_0tag  = (TH2F*)infile_ff_wjets->Get("Bveto1p"); h_ff_wfr_1p_0tag->SetDirectory(0);
  file.Close(); delete file; file = NULL;

  file = TFile::Open( "FakeFactors/WFRBveto3p.root" );
  h_ff_wfr_3p_0tag  = (TH2F*)infile_ff_wjets->Get("Bveto3p"); h_ff_wfr_3p_0tag->SetDirectory(0);
  file.Close(); delete file; file = NULL;

*/
  //h_ff_wfr_1p_0tag_up   = (TH1F*)infile_ff_wjets->Get("combined_1prong_up");
  //h_ff_wfr_3p_0tag_up   = (TH1F*)infile_ff_wjets->Get("combined_3prong_up");
  //h_ff_wfr_1p_0tag_down = (TH1F*)infile_ff_wjets->Get("combined_1prong_down");
  //h_ff_wfr_3p_0tag_down = (TH1F*)infile_ff_wjets->Get("combined_3prong_down");

/*
  h_ff_wfr_1p_1tag_cor = (TH1F*)infile_ff_wjets->Get("WFF_BtagCorrection_1prong");
  h_ff_wfr_3p_1tag_cor = (TH1F*)infile_ff_wjets->Get("WFF_BtagCorrection_3prong");

  h_ff_wfr_1p_1tag_cor_up   = (TH1F*)infile_ff_wjets->Get("WFF_BtagCorrection_1prong_up");
  h_ff_wfr_3p_1tag_cor_up   = (TH1F*)infile_ff_wjets->Get("WFF_BtagCorrection_3prong_up");
  h_ff_wfr_1p_1tag_cor_down = (TH1F*)infile_ff_wjets->Get("WFF_BtagCorrection_1prong_down");
  h_ff_wfr_3p_1tag_cor_down = (TH1F*)infile_ff_wjets->Get("WFF_BtagCorrection_3prong_down");

  TFile *infile_dphi_cor = new TFile( "/afs/cern.ch/user/v/vmuckhof/public/tag_00_02_26_05/dphi_correction_qcd_bveto_jbp70.root" );
  h_dphi_cor= (TH1D*)infile_dphi_cor->Get("bveto_low_tauPt_inclusive_ratio");

  TFile *infile_dphiW25 = new TFile("/afs/cern.ch/user/k/kluonas/public/BSMtautauCAFStuff/MyDphiCorrection25PT.root");
  TFile *infile_dphiW30 = new TFile("/afs/cern.ch/user/k/kluonas/public/BSMtautauCAFStuff/MyDphiCorrection30PT.root");
  TFile *infile_dphiW40 = new TFile("/afs/cern.ch/user/k/kluonas/public/BSMtautauCAFStuff/MyDphiCorrection40PT.root");
  TFile *infile_dphiW60 = new TFile("/afs/cern.ch/user/k/kluonas/public/BSMtautauCAFStuff/MyDphiCorrection60PT.root");
  h_dphiW25 = (TH1F*)infile_dphiW25 ->Get("Combined");
  h_dphiW30 = (TH1F*)infile_dphiW30 ->Get("Combined");
  h_dphiW40 = (TH1F*)infile_dphiW40 ->Get("Combined");
  h_dphiW60 = (TH1F*)infile_dphiW60 ->Get("Combined");
*/
}

//______________________________________________________________________________________________

const TString& ptReweight::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool ptReweight::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void ptReweight::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool ptReweight::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void ptReweight::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString ptReweight::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool ptReweight::initializeSelf(){
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
  this->lep_0                   = new TTreeFormula( "lep_0",    "lep_0",      this->fTree);
  this->n_bjets                 = new TTreeFormula( "n_bjets",  "n_bjets",      this->fTree);
  //this->met_anti_iso_phi = new TTreeFormula( "met_anti_iso_phi", "met_anti_iso_phi", this->fTree);
  return true;
}

//______________________________________________________________________________________________

bool ptReweight::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->lep_0;
  delete this->tau_0_phi;
  delete this->tau_0_pt;
  //delete this->met_anti_iso_phi;
  delete this->tau_0_n_charged_tracks;
  delete this->lephad_met_lep1_cos_dphi;
  delete this->lep_0_iso_Gradient;
  delete this->n_bjets;

  return true;
}
