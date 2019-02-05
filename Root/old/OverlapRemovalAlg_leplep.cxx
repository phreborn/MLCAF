#include "Htautau2015/OverlapRemovalAlg_leplep.h"
#include <limits>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>
#include "QFramework/TQIterator.h"

// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(OverlapRemovalAlg_leplep)

//forward declaration of static members
long OverlapRemovalAlg_leplep::event_number; 
long OverlapRemovalAlg_leplep::run_number; 
std::vector < bool >  OverlapRemovalAlg_leplep::jets_selected;
std::vector < bool >  OverlapRemovalAlg_leplep::els_selected;
std::vector < bool >  OverlapRemovalAlg_leplep::mus_selected;
std::vector < bool >  OverlapRemovalAlg_leplep::taus_selected;
std::vector < int >  OverlapRemovalAlg_leplep::els_idx;
std::vector < int >  OverlapRemovalAlg_leplep::mus_idx;
std::vector < int >  OverlapRemovalAlg_leplep::jets_selected_idx;
std::vector < int >  OverlapRemovalAlg_leplep::leptons_selected_idx;
std::vector < int >  OverlapRemovalAlg_leplep::els_selected_idx;
std::vector < int >  OverlapRemovalAlg_leplep::mus_selected_idx;
std::vector < int >  OverlapRemovalAlg_leplep::taus_selected_idx;
bool OverlapRemovalAlg_leplep::debug;

//______________________________________________________________________________________________
OverlapRemovalAlg_leplep::OverlapRemovalAlg_leplep() {
}
//______________________________________________________________________________________________
OverlapRemovalAlg_leplep::~OverlapRemovalAlg_leplep() {

  // default destructor
}
//______________________________________________________________________________________________

bool OverlapRemovalAlg_leplep::finalize(){
  if (m_event_number)      delete m_event_number;
  if (m_run_number)        delete m_run_number;
  if (m_jets_pt)           delete m_jets_pt    ;
  if (m_jets_eta)          delete m_jets_eta;
  if (m_jets_phi)          delete m_jets_phi;
  if (m_jets_m)            delete m_jets_m     ;
  if (m_leptons)           delete m_leptons    ;
  if (m_leptons_pt)        delete m_leptons_pt ;
  if (m_leptons_eta)       delete m_leptons_eta;
  if (m_leptons_cluster_eta)       delete m_leptons_cluster_eta;
  if (m_leptons_cluster_eta_be2)   delete m_leptons_cluster_eta_be2;
  if (m_leptons_phi)       delete m_leptons_phi;
  if (m_leptons_m)         delete m_leptons_m  ;
  if (m_leptons_iso_wp)    delete m_leptons_iso_wp;
  if (m_leptons_id_loose)  delete m_leptons_id_loose;
  if (m_leptons_id_medium) delete m_leptons_id_medium;
  if (m_leptons_id_tight)  delete m_leptons_id_tight;
  if (m_taus_pt)           delete m_taus_pt    ;
  if (m_taus_eta)          delete m_taus_eta;
  if (m_taus_phi)          delete m_taus_phi;
  if (m_taus_m)            delete m_taus_m     ;
  if (m_taus_n_tracks)     delete m_taus_n_tracks;
  return true;
} 
//______________________________________________________________________________________________
bool OverlapRemovalAlg_leplep::initialize(TQSample* sample) {

  if (debug)  std::cout << "IA" << std::endl;
  //if (this->fTreeToken || this->fTree) return false;


  /* the sample to use has to be valid */
  if (debug)  std::cout << "IB" << std::endl;
  if(!sample) return false;

  /* try to get a tree token */
  this->fTreeToken = sample->getTreeToken();
  //std::cout << "IC" << std::endl;
  if (!this->fTreeToken) return false;

  this->fSample = sample;
  this->fTreeToken->setOwner(this);
  this->fTree = static_cast<TTree*>(this->fTreeToken->getContent());

  TObjArray* activeBranches=getBranchNames();

  TQIterator itr(activeBranches);
  while (itr.hasNext()) {
    TObject* bName=itr.readNext();
    if (!bName) continue;
    TString name(bName->GetName());
    if (name.First("*") != kNPOS || fTree->FindBranch(name)) {
      fTree->SetBranchStatus(name,1);
    }
  }

    m_event_number      = new TTreeFormula ("event_number"      , "event_number"      , this->fTree);
    m_run_number        = new TTreeFormula ("run_number"        , "run_number"        , this->fTree);

    m_jets_pt           = new TTreeFormula( "jets_pt"           , "jets_pt"           , this->fTree);
    m_jets_eta          = new TTreeFormula( "jets_eta"          , "jets_eta"          , this->fTree);
    m_jets_phi          = new TTreeFormula( "jets_phi"          , "jets_phi"          , this->fTree);
    m_jets_m            = new TTreeFormula( "jets_m"            , "jets_m"            , this->fTree);

    m_leptons           = new TTreeFormula( "leptons"           , "leptons"           , this->fTree);
    m_leptons_pt        = new TTreeFormula( "leptons_pt"        , "leptons_pt"        , this->fTree);
    m_leptons_eta       = new TTreeFormula( "leptons_eta"       , "leptons_eta"       , this->fTree);
    m_leptons_cluster_eta       = new TTreeFormula( "leptons_cluster_eta"       , "leptons_cluster_eta"       , this->fTree);
    m_leptons_cluster_eta_be2   = new TTreeFormula( "leptons_cluster_eta_be2"   , "leptons_cluster_eta_be2"   , this->fTree);
    m_leptons_phi       = new TTreeFormula( "leptons_phi"       , "leptons_phi"       , this->fTree);
    m_leptons_m         = new TTreeFormula( "leptons_m"         , "leptons_m"         , this->fTree);
    m_leptons_iso_wp    = new TTreeFormula( "leptons_iso_wp"    , "leptons_iso_wp"    , this->fTree);
    m_leptons_id_loose  = new TTreeFormula( "leptons_id_loose"  , "leptons_id_loose"  , this->fTree);
    m_leptons_id_medium = new TTreeFormula( "leptons_id_medium" , "leptons_id_medium" , this->fTree);
    m_leptons_id_tight  = new TTreeFormula( "leptons_id_tight"  , "leptons_id_tight"  , this->fTree);

    m_taus_pt           = new TTreeFormula( "taus_pt"           , "taus_pt"           , this->fTree);
    m_taus_eta          = new TTreeFormula( "taus_eta"          , "taus_eta"          , this->fTree);
    m_taus_phi          = new TTreeFormula( "taus_phi"          , "taus_phi"          , this->fTree);
    m_taus_m            = new TTreeFormula( "taus_m"            , "taus_m"            , this->fTree);
    m_taus_n_tracks     = new TTreeFormula( "taus_n_tracks"     , "taus_n_tracks"     , this->fTree);

  return true;
}

