#include "Htautau/FakeLepSel_ll.h"
#include <limits>

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(FakeLepSel_ll)

//______________________________________________________________________________________________

FakeLepSel_ll::FakeLepSel_ll(){
  // default constructor
  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

FakeLepSel_ll::~FakeLepSel_ll(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* FakeLepSel_ll::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  //  bnames->SetOwner(false);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));

  bnames->Add(new TObjString("leptons"));
  bnames->Add(new TObjString("leptons_pt"));
  bnames->Add(new TObjString("leptons_eta"));
  bnames->Add(new TObjString("leptons_phi"));
  bnames->Add(new TObjString("leptons_cluster_eta"));
  bnames->Add(new TObjString("leptons_id_medium"));
  bnames->Add(new TObjString("leptons_id_tight"));
  bnames->Add(new TObjString("leptons_id_loose"));
  bnames->Add(new TObjString("leptons_iso_wp"));

  //info on first two leptons:
  bnames->Add(new TObjString("lep_0"));
  bnames->Add(new TObjString("lep_1"));
  bnames->Add(new TObjString("lep_0_pt"));
  bnames->Add(new TObjString("lep_1_pt"));
  bnames->Add(new TObjString("lep_0_eta"));
  bnames->Add(new TObjString("lep_1_eta"));
  bnames->Add(new TObjString("lep_0_phi"));
  bnames->Add(new TObjString("lep_1_phi"));

  bnames->Add(new TObjString("jet_0_eta"));
  bnames->Add(new TObjString("jet_1_eta"));
  bnames->Add(new TObjString("jet_0_phi"));
  bnames->Add(new TObjString("jet_1_phi"));

  return bnames;
}

//______________________________________________________________________________________________

double FakeLepSel_ll::getValue() const {
  // in the rest of this function, you should retrieve the data and calculate your return value

  //info on first two leptons:
  int lep_0 = this->lep_0->EvalInstance();
  int lep_1 = this->lep_1->EvalInstance();
  double lep_0_pt  = this->lep_0_pt->EvalInstance();
  double lep_1_pt  = this->lep_1_pt->EvalInstance();
  double lep_0_eta = this->lep_0_eta->EvalInstance();
  double lep_1_eta = this->lep_1_eta->EvalInstance();
  double lep_0_phi = this->lep_0_phi->EvalInstance();
  double lep_1_phi = this->lep_1_phi->EvalInstance();

  double jet_0_eta = this->jet_0_eta->EvalInstance();
  double jet_1_eta = this->jet_1_eta->EvalInstance();
  double jet_0_phi = this->jet_0_phi->EvalInstance();
  double jet_1_phi = this->jet_1_phi->EvalInstance();

  //leptons vector branches
  int  nleptons			=  leptons		->GetNdata();
  int  nleptons_pt		=  leptons_pt		->GetNdata();
  int  nleptons_eta		=  leptons_eta		->GetNdata();
  int  nleptons_phi		=  leptons_phi		->GetNdata();
  int  nleptons_cluster_eta	=  leptons_cluster_eta	->GetNdata();
  int  nleptons_id_medium	=  leptons_id_medium	->GetNdata();
  int  nleptons_id_tight	=  leptons_id_tight	->GetNdata();
  int  nleptons_id_loose	=  leptons_id_loose	->GetNdata();
  int  nleptons_iso_wp		=  leptons_iso_wp	->GetNdata();

  if ((nleptons <= 2) || (nleptons_pt <= 2) || (nleptons_eta <=2) || (nleptons_cluster_eta <= 2) || (nleptons_id_medium <=2 )|| (nleptons_id_tight <=2 )||( nleptons_id_loose <= 2) || (nleptons_iso_wp <= 2) )
    {
      DEBUGclass("No additional lepton present.");
      return 0; //do not select the event if there is no additional lepton
    };


  int leptons_fake			= 0;
  double leptons_pt_fake		= 0;
  double leptons_eta_fake		= 0;
  double leptons_phi_fake		= 0;
  double leptons_cluster_eta_fake	= 0;
  int leptons_id_medium_fake		= 0;
  int leptons_id_tight_fake		= 0;
  int leptons_id_loose_fake		= 0;
  int leptons_iso_wp_fake		= 0;

   // std::cout << fExpression <<std::endl;
    // std::cout << "lep_0_pt= " << lep_0_pt<< ", lep_1_pt= " << lep_1_pt <<", lep_0_eta= " << lep_0_eta<< ", lep_1_eta= " << lep_1_eta <<  "lep_0_phi= " << lep_0_phi <<  "lep_1_phi= " << lep_1_phi  <<std::endl;
    // std::cout <<  "leptons_pt[0]= " << leptons_pt->EvalInstance(0)<<"leptons_pt[1]= " << leptons_pt->EvalInstance(1) << "leptons_pt[2]= " << leptons_pt->EvalInstance(2)<<std::endl;
    // std::cout << "leptons_eta[0]= " << leptons_eta->EvalInstance(0)<<"leptons_eta[1]= " << leptons_eta->EvalInstance(1) << "leptons_eta[2]= " << leptons_eta->EvalInstance(2)<<std::endl;
    // std::cout <<  "leptons_phi[0]= " << leptons_phi->EvalInstance(0)<<"leptons_phi[1]= " << leptons_phi->EvalInstance(1) << "leptons_phi[2]= " << leptons_phi->EvalInstance(2)<<std::endl;

  //find the odd one out. Assign its kinematic properties to the ones used for the third lepton, which need to be initialized to 0
  bool FoundThirdLepton = false;
  for (int i=0;i<3;i++)
    {
      //need eta and phi of the lepton with this index, and of lep_0 and lep_1
      double eta_candidate = this->leptons_eta->EvalInstance(i);
      double phi_candidate = this->leptons_phi->EvalInstance(i);

      double dRsquared_lep0 = deltaRsquared( eta_candidate, lep_0_eta, phi_candidate, lep_0_phi ) ;
      double dRsquared_lep1 = deltaRsquared( eta_candidate, lep_1_eta, phi_candidate, lep_1_phi ) ;
      //            std::cout << "dRsquared_lep0= "<< dRsquared_lep0<< ", dRsquared_lep1= " << dRsquared_lep1<<std::endl;
      if ((dRsquared_lep0 > 0.01)  && (dRsquared_lep1 > 0.01))
	{
	  if (FoundThirdLepton)
	    {
	    WARNclass("Found two matches for the Third Lepton. Using the one with larger pt. Investigate if that happens often.");
	    //check whether the second one has higher pt
	    if (this->leptons_pt->EvalInstance(i) < leptons_pt_fake) //second one has smaller pt
	      continue;
	    // if it does, change the variables
	    //otherwise don't, i.e. continue with the for loop
	    }
	  //let the fake properties point to this index
	   leptons_fake			= this->leptons->EvalInstance(i);
	   leptons_pt_fake		= this->leptons_pt->EvalInstance(i);
	   leptons_eta_fake		= this->leptons_eta->EvalInstance(i);
	   leptons_phi_fake		= this->leptons_phi->EvalInstance(i);
	   leptons_cluster_eta_fake	= this->leptons_cluster_eta->EvalInstance(i);
	   leptons_id_medium_fake	= this->leptons_id_medium->EvalInstance(i);
	   leptons_id_tight_fake	= this->leptons_id_tight->EvalInstance(i);
	   leptons_id_loose_fake	= this->leptons_id_loose->EvalInstance(i);
	   leptons_iso_wp_fake		= this->leptons_iso_wp->EvalInstance(i);

	  FoundThirdLepton = true;
	}
      //else go to next index and if it never is found, the bool will stay false and we do not use this event
    }

  if (FoundThirdLepton == false) return 0; //do not use this event as it has strange topology (two leptons very close)

  //  std::cout << "leptons_pt_fake= " << leptons_pt_fake<< ", leptons_eta_fake= " << leptons_eta_fake <<std::endl;

  bool IsLepOfInterest = 0;
  //return true in case the lepton fulfills
  //loose id/iso criteria if the name contains Loose,
  //tight id/iso criteria if the name contains Tight

  //pt, eta cuts identical to nominal selection
  double pt_elec = 15*1000.;
  double pt_muon = 10*1000.;
  double eta_elec = 2.47;
  double eta_muon = 2.47;

  if (selectElectron && leptons_fake == 1) return 0;
  if (selectMuon && leptons_fake  ==2 ) return 0;

  //return false if pt or eta cuts are not fulfilled
 if (leptons_fake == 2) //electron
   {
     //std::cout << "It's an electron!" << std::endl;
     if ((leptons_pt_fake < pt_elec) || fabs(leptons_cluster_eta_fake ) > eta_elec)
       return 0;  //return false as the lepton fails pt and eta cuts
   }
 else if (leptons_fake == 1) //muon
   {
     //std::cout << "It's a muon!" << std::endl;
     if ((leptons_pt_fake < pt_muon) || fabs(leptons_eta_fake) > eta_muon)
       return 0; //return false as the lepton fails pt and eta cuts
   }
 else
   std::cout << "Strange id of third lepton " << leptons_fake <<std::endl;
 // iso and id: depending on the name of the instance
 //loose id/iso criteria if the name contains Loose, tight id/iso criteria if the name contains Tight




 if (useLoose)
   {
     // select loose lepton
     DEBUGclass("check if the lepton passes loose id");
     IsLepOfInterest = (leptons_id_loose_fake == 1);
     //     IsLepOfInterest = ((leptons_iso_wp_2 % 100) < 10 && (leptons_id_loose_2 == 1 && leptons_id_medium_2 == 0)); //inverted isolation and id loose, non-medium
   }

 else if (useTight)
   {
     DEBUGclass("check if the lepton passes tight id");
     IsLepOfInterest = ( leptons_id_tight_fake == 1);
     //IsLepOfInterest = ((leptons_iso_wp_2 % 100) >= 10 && ( leptons_id_medium_2 == 1)); //tight iso and medium id
   }

 else IsLepOfInterest = 0;


  DEBUGclass("returning");
  if (makeSelection)  return IsLepOfInterest;

  if (makeKinematics)
    {
      if (plotEta) return leptons_eta_fake;
      else if (plotPt) return leptons_pt_fake;
      else if (plotDRlep0) return sqrt(deltaRsquared(  leptons_eta_fake, lep_0_eta, leptons_phi_fake, lep_0_phi ) );
      else if (plotDRlep1) return sqrt(deltaRsquared(  leptons_eta_fake, lep_1_eta, leptons_phi_fake, lep_1_phi ) );
      else if (plotDRjet)
	{
	  double minDRtoJet = sqrt(deltaRsquared( leptons_eta_fake, jet_0_eta,leptons_phi_fake, jet_0_phi));
	  double DRtoJet1 = sqrt(deltaRsquared( leptons_eta_fake, jet_1_eta,leptons_phi_fake, jet_1_phi));
	  if (DRtoJet1 < minDRtoJet) minDRtoJet = DRtoJet1;
	  return minDRtoJet;
	}
    }
  return 0;
}
//______________________________________________________________________________________________
double FakeLepSel_ll::deltaRsquared( double eta1, double eta2, double phi1, double phi2) const
{
  return (eta1 - eta2)*(eta1 - eta2) + (phi1 - phi2)*(phi1 - phi2);
}

//______________________________________________________________________________________________

FakeLepSel_ll::FakeLepSel_ll(const TString& expression):
TQTreeObservable(expression)
{
  // constructor with expression argument
  DEBUGclass("constructor called with '%s'",expression.Data());
  // the predefined string member "expression" allows your observable to store an expression of your choice
  // this string will be the verbatim argument you passed to the constructor of your observable
  // you can use it to choose between different modes or pass configuration options to your observable
  this->SetName(TQObservable::makeObservableName(expression));
  this->setExpression(expression);

  if (expression.Contains("Sel"))
    makeSelection = true;
  else if (expression.Contains("Kin"))
    makeKinematics = true;

  if(expression.Contains("Loose") || expression.Contains("loose"))
    {
      DEBUGclass("use loose fake lepton in '%s'" , expression.Data());
      useLoose = true;
    }
  else if (expression.Contains("Tight") || expression.Contains("tight"))
    {

      DEBUGclass("use tight fake lepton in '%s'" , expression.Data());
      useTight = true;
    };

  if(expression.Contains("Eta") || expression.Contains("eta"))
    {
      INFOclass("Plot third lepton's eta in '%s'" , expression.Data());
      plotEta = true;
    }
  else if (expression.Contains("Pt") || expression.Contains("pt") || expression.Contains("pT"))
    {
      INFOclass("Plot third lepton's pT in '%s'" , expression.Data());
      plotPt = true;
    }
  else if (expression.Contains("DRjet"))
    {
      INFOclass("Plot DRjet in '%s'" , expression.Data());
      plotDRjet = true;
    }
  else if (expression.Contains("DRlep0"))
    {
      INFOclass("Plot DRlep0 in '%s'" , expression.Data());
      plotDRlep0 = true;
    }
 else if (expression.Contains("DRlep1"))
    {
      INFOclass("Plot DRlep1 in '%s'" , expression.Data());
      plotDRlep1 = true;
    };

  if(expression.Contains("Muon"))
    {
      INFOclass("Look for fake muons in '%s'" , expression.Data());
      selectMuon = true;
    }
  else if (expression.Contains("Elec"))
    {
      INFOclass("Look for fake electrons in '%s'" , expression.Data());
      selectElectron = true;
    }

}

//______________________________________________________________________________________________

const TString& FakeLepSel_ll::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool FakeLepSel_ll::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void FakeLepSel_ll::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool FakeLepSel_ll::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void FakeLepSel_ll::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString FakeLepSel_ll::getActiveExpression() const {
  // retrieve the expression associated with this incarnation
  //  return this->getExpression();
  return "";
}

//______________________________________________________________________________________________

bool FakeLepSel_ll::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }



  // fTree->SetBranchAddress("leptons"		, &leptons		);
  // fTree->SetBranchAddress("leptons_pt"		, &leptons_pt		);
  // fTree->SetBranchAddress("leptons_eta"		, &leptons_eta		);
  // fTree->SetBranchAddress("leptons_cluster_eta" , &leptons_cluster_eta	);
  // fTree->SetBranchAddress("leptons_id_medium"	, &leptons_id_medium	);
  // fTree->SetBranchAddress("leptons_id_loose"	, &leptons_id_loose	);
  // fTree->SetBranchAddress("leptons_iso_wp"	, &leptons_iso_wp	);

  //first two leptons:
  this->lep_0 = new TTreeFormula( "lep_0", "lep_0", this->fTree);
  this->lep_1 = new TTreeFormula( "lep_1", "lep_1", this->fTree);
  this->lep_0_pt  = new TTreeFormula( "lep_0_pt", "lep_0_pt", this->fTree);
  this->lep_1_pt  = new TTreeFormula( "lep_1_pt", "lep_1_pt", this->fTree);
  this->lep_0_eta = new TTreeFormula( "lep_0_eta", "lep_0_eta", this->fTree);
  this->lep_1_eta = new TTreeFormula( "lep_1_eta", "lep_1_eta", this->fTree);
  this->lep_0_phi = new TTreeFormula( "lep_0_phi", "lep_0_phi", this->fTree);
  this->lep_1_phi = new TTreeFormula( "lep_1_phi", "lep_1_phi", this->fTree);

  this->jet_0_eta = new TTreeFormula( "jet_0_eta", "jet_0_eta", this->fTree);
  this->jet_1_eta = new TTreeFormula( "jet_1_eta", "jet_1_eta", this->fTree);
  this->jet_0_phi = new TTreeFormula( "jet_0_phi", "jet_0_phi", this->fTree);
  this->jet_1_phi = new TTreeFormula( "jet_1_phi", "jet_1_phi", this->fTree);

  //leptons vector branches
   this->leptons = new TTreeFormula( "leptons", "leptons", this->fTree);
   this->leptons_pt = new TTreeFormula( "leptons_pt", "leptons_pt", this->fTree);
   this->leptons_eta = new TTreeFormula( "leptons_eta", "leptons_eta", this->fTree);
   this->leptons_phi = new TTreeFormula( "leptons_phi", "leptons_phi", this->fTree);
   this->leptons_cluster_eta = new TTreeFormula( "leptons_cluster_eta", "leptons_cluster_eta", this->fTree);
   this->leptons_id_medium = new TTreeFormula( "leptons_id_medium", "leptons_id_medium", this->fTree);
   this->leptons_id_tight = new TTreeFormula( "leptons_id_tight", "leptons_id_tight", this->fTree);
   this->leptons_id_loose = new TTreeFormula( "leptons_id_loose", "leptons_id_loose", this->fTree);
   this->leptons_iso_wp = new TTreeFormula( "leptons_iso_wp", "leptons_iso_wp", this->fTree);



  return true;
}

//______________________________________________________________________________________________

bool FakeLepSel_ll::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  //first two leptons:
  delete this->lep_0;
  delete this->lep_1;
  delete this->lep_0_pt;
  delete this->lep_1_pt;
  delete this->lep_0_eta;
  delete this->lep_1_eta;
  delete this->lep_0_phi;
  delete this->lep_1_phi;

  delete this->jet_0_eta;
  delete this->jet_1_eta;
  delete this->jet_0_phi;
  delete this->jet_1_phi;

  //leptons vector branches:
   delete this->leptons;
   delete this->leptons_pt;
   delete this->leptons_eta;
   delete this->leptons_phi;
   delete this->leptons_cluster_eta;
   delete this->leptons_id_medium;
   delete this->leptons_id_tight;
   delete this->leptons_id_loose;
   delete this->leptons_iso_wp;

  return true;
}


