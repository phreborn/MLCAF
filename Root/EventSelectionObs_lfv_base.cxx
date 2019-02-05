#include "Htautau/EventSelectionObs_lfv_base.h"
#include <limits>

// uncomment the following line to enable debug printouts
//#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
#include "Htautau/EventSelection_lfv_leplep_default.h"
#include "Htautau/EventSelection_leplep_fake.h"
#include "Htautau/EventSelectionObs_base.h"

//ClassImp (EventSelectionObs_lfv_leplep_default)
//
//// default
//EventSelectionObs_lfv_leplep_default::EventSelectionObs_lfv_leplep_default(const TString &expression):TQTreeObservable(expression){
//    EventSelectionObs = new EventSelectionObs_base < EventSelection_lfv_leplep_default >(expression);
//    this->SetName(TQObservable::makeObservableName(expression));
//    this->setExpression(expression);
//}
//
//EventSelectionObs_lfv_leplep_default::~EventSelectionObs_lfv_leplep_default(){
//    delete EventSelectionObs;
//}
//
//double EventSelectionObs_lfv_leplep_default::getValue() const {
//    return EventSelectionObs->getValue();
//}
//
//bool EventSelectionObs_lfv_leplep_default::hasExpression() const {
//    return true;
//}
//
//const TString& EventSelectionObs_lfv_leplep_default::getExpression() const {
//    return fExpression;
//}
//
//void EventSelectionObs_lfv_leplep_default::setExpression(const TString& expr) {
//    this->fExpression = expr;
//}
//
//TObjArray* EventSelectionObs_lfv_leplep_default::getBranchNames() const {
//    TObjArray* bnames = new TObjArray();
//    bnames->SetOwner(false);
//    return bnames;
//}
//
//bool EventSelectionObs_lfv_leplep_default::parseExpression(const TString& expr){
//    (void)expr;
//    return true;
//}
//
//void EventSelectionObs_lfv_leplep_default::clearParsedExpression(){
//}
//
//TString EventSelectionObs_lfv_leplep_default::getActiveExpression() const {
//    return this->getExpression();
//}
//
//bool EventSelectionObs_lfv_leplep_default::initializeSelf() {
//    if(!this->parseExpression(TQObservable::compileExpression(this->fExpression,this->fSample))){
//        return false;
//    }
//    return true;
//}
//
//bool EventSelectionObs_lfv_leplep_default::finalizeSelf () {
//    this->clearParsedExpression();
//    return true;
//}
//
