#include "Htautau/EventSelection.h"
#include <limits>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>
#include "QFramework/TQIterator.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TBranch.h"

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(EventSelection)



//______________________________________________________________________________________________

EventSelection::EventSelection(const TString& expression, int systematic, int flag):m_systematic(systematic),m_flag(flag) {
  SetName(TQObservable::makeObservableName(expression));
  if ((m_flag & 0xFF) == 15) is15=true;
  if ((m_flag & 0xFF) == 16) is16=true;
  if ((m_flag & 0xF00) == 0x100) isTemplateFake=true;
  //std::cout << "EventSelection flags " << m_flag << " " << is15 << " " << is16  << " " << isTemplateFake << std::endl;
}
//______________________________________________________________________________________________

EventSelection::~EventSelection() {

  // default destructor
}
//______________________________________________________________________________________________

bool EventSelection::provideSystematicMap(const std::map < TString, int > &map){
    m_systematicMap=map;
    //for (auto e: map) std::cout<< e.first << " " << e.second << std::endl;
    return true;
}

int EventSelection::getSystematic(const TString & syst) {
    if ( m_systematicMap.find(syst) == m_systematicMap.end() && m_systematic != -1 ) {
        std::cout << "WARNING: cannot find systematics " << syst << std::endl;
        return -999;
    }
    if (m_systematicMap.size() ==0) return -9999;
    return m_systematicMap[syst];
}

bool EventSelection::finalize(){
    delete m_event_number;
    delete m_run_number;

    delete m_jets_pt;
    delete m_jets_eta;
    delete m_jets_phi;
    delete m_jets_m;
    delete m_jets_mvx_tagged;

    delete m_leptons;
    delete m_leptons_pt;
    delete m_leptons_eta;
    delete m_leptons_phi;
    delete m_leptons_m;
    delete m_leptons_q;

    if (!m_isData || m_isBoth){
      delete m_lep_matched_lep;
      delete m_lep_matched_lep_pdgId;
      delete m_lep_matched_lep_mother_pdgId;
      delete m_lep_matched_lep_origin;
      delete m_lep_matched_lep_type;
    }

    delete m_taus_pt;
    delete m_taus_eta;
    delete m_taus_phi;
    delete m_taus_m;

    delete m_dilep_mt_lep0_met;
    delete m_dilep_met_lep0_cos_dphi;
    delete m_dilep_met_lep1_cos_dphi;
    delete m_dilep_deta;
    delete m_dilep_mmc_maxw_m;
    delete m_dilep_mmc_mlm_m;
    delete m_dilep_mmc_mlnu3p_m;
    delete m_dilep_coll_approx_x0;
    delete m_dilep_coll_approx_x1;

    return true;
}

bool EventSelection::add_particle_branches()  {
    additional_branches.push_back("jets_pt");
    additional_branches.push_back("jets_eta");
    additional_branches.push_back("jets_phi");
    additional_branches.push_back("jets_m");
    additional_branches.push_back("jets_mvx_tagged");

    additional_branches.push_back("leptons");
    additional_branches.push_back("leptons_pt");
    additional_branches.push_back("leptons_eta");
    additional_branches.push_back("leptons_phi");
    additional_branches.push_back("leptons_m");
    additional_branches.push_back("leptons_q");
    additional_branches.push_back("dilep_mt_lep0_met");
    additional_branches.push_back("dilep_met_lep0_cos_dphi");
    additional_branches.push_back("dilep_met_lep1_cos_dphi");
    additional_branches.push_back("dilep_deta");
    additional_branches.push_back("dilep_mmc_maxw_m");
    additional_branches.push_back("dilep_mmc_mlm_m");
    additional_branches.push_back("dilep_mmc_mlnu3p_m");
    additional_branches.push_back("dilep_coll_approx_x0");
    additional_branches.push_back("dilep_coll_approx_x1");
    additional_branches.push_back("dilep_coll_approx_m");
    //additional_branches.push_back("lep_lep_met_pt");

    if (!m_isData || m_isBoth){
      additional_branches.push_back("leptons_matched_lep");
      additional_branches.push_back("leptons_matched_lep_pdgId");
      additional_branches.push_back("leptons_matched_lep_mother_pdgId");
      additional_branches.push_back("leptons_matched_lep_origin");
      additional_branches.push_back("leptons_matched_lep_type");
    }

    additional_branches.push_back("taus_pt");
    additional_branches.push_back("taus_eta");
    additional_branches.push_back("taus_phi");
    additional_branches.push_back("taus_m");

    additional_branches.push_back("met_et");
    additional_branches.push_back("met_etx");
    additional_branches.push_back("met_ety");
    additional_branches.push_back("met_phi");

    //additional_branches.push_back("category_2jetVBF");
    //additional_branches.push_back("category_boosted");

    return true;
}


