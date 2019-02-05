
#include "Htautau/EventSelection_leplep_default.h"
#include <limits>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>
#include "QFramework/TQIterator.h"
#include "Htautau/EventSelection_leplep_base_static.h"

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
//

ClassImp(EventSelection_leplep_default)

//______________________________________________________________________________________________
EventSelection_leplep_default::EventSelection_leplep_default(const TString& expression, int systematic, int flag):EventSelection_leplep_base(expression,systematic,flag){
}
//______________________________________________________________________________________________
EventSelection_leplep_default::~EventSelection_leplep_default() {
  // default destructor
}
