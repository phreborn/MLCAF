#ifndef __EventSelection_lfv_leplep_default__
#define __EventSelection_lfv_leplep_default__
#include "QFramework/TQAlgorithm.h"
#include "QFramework/TQSample.h"

#include "TLorentzVector.h"
#include "TTreeFormula.h"
#include "Htautau/EventSelection.h"
#include "Htautau/EventSelection_leplep_base.h"
#include <vector>

class EventSelection_lfv_leplep_default : public EventSelection_leplep_base<EventSelection_lfv_leplep_default> {
public:
  EventSelection_lfv_leplep_default(const TString& expression="", int systematic=0, int flag=-1);
  virtual ~EventSelection_lfv_leplep_default();
  ClassDef(EventSelection_lfv_leplep_default, 1);

protected:
//  virtual bool add_trigger_sf_brachnes();
//  virtual bool add_lepton_sf_brachnes();
//  //virtual bool obtain_lepton_sf();
//  //virtual bool calculate_variables();
//
//  virtual bool el_selection(int el_idx) const;
//  virtual bool mu_selection(int mu_idx) const;
};
#endif