bool EventSelection::connect_particle_branches()  {
    m_jets_pt              = new TTreeFormula( "jets_pt"        , "jets_pt"              , this->fTree);
    m_jets_eta             = new TTreeFormula( "jets_eta"       , "jets_eta"             , this->fTree);
    m_jets_phi             = new TTreeFormula( "jets_phi"       , "jets_phi"             , this->fTree);
    m_jets_m               = new TTreeFormula( "jets_m"         , "jets_m"               , this->fTree);
    m_jets_mvx_tagged      = new TTreeFormula("jets_mvx_tagged" , "jets_mvx_tagged"      , this->fTree);

    m_leptons              = new TTreeFormula( "leptons"        , "leptons"              , this->fTree);
    m_leptons_pt           = new TTreeFormula( "leptons_pt"     , "leptons_pt"           , this->fTree);
    m_leptons_eta          = new TTreeFormula( "leptons_eta"    , "leptons_eta"          , this->fTree);
    m_leptons_phi          = new TTreeFormula( "leptons_phi"    , "leptons_phi"          , this->fTree);
    m_leptons_m            = new TTreeFormula( "leptons_m"      , "leptons_m"            , this->fTree);
    m_leptons_q            = new TTreeFormula( "leptons_q"      , "leptons_q"            , this->fTree);

    if (!m_isData || m_isBoth){
      m_lep_matched_lep              = new TTreeFormula( "leptons_matched_lep", "leptons_matched_lep", this->fTree);
      m_lep_matched_lep_pdgId        = new TTreeFormula( "leptons_matched_lep_pdgId", "leptons_matched_lep_pdgId", this->fTree);
      m_lep_matched_lep_mother_pdgId = new TTreeFormula( "leptons_matched_lep_mother_pdgId", "leptons_matched_lep_mother_pdgId", this->fTree);
      m_lep_matched_lep_origin       = new TTreeFormula( "leptons_matched_lep_origin", "leptons_matched_lep_origin", this->fTree);
      m_lep_matched_lep_type         = new TTreeFormula( "leptons_matched_lep_type", "leptons_matched_lep_type", this->fTree);
    }


    m_taus_pt                         = new TTreeFormula( "taus_pt"                           , "taus_pt"                           , this->fTree);
    m_taus_eta                        = new TTreeFormula( "taus_eta"                          , "taus_eta"                          , this->fTree);
    m_taus_phi                        = new TTreeFormula( "taus_phi"                          , "taus_phi"                          , this->fTree);
    m_taus_m                          = new TTreeFormula( "taus_m"                            , "taus_m"                            , this->fTree);

    m_dilep_mt_lep0_met = new TTreeFormula( "dilep_mt_lep0_met", "dilep_mt_lep0_met", this->fTree);
    m_dilep_met_lep0_cos_dphi = new TTreeFormula( "dilep_met_lep0_cos_dphi", "dilep_met_lep0_cos_dphi", this->fTree);
    m_dilep_met_lep1_cos_dphi = new TTreeFormula( "dilep_met_lep1_cos_dphi", "dilep_met_lep1_cos_dphi", this->fTree);
    m_dilep_deta = new TTreeFormula( "dilep_deta", "dilep_deta", this->fTree);

    m_dilep_mmc_maxw_m   = new TTreeFormula("dilep_mmc_maxw_m", "dilep_mmc_maxw_m", this->fTree);
    m_dilep_mmc_mlm_m    = new TTreeFormula("dilep_mmc_mlm_m", "dilep_mmc_mlm_m", this->fTree);
    m_dilep_mmc_mlnu3p_m = new TTreeFormula("dilep_mmc_mlnu3p_m", "dilep_mmc_mlnu3p_m", this->fTree);

    m_dilep_coll_approx_x0 = new TTreeFormula( "dilep_coll_approx_x0", "dilep_coll_approx_x0", this->fTree);
    m_dilep_coll_approx_x1 = new TTreeFormula( "dilep_coll_approx_x1", "dilep_coll_approx_x1", this->fTree);

    m_met_et               = new TTreeFormula( "met_et"         , "met_et"               , this->fTree);
    m_met_etx              = new TTreeFormula( "met_etx"        , "met_etx"              , this->fTree);
    m_met_ety              = new TTreeFormula( "met_ety"        , "met_ety"              , this->fTree);
    m_met_phi              = new TTreeFormula( "met_phi"        , "met_phi"              , this->fTree);


    m_dilep_coll_approx_x0 = new TTreeFormula( "dilep_coll_approx_x0"      , "dilep_coll_approx_x0" , this->fTree);
    m_dilep_coll_approx_x1 = new TTreeFormula( "dilep_coll_approx_x1"      , "dilep_coll_approx_x1" , this->fTree);
    m_dilep_coll_approx_m  = new TTreeFormula ("dilep_coll_approx_m"     , "dilep_coll_approx_m"  , this->fTree);
    //m_lep_lep_met_pt       = new TTreeFormula ("lep_lep_met_pt",         "lep_lep_met_pt", this->fTree );

    //m_category_2jetVBF = new TTreeFormula("category_2jetVBF","category_2jetVBF",this->fTree);
    //m_category_boosted = new TTreeFormula("category_boosted","category_boosted",this->fTree);
    return true;
}


bool EventSelection::add_trigger_branches() {
    return true;
}


bool EventSelection::connect_trigger_branches() {
    return true;
}


bool EventSelection::add_lepton_sf_brachnes() {
    return true;
}


bool EventSelection::connect_lepton_sf_brachnes() {
    return true;
}

bool EventSelection::add_jet_sf_brachnes() {
    return true;
}


bool EventSelection::connect_jet_sf_brachnes() {
    return true;
}


bool EventSelection::add_trigger_sf_brachnes() {
    return true;
}


bool EventSelection::connect_trigger_sf_brachnes() {
    return true;
}

//______________________________________________________________________________________________


bool EventSelection::initialize(TQSample* sample) {

    /* the sample to use has to be valid */
    if(!sample) return false;

    /* try to get a tree token */
    this->fTreeToken = sample->getTreeToken();
    if (!this->fTreeToken) return false;

    this->fSample = sample;
    //this->fTreeToken->setOwner(this);
    //this->fTree = static_cast<TTree*>(this->fTreeToken->getContent());

    bool mcfound=false;

    TObjArray * list = fTree->GetListOfBranches();
    //std::cout << "tree " << fTree << std::endl;
    for (int  i=0; i<=  list->LastIndex() ; i++) {
        if (TString(((TBranch *) list->At(i))->GetName())==TString("weight_mc")) {
            //std::cout << "MC found" << std::endl;
            mcfound=true;
        }
    }

    if (m_isBoth) {
        m_isBoth=false;
    }
    if (mcfound) m_isData=false; else m_isData=true;

    TString run_number_name="run_number";
    if(!m_isData) {
        run_number_name="NOMINAL_pileup_random_run_number";
        if ( m_systematic == getSystematic ( "PU_weight_up"   )  ) run_number_name="PRW_DATASF_1up_pileup_random_run_number";
        if ( m_systematic == getSystematic ( "PU_weight_down"   )  ) run_number_name="PRW_DATASF_1down_pileup_random_run_number";
    }

    std::cout << "run_number name " << run_number_name << std::endl;
    additional_branches.push_back(run_number_name);

    add_particle_branches();
    add_trigger_branches();
    add_lepton_sf_brachnes();
    add_trigger_sf_brachnes();
    add_jet_sf_brachnes();

    TObjArray* activeBranches=getBranchNames();

    TQIterator itr(activeBranches);
    while (itr.hasNext()) {
        TObject* bName=itr.readNext();
        if (!bName) continue;
        TString name(bName->GetName());
        //std::cout << "BR active " << name << std::endl;
        if (name.First("*") != kNPOS || fTree->FindBranch(name)) {
            fTree->SetBranchStatus(name,1);
        }
    }

    m_event_number = new TTreeFormula ("event_number" , "event_number" , this->fTree);
    m_run_number   = new TTreeFormula (run_number_name, run_number_name, this->fTree);

    connect_particle_branches();
    connect_trigger_branches();
    connect_lepton_sf_brachnes();
    connect_trigger_sf_brachnes();
    connect_jet_sf_brachnes();

    return true;
}


