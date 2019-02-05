//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __EventSelectionObs_lfv_base__
#define __EventSelectionObs_lfv_base__
#include "QFramework/TQTreeObservable.h"

#include "TLorentzVector.h"
#include "TTreeFormula.h"
#include <vector>
#include "Htautau/EventSelection_lfv_leplep_default.h"
#include "Htautau/EventSelectionObs_base.h"
//class EventSelectionObs_lfv_leplep_default: public TQTreeObservable {
//    public:
//        EventSelectionObs_lfv_leplep_default(const TString &expression);
//        ~EventSelectionObs_lfv_leplep_default();
//        virtual double getValue() const override;
//        virtual bool hasExpression() const override;
//        virtual const TString& getExpression() const override;
//        virtual void setExpression(const TString& expr) override;
//        bool parseExpression( const TString& expr);
//        virtual TObjArray* getBranchNames() const override;
//        void clearParsedExpression();
//        virtual TString getActiveExpression() const override;
//        ClassDef(EventSelectionObs_lfv_leplep_default,1);
//    protected:
//        TString fExpression = "";
//        virtual bool initializeSelf() override;
//        virtual bool finalizeSelf () override;
//        EventSelectionObs_base <EventSelection_lfv_leplep_default> * EventSelectionObs;
//};
#endif
