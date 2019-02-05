#ifndef __EventSelectionObs_base__
#define __EventSelectionObs_base__
#include "QFramework/TQTreeObservable.h"
#include "TTreeFormula.h"
#include "Htautau/EventSelection_leplep_default.h"
#include "Htautau/EventSelection_leplep_fake.h"
#include "Htautau/EventSelection_leplep_tight.h"
#include "Htautau/EventSelection_lfv_leplep_default.h"

template < typename selection >
class EventSelectionObs_base {
    public:
        EventSelectionObs_base();
        EventSelectionObs_base(const TString& expression);
        virtual ~EventSelectionObs_base();
        virtual double getValue() const;
        ClassDef(EventSelectionObs_base<selection>,1);
    protected:
        selection * ovl;
        bool debug=false;


        TString fExpression = "";

        TTreeFormula *m_event_number;
        TTreeFormula *m_run_number;

        bool jetIndexMode    = false;
        bool elIndexMode     = false;
        bool muIndexMode     = false;
        bool tauIndexMode    = false;
        bool leptonIndexMode = false;

        bool jetNMode    = false;
        bool elNMode     = false;
        bool muNMode     = false;
        bool tauNMode    = false;
        bool leptonNMode = false;

        bool leptonSelectMode = false;
        bool leptonSelectMode_Lep0Tight = false;
        bool leptonSelectMode_Lep1Tight = false;
        bool leptonPt0Mode = false;
        bool leptonPt1Mode = false;
        bool leptonEta0Mode = false;
        bool leptonEta1Mode = false;

        bool lep0MatchMode=false;
        bool lep1MatchMode=false;

        bool lep0jetdRMode=false;
        bool lep1jetdRMode=false;

        int jetIndex    = -1;
        int elIndex     = -1;
        int muIndex     = -1;
        int tauIndex    = -1;
        int leptonIndex = -1;

        bool triggerWeightMode=false;
        bool leptonWeightMode=false;
        bool isTriggeredMCMode=false;
        bool isTriggeredDataMode=false;
        bool isTriggerTypeMode=false;

	bool SpecialtriggerWeightMode=false;
        bool isSpecialTriggeredMCMode=false;
        bool isSpecialTriggeredDataMode=false;
        bool isSpecialTriggerTypeMode=false;

        bool leptonMVisMode=false;
        bool leptonMtMode=false;
        bool leptonMMCmaxwMode=false;
        bool leptonMMCmlmMode=false;
        bool leptonMMCmlnu3pMode=false;
        bool leptonSumPtMode=false;
        bool leptonDphiLLMode=false;
        bool leptonDphiL0METMode=false;
        bool leptonDphiL1METMode=false;
        bool leptonDEtaLLMode=false;
        bool leptonMLLMode=false;
        bool leptonMCollASymMode=false;
        bool leptonSignMode=false;
        bool leptonXCollAppMode=false;
        bool leptonMCollMode=false;
        bool leptonX0CollMode=false;
        bool leptonX1CollMode=false;

        bool jetPt0Mode=false;
        bool jetPt1Mode=false;
        bool jetJVTWeightMode=false;
        bool jetMVXWeightMode=false;
        bool jetBtagMode=false;

        bool mJetJetMode=false;
        bool DetaJetJetMode=false;

        bool metHptoMode=false;

        bool hptoEtxMode=false;
        bool hptoEtyMode=false;
        bool hptoPhiMode=false;
        bool hptoX0Mode=false;
        bool hptoX1Mode=false;
        bool hptoCollmMode=false;
        bool higgsPtMode=false;

        bool bVetoMode=false;
        bool leptonCentralityMode=false;
        bool centralJetVetoMode=false;

        bool jetN25PtMode=false;
        bool jetN2p4Eta25PtMode=false;
        bool MtLep0mode=false;
        bool MtLep1mode=false;
        bool leptonDphiLep0METMode=false;
        bool leptonDphiLep1METMode=false;

        bool PtLLMode=false;
        bool PtTauTauMode=false;
        bool PtCollPtMode=false;

        bool PtLep0METmode=false;
        bool PtLep1METmode=false;

        bool d0l0Mode=false;
        bool d0l1Mode=false;
        bool d0sigl0Mode=false;
        bool d0sigl1Mode=false;

        bool VBFcatMode=false;
        bool VBFcat_ZttCRMode=false;
        bool boostedcatMode=false;
        bool boostedcat_ZttCRMode=false;

	bool runnumberMode=false;
};

class EventSelectionObs_leplep_default: public TQTreeObservable {
    public:
        EventSelectionObs_leplep_default(const TString &expression);
        ~EventSelectionObs_leplep_default();
        virtual double getValue() const override;
        virtual bool hasExpression() const override;
        virtual const TString& getExpression() const override;
        virtual void setExpression(const TString& expr) override;
        bool parseExpression( const TString& expr);
        virtual TObjArray* getBranchNames() const override;
        void clearParsedExpression();
        virtual TString getActiveExpression() const override;
        ClassDef(EventSelectionObs_leplep_default,1);
    protected:
        TString fExpression = "";
        virtual bool initializeSelf() override;
        virtual bool finalizeSelf () override;
        EventSelectionObs_base <EventSelection_leplep_default> * EventSelectionObs;
};

class EventSelectionObs_leplep_fake: public TQTreeObservable {
 public:
  EventSelectionObs_leplep_fake(const TString &expression);
  ~EventSelectionObs_leplep_fake();
  virtual double getValue() const override;
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;
  bool parseExpression( const TString& expr);
  virtual TObjArray* getBranchNames() const override;
  void clearParsedExpression();
  virtual TString getActiveExpression() const override;
  ClassDef(EventSelectionObs_leplep_fake,1);
 protected:
  TString fExpression = "";
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf () override;
  EventSelectionObs_base <EventSelection_leplep_fake> * EventSelectionObs;
};

class EventSelectionObs_leplep_tight: public TQTreeObservable {
 public:
  EventSelectionObs_leplep_tight(const TString &expression);
  ~EventSelectionObs_leplep_tight();
  virtual double getValue() const override;
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;
  bool parseExpression( const TString& expr);
  virtual TObjArray* getBranchNames() const override;
  void clearParsedExpression();
  virtual TString getActiveExpression() const override;
  ClassDef(EventSelectionObs_leplep_tight,1);
 protected:
  TString fExpression = "";
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf () override;
  EventSelectionObs_base <EventSelection_leplep_tight> * EventSelectionObs;
};

class EventSelectionObs_lfv_leplep_default: public TQTreeObservable {
 public:
  EventSelectionObs_lfv_leplep_default(const TString &expression);
  ~EventSelectionObs_lfv_leplep_default();
  virtual double getValue() const override;
  virtual bool hasExpression() const override;
  virtual const TString& getExpression() const override;
  virtual void setExpression(const TString& expr) override;
  bool parseExpression( const TString& expr);
  virtual TObjArray* getBranchNames() const override;
  void clearParsedExpression();
  virtual TString getActiveExpression() const override;
  ClassDef(EventSelectionObs_lfv_leplep_default,1);
 protected:
  TString fExpression = "";
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf () override;
  EventSelectionObs_base <EventSelection_lfv_leplep_default> * EventSelectionObs;
};

#endif