bool EventSelection::create_objects() {
    jets    = buildVector( m_jets_pt, m_jets_eta, m_jets_phi, m_jets_m);
    leptons = buildVector( m_leptons_pt, m_leptons_eta, m_leptons_phi, m_leptons_m);
    taus    = buildVector( m_taus_pt, m_taus_eta, m_taus_phi, m_taus_m);
    els.clear();
    mus.clear();

    m_leptons->GetNdata();
    els_idx.clear();
    mus_idx.clear();
    for (size_t i=0; i<leptons.size(); i++) {
        if (m_leptons->EvalInstance(i) == 1) {
            mus_idx.push_back(i);
            mus.push_back(leptons[i]);
        } else {
            els_idx.push_back(i);
            els.push_back(leptons[i]);
        }
    }

    if (debug) {
        std::cout << "Aj ";
        printVectors(jets);
        std::cout << "Al ";
        printVectors(leptons);
        std::cout << "Ae ";
        printVectors(els);
        std::cout << "Am ";
        printVectors(mus);
        std::cout << "At ";
        printVectors(taus);

        std::cout << "AeIdx ";
        printVectors(els_idx);
        std::cout << "AmIdx ";
        printVectors(mus_idx);
    }
    return true;
}


bool EventSelection::initialise_branches() {
    m_jets_mvx_tagged->GetNdata();
    m_leptons_q->GetNdata();
    m_dilep_coll_approx_x0->GetNdata();
    m_dilep_coll_approx_x1->GetNdata();
    m_dilep_coll_approx_m->GetNdata();
    //m_lep_lep_met_pt->GetNdata();
    m_met_et->GetNdata();
    m_met_etx->GetNdata();
    m_met_ety->GetNdata();
    m_met_phi->GetNdata();
    return true;
}


bool EventSelection::selection_objects() {
    prepare_selection(els  , els_selected);
    prepare_selection(mus  , mus_selected);
    prepare_selection(taus , taus_selected);
    prepare_selection(jets , jets_selected);

    for (size_t i=0; i<els.size(); i++) {
        int index=els_idx[i];
        if (el_selection(index)){
            els_selected[i]=true;
        } else {
            els_selected[i]=false;
        }
    }
    for (size_t i=0; i<mus.size(); i++) {
        int index=mus_idx[i];
        if (mu_selection(index)){
            mus_selected[i]=true;
        } else {
            mus_selected[i]=false;
        }
    }
    for (size_t i=0; i<taus.size(); i++) {
        int index=i;
        if (tau_selection(index)){
            taus_selected[i]=true;
        } else {
            taus_selected[i]=false;
        }
    }
    for (size_t i=0; i<jets.size(); i++) {
        int index=i;
        if (jet_selection(index)){
            jets_selected[i]=true;
        } else {
            jets_selected[i]=false;
        }
    }

    if (debug) {
        std::cout << "AA j ";
        printVectors(jets_selected);
        std::cout << "AA e ";
        printVectors(els_selected);
        std::cout << "AA m ";
        printVectors(mus_selected);
        std::cout << "AA t ";
        printVectors(taus_selected);
    }
    return true;
}


bool EventSelection::output_objects() {
    leptons_selected_idx.clear();
    for (size_t i=0; i<els_selected.size(); i++) {
        if (els_selected[i]) {
            leptons_selected_idx.push_back(els_idx[i]);
        }
    }
    for (size_t i=0; i<mus_selected.size(); i++) {
        if (mus_selected[i]) {
            leptons_selected_idx.push_back(mus_idx[i]);
        }
    }

    convertSelectionToIndex(els_selected  , &els_idx , els_selected_idx);
    convertSelectionToIndex(mus_selected  , &mus_idx , mus_selected_idx);
    convertSelectionToIndex(taus_selected , NULL     , taus_selected_idx);
    convertSelectionToIndex(jets_selected , NULL     , jets_selected_idx);

    if (debug) {
        std::cout << "Aj_s_Idx ";
        printVectors(jets_selected_idx);
        std::cout << "Al_s_Idx ";
        printVectors(leptons_selected_idx);
        std::cout << "Ae_s_Idx ";
        printVectors(els_selected_idx);
        std::cout << "Am_s_Idx ";
        printVectors(mus_selected_idx);
        std::cout << "At_s_Idx ";
        printVectors(taus_selected_idx);
    }

    els_selected_idx=sortobbjects(els_selected_idx   , m_leptons_pt);
    mus_selected_idx=sortobbjects(mus_selected_idx   , m_leptons_pt);
    leptons_selected_idx=sortobbjects(leptons_selected_idx , m_leptons_pt);
    jets_selected_idx=sortobbjects(jets_selected_idx , m_jets_pt);
    taus_selected_idx=sortobbjects(taus_selected_idx , m_taus_pt);

    if (debug) {
        std::cout << "Aj_sort_Idx ";
        printVectors(jets_selected_idx);
        std::cout << "Al_sort_Idx ";
        printVectors(leptons_selected_idx);
        std::cout << "Ae_sort_Idx ";
        printVectors(els_selected_idx);
        std::cout << "Am_sort_Idx ";
        printVectors(mus_selected_idx);
        std::cout << "At_sort_Idx ";
        printVectors(taus_selected_idx);

        std::cout << "Aj_sort_v ";
        printVectors(jets,&jets_selected_idx);
        std::cout << "Al_sort_v ";
        printVectors(leptons,&leptons_selected_idx);
        std::cout << "Ae_sort_v ";
        printVectors(leptons,&els_selected_idx);
        std::cout << "Am_sort_v ";
        printVectors(leptons,&mus_selected_idx);
        std::cout << "At_sort_v ";
        printVectors(taus,&taus_selected_idx);
    }
    els_selected_vector=getSelectedVector(leptons,els_selected_idx);
    mus_selected_vector=getSelectedVector(leptons,mus_selected_idx);
    jets_selected_vector=getSelectedVector(jets,jets_selected_idx);
    taus_selected_vector=getSelectedVector(taus,taus_selected_idx);
    leptons_selected_vector=getSelectedVector(leptons,leptons_selected_idx);
    return true;
}


