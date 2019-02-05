#include "Htautau/ptReweightBDT.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "TFile.h"
ClassImp(ptReweightBDT)

//______________________________________________________________________________________________

ptReweightBDT::ptReweightBDT(){
  // default constructor
  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

ptReweightBDT::~ptReweightBDT(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* ptReweightBDT::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);

  bnames->Add(new TObjString("tau_0_phi"));
  bnames->Add(new TObjString("lep_0_iso_Gradient"));
  bnames->Add(new TObjString("tau_0_n_charged_tracks"));
  bnames->Add(new TObjString("tau_0_pt"));

  bnames->Add(new TObjString("n_bjets"));
  bnames->Add(new TObjString("lephad_met_lep1_cos_dphi"));

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  return bnames;
}

//______________________________________________________________________________________________

double ptReweightBDT::getValue() const {
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
  double f_tau_0_phi          = this->tau_0_phi->EvalInstance();
  double f_lep_0_iso_Gradient = this->lep_0_iso_Gradient->EvalInstance();
  double f_tau_0_pt       = this->tau_0_pt->EvalInstance();
  int    f_tau_0_n_charged_tracks = this->tau_0_n_charged_tracks->EvalInstance();
  int    f_n_bjets        = this->n_bjets->EvalInstance();
  int    f_lephad_met_lep1_cos_dphi = this->lephad_met_lep1_cos_dphi->EvalInstance();

  if(f_tau_0_pt>=200) f_tau_0_pt = 199;


  double nonclosure_W(1), nonclosure_W_err(0);

  int prongs=-1,tags=-1,bdt=-1,dphi=-1;
  if      ( fSysName.Contains("_BDT1") ) bdt=1;
  else if ( fSysName.Contains("_BDT2") ) bdt=2;
  else if ( fSysName.Contains("_BDT3") ) bdt=3;
  else if ( fSysName.Contains("_BDT4") ) bdt=4;
  else    bdt=0;

  if (f_tau_0_n_charged_tracks==1) prongs=0; else prongs=1;
  if (f_n_bjets==0)        tags=0; else tags=1;

  if(tags==1) dphi=0;
  else if(f_lephad_met_lep1_cos_dphi<1.) dphi=1;
  else if(f_lephad_met_lep1_cos_dphi>=1.&&f_lephad_met_lep1_cos_dphi<2.)  dphi=2;
  else if(f_lephad_met_lep1_cos_dphi>=2.) dphi=3;
  else dphi=0;

  //if(!checkFF(prongs,tags,bdt,dphi)) std::cout << "WARNING!!! requesting non existing ff histo!!!"<< prongs << tags << bdt << dphi;
  //std::cout << "requesting "<< prongs << tags << bdt << dphi << h_ff_wcr[prongs][tags][bdt][dphi]     ->GetName();
  double fffff_ew(1),errfffff_ew(0);
  fffff_ew    =       h_ff_wcr[prongs][tags][bdt][dphi]     ->GetBinContent( h_ff_wcr[prongs][tags][bdt][dphi]->FindBin(f_tau_0_pt) );
  errfffff_ew = fabs( h_ff_wcr_up[prongs][tags][bdt][dphi]  ->GetBinContent( h_ff_wcr_up[prongs][tags][bdt][dphi]->FindBin(f_tau_0_pt) ) -
                      h_ff_wcr_down[prongs][tags][bdt][dphi]->GetBinContent( h_ff_wcr_down[prongs][tags][bdt][dphi]->FindBin(f_tau_0_pt) ) );
  errfffff_ew/=2.;


//if(f_n_bjets==0 && f_tau_0_n_charged_tracks==1)
//{
//  if( fSysName.Contains("_BDT1") )
//  {
//    nonclosure_W    = h_corr_wcr_1p_0tag_bdt1 ->GetBinContent( h_corr_wcr_1p_0tag_bdt1 ->FindBin(f_lephad_met_lep1_cos_dphi) );
//    nonclosure_W_err= h_corr_wcr_1p_0tag_bdt1 ->GetBinError( h_corr_wcr_1p_0tag_bdt1 ->FindBin(f_lephad_met_lep1_cos_dphi) );
//  }
//  if( fSysName.Contains("_BDT2") )
//  {
//    nonclosure_W    = h_corr_wcr_1p_0tag_bdt2 ->GetBinContent( h_corr_wcr_1p_0tag_bdt2 ->FindBin(f_lephad_met_lep1_cos_dphi) );
//    nonclosure_W_err= h_corr_wcr_1p_0tag_bdt2 ->GetBinError( h_corr_wcr_1p_0tag_bdt2 ->FindBin(f_lephad_met_lep1_cos_dphi) );
//  }
//  if( fSysName.Contains("_BDT3") )
//  {
//    nonclosure_W    = h_corr_wcr_1p_0tag_bdt3 ->GetBinContent( h_corr_wcr_1p_0tag_bdt3 ->FindBin(f_lephad_met_lep1_cos_dphi) );
//    nonclosure_W_err= h_corr_wcr_1p_0tag_bdt3 ->GetBinError( h_corr_wcr_1p_0tag_bdt3 ->FindBin(f_lephad_met_lep1_cos_dphi) );
//  }
//  if( fSysName.Contains("_BDT4") )
//  {
//    nonclosure_W    = h_corr_wcr_1p_0tag_bdt4 ->GetBinContent( h_corr_wcr_1p_0tag_bdt4 ->FindBin(f_lephad_met_lep1_cos_dphi) );
//    nonclosure_W_err= h_corr_wcr_1p_0tag_bdt4 ->GetBinError( h_corr_wcr_1p_0tag_bdt4 ->FindBin(f_lephad_met_lep1_cos_dphi) );
//  }
//}
//else if(f_n_bjets==0 && f_tau_0_n_charged_tracks==3)
//{
//  nonclosure_W    = h_corr_wcr_3p_0tag_bdt123 ->GetBinContent( h_corr_wcr_3p_0tag_bdt123 ->FindBin(f_lephad_met_lep1_cos_dphi) );
//  nonclosure_W_err= h_corr_wcr_3p_0tag_bdt123 ->GetBinError( h_corr_wcr_3p_0tag_bdt123 ->FindBin(f_lephad_met_lep1_cos_dphi) );
//}

  double ff_ew(0),errff_ew(0);
//  if( fSysName.Contains("_BDT1") )
//  {
//    if( f_tau_0_n_charged_tracks==1 )
//    {
//      ff_ew    = f_n_bjets==0?  h_ff_wcr_1p_0tag_bdt1->GetBinContent( h_ff_wcr_1p_0tag_bdt1->FindBin(f_tau_0_pt) ):
//                                h_ff_wcr_1p_1tag_bdt1->GetBinContent( h_ff_wcr_1p_1tag_bdt1->FindBin(f_tau_0_pt) );
//      errff_ew = f_n_bjets==0?  fabs(h_ff_wcr_1p_0tag_bdt1_up   ->GetBinContent( h_ff_wcr_1p_0tag_bdt1_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_1p_0tag_bdt1_down ->GetBinContent( h_ff_wcr_1p_0tag_bdt1_down->FindBin(f_tau_0_pt) ) ) :
//                                fabs(h_ff_wcr_1p_1tag_bdt1_up   ->GetBinContent( h_ff_wcr_1p_1tag_bdt1_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_1p_1tag_bdt1_down ->GetBinContent( h_ff_wcr_1p_1tag_bdt1_down->FindBin(f_tau_0_pt) ) );
//      errff_ew /= 2.;
//    }
//    else if( f_tau_0_n_charged_tracks==3 )
//    {
//      ff_ew    = f_n_bjets==0?  h_ff_wcr_3p_0tag_bdt1->GetBinContent( h_ff_wcr_3p_0tag_bdt1->FindBin(f_tau_0_pt) ):
//                                h_ff_wcr_3p_1tag_bdt1->GetBinContent( h_ff_wcr_3p_1tag_bdt1->FindBin(f_tau_0_pt) );
//      errff_ew = f_n_bjets==0?  fabs(h_ff_wcr_3p_0tag_bdt1_up   ->GetBinContent( h_ff_wcr_3p_0tag_bdt1_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_3p_0tag_bdt1_down ->GetBinContent( h_ff_wcr_3p_0tag_bdt1_down->FindBin(f_tau_0_pt) ) ) :
//                                fabs(h_ff_wcr_3p_1tag_bdt1_up   ->GetBinContent( h_ff_wcr_3p_1tag_bdt1_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_3p_1tag_bdt1_down ->GetBinContent( h_ff_wcr_3p_1tag_bdt1_down->FindBin(f_tau_0_pt) ) );
//      errff_ew /= 2.;
//    }
//  }
//  else if( fSysName.Contains("_BDT2") )
//  {
//    if( f_tau_0_n_charged_tracks==1 )
//    {
//      ff_ew    = f_n_bjets==0?  h_ff_wcr_1p_0tag_bdt2->GetBinContent( h_ff_wcr_1p_0tag_bdt2->FindBin(f_tau_0_pt) ):
//                                h_ff_wcr_1p_1tag_bdt2->GetBinContent( h_ff_wcr_1p_1tag_bdt2->FindBin(f_tau_0_pt) );
//      errff_ew = f_n_bjets==0?  fabs(h_ff_wcr_1p_0tag_bdt2_up   ->GetBinContent( h_ff_wcr_1p_0tag_bdt2_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_1p_0tag_bdt2_down ->GetBinContent( h_ff_wcr_1p_0tag_bdt2_down->FindBin(f_tau_0_pt) ) ) :
//                                fabs(h_ff_wcr_1p_1tag_bdt2_up   ->GetBinContent( h_ff_wcr_1p_1tag_bdt2_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_1p_1tag_bdt2_down ->GetBinContent( h_ff_wcr_1p_1tag_bdt2_down->FindBin(f_tau_0_pt) ) );
//      errff_ew /= 2.;
//    }
//    else if( f_tau_0_n_charged_tracks==3 )
//    {
//      ff_ew    = f_n_bjets==0?  h_ff_wcr_3p_0tag_bdt2->GetBinContent( h_ff_wcr_3p_0tag_bdt2->FindBin(f_tau_0_pt) ):
//                                h_ff_wcr_3p_1tag_bdt2->GetBinContent( h_ff_wcr_3p_1tag_bdt2->FindBin(f_tau_0_pt) );
//      errff_ew = f_n_bjets==0?  fabs(h_ff_wcr_3p_0tag_bdt2_up   ->GetBinContent( h_ff_wcr_3p_0tag_bdt2_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_3p_0tag_bdt2_down ->GetBinContent( h_ff_wcr_3p_0tag_bdt2_down->FindBin(f_tau_0_pt) ) ) :
//                                fabs(h_ff_wcr_3p_1tag_bdt2_up   ->GetBinContent( h_ff_wcr_3p_1tag_bdt2_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_3p_1tag_bdt2_down ->GetBinContent( h_ff_wcr_3p_1tag_bdt2_down->FindBin(f_tau_0_pt) ) );
//      errff_ew /= 2.;
//    }
//  }
//  else if( fSysName.Contains("_BDT3") )
//  {
//    if( f_tau_0_n_charged_tracks==1 )
//    {
//      ff_ew    = f_n_bjets==0?  h_ff_wcr_1p_0tag_bdt3->GetBinContent( h_ff_wcr_1p_0tag_bdt3->FindBin(f_tau_0_pt) ):
//                                h_ff_wcr_1p_1tag_bdt3->GetBinContent( h_ff_wcr_1p_1tag_bdt3->FindBin(f_tau_0_pt) );
//      errff_ew = f_n_bjets==0?  fabs(h_ff_wcr_1p_0tag_bdt3_up   ->GetBinContent( h_ff_wcr_1p_0tag_bdt3_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_1p_0tag_bdt3_down ->GetBinContent( h_ff_wcr_1p_0tag_bdt3_down->FindBin(f_tau_0_pt) ) ) :
//                                fabs(h_ff_wcr_1p_1tag_bdt3_up   ->GetBinContent( h_ff_wcr_1p_1tag_bdt3_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_1p_1tag_bdt3_down ->GetBinContent( h_ff_wcr_1p_1tag_bdt3_down->FindBin(f_tau_0_pt) ) );
//      errff_ew /= 2.;
//    }
//    else if( f_tau_0_n_charged_tracks==3 )
//    {
//      ff_ew    = f_n_bjets==0?  h_ff_wcr_3p_0tag_bdt3->GetBinContent( h_ff_wcr_3p_0tag_bdt3->FindBin(f_tau_0_pt) ):
//                                h_ff_wcr_3p_1tag_bdt3->GetBinContent( h_ff_wcr_3p_1tag_bdt3->FindBin(f_tau_0_pt) );
//      errff_ew = f_n_bjets==0?  fabs(h_ff_wcr_3p_0tag_bdt3_up   ->GetBinContent( h_ff_wcr_3p_0tag_bdt3_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_3p_0tag_bdt3_down ->GetBinContent( h_ff_wcr_3p_0tag_bdt3_down->FindBin(f_tau_0_pt) ) ) :
//                                fabs(h_ff_wcr_3p_1tag_bdt3_up   ->GetBinContent( h_ff_wcr_3p_1tag_bdt3_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_3p_1tag_bdt3_down ->GetBinContent( h_ff_wcr_3p_1tag_bdt3_down->FindBin(f_tau_0_pt) ) );
//      errff_ew /= 2.;
//    }
//  }
//  else if( fSysName.Contains("_BDT4") )
//  {
//    if( f_tau_0_n_charged_tracks==1 )
//    {
//      ff_ew    = f_n_bjets==0?  h_ff_wcr_1p_0tag_bdt4->GetBinContent( h_ff_wcr_1p_0tag_bdt4->FindBin(f_tau_0_pt) ):
//                                h_ff_wcr_1p_1tag_bdt4->GetBinContent( h_ff_wcr_1p_1tag_bdt4->FindBin(f_tau_0_pt) );
//      errff_ew = f_n_bjets==0?  fabs(h_ff_wcr_1p_0tag_bdt4_up   ->GetBinContent( h_ff_wcr_1p_0tag_bdt4_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_1p_0tag_bdt4_down ->GetBinContent( h_ff_wcr_1p_0tag_bdt4_down->FindBin(f_tau_0_pt) ) ) :
//                                fabs(h_ff_wcr_1p_1tag_bdt4_up   ->GetBinContent( h_ff_wcr_1p_1tag_bdt4_up->FindBin(f_tau_0_pt) ) -
//                                     h_ff_wcr_1p_1tag_bdt4_down ->GetBinContent( h_ff_wcr_1p_1tag_bdt4_down->FindBin(f_tau_0_pt) ) );
//      errff_ew /= 2.;
//    }
//    else if( f_tau_0_n_charged_tracks==3 )
//    {
//      std::cout << "ERROR::ptReweightBDT::getValue(): you are asking for 3-prong bdt4, why?" << std::endl;
//    }
//  }



  if( (fSysName.Contains("FakeFactor_WjetsBveto1pBDT1_1up") && fSysName.Contains("_BDT1") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
      (fSysName.Contains("FakeFactor_WjetsBveto1pBDT2_1up") && fSysName.Contains("_BDT2") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
      (fSysName.Contains("FakeFactor_WjetsBveto1pBDT3_1up") && fSysName.Contains("_BDT3") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
      (fSysName.Contains("FakeFactor_WjetsBveto1pBDT4_1up") && fSysName.Contains("_BDT4") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
      (fSysName.Contains("FakeFactor_WjetsBtag1pBDT1_1up") && fSysName.Contains("_BDT1") && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
      (fSysName.Contains("FakeFactor_WjetsBtag1pBDT2_1up") && fSysName.Contains("_BDT2") && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
      (fSysName.Contains("FakeFactor_WjetsBtag1pBDT3_1up") && fSysName.Contains("_BDT3") && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
      (fSysName.Contains("FakeFactor_WjetsBtag1pBDT4_1up") && fSysName.Contains("_BDT4") && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||

      (fSysName.Contains("FakeFactor_WjetsBveto3pBDT1_1up") && fSysName.Contains("_BDT1") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3) ||
      (fSysName.Contains("FakeFactor_WjetsBveto3pBDT2_1up") && fSysName.Contains("_BDT2") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3) ||
      (fSysName.Contains("FakeFactor_WjetsBveto3pBDT3_1up") && fSysName.Contains("_BDT3") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3) ||
      (fSysName.Contains("FakeFactor_WjetsBveto3pBDT4_1up") && fSysName.Contains("_BDT4") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3) ||
      (fSysName.Contains("FakeFactor_WjetsBtag3pBDT1_1up") && fSysName.Contains("_BDT1") && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
      (fSysName.Contains("FakeFactor_WjetsBtag3pBDT2_1up") && fSysName.Contains("_BDT2") && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
      (fSysName.Contains("FakeFactor_WjetsBtag3pBDT3_1up") && fSysName.Contains("_BDT3") && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
      (fSysName.Contains("FakeFactor_WjetsBtag3pBDT4_1up") && fSysName.Contains("_BDT4") && f_n_bjets>0 && f_tau_0_n_charged_tracks==3)
      ) {
    ff_ew += errff_ew;
    fffff_ew += errfffff_ew;
  }
  else if((fSysName.Contains("FakeFactor_WjetsBveto1pBDT1_1down") && fSysName.Contains("_BDT1") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBveto1pBDT2_1down") && fSysName.Contains("_BDT2") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBveto1pBDT3_1down") && fSysName.Contains("_BDT3") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBveto1pBDT4_1down") && fSysName.Contains("_BDT4") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBtag1pBDT1_1down") && fSysName.Contains("_BDT1") && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBtag1pBDT2_1down") && fSysName.Contains("_BDT2") && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBtag1pBDT3_1down") && fSysName.Contains("_BDT3") && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||
          (fSysName.Contains("FakeFactor_WjetsBtag1pBDT4_1down") && fSysName.Contains("_BDT4") && f_n_bjets>0 && f_tau_0_n_charged_tracks==1) ||

          (fSysName.Contains("FakeFactor_WjetsBveto3pBDT1_1down") && fSysName.Contains("_BDT1") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBveto3pBDT2_1down") && fSysName.Contains("_BDT2") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBveto3pBDT3_1down") && fSysName.Contains("_BDT3") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBveto3pBDT4_1down") && fSysName.Contains("_BDT4") && f_n_bjets==0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBtag3pBDT1_1down") && fSysName.Contains("_BDT1") && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBtag3pBDT2_1down") && fSysName.Contains("_BDT2") && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBtag3pBDT3_1down") && fSysName.Contains("_BDT3") && f_n_bjets>0 && f_tau_0_n_charged_tracks==3) ||
          (fSysName.Contains("FakeFactor_WjetsBtag3pBDT4_1down") && fSysName.Contains("_BDT4") && f_n_bjets>0 && f_tau_0_n_charged_tracks==3)
      ) {
    ff_ew -= errff_ew;
    fffff_ew -= errfffff_ew;
  }

  if( (fSysName.Contains("FakeDphi_WjetsBDT1SysUp") && fSysName.Contains("_BDT1") && f_n_bjets==0) ||
      (fSysName.Contains("FakeDphi_WjetsBDT2SysUp") && fSysName.Contains("_BDT2") && f_n_bjets==0) ||
      (fSysName.Contains("FakeDphi_WjetsBDT3SysUp") && fSysName.Contains("_BDT3") && f_n_bjets==0) ||
      (fSysName.Contains("FakeDphi_WjetsBDT4SysUp") && fSysName.Contains("_BDT4") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ) {
    nonclosure_W += nonclosure_W_err;
  }
  else if( (fSysName.Contains("FakeDphi_WjetsBDT1SysDo") && fSysName.Contains("_BDT1") && f_n_bjets==0) ||
      (fSysName.Contains("FakeDphi_WjetsBDT2SysDo") && fSysName.Contains("_BDT2") && f_n_bjets==0) ||
      (fSysName.Contains("FakeDphi_WjetsBDT3SysDo") && fSysName.Contains("_BDT3") && f_n_bjets==0) ||
      (fSysName.Contains("FakeDphi_WjetsBDT4SysDo") && fSysName.Contains("_BDT4") && f_n_bjets==0 && f_tau_0_n_charged_tracks==1) ) {
    nonclosure_W -= nonclosure_W_err;
  }

  double retval(0);
  TString process="";
  if(!this->fSample->getTag("~myWjetsFF",process)) std::cout<<"What is your process name???!!!\n";
  if     (process=="FFDPHI")     retval = ff_ew * nonclosure_W;
  else if(process=="FFPT")  retval = ff_ew;
  else if(process=="FFWPTDPHI")  retval = fffff_ew;
  DEBUGclass("returning");
  return retval;
}
//______________________________________________________________________________________________

bool ptReweightBDT::initializeSelf(){
  // initialize this observable on a sample/tree
  DEBUGclass("initializing");

  // since this function is only called once per sample, we can
  // perform any checks that seem necessary
  if(!this->fTree){
    DEBUGclass("no tree, terminating");
    return false;
  }

  // if you want to use a TTreeFormula, can may construct it here
  /* example block for TTreeFormula method:
  this->fFormula = new TTreeFormula("branch1 + branch2",this->fTree);
  */

  // if you want to use the TTree::SetBranchAddress method, you can
  // call TTree::SetBranchAddress here
  // please note that this method is highly discouraged.
  // if a branch you access via this method is used by any other
  // observable, you will 'steal' the branch address from that
  // observable, leading to the other observable returning wrong
  // results
  /* example block for TTree::SetBranchAddress method:
  this->fTree->SetBranchAddress("branch1",&(this->fBranch1));
  this->fTree->SetBranchAddress("branch2",&(this->fBranch2));
  */


  this->tau_0_phi                 = new TTreeFormula( "tau_0_phi",     "tau_0_phi",      this->fTree);
  this->tau_0_n_charged_tracks            = new TTreeFormula( "tau_0_n_charged_tracks","tau_0_n_charged_tracks", this->fTree);
  this->tau_0_pt                  = new TTreeFormula( "tau_0_pt",     "tau_0_pt",      this->fTree);
  this->lep_0_iso_Gradient        = new TTreeFormula( "lep_0_iso_Gradient",     "lep_0_iso_Gradient",      this->fTree);
  this->lephad_met_lep1_cos_dphi  = new TTreeFormula( "lephad_met_lep1_cos_dphi", "lephad_met_lep1_cos_dphi", this->fTree);
  this->n_bjets                   = new TTreeFormula( "n_bjets",      "n_bjets",      this->fTree);
  return true;
}

//______________________________________________________________________________________________

bool ptReweightBDT::finalizeSelf(){
  // finalize this observable on a sample/tree
  DEBUGclass("finalizing");
  // here, you should undo anything that you did while initializing
  /* example block for TTreeFormula method:
  delete this->fFormula;
  this->fFormula = NULL;
  */
  delete this->tau_0_phi;
  delete this->tau_0_pt;
  delete this->tau_0_n_charged_tracks;
  delete this->lephad_met_lep1_cos_dphi;
  delete this->lep_0_iso_Gradient;
  delete this->n_bjets;

  return true;
}
//______________________________________________________________________________________________
void ptReweightBDT::printError(const TString& name)
{
  std::cout  << "ERROR in getting histos " << name << std::endl;
}

//______________________________________________________________________________________________
bool ptReweightBDT::checkFF(int prongs,int tags,int bdt,int dphi)const
{
  if(tags==1&&dphi>0) return false;
  if(prongs==1&&bdt==4) return false;
  return true;
}
//______________________________________________________________________________________________
std::string ptReweightBDT::resolveFileName(int prongs,int tags,int bdt,int dphi)const
{
  if(!checkFF(prongs,tags,bdt,dphi)) return "";
  std::string s_prongs,s_tags,s_bdt,s_dphi,s_region;

  if(prongs==0)  s_prongs="1p"; else s_prongs="3p";
  if(tags==0)    s_tags="Bveto"; else s_tags="Btag";
  if(tags==0)    s_region="WCR"; else s_region="SSWCR";
  switch(bdt){
    case 0: s_bdt="";     break;
    case 1: s_bdt="BDT1"; break;
    case 2: s_bdt="BDT2"; break;
    case 3: s_bdt="BDT3"; break;
    case 4: s_bdt="BDT4"; break;
  }
  switch(dphi){
    case 0: s_dphi="";      break;
    case 1: s_dphi="Dphi1"; break;
    case 2: s_dphi="Dphi2"; break;
    case 3: s_dphi="Dphi3"; break;
  }
  return s_region+"15"+s_tags+s_bdt+"lephad"+"TauPtFF"+s_tags+s_prongs+s_dphi+".root";
}
//______________________________________________________________________________________________
std::string ptReweightBDT::resolveHistName(int prongs,int tags,int bdt,int dphi)const
{
  std::string s_prongs,s_tags,s_bdt,s_dphi;
  if(prongs==0)  s_prongs="1p"; else s_prongs="3p";
  if(tags==0)    s_tags="Bveto"; else s_tags="Btag";
  switch(bdt){
    case 0: s_bdt="";     break;
    case 1: s_bdt="BDT1"; break;
    case 2: s_bdt="BDT2"; break;
    case 3: s_bdt="BDT3"; break;
    case 4: s_bdt="BDT4"; break;
  }
  switch(dphi){
    case 0: s_dphi="";      break;
    case 1: s_dphi="Dphi1"; break;
    case 2: s_dphi="Dphi2"; break;
    case 3: s_dphi="Dphi3"; break;
  }
  return s_tags+s_bdt+"FF_lephad_"+"TauPtFF"+s_tags+s_prongs+s_dphi;
}

//______________________________________________________________________________________________
ptReweightBDT::ptReweightBDT(const TString& name):
LepHadObservable(name)
{
  // constructor with name argument
  DEBUGclass("constructor called with '%s'",name.Data());
  fSysName = name;



  // when files are closed histograms also dissapear, so detatch them and keep in this directory:
  m_histoDir = new TDirectory("ffhistoDir","ffhistoDir");
  // temporary pointer to ff files:
  TFile* tempFile=0;

  std::cout << "INFO: ptReweightBDT.cxx getting histograms from files. " << std::endl;
  ///////////////////////////////
  //
  //  Wjets FF
  //
  ///////////////////////////////
/*
  1-prong:  prongs=0
  3-prong:  prongs=1
  bveto:    tags=0
  btag:     tags=1
  nobdt:    bdt=0
  bdt1:     bdt=1
  bdt2:     bdt=2
  bdt3:     bdt=3
  bdt4:     bdt=4
  nodphi:   dphi=0
  dphi<1:   dphi=1
  1<dphi<2: dphi=2
  2<dphi:   dphi=3
*/

  for(int prongs=0;prongs<2;++prongs)
    for(int tags=0;tags<2;++tags)
      for(int bdt=0;bdt<5;++bdt)
        for(int dphi=0;dphi<4;++dphi)
        {
          h_ff_wcr[prongs][tags][bdt][dphi]     = NULL;
          h_ff_wcr_up[prongs][tags][bdt][dphi]  = NULL;
          h_ff_wcr_down[prongs][tags][bdt][dphi]= NULL;
          std::string fn = resolveFileName(prongs,tags,bdt,dphi);
          if(fn=="") continue;
          std::string hn = resolveHistName(prongs,tags,bdt,dphi);
          std::cout << "filename " << fn << std::endl;
          std::cout << "histname " << hn << std::endl;
          tempFile=TFile::Open(("FakeFactors/"+fn).c_str());
          if(!tempFile) {std::cout << "ERROR cant open FF file " << fn << std::endl; continue;}
          else
          {
            h_ff_wcr[prongs][tags][bdt][dphi]     = (TH1F*)tempFile->Get((hn).c_str());               h_ff_wcr[prongs][tags][bdt][dphi]     ->SetDirectory(m_histoDir);
            h_ff_wcr_up[prongs][tags][bdt][dphi]  = (TH1F*)tempFile->Get((hn+"_up").c_str());         h_ff_wcr_up[prongs][tags][bdt][dphi]  ->SetDirectory(m_histoDir);
            h_ff_wcr_down[prongs][tags][bdt][dphi]= (TH1F*)tempFile->Get((hn+"_down").c_str());       h_ff_wcr_down[prongs][tags][bdt][dphi]->SetDirectory(m_histoDir);
            tempFile->Close(); delete tempFile; tempFile=0;
          }
        }


  tempFile=TFile::Open("FakeFactors/WCRBvetoBDT2lephadTauPtFFBveto1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WCRBvetoBDT2lephadTauPtFFBveto1p.root " << std::endl;
  else
  {
    h_ff_wcr_1p_0tag_bdt2     = (TH1F*)tempFile->Get("BvetoBDT2FF_lephad_TauPtFFBveto1p");           if(!h_ff_wcr_1p_0tag_bdt2) printError("bdt2 1p");      else     h_ff_wcr_1p_0tag_bdt2->SetDirectory(m_histoDir);
    h_ff_wcr_1p_0tag_bdt2_up  = (TH1F*)tempFile->Get("BvetoBDT2FF_lephad_TauPtFFBveto1p_up");        if(!h_ff_wcr_1p_0tag_bdt2_up) printError("bdt2 1p");   else     h_ff_wcr_1p_0tag_bdt2_up->SetDirectory(m_histoDir);
    h_ff_wcr_1p_0tag_bdt2_down= (TH1F*)tempFile->Get("BvetoBDT2FF_lephad_TauPtFFBveto1p_down");      if(!h_ff_wcr_1p_0tag_bdt2_down) printError("bdt2 1p"); else     h_ff_wcr_1p_0tag_bdt2_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WCRBvetoBDT3lephadTauPtFFBveto1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WCRBvetoBDT3lephadTauPtFFBveto1p.root " << std::endl;
  else
  {
    h_ff_wcr_1p_0tag_bdt3     = (TH1F*)tempFile->Get("BvetoBDT3FF_lephad_TauPtFFBveto1p");           if(!h_ff_wcr_1p_0tag_bdt3)      printError("bdt3 1p"); else     h_ff_wcr_1p_0tag_bdt3->SetDirectory(m_histoDir);
    h_ff_wcr_1p_0tag_bdt3_up  = (TH1F*)tempFile->Get("BvetoBDT3FF_lephad_TauPtFFBveto1p_up");        if(!h_ff_wcr_1p_0tag_bdt3_up)   printError("bdt3 1p"); else     h_ff_wcr_1p_0tag_bdt3_up->SetDirectory(m_histoDir);
    h_ff_wcr_1p_0tag_bdt3_down= (TH1F*)tempFile->Get("BvetoBDT3FF_lephad_TauPtFFBveto1p_down");      if(!h_ff_wcr_1p_0tag_bdt3_down) printError("bdt3 1p"); else     h_ff_wcr_1p_0tag_bdt3_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WCRBvetoBDT4lephadTauPtFFBveto1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WCRBvetoBDT4lephadTauPtFFBveto1p.root " << std::endl;
  else
  {
    h_ff_wcr_1p_0tag_bdt4     = (TH1F*)tempFile->Get("BvetoBDT4FF_lephad_TauPtFFBveto1p");           if(!h_ff_wcr_1p_0tag_bdt4)      printError("bdt4 1p"); else     h_ff_wcr_1p_0tag_bdt4->SetDirectory(m_histoDir);
    h_ff_wcr_1p_0tag_bdt4_up  = (TH1F*)tempFile->Get("BvetoBDT4FF_lephad_TauPtFFBveto1p_up");        if(!h_ff_wcr_1p_0tag_bdt4_up)   printError("bdt4 1p"); else     h_ff_wcr_1p_0tag_bdt4_up->SetDirectory(m_histoDir);
    h_ff_wcr_1p_0tag_bdt4_down= (TH1F*)tempFile->Get("BvetoBDT4FF_lephad_TauPtFFBveto1p_down");      if(!h_ff_wcr_1p_0tag_bdt4_down) printError("bdt4 1p"); else     h_ff_wcr_1p_0tag_bdt4_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  ///////////////////////
  //
  //  B-VETO 3-PRONG
  //
  tempFile=TFile::Open("FakeFactors/WCRBvetoBDT1lephadTauPtFFBveto3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WCRBvetoBDT1lephadTauPtFFBveto3p.root " << std::endl;
  else
  {
    h_ff_wcr_3p_0tag_bdt1     = (TH1F*)tempFile->Get("BvetoBDT1FF_lephad_TauPtFFBveto3p");           if(!h_ff_wcr_3p_0tag_bdt1)      printError("bdt1 3p"); else     h_ff_wcr_3p_0tag_bdt1->SetDirectory(m_histoDir);
    h_ff_wcr_3p_0tag_bdt1_up  = (TH1F*)tempFile->Get("BvetoBDT1FF_lephad_TauPtFFBveto3p_up");        if(!h_ff_wcr_3p_0tag_bdt1_up)   printError("bdt1 3p"); else     h_ff_wcr_3p_0tag_bdt1_up->SetDirectory(m_histoDir);
    h_ff_wcr_3p_0tag_bdt1_down= (TH1F*)tempFile->Get("BvetoBDT1FF_lephad_TauPtFFBveto3p_down");      if(!h_ff_wcr_3p_0tag_bdt1_down) printError("bdt1 3p"); else     h_ff_wcr_3p_0tag_bdt1_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WCRBvetoBDT2lephadTauPtFFBveto3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WCRBvetoBDT2lephadTauPtFFBveto3p.root " << std::endl;
  else
  {
    h_ff_wcr_3p_0tag_bdt2     = (TH1F*)tempFile->Get("BvetoBDT2FF_lephad_TauPtFFBveto3p");           if(!h_ff_wcr_3p_0tag_bdt2)      printError("bdt2 3p"); else     h_ff_wcr_3p_0tag_bdt2->SetDirectory(m_histoDir);
    h_ff_wcr_3p_0tag_bdt2_up  = (TH1F*)tempFile->Get("BvetoBDT2FF_lephad_TauPtFFBveto3p_up");        if(!h_ff_wcr_3p_0tag_bdt2_up)   printError("bdt2 3p"); else     h_ff_wcr_3p_0tag_bdt2_up->SetDirectory(m_histoDir);
    h_ff_wcr_3p_0tag_bdt2_down= (TH1F*)tempFile->Get("BvetoBDT2FF_lephad_TauPtFFBveto3p_down");      if(!h_ff_wcr_3p_0tag_bdt2_down) printError("bdt2 3p"); else     h_ff_wcr_3p_0tag_bdt2_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/WCRBvetoBDT3lephadTauPtFFBveto3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WCRBvetoBDT3lephadTauPtFFBveto3p.root " << std::endl;
  else
  {
    h_ff_wcr_3p_0tag_bdt3     = (TH1F*)tempFile->Get("BvetoBDT3FF_lephad_TauPtFFBveto3p");           if(!h_ff_wcr_3p_0tag_bdt3)      printError("bdt3 3p"); else     h_ff_wcr_3p_0tag_bdt3->SetDirectory(m_histoDir);
    h_ff_wcr_3p_0tag_bdt3_up  = (TH1F*)tempFile->Get("BvetoBDT3FF_lephad_TauPtFFBveto3p_up");        if(!h_ff_wcr_3p_0tag_bdt3_up)   printError("bdt3 3p"); else     h_ff_wcr_3p_0tag_bdt3_up->SetDirectory(m_histoDir);
    h_ff_wcr_3p_0tag_bdt3_down= (TH1F*)tempFile->Get("BvetoBDT3FF_lephad_TauPtFFBveto3p_down");      if(!h_ff_wcr_3p_0tag_bdt3_down) printError("bdt3 3p"); else     h_ff_wcr_3p_0tag_bdt3_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  ///////////////////////
  //
  //  B-TAG 1-PRONG
  //
  tempFile=TFile::Open("FakeFactors/SSWCRBtagBDT1lephadTauPtFFBtag1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWCRBtagBDT1lephadTauPtFFBtag1p.root " << std::endl;
  else
  {
    h_ff_wcr_1p_1tag_bdt1     = (TH1F*)tempFile->Get("BtagBDT1FF_lephad_TauPtFFBtag1p");           if(!h_ff_wcr_1p_1tag_bdt1)      printError("bdt1 1p"); else     h_ff_wcr_1p_1tag_bdt1->SetDirectory(m_histoDir);
    h_ff_wcr_1p_1tag_bdt1_up  = (TH1F*)tempFile->Get("BtagBDT1FF_lephad_TauPtFFBtag1p_up");        if(!h_ff_wcr_1p_1tag_bdt1_up)   printError("bdt1 1p"); else     h_ff_wcr_1p_1tag_bdt1_up->SetDirectory(m_histoDir);
    h_ff_wcr_1p_1tag_bdt1_down= (TH1F*)tempFile->Get("BtagBDT1FF_lephad_TauPtFFBtag1p_down");      if(!h_ff_wcr_1p_1tag_bdt1_down) printError("bdt1 1p"); else     h_ff_wcr_1p_1tag_bdt1_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/SSWCRBtagBDT2lephadTauPtFFBtag1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWCRBtagBDT2lephadTauPtFFBtag1p.root " << std::endl;
  else
  {
    h_ff_wcr_1p_1tag_bdt2     = (TH1F*)tempFile->Get("BtagBDT2FF_lephad_TauPtFFBtag1p");           if(!h_ff_wcr_1p_1tag_bdt2)      printError("bdt2 1p"); else     h_ff_wcr_1p_1tag_bdt2->SetDirectory(m_histoDir);
    h_ff_wcr_1p_1tag_bdt2_up  = (TH1F*)tempFile->Get("BtagBDT2FF_lephad_TauPtFFBtag1p_up");        if(!h_ff_wcr_1p_1tag_bdt2_up)   printError("bdt2 1p"); else     h_ff_wcr_1p_1tag_bdt2_up->SetDirectory(m_histoDir);
    h_ff_wcr_1p_1tag_bdt2_down= (TH1F*)tempFile->Get("BtagBDT2FF_lephad_TauPtFFBtag1p_down");      if(!h_ff_wcr_1p_1tag_bdt2_down) printError("bdt2 1p"); else     h_ff_wcr_1p_1tag_bdt2_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/SSWCRBtagBDT3lephadTauPtFFBtag1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWCRBtagBDT3lephadTauPtFFBtag1p.root " << std::endl;
  else
  {
    h_ff_wcr_1p_1tag_bdt3     = (TH1F*)tempFile->Get("BtagBDT3FF_lephad_TauPtFFBtag1p");           if(!h_ff_wcr_1p_1tag_bdt3)      printError("bdt3 1p"); else     h_ff_wcr_1p_1tag_bdt3->SetDirectory(m_histoDir);
    h_ff_wcr_1p_1tag_bdt3_up  = (TH1F*)tempFile->Get("BtagBDT3FF_lephad_TauPtFFBtag1p_up");        if(!h_ff_wcr_1p_1tag_bdt3_up)   printError("bdt3 1p"); else     h_ff_wcr_1p_1tag_bdt3_up->SetDirectory(m_histoDir);
    h_ff_wcr_1p_1tag_bdt3_down= (TH1F*)tempFile->Get("BtagBDT3FF_lephad_TauPtFFBtag1p_down");      if(!h_ff_wcr_1p_1tag_bdt3_down) printError("bdt3 1p"); else     h_ff_wcr_1p_1tag_bdt3_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/SSWCRBtagBDT4lephadTauPtFFBtag1p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWCRBtagBDT4lephadTauPtFFBtag1p.root " << std::endl;
  else
  {
    h_ff_wcr_1p_1tag_bdt4     = (TH1F*)tempFile->Get("BtagBDT4FF_lephad_TauPtFFBtag1p");           if(!h_ff_wcr_1p_1tag_bdt4)      printError("bdt4 1p"); else     h_ff_wcr_1p_1tag_bdt4->SetDirectory(m_histoDir);
    h_ff_wcr_1p_1tag_bdt4_up  = (TH1F*)tempFile->Get("BtagBDT4FF_lephad_TauPtFFBtag1p_up");        if(!h_ff_wcr_1p_1tag_bdt4_up)   printError("bdt4 1p"); else     h_ff_wcr_1p_1tag_bdt4_up->SetDirectory(m_histoDir);
    h_ff_wcr_1p_1tag_bdt4_down= (TH1F*)tempFile->Get("BtagBDT4FF_lephad_TauPtFFBtag1p_down");      if(!h_ff_wcr_1p_1tag_bdt4_down) printError("bdt4 1p"); else     h_ff_wcr_1p_1tag_bdt4_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  ///////////////////////
  //
  //  B-TAG 3-PRONG
  //
  tempFile=TFile::Open("FakeFactors/SSWCRBtagBDT1lephadTauPtFFBtag3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWCRBtagBDT1lephadTauPtFFBtag3p.root " << std::endl;
  else
  {
    h_ff_wcr_3p_1tag_bdt1     = (TH1F*)tempFile->Get("BtagBDT1FF_lephad_TauPtFFBtag3p");           h_ff_wcr_3p_1tag_bdt1     ->SetDirectory(m_histoDir);
    h_ff_wcr_3p_1tag_bdt1_up  = (TH1F*)tempFile->Get("BtagBDT1FF_lephad_TauPtFFBtag3p_up");        h_ff_wcr_3p_1tag_bdt1_up  ->SetDirectory(m_histoDir);
    h_ff_wcr_3p_1tag_bdt1_down= (TH1F*)tempFile->Get("BtagBDT1FF_lephad_TauPtFFBtag3p_down");      h_ff_wcr_3p_1tag_bdt1_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/SSWCRBtagBDT2lephadTauPtFFBtag3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWCRBtagBDT2lephadTauPtFFBtag3p.root " << std::endl;
  else
  {
    h_ff_wcr_3p_1tag_bdt2     = (TH1F*)tempFile->Get("BtagBDT2FF_lephad_TauPtFFBtag3p");           h_ff_wcr_3p_1tag_bdt2     ->SetDirectory(m_histoDir);
    h_ff_wcr_3p_1tag_bdt2_up  = (TH1F*)tempFile->Get("BtagBDT2FF_lephad_TauPtFFBtag3p_up");        h_ff_wcr_3p_1tag_bdt2_up  ->SetDirectory(m_histoDir);
    h_ff_wcr_3p_1tag_bdt2_down= (TH1F*)tempFile->Get("BtagBDT2FF_lephad_TauPtFFBtag3p_down");      h_ff_wcr_3p_1tag_bdt2_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

  tempFile=TFile::Open("FakeFactors/SSWCRBtagBDT3lephadTauPtFFBtag3p.root");
  if(!tempFile) std::cout << "ERROR cant open FF file SSWCRBtagBDT3lephadTauPtFFBtag3p.root " << std::endl;
  else
  {
    h_ff_wcr_3p_1tag_bdt3     = (TH1F*)tempFile->Get("BtagBDT3FF_lephad_TauPtFFBtag3p");           h_ff_wcr_3p_1tag_bdt3     ->SetDirectory(m_histoDir);
    h_ff_wcr_3p_1tag_bdt3_up  = (TH1F*)tempFile->Get("BtagBDT3FF_lephad_TauPtFFBtag3p_up");        h_ff_wcr_3p_1tag_bdt3_up  ->SetDirectory(m_histoDir);
    h_ff_wcr_3p_1tag_bdt3_down= (TH1F*)tempFile->Get("BtagBDT3FF_lephad_TauPtFFBtag3p_down");      h_ff_wcr_3p_1tag_bdt3_down->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }






  // Wjets correction
  tempFile=TFile::Open("FakeFactors/WCRdphiBveto1pBDT1lephadTauMETDphiCorrection.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WCRdphiBveto1pBDT1lephadTauMETDphiCorrection.root " << std::endl;
  else
  {
    h_corr_wcr_1p_0tag_bdt1 = (TH1F*)tempFile->Get("dphicorr_Bveto1pBDT1_lephad_TauMETDphiCorrection");         if(!h_corr_wcr_1p_0tag_bdt1)      printError("bdt1 1p"); else     h_corr_wcr_1p_0tag_bdt1->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  tempFile=TFile::Open("FakeFactors/WCRdphiBveto1pBDT2lephadTauMETDphiCorrection.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WCRdphiBveto1pBDT2lephadTauMETDphiCorrection.root " << std::endl;
  else
  {
    h_corr_wcr_1p_0tag_bdt2 = (TH1F*)tempFile->Get("dphicorr_Bveto1pBDT2_lephad_TauMETDphiCorrection");        if(!h_corr_wcr_1p_0tag_bdt2)      printError("bdt2 1p"); else     h_corr_wcr_1p_0tag_bdt2->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  tempFile=TFile::Open("FakeFactors/WCRdphiBveto1pBDT3lephadTauMETDphiCorrection.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WCRdphiBveto1pBDT3lephadTauMETDphiCorrection.root " << std::endl;
  else
  {
    h_corr_wcr_1p_0tag_bdt3 = (TH1F*)tempFile->Get("dphicorr_Bveto1pBDT3_lephad_TauMETDphiCorrection");         if(!h_corr_wcr_1p_0tag_bdt3)      printError("bdt3 1p"); else     h_corr_wcr_1p_0tag_bdt3->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }
  tempFile=TFile::Open("FakeFactors/WCRdphiBveto1pBDT4lephadTauMETDphiCorrection.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WCRdphiBveto1pBDT4lephadTauMETDphiCorrection.root " << std::endl;
  else
  {
    h_corr_wcr_1p_0tag_bdt4 = (TH1F*)tempFile->Get("dphicorr_Bveto1pBDT4_lephad_TauMETDphiCorrection");        if(!h_corr_wcr_1p_0tag_bdt4)      printError("bdt4 1p"); else     h_corr_wcr_1p_0tag_bdt4->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }



  tempFile=TFile::Open("FakeFactors/WCRdphiBveto3pBDT123lephadTauMETDphiCorrection.root");
  if(!tempFile) std::cout << "ERROR cant open FF file WCRdphiBveto3pBDT123lephadTauMETDphiCorrection.root " << std::endl;
  else
  {
    h_corr_wcr_3p_0tag_bdt123 = (TH1F*)tempFile->Get("dphicorr_Bveto3pBDT123_lephad_TauMETDphiCorrection");      if(!h_corr_wcr_3p_0tag_bdt123)      printError("bdt123 3p"); else     h_corr_wcr_3p_0tag_bdt123->SetDirectory(m_histoDir);
    tempFile->Close(); delete tempFile; tempFile=0;
  }

}
