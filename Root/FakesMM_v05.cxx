#include "Htautau/FakesMM_v05.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "Htautau/EventSelection_leplep_fake.h"

ClassImp(FakesMM_v05)

//______________________________________________________________________________________________

FakesMM_v05::FakesMM_v05(){
  // default constructor

  this->setExpression(this->GetName() );

  DEBUGclass("default constructor called");
}

//______________________________________________________________________________________________

FakesMM_v05::~FakesMM_v05(){
  // default destructor
  DEBUGclass("destructor called");
}


//______________________________________________________________________________________________

TObjArray* FakesMM_v05::getBranchNames() const {
  // retrieve the list of branch names
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();

  //bnames->SetOwner(true);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));


  bnames->Add(new TObjString("leptons"));
  bnames->Add(new TObjString("leptons_pt"));


  return bnames;
}

//______________________________________________________________________________________________

double FakesMM_v05::getEff(double val, TGraphAsymmErrors* graph, int m_systematic, TString whateff) const {

  //std::cout << "Have sys: " << m_systematic << std::endl;

  // systematic variation of efficiencies:
  // m_systematic=0: real nom,  fake nom
  // m_systematic=1: real nom,  fake up
  // m_systematic=2: real nom,  fake down
  // m_systematic=3: real up,   fake nom
  // m_systematic=4: real up,   fake up
  // m_systematic=5: real up,   fake down
  // m_systematic=6: real down, fake nom
  // m_systematic=7: real down, fake down
  // m_systematic=8: real down, fake up

  //std::cout << "In get eff:" << std::endl;
  //std::cout << "pt val:" << val << std::endl;
  //std::cout << "histo:" << graph->GetName() << std::endl;

  double eff = 0.;
  bool beyondrange=false;
  int npoints = graph->GetN();
  double xend,yend;
  graph->GetPoint(npoints-1,xend,yend);
  double exend=graph->GetErrorX(npoints-1);
  double eyend=graph->GetErrorY(npoints-1);
  if (val>(xend+exend)){
    beyondrange=true;
    eff=yend;
  }
  double xstart,ystart;
  graph->GetPoint(0,xstart,ystart);
  double exstart=graph->GetErrorX(0);
  double eystart=graph->GetErrorY(0);
  if(val<(xstart-exstart)){
    beyondrange=true;
    eff=ystart;
  }
  for(int i=0; i<npoints; i++){
    double x,y;
    graph->GetPoint(i,x,y);
    double ex=graph->GetErrorX(i);
    double ey=graph->GetErrorY(i);
    if(val>(x-ex) && val<(x+ex)){  // nominal
      if(m_systematic==0){
	if(y>1.){
	  std::cout << "Problem"<< std::endl;
	  eff=y-ey;
	}
	else if(y<0.){
	  std::cout << "Problem" << std::endl;
	  eff=y+ey;
	}
      	else eff=y;
      	break;
      }
      else if (m_systematic == 1){
	if(whateff.Contains("real")){
	  eff=y;
	}
	else if(whateff.Contains("fake")){
	  eff=y+ey;
	}
      	break;
      }
      else if (m_systematic == 2){
        if(whateff.Contains("real")){
          eff=y;
        }
        else if(whateff.Contains("fake")){
          eff=y-ey;
        }
        break;
      }
      else if (m_systematic == 3){
        if(whateff.Contains("real")){
          eff=y+ey;
        }
        else if(whateff.Contains("fake")){
          eff=y;
        }
        break;
      }
      else if (m_systematic == 4){
        if(whateff.Contains("real")){
          eff=y+ey;
        }
        else if(whateff.Contains("fake")){
          eff=y+ey;
        }
        break;
      }
      else if (m_systematic == 5){
        if(whateff.Contains("real")){
          eff=y+ey;
        }
        else if(whateff.Contains("fake")){
          eff=y-ey;
        }
        break;
      }
      else if (m_systematic == 6){
        if(whateff.Contains("real")){
          eff=y-ey;
        }
        else if(whateff.Contains("fake")){
          eff=y;
        }
        break;
      }
      else if (m_systematic == 7){
        if(whateff.Contains("real")){
          eff=y-ey;
        }
        else if(whateff.Contains("fake")){
          eff=y-ey;
        }
        break;
      }
      else if (m_systematic == 8){
        if(whateff.Contains("real")){
          eff=y-ey;
        }
        else if(whateff.Contains("fake")){
          eff=y+ey;
        }
        break;
      }
    }
  }


  return eff;

}