bool EventSelection::obtain_trigger_sf() {
    TriggerWeight= 1.0;
    return true;
}


bool EventSelection::obtain_lepton_sf() {
    LeptonWeight=1.0;
    LeptonWeight_tight =1.0;
    LeptonWeight_lep0_tight =1.0;
    LeptonWeight_lep1_tight =1.0;
    return true;
}
bool EventSelection::obtain_jet_sf() {
    JVTweight=1.0;
    MVXweight=1.0;
    return true;
}


bool EventSelection::el_selection(int el_idx) const {
    (void) el_idx;
    return true;
}


bool EventSelection::mu_selection(int mu_idx) const {
    (void) mu_idx;
    return true;
}


bool EventSelection::tau_selection(int tau_idx) const {
    (void) tau_idx;
    return true;
}


bool EventSelection::jet_selection(int jet_idx) const {
    (void) jet_idx;
    return true;
}


bool EventSelection::finalise_selection() {
    return true;
}


bool EventSelection::execute(){

    current_event_number=m_event_number->EvalInstance();

    current_run_number = m_run_number->EvalInstance();

    //debug=true;

    //std::cout << "Aevent " << current_run_number << " "  << current_event_number << " EVS" << std::endl;
    if (debug ) std::cout << "Aevent " << current_run_number << " "  << current_event_number << " EVS" << std::endl;
    event_number = current_event_number;
    run_number   = current_run_number;

    if ((m_flag & 0xFF) == 0 ){
        is15=false;
        is16=false;
        if (run_number <= 284484) is15=true;
        if (run_number > 284484) is16=true;
        if (is15==false && is16==false) std::cout << "WARNING: event is neither 15 nor 16" << std::endl;
    }

    initialise_branches();

    create_objects();
    selection_objects();
    removeoverlap();

    if (debug ) {
        std::cout << "AB j ";
        printVectors(jets_selected);
        std::cout << "AB e ";
        printVectors(els_selected);
        std::cout << "AB m ";
        printVectors(mus_selected);
        std::cout << "AB t ";
        printVectors(taus_selected);
    }

    output_objects();
    obtain_trigger_sf();
    obtain_lepton_sf();
    obtain_jet_sf();
    calculate_variables();
    finalise_selection();
    return true;
}


bool EventSelection::cleanup(){
    return true;
}


TObjArray* EventSelection::getBranchNames() const {
    // retrieve the list of branch names
    // ownership of the list belongs to the caller of the function
    DEBUGclass("retrieving branch names");
    TObjArray* bnames = new TObjArray();
    bnames->SetOwner(false);

    bnames->Add(new TObjString("run_number"));
    bnames->Add(new TObjString("event_number"));

    for (auto s: additional_branches) {
        bnames->Add(new TObjString(s));
        //std::cout << "additional b " << s << std::endl;
    }

    return bnames;
}

//___________________________________________________________________________________________


std::vector <TLorentzVector> EventSelection::buildVector( TTreeFormula *pts, TTreeFormula *etas, TTreeFormula *phis, TTreeFormula *ms) const {
    std::vector <TLorentzVector> result;
    int npts=pts->GetNdata();
    int netas=etas->GetNdata();
    int nphis=phis->GetNdata();
    int nms=ms->GetNdata();
    int num=std::min({npts,netas,nphis,nms});
    for (int n = 0; n<num; n++) {
        TLorentzVector v;
        v.SetPtEtaPhiM(pts->EvalInstance(n),etas->EvalInstance(n),phis->EvalInstance(n),ms->EvalInstance(n));
        result.push_back(v);
    }
    return result;
}


void EventSelection::OVR_DeltaR (const std::vector < TLorentzVector > &vec1, const std::vector <bool> &select1, const std::vector < TLorentzVector > &vec2, std::vector <bool> &select2, double DeltaR) const {
    for (size_t i=0; i<vec1.size(); i++) {
        if (!select1[i]) continue;
        for (size_t j=0; j<vec2.size(); j++) {
            if (!select2[j]) continue;
            if (vec2[j].DeltaR(vec1[i])< DeltaR) {
                select2[j]=false;
            }
        }
    }
}



void EventSelection::prepare_selection(const std::vector < TLorentzVector > &vector, std::vector < bool > &selection) const {
    selection.clear();
    for (auto e:vector) {
        selection.push_back(true);
    }
}


void EventSelection::objectselection(const std::vector < TLorentzVector > &vector, std::vector < bool > &selection, const std::vector < int > * proxy, bool (EventSelection::*selector)(int) const) const {
    for (size_t i=0; i<vector.size(); i++) {
        int index=i;
        if (proxy) index = proxy->at(i);
        if ((this->*selector)(index)){
            selection[i]=true;
        } else {
            selection[i]=false;
        }
    }
}