bool OverlapRemovalAlg_leplep::execute(){
    debug=false;

    long current_event_number=m_event_number->EvalInstance();
    long current_run_number=m_run_number->EvalInstance();

    if (debug) std::cout << "Aevent " << current_run_number << " "  << current_event_number << std::endl;
    event_number = current_event_number;
    run_number   = current_run_number;
    std::vector < TLorentzVector > jets    = buildVector( m_jets_pt, m_jets_eta, m_jets_phi, m_jets_m );
    std::vector < TLorentzVector > leptons = buildVector( m_leptons_pt, m_leptons_eta, m_leptons_phi, m_leptons_m );
    std::vector < TLorentzVector > els;
    std::vector < TLorentzVector > mus;
    std::vector < TLorentzVector > taus    = buildVector( m_taus_pt, m_taus_eta, m_taus_phi, m_taus_m );
    m_leptons->GetNdata();

    els_idx.clear();
    mus_idx.clear();
    for (size_t i=0; i<leptons.size(); i++ ) {
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

    prepare_selection(els  , els_selected);
    prepare_selection(mus  , mus_selected);
    prepare_selection(taus , taus_selected);
    prepare_selection(jets , jets_selected);

    m_leptons_id_loose->GetNdata();
    m_leptons_id_medium->GetNdata();
    m_leptons_id_tight->GetNdata();
    m_leptons_iso_wp->GetNdata();
    m_taus_n_tracks->GetNdata();

    objectselection(els  , els_selected  , &els_idx , &OverlapRemovalAlg_leplep::el_selection);
    objectselection(mus  , mus_selected  , &mus_idx , &OverlapRemovalAlg_leplep::mu_selection);
    objectselection(taus , taus_selected , NULL     , &OverlapRemovalAlg_leplep::tau_selection);
    objectselection(jets , jets_selected , NULL     , &OverlapRemovalAlg_leplep::jet_selection);

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

    removeoverlap(els,els_selected,mus,mus_selected,taus,taus_selected,jets,jets_selected);

    if (debug) {
        std::cout << "AB j ";
        printVectors(jets_selected);
        std::cout << "AB e ";
        printVectors(els_selected);
        std::cout << "AB m ";
        printVectors(mus_selected);
        std::cout << "AB t ";
        printVectors(taus_selected);
    }

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


    return true;
}

bool OverlapRemovalAlg_leplep::cleanup(){
    return true;
}

TObjArray* OverlapRemovalAlg_leplep::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("retrieving branch names");
  TObjArray* bnames = new TObjArray();
  bnames->SetOwner(false);

  // add the branch names needed by your observable here, e.g.
  // bnames->Add(new TObjString("someBranch"));
  bnames->Add(new TObjString("jets_pt"));  
  bnames->Add(new TObjString("jets_eta"));  
  bnames->Add(new TObjString("jets_phi"));  
  bnames->Add(new TObjString("jets_m"));  

  bnames->Add(new TObjString("leptons"));  
  bnames->Add(new TObjString("leptons_pt"));  
  bnames->Add(new TObjString("leptons_eta"));  
  bnames->Add(new TObjString("leptons_cluster_eta"));  
  bnames->Add(new TObjString("leptons_cluster_eta_be2"));  
  bnames->Add(new TObjString("leptons_phi"));  
  bnames->Add(new TObjString("leptons_m"));  
  bnames->Add(new TObjString("leptons_iso_wp"));  
  bnames->Add(new TObjString("leptons_id_loose"));  
  bnames->Add(new TObjString("leptons_id_medium"));  
  bnames->Add(new TObjString("leptons_id_tight"));  

  bnames->Add(new TObjString("taus_pt"));  
  bnames->Add(new TObjString("taus_eta"));  
  bnames->Add(new TObjString("taus_phi"));  
  bnames->Add(new TObjString("taus_m"));  
  bnames->Add(new TObjString("taus_n_tracks"));  
  
  bnames->Add(new TObjString("run_number"));  
  bnames->Add(new TObjString("event_number"));  

  return bnames;
}

