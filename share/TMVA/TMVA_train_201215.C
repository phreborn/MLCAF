 /// to run, do: root -l TMVAClassfication fakes
 ///
 /// make sure you have post-selection ntuples in TMVA/inputNtuples
 /// currently:
 /// all MC bkg is in one file
 /// fail ISO pass ID, pass ISO fail ID, fail ISO fail ID are in three files
 /// MC signal has one file for each mass point
 /// ISO/ID bkg needs fake factors - add weight_total branch to the ntuples!
 /// to use the parameterized neural net, add signal_mass branch to all ntuples, and run signal samples without weighting
 ///
 /// scale factors are not currently in use
 ///
 /// choose your favorite MVA methods below
 
 
 #include <cstdlib>
 #include <iostream>
 #include <map>
 #include <string>
 #include <math.h>
 #include <algorithm>
 
 #include "TChain.h"
 #include "TFile.h"
 #include "TTree.h"
 #include "TString.h"
 #include "TObjString.h"
 #include "TSystem.h"
 #include "TROOT.h"
 
 #include "TMVA/Factory.h"
 #include "TMVA/DataLoader.h"
 #include "TMVA/Tools.h"
 //#include "TMVA/TMVAGui.h"

using namespace std;
 
 int TMVA_train_201215( TString myMethodList = "" )
 {
    // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
    // if you use your private .rootrc, or run from a different directory, please copy the
    // corresponding lines from .rootrc
 
    // Methods to be processed can be given as an argument; use format:
    //
    //     mylinux~> root -l TMVAClassification.CUndefined control sequence \"
 
    //---------------------------------------------------------------
    // This loads the library
    TMVA::Tools::Instance();
 
    // Default MVA methods to be trained + tested
    std::map<std::string,int> Use;
 
    // Cut optimisation
    Use["Cuts"]            = 0;
    Use["CutsD"]           = 0;
    Use["CutsPCA"]         = 0;
    Use["CutsGA"]          = 0;
    Use["CutsSA"]          = 0;
    //
    // 1-dimensional likelihood ("naive Bayes estimator")
    Use["Likelihood"]      = 0;
    Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
    Use["LikelihoodPCA"]   = 0; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
    Use["LikelihoodKDE"]   = 0;
    Use["LikelihoodMIX"]   = 0;
    //
    // Mutidimensional likelihood and Nearest-Neighbour methods
    Use["PDERS"]           = 0;
    Use["PDERSD"]          = 0;
    Use["PDERSPCA"]        = 0;
    Use["PDEFoam"]         = 0;
    Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
    Use["KNN"]             = 0; // k-nearest neighbour method
    //
    // Linear Discriminant Analysis
    Use["LD"]              = 0; // Linear Discriminant identical to Fisher
    Use["Fisher"]          = 0;
    Use["FisherG"]         = 0;
    Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
    Use["HMatrix"]         = 0;
    //
    // Function Discriminant analysis
    Use["FDA_GA"]          = 0; // minimisation of user-defined function using Genetics Algorithm
    Use["FDA_SA"]          = 0;
    Use["FDA_MC"]          = 0;
    Use["FDA_MT"]          = 0;
    Use["FDA_GAMT"]        = 0;
    Use["FDA_MCMT"]        = 0;
    //
    // Neural Networks (all are feed-forward Multilayer Perceptrons)
    Use["MLP"]             = 1; // Recommended ANN
    Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
    Use["MLPBNN"]          = 0; // Recommended ANN with BFGS training method and bayesian regulator
    Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
    Use["TMlpANN"]         = 0; // ROOT's own ANN
 #ifdef R__HAS_TMVAGPU
    Use["DNN_GPU"]         = 0; // CUDA-accelerated DNN training.
 #else
    Use["DNN_GPU"]         = 0;
 #endif
 
 #ifdef R__HAS_TMVACPU
    Use["DNN_CPU"]         = 0; // Multi-core accelerated DNN.
 #else
    Use["DNN_CPU"]         = 0;
 #endif
    //
    // Support Vector Machine
    Use["SVM"]             = 0;
    //
    // Boosted Decision Trees
    Use["BDT"]             = 0; // uses Adaptive Boost
    Use["BDTG"]            = 0; // uses Gradient Boost
    Use["BDTB"]            = 0; // uses Bagging
    Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
    Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting
    //
    // Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
    Use["RuleFit"]         = 0;
    // ---------------------------------------------------------------
 
    std::cout << std::endl;
    std::cout << "==> Start TMVAClassification" << std::endl;
 
    // Select methods (don't look at this code - not of interest)
    if (myMethodList != "") {
       for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
 
       std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
       for (UInt_t i=0; i<mlist.size(); i++) {
          std::string regMethod(mlist[i]);
 
          if (Use.find(regMethod) == Use.end()) {
             std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
             for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
             std::cout << std::endl;
             return 1;
          }
          Use[regMethod] = 1;
       }
    }
 
    // --------------------------------------------------------------------------------------------------
 
    // Here the preparation phase begins
 
    // Read training and test data
    // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
    TFile *input_Ztautau_c16a_200GeV(0);
    TFile *input_Ztautau_c16a_250GeV(0);
    TFile *input_Ztautau_c16a_300GeV(0);
    TFile *input_Ztautau_c16a_350GeV(0);
    TFile *input_Ztautau_c16a_400GeV(0);
    TFile *input_Ztautau_c16a_500GeV(0);
    TFile *input_Ztautau_c16a_600GeV(0);
    TFile *input_Ztautau_c16a_700GeV(0);
    TFile *input_Ztautau_c16a_800GeV(0);
    TFile *input_Ztautau_c16a_1200GeV(0);
    TFile *input_Ztautau_c16a_1500GeV(0);
    TFile *input_Ztautau_c16a_2000GeV(0);
    TFile *input_Ztautau_c16a_2500GeV(0);

    TFile *input_Ztautau_c16d_200GeV(0);
    TFile *input_Ztautau_c16d_250GeV(0);
    TFile *input_Ztautau_c16d_300GeV(0);
    TFile *input_Ztautau_c16d_350GeV(0);
    TFile *input_Ztautau_c16d_400GeV(0);
    TFile *input_Ztautau_c16d_500GeV(0);
    TFile *input_Ztautau_c16d_600GeV(0);
    TFile *input_Ztautau_c16d_700GeV(0);
    TFile *input_Ztautau_c16d_800GeV(0);
    TFile *input_Ztautau_c16d_1200GeV(0);
    TFile *input_Ztautau_c16d_1500GeV(0);
    TFile *input_Ztautau_c16d_2000GeV(0);
    TFile *input_Ztautau_c16d_2500GeV(0);

    TFile *input_Ztautau_c16e_200GeV(0);
    TFile *input_Ztautau_c16e_250GeV(0);
    TFile *input_Ztautau_c16e_300GeV(0);
    TFile *input_Ztautau_c16e_350GeV(0);
    TFile *input_Ztautau_c16e_400GeV(0);
    TFile *input_Ztautau_c16e_500GeV(0);
    TFile *input_Ztautau_c16e_600GeV(0);
    TFile *input_Ztautau_c16e_700GeV(0);
    TFile *input_Ztautau_c16e_800GeV(0);
    TFile *input_Ztautau_c16e_1200GeV(0);
    TFile *input_Ztautau_c16e_1500GeV(0);
    TFile *input_Ztautau_c16e_2000GeV(0);
    TFile *input_Ztautau_c16e_2500GeV(0);

    TFile *input_FakesID_c16a_200GeV(0);
    TFile *input_FakesID_c16a_250GeV(0);
    TFile *input_FakesID_c16a_300GeV(0);
    TFile *input_FakesID_c16a_350GeV(0);
    TFile *input_FakesID_c16a_400GeV(0);
    TFile *input_FakesID_c16a_500GeV(0);
    TFile *input_FakesID_c16a_600GeV(0);
    TFile *input_FakesID_c16a_700GeV(0);
    TFile *input_FakesID_c16a_800GeV(0);
    TFile *input_FakesID_c16a_1200GeV(0);
    TFile *input_FakesID_c16a_1500GeV(0);
    TFile *input_FakesID_c16a_2000GeV(0);
    TFile *input_FakesID_c16a_2500GeV(0);

    TFile *input_FakesID_c16d_200GeV(0);
    TFile *input_FakesID_c16d_250GeV(0);
    TFile *input_FakesID_c16d_300GeV(0);
    TFile *input_FakesID_c16d_350GeV(0);
    TFile *input_FakesID_c16d_400GeV(0);
    TFile *input_FakesID_c16d_500GeV(0);
    TFile *input_FakesID_c16d_600GeV(0);
    TFile *input_FakesID_c16d_700GeV(0);
    TFile *input_FakesID_c16d_800GeV(0);
    TFile *input_FakesID_c16d_1200GeV(0);
    TFile *input_FakesID_c16d_1500GeV(0);
    TFile *input_FakesID_c16d_2000GeV(0);
    TFile *input_FakesID_c16d_2500GeV(0);

    TFile *input_FakesID_c16e_200GeV(0);
    TFile *input_FakesID_c16e_250GeV(0);
    TFile *input_FakesID_c16e_300GeV(0);
    TFile *input_FakesID_c16e_350GeV(0);
    TFile *input_FakesID_c16e_400GeV(0);
    TFile *input_FakesID_c16e_500GeV(0);
    TFile *input_FakesID_c16e_600GeV(0);
    TFile *input_FakesID_c16e_700GeV(0);
    TFile *input_FakesID_c16e_800GeV(0);
    TFile *input_FakesID_c16e_1200GeV(0);
    TFile *input_FakesID_c16e_1500GeV(0);
    TFile *input_FakesID_c16e_2000GeV(0);
    TFile *input_FakesID_c16e_2500GeV(0);

    TFile *input_FakesISO_c16a_200GeV(0);
    TFile *input_FakesISO_c16a_250GeV(0);
    TFile *input_FakesISO_c16a_300GeV(0);
    TFile *input_FakesISO_c16a_350GeV(0);
    TFile *input_FakesISO_c16a_400GeV(0);
    TFile *input_FakesISO_c16a_500GeV(0);
    TFile *input_FakesISO_c16a_600GeV(0);
    TFile *input_FakesISO_c16a_700GeV(0);
    TFile *input_FakesISO_c16a_800GeV(0);
    TFile *input_FakesISO_c16a_1200GeV(0);
    TFile *input_FakesISO_c16a_1500GeV(0);
    TFile *input_FakesISO_c16a_2000GeV(0);
    TFile *input_FakesISO_c16a_2500GeV(0);

    TFile *input_FakesISO_c16d_200GeV(0);
    TFile *input_FakesISO_c16d_250GeV(0);
    TFile *input_FakesISO_c16d_300GeV(0);
    TFile *input_FakesISO_c16d_350GeV(0);
    TFile *input_FakesISO_c16d_400GeV(0);
    TFile *input_FakesISO_c16d_500GeV(0);
    TFile *input_FakesISO_c16d_600GeV(0);
    TFile *input_FakesISO_c16d_700GeV(0);
    TFile *input_FakesISO_c16d_800GeV(0);
    TFile *input_FakesISO_c16d_1200GeV(0);
    TFile *input_FakesISO_c16d_1500GeV(0);
    TFile *input_FakesISO_c16d_2000GeV(0);
    TFile *input_FakesISO_c16d_2500GeV(0);

    TFile *input_FakesISO_c16e_200GeV(0);
    TFile *input_FakesISO_c16e_250GeV(0);
    TFile *input_FakesISO_c16e_300GeV(0);
    TFile *input_FakesISO_c16e_350GeV(0);
    TFile *input_FakesISO_c16e_400GeV(0);
    TFile *input_FakesISO_c16e_500GeV(0);
    TFile *input_FakesISO_c16e_600GeV(0);
    TFile *input_FakesISO_c16e_700GeV(0);
    TFile *input_FakesISO_c16e_800GeV(0);
    TFile *input_FakesISO_c16e_1200GeV(0);
    TFile *input_FakesISO_c16e_1500GeV(0);
    TFile *input_FakesISO_c16e_2000GeV(0);
    TFile *input_FakesISO_c16e_2500GeV(0);

    TFile *input_Zll_c16a_200GeV(0);
    TFile *input_Zll_c16a_250GeV(0);
    TFile *input_Zll_c16a_300GeV(0);
    TFile *input_Zll_c16a_350GeV(0);
    TFile *input_Zll_c16a_400GeV(0);
    TFile *input_Zll_c16a_500GeV(0);
    TFile *input_Zll_c16a_600GeV(0);
    TFile *input_Zll_c16a_700GeV(0);
    TFile *input_Zll_c16a_800GeV(0);
    TFile *input_Zll_c16a_1200GeV(0);
    TFile *input_Zll_c16a_1500GeV(0);
    TFile *input_Zll_c16a_2000GeV(0);
    TFile *input_Zll_c16a_2500GeV(0);

    TFile *input_Zll_c16d_200GeV(0);
    TFile *input_Zll_c16d_250GeV(0);
    TFile *input_Zll_c16d_300GeV(0);
    TFile *input_Zll_c16d_350GeV(0);
    TFile *input_Zll_c16d_400GeV(0);
    TFile *input_Zll_c16d_500GeV(0);
    TFile *input_Zll_c16d_600GeV(0);
    TFile *input_Zll_c16d_700GeV(0);
    TFile *input_Zll_c16d_800GeV(0);
    TFile *input_Zll_c16d_1200GeV(0);
    TFile *input_Zll_c16d_1500GeV(0);
    TFile *input_Zll_c16d_2000GeV(0);
    TFile *input_Zll_c16d_2500GeV(0);

    TFile *input_Zll_c16e_200GeV(0);
    TFile *input_Zll_c16e_250GeV(0);
    TFile *input_Zll_c16e_300GeV(0);
    TFile *input_Zll_c16e_350GeV(0);
    TFile *input_Zll_c16e_400GeV(0);
    TFile *input_Zll_c16e_500GeV(0);
    TFile *input_Zll_c16e_600GeV(0);
    TFile *input_Zll_c16e_700GeV(0);
    TFile *input_Zll_c16e_800GeV(0);
    TFile *input_Zll_c16e_1200GeV(0);
    TFile *input_Zll_c16e_1500GeV(0);
    TFile *input_Zll_c16e_2000GeV(0);
    TFile *input_Zll_c16e_2500GeV(0);

    //btag
    TFile *input_top_single_btag_c16a_200GeV(0);
    TFile *input_top_single_btag_c16a_250GeV(0);
    TFile *input_top_single_btag_c16a_300GeV(0);
    TFile *input_top_single_btag_c16a_350GeV(0);
    TFile *input_top_single_btag_c16a_400GeV(0);
    TFile *input_top_single_btag_c16a_500GeV(0);
    TFile *input_top_single_btag_c16a_600GeV(0);
    TFile *input_top_single_btag_c16a_700GeV(0);
    TFile *input_top_single_btag_c16a_800GeV(0);
    TFile *input_top_single_btag_c16a_1200GeV(0);
    TFile *input_top_single_btag_c16a_1500GeV(0);
    TFile *input_top_single_btag_c16a_2000GeV(0);
    TFile *input_top_single_btag_c16a_2500GeV(0);

    TFile *input_top_single_btag_c16d_200GeV(0);
    TFile *input_top_single_btag_c16d_250GeV(0);
    TFile *input_top_single_btag_c16d_300GeV(0);
    TFile *input_top_single_btag_c16d_350GeV(0);
    TFile *input_top_single_btag_c16d_400GeV(0);
    TFile *input_top_single_btag_c16d_500GeV(0);
    TFile *input_top_single_btag_c16d_600GeV(0);
    TFile *input_top_single_btag_c16d_700GeV(0);
    TFile *input_top_single_btag_c16d_800GeV(0);
    TFile *input_top_single_btag_c16d_1200GeV(0);
    TFile *input_top_single_btag_c16d_1500GeV(0);
    TFile *input_top_single_btag_c16d_2000GeV(0);
    TFile *input_top_single_btag_c16d_2500GeV(0);

    TFile *input_top_single_btag_c16e_200GeV(0);
    TFile *input_top_single_btag_c16e_250GeV(0);
    TFile *input_top_single_btag_c16e_300GeV(0);
    TFile *input_top_single_btag_c16e_350GeV(0);
    TFile *input_top_single_btag_c16e_400GeV(0);
    TFile *input_top_single_btag_c16e_500GeV(0);
    TFile *input_top_single_btag_c16e_600GeV(0);
    TFile *input_top_single_btag_c16e_700GeV(0);
    TFile *input_top_single_btag_c16e_800GeV(0);
    TFile *input_top_single_btag_c16e_1200GeV(0);
    TFile *input_top_single_btag_c16e_1500GeV(0);
    TFile *input_top_single_btag_c16e_2000GeV(0);
    TFile *input_top_single_btag_c16e_2500GeV(0);

    TFile *input_top_ttbar_btag_c16a_200GeV(0);
    TFile *input_top_ttbar_btag_c16a_250GeV(0);
    TFile *input_top_ttbar_btag_c16a_300GeV(0);
    TFile *input_top_ttbar_btag_c16a_350GeV(0);
    TFile *input_top_ttbar_btag_c16a_400GeV(0);
    TFile *input_top_ttbar_btag_c16a_500GeV(0);
    TFile *input_top_ttbar_btag_c16a_600GeV(0);
    TFile *input_top_ttbar_btag_c16a_700GeV(0);
    TFile *input_top_ttbar_btag_c16a_800GeV(0);
    TFile *input_top_ttbar_btag_c16a_1200GeV(0);
    TFile *input_top_ttbar_btag_c16a_1500GeV(0);
    TFile *input_top_ttbar_btag_c16a_2000GeV(0);
    TFile *input_top_ttbar_btag_c16a_2500GeV(0);

    TFile *input_top_ttbar_btag_c16d_200GeV(0);
    TFile *input_top_ttbar_btag_c16d_250GeV(0);
    TFile *input_top_ttbar_btag_c16d_300GeV(0);
    TFile *input_top_ttbar_btag_c16d_350GeV(0);
    TFile *input_top_ttbar_btag_c16d_400GeV(0);
    TFile *input_top_ttbar_btag_c16d_500GeV(0);
    TFile *input_top_ttbar_btag_c16d_600GeV(0);
    TFile *input_top_ttbar_btag_c16d_700GeV(0);
    TFile *input_top_ttbar_btag_c16d_800GeV(0);
    TFile *input_top_ttbar_btag_c16d_1200GeV(0);
    TFile *input_top_ttbar_btag_c16d_1500GeV(0);
    TFile *input_top_ttbar_btag_c16d_2000GeV(0);
    TFile *input_top_ttbar_btag_c16d_2500GeV(0);

    TFile *input_top_ttbar_btag_c16e_200GeV(0);
    TFile *input_top_ttbar_btag_c16e_250GeV(0);
    TFile *input_top_ttbar_btag_c16e_300GeV(0);
    TFile *input_top_ttbar_btag_c16e_350GeV(0);
    TFile *input_top_ttbar_btag_c16e_400GeV(0);
    TFile *input_top_ttbar_btag_c16e_500GeV(0);
    TFile *input_top_ttbar_btag_c16e_600GeV(0);
    TFile *input_top_ttbar_btag_c16e_700GeV(0);
    TFile *input_top_ttbar_btag_c16e_800GeV(0);
    TFile *input_top_ttbar_btag_c16e_1200GeV(0);
    TFile *input_top_ttbar_btag_c16e_1500GeV(0);
    TFile *input_top_ttbar_btag_c16e_2000GeV(0);
    TFile *input_top_ttbar_btag_c16e_2500GeV(0);

    TFile *input_Ztautau_btag_c16a_200GeV(0);
    TFile *input_Ztautau_btag_c16a_250GeV(0);
    TFile *input_Ztautau_btag_c16a_300GeV(0);
    TFile *input_Ztautau_btag_c16a_350GeV(0);
    TFile *input_Ztautau_btag_c16a_400GeV(0);
    TFile *input_Ztautau_btag_c16a_500GeV(0);
    TFile *input_Ztautau_btag_c16a_600GeV(0);
    TFile *input_Ztautau_btag_c16a_700GeV(0);
    TFile *input_Ztautau_btag_c16a_800GeV(0);
    TFile *input_Ztautau_btag_c16a_1200GeV(0);
    TFile *input_Ztautau_btag_c16a_1500GeV(0);
    TFile *input_Ztautau_btag_c16a_2000GeV(0);
    TFile *input_Ztautau_btag_c16a_2500GeV(0);

    TFile *input_Ztautau_btag_c16d_200GeV(0);
    TFile *input_Ztautau_btag_c16d_250GeV(0);
    TFile *input_Ztautau_btag_c16d_300GeV(0);
    TFile *input_Ztautau_btag_c16d_350GeV(0);
    TFile *input_Ztautau_btag_c16d_400GeV(0);
    TFile *input_Ztautau_btag_c16d_500GeV(0);
    TFile *input_Ztautau_btag_c16d_600GeV(0);
    TFile *input_Ztautau_btag_c16d_700GeV(0);
    TFile *input_Ztautau_btag_c16d_800GeV(0);
    TFile *input_Ztautau_btag_c16d_1200GeV(0);
    TFile *input_Ztautau_btag_c16d_1500GeV(0);
    TFile *input_Ztautau_btag_c16d_2000GeV(0);
    TFile *input_Ztautau_btag_c16d_2500GeV(0);

    TFile *input_Ztautau_btag_c16e_200GeV(0);
    TFile *input_Ztautau_btag_c16e_250GeV(0);
    TFile *input_Ztautau_btag_c16e_300GeV(0);
    TFile *input_Ztautau_btag_c16e_350GeV(0);
    TFile *input_Ztautau_btag_c16e_400GeV(0);
    TFile *input_Ztautau_btag_c16e_500GeV(0);
    TFile *input_Ztautau_btag_c16e_600GeV(0);
    TFile *input_Ztautau_btag_c16e_700GeV(0);
    TFile *input_Ztautau_btag_c16e_800GeV(0);
    TFile *input_Ztautau_btag_c16e_1200GeV(0);
    TFile *input_Ztautau_btag_c16e_1500GeV(0);
    TFile *input_Ztautau_btag_c16e_2000GeV(0);
    TFile *input_Ztautau_btag_c16e_2500GeV(0);

    TFile *input_FakesID_btag_c16a_200GeV(0);
    TFile *input_FakesID_btag_c16a_250GeV(0);
    TFile *input_FakesID_btag_c16a_300GeV(0);
    TFile *input_FakesID_btag_c16a_350GeV(0);
    TFile *input_FakesID_btag_c16a_400GeV(0);
    TFile *input_FakesID_btag_c16a_500GeV(0);
    TFile *input_FakesID_btag_c16a_600GeV(0);
    TFile *input_FakesID_btag_c16a_700GeV(0);
    TFile *input_FakesID_btag_c16a_800GeV(0);
    TFile *input_FakesID_btag_c16a_1200GeV(0);
    TFile *input_FakesID_btag_c16a_1500GeV(0);
    TFile *input_FakesID_btag_c16a_2000GeV(0);
    TFile *input_FakesID_btag_c16a_2500GeV(0);

    TFile *input_FakesID_btag_c16d_200GeV(0);
    TFile *input_FakesID_btag_c16d_250GeV(0);
    TFile *input_FakesID_btag_c16d_300GeV(0);
    TFile *input_FakesID_btag_c16d_350GeV(0);
    TFile *input_FakesID_btag_c16d_400GeV(0);
    TFile *input_FakesID_btag_c16d_500GeV(0);
    TFile *input_FakesID_btag_c16d_600GeV(0);
    TFile *input_FakesID_btag_c16d_700GeV(0);
    TFile *input_FakesID_btag_c16d_800GeV(0);
    TFile *input_FakesID_btag_c16d_1200GeV(0);
    TFile *input_FakesID_btag_c16d_1500GeV(0);
    TFile *input_FakesID_btag_c16d_2000GeV(0);
    TFile *input_FakesID_btag_c16d_2500GeV(0);

    TFile *input_FakesID_btag_c16e_200GeV(0);
    TFile *input_FakesID_btag_c16e_250GeV(0);
    TFile *input_FakesID_btag_c16e_300GeV(0);
    TFile *input_FakesID_btag_c16e_350GeV(0);
    TFile *input_FakesID_btag_c16e_400GeV(0);
    TFile *input_FakesID_btag_c16e_500GeV(0);
    TFile *input_FakesID_btag_c16e_600GeV(0);
    TFile *input_FakesID_btag_c16e_700GeV(0);
    TFile *input_FakesID_btag_c16e_800GeV(0);
    TFile *input_FakesID_btag_c16e_1200GeV(0);
    TFile *input_FakesID_btag_c16e_1500GeV(0);
    TFile *input_FakesID_btag_c16e_2000GeV(0);
    TFile *input_FakesID_btag_c16e_2500GeV(0);

    TFile *input_FakesISO_btag_c16a_200GeV(0);
    TFile *input_FakesISO_btag_c16a_250GeV(0);
    TFile *input_FakesISO_btag_c16a_300GeV(0);
    TFile *input_FakesISO_btag_c16a_350GeV(0);
    TFile *input_FakesISO_btag_c16a_400GeV(0);
    TFile *input_FakesISO_btag_c16a_500GeV(0);
    TFile *input_FakesISO_btag_c16a_600GeV(0);
    TFile *input_FakesISO_btag_c16a_700GeV(0);
    TFile *input_FakesISO_btag_c16a_800GeV(0);
    TFile *input_FakesISO_btag_c16a_1200GeV(0);
    TFile *input_FakesISO_btag_c16a_1500GeV(0);
    TFile *input_FakesISO_btag_c16a_2000GeV(0);
    TFile *input_FakesISO_btag_c16a_2500GeV(0);

    TFile *input_FakesISO_btag_c16d_200GeV(0);
    TFile *input_FakesISO_btag_c16d_250GeV(0);
    TFile *input_FakesISO_btag_c16d_300GeV(0);
    TFile *input_FakesISO_btag_c16d_350GeV(0);
    TFile *input_FakesISO_btag_c16d_400GeV(0);
    TFile *input_FakesISO_btag_c16d_500GeV(0);
    TFile *input_FakesISO_btag_c16d_600GeV(0);
    TFile *input_FakesISO_btag_c16d_700GeV(0);
    TFile *input_FakesISO_btag_c16d_800GeV(0);
    TFile *input_FakesISO_btag_c16d_1200GeV(0);
    TFile *input_FakesISO_btag_c16d_1500GeV(0);
    TFile *input_FakesISO_btag_c16d_2000GeV(0);
    TFile *input_FakesISO_btag_c16d_2500GeV(0);

    TFile *input_FakesISO_btag_c16e_200GeV(0);
    TFile *input_FakesISO_btag_c16e_250GeV(0);
    TFile *input_FakesISO_btag_c16e_300GeV(0);
    TFile *input_FakesISO_btag_c16e_350GeV(0);
    TFile *input_FakesISO_btag_c16e_400GeV(0);
    TFile *input_FakesISO_btag_c16e_500GeV(0);
    TFile *input_FakesISO_btag_c16e_600GeV(0);
    TFile *input_FakesISO_btag_c16e_700GeV(0);
    TFile *input_FakesISO_btag_c16e_800GeV(0);
    TFile *input_FakesISO_btag_c16e_1200GeV(0);
    TFile *input_FakesISO_btag_c16e_1500GeV(0);
    TFile *input_FakesISO_btag_c16e_2000GeV(0);
    TFile *input_FakesISO_btag_c16e_2500GeV(0);



    //signal, bveto
    TFile *input_ggH_c16a_200GeV(0);
    TFile *input_ggH_c16a_250GeV(0);
    TFile *input_ggH_c16a_300GeV(0);
    TFile *input_ggH_c16a_350GeV(0);
    TFile *input_ggH_c16a_400GeV(0);
    TFile *input_ggH_c16a_500GeV(0);
    TFile *input_ggH_c16a_600GeV(0);
    TFile *input_ggH_c16a_700GeV(0);
    TFile *input_ggH_c16a_800GeV(0);
    TFile *input_ggH_c16a_1200GeV(0);
    TFile *input_ggH_c16a_1500GeV(0);
    TFile *input_ggH_c16a_2000GeV(0);
    TFile *input_ggH_c16a_2500GeV(0);

    TFile *input_ggH_c16d_200GeV(0);
    TFile *input_ggH_c16d_250GeV(0);
    TFile *input_ggH_c16d_300GeV(0);
    TFile *input_ggH_c16d_350GeV(0);
    TFile *input_ggH_c16d_400GeV(0);
    TFile *input_ggH_c16d_500GeV(0);
    TFile *input_ggH_c16d_600GeV(0);
    TFile *input_ggH_c16d_700GeV(0);
    TFile *input_ggH_c16d_800GeV(0);
    TFile *input_ggH_c16d_1200GeV(0);
    TFile *input_ggH_c16d_1500GeV(0);
    TFile *input_ggH_c16d_2000GeV(0);
    TFile *input_ggH_c16d_2500GeV(0);

    TFile *input_ggH_c16e_200GeV(0);
    TFile *input_ggH_c16e_250GeV(0);
    TFile *input_ggH_c16e_300GeV(0);
    TFile *input_ggH_c16e_350GeV(0);
    TFile *input_ggH_c16e_400GeV(0);
    TFile *input_ggH_c16e_500GeV(0);
    TFile *input_ggH_c16e_600GeV(0);
    TFile *input_ggH_c16e_700GeV(0);
    TFile *input_ggH_c16e_800GeV(0);
    TFile *input_ggH_c16e_1200GeV(0);
    TFile *input_ggH_c16e_1500GeV(0);
    TFile *input_ggH_c16e_2000GeV(0);
    TFile *input_ggH_c16e_2500GeV(0);


    TFile *input_bbH_c16a_200GeV(0);
    TFile *input_bbH_c16a_250GeV(0);
    TFile *input_bbH_c16a_300GeV(0);
    TFile *input_bbH_c16a_350GeV(0);
    TFile *input_bbH_c16a_400GeV(0);
    TFile *input_bbH_c16a_500GeV(0);
    TFile *input_bbH_c16a_600GeV(0);
    TFile *input_bbH_c16a_700GeV(0);
    TFile *input_bbH_c16a_800GeV(0);
    TFile *input_bbH_c16a_1200GeV(0);
    TFile *input_bbH_c16a_1500GeV(0);
    TFile *input_bbH_c16a_2000GeV(0);
    TFile *input_bbH_c16a_2500GeV(0);

    TFile *input_bbH_c16d_200GeV(0);
    TFile *input_bbH_c16d_250GeV(0);
    TFile *input_bbH_c16d_300GeV(0);
    TFile *input_bbH_c16d_350GeV(0);
    TFile *input_bbH_c16d_400GeV(0);
    TFile *input_bbH_c16d_500GeV(0);
    TFile *input_bbH_c16d_600GeV(0);
    TFile *input_bbH_c16d_700GeV(0);
    TFile *input_bbH_c16d_800GeV(0);
    TFile *input_bbH_c16d_1200GeV(0);
    TFile *input_bbH_c16d_1500GeV(0);
    TFile *input_bbH_c16d_2000GeV(0);
    TFile *input_bbH_c16d_2500GeV(0);

    TFile *input_bbH_c16e_200GeV(0);
    TFile *input_bbH_c16e_250GeV(0);
    TFile *input_bbH_c16e_300GeV(0);
    TFile *input_bbH_c16e_350GeV(0);
    TFile *input_bbH_c16e_400GeV(0);
    TFile *input_bbH_c16e_500GeV(0);
    TFile *input_bbH_c16e_600GeV(0);
    TFile *input_bbH_c16e_700GeV(0);
    TFile *input_bbH_c16e_800GeV(0);
    TFile *input_bbH_c16e_1200GeV(0);
    TFile *input_bbH_c16e_1500GeV(0);
    TFile *input_bbH_c16e_2000GeV(0);
    TFile *input_bbH_c16e_2500GeV(0);



    //signal, btag
    TFile *input_ggH_btag_c16a_200GeV(0);
    TFile *input_ggH_btag_c16a_250GeV(0);
    TFile *input_ggH_btag_c16a_300GeV(0);
    TFile *input_ggH_btag_c16a_350GeV(0);
    TFile *input_ggH_btag_c16a_400GeV(0);
    TFile *input_ggH_btag_c16a_500GeV(0);
    TFile *input_ggH_btag_c16a_600GeV(0);
    TFile *input_ggH_btag_c16a_700GeV(0);
    TFile *input_ggH_btag_c16a_800GeV(0);
    TFile *input_ggH_btag_c16a_1200GeV(0);
    TFile *input_ggH_btag_c16a_1500GeV(0);
    TFile *input_ggH_btag_c16a_2000GeV(0);
    TFile *input_ggH_btag_c16a_2500GeV(0);

    TFile *input_ggH_btag_c16d_200GeV(0);
    TFile *input_ggH_btag_c16d_250GeV(0);
    TFile *input_ggH_btag_c16d_300GeV(0);
    TFile *input_ggH_btag_c16d_350GeV(0);
    TFile *input_ggH_btag_c16d_400GeV(0);
    TFile *input_ggH_btag_c16d_500GeV(0);
    TFile *input_ggH_btag_c16d_600GeV(0);
    TFile *input_ggH_btag_c16d_700GeV(0);
    TFile *input_ggH_btag_c16d_800GeV(0);
    TFile *input_ggH_btag_c16d_1200GeV(0);
    TFile *input_ggH_btag_c16d_1500GeV(0);
    TFile *input_ggH_btag_c16d_2000GeV(0);
    TFile *input_ggH_btag_c16d_2500GeV(0);

    TFile *input_ggH_btag_c16e_200GeV(0);
    TFile *input_ggH_btag_c16e_250GeV(0);
    TFile *input_ggH_btag_c16e_300GeV(0);
    TFile *input_ggH_btag_c16e_350GeV(0);
    TFile *input_ggH_btag_c16e_400GeV(0);
    TFile *input_ggH_btag_c16e_500GeV(0);
    TFile *input_ggH_btag_c16e_600GeV(0);
    TFile *input_ggH_btag_c16e_700GeV(0);
    TFile *input_ggH_btag_c16e_800GeV(0);
    TFile *input_ggH_btag_c16e_1200GeV(0);
    TFile *input_ggH_btag_c16e_1500GeV(0);
    TFile *input_ggH_btag_c16e_2000GeV(0);
    TFile *input_ggH_btag_c16e_2500GeV(0);


    TFile *input_bbH_btag_c16a_200GeV(0);
    TFile *input_bbH_btag_c16a_250GeV(0);
    TFile *input_bbH_btag_c16a_300GeV(0);
    TFile *input_bbH_btag_c16a_350GeV(0);
    TFile *input_bbH_btag_c16a_400GeV(0);
    TFile *input_bbH_btag_c16a_500GeV(0);
    TFile *input_bbH_btag_c16a_600GeV(0);
    TFile *input_bbH_btag_c16a_700GeV(0);
    TFile *input_bbH_btag_c16a_800GeV(0);
    TFile *input_bbH_btag_c16a_1200GeV(0);
    TFile *input_bbH_btag_c16a_1500GeV(0);
    TFile *input_bbH_btag_c16a_2000GeV(0);
    TFile *input_bbH_btag_c16a_2500GeV(0);

    TFile *input_bbH_btag_c16d_200GeV(0);
    TFile *input_bbH_btag_c16d_250GeV(0);
    TFile *input_bbH_btag_c16d_300GeV(0);
    TFile *input_bbH_btag_c16d_350GeV(0);
    TFile *input_bbH_btag_c16d_400GeV(0);
    TFile *input_bbH_btag_c16d_500GeV(0);
    TFile *input_bbH_btag_c16d_600GeV(0);
    TFile *input_bbH_btag_c16d_700GeV(0);
    TFile *input_bbH_btag_c16d_800GeV(0);
    TFile *input_bbH_btag_c16d_1200GeV(0);
    TFile *input_bbH_btag_c16d_1500GeV(0);
    TFile *input_bbH_btag_c16d_2000GeV(0);
    TFile *input_bbH_btag_c16d_2500GeV(0);

    TFile *input_bbH_btag_c16e_200GeV(0);
    TFile *input_bbH_btag_c16e_250GeV(0);
    TFile *input_bbH_btag_c16e_300GeV(0);
    TFile *input_bbH_btag_c16e_350GeV(0);
    TFile *input_bbH_btag_c16e_400GeV(0);
    TFile *input_bbH_btag_c16e_500GeV(0);
    TFile *input_bbH_btag_c16e_600GeV(0);
    TFile *input_bbH_btag_c16e_700GeV(0);
    TFile *input_bbH_btag_c16e_800GeV(0);
    TFile *input_bbH_btag_c16e_1200GeV(0);
    TFile *input_bbH_btag_c16e_1500GeV(0);
    TFile *input_bbH_btag_c16e_2000GeV(0);
    TFile *input_bbH_btag_c16e_2500GeV(0);





    //TString fname = "./tmva_class_example.root";
    //TString fname = "../bveto_Ztautau_bkg.root";

	//Ztautau bveto
    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_200_bveto.root" )) {
       input_Ztautau_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_200GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_200_bveto.root" )) {
       input_Ztautau_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_200GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_200_bveto.root" )) {
       input_Ztautau_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_200GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_250_bveto.root" )) {
       input_Ztautau_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_250_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_250GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_250_bveto.root" )) {
       input_Ztautau_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_250_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_250GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_250_bveto.root" )) {
       input_Ztautau_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_250_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_250GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_300_bveto.root" )) {
       input_Ztautau_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_300_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_300GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_300_bveto.root" )) {
       input_Ztautau_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_300_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_300GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_300_bveto.root" )) {
       input_Ztautau_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_300_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_300GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_350_bveto.root" )) {
       input_Ztautau_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_350_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_350GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_350_bveto.root" )) {
       input_Ztautau_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_350_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_350GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_350_bveto.root" )) {
       input_Ztautau_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_350_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_350GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_400_bveto.root" )) {
       input_Ztautau_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_400_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_400GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_400_bveto.root" )) {
       input_Ztautau_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_400_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_400GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_400_bveto.root" )) {
       input_Ztautau_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_400_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_400GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_500_bveto.root" )) {
       input_Ztautau_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_500_bveto.root" )) {
       input_Ztautau_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_500_bveto.root" )) {
       input_Ztautau_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_600_bveto.root" )) {
       input_Ztautau_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_600_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_600GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_600_bveto.root" )) {
       input_Ztautau_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_600_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_600GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_600_bveto.root" )) {
       input_Ztautau_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_600_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_600GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_700_bveto.root" )) {
       input_Ztautau_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_700_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_700GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_700_bveto.root" )) {
       input_Ztautau_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_700_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_700GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_700_bveto.root" )) {
       input_Ztautau_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_700_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_700GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_800_bveto.root" )) {
       input_Ztautau_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_800_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_800GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_800_bveto.root" )) {
       input_Ztautau_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_800_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_800GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_800_bveto.root" )) {
       input_Ztautau_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_800_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_800GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_1200_bveto.root" )) {
       input_Ztautau_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_1200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_1200GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_1200_bveto.root" )) {
       input_Ztautau_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_1200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_1200GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_1200_bveto.root" )) {
       input_Ztautau_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_1200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_1200GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_1500_bveto.root" )) {
       input_Ztautau_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_1500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_1500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_1500_bveto.root" )) {
       input_Ztautau_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_1500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_1500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_1500_bveto.root" )) {
       input_Ztautau_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_1500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_1500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_2000_bveto.root" )) {
       input_Ztautau_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_2000_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_2000GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_2000_bveto.root" )) {
       input_Ztautau_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_2000_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_2000GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_2000_bveto.root" )) {
       input_Ztautau_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_2000_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_2000GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_2500_bveto.root" )) {
       input_Ztautau_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_2500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16a_2500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_2500_bveto.root" )) {
       input_Ztautau_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_2500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16d_2500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_2500_bveto.root" )) {
       input_Ztautau_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_2500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_c16e_2500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }



	//Ztautau btag

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_200_btag.root" )) {
       input_Ztautau_btag_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_200GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_200_btag.root" )) {
       input_Ztautau_btag_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_200GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_200_btag.root" )) {
       input_Ztautau_btag_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_200GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_250_btag.root" )) {
       input_Ztautau_btag_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_250GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_250_btag.root" )) {
       input_Ztautau_btag_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_250GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_250_btag.root" )) {
       input_Ztautau_btag_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_250GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_300_btag.root" )) {
       input_Ztautau_btag_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_300GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_300_btag.root" )) {
       input_Ztautau_btag_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_300GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_300_btag.root" )) {
       input_Ztautau_btag_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_300GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_350_btag.root" )) {
       input_Ztautau_btag_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_350GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_350_btag.root" )) {
       input_Ztautau_btag_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_350GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_350_btag.root" )) {
       input_Ztautau_btag_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_350GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_400_btag.root" )) {
       input_Ztautau_btag_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_400GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_400_btag.root" )) {
       input_Ztautau_btag_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_400GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_400_btag.root" )) {
       input_Ztautau_btag_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_400GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_500_btag.root" )) {
       input_Ztautau_btag_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_500_btag.root" )) {
       input_Ztautau_btag_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_500_btag.root" )) {
       input_Ztautau_btag_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_600_btag.root" )) {
       input_Ztautau_btag_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_600GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_600_btag.root" )) {
       input_Ztautau_btag_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_600GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_600_btag.root" )) {
       input_Ztautau_btag_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_600GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_700_btag.root" )) {
       input_Ztautau_btag_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_700GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_700_btag.root" )) {
       input_Ztautau_btag_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_700GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_700_btag.root" )) {
       input_Ztautau_btag_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_700GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_800_btag.root" )) {
       input_Ztautau_btag_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_800GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_800_btag.root" )) {
       input_Ztautau_btag_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_800GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_800_btag.root" )) {
       input_Ztautau_btag_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_800GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_1200_btag.root" )) {
       input_Ztautau_btag_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_1200GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_1200_btag.root" )) {
       input_Ztautau_btag_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_1200GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_1200_btag.root" )) {
       input_Ztautau_btag_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_1200GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_1500_btag.root" )) {
       input_Ztautau_btag_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_1500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_1500_btag.root" )) {
       input_Ztautau_btag_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_1500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_1500_btag.root" )) {
       input_Ztautau_btag_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_1500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_2000_btag.root" )) {
       input_Ztautau_btag_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_2000GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_2000_btag.root" )) {
       input_Ztautau_btag_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_2000GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_2000_btag.root" )) {
       input_Ztautau_btag_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_2000GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_2500_btag.root" )) {
       input_Ztautau_btag_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16a_2500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_2500_btag.root" )) {
       input_Ztautau_btag_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16d_2500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_2500_btag.root" )) {
       input_Ztautau_btag_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_Ztautau_btag_c16e_2500GeV) {
       std::cout << "ERROR: could not open Ztautau data file" << std::endl;
       exit(1);
    }



	//Zll bveto

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_200_bveto.root" )) {
       input_Zll_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_200GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_200_bveto.root" )) {
       input_Zll_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_200GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_200_bveto.root" )) {
       input_Zll_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_200GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_250_bveto.root" )) {
       input_Zll_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_250_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_250GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_250_bveto.root" )) {
       input_Zll_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_250_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_250GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_250_bveto.root" )) {
       input_Zll_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_250_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_250GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_300_bveto.root" )) {
       input_Zll_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_300_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_300GeV) {
       std::cout << "ERROR: could not open top_Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_300_bveto.root" )) {
       input_Zll_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_300_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_300GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_300_bveto.root" )) {
       input_Zll_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_300_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_300GeV) {
       std::cout << "ERROR: could not open ZLl data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_350_bveto.root" )) {
       input_Zll_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_350_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_350GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_350_bveto.root" )) {
       input_Zll_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_350_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_350GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_350_bveto.root" )) {
       input_Zll_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_350_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_350GeV) {
       std::cout << "ERROR: could not open zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_400_bveto.root" )) {
       input_Zll_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_400_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_400GeV) {
       std::cout << "ERROR: could not open zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_400_bveto.root" )) {
       input_Zll_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_400_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_400GeV) {
       std::cout << "ERROR: could not open zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_400_bveto.root" )) {
       input_Zll_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_400_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_400GeV) {
       std::cout << "ERROR: could not open zll data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_500_bveto.root" )) {
       input_Zll_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_500GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_500_bveto.root" )) {
       input_Zll_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_500GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_500_bveto.root" )) {
       input_Zll_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_500GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_600_bveto.root" )) {
       input_Zll_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_600_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_600GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_600_bveto.root" )) {
       input_Zll_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_600_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_600GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_600_bveto.root" )) {
       input_Zll_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_600_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_600GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_700_bveto.root" )) {
       input_Zll_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_700_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_700GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_700_bveto.root" )) {
       input_Zll_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_700_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_700GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_700_bveto.root" )) {
       input_Zll_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_700_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_700GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_800_bveto.root" )) {
       input_Zll_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_800_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_800GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_800_bveto.root" )) {
       input_Zll_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_800_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_800GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_800_bveto.root" )) {
       input_Zll_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_800_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_800GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_1200_bveto.root" )) {
       input_Zll_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_1200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_1200GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_1200_bveto.root" )) {
       input_Zll_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_1200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_1200GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_1200_bveto.root" )) {
       input_Zll_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_1200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_1200GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_1500_bveto.root" )) {
       input_Zll_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_1500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_1500GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_1500_bveto.root" )) {
       input_Zll_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_1500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_1500GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_1500_bveto.root" )) {
       input_Zll_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_1500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_1500GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_2000_bveto.root" )) {
       input_Zll_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_2000_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_2000GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_2000_bveto.root" )) {
       input_Zll_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_2000_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_2000GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_2000_bveto.root" )) {
       input_Zll_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_2000_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_2000GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_2500_bveto.root" )) {
       input_Zll_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Zll_2500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16a_2500GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_2500_bveto.root" )) {
       input_Zll_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Zll_2500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16d_2500GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_2500_bveto.root" )) {
       input_Zll_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Zll_2500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_Zll_c16e_2500GeV) {
       std::cout << "ERROR: could not open Zll data file" << std::endl;
       exit(1);
    }






	//Fakes ID bveto

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_200_bveto.root" )) {
       input_FakesID_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_200GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_200_bveto.root" )) {
       input_FakesID_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_200GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_200_bveto.root" )) {
       input_FakesID_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_200GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_250_bveto.root" )) {
       input_FakesID_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_250_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_250GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_250_bveto.root" )) {
       input_FakesID_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_250_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_250GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_250_bveto.root" )) {
       input_FakesID_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_250_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_250GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_300_bveto.root" )) {
       input_FakesID_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_300_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_300GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_300_bveto.root" )) {
       input_FakesID_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_300_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_300GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_300_bveto.root" )) {
       input_FakesID_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_300_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_300GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_350_bveto.root" )) {
       input_FakesID_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_350_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_350GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_350_bveto.root" )) {
       input_FakesID_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_350_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_350GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_350_bveto.root" )) {
       input_FakesID_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_350_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_350GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_400_bveto.root" )) {
       input_FakesID_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_400_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_400GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_400_bveto.root" )) {
       input_FakesID_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_400_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_400GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_400_bveto.root" )) {
       input_FakesID_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_400_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_400GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_500_bveto.root" )) {
       input_FakesID_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_500_bveto.root" )) {
       input_FakesID_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_500_bveto.root" )) {
       input_FakesID_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_600_bveto.root" )) {
       input_FakesID_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_600_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_600GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_600_bveto.root" )) {
       input_FakesID_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_600_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_600GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_600_bveto.root" )) {
       input_FakesID_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_600_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_600GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_700_bveto.root" )) {
       input_FakesID_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_700_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_700GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_700_bveto.root" )) {
       input_FakesID_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_700_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_700GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_700_bveto.root" )) {
       input_FakesID_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_700_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_700GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_800_bveto.root" )) {
       input_FakesID_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_800_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_800GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_800_bveto.root" )) {
       input_FakesID_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_800_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_800GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_800_bveto.root" )) {
       input_FakesID_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_800_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_800GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_1200_bveto.root" )) {
       input_FakesID_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_1200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_1200GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_1200_bveto.root" )) {
       input_FakesID_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_1200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_1200GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_1200_bveto.root" )) {
       input_FakesID_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_1200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_1200GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_1500_bveto.root" )) {
       input_FakesID_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_1500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_1500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_1500_bveto.root" )) {
       input_FakesID_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_1500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_1500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_1500_bveto.root" )) {
       input_FakesID_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_1500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_1500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_2000_bveto.root" )) {
       input_FakesID_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_2000_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_2000GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_2000_bveto.root" )) {
       input_FakesID_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_2000_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_2000GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_2000_bveto.root" )) {
       input_FakesID_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_2000_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_2000GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_2500_bveto.root" )) {
       input_FakesID_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_2500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16a_2500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_2500_bveto.root" )) {
       input_FakesID_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_2500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16d_2500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_2500_bveto.root" )) {
       input_FakesID_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_2500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_c16e_2500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

	//Fakes ID btag

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_200_btag.root" )) {
       input_FakesID_btag_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_200GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_200_btag.root" )) {
       input_FakesID_btag_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_200GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_200_btag.root" )) {
       input_FakesID_btag_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_200GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_250_btag.root" )) {
       input_FakesID_btag_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_250GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_250_btag.root" )) {
       input_FakesID_btag_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_250GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_250_btag.root" )) {
       input_FakesID_btag_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_250GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_300_btag.root" )) {
       input_FakesID_btag_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_300GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_300_btag.root" )) {
       input_FakesID_btag_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_300GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_300_btag.root" )) {
       input_FakesID_btag_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_300GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_350_btag.root" )) {
       input_FakesID_btag_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_350GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_350_btag.root" )) {
       input_FakesID_btag_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_350GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_350_btag.root" )) {
       input_FakesID_btag_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_350GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_400_btag.root" )) {
       input_FakesID_btag_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_400GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_400_btag.root" )) {
       input_FakesID_btag_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_400GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_400_btag.root" )) {
       input_FakesID_btag_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_400GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_500_btag.root" )) {
       input_FakesID_btag_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_500_btag.root" )) {
       input_FakesID_btag_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_500_btag.root" )) {
       input_FakesID_btag_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_600_btag.root" )) {
       input_FakesID_btag_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_600GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_600_btag.root" )) {
       input_FakesID_btag_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_600GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_600_btag.root" )) {
       input_FakesID_btag_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_600GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_700_btag.root" )) {
       input_FakesID_btag_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_700GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_700_btag.root" )) {
       input_FakesID_btag_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_700GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_700_btag.root" )) {
       input_FakesID_btag_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_700GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_800_btag.root" )) {
       input_FakesID_btag_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_800GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_800_btag.root" )) {
       input_FakesID_btag_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_800GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_800_btag.root" )) {
       input_FakesID_btag_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_800GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_1200_btag.root" )) {
       input_FakesID_btag_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_1200GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_1200_btag.root" )) {
       input_FakesID_btag_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_1200GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_1200_btag.root" )) {
       input_FakesID_btag_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_1200GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_1500_btag.root" )) {
       input_FakesID_btag_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_1500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_1500_btag.root" )) {
       input_FakesID_btag_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_1500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_1500_btag.root" )) {
       input_FakesID_btag_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_1500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_2000_btag.root" )) {
       input_FakesID_btag_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_2000GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_2000_btag.root" )) {
       input_FakesID_btag_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_2000GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_2000_btag.root" )) {
       input_FakesID_btag_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_2000GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_2500_btag.root" )) {
       input_FakesID_btag_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16a_2500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_2500_btag.root" )) {
       input_FakesID_btag_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ID_data_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16d_2500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_2500_btag.root" )) {
       input_FakesID_btag_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ID_data_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesID_btag_c16e_2500GeV) {
       std::cout << "ERROR: could not open fakes ID data data file" << std::endl;
       exit(1);
    }




	//Fakes ISO bveto

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_200_bveto.root" )) {
       input_FakesISO_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_200GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_200_bveto.root" )) {
       input_FakesISO_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_200GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_200_bveto.root" )) {
       input_FakesISO_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_200GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_250_bveto.root" )) {
       input_FakesISO_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_250_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_250GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_250_bveto.root" )) {
       input_FakesISO_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_250_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_250GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_250_bveto.root" )) {
       input_FakesISO_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_250_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_250GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_300_bveto.root" )) {
       input_FakesISO_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_300_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_300GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_300_bveto.root" )) {
       input_FakesISO_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_300_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_300GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_300_bveto.root" )) {
       input_FakesISO_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_300_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_300GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_350_bveto.root" )) {
       input_FakesISO_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_350_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_350GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_350_bveto.root" )) {
       input_FakesISO_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_350_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_350GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_350_bveto.root" )) {
       input_FakesISO_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_350_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_350GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_400_bveto.root" )) {
       input_FakesISO_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_400_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_400GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_400_bveto.root" )) {
       input_FakesISO_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_400_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_400GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_400_bveto.root" )) {
       input_FakesISO_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_400_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_400GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_500_bveto.root" )) {
       input_FakesISO_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_500GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_500_bveto.root" )) {
       input_FakesISO_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_500GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_500_bveto.root" )) {
       input_FakesISO_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_500GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_600_bveto.root" )) {
       input_FakesISO_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_600_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_600GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_600_bveto.root" )) {
       input_FakesISO_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_600_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_600GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_600_bveto.root" )) {
       input_FakesISO_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_600_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_600GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_700_bveto.root" )) {
       input_FakesISO_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_700_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_700GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_700_bveto.root" )) {
       input_FakesISO_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_700_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_700GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_700_bveto.root" )) {
       input_FakesISO_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_700_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_700GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_800_bveto.root" )) {
       input_FakesISO_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_800_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_800GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_800_bveto.root" )) {
       input_FakesISO_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_800_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_800GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_800_bveto.root" )) {
       input_FakesISO_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_800_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_800GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_1200_bveto.root" )) {
       input_FakesISO_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_1200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_1200GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_1200_bveto.root" )) {
       input_FakesISO_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_1200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_1200GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_1200_bveto.root" )) {
       input_FakesISO_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_1200_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_1200GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_1500_bveto.root" )) {
       input_FakesISO_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_1500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_1500GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_1500_bveto.root" )) {
       input_FakesISO_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_1500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_1500GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_1500_bveto.root" )) {
       input_FakesISO_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_1500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_1500GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_2000_bveto.root" )) {
       input_FakesISO_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_2000_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_2000GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_2000_bveto.root" )) {
       input_FakesISO_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_2000_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_2000GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_2000_bveto.root" )) {
       input_FakesISO_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_2000_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_2000GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_2500_bveto.root" )) {
       input_FakesISO_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_2500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16a_2500GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_2500_bveto.root" )) {
       input_FakesISO_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_2500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16d_2500GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_2500_bveto.root" )) {
       input_FakesISO_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_2500_bveto.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_c16e_2500GeV) {
       std::cout << "ERROR: could not open fakes ISO data bveto data file" << std::endl;
       exit(1);
    }



	//Fakes ISO btag


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_200_btag.root" )) {
       input_FakesISO_btag_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_200GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_200_btag.root" )) {
       input_FakesISO_btag_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_200GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_200_btag.root" )) {
       input_FakesISO_btag_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_200GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_250_btag.root" )) {
       input_FakesISO_btag_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_250GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_250_btag.root" )) {
       input_FakesISO_btag_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_250GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_250_btag.root" )) {
       input_FakesISO_btag_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_250GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_300_btag.root" )) {
       input_FakesISO_btag_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_300GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_300_btag.root" )) {
       input_FakesISO_btag_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_300GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_300_btag.root" )) {
       input_FakesISO_btag_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_300GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_350_btag.root" )) {
       input_FakesISO_btag_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_350GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_350_btag.root" )) {
       input_FakesISO_btag_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_350GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_350_btag.root" )) {
       input_FakesISO_btag_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_350GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_400_btag.root" )) {
       input_FakesISO_btag_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_400GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_400_btag.root" )) {
       input_FakesISO_btag_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_400GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_400_btag.root" )) {
       input_FakesISO_btag_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_400GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_500_btag.root" )) {
       input_FakesISO_btag_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_500_btag.root" )) {
       input_FakesISO_btag_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_500_btag.root" )) {
       input_FakesISO_btag_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_600_btag.root" )) {
       input_FakesISO_btag_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_600GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_600_btag.root" )) {
       input_FakesISO_btag_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_600GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_600_btag.root" )) {
       input_FakesISO_btag_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_600GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_700_btag.root" )) {
       input_FakesISO_btag_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_700GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_700_btag.root" )) {
       input_FakesISO_btag_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_700GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_700_btag.root" )) {
       input_FakesISO_btag_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_700GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_800_btag.root" )) {
       input_FakesISO_btag_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_800GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_800_btag.root" )) {
       input_FakesISO_btag_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_800GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_800_btag.root" )) {
       input_FakesISO_btag_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_800GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_1200_btag.root" )) {
       input_FakesISO_btag_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_1200GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_1200_btag.root" )) {
       input_FakesISO_btag_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_1200GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_1200_btag.root" )) {
       input_FakesISO_btag_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_1200GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_1500_btag.root" )) {
       input_FakesISO_btag_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_1500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_1500_btag.root" )) {
       input_FakesISO_btag_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_1500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_1500_btag.root" )) {
       input_FakesISO_btag_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_1500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_2000_btag.root" )) {
       input_FakesISO_btag_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_2000GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_2000_btag.root" )) {
       input_FakesISO_btag_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_2000GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_2000_btag.root" )) {
       input_FakesISO_btag_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_2000GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_2500_btag.root" )) {
       input_FakesISO_btag_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_2500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_2500_btag.root" )) {
       input_FakesISO_btag_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_2500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_2500_btag.root" )) {
       input_FakesISO_btag_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_2500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }




	//Fakes ISO btag


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_200_btag.root" )) {
       input_FakesISO_btag_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_200GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_200_btag.root" )) {
       input_FakesISO_btag_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_200GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_200_btag.root" )) {
       input_FakesISO_btag_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_200GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_250_btag.root" )) {
       input_FakesISO_btag_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_250GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_250_btag.root" )) {
       input_FakesISO_btag_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_250GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_250_btag.root" )) {
       input_FakesISO_btag_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_250GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_300_btag.root" )) {
       input_FakesISO_btag_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_300GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_300_btag.root" )) {
       input_FakesISO_btag_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_300GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_300_btag.root" )) {
       input_FakesISO_btag_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_300GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_350_btag.root" )) {
       input_FakesISO_btag_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_350GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_350_btag.root" )) {
       input_FakesISO_btag_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_350GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_350_btag.root" )) {
       input_FakesISO_btag_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_350GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_400_btag.root" )) {
       input_FakesISO_btag_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_400GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_400_btag.root" )) {
       input_FakesISO_btag_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_400GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_400_btag.root" )) {
       input_FakesISO_btag_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_400GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_500_btag.root" )) {
       input_FakesISO_btag_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_500GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_500_btag.root" )) {
       input_FakesISO_btag_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_500GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_500_btag.root" )) {
       input_FakesISO_btag_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_500GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_600_btag.root" )) {
       input_FakesISO_btag_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_600GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_600_btag.root" )) {
       input_FakesISO_btag_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_600GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_600_btag.root" )) {
       input_FakesISO_btag_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_600GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_700_btag.root" )) {
       input_FakesISO_btag_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_700GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_700_btag.root" )) {
       input_FakesISO_btag_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_700GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_700_btag.root" )) {
       input_FakesISO_btag_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_700GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_800_btag.root" )) {
       input_FakesISO_btag_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_800GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_800_btag.root" )) {
       input_FakesISO_btag_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_800GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_800_btag.root" )) {
       input_FakesISO_btag_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_800GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_1200_btag.root" )) {
       input_FakesISO_btag_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_1200GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_1200_btag.root" )) {
       input_FakesISO_btag_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_1200GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_1200_btag.root" )) {
       input_FakesISO_btag_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_1200GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_1500_btag.root" )) {
       input_FakesISO_btag_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_1500GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_1500_btag.root" )) {
       input_FakesISO_btag_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_1500GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_1500_btag.root" )) {
       input_FakesISO_btag_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_1500GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_2000_btag.root" )) {
       input_FakesISO_btag_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_2000GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_2000_btag.root" )) {
       input_FakesISO_btag_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_2000GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_2000_btag.root" )) {
       input_FakesISO_btag_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_2000GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_2500_btag.root" )) {
       input_FakesISO_btag_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16a_2500GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_2500_btag.root" )) {
       input_FakesISO_btag_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Fakes_ISO_data_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16d_2500GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_2500_btag.root" )) {
       input_FakesISO_btag_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Fakes_ISO_data_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_FakesISO_btag_c16e_2500GeV) {
       std::cout << "ERROR: could not open fakes ISO data btag data file" << std::endl;
       exit(1);
    }






	//single top btag

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_200_btag.root" )) {
       input_top_single_btag_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_200GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_200_btag.root" )) {
       input_top_single_btag_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_200GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_200_btag.root" )) {
       input_top_single_btag_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_200GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_250_btag.root" )) {
       input_top_single_btag_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_250GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_250_btag.root" )) {
       input_top_single_btag_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_250GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_250_btag.root" )) {
       input_top_single_btag_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_250GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_300_btag.root" )) {
       input_top_single_btag_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_300GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_300_btag.root" )) {
       input_top_single_btag_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_300GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_300_btag.root" )) {
       input_top_single_btag_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_300GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_350_btag.root" )) {
       input_top_single_btag_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_350GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_350_btag.root" )) {
       input_top_single_btag_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_350GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_350_btag.root" )) {
       input_top_single_btag_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_350GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_400_btag.root" )) {
       input_top_single_btag_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_400GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_400_btag.root" )) {
       input_top_single_btag_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_400GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_400_btag.root" )) {
       input_top_single_btag_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_400GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_500_btag.root" )) {
       input_top_single_btag_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_500GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_500_btag.root" )) {
       input_top_single_btag_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_500GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_500_btag.root" )) {
       input_top_single_btag_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_500GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_600_btag.root" )) {
       input_top_single_btag_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_600GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_600_btag.root" )) {
       input_top_single_btag_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_600GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_600_btag.root" )) {
       input_top_single_btag_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_600GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_700_btag.root" )) {
       input_top_single_btag_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_700GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_700_btag.root" )) {
       input_top_single_btag_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_700GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_700_btag.root" )) {
       input_top_single_btag_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_700GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_800_btag.root" )) {
       input_top_single_btag_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_800GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_800_btag.root" )) {
       input_top_single_btag_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_800GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_800_btag.root" )) {
       input_top_single_btag_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_800GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_1200_btag.root" )) {
       input_top_single_btag_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_1200GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_1200_btag.root" )) {
       input_top_single_btag_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_1200GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_1200_btag.root" )) {
       input_top_single_btag_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_1200GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_1500_btag.root" )) {
       input_top_single_btag_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_1500GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_1500_btag.root" )) {
       input_top_single_btag_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_1500GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_1500_btag.root" )) {
       input_top_single_btag_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_1500GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_2000_btag.root" )) {
       input_top_single_btag_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_2000GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_2000_btag.root" )) {
       input_top_single_btag_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_2000GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_2000_btag.root" )) {
       input_top_single_btag_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_2000GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_2500_btag.root" )) {
       input_top_single_btag_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_single_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16a_2500GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_2500_btag.root" )) {
       input_top_single_btag_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_single_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16d_2500GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_2500_btag.root" )) {
       input_top_single_btag_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_single_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_single_btag_c16e_2500GeV) {
       std::cout << "ERROR: could not open top_single data file" << std::endl;
       exit(1);
    }
	

	//ttbar btag

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_200_btag.root" )) {
       input_top_ttbar_btag_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_200GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_200_btag.root" )) {
       input_top_ttbar_btag_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_200GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_200_btag.root" )) {
       input_top_ttbar_btag_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_200_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_200GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_250_btag.root" )) {
       input_top_ttbar_btag_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_250GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_250_btag.root" )) {
       input_top_ttbar_btag_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_250GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_250_btag.root" )) {
       input_top_ttbar_btag_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_250_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_250GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_300_btag.root" )) {
       input_top_ttbar_btag_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_300GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_300_btag.root" )) {
       input_top_ttbar_btag_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_300GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_300_btag.root" )) {
       input_top_ttbar_btag_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_300_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_300GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_350_btag.root" )) {
       input_top_ttbar_btag_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_350GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_350_btag.root" )) {
       input_top_ttbar_btag_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_350GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_350_btag.root" )) {
       input_top_ttbar_btag_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_350_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_350GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_400_btag.root" )) {
       input_top_ttbar_btag_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_400GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_400_btag.root" )) {
       input_top_ttbar_btag_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_400GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_400_btag.root" )) {
       input_top_ttbar_btag_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_400_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_400GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_500_btag.root" )) {
       input_top_ttbar_btag_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_500_btag.root" )) {
       input_top_ttbar_btag_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_500_btag.root" )) {
       input_top_ttbar_btag_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_600_btag.root" )) {
       input_top_ttbar_btag_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_600GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_600_btag.root" )) {
       input_top_ttbar_btag_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_600GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_600_btag.root" )) {
       input_top_ttbar_btag_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_600_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_600GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_700_btag.root" )) {
       input_top_ttbar_btag_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_700GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_700_btag.root" )) {
       input_top_ttbar_btag_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_700GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_700_btag.root" )) {
       input_top_ttbar_btag_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_700_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_700GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_800_btag.root" )) {
       input_top_ttbar_btag_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_800GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_800_btag.root" )) {
       input_top_ttbar_btag_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_800GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_800_btag.root" )) {
       input_top_ttbar_btag_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_800_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_800GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_1200_btag.root" )) {
       input_top_ttbar_btag_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_1200GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_1200_btag.root" )) {
       input_top_ttbar_btag_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_1200GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_1200_btag.root" )) {
       input_top_ttbar_btag_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_1200_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_1200GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_1500_btag.root" )) {
       input_top_ttbar_btag_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_1500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_1500_btag.root" )) {
       input_top_ttbar_btag_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_1500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_1500_btag.root" )) {
       input_top_ttbar_btag_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_1500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_1500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_2000_btag.root" )) {
       input_top_ttbar_btag_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_2000GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_2000_btag.root" )) {
       input_top_ttbar_btag_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_2000GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_2000_btag.root" )) {
       input_top_ttbar_btag_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_2000_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_2000GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_2500_btag.root" )) {
       input_top_ttbar_btag_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16a_2500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_2500_btag.root" )) {
       input_top_ttbar_btag_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16d_2500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_2500_btag.root" )) {
       input_top_ttbar_btag_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_2500_btag.root" ); // check if file in local directory exists
    }
    if (!input_top_ttbar_btag_c16e_2500GeV) {
       std::cout << "ERROR: could not open top_ttbar data file" << std::endl;
       exit(1);
    }





















	//ggH bveto

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_200_bveto_2.root" )) {
       input_ggH_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_200_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_200GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_200_bveto_2.root" )) {
       input_ggH_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_200_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_200GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_200_bveto_2.root" )) {
       input_ggH_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_200_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_200GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_250_bveto_2.root" )) {
       input_ggH_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_250_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_250GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_250_bveto_2.root" )) {
       input_ggH_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_250_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_250GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_250_bveto_2.root" )) {
       input_ggH_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_250_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_250GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_300_bveto_2.root" )) {
       input_ggH_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_300_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_300GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_300_bveto_2.root" )) {
       input_ggH_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_300_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_300GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_300_bveto_2.root" )) {
       input_ggH_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_300_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_300GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_350_bveto_2.root" )) {
       input_ggH_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_350_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_350GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_350_bveto_2.root" )) {
       input_ggH_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_350_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_350GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_350_bveto_2.root" )) {
       input_ggH_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_350_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_350GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_400_bveto_2.root" )) {
       input_ggH_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_400_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_400GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_400_bveto_2.root" )) {
       input_ggH_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_400_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_400GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_400_bveto_2.root" )) {
       input_ggH_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_400_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_400GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_500_bveto_2.root" )) {
       input_ggH_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_500_bveto_2.root" )) {
       input_ggH_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_500_bveto_2.root" )) {
       input_ggH_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_600_bveto_2.root" )) {
       input_ggH_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_600_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_600GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_600_bveto_2.root" )) {
       input_ggH_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_600_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_600GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_600_bveto_2.root" )) {
       input_ggH_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_600_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_600GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_700_bveto_2.root" )) {
       input_ggH_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_700_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_700GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_700_bveto_2.root" )) {
       input_ggH_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_700_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_700GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_700_bveto_2.root" )) {
       input_ggH_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_700_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_700GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_800_bveto_2.root" )) {
       input_ggH_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_800_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_800GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_800_bveto_2.root" )) {
       input_ggH_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_800_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_800GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_800_bveto_2.root" )) {
       input_ggH_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_800_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_800GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_1200_bveto_2.root" )) {
       input_ggH_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_1200_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_1200GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_1200_bveto_2.root" )) {
       input_ggH_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_1200_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_1200GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_1200_bveto_2.root" )) {
       input_ggH_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_1200_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_1200GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_1500_bveto_2.root" )) {
       input_ggH_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_1500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_1500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_1500_bveto_2.root" )) {
       input_ggH_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_1500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_1500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_1500_bveto_2.root" )) {
       input_ggH_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_1500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_1500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_2000_bveto_2.root" )) {
       input_ggH_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_2000_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_2000GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_2000_bveto_2.root" )) {
       input_ggH_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_2000_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_2000GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_2000_bveto_2.root" )) {
       input_ggH_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_2000_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_2000GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }





    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_2500_bveto_2.root" )) {
       input_ggH_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_2500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16a_2500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_2500_bveto_2.root" )) {
       input_ggH_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_2500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16d_2500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_2500_bveto_2.root" )) {
       input_ggH_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_2500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_c16e_2500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

	//ggH btag

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_200_btag_2.root" )) {
       input_ggH_btag_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_200_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_200GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_200_btag_2.root" )) {
       input_ggH_btag_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_200_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_200GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_200_btag_2.root" )) {
       input_ggH_btag_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_200_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_200GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_250_btag_2.root" )) {
       input_ggH_btag_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_250_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_250GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_250_btag_2.root" )) {
       input_ggH_btag_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_250_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_250GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_250_btag_2.root" )) {
       input_ggH_btag_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_250_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_250GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_300_btag_2.root" )) {
       input_ggH_btag_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_300_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_300GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_300_btag_2.root" )) {
       input_ggH_btag_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_300_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_300GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_300_btag_2.root" )) {
       input_ggH_btag_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_300_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_300GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_350_btag_2.root" )) {
       input_ggH_btag_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_350_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_350GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_350_btag_2.root" )) {
       input_ggH_btag_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_350_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_350GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_350_btag_2.root" )) {
       input_ggH_btag_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_350_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_350GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_400_btag_2.root" )) {
       input_ggH_btag_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_400_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_400GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_400_btag_2.root" )) {
       input_ggH_btag_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_400_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_400GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_400_btag_2.root" )) {
       input_ggH_btag_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_400_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_400GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_500_btag_2.root" )) {
       input_ggH_btag_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_500_btag_2.root" )) {
       input_ggH_btag_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_500_btag_2.root" )) {
       input_ggH_btag_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_600_btag_2.root" )) {
       input_ggH_btag_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_600_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_600GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_600_btag_2.root" )) {
       input_ggH_btag_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_600_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_600GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_600_btag_2.root" )) {
       input_ggH_btag_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_600_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_600GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_700_btag_2.root" )) {
       input_ggH_btag_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_700_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_700GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_700_btag_2.root" )) {
       input_ggH_btag_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_700_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_700GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_700_btag_2.root" )) {
       input_ggH_btag_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_700_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_700GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_800_btag_2.root" )) {
       input_ggH_btag_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_800_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_800GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_800_btag_2.root" )) {
       input_ggH_btag_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_800_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_800GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_800_btag_2.root" )) {
       input_ggH_btag_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_800_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_800GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_1200_btag_2.root" )) {
       input_ggH_btag_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_1200_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_1200GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_1200_btag_2.root" )) {
       input_ggH_btag_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_1200_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_1200GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_1200_btag_2.root" )) {
       input_ggH_btag_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_1200_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_1200GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_1500_btag_2.root" )) {
       input_ggH_btag_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_1500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_1500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_1500_btag_2.root" )) {
       input_ggH_btag_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_1500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_1500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_1500_btag_2.root" )) {
       input_ggH_btag_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_1500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_1500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_2000_btag_2.root" )) {
       input_ggH_btag_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_2000_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_2000GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_2000_btag_2.root" )) {
       input_ggH_btag_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_2000_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_2000GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_2000_btag_2.root" )) {
       input_ggH_btag_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_2000_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_2000GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }





    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_ggH_2500_btag_2.root" )) {
       input_ggH_btag_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_ggH_2500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16a_2500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_ggH_2500_btag_2.root" )) {
       input_ggH_btag_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_ggH_2500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16d_2500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_ggH_2500_btag_2.root" )) {
       input_ggH_btag_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_ggH_2500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_ggH_btag_c16e_2500GeV) {
       std::cout << "ERROR: could not open ggH data file" << std::endl;
       exit(1);
    }







	//bbH bveto

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_200_bveto_2.root" )) {
       input_bbH_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_200_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_200GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_200_bveto_2.root" )) {
       input_bbH_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_200_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_200GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_200_bveto_2.root" )) {
       input_bbH_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_200_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_200GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_250_bveto_2.root" )) {
       input_bbH_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_250_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_250GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_250_bveto_2.root" )) {
       input_bbH_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_250_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_250GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_250_bveto_2.root" )) {
       input_bbH_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_250_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_250GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_300_bveto_2.root" )) {
       input_bbH_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_300_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_300GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_300_bveto_2.root" )) {
       input_bbH_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_300_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_300GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_300_bveto_2.root" )) {
       input_bbH_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_300_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_300GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_350_bveto_2.root" )) {
       input_bbH_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_350_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_350GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_350_bveto_2.root" )) {
       input_bbH_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_350_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_350GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_350_bveto_2.root" )) {
       input_bbH_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_350_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_350GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_400_bveto_2.root" )) {
       input_bbH_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_400_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_400GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_400_bveto_2.root" )) {
       input_bbH_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_400_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_400GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_400_bveto_2.root" )) {
       input_bbH_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_400_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_400GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_500_bveto_2.root" )) {
       input_bbH_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_500_bveto_2.root" )) {
       input_bbH_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_500_bveto_2.root" )) {
       input_bbH_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_600_bveto_2.root" )) {
       input_bbH_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_600_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_600GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_600_bveto_2.root" )) {
       input_bbH_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_600_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_600GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_600_bveto_2.root" )) {
       input_bbH_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_600_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_600GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_700_bveto_2.root" )) {
       input_bbH_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_700_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_700GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_700_bveto_2.root" )) {
       input_bbH_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_700_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_700GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_700_bveto_2.root" )) {
       input_bbH_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_700_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_700GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_800_bveto_2.root" )) {
       input_bbH_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_800_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_800GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_800_bveto_2.root" )) {
       input_bbH_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_800_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_800GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_800_bveto_2.root" )) {
       input_bbH_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_800_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_800GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_1200_bveto_2.root" )) {
       input_bbH_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_1200_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_1200GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_1200_bveto_2.root" )) {
       input_bbH_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_1200_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_1200GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_1200_bveto_2.root" )) {
       input_bbH_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_1200_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_1200GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_1500_bveto_2.root" )) {
       input_bbH_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_1500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_1500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_1500_bveto_2.root" )) {
       input_bbH_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_1500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_1500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_1500_bveto_2.root" )) {
       input_bbH_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_1500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_1500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_2000_bveto_2.root" )) {
       input_bbH_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_2000_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_2000GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_2000_bveto_2.root" )) {
       input_bbH_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_2000_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_2000GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_2000_bveto_2.root" )) {
       input_bbH_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_2000_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_2000GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }





    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_2500_bveto_2.root" )) {
       input_bbH_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_2500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16a_2500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_2500_bveto_2.root" )) {
       input_bbH_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_2500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16d_2500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_2500_bveto_2.root" )) {
       input_bbH_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_2500_bveto_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_c16e_2500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }






	//bbH btag

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_200_btag_2.root" )) {
       input_bbH_btag_c16a_200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_200_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_200GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_200_btag_2.root" )) {
       input_bbH_btag_c16d_200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_200_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_200GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_200_btag_2.root" )) {
       input_bbH_btag_c16e_200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_200_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_200GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_250_btag_2.root" )) {
       input_bbH_btag_c16a_250GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_250_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_250GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_250_btag_2.root" )) {
       input_bbH_btag_c16d_250GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_250_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_250GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_250_btag_2.root" )) {
       input_bbH_btag_c16e_250GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_250_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_250GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_300_btag_2.root" )) {
       input_bbH_btag_c16a_300GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_300_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_300GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_300_btag_2.root" )) {
       input_bbH_btag_c16d_300GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_300_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_300GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_300_btag_2.root" )) {
       input_bbH_btag_c16e_300GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_300_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_300GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_350_btag_2.root" )) {
       input_bbH_btag_c16a_350GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_350_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_350GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_350_btag_2.root" )) {
       input_bbH_btag_c16d_350GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_350_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_350GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_350_btag_2.root" )) {
       input_bbH_btag_c16e_350GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_350_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_350GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_400_btag_2.root" )) {
       input_bbH_btag_c16a_400GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_400_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_400GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_400_btag_2.root" )) {
       input_bbH_btag_c16d_400GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_400_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_400GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_400_btag_2.root" )) {
       input_bbH_btag_c16e_400GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_400_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_400GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_500_btag_2.root" )) {
       input_bbH_btag_c16a_500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_500_btag_2.root" )) {
       input_bbH_btag_c16d_500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_500_btag_2.root" )) {
       input_bbH_btag_c16e_500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_600_btag_2.root" )) {
       input_bbH_btag_c16a_600GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_600_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_600GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_600_btag_2.root" )) {
       input_bbH_btag_c16d_600GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_600_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_600GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_600_btag_2.root" )) {
       input_bbH_btag_c16e_600GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_600_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_600GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_700_btag_2.root" )) {
       input_bbH_btag_c16a_700GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_700_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_700GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_700_btag_2.root" )) {
       input_bbH_btag_c16d_700GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_700_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_700GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_700_btag_2.root" )) {
       input_bbH_btag_c16e_700GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_700_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_700GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_800_btag_2.root" )) {
       input_bbH_btag_c16a_800GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_800_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_800GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_800_btag_2.root" )) {
       input_bbH_btag_c16d_800GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_800_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_800GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_800_btag_2.root" )) {
       input_bbH_btag_c16e_800GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_800_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_800GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_1200_btag_2.root" )) {
       input_bbH_btag_c16a_1200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_1200_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_1200GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_1200_btag_2.root" )) {
       input_bbH_btag_c16d_1200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_1200_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_1200GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_1200_btag_2.root" )) {
       input_bbH_btag_c16e_1200GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_1200_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_1200GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }



    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_1500_btag_2.root" )) {
       input_bbH_btag_c16a_1500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_1500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_1500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_1500_btag_2.root" )) {
       input_bbH_btag_c16d_1500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_1500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_1500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_1500_btag_2.root" )) {
       input_bbH_btag_c16e_1500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_1500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_1500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_2000_btag_2.root" )) {
       input_bbH_btag_c16a_2000GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_2000_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_2000GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_2000_btag_2.root" )) {
       input_bbH_btag_c16d_2000GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_2000_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_2000GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_2000_btag_2.root" )) {
       input_bbH_btag_c16e_2000GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_2000_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_2000GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }





    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16a_bbH_2500_btag_2.root" )) {
       input_bbH_btag_c16a_2500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16a_bbH_2500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16a_2500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }

    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16d_bbH_2500_btag_2.root" )) {
       input_bbH_btag_c16d_2500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16d_bbH_2500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16d_2500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }


    if (!gSystem->AccessPathName( "dumpNtuples/201215/SR_sig_X_c16e_bbH_2500_btag_2.root" )) {
       input_bbH_btag_c16e_2500GeV = TFile::Open( "dumpNtuples/201215/SR_sig_X_c16e_bbH_2500_btag_2.root" ); // check if file in local directory exists
    }
    if (!input_bbH_btag_c16e_2500GeV) {
       std::cout << "ERROR: could not open bbH data file" << std::endl;
       exit(1);
    }















 
    // Register the training and test trees

	//bveto
 
    TTree *signalTree_ggH_c16a_200GeV                = (TTree*)input_ggH_c16a_200GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16a_250GeV                = (TTree*)input_ggH_c16a_250GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16a_300GeV                = (TTree*)input_ggH_c16a_300GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16a_350GeV                = (TTree*)input_ggH_c16a_350GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16a_400GeV                = (TTree*)input_ggH_c16a_400GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16a_500GeV                = (TTree*)input_ggH_c16a_500GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16a_600GeV                = (TTree*)input_ggH_c16a_600GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16a_700GeV                = (TTree*)input_ggH_c16a_700GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16a_800GeV                = (TTree*)input_ggH_c16a_800GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16a_1200GeV                = (TTree*)input_ggH_c16a_1200GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16a_1500GeV                = (TTree*)input_ggH_c16a_1500GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16a_2000GeV                = (TTree*)input_ggH_c16a_2000GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16a_2500GeV                = (TTree*)input_ggH_c16a_2500GeV->Get("NOMINAL");

    TTree *signalTree_ggH_c16d_200GeV                = (TTree*)input_ggH_c16d_200GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16d_250GeV                = (TTree*)input_ggH_c16d_250GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16d_300GeV                = (TTree*)input_ggH_c16d_300GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16d_350GeV                = (TTree*)input_ggH_c16d_350GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16d_400GeV                = (TTree*)input_ggH_c16d_400GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16d_500GeV                = (TTree*)input_ggH_c16d_500GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16d_600GeV                = (TTree*)input_ggH_c16d_600GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16d_700GeV                = (TTree*)input_ggH_c16d_700GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16d_800GeV                = (TTree*)input_ggH_c16d_800GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16d_1200GeV                = (TTree*)input_ggH_c16d_1200GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16d_1500GeV                = (TTree*)input_ggH_c16d_1500GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16d_2000GeV                = (TTree*)input_ggH_c16d_2000GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16d_2500GeV                = (TTree*)input_ggH_c16d_2500GeV->Get("NOMINAL");

    TTree *signalTree_ggH_c16e_200GeV                = (TTree*)input_ggH_c16e_200GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16e_250GeV                = (TTree*)input_ggH_c16e_250GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16e_300GeV                = (TTree*)input_ggH_c16e_300GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16e_350GeV                = (TTree*)input_ggH_c16e_350GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16e_400GeV                = (TTree*)input_ggH_c16e_400GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16e_500GeV                = (TTree*)input_ggH_c16e_500GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16e_600GeV                = (TTree*)input_ggH_c16e_600GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16e_700GeV                = (TTree*)input_ggH_c16e_700GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16e_800GeV                = (TTree*)input_ggH_c16e_800GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16e_1200GeV                = (TTree*)input_ggH_c16e_1200GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16e_1500GeV                = (TTree*)input_ggH_c16e_1500GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16e_2000GeV                = (TTree*)input_ggH_c16e_2000GeV->Get("NOMINAL");
    TTree *signalTree_ggH_c16e_2500GeV                = (TTree*)input_ggH_c16e_2500GeV->Get("NOMINAL");


    TTree *signalTree_bbH_c16a_200GeV                = (TTree*)input_bbH_c16a_200GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16a_250GeV                = (TTree*)input_bbH_c16a_250GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16a_300GeV                = (TTree*)input_bbH_c16a_300GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16a_350GeV                = (TTree*)input_bbH_c16a_350GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16a_400GeV                = (TTree*)input_bbH_c16a_400GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16a_500GeV                = (TTree*)input_bbH_c16a_500GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16a_600GeV                = (TTree*)input_bbH_c16a_600GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16a_700GeV                = (TTree*)input_bbH_c16a_700GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16a_800GeV                = (TTree*)input_bbH_c16a_800GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16a_1200GeV                = (TTree*)input_bbH_c16a_1200GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16a_1500GeV                = (TTree*)input_bbH_c16a_1500GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16a_2000GeV                = (TTree*)input_bbH_c16a_2000GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16a_2500GeV                = (TTree*)input_bbH_c16a_2500GeV->Get("NOMINAL");

    TTree *signalTree_bbH_c16d_200GeV                = (TTree*)input_bbH_c16d_200GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16d_250GeV                = (TTree*)input_bbH_c16d_250GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16d_300GeV                = (TTree*)input_bbH_c16d_300GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16d_350GeV                = (TTree*)input_bbH_c16d_350GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16d_400GeV                = (TTree*)input_bbH_c16d_400GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16d_500GeV                = (TTree*)input_bbH_c16d_500GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16d_600GeV                = (TTree*)input_bbH_c16d_600GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16d_700GeV                = (TTree*)input_bbH_c16d_700GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16d_800GeV                = (TTree*)input_bbH_c16d_800GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16d_1200GeV                = (TTree*)input_bbH_c16d_1200GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16d_1500GeV                = (TTree*)input_bbH_c16d_1500GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16d_2000GeV                = (TTree*)input_bbH_c16d_2000GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16d_2500GeV                = (TTree*)input_bbH_c16d_2500GeV->Get("NOMINAL");

    TTree *signalTree_bbH_c16e_200GeV                = (TTree*)input_bbH_c16e_200GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16e_250GeV                = (TTree*)input_bbH_c16e_250GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16e_300GeV                = (TTree*)input_bbH_c16e_300GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16e_350GeV                = (TTree*)input_bbH_c16e_350GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16e_400GeV                = (TTree*)input_bbH_c16e_400GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16e_500GeV                = (TTree*)input_bbH_c16e_500GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16e_600GeV                = (TTree*)input_bbH_c16e_600GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16e_700GeV                = (TTree*)input_bbH_c16e_700GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16e_800GeV                = (TTree*)input_bbH_c16e_800GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16e_1200GeV                = (TTree*)input_bbH_c16e_1200GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16e_1500GeV                = (TTree*)input_bbH_c16e_1500GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16e_2000GeV                = (TTree*)input_bbH_c16e_2000GeV->Get("NOMINAL");
    TTree *signalTree_bbH_c16e_2500GeV                = (TTree*)input_bbH_c16e_2500GeV->Get("NOMINAL");


    TTree *bkgTree_Ztautau_c16a_200GeV                = (TTree*)input_Ztautau_c16a_200GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16a_250GeV                = (TTree*)input_Ztautau_c16a_250GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16a_300GeV                = (TTree*)input_Ztautau_c16a_300GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16a_350GeV                = (TTree*)input_Ztautau_c16a_350GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16a_400GeV                = (TTree*)input_Ztautau_c16a_400GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16a_500GeV                = (TTree*)input_Ztautau_c16a_500GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16a_600GeV                = (TTree*)input_Ztautau_c16a_600GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16a_700GeV                = (TTree*)input_Ztautau_c16a_700GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16a_800GeV                = (TTree*)input_Ztautau_c16a_800GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16a_1200GeV                = (TTree*)input_Ztautau_c16a_1200GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16a_1500GeV                = (TTree*)input_Ztautau_c16a_1500GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16a_2000GeV                = (TTree*)input_Ztautau_c16a_2000GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16a_2500GeV                = (TTree*)input_Ztautau_c16a_2500GeV->Get("NOMINAL");

    TTree *bkgTree_Ztautau_c16d_200GeV                = (TTree*)input_Ztautau_c16d_200GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16d_250GeV                = (TTree*)input_Ztautau_c16d_250GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16d_300GeV                = (TTree*)input_Ztautau_c16d_300GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16d_350GeV                = (TTree*)input_Ztautau_c16d_350GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16d_400GeV                = (TTree*)input_Ztautau_c16d_400GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16d_500GeV                = (TTree*)input_Ztautau_c16d_500GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16d_600GeV                = (TTree*)input_Ztautau_c16d_600GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16d_700GeV                = (TTree*)input_Ztautau_c16d_700GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16d_800GeV                = (TTree*)input_Ztautau_c16d_800GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16d_1200GeV                = (TTree*)input_Ztautau_c16d_1200GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16d_1500GeV                = (TTree*)input_Ztautau_c16d_1500GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16d_2000GeV                = (TTree*)input_Ztautau_c16d_2000GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16d_2500GeV                = (TTree*)input_Ztautau_c16d_2500GeV->Get("NOMINAL");

    TTree *bkgTree_Ztautau_c16e_200GeV                = (TTree*)input_Ztautau_c16e_200GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16e_250GeV                = (TTree*)input_Ztautau_c16e_250GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16e_300GeV                = (TTree*)input_Ztautau_c16e_300GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16e_350GeV                = (TTree*)input_Ztautau_c16e_350GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16e_400GeV                = (TTree*)input_Ztautau_c16e_400GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16e_500GeV                = (TTree*)input_Ztautau_c16e_500GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16e_600GeV                = (TTree*)input_Ztautau_c16e_600GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16e_700GeV                = (TTree*)input_Ztautau_c16e_700GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16e_800GeV                = (TTree*)input_Ztautau_c16e_800GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16e_1200GeV                = (TTree*)input_Ztautau_c16e_1200GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16e_1500GeV                = (TTree*)input_Ztautau_c16e_1500GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16e_2000GeV                = (TTree*)input_Ztautau_c16e_2000GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_c16e_2500GeV                = (TTree*)input_Ztautau_c16e_2500GeV->Get("NOMINAL");


    TTree *bkgTree_Zll_c16a_200GeV                = (TTree*)input_Zll_c16a_200GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16a_250GeV                = (TTree*)input_Zll_c16a_250GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16a_300GeV                = (TTree*)input_Zll_c16a_300GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16a_350GeV                = (TTree*)input_Zll_c16a_350GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16a_400GeV                = (TTree*)input_Zll_c16a_400GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16a_500GeV                = (TTree*)input_Zll_c16a_500GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16a_600GeV                = (TTree*)input_Zll_c16a_600GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16a_700GeV                = (TTree*)input_Zll_c16a_700GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16a_800GeV                = (TTree*)input_Zll_c16a_800GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16a_1200GeV                = (TTree*)input_Zll_c16a_1200GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16a_1500GeV                = (TTree*)input_Zll_c16a_1500GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16a_2000GeV                = (TTree*)input_Zll_c16a_2000GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16a_2500GeV                = (TTree*)input_Zll_c16a_2500GeV->Get("NOMINAL");

    TTree *bkgTree_Zll_c16d_200GeV                = (TTree*)input_Zll_c16d_200GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16d_250GeV                = (TTree*)input_Zll_c16d_250GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16d_300GeV                = (TTree*)input_Zll_c16d_300GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16d_350GeV                = (TTree*)input_Zll_c16d_350GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16d_400GeV                = (TTree*)input_Zll_c16d_400GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16d_500GeV                = (TTree*)input_Zll_c16d_500GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16d_600GeV                = (TTree*)input_Zll_c16d_600GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16d_700GeV                = (TTree*)input_Zll_c16d_700GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16d_800GeV                = (TTree*)input_Zll_c16d_800GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16d_1200GeV                = (TTree*)input_Zll_c16d_1200GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16d_1500GeV                = (TTree*)input_Zll_c16d_1500GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16d_2000GeV                = (TTree*)input_Zll_c16d_2000GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16d_2500GeV                = (TTree*)input_Zll_c16d_2500GeV->Get("NOMINAL");

    TTree *bkgTree_Zll_c16e_200GeV                = (TTree*)input_Zll_c16e_200GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16e_250GeV                = (TTree*)input_Zll_c16e_250GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16e_300GeV                = (TTree*)input_Zll_c16e_300GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16e_350GeV                = (TTree*)input_Zll_c16e_350GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16e_400GeV                = (TTree*)input_Zll_c16e_400GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16e_500GeV                = (TTree*)input_Zll_c16e_500GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16e_600GeV                = (TTree*)input_Zll_c16e_600GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16e_700GeV                = (TTree*)input_Zll_c16e_700GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16e_800GeV                = (TTree*)input_Zll_c16e_800GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16e_1200GeV                = (TTree*)input_Zll_c16e_1200GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16e_1500GeV                = (TTree*)input_Zll_c16e_1500GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16e_2000GeV                = (TTree*)input_Zll_c16e_2000GeV->Get("NOMINAL");
    TTree *bkgTree_Zll_c16e_2500GeV                = (TTree*)input_Zll_c16e_2500GeV->Get("NOMINAL");


    TTree *bkgTree_FakesID_c16a_200GeV                = (TTree*)input_FakesID_c16a_200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16a_250GeV                = (TTree*)input_FakesID_c16a_250GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16a_300GeV                = (TTree*)input_FakesID_c16a_300GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16a_350GeV                = (TTree*)input_FakesID_c16a_350GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16a_400GeV                = (TTree*)input_FakesID_c16a_400GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16a_500GeV                = (TTree*)input_FakesID_c16a_500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16a_600GeV                = (TTree*)input_FakesID_c16a_600GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16a_700GeV                = (TTree*)input_FakesID_c16a_700GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16a_800GeV                = (TTree*)input_FakesID_c16a_800GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16a_1200GeV                = (TTree*)input_FakesID_c16a_1200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16a_1500GeV                = (TTree*)input_FakesID_c16a_1500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16a_2000GeV                = (TTree*)input_FakesID_c16a_2000GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16a_2500GeV                = (TTree*)input_FakesID_c16a_2500GeV->Get("NOMINAL");

    TTree *bkgTree_FakesID_c16d_200GeV                = (TTree*)input_FakesID_c16d_200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16d_250GeV                = (TTree*)input_FakesID_c16d_250GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16d_300GeV                = (TTree*)input_FakesID_c16d_300GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16d_350GeV                = (TTree*)input_FakesID_c16d_350GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16d_400GeV                = (TTree*)input_FakesID_c16d_400GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16d_500GeV                = (TTree*)input_FakesID_c16d_500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16d_600GeV                = (TTree*)input_FakesID_c16d_600GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16d_700GeV                = (TTree*)input_FakesID_c16d_700GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16d_800GeV                = (TTree*)input_FakesID_c16d_800GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16d_1200GeV                = (TTree*)input_FakesID_c16d_1200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16d_1500GeV                = (TTree*)input_FakesID_c16d_1500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16d_2000GeV                = (TTree*)input_FakesID_c16d_2000GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16d_2500GeV                = (TTree*)input_FakesID_c16d_2500GeV->Get("NOMINAL");

    TTree *bkgTree_FakesID_c16e_200GeV                = (TTree*)input_FakesID_c16e_200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16e_250GeV                = (TTree*)input_FakesID_c16e_250GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16e_300GeV                = (TTree*)input_FakesID_c16e_300GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16e_350GeV                = (TTree*)input_FakesID_c16e_350GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16e_400GeV                = (TTree*)input_FakesID_c16e_400GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16e_500GeV                = (TTree*)input_FakesID_c16e_500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16e_600GeV                = (TTree*)input_FakesID_c16e_600GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16e_700GeV                = (TTree*)input_FakesID_c16e_700GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16e_800GeV                = (TTree*)input_FakesID_c16e_800GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16e_1200GeV                = (TTree*)input_FakesID_c16e_1200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16e_1500GeV                = (TTree*)input_FakesID_c16e_1500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16e_2000GeV                = (TTree*)input_FakesID_c16e_2000GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_c16e_2500GeV                = (TTree*)input_FakesID_c16e_2500GeV->Get("NOMINAL");


    TTree *bkgTree_FakesISO_c16a_200GeV                = (TTree*)input_FakesISO_c16a_200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16a_250GeV                = (TTree*)input_FakesISO_c16a_250GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16a_300GeV                = (TTree*)input_FakesISO_c16a_300GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16a_350GeV                = (TTree*)input_FakesISO_c16a_350GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16a_400GeV                = (TTree*)input_FakesISO_c16a_400GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16a_500GeV                = (TTree*)input_FakesISO_c16a_500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16a_600GeV                = (TTree*)input_FakesISO_c16a_600GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16a_700GeV                = (TTree*)input_FakesISO_c16a_700GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16a_800GeV                = (TTree*)input_FakesISO_c16a_800GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16a_1200GeV                = (TTree*)input_FakesISO_c16a_1200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16a_1500GeV                = (TTree*)input_FakesISO_c16a_1500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16a_2000GeV                = (TTree*)input_FakesISO_c16a_2000GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16a_2500GeV                = (TTree*)input_FakesISO_c16a_2500GeV->Get("NOMINAL");

    TTree *bkgTree_FakesISO_c16d_200GeV                = (TTree*)input_FakesISO_c16d_200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16d_250GeV                = (TTree*)input_FakesISO_c16d_250GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16d_300GeV                = (TTree*)input_FakesISO_c16d_300GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16d_350GeV                = (TTree*)input_FakesISO_c16d_350GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16d_400GeV                = (TTree*)input_FakesISO_c16d_400GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16d_500GeV                = (TTree*)input_FakesISO_c16d_500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16d_600GeV                = (TTree*)input_FakesISO_c16d_600GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16d_700GeV                = (TTree*)input_FakesISO_c16d_700GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16d_800GeV                = (TTree*)input_FakesISO_c16d_800GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16d_1200GeV                = (TTree*)input_FakesISO_c16d_1200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16d_1500GeV                = (TTree*)input_FakesISO_c16d_1500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16d_2000GeV                = (TTree*)input_FakesISO_c16d_2000GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16d_2500GeV                = (TTree*)input_FakesISO_c16d_2500GeV->Get("NOMINAL");

    TTree *bkgTree_FakesISO_c16e_200GeV                = (TTree*)input_FakesISO_c16e_200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16e_250GeV                = (TTree*)input_FakesISO_c16e_250GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16e_300GeV                = (TTree*)input_FakesISO_c16e_300GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16e_350GeV                = (TTree*)input_FakesISO_c16e_350GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16e_400GeV                = (TTree*)input_FakesISO_c16e_400GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16e_500GeV                = (TTree*)input_FakesISO_c16e_500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16e_600GeV                = (TTree*)input_FakesISO_c16e_600GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16e_700GeV                = (TTree*)input_FakesISO_c16e_700GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16e_800GeV                = (TTree*)input_FakesISO_c16e_800GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16e_1200GeV                = (TTree*)input_FakesISO_c16e_1200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16e_1500GeV                = (TTree*)input_FakesISO_c16e_1500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16e_2000GeV                = (TTree*)input_FakesISO_c16e_2000GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_c16e_2500GeV                = (TTree*)input_FakesISO_c16e_2500GeV->Get("NOMINAL");



	//btag

    TTree *signalTree_ggH_btag_c16a_200GeV                = (TTree*)input_ggH_btag_c16a_200GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16a_250GeV                = (TTree*)input_ggH_btag_c16a_250GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16a_300GeV                = (TTree*)input_ggH_btag_c16a_300GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16a_350GeV                = (TTree*)input_ggH_btag_c16a_350GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16a_400GeV                = (TTree*)input_ggH_btag_c16a_400GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16a_500GeV                = (TTree*)input_ggH_btag_c16a_500GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16a_600GeV                = (TTree*)input_ggH_btag_c16a_600GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16a_700GeV                = (TTree*)input_ggH_btag_c16a_700GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16a_800GeV                = (TTree*)input_ggH_btag_c16a_800GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16a_1200GeV                = (TTree*)input_ggH_btag_c16a_1200GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16a_1500GeV                = (TTree*)input_ggH_btag_c16a_1500GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16a_2000GeV                = (TTree*)input_ggH_btag_c16a_2000GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16a_2500GeV                = (TTree*)input_ggH_btag_c16a_2500GeV->Get("NOMINAL");

    TTree *signalTree_ggH_btag_c16d_200GeV                = (TTree*)input_ggH_btag_c16d_200GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16d_250GeV                = (TTree*)input_ggH_btag_c16d_250GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16d_300GeV                = (TTree*)input_ggH_btag_c16d_300GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16d_350GeV                = (TTree*)input_ggH_btag_c16d_350GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16d_400GeV                = (TTree*)input_ggH_btag_c16d_400GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16d_500GeV                = (TTree*)input_ggH_btag_c16d_500GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16d_600GeV                = (TTree*)input_ggH_btag_c16d_600GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16d_700GeV                = (TTree*)input_ggH_btag_c16d_700GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16d_800GeV                = (TTree*)input_ggH_btag_c16d_800GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16d_1200GeV                = (TTree*)input_ggH_btag_c16d_1200GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16d_1500GeV                = (TTree*)input_ggH_btag_c16d_1500GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16d_2000GeV                = (TTree*)input_ggH_btag_c16d_2000GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16d_2500GeV                = (TTree*)input_ggH_btag_c16d_2500GeV->Get("NOMINAL");

    TTree *signalTree_ggH_btag_c16e_200GeV                = (TTree*)input_ggH_btag_c16e_200GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16e_250GeV                = (TTree*)input_ggH_btag_c16e_250GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16e_300GeV                = (TTree*)input_ggH_btag_c16e_300GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16e_350GeV                = (TTree*)input_ggH_btag_c16e_350GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16e_400GeV                = (TTree*)input_ggH_btag_c16e_400GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16e_500GeV                = (TTree*)input_ggH_btag_c16e_500GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16e_600GeV                = (TTree*)input_ggH_btag_c16e_600GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16e_700GeV                = (TTree*)input_ggH_btag_c16e_700GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16e_800GeV                = (TTree*)input_ggH_btag_c16e_800GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16e_1200GeV                = (TTree*)input_ggH_btag_c16e_1200GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16e_1500GeV                = (TTree*)input_ggH_btag_c16e_1500GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16e_2000GeV                = (TTree*)input_ggH_btag_c16e_2000GeV->Get("NOMINAL");
    TTree *signalTree_ggH_btag_c16e_2500GeV                = (TTree*)input_ggH_btag_c16e_2500GeV->Get("NOMINAL");


    TTree *signalTree_bbH_btag_c16a_200GeV                = (TTree*)input_bbH_btag_c16a_200GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16a_250GeV                = (TTree*)input_bbH_btag_c16a_250GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16a_300GeV                = (TTree*)input_bbH_btag_c16a_300GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16a_350GeV                = (TTree*)input_bbH_btag_c16a_350GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16a_400GeV                = (TTree*)input_bbH_btag_c16a_400GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16a_500GeV                = (TTree*)input_bbH_btag_c16a_500GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16a_600GeV                = (TTree*)input_bbH_btag_c16a_600GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16a_700GeV                = (TTree*)input_bbH_btag_c16a_700GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16a_800GeV                = (TTree*)input_bbH_btag_c16a_800GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16a_1200GeV                = (TTree*)input_bbH_btag_c16a_1200GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16a_1500GeV                = (TTree*)input_bbH_btag_c16a_1500GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16a_2000GeV                = (TTree*)input_bbH_btag_c16a_2000GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16a_2500GeV                = (TTree*)input_bbH_btag_c16a_2500GeV->Get("NOMINAL");

    TTree *signalTree_bbH_btag_c16d_200GeV                = (TTree*)input_bbH_btag_c16d_200GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16d_250GeV                = (TTree*)input_bbH_btag_c16d_250GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16d_300GeV                = (TTree*)input_bbH_btag_c16d_300GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16d_350GeV                = (TTree*)input_bbH_btag_c16d_350GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16d_400GeV                = (TTree*)input_bbH_btag_c16d_400GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16d_500GeV                = (TTree*)input_bbH_btag_c16d_500GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16d_600GeV                = (TTree*)input_bbH_btag_c16d_600GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16d_700GeV                = (TTree*)input_bbH_btag_c16d_700GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16d_800GeV                = (TTree*)input_bbH_btag_c16d_800GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16d_1200GeV                = (TTree*)input_bbH_btag_c16d_1200GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16d_1500GeV                = (TTree*)input_bbH_btag_c16d_1500GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16d_2000GeV                = (TTree*)input_bbH_btag_c16d_2000GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16d_2500GeV                = (TTree*)input_bbH_btag_c16d_2500GeV->Get("NOMINAL");

    TTree *signalTree_bbH_btag_c16e_200GeV                = (TTree*)input_bbH_btag_c16e_200GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16e_250GeV                = (TTree*)input_bbH_btag_c16e_250GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16e_300GeV                = (TTree*)input_bbH_btag_c16e_300GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16e_350GeV                = (TTree*)input_bbH_btag_c16e_350GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16e_400GeV                = (TTree*)input_bbH_btag_c16e_400GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16e_500GeV                = (TTree*)input_bbH_btag_c16e_500GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16e_600GeV                = (TTree*)input_bbH_btag_c16e_600GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16e_700GeV                = (TTree*)input_bbH_btag_c16e_700GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16e_800GeV                = (TTree*)input_bbH_btag_c16e_800GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16e_1200GeV                = (TTree*)input_bbH_btag_c16e_1200GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16e_1500GeV                = (TTree*)input_bbH_btag_c16e_1500GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16e_2000GeV                = (TTree*)input_bbH_btag_c16e_2000GeV->Get("NOMINAL");
    TTree *signalTree_bbH_btag_c16e_2500GeV                = (TTree*)input_bbH_btag_c16e_2500GeV->Get("NOMINAL");


    TTree *bkgTree_Ztautau_btag_c16a_200GeV                = (TTree*)input_Ztautau_btag_c16a_200GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16a_250GeV                = (TTree*)input_Ztautau_btag_c16a_250GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16a_300GeV                = (TTree*)input_Ztautau_btag_c16a_300GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16a_350GeV                = (TTree*)input_Ztautau_btag_c16a_350GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16a_400GeV                = (TTree*)input_Ztautau_btag_c16a_400GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16a_500GeV                = (TTree*)input_Ztautau_btag_c16a_500GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16a_600GeV                = (TTree*)input_Ztautau_btag_c16a_600GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16a_700GeV                = (TTree*)input_Ztautau_btag_c16a_700GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16a_800GeV                = (TTree*)input_Ztautau_btag_c16a_800GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16a_1200GeV                = (TTree*)input_Ztautau_btag_c16a_1200GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16a_1500GeV                = (TTree*)input_Ztautau_btag_c16a_1500GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16a_2000GeV                = (TTree*)input_Ztautau_btag_c16a_2000GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16a_2500GeV                = (TTree*)input_Ztautau_btag_c16a_2500GeV->Get("NOMINAL");

    TTree *bkgTree_Ztautau_btag_c16d_200GeV                = (TTree*)input_Ztautau_btag_c16d_200GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16d_250GeV                = (TTree*)input_Ztautau_btag_c16d_250GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16d_300GeV                = (TTree*)input_Ztautau_btag_c16d_300GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16d_350GeV                = (TTree*)input_Ztautau_btag_c16d_350GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16d_400GeV                = (TTree*)input_Ztautau_btag_c16d_400GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16d_500GeV                = (TTree*)input_Ztautau_btag_c16d_500GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16d_600GeV                = (TTree*)input_Ztautau_btag_c16d_600GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16d_700GeV                = (TTree*)input_Ztautau_btag_c16d_700GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16d_800GeV                = (TTree*)input_Ztautau_btag_c16d_800GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16d_1200GeV                = (TTree*)input_Ztautau_btag_c16d_1200GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16d_1500GeV                = (TTree*)input_Ztautau_btag_c16d_1500GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16d_2000GeV                = (TTree*)input_Ztautau_btag_c16d_2000GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16d_2500GeV                = (TTree*)input_Ztautau_btag_c16d_2500GeV->Get("NOMINAL");

    TTree *bkgTree_Ztautau_btag_c16e_200GeV                = (TTree*)input_Ztautau_btag_c16e_200GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16e_250GeV                = (TTree*)input_Ztautau_btag_c16e_250GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16e_300GeV                = (TTree*)input_Ztautau_btag_c16e_300GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16e_350GeV                = (TTree*)input_Ztautau_btag_c16e_350GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16e_400GeV                = (TTree*)input_Ztautau_btag_c16e_400GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16e_500GeV                = (TTree*)input_Ztautau_btag_c16e_500GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16e_600GeV                = (TTree*)input_Ztautau_btag_c16e_600GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16e_700GeV                = (TTree*)input_Ztautau_btag_c16e_700GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16e_800GeV                = (TTree*)input_Ztautau_btag_c16e_800GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16e_1200GeV                = (TTree*)input_Ztautau_btag_c16e_1200GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16e_1500GeV                = (TTree*)input_Ztautau_btag_c16e_1500GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16e_2000GeV                = (TTree*)input_Ztautau_btag_c16e_2000GeV->Get("NOMINAL");
    TTree *bkgTree_Ztautau_btag_c16e_2500GeV                = (TTree*)input_Ztautau_btag_c16e_2500GeV->Get("NOMINAL");


    TTree *bkgTree_FakesID_btag_c16a_200GeV                = (TTree*)input_FakesID_btag_c16a_200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16a_250GeV                = (TTree*)input_FakesID_btag_c16a_250GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16a_300GeV                = (TTree*)input_FakesID_btag_c16a_300GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16a_350GeV                = (TTree*)input_FakesID_btag_c16a_350GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16a_400GeV                = (TTree*)input_FakesID_btag_c16a_400GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16a_500GeV                = (TTree*)input_FakesID_btag_c16a_500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16a_600GeV                = (TTree*)input_FakesID_btag_c16a_600GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16a_700GeV                = (TTree*)input_FakesID_btag_c16a_700GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16a_800GeV                = (TTree*)input_FakesID_btag_c16a_800GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16a_1200GeV                = (TTree*)input_FakesID_btag_c16a_1200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16a_1500GeV                = (TTree*)input_FakesID_btag_c16a_1500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16a_2000GeV                = (TTree*)input_FakesID_btag_c16a_2000GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16a_2500GeV                = (TTree*)input_FakesID_btag_c16a_2500GeV->Get("NOMINAL");

    TTree *bkgTree_FakesID_btag_c16d_200GeV                = (TTree*)input_FakesID_btag_c16d_200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16d_250GeV                = (TTree*)input_FakesID_btag_c16d_250GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16d_300GeV                = (TTree*)input_FakesID_btag_c16d_300GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16d_350GeV                = (TTree*)input_FakesID_btag_c16d_350GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16d_400GeV                = (TTree*)input_FakesID_btag_c16d_400GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16d_500GeV                = (TTree*)input_FakesID_btag_c16d_500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16d_600GeV                = (TTree*)input_FakesID_btag_c16d_600GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16d_700GeV                = (TTree*)input_FakesID_btag_c16d_700GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16d_800GeV                = (TTree*)input_FakesID_btag_c16d_800GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16d_1200GeV                = (TTree*)input_FakesID_btag_c16d_1200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16d_1500GeV                = (TTree*)input_FakesID_btag_c16d_1500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16d_2000GeV                = (TTree*)input_FakesID_btag_c16d_2000GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16d_2500GeV                = (TTree*)input_FakesID_btag_c16d_2500GeV->Get("NOMINAL");

    TTree *bkgTree_FakesID_btag_c16e_200GeV                = (TTree*)input_FakesID_btag_c16e_200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16e_250GeV                = (TTree*)input_FakesID_btag_c16e_250GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16e_300GeV                = (TTree*)input_FakesID_btag_c16e_300GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16e_350GeV                = (TTree*)input_FakesID_btag_c16e_350GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16e_400GeV                = (TTree*)input_FakesID_btag_c16e_400GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16e_500GeV                = (TTree*)input_FakesID_btag_c16e_500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16e_600GeV                = (TTree*)input_FakesID_btag_c16e_600GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16e_700GeV                = (TTree*)input_FakesID_btag_c16e_700GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16e_800GeV                = (TTree*)input_FakesID_btag_c16e_800GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16e_1200GeV                = (TTree*)input_FakesID_btag_c16e_1200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16e_1500GeV                = (TTree*)input_FakesID_btag_c16e_1500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16e_2000GeV                = (TTree*)input_FakesID_btag_c16e_2000GeV->Get("NOMINAL");
    TTree *bkgTree_FakesID_btag_c16e_2500GeV                = (TTree*)input_FakesID_btag_c16e_2500GeV->Get("NOMINAL");


    TTree *bkgTree_FakesISO_btag_c16a_200GeV                = (TTree*)input_FakesISO_btag_c16a_200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16a_250GeV                = (TTree*)input_FakesISO_btag_c16a_250GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16a_300GeV                = (TTree*)input_FakesISO_btag_c16a_300GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16a_350GeV                = (TTree*)input_FakesISO_btag_c16a_350GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16a_400GeV                = (TTree*)input_FakesISO_btag_c16a_400GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16a_500GeV                = (TTree*)input_FakesISO_btag_c16a_500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16a_600GeV                = (TTree*)input_FakesISO_btag_c16a_600GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16a_700GeV                = (TTree*)input_FakesISO_btag_c16a_700GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16a_800GeV                = (TTree*)input_FakesISO_btag_c16a_800GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16a_1200GeV                = (TTree*)input_FakesISO_btag_c16a_1200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16a_1500GeV                = (TTree*)input_FakesISO_btag_c16a_1500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16a_2000GeV                = (TTree*)input_FakesISO_btag_c16a_2000GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16a_2500GeV                = (TTree*)input_FakesISO_btag_c16a_2500GeV->Get("NOMINAL");

    TTree *bkgTree_FakesISO_btag_c16d_200GeV                = (TTree*)input_FakesISO_btag_c16d_200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16d_250GeV                = (TTree*)input_FakesISO_btag_c16d_250GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16d_300GeV                = (TTree*)input_FakesISO_btag_c16d_300GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16d_350GeV                = (TTree*)input_FakesISO_btag_c16d_350GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16d_400GeV                = (TTree*)input_FakesISO_btag_c16d_400GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16d_500GeV                = (TTree*)input_FakesISO_btag_c16d_500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16d_600GeV                = (TTree*)input_FakesISO_btag_c16d_600GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16d_700GeV                = (TTree*)input_FakesISO_btag_c16d_700GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16d_800GeV                = (TTree*)input_FakesISO_btag_c16d_800GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16d_1200GeV                = (TTree*)input_FakesISO_btag_c16d_1200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16d_1500GeV                = (TTree*)input_FakesISO_btag_c16d_1500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16d_2000GeV                = (TTree*)input_FakesISO_btag_c16d_2000GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16d_2500GeV                = (TTree*)input_FakesISO_btag_c16d_2500GeV->Get("NOMINAL");

    TTree *bkgTree_FakesISO_btag_c16e_200GeV                = (TTree*)input_FakesISO_btag_c16e_200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16e_250GeV                = (TTree*)input_FakesISO_btag_c16e_250GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16e_300GeV                = (TTree*)input_FakesISO_btag_c16e_300GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16e_350GeV                = (TTree*)input_FakesISO_btag_c16e_350GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16e_400GeV                = (TTree*)input_FakesISO_btag_c16e_400GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16e_500GeV                = (TTree*)input_FakesISO_btag_c16e_500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16e_600GeV                = (TTree*)input_FakesISO_btag_c16e_600GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16e_700GeV                = (TTree*)input_FakesISO_btag_c16e_700GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16e_800GeV                = (TTree*)input_FakesISO_btag_c16e_800GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16e_1200GeV                = (TTree*)input_FakesISO_btag_c16e_1200GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16e_1500GeV                = (TTree*)input_FakesISO_btag_c16e_1500GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16e_2000GeV                = (TTree*)input_FakesISO_btag_c16e_2000GeV->Get("NOMINAL");
    TTree *bkgTree_FakesISO_btag_c16e_2500GeV                = (TTree*)input_FakesISO_btag_c16e_2500GeV->Get("NOMINAL");


    TTree *bkgTree_top_single_btag_c16a_200GeV                = (TTree*)input_top_single_btag_c16a_200GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16a_250GeV                = (TTree*)input_top_single_btag_c16a_250GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16a_300GeV                = (TTree*)input_top_single_btag_c16a_300GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16a_350GeV                = (TTree*)input_top_single_btag_c16a_350GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16a_400GeV                = (TTree*)input_top_single_btag_c16a_400GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16a_500GeV                = (TTree*)input_top_single_btag_c16a_500GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16a_600GeV                = (TTree*)input_top_single_btag_c16a_600GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16a_700GeV                = (TTree*)input_top_single_btag_c16a_700GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16a_800GeV                = (TTree*)input_top_single_btag_c16a_800GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16a_1200GeV                = (TTree*)input_top_single_btag_c16a_1200GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16a_1500GeV                = (TTree*)input_top_single_btag_c16a_1500GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16a_2000GeV                = (TTree*)input_top_single_btag_c16a_2000GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16a_2500GeV                = (TTree*)input_top_single_btag_c16a_2500GeV->Get("NOMINAL");

    TTree *bkgTree_top_single_btag_c16d_200GeV                = (TTree*)input_top_single_btag_c16d_200GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16d_250GeV                = (TTree*)input_top_single_btag_c16d_250GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16d_300GeV                = (TTree*)input_top_single_btag_c16d_300GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16d_350GeV                = (TTree*)input_top_single_btag_c16d_350GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16d_400GeV                = (TTree*)input_top_single_btag_c16d_400GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16d_500GeV                = (TTree*)input_top_single_btag_c16d_500GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16d_600GeV                = (TTree*)input_top_single_btag_c16d_600GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16d_700GeV                = (TTree*)input_top_single_btag_c16d_700GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16d_800GeV                = (TTree*)input_top_single_btag_c16d_800GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16d_1200GeV                = (TTree*)input_top_single_btag_c16d_1200GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16d_1500GeV                = (TTree*)input_top_single_btag_c16d_1500GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16d_2000GeV                = (TTree*)input_top_single_btag_c16d_2000GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16d_2500GeV                = (TTree*)input_top_single_btag_c16d_2500GeV->Get("NOMINAL");

    TTree *bkgTree_top_single_btag_c16e_200GeV                = (TTree*)input_top_single_btag_c16e_200GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16e_250GeV                = (TTree*)input_top_single_btag_c16e_250GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16e_300GeV                = (TTree*)input_top_single_btag_c16e_300GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16e_350GeV                = (TTree*)input_top_single_btag_c16e_350GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16e_400GeV                = (TTree*)input_top_single_btag_c16e_400GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16e_500GeV                = (TTree*)input_top_single_btag_c16e_500GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16e_600GeV                = (TTree*)input_top_single_btag_c16e_600GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16e_700GeV                = (TTree*)input_top_single_btag_c16e_700GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16e_800GeV                = (TTree*)input_top_single_btag_c16e_800GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16e_1200GeV                = (TTree*)input_top_single_btag_c16e_1200GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16e_1500GeV                = (TTree*)input_top_single_btag_c16e_1500GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16e_2000GeV                = (TTree*)input_top_single_btag_c16e_2000GeV->Get("NOMINAL");
    TTree *bkgTree_top_single_btag_c16e_2500GeV                = (TTree*)input_top_single_btag_c16e_2500GeV->Get("NOMINAL");


    TTree *bkgTree_top_ttbar_btag_c16a_200GeV                = (TTree*)input_top_ttbar_btag_c16a_200GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16a_250GeV                = (TTree*)input_top_ttbar_btag_c16a_250GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16a_300GeV                = (TTree*)input_top_ttbar_btag_c16a_300GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16a_350GeV                = (TTree*)input_top_ttbar_btag_c16a_350GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16a_400GeV                = (TTree*)input_top_ttbar_btag_c16a_400GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16a_500GeV                = (TTree*)input_top_ttbar_btag_c16a_500GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16a_600GeV                = (TTree*)input_top_ttbar_btag_c16a_600GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16a_700GeV                = (TTree*)input_top_ttbar_btag_c16a_700GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16a_800GeV                = (TTree*)input_top_ttbar_btag_c16a_800GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16a_1200GeV                = (TTree*)input_top_ttbar_btag_c16a_1200GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16a_1500GeV                = (TTree*)input_top_ttbar_btag_c16a_1500GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16a_2000GeV                = (TTree*)input_top_ttbar_btag_c16a_2000GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16a_2500GeV                = (TTree*)input_top_ttbar_btag_c16a_2500GeV->Get("NOMINAL");

    TTree *bkgTree_top_ttbar_btag_c16d_200GeV                = (TTree*)input_top_ttbar_btag_c16d_200GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16d_250GeV                = (TTree*)input_top_ttbar_btag_c16d_250GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16d_300GeV                = (TTree*)input_top_ttbar_btag_c16d_300GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16d_350GeV                = (TTree*)input_top_ttbar_btag_c16d_350GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16d_400GeV                = (TTree*)input_top_ttbar_btag_c16d_400GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16d_500GeV                = (TTree*)input_top_ttbar_btag_c16d_500GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16d_600GeV                = (TTree*)input_top_ttbar_btag_c16d_600GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16d_700GeV                = (TTree*)input_top_ttbar_btag_c16d_700GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16d_800GeV                = (TTree*)input_top_ttbar_btag_c16d_800GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16d_1200GeV                = (TTree*)input_top_ttbar_btag_c16d_1200GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16d_1500GeV                = (TTree*)input_top_ttbar_btag_c16d_1500GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16d_2000GeV                = (TTree*)input_top_ttbar_btag_c16d_2000GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16d_2500GeV                = (TTree*)input_top_ttbar_btag_c16d_2500GeV->Get("NOMINAL");

    TTree *bkgTree_top_ttbar_btag_c16e_200GeV                = (TTree*)input_top_ttbar_btag_c16e_200GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16e_250GeV                = (TTree*)input_top_ttbar_btag_c16e_250GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16e_300GeV                = (TTree*)input_top_ttbar_btag_c16e_300GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16e_350GeV                = (TTree*)input_top_ttbar_btag_c16e_350GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16e_400GeV                = (TTree*)input_top_ttbar_btag_c16e_400GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16e_500GeV                = (TTree*)input_top_ttbar_btag_c16e_500GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16e_600GeV                = (TTree*)input_top_ttbar_btag_c16e_600GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16e_700GeV                = (TTree*)input_top_ttbar_btag_c16e_700GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16e_800GeV                = (TTree*)input_top_ttbar_btag_c16e_800GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16e_1200GeV                = (TTree*)input_top_ttbar_btag_c16e_1200GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16e_1500GeV                = (TTree*)input_top_ttbar_btag_c16e_1500GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16e_2000GeV                = (TTree*)input_top_ttbar_btag_c16e_2000GeV->Get("NOMINAL");
    TTree *bkgTree_top_ttbar_btag_c16e_2500GeV                = (TTree*)input_top_ttbar_btag_c16e_2500GeV->Get("NOMINAL");












 
    // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
    TString outfileName( "TMVA_PNN.root" );
    TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
 



    TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                                "!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );
