//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __FAKELEPSEL_LL__
#define __FAKELEPSEL_LL__
#include "QFramework/TQTreeObservable.h"

#include "TTreeFormula.h"

class FakeLepSel_ll : public TQTreeObservable {
protected:
  // put here any data members your class might need
 
public:
  virtual double getValue() const override;
  virtual TObjArray* getBranchNames() const override;
protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
protected:
  TString fExpression = "";
  TString fOptionName = ""; //access the name of the instance
  
  virtual double deltaRsquared(  double,  double,  double,  double ) const;


   TTreeFormula* leptons		= NULL;
   TTreeFormula* leptons_pt		= NULL;
   TTreeFormula* leptons_eta		= NULL;
   TTreeFormula* leptons_phi		= NULL;
   TTreeFormula* leptons_cluster_eta	= NULL;
   TTreeFormula* leptons_id_medium	= NULL;
   TTreeFormula* leptons_id_tight	= NULL;
   TTreeFormula* leptons_id_loose	= NULL;
   TTreeFormula* leptons_iso_wp	= NULL;    

  //info on the first two leptons:
  TTreeFormula* lep_0 = NULL;
  TTreeFormula* lep_1 = NULL;
  TTreeFormula* lep_0_pt = NULL; 
  TTreeFormula* lep_1_pt = NULL;
  TTreeFormula* lep_0_eta = NULL;
  TTreeFormula* lep_1_eta = NULL;
  TTreeFormula* lep_0_phi = NULL;
  TTreeFormula* lep_1_phi = NULL;

  TTreeFormula* jet_0_eta = NULL;
  TTreeFormula* jet_1_eta = NULL;
  TTreeFormula* jet_0_phi = NULL;
  TTreeFormula* jet_1_phi = NULL;

  //for plotting/selecting
  bool makeSelection = false;
  bool makeKinematics = false;

  bool plotPt = false;
  bool plotEta = false;
  bool plotDRjet = false;
  bool plotDRlep0 = false;
  bool plotDRlep1 = false;

	
  bool useLoose = false;
  bool useTight = false;
  bool selectMuon = false;
  bool selectElectron =false;



  // TLorentzVector* vlep0 = NULL;
  // TLorentzVector* vlep1 = NULL;
  // TLorentzVector* vlep2 = NULL;

	
  // std::vector<int>    *leptons			= 0;
  // std::vector<double> *leptons_pt		= 0;
  // std::vector<double> *leptons_eta		= 0;
  // std::vector<double> *leptons_cluster_eta	= 0;
  // std::vector<int>    *leptons_id_medium	= 0;
  // std::vector<int>    *leptons_id_loose		= 0;
  // std::vector<int>    *leptons_iso_wp		= 0;    

   // int nleptons			= 0;
   // int nleptons_pt		= 0;
   // int nleptons_eta		= 0;
   // int nleptons_cluster_eta	= 0;
   // int nleptons_id_medium		= 0;
   // int nleptons_id_loose		= 0;
   // int nleptons_iso_wp		= 0;    
 

public:
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;

  FakeLepSel_ll();
  FakeLepSel_ll(const TString& expression);
  virtual ~FakeLepSel_ll();
public:
  bool parseExpression(const TString& expr);
  void clearParsedExpression();

  virtual TString getActiveExpression() const override;

  //public:
  //DECLARE_OBSERVABLE_FACTORY(FakeLepSel_ll,TString expr)

  ClassDef(FakeLepSel_ll, 0);

};
#endif
