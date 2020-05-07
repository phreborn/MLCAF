//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __PZETA__
#define __PZETA__
#include "BSMtautauCAF/LepHadObservable.h"

class Pzeta : public LepHadObservable {
protected:
  // put here any data members your class might need

public:
  virtual double getValue() const override;
  virtual TObjArray* getBranchNames() const override;
protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;

  float p_z_phi_custom(float lep_phi, float tau_phi, float frac) const;
  float p_z_vis(float p_z_phi, float lep_pt, float lep_phi, float tau_pt, float tau_phi) const;
  float p_z(float p_z_phi, float lep_pt, float lep_phi, float tau_pt, float tau_phi, float met_et, float met_phi) const;

public:
  Pzeta();
  Pzeta(const TString& name);
  virtual ~Pzeta();
  ClassDefOverride(Pzeta, 1);


};
#endif