//                                                "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
 
    TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset_bveto_PNN_201215_200-2500GeV_kfold");
    //TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset_test_new");

	//mass vars
    dataloader->AddVariable( "MTtot", "MTtot", "GeV", 'I' ); //all
    dataloader->AddVariable("vis_mass","vis_mass","GeV",'I'); //all
    dataloader->AddVariable("lephad_mmc_maxw_m","lephad_mmc_maxw_m","GeV",'I'); //all
    //dataloader->AddVariable("lephad_mmc_mlm_m/signal_mass","lephad_mmc_mlm_m/signal_mass","GeV",'F'); //all
    //dataloader->AddVariable("lephad_coll_approx_m","lephad_coll_approx_m","GeV",'I');
    //dataloader->AddVariable("pow((pow(tau_e+lep_e+MET,2)-pow(tau_px+lep_px+(MET_px - (MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_px)/lep_px*lep_px+(MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_px,2)-pow(tau_py+lep_py+(MET_px - (MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_px)/lep_px*lep_py+(MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_py,2)),0.5)","collApprox","GeV",'F');
    dataloader->AddVariable("pow((pow(tau_e+lep_e+pow(pow((MET_px - (MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_px)/lep_px*lep_px,2)+pow((MET_px - (MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_px)/lep_px*lep_py,2)+pow((MET_px - (MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_px)/lep_px*lep_pz,2),0.5)+pow(pow((MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_px,2)+pow((MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_py,2)+pow((MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_pz,2),0.5),2)-pow(tau_px+lep_px+(MET_px - (MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_px)/lep_px*lep_px+(MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_px,2)-pow(tau_py+lep_py+(MET_px - (MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_px)/lep_px*lep_py+(MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_py,2)-pow(tau_pz+lep_pz+(MET_px - (MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_px)/lep_px*lep_pz+(MET_py - MET_px*lep_py/lep_px)/(1-tau_px*lep_py/lep_px)*tau_pz,2)),0.5)","collApprox","GeV",'F')

	//4-vectors
    dataloader->AddVariable("tau_pt","tau_pt","GeV",'I'); //all
    //dataloader->AddVariable("lep_pt","lep_pt","GeV",'I'); //tcr
    //dataloader->AddVariable("lep_px","lep_px","GeV",'I');
    //dataloader->AddVariable("tau_px","tau_px","GeV",'I');
    //dataloader->AddVariable("lep_py","lep_py","GeV",'I');
    //dataloader->AddVariable("tau_py","tau_py","GeV",'I');
    //dataloader->AddVariable("lep_pz","lep_pz","GeV",'I');
    //dataloader->AddVariable("tau_pz","tau_pz","GeV",'I');
    //dataloader->AddVariable("lep_phi","lep_phi","GeV",'I'); //tcr
    //dataloader->AddVariable("tau_phi","tau_phi","GeV",'I'); //tcr
    //dataloader->AddVariable("lep_eta","lep_eta",'I'); //tcr
    //dataloader->AddVariable("tau_eta","tau_eta",'I'); //tcr
    //dataloader->AddVariable("MET","MET","GeV",'F'); //btag
    //dataloader->AddVariable("MET_px","MET_px","GeV",'I');
    //dataloader->AddVariable("MET_py","MET_py","GeV",'I');
    //dataloader->AddVariable("MET_phi","MET_phi","GeV",'I');

	//differences
    //dataloader->AddVariable("(lep_pt-tau_pt)/(lep_pt+tau_pt)","GeV",'F');
    //dataloader->AddVariable("lep_phi-tau_phi","lep_phi-tau_phi","GeV",'F'); //btag, tcr
    ////dataloader->AddVariable("lep_phi-MET_phi","GeV",'F');
    ////dataloader->AddVariable("lephad_dphi","lephad_dphi",'F');
    ////dataloader->AddVariable("lephad_met_lep0_cos_dphi","lephad_met_lep0_cos_dphi",'F');
    ////dataloader->AddVariable("lephad_met_lep1_cos_dphi","lephad_met_lep1_cos_dphi",'F');

	//b-jet vars
    //dataloader->AddVariable("bjet_e","bjet_e","GeV",'I');
    //dataloader->AddVariable("bjet_pt","bjet_pt","GeV",'I'); //btag, tcr
    ////dataloader->AddVariable("bjet_px","bjet_px","GeV",'I');
    ////dataloader->AddVariable("bjet_py","bjet_py","GeV",'I');
    ////dataloader->AddVariable("bjet_pz","bjet_pz","GeV",'I');
    //dataloader->AddVariable("bjet_phi","bjet_phi",'F'); //btag, tcr
    //dataloader->AddVariable("bjet_eta","bjet_eta",'F'); //btag, tcr
    ////dataloader->AddVariable("bjet_pt+MET+tau_pt+lep_pt","PTtot","GeV",'I');
    //dataloader->AddVariable("bjet_eta-lep_eta","dEta(jet,lep)","",'F'); //btag, tcr
    //dataloader->AddVariable("fabs(bjet_phi-lep_phi)","dPhi(jet,lep)","",'F');
    //dataloader->AddVariable("fabs(bjet_phi-tau_phi)","dPhi(jet,tau)","",'F');
    //dataloader->AddVariable("bjet_eta-tau_eta","dEta(jet,tau)","",'F'); //btag, tcr
    //dataloader->AddVariable("fabs(bjet_eta-MET_eta)","dEta(jet,met)","",'F');
    //dataloader->AddVariable("pow(MET+bjet_pt+tau_pt+lep_pt,2)-pow(MET_px+bjet_px+tau_px+lep_px,2)-pow(MET_py+bjet_py+tau_py+lep_py,2)","m(lep,tau,bjet,met)","GeV",'F');
    //dataloader->AddVariable("bjet_0_q","bjet_0_q","",'F');
    //dataloader->AddVariable("bjet_0_width","bjet_0_width","",'F');
    dataloader->AddVariable("signal_mass","signal_mass","",'I');


   





    dataloader->AddSpectator("MTtot","MTtot","",'F');


    //k-folding
    /*int numFolds = 5;
    //TString splitExpr = "";
    TString splitExpr = "int(fabs([MTtot]*10.))%5";
    //TString splitExpr = "int([event_number])%2";
    TString cvOptions = Form("!V"
                     ":DrawProgressBar"
                     ":ModelPersistence"
                     ":AnalysisType=Classification"
                     ":SplitType=Deterministic"
                     ":NumFolds=%i"
                     ":SplitExpr=%s",
                     numFolds, splitExpr.Data());
    cout << cvOptions << endl;
    TMVA::CrossValidation cv {"TMVACrossValidation", dataloader, outputFile, cvOptions};*/


 
 
    // global event weights per tree (see below for setting event-wise weights)
    Double_t signalWeight = 1.0; //pow(signal_mass/2500,2)+1.0;
    //Double_t bkgWeight1 = 1.0;
 
    // You can add an arbitrary number of signal or background trees

    // PNN - here the signal mass distribution was kept flat, so samples are normalized to the number of weighted events
	//**********bveto***************
	dataloader->AddSignalTree(signalTree_ggH_c16a_200GeV, signalWeight/890.97);
	dataloader->AddSignalTree(signalTree_ggH_c16d_200GeV, signalWeight/1032.17);
	dataloader->AddSignalTree(signalTree_ggH_c16e_200GeV, signalWeight/1370.52);

	dataloader->AddSignalTree(signalTree_ggH_c16a_250GeV, signalWeight/1268.54);
	dataloader->AddSignalTree(signalTree_ggH_c16d_250GeV, signalWeight/1469.79);
	dataloader->AddSignalTree(signalTree_ggH_c16e_250GeV, signalWeight/1990.42);

	dataloader->AddSignalTree(signalTree_ggH_c16a_300GeV, signalWeight/1599.52);
	dataloader->AddSignalTree(signalTree_ggH_c16d_300GeV, signalWeight/1891.05);
	dataloader->AddSignalTree(signalTree_ggH_c16e_300GeV, signalWeight/2526.52);

	dataloader->AddSignalTree(signalTree_ggH_c16a_350GeV, signalWeight/1870.24);
	dataloader->AddSignalTree(signalTree_ggH_c16d_350GeV, signalWeight/2208.98);
	dataloader->AddSignalTree(signalTree_ggH_c16e_350GeV, signalWeight/2935.52);

	dataloader->AddSignalTree(signalTree_ggH_c16a_400GeV, signalWeight/2089.09);
	dataloader->AddSignalTree(signalTree_ggH_c16d_400GeV, signalWeight/2404.42);
	dataloader->AddSignalTree(signalTree_ggH_c16e_400GeV, signalWeight/3293.09);

	dataloader->AddSignalTree(signalTree_ggH_c16a_500GeV, signalWeight/2325.48);
	dataloader->AddSignalTree(signalTree_ggH_c16d_500GeV, signalWeight/2721.67);
	dataloader->AddSignalTree(signalTree_ggH_c16e_500GeV, signalWeight/3600.95);

	dataloader->AddSignalTree(signalTree_ggH_c16a_600GeV, signalWeight/2374.13);
	dataloader->AddSignalTree(signalTree_ggH_c16d_600GeV, signalWeight/2818.31);
	dataloader->AddSignalTree(signalTree_ggH_c16e_600GeV, signalWeight/3779.38);

	dataloader->AddSignalTree(signalTree_ggH_c16a_700GeV, signalWeight/2459.13);
	dataloader->AddSignalTree(signalTree_ggH_c16d_700GeV, signalWeight/2848.02);
	dataloader->AddSignalTree(signalTree_ggH_c16e_700GeV, signalWeight/3737.0);

	dataloader->AddSignalTree(signalTree_ggH_c16a_800GeV, signalWeight/2495.29);
	dataloader->AddSignalTree(signalTree_ggH_c16d_800GeV, signalWeight/2864.03);
	dataloader->AddSignalTree(signalTree_ggH_c16e_800GeV, signalWeight/3746.27);

	dataloader->AddSignalTree(signalTree_ggH_c16a_1200GeV, signalWeight/2201.08);
	dataloader->AddSignalTree(signalTree_ggH_c16d_1200GeV, signalWeight/2567.48);
	dataloader->AddSignalTree(signalTree_ggH_c16e_1200GeV, signalWeight/3355.05);

	dataloader->AddSignalTree(signalTree_ggH_c16a_1500GeV, signalWeight/2012.42);
	dataloader->AddSignalTree(signalTree_ggH_c16d_1500GeV, signalWeight/2325.43);
	dataloader->AddSignalTree(signalTree_ggH_c16e_1500GeV, signalWeight/3075.23);

	dataloader->AddSignalTree(signalTree_ggH_c16a_2000GeV, signalWeight/1719.79);
	dataloader->AddSignalTree(signalTree_ggH_c16d_2000GeV, signalWeight/1973.25);
	dataloader->AddSignalTree(signalTree_ggH_c16e_2000GeV, signalWeight/2585.51);

	dataloader->AddSignalTree(signalTree_ggH_c16a_2500GeV, signalWeight/1474.08);
	dataloader->AddSignalTree(signalTree_ggH_c16d_2500GeV, signalWeight/1741.63);
	dataloader->AddSignalTree(signalTree_ggH_c16e_2500GeV, signalWeight/2324.65);


	dataloader->AddSignalTree(signalTree_bbH_c16a_200GeV, signalWeight/676.55);
	dataloader->AddSignalTree(signalTree_bbH_c16d_200GeV, signalWeight/839.92);
	dataloader->AddSignalTree(signalTree_bbH_c16e_200GeV, signalWeight/1066.69);

	dataloader->AddSignalTree(signalTree_bbH_c16a_250GeV, signalWeight/944.42);
	dataloader->AddSignalTree(signalTree_bbH_c16d_250GeV, signalWeight/1075.65);
	dataloader->AddSignalTree(signalTree_bbH_c16e_250GeV, signalWeight/1466.19);

	dataloader->AddSignalTree(signalTree_bbH_c16a_300GeV, signalWeight/1155.98);
	dataloader->AddSignalTree(signalTree_bbH_c16d_300GeV, signalWeight/1328.41);
	dataloader->AddSignalTree(signalTree_bbH_c16e_300GeV, signalWeight/1706.0);

	dataloader->AddSignalTree(signalTree_bbH_c16a_350GeV, signalWeight/1247.94);
	dataloader->AddSignalTree(signalTree_bbH_c16d_350GeV, signalWeight/1515.47);
	dataloader->AddSignalTree(signalTree_bbH_c16e_350GeV, signalWeight/1983.22);

	dataloader->AddSignalTree(signalTree_bbH_c16a_400GeV, signalWeight/1360.79);
	dataloader->AddSignalTree(signalTree_bbH_c16d_400GeV, signalWeight/1599.1);
	dataloader->AddSignalTree(signalTree_bbH_c16e_400GeV, signalWeight/2153.87);

	dataloader->AddSignalTree(signalTree_bbH_c16a_500GeV, signalWeight/1416.31);
	dataloader->AddSignalTree(signalTree_bbH_c16d_500GeV, signalWeight/1699.64);
	dataloader->AddSignalTree(signalTree_bbH_c16e_500GeV, signalWeight/2172.19);

	dataloader->AddSignalTree(signalTree_bbH_c16a_600GeV, signalWeight/1543.45);
	dataloader->AddSignalTree(signalTree_bbH_c16d_600GeV, signalWeight/1805.79);
	dataloader->AddSignalTree(signalTree_bbH_c16e_600GeV, signalWeight/2419.28);

	dataloader->AddSignalTree(signalTree_bbH_c16a_700GeV, signalWeight/1421.42);
	dataloader->AddSignalTree(signalTree_bbH_c16d_700GeV, signalWeight/1743.38);
	dataloader->AddSignalTree(signalTree_bbH_c16e_700GeV, signalWeight/2377.0);

	dataloader->AddSignalTree(signalTree_bbH_c16a_800GeV, signalWeight/1447.12);
	dataloader->AddSignalTree(signalTree_bbH_c16d_800GeV, signalWeight/1722.12);
	dataloader->AddSignalTree(signalTree_bbH_c16e_800GeV, signalWeight/2339.25);

	dataloader->AddSignalTree(signalTree_bbH_c16a_1200GeV, signalWeight/1413.65);
	dataloader->AddSignalTree(signalTree_bbH_c16d_1200GeV, signalWeight/1536.24);
	dataloader->AddSignalTree(signalTree_bbH_c16e_1200GeV, signalWeight/2099.87);

	dataloader->AddSignalTree(signalTree_bbH_c16a_1500GeV, signalWeight/1317.53);
	dataloader->AddSignalTree(signalTree_bbH_c16d_1500GeV, signalWeight/1400.47);
	dataloader->AddSignalTree(signalTree_bbH_c16e_1500GeV, signalWeight/1970.32);

	dataloader->AddSignalTree(signalTree_bbH_c16a_2000GeV, signalWeight/1053.71);
	dataloader->AddSignalTree(signalTree_bbH_c16d_2000GeV, signalWeight/1163.11);
	dataloader->AddSignalTree(signalTree_bbH_c16e_2000GeV, signalWeight/1665.87);

	dataloader->AddSignalTree(signalTree_bbH_c16a_2500GeV, signalWeight/957.16);
	dataloader->AddSignalTree(signalTree_bbH_c16d_2500GeV, signalWeight/1129.97);
	dataloader->AddSignalTree(signalTree_bbH_c16e_2500GeV, signalWeight/1405.39);


	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_200GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_250GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_250GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_250GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_300GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_300GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_300GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_350GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_350GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_350GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_400GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_400GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_400GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_500GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_600GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_600GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_600GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_700GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_700GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_700GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_800GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_800GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_800GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_1200GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_1200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_1200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_1500GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_1500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_1500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_2000GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_2000GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_2000GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_c16a_2500GeV, signalWeight);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16d_2500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Ztautau_c16e_2500GeV, 1.0);*/


	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_250GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_250GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_250GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_300GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_300GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_300GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_350GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_350GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_350GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_400GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_400GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_400GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_600GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_600GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_600GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_700GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_700GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_700GeV, 1.0);*/

	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_800GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_800GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_800GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_1200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_1200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_1200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_1500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_1500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_1500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_2000GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_2000GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_2000GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Zll_c16a_2500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16d_2500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_Zll_c16e_2500GeV, 1.0);


	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_250GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_250GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_250GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_300GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_300GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_300GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_350GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_350GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_350GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_400GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_400GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_400GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_600GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_600GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_600GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_700GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_700GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_700GeV, 1.0);*/

	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_800GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_800GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_800GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_1200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_1200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_1200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_1500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_1500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_1500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_2000GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_2000GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_2000GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_c16a_2500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16d_2500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesID_c16e_2500GeV, 1.0);


	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_250GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_250GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_250GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_300GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_300GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_300GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_350GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_350GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_350GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_400GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_400GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_400GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_600GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_600GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_600GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_700GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_700GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_700GeV, 1.0);*/

	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_800GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_800GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_800GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_1200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_1200GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_1200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_1500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_1500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_1500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_2000GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_2000GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_2000GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_c16a_2500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16d_2500GeV, 1.0);
	//dataloader->AddBackgroundTree(bkgTree_FakesISO_c16e_2500GeV, 1.0);*/





	//**************btag*********************
	/*dataloader->AddSignalTree(signalTree_ggH_btag_c16a_200GeV, 1.0/850);//795.56); //(221.805+5.3));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_200GeV, 1.0/850);//795.56); //(278.63+10.42));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16e_200GeV, 1.0/850);//795.56); //(333.79+14.25));

	dataloader->AddSignalTree(signalTree_ggH_btag_c16a_250GeV, 1.0/1400);//1392.05);//(369.48+12.16));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_250GeV, 1.0/1400);//1392.05);//(392.49+16.6));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16e_250GeV, 1.0/1400);//1392.05);//(567.6+21.88));

	dataloader->AddSignalTree(signalTree_ggH_btag_c16a_300GeV, 1.0/2000);//1931.23);//(501.07+14.94));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_300GeV, 1.0/2000);//1931.23);//(526.1+22.33));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16e_300GeV, 1.0/2000);//1931.23);//(718.11+32.77));

	dataloader->AddSignalTree(signalTree_ggH_btag_c16a_350GeV, 1.0/2444.69);//(604.33+19.43));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_350GeV, 1.0/2444.69);//(683.7+27.34));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16e_350GeV, 1.0/2444.69);//(880.58+37.7));

	dataloader->AddSignalTree(signalTree_ggH_btag_c16a_400GeV, 1.0/2831.28);//(700+24.63));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_400GeV, 1.0/2831.28);//(805.29+28.57));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16e_400GeV, 1.0/2831.28);//(991.97+39.55));

	dataloader->AddSignalTree(signalTree_ggH_btag_c16a_500GeV, 1.0/3364.76);//(825+30.5));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_500GeV, 1.0/3364.76);//(918.83+38.18));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16e_500GeV, 1.0/3364.76);//(1172.78+48.1));

	dataloader->AddSignalTree(signalTree_ggH_btag_c16a_600GeV, 1.0/3824.85);//(910+30.56));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_600GeV, 1.0/3824.85);//(1025.12+39.51));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16e_600GeV, 1.0/3824.85);//(1369.79+59.36));

	dataloader->AddSignalTree(signalTree_ggH_btag_c16a_700GeV, 1.0/4111.38);//(1000+36.57));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_700GeV, 1.0/4111.38);//(1031.25+51.45));
        dataloader->AddSignalTree(signalTree_ggH_btag_c16e_700GeV, 1.0/4111.38);//(1388.2+66.5));

	dataloader->AddSignalTree(signalTree_ggH_btag_c16a_800GeV, 1.0/4015.3);//(980+36.29));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_800GeV, 1.0/4015.3);//(1084.09+53.74));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16e_800GeV, 1.0/4015.3);//(1467.04+62.51));

	dataloader->AddSignalTree(signalTree_ggH_btag_c16a_1200GeV, 1.0/4036.45);//(950+48.24));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_1200GeV, 1.0/4036.45);//(1058.94+58.28));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16e_1200GeV, 1.0/4036.45);//(1309.04+76.05));

	dataloader->AddSignalTree(signalTree_ggH_btag_c16a_1500GeV, 1.0/3781.96);//(900+45.8));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_1500GeV, 1.0/3781.96);//(856.46+50.74));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16e_1500GeV, 1.0/3781.96);//(1349.36+73.1));

	dataloader->AddSignalTree(signalTree_ggH_btag_c16a_2000GeV, 1.0/3363.73);//(780+49.55));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_2000GeV, 1.0/3363.73);//(805.27+56.94));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16e_2000GeV, 1.0/3363.73);//(1160.38+80.44));

	dataloader->AddSignalTree(signalTree_ggH_btag_c16a_2500GeV, 1.0/2942.16);//(720+40.37));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16d_2500GeV, 1.0/2942.16);//(760.76+53.68));
	dataloader->AddSignalTree(signalTree_ggH_btag_c16e_2500GeV, 1.0/2942.16);//(965.54+67.05));


	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_200GeV, 1.0/850);//795.56);//221.805);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_200GeV, 1.0/850);//795.56);//278.63);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_200GeV, 1.0/850);//795.56);//333.79);

	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_250GeV, 1.0/1400);//1392.05);//369.48);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_250GeV, 1.0/1400);//1392.05);//392.49);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_250GeV, 1.0/1400);//1392.05);//567.6);

	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_300GeV, 1.0/2000);//1931.23);//501.07);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_300GeV, 1.0/2000);//1931.23);//526.1);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_300GeV, 1.0/2000);//1931.23);//718.11);

	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_350GeV, 1.0/2444.69);//604.33);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_350GeV, 1.0/2444.69);//683.7);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_350GeV, 1.0/2444.69);//880.58);

	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_400GeV, 1.0/2831.28);//700); //666.08);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_400GeV, 1.0/2831.28);//805.29);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_400GeV, 1.0/2831.28);//991.97);

	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_500GeV, 1.0/3364.76);//825);//772.18);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_500GeV, 1.0/3364.76);//918.83);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_500GeV, 1.0/3364.76);//1172.78);

	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_600GeV, 1.0/3824.85);//910);//824.38);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_600GeV, 1.0/3824.85);//1025.12);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_600GeV, 1.0/3824.85);//1369.79);

	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_700GeV, 1.0/4111.38);//1000);//924.96);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_700GeV, 1.0/4111.38);//1031.25);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_700GeV, 1.0/4111.38);//1388.2);

	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_800GeV, 1.0/4015.3);//980);//888.84);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_800GeV, 1.0/4015.3);//1084.09);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_800GeV, 1.0/4015.3);//1467.04);

	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_1200GeV, 1.0/4036.45);//950); //790.63);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_1200GeV, 1.0/4036.45);//1058.94);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_1200GeV, 1.0/4036.45);//1309.04);

	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_1500GeV, 1.0/3781.96);//900);//781.24);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_1500GeV, 1.0/3781.96);//856.46);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_1500GeV, 1.0/3781.96);//1349.36);

	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_2000GeV, 1.0/3363.73);//780);//709.53);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_2000GeV, 1.0/3363.73);//805.27);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_2000GeV, 1.0/3363.73);//1160.38);

	dataloader->AddSignalTree(signalTree_bbH_btag_c16a_2500GeV, 1.0/2942.16);//720);//681.16);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16d_2500GeV, 1.0/2942.16);//760.76);
	dataloader->AddSignalTree(signalTree_bbH_btag_c16e_2500GeV, 1.0/2942.16);//965.54);




	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_250GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_250GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_250GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_300GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_300GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_300GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_350GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_350GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_350GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_400GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_400GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_400GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_600GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_600GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_600GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_700GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_700GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_700GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_800GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_800GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_800GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_1200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_1200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_1200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_1500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_1500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_1500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_2000GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_2000GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_2000GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16a_2500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16d_2500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_single_btag_c16e_2500GeV, 1.0);


	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_250GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_250GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_250GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_300GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_300GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_300GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_350GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_350GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_350GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_400GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_400GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_400GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_600GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_600GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_600GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_700GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_700GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_700GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_800GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_800GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_800GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_1200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_1200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_1200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_1500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_1500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_1500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_2000GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_2000GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_2000GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16a_2500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16d_2500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_top_ttbar_btag_c16e_2500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_250GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_250GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_250GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_300GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_300GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_300GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_350GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_350GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_350GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_400GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_400GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_400GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_600GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_600GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_600GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_700GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_700GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_700GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_800GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_800GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_800GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_1200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_1200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_1200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_1500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_1500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_1500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_2000GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_2000GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_2000GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16a_2500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16d_2500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_Ztautau_btag_c16e_2500GeV, 1.0);


	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_250GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_250GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_250GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_300GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_300GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_300GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_350GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_350GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_350GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_400GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_400GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_400GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_600GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_600GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_600GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_700GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_700GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_700GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_800GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_800GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_800GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_1200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_1200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_1200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_1500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_1500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_1500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_2000GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_2000GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_2000GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16a_2500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16d_2500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesID_btag_c16e_2500GeV, 1.0);


	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_250GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_250GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_250GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_300GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_300GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_300GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_350GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_350GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_350GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_400GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_400GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_400GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_600GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_600GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_600GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_700GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_700GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_700GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_800GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_800GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_800GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_1200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_1200GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_1200GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_1500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_1500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_1500GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_2000GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_2000GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_2000GeV, 1.0);

	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16a_2500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16d_2500GeV, 1.0);
	dataloader->AddBackgroundTree(bkgTree_FakesISO_btag_c16e_2500GeV, 1.0);*/











 
 
 

    //dataloader->SetBackgroundWeightExpression( "weight*(pow(signal_mass/1000.0,2)+1)" );
    //dataloader->SetSignalWeightExpression( "weight*(pow(signal_mass/1000.0,2)+1)"); //*pow(signal_mass/2000.0,2)+1" );
  
    // we don't want to use negative weights in training - can ignore events with negative weights or use the absolute value of the weight (this second option is our nominal method)
    dataloader->SetBackgroundWeightExpression( "fabs(weight)" );
    dataloader->SetSignalWeightExpression( "fabs(weight)"); 
 

    TCut mycuts = "";
    TCut mycutb = "";


    //dataloader->PrepareTrainingAndTestTree( mycuts, mycutb, "SplitMode=Random:NormMode=NumEvents:!V" );
                                         //"nTrain_Signal=1500:nTrain_Background=187500:SplitMode=Random:NormMode=NumEvents:!V" );
    dataloader->PrepareTrainingAndTestTree(mycuts, mycutb,  "nTest_Signal=0:nTest_Background=0:SplitMode=Random");
 
    // ### Book MVA methods
    //
    // Please lookup the various method configuration options in the corresponding cxx files, eg:
    // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
    // it is possible to preset ranges in the option string in which the cut optimisation should be done:
    // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable
 
    // Cut optimisation
    if (Use["Cuts"])
       factory->BookMethod( dataloader, TMVA::Types::kCuts, "Cuts",
                            "!H:!V:FitMethod=MC:EffSel:VarProp=NotEnforced" );
 
    if (Use["CutsD"])
       factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsD",
                            "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );
 
    if (Use["CutsPCA"])
       factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsPCA",
                            "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );
 
    if (Use["CutsGA"])
       factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsGA",
                            "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );
 
    if (Use["CutsSA"])
       factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsSA",
                            "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );
 
    // Likelihood ("naive Bayes estimator")
    if (Use["Likelihood"])
       factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "Likelihood",
                            "!H:!V:IgnoreNegWeightsInTraining:TransformOutput:PDFInterpol=Spline2:NAvEvtPerBin=50" );
 
    // Decorrelated likelihood
    if (Use["LikelihoodD"])
       factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodD",
                            "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );
 
    // PCA-transformed likelihood
    if (Use["LikelihoodPCA"])
       factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodPCA",
                            "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" );
 
    // Use a kernel density estimator to approximate the PDFs
    if (Use["LikelihoodKDE"])
       factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodKDE",
                            "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" );
 
    // Use a variable-dependent mix of splines and kernel density estimator
    if (Use["LikelihoodMIX"])
       factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodMIX",
                            "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" );
 
    // Test the multi-dimensional probability density estimator
    // here are the options strings for the MinMax and RMS methods, respectively:
    //
    //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );
    //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );
    if (Use["PDERS"])
       factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERS",
                            "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );
 
    if (Use["PDERSD"])
       factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERSD",
                            "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate" );
 
    if (Use["PDERSPCA"])
       factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERSPCA",
                            "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA" );
 
    // Multi-dimensional likelihood estimator using self-adapting phase-space binning
    if (Use["PDEFoam"])
       factory->BookMethod( dataloader, TMVA::Types::kPDEFoam, "PDEFoam",
                            "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T" );
 
    if (Use["PDEFoamBoost"])
       factory->BookMethod( dataloader, TMVA::Types::kPDEFoam, "PDEFoamBoost",
                            "!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T" );
 
    // K-Nearest Neighbour classifier (KNN)
    if (Use["KNN"])
       factory->BookMethod( dataloader, TMVA::Types::kKNN, "KNN",
                            "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );
 
    // H-Matrix (chi2-squared) method
    if (Use["HMatrix"])
       factory->BookMethod( dataloader, TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );
 
    // Linear discriminant (same as Fisher discriminant)
    if (Use["LD"])
       factory->BookMethod( dataloader, TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10:IgnoreNegWeightsInTraining" );
 
    // Fisher discriminant (same as LD)
    if (Use["Fisher"])
       factory->BookMethod( dataloader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
 
    // Fisher with Gauss-transformed input variables
    if (Use["FisherG"])
       factory->BookMethod( dataloader, TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );
 
    // Composite classifier: ensemble (tree) of boosted Fisher classifiers
    if (Use["BoostedFisher"])
       factory->BookMethod( dataloader, TMVA::Types::kFisher, "BoostedFisher",
                            "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring" );
 
    // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
    if (Use["FDA_MC"])
       factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MC",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );
 
    if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
       factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_GA",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=100:Cycles=2:Steps=5:Trim=True:SaveBestGen=1" );
 
    if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
       factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_SA",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );
 
    if (Use["FDA_MT"])
       factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MT",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );
 
    if (Use["FDA_GAMT"])
       factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_GAMT",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );
 
    if (Use["FDA_MCMT"])
       factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MCMT",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );
 
    // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
    if (Use["MLP"])
	factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=sigmoid:VarTransform=N:NCycles=200:HiddenLayers=3,3,3:TestRate=5:!UseRegulator:IgnoreNegWeightsInTraining" ); //bveto
       //factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=sigmoid:VarTransform=G:NCycles=200:HiddenLayers=N+1:TestRate=5:!UseRegulator:IgnoreNegWeightsInTraining"  ); //btag
       //cv.BookMethod( TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=sigmoid:VarTransform=N:NCycles=200:HiddenLayers=3,3,3:TestRate=5:!UseRegulator:IgnoreNegWeightsInTraining" );

    if (Use["MLPBFGS"])
       factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=800:HiddenLayers=N+3:TestRate=5:TrainingMethod=BFGS:!UseRegulator:IgnoreNegWeightsInTraining" );
 
    if (Use["MLPBNN"])
       factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=1000:HiddenLayers=N+5:TestRate=5:ConvergenceTests=20:TrainingMethod=BFGS:UseRegulator:IgnoreNegWeightsInTraining" ); // BFGS training with bayesian regulators
 
 
    // Multi-architecture DNN implementation.
    if (Use["DNN_CPU"] or Use["DNN_GPU"]) {
       // General layout.
       TString layoutString ("Layout=TANH|3,TANH|3,TANH|3,LINEAR");
 
       // Training strategies.
       TString training0("LearningRate=1e-2,Momentum=0.9,Repetitions=1,"
                         "ConvergenceSteps=30,BatchSize=256,TestRepetitions=10,"
                         "WeightDecay=1e-4,Regularization=None,"
                         "DropConfig=0.0+0.5+0.5+0.5, Multithreading=True");
       TString training1("LearningRate=1e-2,Momentum=0.9,Repetitions=1,"
                         "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                         "WeightDecay=1e-4,Regularization=L2,"
                         "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
       TString training2("LearningRate=1e-3,Momentum=0.0,Repetitions=1,"
                         "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                         "WeightDecay=1e-4,Regularization=L2,"
                         "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
       TString trainingStrategyString ("TrainingStrategy=");
       trainingStrategyString += training0 + "|" + training1 + "|" + training2;
 
       // General Options.
       TString dnnOptions ("!H:V:ErrorStrategy=CROSSENTROPY:VarTransform=N:"
                           "WeightInitialization=XAVIERUNIFORM");
       dnnOptions.Append (":"); dnnOptions.Append (layoutString);
       dnnOptions.Append (":"); dnnOptions.Append (trainingStrategyString);
 
       // Cuda implementation.
       if (Use["DNN_GPU"]) {
          TString gpuOptions = dnnOptions + ":Architecture=GPU";
          factory->BookMethod(dataloader, TMVA::Types::kDL, "DNN_GPU", gpuOptions);
       }
       // Multi-core CPU implementation.
       if (Use["DNN_CPU"]) {
          TString cpuOptions = dnnOptions + ":Architecture=CPU";
          factory->BookMethod(dataloader, TMVA::Types::kDL, "DNN_CPU", cpuOptions);
       }
    }
 
    // CF(Clermont-Ferrand)ANN
    if (Use["CFMlpANN"])
       factory->BookMethod( dataloader, TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...
 
    // Tmlp(Root)ANN
    if (Use["TMlpANN"])
       factory->BookMethod( dataloader, TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...
 
    // Support Vector Machine
    if (Use["SVM"])
       factory->BookMethod( dataloader, TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );
 
    // Boosted Decision Trees
    if (Use["BDTG"]) // Gradient Boost
       factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG","!H:!V:NTrees=80:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=4" );
 	//cv.BookMethod( TMVA::Types::kBDT, "BDTG","!H:!V:NTrees=200:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=4:IgnoreNegWeightsInTraining" );
 
    if (Use["BDT"])  // Adaptive Boost
       factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT","!H:!V:NTrees=80:MinNodeSize=2%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.4:SeparationType=GiniIndex:nCuts=20:IgnoreNegWeightsInTraining" );
       //cv.BookMethod( TMVA::Types::kBDT, "BDT","!H:!V:NTrees=80:MinNodeSize=2%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.4:SeparationType=GiniIndex:nCuts=20:IgnoreNegWeightsInTraining" );
 
    if (Use["BDTB"]) // Bagging
       factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTB",
                            "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );
 
    if (Use["BDTD"]) // Decorrelation + Adaptive Boost
       factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTD",
                            "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );
 
    if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
       factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTF",
                            "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20" );
 
    // RuleFit -- TMVA implementation of Friedman's method
    if (Use["RuleFit"])
       factory->BookMethod( dataloader, TMVA::Types::kRuleFit, "RuleFit",
                            "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );
 
    // For an example of the category classifier usage, see: TMVAClassificationCategory
    //
    // --------------------------------------------------------------------------------------------------
    //  Now you can optimize the setting (configuration) of the MVAs using the set of training events
    // STILL EXPERIMENTAL and only implemented for BDT's !
    //
    //     factory->OptimizeAllMethods("SigEffAtBkg0.01","Scan");
       //factory->OptimizeAllMethods("ROCIntegral","FitGA");
    //
    // --------------------------------------------------------------------------------------------------
 
    // Now you can tell the factory to train, test, and evaluate the MVAs
    //
    // Train MVAs using the set of training events
    factory->TrainAllMethods();
 
    // Evaluate all MVAs using the set of test events
    factory->TestAllMethods();
 
    // Evaluate and compare performance of all configured MVAs
    factory->EvaluateAllMethods();
 
    // --------------------------------------------------------------

    //cv.Evaluate();
  
    // Save the output
    outputFile->Close();
 
    std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
    std::cout << "==> TMVAClassification is done!" << std::endl;
 
    delete factory;
    delete dataloader;
    // Launch the GUI for the root macros
    if (!gROOT->IsBatch())
    {
	 TMVA::TMVAGui( outfileName );
	 //cv.GetResults()[0].DrawAvgROCCurve(kTRUE, "Avg ROC");
         //cv.GetResults()[0].DrawAvgROCCurve(kTRUE, "Avg ROC");
     }

 
    return 0;
 }
 
 int main( int argc, char** argv )
 {
    TString methodList;
    for (int i=1; i<argc; i++) {
       TString regMethod(argv[i]);
       if(regMethod=="-b" || regMethod=="--batch") continue;
       if (!methodList.IsNull()) methodList += TString(",");
       methodList += regMethod;
    }
    return TMVA_train_201215(methodList);
 }