//______________________________________________________________________________________________

double FakesMM_v05::getValue() const {

  // calculate Fake weights

  //std::cout << "Have systematics: " << m_systematic << std::endl;
  //std::cout << "START" << std::endl;

  this->leptons->GetNdata();
  this->leptons_pt->GetNdata();

  int idx0 = -1;
  int idx1 = -1;

  idx0=EVS_fake->getLeptonIdx(0);
  idx1=EVS_fake->getLeptonIdx(1);

  bool lep0_is_tight = false;
  bool lep1_is_tight = false;

  int TriggerType = -1;

  double wFake = 0.;


  if(idx0>=0 && idx1>=0){

    lep0_is_tight = EVS_fake->getLepTight(0);
    lep1_is_tight = EVS_fake->getLepTight(1);

    TriggerType = EVS_fake->getTriggerType();

    //std::cout << "TriggerType: " << TriggerType << std::endl;

    if(TriggerType == 0){
      return 0;
    }

    double lep_0     = this->leptons->EvalInstance(idx0);
    double lep_1     = this->leptons->EvalInstance(idx1);
    double lep_0_pt  = this->leptons_pt->EvalInstance(idx0);
    double lep_1_pt  = this->leptons_pt->EvalInstance(idx1);


    //std::cout << "lepton type: " << lep_0 << " " << lep_1 << std::endl;

    bool isEE=false; bool isMM=false; bool isEM=false;bool isME=false;

    if(lep_0 == 2 && lep_1 == 2) isEE = true;
    if(lep_0 == 1 && lep_1 == 1) isMM = true;
    if(lep_0 == 2 && lep_1 == 1) isEM = true;
    if(lep_0 == 1 && lep_1 == 2) isME = true;

    //std::cout << "isEE: " << isEE << " isMM: " << isMM << " isEM: " << isEM << " isME: " << isME << std::endl;

    ///// double fakes

    double deltai_TT = 0.;
    double deltai_TL = 0.;
    double deltai_LT = 0.;
    double deltai_LL = 0.;

    if(lep0_is_tight==1 && lep1_is_tight==0){ // TL
      deltai_TL = 1.;
    }
    else if(lep0_is_tight==0 && lep1_is_tight==1){ // LT
      deltai_LT = 1.;
    }
    else if(lep0_is_tight==1 && lep1_is_tight==1) { // TT
      deltai_TT = 1.;
    }
    else if(lep0_is_tight!=1 && lep1_is_tight!=1){ //LL
      deltai_LL = 1.;
    }
    else {
      std::cout << "problem with deltai" << std::endl;
    }

    //if(isMM && TriggerType==12){
    //std::cout << "delta i:" << std::endl;
    //std::cout << " TL: " << deltai_TL << std::endl;
    //std::cout << " LT: " << deltai_LT << std::endl;
    //std::cout << " TT: " << deltai_TT << std::endl;
    //std::cout << " LL: " << deltai_LL << std::endl;
    //}

    double lep0_effReal_pt = 0.;
    double lep0_effFake_pt = 0.;
    double lep1_effReal_pt = 0.;
    double lep1_effFake_pt = 0.;

    double lep0_effReal = 0.;
    double lep0_effFake = 0.;
    double lep1_effReal = 0.;
    double lep1_effFake = 0.;


    if(isMM){ // mumu channel
      //std::cout << "In MM" << std::endl;
      if(TriggerType == 10){
	if(m_flag==15){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
	  lep1_effReal_pt = getEff(lep_1_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
	  lep0_effFake_pt = getEff(lep_0_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
	  lep1_effFake_pt = getEff(lep_1_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
	}
	if(m_flag==16){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
	  lep1_effReal_pt = getEff(lep_1_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
	  lep0_effFake_pt = getEff(lep_0_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
	  lep1_effFake_pt = getEff(lep_1_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
	}
      }
      else if(TriggerType == 11){ // not used
	//std::cout << "IN SL1T" << std::endl;
	lep0_effReal_pt = getEff(lep_0_pt, g_real_muon_SL1T_pt0,m_systematic,"real");
        lep1_effReal_pt = getEff(lep_1_pt, g_real_muon_SL1T_pt1,m_systematic,"real");
        lep0_effFake_pt = getEff(lep_0_pt, g_fake_muon_SL1T_pt0,m_systematic,"fake");
        lep1_effFake_pt = getEff(lep_1_pt, g_fake_muon_SL1T_pt1,m_systematic,"fake");
      }
      else if(TriggerType == 12){
	if(m_flag==15){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
	  lep1_effReal_pt = getEff(lep_1_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
	  lep0_effFake_pt = getEff(lep_0_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
	  lep1_effFake_pt = getEff(lep_1_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
	}
	if(m_flag==16){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
	  lep1_effReal_pt = getEff(lep_1_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
	  lep0_effFake_pt = getEff(lep_0_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
	  lep1_effFake_pt = getEff(lep_1_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
	}
      }
    }
    else if(isEE) { // ee channel
      //std::cout << "In EE" << std::endl;
      if(TriggerType == 20){
	//std::cout << "In SL0T" << std::endl;
	lep0_effReal_pt = getEff(lep_0_pt, g_real_elec_SL0T_pt0,m_systematic,"real");
        lep1_effReal_pt = getEff(lep_1_pt, g_real_elec_SL0T_pt1,m_systematic,"real");
        lep0_effFake_pt = getEff(lep_0_pt, g_fake_elec_SL0T_pt0,m_systematic,"fake");
        lep1_effFake_pt = getEff(lep_1_pt, g_fake_elec_SL0T_pt1,m_systematic,"fake");
      }
      else if(TriggerType == 21){ // not used
	//std::cout << "IN SL1T" << std::endl;
	lep0_effReal_pt = getEff(lep_0_pt, g_real_elec_SL0T_pt1,m_systematic,"real");
        lep1_effReal_pt = getEff(lep_1_pt, g_real_elec_SL0T_pt0,m_systematic,"real");
        lep0_effFake_pt = getEff(lep_0_pt, g_fake_elec_SL0T_pt1,m_systematic,"fake");
        lep1_effFake_pt = getEff(lep_1_pt, g_fake_elec_SL0T_pt0,m_systematic,"fake");
      }
      else if(TriggerType == 22){
	//std::cout << "In DLT" << std::endl;
	if(m_flag==15){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_elec_DLT_pt1,m_systematic,"real");
	  lep1_effReal_pt = getEff(lep_1_pt, g_real_elec_DLT_pt1,m_systematic,"real");
	  lep0_effFake_pt = getEff(lep_0_pt, g_fake_elec_DLT_pt1,m_systematic,"fake");
	  lep1_effFake_pt = getEff(lep_1_pt, g_fake_elec_DLT_pt1,m_systematic,"fake");
	}
	if(m_flag==16){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_elec_DLT_pt0,m_systematic,"real");
	  lep1_effReal_pt = getEff(lep_1_pt, g_real_elec_DLT_pt0,m_systematic,"real");
	  lep0_effFake_pt = getEff(lep_0_pt, g_fake_elec_DLT_pt0,m_systematic,"fake");
	  lep1_effFake_pt = getEff(lep_1_pt, g_fake_elec_DLT_pt0,m_systematic,"fake");
	}
      }
    }
    else if(isME){ // mu e channel
      //std::cout << "In ME" << std::endl;
      if(TriggerType == 10){
	//std::cout << "In SL0T" <<g std::endl;
	if(m_flag==15){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
	  lep1_effReal_pt = getEff(lep_1_pt, g_real_elec_SL0T_pt1,m_systematic,"real");
	  lep0_effFake_pt = getEff(lep_0_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
	  lep1_effFake_pt = getEff(lep_1_pt, g_fake_elec_SL0T_pt1,m_systematic,"fake");
	}
	if(m_flag==16){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
          lep1_effReal_pt = getEff(lep_1_pt, g_real_elec_SL0T_pt1,m_systematic,"real");
          lep0_effFake_pt = getEff(lep_0_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
          lep1_effFake_pt = getEff(lep_1_pt, g_fake_elec_SL0T_pt1,m_systematic,"fake");
	}
      }
      else if(TriggerType == 21){
	//std::cout << "IN SL1T" << std::endl;
	if(m_flag==15){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
	  lep1_effReal_pt = getEff(lep_1_pt, g_real_elec_SL0T_pt0,m_systematic,"real");
	  lep0_effFake_pt = getEff(lep_0_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
	  lep1_effFake_pt = getEff(lep_1_pt, g_fake_elec_SL0T_pt0,m_systematic,"fake");
	}
	if(m_flag==16){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
	  lep1_effReal_pt = getEff(lep_1_pt, g_real_elec_SL0T_pt0,m_systematic,"real");
	  lep0_effFake_pt = getEff(lep_0_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
	  lep1_effFake_pt = getEff(lep_1_pt, g_fake_elec_SL1T_pt0,m_systematic,"fake");
	}
      }
      else if(TriggerType == 211){
	//std::cout << "In DLT" << std::endl;
	if(m_flag==15){
	lep0_effReal_pt = getEff(lep_0_pt, g_real_muon_DLT_pt0,m_systematic,"real");
        lep1_effReal_pt = getEff(lep_1_pt, g_real_elec_DLT_pt1,m_systematic,"real");
        lep0_effFake_pt = getEff(lep_0_pt, g_fake_muon_DLT_pt0,m_systematic,"fake");
        lep1_effFake_pt = getEff(lep_1_pt, g_fake_elec_DLT_pt1,m_systematic,"fake");
	}
	if(m_flag==16){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_muon_DLT_pt0,m_systematic,"real");
	  lep1_effReal_pt = getEff(lep_1_pt, g_real_elec_DLT_pt1,m_systematic,"real");
	  lep0_effFake_pt = getEff(lep_0_pt, g_fake_muon_DLT_pt0,m_systematic,"fake");
	  lep1_effFake_pt = getEff(lep_1_pt, g_fake_elec_DLT_pt1,m_systematic,"fake");
	}
      }
    }
    else if(isEM){ // emu channel
      //std::cout<< "In EM" << std::endl;
      if(TriggerType == 20){
	//std::cout << "In SL0T" << std::endl;
	lep0_effReal_pt = getEff(lep_0_pt, g_real_elec_SL0T_pt0,m_systematic,"real");
        lep1_effReal_pt = getEff(lep_1_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
        lep0_effFake_pt = getEff(lep_0_pt, g_fake_elec_SL0T_pt0,m_systematic,"fake");
        lep1_effFake_pt = getEff(lep_1_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
      }
      else if(TriggerType == 11){
	//std::cout << "IN SL1T" << std::endl;
        lep0_effReal_pt = getEff(lep_0_pt, g_real_elec_SL0T_pt1,m_systematic,"real");
        lep1_effReal_pt = getEff(lep_1_pt, g_real_muon_SL0T_pt0,m_systematic,"real");
        lep0_effFake_pt = getEff(lep_0_pt, g_fake_elec_SL0T_pt1,m_systematic,"fake");
        lep1_effFake_pt = getEff(lep_1_pt, g_fake_muon_SL0T_pt0,m_systematic,"fake");
      }
      else if(TriggerType == 211){
	//std::cout << "In DLT" << std::endl;
	if(m_flag==15){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_elec_DLT_pt1,m_systematic,"real");
	  lep1_effReal_pt = getEff(lep_1_pt, g_real_elec_DLT_pt1,m_systematic,"real");
	  lep0_effFake_pt = getEff(lep_0_pt, g_fake_elec_DLT_pt1,m_systematic,"fake");
	  lep1_effFake_pt = getEff(lep_1_pt, g_fake_elec_DLT_pt1,m_systematic,"fake");
	}
	if(m_flag==16){
	  lep0_effReal_pt = getEff(lep_0_pt, g_real_elec_DLT_pt0,m_systematic,"real");
          lep1_effReal_pt = getEff(lep_1_pt, g_real_muon_DLT_pt1,m_systematic,"real");
          lep0_effFake_pt = getEff(lep_0_pt, g_fake_elec_DLT_pt0,m_systematic,"fake");
          lep1_effFake_pt = getEff(lep_1_pt, g_fake_muon_DLT_pt1,m_systematic,"fake");
	}
      }
    }
    else {
      std::cout << "In FakesMM:: No valid lepton channel found! Return fake weight of 0!" << std::endl;
      return 0.;
    }



    //if(isMM && TriggerType==12){
    //  std::cout << "lep0 eff real: " << lep0_effReal_pt << std::endl;
    //  std::cout << "lep1 eff real: " << lep1_effReal_pt << std::endl;
    //  std::cout << "lep0 eff fake: " << lep0_effFake_pt << std::endl;
    //  std::cout << "lep1 eff fake: " << lep1_effFake_pt << std::endl;
    //}

    // multiply efficiencies here, atm only pt is considered
    lep0_effReal = lep0_effReal_pt;
    lep1_effReal = lep1_effReal_pt;
    lep0_effFake = lep0_effFake_pt;
    lep1_effFake = lep1_effFake_pt;


    // avoid inf
    if((lep0_effReal-lep0_effFake)*(lep1_effReal-lep1_effFake)==0) {
      std::cout << "Need to avoid inf" << std::endl;
      std::cout << "isMM: " << isMM << " isEE: " << isEE << " isEM: " << isEM << " isME: " << isME << std::endl;
      std::cout <<"triggertype:" << TriggerType << std::endl;
      std::cout << "pt0: " << lep_0_pt << " pt1: " << lep_1_pt << std::endl;
      std::cout << "lep0 eff real: " << lep0_effReal_pt << std::endl;
      std::cout << "lep1 eff real: " << lep1_effReal_pt << std::endl;
      std::cout << "lep0 eff fake: " << lep0_effFake_pt << std::endl;
      std::cout << "lep1 eff fake: " << lep1_effFake_pt << std::endl;
      return 0.;
    }

    //calculate ME for the already inverted matrix:
    // |m11 m12 m13 m14|
    // |m21 m22 m23 m24|
    // |m31 m32 m33 m34|
    // |m41 m42 m43 m44|
    double m11 = (lep0_effFake*lep1_effFake-lep0_effFake-lep1_effFake+1);
    double m12 = (lep0_effFake*lep1_effFake-lep1_effFake);
    double m13 = (lep0_effFake*lep1_effFake-lep0_effFake);
    double m14 = (lep0_effFake*lep1_effFake);
    double m21 = (-lep0_effFake*lep1_effReal+lep1_effReal+lep0_effFake-1);
    double m22 = (lep1_effReal-lep1_effReal*lep0_effFake);
    double m23 = (lep0_effFake-lep1_effReal*lep0_effFake);
    double m24 = (-lep1_effReal*lep0_effFake);
    double m31 = (-lep1_effFake*lep0_effReal+lep0_effReal+lep1_effFake-1);
    double m32 = (lep1_effFake-lep0_effReal*lep1_effFake);
    double m33 = (lep0_effReal-lep0_effReal*lep1_effFake);
    double m34 = (-lep0_effReal*lep1_effFake);
    double m41 = (lep0_effReal*lep1_effReal-lep0_effReal-lep1_effReal+1);
    double m42 = (lep0_effReal*lep1_effReal-lep1_effReal);
    double m43 = (lep0_effReal*lep1_effReal-lep0_effReal);
    double m44 = (lep0_effReal*lep1_effReal);

    double prefac = 1./((lep0_effReal-lep0_effFake)*(lep1_effReal-lep1_effFake));

    double wFake_ff = 0.;
    double wFake_rf = 0.;
    double wFake_fr = 0.;

    wFake_rf = (m21*deltai_TT+m22*deltai_TL+m23*deltai_LT+m24*deltai_LL);
    wFake_fr = (m31*deltai_TT+m32*deltai_TL+m33*deltai_LT+m34*deltai_LL);
    wFake_ff = (m41*deltai_TT+m42*deltai_TL+m43*deltai_LT+m44*deltai_LL);

    wFake_rf *= prefac*(lep0_effReal*lep1_effFake);
    wFake_fr *= prefac*(lep0_effFake*lep1_effReal);
    wFake_ff *= prefac*(lep0_effFake*lep1_effFake);


    wFake = wFake_rf+wFake_fr+wFake_ff;



    //////////////////////////////////////////////////////
    /////////////// single fakes only ////////////////////
    //////////////////////////////////////////////////////

    /*
    double effReal = 0.;
    double effFake = 0.;

    double deltai = -1000.;

    if (lep0_is_tight == 1) {
      deltai = 0.;
      if (lep1_is_tight == 1) {
        deltai = 1.;
      }
    }
    else {
      return 0.;
    }

    //int binReal = -1;
    //int binFake = -1;

    if (isMM){
      if(TriggerType == 10){
	effReal = getEff(lep_1_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
	effFake = getEff(lep_1_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
      }
      else if(TriggerType == 11){
	effReal = getEff(lep_1_pt, g_real_muon_SL1T_pt1,m_systematic,"real");
	effFake = getEff(lep_1_pt, g_fake_muon_SL1T_pt1,m_systematic,"fake");
      }
      else if(TriggerType == 12){
	effReal = getEff(lep_1_pt, g_real_muon_DLT_pt1,m_systematic,"real");
	effFake = getEff(lep_1_pt, g_fake_muon_DLT_pt1,m_systematic,"fake");
      }
    }
    else if (isEE){
      if(TriggerType == 20){
        effReal = getEff(lep_1_pt, g_real_elec_SL0T_pt1,m_systematic,"real");
        effFake = getEff(lep_1_pt, g_fake_elec_SL0T_pt1,m_systematic,"fake");
      }
      else if(TriggerType == 21){
	effReal = getEff(lep_1_pt, g_real_elec_SL1T_pt1,m_systematic,"real");
	effFake = getEff(lep_1_pt, g_fake_elec_SL1T_pt1,m_systematic,"fake");
      }
      else if(TriggerType == 22){
	effReal = getEff(lep_1_pt, g_real_elec_DLT_pt1,m_systematic,"real");
	effFake = getEff(lep_1_pt, g_fake_elec_DLT_pt1,m_systematic,"fake");
      }
    }
    else if(isME){
      if(TriggerType == 10){
        effReal = getEff(lep_1_pt, g_real_elec_SL0T_pt1,m_systematic,"real");
        effFake = getEff(lep_1_pt, g_fake_elec_SL0T_pt1,m_systematic,"fake");
      }
      else if(TriggerType == 21){
        effReal = getEff(lep_1_pt, g_real_elec_SL0T_pt0,m_systematic,"real");
        effFake = getEff(lep_1_pt, g_fake_elec_SL0T_pt0,m_systematic,"fake");
      }
      else if(TriggerType == 211){
        effReal = getEff(lep_1_pt, g_real_elec_DLT_pt1,m_systematic,"real");
        effFake = getEff(lep_1_pt, g_fake_elec_DLT_pt1,m_systematic,"fake");
      }
    }
    else if(isEM){
      if(TriggerType == 20){
        effReal = getEff(lep_1_pt, g_real_muon_SL0T_pt1,m_systematic,"real");
        effFake = getEff(lep_1_pt, g_fake_muon_SL0T_pt1,m_systematic,"fake");
      }
      else if(TriggerType == 11){
        effReal = getEff(lep_1_pt, g_real_muon_SL0T_pt0,m_systematic,"real");
        effFake = getEff(lep_1_pt, g_fake_muon_SL0T_pt0,m_systematic,"fake");
      }
      else if(TriggerType == 211){
        effReal = getEff(lep_1_pt, g_real_muon_DLT_pt1,m_systematic,"real");
        effFake = getEff(lep_1_pt, g_fake_muon_DLT_pt1,m_systematic,"fake");
      }
    }
    else return 0.;

    //if (effReal!=effFake && (effReal!=0. && effFake!=0.)){
    if (effReal!=effFake){
      wFake = effFake/(effReal-effFake)*(effReal-deltai);
    }
    else {
      //std::cout << "FakesMM: Something went wrong with efficiencies! Return fake weight of 0!" << std::endl;
      return 0.;
    }


    //std::cout << "wFakes: " << wFake << std::endl;

    */
  }

  //printf("wFake result : %.6f \n", wFake);

  return wFake;
}
//______________________________________________________________________________________________

FakesMM_v05::FakesMM_v05(const TString& expression, const TString& filePath, int systematic, int flag):
  TQTreeObservable(expression), m_systematic(systematic), m_flag(flag), m_filePath(filePath)
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

const TString& FakesMM_v05::getExpression() const {
  // retrieve the expression associated with this observable
  return this->fExpression;
}

//______________________________________________________________________________________________

bool FakesMM_v05::hasExpression() const {
  // check if this observable type knows expressions
  return true;
}

//______________________________________________________________________________________________

void FakesMM_v05::setExpression(const TString& expr){
  // set the expression to a given string
  this->fExpression = expr;
}
//______________________________________________________________________________________________

bool FakesMM_v05::parseExpression(const TString& expr){
  // parse the expression
  return true;
}

//______________________________________________________________________________________________

void FakesMM_v05::clearParsedExpression(){
  // clear the current expression
}

//______________________________________________________________________________________________

TString FakesMM_v05::getActiveExpression() const {
  // retrieve the expression associated with this incarnation

  return this->getExpression();
}

//______________________________________________________________________________________________

bool FakesMM_v05::initializeSelf(){
  // initialize self - compile container name, construct accessor
  if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
    return false;
  }


  EVS_fake = new EventSelection_leplep_fake();

  this->leptons      = new TTreeFormula( "leptons", "leptons", this->fTree);
  this->leptons_pt      = new TTreeFormula( "leptons_pt", "leptons_pt", this->fTree);

  infile = TFile::Open(m_filePath,"READ");
  if(!infile) std::cout << "ERROR in FakesMM:: Failed to open input file!" << std::endl;

  g_real_elec_SL0T_pt0  = (TGraphAsymmErrors*)infile->Get("g_Real_LeptonPt0_ee_SL0T_ZllM" )->Clone("g_real_elec_SL0T_pt0");
  g_real_elec_SL0T_pt1  = (TGraphAsymmErrors*)infile->Get("g_Real_LeptonPt1_ee_SL0T_ZllM" )->Clone("g_real_elec_SL0T_pt1");
  g_real_elec_SL1T_pt0  = (TGraphAsymmErrors*)infile->Get("g_Real_LeptonPt0_ee_SL1T_ZllM" )->Clone("g_real_elec_SL1T_pt0");
  g_real_elec_SL1T_pt1  = (TGraphAsymmErrors*)infile->Get("g_Real_LeptonPt1_ee_SL1T_ZllM" )->Clone("g_real_elec_SL1T_pt1");
  g_real_elec_DLT_pt0   = (TGraphAsymmErrors*)infile->Get("g_Real_LeptonPt0_ee_DLT_ZllM"  )->Clone("g_real_elec_DLT_pt0" );
  g_real_elec_DLT_pt1   = (TGraphAsymmErrors*)infile->Get("g_Real_LeptonPt1_ee_DLT_ZllM"  )->Clone("g_real_elec_DLT_pt1" );

  g_real_muon_SL0T_pt0  = (TGraphAsymmErrors*)infile->Get("g_Real_LeptonPt0_mm_SL0T_ZllM" )->Clone("g_real_muon_SL0T_pt0");
  g_real_muon_SL0T_pt1  = (TGraphAsymmErrors*)infile->Get("g_Real_LeptonPt1_mm_SL0T_ZllM" )->Clone("g_real_muon_SL0T_pt1");
  g_real_muon_SL1T_pt0  = (TGraphAsymmErrors*)infile->Get("g_Real_LeptonPt0_mm_SL1T_ZllM" )->Clone("g_real_muon_SL1T_pt0");
  g_real_muon_SL1T_pt1  = (TGraphAsymmErrors*)infile->Get("g_Real_LeptonPt1_mm_SL1T_ZllM" )->Clone("g_real_muon_SL1T_pt1");
  g_real_muon_DLT_pt0   = (TGraphAsymmErrors*)infile->Get("g_Real_LeptonPt0_mm_DLT_ZllM"  )->Clone("g_real_muon_DLT_pt0" );
  g_real_muon_DLT_pt1   = (TGraphAsymmErrors*)infile->Get("g_Real_LeptonPt1_mm_DLT_ZllM"  )->Clone("g_real_muon_DLT_pt1" );

  g_fake_elec_SL0T_pt0  = (TGraphAsymmErrors*)infile->Get("g_Fake_LeptonPt0_em_SL0T_WWss"   )->Clone("g_fake_elec_SL0T_pt0");
  g_fake_elec_SL0T_pt1  = (TGraphAsymmErrors*)infile->Get("g_Fake_LeptonPt1_me_SL0T_WWss"   )->Clone("g_fake_elec_SL0T_pt1");
  g_fake_elec_SL1T_pt0  = (TGraphAsymmErrors*)infile->Get("g_Fake_LeptonPt0_em_SL1T_WWss"   )->Clone("g_fake_elec_SL1T_pt0");
  g_fake_elec_SL1T_pt1  = (TGraphAsymmErrors*)infile->Get("g_Fake_LeptonPt1_me_SL1T_WWss"   )->Clone("g_fake_elec_SL1T_pt1");
  g_fake_elec_DLT_pt0   = (TGraphAsymmErrors*)infile->Get("g_Fake_LeptonPt0_em_DLT_WWss"    )->Clone("g_fake_elec_DLT_pt0" );
  g_fake_elec_DLT_pt1   = (TGraphAsymmErrors*)infile->Get("g_Fake_LeptonPt1_me_DLT_WWss"    )->Clone("g_fake_elec_DLT_pt1" );

  g_fake_muon_SL0T_pt0  = (TGraphAsymmErrors*)infile->Get("g_Fake_LeptonPt0_mm_SL0T_WWss"   )->Clone("g_fake_muon_SL0T_pt0");
  g_fake_muon_SL0T_pt1  = (TGraphAsymmErrors*)infile->Get("g_Fake_LeptonPt1_mm_SL0T_WWss"   )->Clone("g_fake_muon_SL0T_pt1");
  g_fake_muon_SL1T_pt0  = (TGraphAsymmErrors*)infile->Get("g_Fake_LeptonPt0_mm_SL1T_WWss"   )->Clone("g_fake_muon_SL1T_pt0");
  g_fake_muon_SL1T_pt1  = (TGraphAsymmErrors*)infile->Get("g_Fake_LeptonPt1_mm_SL1T_WWss"   )->Clone("g_fake_muon_SL1T_pt1");
  g_fake_muon_DLT_pt0   = (TGraphAsymmErrors*)infile->Get("g_Fake_LeptonPt0_mm_DLT_WWss"    )->Clone("g_fake_muon_DLT_pt0" );
  g_fake_muon_DLT_pt1   = (TGraphAsymmErrors*)infile->Get("g_Fake_LeptonPt1_mm_DLT_WWss"    )->Clone("g_fake_muon_DLT_pt1" );

  infile->Close();

  return true;
}

//______________________________________________________________________________________________

bool FakesMM_v05::finalizeSelf(){
  // finalize self - delete accessor
  this->clearParsedExpression();

  delete this->leptons;
  delete this->leptons_pt;

  delete EVS_fake;
  delete infile;

  delete g_real_elec_SL0T_pt0;
  delete g_real_elec_SL0T_pt1;
  delete g_real_elec_SL1T_pt0;
  delete g_real_elec_SL1T_pt1;
  delete g_real_elec_DLT_pt0;
  delete g_real_elec_DLT_pt1;

  delete g_real_muon_SL0T_pt0;
  delete g_real_muon_SL0T_pt1;
  delete g_real_muon_SL1T_pt0;
  delete g_real_muon_SL1T_pt1;
  delete g_real_muon_DLT_pt0;
  delete g_real_muon_DLT_pt1;

  delete g_fake_elec_SL0T_pt0;
  delete g_fake_elec_SL0T_pt1;
  delete g_fake_elec_SL1T_pt0;
  delete g_fake_elec_SL1T_pt1;
  delete g_fake_elec_DLT_pt0;
  delete g_fake_elec_DLT_pt1;

  delete g_fake_muon_SL0T_pt0;
  delete g_fake_muon_SL0T_pt1;
  delete g_fake_muon_SL1T_pt0;
  delete g_fake_muon_SL1T_pt1;
  delete g_fake_muon_DLT_pt0;
  delete g_fake_muon_DLT_pt1;

  return true;
}