void EventSelection::convertSelectionToIndex(const std::vector < bool > &selection, const std::vector < int > * proxy,  std::vector < int > &selection_idx) const {
    selection_idx.clear();
    for (size_t i=0; i<selection.size(); i++) {
        int index=i;
        if (proxy) index = proxy->at(i);
        if (selection[i]) selection_idx.push_back(index);
    }
}


std::vector < int > EventSelection::sortobbjects( const std::vector < int > &selection_idx, TTreeFormula * obs) const {
    std::vector < int > result;
    std::vector < double > saved_obs;
    std::vector < double > sorted_obs;
    int nobs=obs->GetNdata();
    for (int i=0; i< nobs; i++) {
        saved_obs.push_back(obs->EvalInstance(i));
    }
    if (debug) {
        std::cout << "sort input ";
        printVectors(selection_idx);
        printVectors(saved_obs);
    }
    for (size_t i=0; i<selection_idx.size(); i++){
        for (size_t j=0; j<selection_idx.size(); j++){
            bool newelem=false;
            if (debug) std::cout << "A " << nobs << " " << selection_idx.size() << " " << saved_obs.size() << " " << sorted_obs.size() << " " << result.size() << " "  << newelem << std::endl;
            if ( sorted_obs.size() == i) {
                newelem=true;
            }
            if (debug) std::cout << "B " << nobs << " " << selection_idx.size() << " " << saved_obs.size() << " " << sorted_obs.size() << " " << result.size() << " "  << newelem << std::endl;
            if ( (newelem || sorted_obs[i]<=saved_obs[selection_idx[j]]) && std::find(result.begin(), result.end(),selection_idx[j]) == result.end()) {
                sorted_obs.resize(i+1);
                result.resize(i+1);
                sorted_obs[i]=saved_obs[selection_idx[j]];
                result[i]=selection_idx[j];
            }
        }
    }
    if (debug) {
        std::cout << "sort output ";
        printVectors(result);
        printVectors(sorted_obs);
    }
    return result;
}


void EventSelection::removeoverlap() {
    OVR_DeltaR(els,els_selected,mus,mus_selected,0.2);
    OVR_DeltaR(jets,jets_selected,mus,mus_selected,0.2);
    OVR_DeltaR(taus,taus_selected,mus,mus_selected,0.2);
    OVR_DeltaR(jets,jets_selected,els,els_selected,0.2);
    OVR_DeltaR(taus,taus_selected,els,els_selected,0.2);
    OVR_DeltaR(taus,taus_selected,jets,jets_selected,0.2);
}


void EventSelection::printVectors (const std::vector < TLorentzVector > &vectors, const std::vector < int > *proxy) const {
    int number=vectors.size();
    if (proxy) number=proxy->size();
    for (int i=0; i< number; i++) {
        std::cout << i << " ";
        int index =i;
        if (proxy) index=proxy->at(i);
        std::cout << vectors[index].Pt() << " " << vectors[index].Eta() << " " << vectors[index].Phi() << " " << vectors[index].M() << " " << std::endl;
    }
    if (vectors.size()== 0) std::cout << std::endl;
}


void EventSelection::printVectors (const std::vector < int > &vectors) const {
    int counter=0;
    for (auto v: vectors) {
        std::cout << counter << ": " << v << " | ";
        counter++;
    }
    std::cout << std::endl;
}


void EventSelection::printVectors (const std::vector < double > &vectors) const {
    int counter=0;
    for (auto v: vectors) {
        std::cout << counter << ": " << v << " | ";
        counter++;
    }
    std::cout << std::endl;
}


void EventSelection::printVectors (const std::vector < bool > &vectors) const {
    int counter=0;
    for (auto v: vectors) {
        std::cout << counter << ": ";
        if (v) std::cout << "t"; else std::cout << "f";
        std::cout << " | ";
        counter++;
    }
    std::cout << std::endl;
}


std::vector < TLorentzVector > EventSelection::getSelectedVector (std::vector < TLorentzVector > vector, std::vector < int > selected_idx){
    std::vector < TLorentzVector > result;
    for (auto idx: selected_idx) {
        result.push_back(vector[idx]);
    }
    return result;
}


bool EventSelection::calculate_variables(){
    calculate_hpto();
    calculate_lepton_variables();
    calculate_jet_variables();
    calculate_sphericity();
    calculate_jet_centrality();
    calculate_hpto_variables();
    calculate_lepton_centrality();
    calculate_central_jet_veto();
    calculate_higgs_pt();

    return true;
}

bool EventSelection::calculate_collinear (const TLorentzVector& k1, const TLorentzVector& k2, Double_t met_etx, Double_t met_ety, Double_t &mass, Double_t &x1, Double_t &x2, Double_t &pt1, Double_t&pt2) {
    x1 = 0; x2 = 0; mass = 0;
    TMatrixD K(2,2);
    K(0, 0) = k1.Px(); K(0, 1) = k2.Px();
    K(1, 0) = k1.Py(); K(1, 1) = k2.Py();
    if(K.Determinant()==0)
        return false;

    TMatrixD M(2, 1);
    M(0, 0) = met_etx; M(1, 0) = met_ety;
    TMatrixD Kinv = K.Invert();
    TMatrixD X(2, 1);
    X = Kinv*M;
    double X1 = X(0, 0);    double X2 = X(1, 0);
    x1 = 1./(1.+X1); x2 = 1./(1.+X2);

    TLorentzVector p1 = k1*(1/x1);
    TLorentzVector p2 = k2*(1/x2);

    mass = (p1+p2).M();
    pt1 = (p1+p2).Pt();
    pt2= (p1+p2+k1+k2).Pt();
    return true;
}