//______________________________________________________________________________________________
//______________________________________________________________________________________________
//______________________________________________________________________________________________
//______________________________________________________________________________________________
//______________________________________________________________________________________________
//______________________________________________________________________________________________
//______________________________________________________________________________________________
//______________________________________________________________________________________________
//___________________________________________________________________________________________

std::vector <TLorentzVector> OverlapRemovalAlg_leplep::buildVector( TTreeFormula *pts, TTreeFormula *etas, TTreeFormula *phis, TTreeFormula *ms ) const {
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

void OverlapRemovalAlg_leplep::OVR_DeltaR (const std::vector < TLorentzVector > &vec1, const std::vector <bool> &select1, const std::vector < TLorentzVector > &vec2, std::vector <bool> &select2, double DeltaR) const {
    for (size_t i=0; i<vec1.size(); i++) {
        if (!select1[i]) continue;
        for (size_t j=0; j<vec2.size(); j++) {
            if (!select2[j]) continue;
            if (vec2[j].DeltaR(vec1[i])< DeltaR ) {
               select2[j]=false;
            }
        }
    }
}

//Alena:
void OverlapRemovalAlg_leplep::OVR_DeltaR_anyMu (const std::vector < TLorentzVector > &vec1, const std::vector <bool> &select1, const std::vector < TLorentzVector > &vec2, std::vector <bool> &select2, double DeltaR) const {
  for (size_t i=0; i<vec1.size(); i++) {
    //if (!select1[i]) continue;
    for (size_t j=0; j<vec2.size(); j++) {
      if (!select2[j]) continue;
      if (vec2[j].DeltaR(vec1[i])< DeltaR ) {
	select2[j]=false;
      }
    }
  }
}

void OverlapRemovalAlg_leplep::OVR_DeltaR_El (const std::vector < TLorentzVector > &vec1, const std::vector <bool> &select1, const std::vector < TLorentzVector > &vec2, std::vector <bool> &select2, double DeltaR) const {
  for (size_t i=0; i<vec1.size(); i++) {
    if (vec1[i].Pt()<15*1000 || m_leptons_id_medium->EvalInstance(i)== 0) continue;
    for (size_t j=0; j<vec2.size(); j++) {
      if (!select2[j]) continue;
      if (vec2[j].DeltaR(vec1[i])< DeltaR ) {
	select2[j]=false;
      }
    }
  }
}

void OverlapRemovalAlg_leplep::prepare_selection(const std::vector < TLorentzVector > &vector, std::vector < bool > &selection) const {
    selection.clear();
    for (auto e:vector) {
        selection.push_back(true);
    }
}

void OverlapRemovalAlg_leplep::objectselection(const std::vector < TLorentzVector > &vector, std::vector < bool > &selection, const std::vector < int > * proxy, bool (OverlapRemovalAlg_leplep::*selector)(int) const ) const {
      for (size_t i=0; i<vector.size(); i++) {
        int index=i;
        if (proxy) index = proxy->at(i);
        if ((this->*selector)(index)){
            selection[i]=true;
            if (debug) { 
                    //std::cout << "OS pass " << index << std::endl;
            }
        } else {
            selection[i]=false;
            if (debug) { 
                    //std::cout << "OS fail " << index << std::endl;
            }
        }
      }
}

bool OverlapRemovalAlg_leplep::el_selection(int el_idx) const {
  bool result= (m_leptons_pt->EvalInstance(el_idx)>=15*1000 && fabs(m_leptons_cluster_eta->EvalInstance(el_idx))<=2.47 && fabs(m_leptons_cluster_eta_be2->EvalInstance(el_idx))<=2.47 && m_leptons_id_medium->EvalInstance(el_idx)==1 && ((int)m_leptons_iso_wp->EvalInstance(el_idx) % 100000)/10000 > 0);
    if (!result && debug) { 
      std::cout << "e fail " << el_idx << " " <<  m_leptons_pt->EvalInstance(el_idx) << " " << m_leptons_cluster_eta->EvalInstance(el_idx) << " "  <<  m_leptons_id_medium->EvalInstance(el_idx) << " "<< m_leptons_iso_wp->EvalInstance(el_idx) <<std::endl;
    }
    return result;
}

bool OverlapRemovalAlg_leplep::mu_selection(int mu_idx) const {
  bool result= (m_leptons_pt->EvalInstance(mu_idx)>=10*1000 && fabs(m_leptons_eta->EvalInstance(mu_idx))<=2.47 && m_leptons_id_medium->EvalInstance(mu_idx)==1 && ((int)m_leptons_iso_wp->EvalInstance(mu_idx)%100000)/10000 > 0);
    if (!result && debug) { 
      std::cout << "m fail " << mu_idx << " " <<  m_leptons_pt->EvalInstance(mu_idx) << " " << m_leptons_eta->EvalInstance(mu_idx) << " "  <<  m_leptons_id_medium->EvalInstance(mu_idx) << " " << m_leptons_iso_wp->EvalInstance(mu_idx) <<std::endl;
    }
    return result; 
}

bool OverlapRemovalAlg_leplep::tau_selection(int tau_idx) const {
    int taus_n_tracks=m_taus_n_tracks->EvalInstance(tau_idx);
    double taus_eta=m_taus_eta->EvalInstance(tau_idx);
    bool result= (m_taus_pt->EvalInstance(tau_idx) >20*1000  && (taus_n_tracks == 1 || taus_n_tracks  == 3) && (taus_eta < 2.5 && (taus_eta<1.37 || taus_eta>1.52) ) );
    if (!result && debug) { 
       std::cout << "tau fail " << tau_idx << " " <<  m_leptons_pt->EvalInstance(tau_idx) << " " << m_leptons_eta->EvalInstance(tau_idx) << " "  <<  m_taus_n_tracks->EvalInstance(tau_idx) << std::endl;
    }
    return result; 
    //(void) tau_idx;
    //return true;
}

bool OverlapRemovalAlg_leplep::jet_selection(int jet_idx) const {
    (void) jet_idx;
    return true;
}

void OverlapRemovalAlg_leplep::convertSelectionToIndex(const std::vector < bool > &selection, const std::vector < int > * proxy,  std::vector < int > &selection_idx) const {
    selection_idx.clear();
    for (size_t i=0; i<selection.size(); i++) {
      int index=i;
      if (proxy) index = proxy->at(i);
      if (selection[i]) selection_idx.push_back(index);
    }
}
  
std::vector < int > OverlapRemovalAlg_leplep::sortobbjects( const std::vector < int > &selection_idx, TTreeFormula * obs) const {
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
            if ( sorted_obs.size() == i ) { 
                newelem=true;
            }
            if (debug) std::cout << "B " << nobs << " " << selection_idx.size() << " " << saved_obs.size() << " " << sorted_obs.size() << " " << result.size() << " "  << newelem << std::endl;
            if ( (newelem || sorted_obs[i]<=saved_obs[selection_idx[j]]) && std::find(result.begin(), result.end(),selection_idx[j]) == result.end() ) {
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

void OverlapRemovalAlg_leplep::removeoverlap(const std::vector <TLorentzVector> &els, std::vector < bool > &els_selected,
        const std::vector <TLorentzVector> &mus, std::vector < bool > &mus_selected,
        const std::vector <TLorentzVector> &taus, std::vector < bool > &taus_selected,
        const std::vector <TLorentzVector> &jets, std::vector < bool > &jets_selected) const{

  // [1] (selected) electron must not overlap with selected muons
  OVR_DeltaR(mus,mus_selected,els,els_selected,0.2);                                                                                                
  // [2] taus must not overlap with any muon in the ntuple
  OVR_DeltaR_anyMu(mus,mus_selected,taus,taus_selected,0.2);                                                                                         
  // [3] taus must not overlap with medium electrons with pT > 15 GeV
  OVR_DeltaR_El(els,els_selected,taus,taus_selected,0.2);                                                                                              
  // [4] jets must not overlap with selected muons, electrons and taus
  OVR_DeltaR(mus,mus_selected,jets,jets_selected,0.2);                                                                                              
  OVR_DeltaR(els,els_selected,jets,jets_selected,0.2);                                                                                              
  OVR_DeltaR(taus,taus_selected,jets,jets_selected,0.2); 

}

void OverlapRemovalAlg_leplep::printVectors (const std::vector < TLorentzVector > &vectors, const std::vector < int > *proxy ) const {
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

void OverlapRemovalAlg_leplep::printVectors (const std::vector < int > &vectors ) const {
  int counter=0;
  for (auto v: vectors) {
    std::cout << counter << ": " << v << " | ";
    counter++;
  }
  std::cout << std::endl;
}

void OverlapRemovalAlg_leplep::printVectors (const std::vector < double > &vectors ) const {
  int counter=0;
  for (auto v: vectors) {
    std::cout << counter << ": " << v << " | ";
    counter++;
  }
  std::cout << std::endl;
}

void OverlapRemovalAlg_leplep::printVectors (const std::vector < bool > &vectors ) const {
  int counter=0;
  for (auto v: vectors) {
    std::cout << counter << ": "; 
    if (v) std::cout << "t"; else std::cout << "f";
    std::cout << " | ";
    counter++;
  }
  std::cout << std::endl;
}

int OverlapRemovalAlg_leplep::getJetIdx(int nr) {
  if (nr <0 || nr >= jets_selected_idx.size()) return -1; 
   else return jets_selected_idx[nr];
} 

int OverlapRemovalAlg_leplep::getElIdx(int nr) {
  if (nr <0 || nr >= els_selected_idx.size()) return -1; 
   else return els_selected_idx[nr];
} 

int OverlapRemovalAlg_leplep::getMuIdx(int nr) {
  if (nr <0 || nr >= mus_selected_idx.size()) return -1; 
   else return mus_selected_idx[nr];
}

int OverlapRemovalAlg_leplep::getLeptonIdx(int nr) {
  if (nr <0 || nr >= leptons_selected_idx.size()) return -1; 
   else return leptons_selected_idx[nr];
}

int OverlapRemovalAlg_leplep::getTauIdx(int nr) {
  if (nr <0 || nr >= taus_selected_idx.size()) return -1; 
   else return taus_selected_idx[nr];
}

int OverlapRemovalAlg_leplep::getNJet() {
   return jets_selected_idx.size();
} 

int OverlapRemovalAlg_leplep::getNEl() {
    return els_selected_idx.size();
} 

int OverlapRemovalAlg_leplep::getNMu() {
    return mus_selected_idx.size();
}

int OverlapRemovalAlg_leplep::getNLepton() {
    return leptons_selected_idx.size();
}

int OverlapRemovalAlg_leplep::getNTau() {
    return taus_selected_idx.size();
}

