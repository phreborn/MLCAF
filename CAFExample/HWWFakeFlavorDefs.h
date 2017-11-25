#ifndef __HWWFAKEFLAVORDEFS__
#define __HWWFAKEFLAVORDEFS__

//***********************************
// Define the fake flavor categories
//***********************************

namespace HWWFakeFlavor {

	enum FakeClassifierMode {
	  MCTruthClassifier=0,
	  Run1
	};

	enum FakeIndex {
	  Leading=1,
	  Subleading=2,
	  Other=3
	};

	enum FakeFlavor {

	  NotClassified        = -3,
	  EL_NonDefined_Origin = -2,
	  MU_NonDefined_Origin = -1,
	  Prompt               =  0,
	  ChargeFlip           =  1,
	  EL_HFb               =  2,
	  MU_HFb               =  3,
	  EL_HFc               =  4,
	  MU_HFc               =  5,
	  EL_LFgamma           =  6,
	  EL_pi0               =  7,
	  EL_Kaon              =  8,
	  MU_Kaon              =  9,
	  EL_LFrest            =  10,
	  MU_LFrest            =  11

	};

	enum FakeFlavorRun1 {

	  notClassified        = -3, // use same number as FakeFlavour
	  bottomLeptonic       =  1,
	  bottomHadronic       =  2,
	  charmLeptonic        =  3,
	  charmHadronic        =  4,
	  strangeLeptonic      =  5,
	  strangeHadronic      =  6,
	  lightLeptonic        =  7,
	  lightHadronic        =  8,
	  otherLeptonic        =  9,
	  otherHadronic        =  10

	//   1 --> Bottom (leptonic)
	// 2 --> Bottom (hadronic)
	//
	// 3 --> Charm (leptonic)
	// 4 --> Charm (hadronic)
	//
	// 5 --> Strange (leptonic)
	// 6 --> Strange (hadronic)
	//
	// 7 --> Light (leptonic)
	// 8 --> Light (hadronic)
	//
	// 9 --> Other (leptonic)
	// 10 --> Other (hadronic)

	};

}

#endif