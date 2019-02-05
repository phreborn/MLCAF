#ifndef __EventSelection_leplep_fake__
#define __EventSelection_leplep_fake__
#include "QFramework/TQAlgorithm.h"
#include "QFramework/TQSample.h"

#include "TLorentzVector.h"
#include "TTreeFormula.h"
#include "Htautau/EventSelection.h"
#include "Htautau/EventSelection_leplep_base.h"
#include <vector>

class EventSelection_leplep_fake : public EventSelection_leplep_base<EventSelection_leplep_fake> {
protected:
  virtual bool add_trigger_sf_brachnes();
  virtual bool add_lepton_sf_brachnes();
  virtual bool obtain_lepton_sf();
  virtual bool calculate_variables();
  virtual bool obtain_trigger_sf();

  virtual bool el_selection(int el_idx) const;
  virtual bool mu_selection(int mu_idx) const;
  virtual bool tau_selection(int tau_idx) const;
  virtual bool jet_selection(int jet_idx) const;


public:
  EventSelection_leplep_fake(const TString& expression="", int systematic=-1, int flag=-1);
  virtual ~EventSelection_leplep_fake();
  ClassDef(EventSelection_leplep_fake, 1);


};
#endif