bool EventSelection::calculate_lepton_variables() {

  m_leplep_mvis = -999;
  m_leplep_mt = -999;
  m_leplep_mmc_maxw = -999;
  m_leplep_mmc_mlm = -999;
  m_leplep_mmc_mlnu3p = -999;
  m_leplep_sumpt = -999;
  m_leplep_dphi = -999;
  m_leplep_dphil0m = -999;
  m_leplep_dphil1m = -999;
  m_leplep_detall = -999;
  m_leplep_mll = -999;
  m_leplep_mcollasym = -999;
  m_leplep_sign = 0.;
  m_lep_x0 = -999;
  m_lep_x1 = -999;
  m_leplep_mtLep0 = -999;
  m_leplep_mtLep1 = -999;

  m_leplep_pt_ll = -999;
  m_leplep_pt_tautau = -999;
  m_leplep_coll_pt = -999;

  m_leplep_dphilep0met = -999;
  m_leplep_dphilep1met = -999;

  m_leplep_pt_lep0met = -999;
  m_leplep_pt_lep1met = -999;

  m_dilep_mt_lep0_met->GetNdata();
  m_dilep_met_lep0_cos_dphi->GetNdata();
  m_dilep_met_lep1_cos_dphi->GetNdata();
  m_dilep_deta->GetNdata();
  m_dilep_mmc_maxw_m->GetNdata();
  m_dilep_mmc_mlm_m->GetNdata();
  m_dilep_mmc_mlnu3p_m->GetNdata();
  leptons_is_selected_tight.clear();
  m_lep_pt.clear();
  m_lep_eta.clear();
  m_lepjet_dRmin.clear();

  for(size_t i=0; i<leptons_selected_vector.size(); i++){
    leptons_is_selected_tight.push_back(false);
    //m_lepjet_dRmin.push_back(false);
  }

  int dilepI = 0;
  if (leptons_selected_vector.size()>1) {
      int idx0 = leptons_selected_idx[0];
      int idx1 = leptons_selected_idx[1];
      int idx0_c = idx0<idx1 ? idx0 : idx1 ;
      int idx1_c = idx0<idx1 ? idx1 : idx0 ;
      //calculate dilep index
      int nLep = m_leptons->GetNdata();
      for(int ii=0; ii < nLep; ++ii) {
          bool leave = false;
          for(int jj=ii+1; jj < nLep; ++jj) {
              if(idx0_c==ii && idx1_c==jj) {
                  leave = true;
                  break;
              }
              ++dilepI;
          }
          if(leave) break;
      }


  //long current_event_number=m_event_number->EvalInstance();
  //long current_run_number=m_run_number->EvalInstance();

    m_lep_pt.push_back(leptons_selected_vector[0].Pt());
    m_lep_pt.push_back(leptons_selected_vector[1].Pt());
    m_lep_eta.push_back(leptons_selected_vector[0].Eta());
    m_lep_eta.push_back(leptons_selected_vector[1].Eta());


    TLorentzVector v = leptons_selected_vector[0]+leptons_selected_vector[1];
    m_leplep_mvis=v.M();

    m_leplep_pt_ll=v.Pt();

    m_leplep_dphi = leptons_selected_vector[0].DeltaPhi(leptons_selected_vector[1]);
    m_leplep_sumpt = leptons_selected_vector[0].Pt() + leptons_selected_vector[1].Pt();
    m_leplep_sign = (m_leptons_q->EvalInstance(idx0)*m_leptons_q->EvalInstance(idx1));
    m_leplep_mt   = m_dilep_mt_lep0_met->EvalInstance(dilepI);
    m_leplep_dphil0m = m_dilep_met_lep0_cos_dphi->EvalInstance(dilepI);
    m_leplep_dphil1m = m_dilep_met_lep1_cos_dphi->EvalInstance(dilepI);
    m_leplep_detall = m_dilep_deta->EvalInstance(dilepI);
    m_leplep_mll = sqrt(2*leptons_selected_vector[0].Pt()*leptons_selected_vector[1].Pt()*(cosh(leptons_selected_vector[0].Eta()-leptons_selected_vector[1].Eta())-cos(leptons_selected_vector[0].DeltaPhi(leptons_selected_vector[1]))));
    m_lep_x0      = m_dilep_coll_approx_x0->EvalInstance(dilepI);
    m_lep_x1      = m_dilep_coll_approx_x1->EvalInstance(dilepI);
    m_lep_coll_m  = m_dilep_coll_approx_m->EvalInstance(dilepI);
    m_leplep_mmc_maxw    = m_dilep_mmc_maxw_m->EvalInstance(dilepI);
    m_leplep_mmc_mlm     = m_dilep_mmc_mlm_m->EvalInstance(dilepI);
    m_leplep_mmc_mlnu3p  = m_dilep_mmc_mlnu3p_m->EvalInstance(dilepI);

    double mass, x1,x2, pt1,pt2;
    calculate_collinear(leptons_selected_vector[0],leptons_selected_vector[1], m_met_etx->EvalInstance(), m_met_ety->EvalInstance(), mass, x1,x2, pt1, pt2);

    m_leplep_pt_tautau=pt1;
    m_leplep_coll_pt=pt2;

    // matching
    m_lep0_ismatched = false;
    m_lep1_ismatched = false;

    if (!m_isData || m_isBoth){
      m_lep_matched_lep->GetNdata();
      m_lep_matched_lep_pdgId->GetNdata();
      m_lep_matched_lep_mother_pdgId->GetNdata();
      m_lep_matched_lep_origin->GetNdata();
      m_lep_matched_lep_type->GetNdata();

      int lep0_matched_lep = m_lep_matched_lep->EvalInstance(idx0);
      int lep0_matched_lep_pdgId = m_lep_matched_lep_pdgId->EvalInstance(idx0);
      int lep0_matched_lep_mother_pdgId = m_lep_matched_lep_mother_pdgId->EvalInstance(idx0);
      int lep0_matched_lep_origin = m_lep_matched_lep_origin->EvalInstance(idx0);
      int lep0_matched_lep_type = m_lep_matched_lep_type->EvalInstance(idx0);
      int lep1_matched_lep = m_lep_matched_lep->EvalInstance(idx1);
      int lep1_matched_lep_pdgId = m_lep_matched_lep_pdgId->EvalInstance(idx1);
      int lep1_matched_lep_mother_pdgId = m_lep_matched_lep_mother_pdgId->EvalInstance(idx1);
      int lep1_matched_lep_origin = m_lep_matched_lep_origin->EvalInstance(idx1);
      int lep1_matched_lep_type = m_lep_matched_lep_type->EvalInstance(idx1);

      if(lep0_matched_lep>0){
          if(fabs(lep0_matched_lep_pdgId) == 11 || fabs(lep0_matched_lep_pdgId) == 13){
              if(fabs(lep0_matched_lep_mother_pdgId) <= 24 ){
                  m_lep0_ismatched=true;
              }
          }
          else if (fabs(lep0_matched_lep_origin) == 13  && (fabs(lep0_matched_lep_type) == 2 || fabs(lep0_matched_lep_type) == 6)){
              m_lep0_ismatched=true;
          }
      }
      if(lep1_matched_lep>0){
          if(fabs(lep1_matched_lep_pdgId) == 11 || fabs(lep1_matched_lep_pdgId) == 13){
              if(fabs(lep1_matched_lep_mother_pdgId) <= 24 ){
                  m_lep1_ismatched=true;
              }
          }
          else if (fabs(lep1_matched_lep_origin) == 13  && (fabs(lep1_matched_lep_type) == 2 || fabs(lep1_matched_lep_type) == 6)){
              m_lep1_ismatched=true;
          }
      }
    }

  }


  for(size_t i=0; i<leptons_selected_vector.size(); i++){
      TLorentzVector lep = leptons_selected_vector[i];
      double dRlj = 9999999.;
      for(size_t j=0; j<jets_selected_vector.size(); j++){
          TLorentzVector jet = jets_selected_vector[j];
          double dRlj_tmp = lep.DeltaR(jet);
          if(dRlj_tmp < dRlj) {
              dRlj = dRlj_tmp;
          }
      }
      m_lepjet_dRmin.push_back(dRlj);
  }

  TLorentzVector met_vec;
  met_vec.SetPxPyPzE(m_met_etx->EvalInstance(), m_met_ety->EvalInstance(),0,0);
  if (leptons_selected_vector.size()>0){
      m_leplep_mtLep0=sqrt( 2*leptons_selected_vector[0].Pt()*met_vec.Pt()* (1-cos (leptons_selected_vector[0].DeltaPhi(met_vec)) ) );
      m_leplep_dphilep0met=leptons_selected_vector[0].DeltaPhi(met_vec);
      m_leplep_pt_lep0met=(leptons_selected_vector[0]+met_vec).Pt();
  }
  if (leptons_selected_vector.size()>1){
      m_leplep_mtLep1=sqrt( 2*leptons_selected_vector[1].Pt()*met_vec.Pt()* (1-cos (leptons_selected_vector[1].DeltaPhi(met_vec)) ) );
      m_leplep_dphilep1met=leptons_selected_vector[1].DeltaPhi(met_vec);
      m_leplep_mcollasym = sqrt(2*leptons_selected_vector[0].Pt()*(leptons_selected_vector[1].Pt()+met_vec.Pt())*(cosh(leptons_selected_vector[0].Eta()-leptons_selected_vector[1].Eta())-cos(leptons_selected_vector[0].DeltaPhi(leptons_selected_vector[1]))));
      m_leplep_pt_lep1met=(leptons_selected_vector[1]+met_vec).Pt();
  }

  return true;

}



