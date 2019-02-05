
class EventClass{
    public:
        EventClass();
        ~EventClass();
        TLorentzVector getJet(int index);
        int getNJet();
        TLorentzVector getLepton(int index);
        int getNLepton();
        TLorentzVector getElectron(int index);
        int getNElectron();
        TLorentzVector getMuon(int index);
        int getNMuon();
    protected:
        std::vector < bool > jets_selected;
        std::vector < bool > els_selected;
        std::vector < bool > mus_selected;
        std::vector < bool > taus_selected;
        long event_number; 
        long run_number; 
        std::vector < int > els_idx;
        std::vector < int > mus_idx;
        std::vector < int > jets_selected_idx;
        std::vector < int > leptons_selected_idx;
        std::vector < int > els_selected_idx;
        std::vector < int > mus_selected_idx;
        std::vector < int > taus_selected_idx;
        std::vector<TLorentzVector>jets;
        std::vector<TLorentzVector>leptons;
        std::vector<TLorentzVector>els;
        std::vector<TLorentzVector>mus;
        std::vector<TLorentzVector>taus;
}
