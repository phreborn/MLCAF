#ifndef __EventSelection_leplep_default__
#define __EventSelection_leplep_default__
#include "QFramework/TQAlgorithm.h"
#include "QFramework/TQSample.h"

#include "TLorentzVector.h"
#include "TTreeFormula.h"
#include "Htautau/EventSelection.h"
#include "Htautau/EventSelection_leplep_base.h"
#include <vector>

class EventSelection_leplep_default : public EventSelection_leplep_base<EventSelection_leplep_default> {
public:
  EventSelection_leplep_default(const TString& expression="", int systematic=-1, int flag =-1);
  virtual ~EventSelection_leplep_default();
  ClassDef(EventSelection_leplep_default, 1);
};
#endif