bool EventSelection::calculate_jet_variables() {
    m_jet0_pt = -999;
    m_jet1_pt = -999;
    m_jet_mjj = -999;
    m_jet_deta = -999;
    m_leplep_nJetPt25 = 0;
    m_leplep_nJetEta2p4Pt25 = 0;
    if(jets_selected_vector.size()>0){
        m_jet0_pt = jets_selected_vector[0].Pt();
    }
    if(jets_selected_vector.size()>1){
        m_jet1_pt = jets_selected_vector[1].Pt();
    }
    if (jets_selected_vector.size()>1) {
        TLorentzVector v = jets_selected_vector[0]+jets_selected_vector[1];
        m_jet_mjj=v.M();
        m_jet_deta = fabs(jets_selected_vector[0].Eta()-jets_selected_vector[1].Eta());
    }
    for (auto j: jets_selected_vector) {
        if (j.Pt()>25000) m_leplep_nJetPt25+=1;
        if (j.Pt()>25000 && fabs(j.Eta())<2.4) m_leplep_nJetEta2p4Pt25+=1;
    }
    return true;
}


bool EventSelection::calculate_jet_centrality() {
    m_jet_centrality = -999;
    if (jets_selected_vector.size()>2) {
        double center = (jets_selected_vector[0].Eta() +jets_selected_vector[1].Eta()) / 2.;
        double width  = 1. / ((jets_selected_vector[0].Eta() - center)*(jets_selected_vector[0].Eta() - center));
        m_jet_centrality = TMath::Exp(-width * ((jets_selected_vector[2].Eta() - center)*(jets_selected_vector[2].Eta() - center)));
    }
    return true;
}

bool EventSelection::calculate_lepton_centrality() {
    m_lepton_centrality = false;
    //std::cout << "lj " << leptons_selected_vector.size() << " "  << jets_selected_vector.size() << std::endl;
    if (leptons_selected_vector.size()<2 || jets_selected_vector.size()< 2) return true;
    double max_jet_eta= std::max(jets_selected_vector[0].Eta(),jets_selected_vector[1].Eta());
    double min_jet_eta= std::min(jets_selected_vector[0].Eta(),jets_selected_vector[1].Eta());
    m_lepton_centrality=(leptons_selected_vector[0].Eta() < max_jet_eta && leptons_selected_vector[0].Eta()> min_jet_eta &&
            leptons_selected_vector[1].Eta() < max_jet_eta && leptons_selected_vector[1].Eta()> min_jet_eta );
    //std::cout << jets_selected_vector[0].Eta() <<  " " << jets_selected_vector[1].Eta()  << " " << leptons_selected_vector[0].Eta() << " " << leptons_selected_vector[1].Eta() << " " << max_jet_eta <<" " << min_jet_eta << m_lepton_centrality << std::endl;
    return true;
}

bool EventSelection::calculate_central_jet_veto(){
    m_central_jet_veto=true;
    if (jets_selected_vector.size()< 3) return true;
    double max_jet_eta= std::max(jets_selected_vector[0].Eta(),jets_selected_vector[1].Eta());
    double min_jet_eta= std::min(jets_selected_vector[0].Eta(),jets_selected_vector[1].Eta());
    //std::cout << jets_selected_vector[0].Eta() <<  " " << jets_selected_vector[1].Eta()  << " " << max_jet_eta <<" " << min_jet_eta << m_lepton_centrality << std::endl;
    for (size_t njet =2; njet < jets_selected_vector.size() ; njet++) {
        //std::cout << jets_selected_vector[njet].Eta() << std::endl;
        if (jets_selected_vector[njet].Pt() >=25000 && fabs(jets_selected_vector[njet].Eta()) <=2.4 && jets_selected_vector[njet].Eta() >= min_jet_eta && jets_selected_vector[njet].Eta()<= max_jet_eta) m_central_jet_veto=false;
    }
    //std::cout << "pt ";
    //for (auto jet:jets_selected_vector) {
    //    std::cout << jet.Pt() << " ";
    //}
    //std::cout <<  std::endl;
    //for (auto jet:jets_selected_idx) {
    //    std::cout << jet << " ";
    //}
    //std::cout << std::endl;
    return true;
}

bool EventSelection::calculate_hpto_variables(){
    TLorentzVector total;
    m_hpto = -999.;
    for (auto vect : m_hpto_vectors) {
        total-=vect;
    }
    m_hpto = total.Vect().Pt();
    m_hpto_etx = total.Vect().Px();
    m_hpto_ety = total.Vect().Py();
    m_hpto_phi = total.Phi();

    m_hpto=sqrt(m_hpto_etx*m_hpto_etx+m_hpto_ety*m_hpto_ety);
    if (leptons_selected_vector.size()>=2) massCollinear(leptons_selected_vector[0],leptons_selected_vector[1],m_hpto_etx,m_hpto_ety,m_hpto_x0,m_hpto_x1,m_hpto_coll_m);
    else {
        m_hpto_coll_m=0;
        m_hpto_x1=0;
        m_hpto_x0=0;
    }
    return true;
}


bool EventSelection::calculate_hpto(){
    std::vector < TLorentzVector > vects;
    for (auto lep: leptons_selected_vector) {
        if (vects.size()<2) vects.push_back(lep);
    }
    for (auto jet : jets_selected_vector) {
        if (jet.Pt()>25*1000) vects.push_back(jet);
    }
    m_hpto_vectors= vects;
    return true;
}


bool EventSelection::calculate_sphericity(){
    m_sphericity = -999;
    std::vector < TLorentzVector > vects;
    for (auto lep: leptons_selected_vector) {
        if (vects.size()<2) vects.push_back(lep);
    }
    for (auto jet : jets_selected_vector) {
        vects.push_back(jet);
    }
    if (vects.size() == 0) {
        m_sphericity=0;
        return true;
    }
    TMatrixD S(3,3);
    for(uint i=0; i<3; ++i){
        for(uint j=0; j<3; ++j){
            S[i][j] = 0;
            for(auto vect : vects) {
                S[i][j] += (vect.Vect()[i] * vect.Vect()[j]);
            }
        }
    }

    // normalize
    double norm = 0;
    for(auto vect : vects) norm += (vect.Vect().Mag() * vect.Vect().Mag());
    S *= 1/norm;

    TVectorD eigenValues;
    S.EigenVectors(eigenValues);

    std::vector<double> eigvals = {eigenValues[0], eigenValues[1], eigenValues[2]};
    std::sort(eigvals.begin(), eigvals.end());

    // getSphericity
    m_sphericity=(eigvals[0] + eigvals[1]) * 1.5;
    return true;

}

bool EventSelection::calculate_higgs_pt(){
    m_higgs_pt=0;
    TLorentzVector vec;
    TLorentzVector met_vec;
    if (leptons_selected_vector.size()>=2) {
        vec+=leptons_selected_vector[0]+leptons_selected_vector[1];
    }
    met_vec.SetPxPyPzE(m_met_etx->EvalInstance(), m_met_ety->EvalInstance(),0,0);
    vec+=met_vec;
    m_higgs_pt=vec.Pt();
    return true;
}

bool EventSelection::massCollinear(const TLorentzVector& k1, const TLorentzVector& k2, Double_t met_etx, Double_t met_ety, Double_t &mass, Double_t &x1, Double_t &x2) {
    x1 = 0;
    x2 = 0;
    mass = 0;
    TMatrixD K(2,2);
    K(0, 0) = k1.Px();
    K(0, 1) = k2.Px();
    K(1, 0) = k1.Py();
    K(1, 1) = k2.Py();
    if(K.Determinant()==0)  return false;

    TMatrixD M(2, 1);
    M(0, 0) = met_etx;
    M(1, 0) = met_ety;
    TMatrixD Kinv = K.Invert();
    TMatrixD X(2, 1);
    X = Kinv*M;
    double X1 = X(0, 0);
    double X2 = X(1, 0);
    x1 = 1./(1.+X1);
    x2 = 1./(1.+X2);

    TLorentzVector p1 = k1*(1/x1);
    TLorentzVector p2 = k2*(1/x2);
    mass = (p1+p2).M();
    return kTRUE;
}
