#!/usr/bin/env python
# TMVA linear discriminators

import ROOT
from ROOT import *
import math
import random
import array

ROOT.TMVA.Tools.Instance()
#TMVA.PyMethodBase.PyInitialize()

reader = ROOT.TMVA.Reader("Color:!Silent")



chainS = ROOT.TChain("NOMINAL","") #collection of files with TTrees
#chainS.Add("dumpNtuples/ggH_2500GeV_c16a_sigMass.root/NOMINAL")
#chainS.Add("dumpNtuples/ggH_2500GeV_c16d_sigMass.root/NOMINAL")
#chainS.Add("dumpNtuples/ggH_2500GeV_c16e_sigMass.root/NOMINAL")
#chainS.Add("dumpNtuples/ggH_200GeV_c16d.root/NOMINAL")
#chainS.Add("dumpNtuples/ggH_200GeV_c16e.root/NOMINAL")
#chainS.Add("dumpNtuples/201215/SR_sig_X_c16a_ZPrime_200_bveto.root/NOMINAL")
#chainS.Add("dumpNtuples/201215/SR_sig_X_c16d_ZPrime_200_bveto.root/NOMINAL")
#chainS.Add("dumpNtuples/201215/SR_sig_X_c16e_ZPrime_200_bveto.root/NOMINAL")
chainS.Add("dumpNtuples/201215/SR_sig_X_c16a_bbH_1500_bveto_2.root/NOMINAL")
chainS.Add("dumpNtuples/201215/SR_sig_X_c16d_bbH_1500_bveto_2.root/NOMINAL")
chainS.Add("dumpNtuples/201215/SR_sig_X_c16e_bbH_1500_bveto_2.root/NOMINAL")

chainB = ROOT.TChain("NOMINAL","")
chainB.Add("dumpNtuples/201215/SR_bkg_X_c16a_Ztautau_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16d_Ztautau_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16e_Ztautau_bveto.root/NOMINAL")
chainB.Add("dumpNtuples/201215/SR_bkg_X_c16a_Zll_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16d_Zll_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16e_Zll_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16a_Diboson_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16d_Diboson_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16e_Diboson_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16a_Top_single_btag.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16d_Top_single_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16e_Top_single_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16a_Top_ttbar_NOMINAL_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16d_Top_ttbar_NOMINAL_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16e_Top_ttbar_NOMINAL_bveto.root/NOMINAL")
chainB.Add("dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ID_data_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16d_FakesID_data_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16e_FakesID_data_bveto.root/NOMINAL")
chainB.Add("dumpNtuples/201215/SR_bkg_X_c16a_Fakes_ISO_data_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16d_FakesISO_data_bveto.root/NOMINAL")
#chainB.Add("dumpNtuples/201215/SR_bkg_X_c16e_FakesISO_data_bveto.root/NOMINAL")


#varList = ["MTtot","vis_mass","lephad_mmc_maxw_m","lephad_mmc_mlm_m","tau_pt"]
#varList = ["MTtot","vis_mass","lephad_mmc_maxw_m","lephad_mmc_mlm_m","tau_pt","lep_pt","tau_eta","lephad_dphi"]
#varList = ["MTtot/signal_mass","lephad_mmc_maxw_m/signal_mass","signal_mass"]
varList = ["MTtot","vis_mass","lephad_mmc_maxw_m","tau_pt"]
#varList = ["MTtot","vis_mass","lephad_mmc_maxw_m","tau_pt","MET","lep_phi-tau_phi","bjet_pt","bjet_eta-lep_eta","bjet_eta-tau_eta"]#,"signal_mass"]

#varList = ["MTtot","vis_mass","lephad_mmc_maxw_m","tau_pt","MET","lep_phi-tau_phi","bjet_pt","bjet_phi","bjet_eta","bjet_eta-lep_eta","bjet_eta-tau_eta"]#,"signal_mass"]
#varList = ["signal_mass","MTtot","lep_pt","tau_pt","MET","lephad_dphi","lephad_met_lep0_cos_dphi","lephad_met_lep1_cos_dphi","vis_mass"]
#varList=["MTtot"]
#specList = ["MTtot"]

import array
#The use of arrays is needed, because the pointer to the address of the object that is used for filling must be given to the TTree::Branch() call, even though the formal argument is declared a void*

v_mttot = array.array('f',[0]) ; reader.AddVariable(varList[0],v_mttot)
v_vis_mass = array.array('f',[0]) ; reader.AddVariable(varList[1],v_vis_mass)
v_mmc = array.array('f',[0]) ; reader.AddVariable(varList[2],v_mmc)
#v_mmc_mlm = array.array('f',[0]) ; reader.AddVariable(varList[3],v_mmc_mlm)
v_tau_pt = array.array('f',[0]) ; reader.AddVariable(varList[3],v_tau_pt)
#v_lep_pt = array.array('f',[0]) ; reader.AddVariable(varList[5],v_lep_pt)
#v_tau_eta = array.array('f',[0]) ; reader.AddVariable(varList[6],v_tau_eta)
#v_met = array.array('f',[0]) ; reader.AddVariable(varList[4],v_met)
#v_dphi_lep_tau = array.array('f',[0]) ; reader.AddVariable(varList[5],v_dphi_lep_tau)
#v_bjet_pt = array.array('f',[0]) ; reader.AddVariable(varList[6],v_bjet_pt)
#v_bjet_phi = array.array('f',[0]) ; reader.AddVariable(varList[7],v_bjet_phi)
#v_bjet_eta = array.array('f',[0]) ; reader.AddVariable(varList[8],v_bjet_eta)
#v_deta_bjet_lep = array.array('f',[0]) ; reader.AddVariable(varList[9],v_deta_bjet_lep)
#v_deta_bjet_tau = array.array('f',[0]) ; reader.AddVariable(varList[10],v_deta_bjet_tau)
#v_signal_mass = array.array('f',[0]) ; reader.AddVariable(varList[4],v_signal_mass)
#v_mttot_spec = array.array('f',[0]) ; reader.AddSpectator(specList[0],v_mttot_spec)

#fout = ROOT.TFile("TMVA_test.root","RECREATE")
#fout_sig = ROOT.TFile("TMVA_apply_sig.root","RECREATE")
#fout_bkg = ROOT.TFile("TMVA_apply_bkg.root","RECREATE")
t = TTree( 'MVout', 'MVA outputs' )
t_sig = TTree( 'MVout_sig', 'MVA outputs sig' )
t_bkg = TTree( 'MVout_bkg', 'MVA outputs bkg' )

#binning might need to be modified depending on how narrow the MVA score distribution is (ex. higher mass points need finer binning near the signal-like end of the distribution. Also keep in mind whether the score distribution starts at -1 or 0 (BDT/NN differences)
binning=[-1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.910, 0.920, 0.930, 0.940, 0.950, 0.960, 0.970, 0.980, 0.985, 0.990, 0.995, 0.9965, 0.9975, 0.9985, 0.999, 0.9995, 1.0]
#binning=[0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.910, 0.920, 0.930, 0.940, 0.950, 0.960, 0.970, 0.980, 0.985, 0.990, 0.9925, 0.9943, 0.9955, 0.9965, 0.9971, 0.9975,0.9978,1.]
#binning=[0.0, 0.3, 0.6, 0.8, 0.9, 0.910, 0.920, 0.930, 0.940, 0.950, 0.960, 0.970, 0.980, 0.985, 0.990, 0.995, 0.9965, 0.9975, 0.9985, 0.999, 0.9995]
#binning= [ 0.991, 0.992, 0.993, 0.994, 0.995, 0.996, 0.997, 0.998, 0.999,1.]
#binning = [ 0.0, 0.935, 0.995, 1.0]
#nBins = len(binning)-1
nBins = 100000

sig_hist_MTTOT = TH1F("","",nBins,0,2500)
bkg_hist_MTTOT = TH1F("","",nBins,0,2500)

#sig_hist_MLP = TH1F("","",nBins,array.array('f',binning))
#bkg_hist_MLP = TH1F("","",nBins,array.array('f',binning))

sig_hist_MLP = TH1F("","",nBins,-1,1.)
bkg_hist_MLP = TH1F("","",nBins,-1,1.)
sig_hist_BDT = TH1F("","",nBins,-1,1.)
bkg_hist_BDT = TH1F("","",nBins,-1,1.)

#sig_hist_likelihood = TH1F("sig_hist_likelihood","signal likelihood score",50,-1.,1.)
#bkg_hist_likelihood = TH1F("bkg_hist_likelihood","background likelihood score",50,-1.,1.)
#sig_hist_fisher = TH1F("sig_hist_fisher","signal fisher score",50,-1.,1.)
#bkg_hist_fisher = TH1F("bkg_hist_fisher","background fisher score",50,-1.,1.)
 
#maxn = 10
#n = array( 'i', [ 0 ] )
#d = array( 'f', maxn*[ 0. ] )


t.Branch( varList[0],v_mttot,varList[0]+'/F')
t.Branch( varList[1],v_vis_mass ,varList[1]+'/F' )
t.Branch( varList[2],v_mmc ,varList[2]+'/F' )
#t.Branch( varList[3],v_mmc_mlm ,varList[3]+'/F' )
t.Branch( varList[3],v_tau_pt ,varList[3]+'/F' )
#t.Branch( varList[5],v_lep_pt ,varList[5]+'/F' )
#t.Branch( varList[6],v_tau_eta ,varList[6]+'/F' )
#t.Branch( varList[4],v_met, varList[4]+'/F')
#t.Branch( varList[5],v_dphi_lep_tau,varList[5]+'/F')
#t.Branch( varList[6],v_bjet_pt ,varList[6]+'/F' )
#t.Branch( varList[7],v_bjet_phi ,varList[7]+'/F' )
#t.Branch( varList[8],v_bjet_eta ,varList[8]+'/F' )
#t.Branch( varList[9],v_deta_bjet_lep ,varList[9]+'/F' )
#t.Branch( varList[10],v_deta_bjet_tau ,varList[10]+'/F' )
#t.Branch( varList[4],v_signal_mass, varList[4]+'/F')
#t.Branch( specList[0], v_mttot_spec, specList[0]+'/F')


#methodList = {'BDT','DNN_CPU','Likelihood','LikelihoodD','MLP'} #list all methods used in TMVAClassificationMW.py
methodList = {'BDT'}
#,'Likelihood','Fisher'}
methodVars = []

for method in methodList:
	methodVars.append( array.array( 'f', [ 0 ] )  )
	t.Branch( method, methodVars[-1] ,method+'/F' )
	reader.BookMVA(method,"dataset_bveto_201215_BDT_1500GeV_fabsWeights/weights/TMVAClassification_"+method+".weights.xml")

#reader.BookMVA('PyKeras', TString('dataset_keras_PNN/weights/TMVAClassification_PyKeras.weights.xml'))
    






#print entries, ' entries'
tot_weight = 0

for chain in [chainS,chainB]:

	#entries = min(chain.GetEntriesFast(),20000)
	entries = chain.GetEntriesFast()

	#for jentry in range( 400000 ):
	for jentry in xrange( entries ):
		# get the next tree in the chain
		ientry = chain.LoadTree(jentry)
		if (ientry % 1000)==0:
			#print "Entry: ",ientry
			print("Entry: ",ientry)
		if ientry < 0:
			break

	    # verify file/tree/chain integrity
		nb = chain.GetEntry( jentry )
		if nb <= 0:
			continue

		tot_weight = tot_weight+chain.weight
		#print("total weight = {}".format(tot_weight))

		#if ((jentry)%5 == 0):
		#	continue

		#if(int(chain.MTtot*10.)%5!=3):
		#	continue

		#cut - tail only
		#if(chain.MTtot<500):
		#	continue

		#ehad or muhad
		#if not(chain.lep_0==1):
		#	continue
	
		#print("getting var values from chain")	
		v_vis_mass[0]=chain.vis_mass
		v_mttot[0]=chain.MTtot
		v_tau_pt[0]=chain.tau_pt
		#v_tau_eta[0]=chain.tau_eta
		#v_lep_pt[0]=chain.lep_pt
		#v_dphi_lep_tau[0]=chain.lephad_dphi
		v_mmc[0]=chain.lephad_mmc_maxw_m
		#v_mmc_mlm[0]=chain.lephad_mmc_mlm_m
		#v_signal_mass[0]=chain.signal_mass
		#v_met[0]=chain.MET
		#v_dphi_lep_tau[0]=chain.lep_phi-chain.tau_phi
		#v_bjet_pt[0]=chain.bjet_pt
		#v_bjet_phi[0]=chain.bjet_phi
		#v_bjet_eta[0]=chain.bjet_eta
		#v_deta_bjet_lep[0]=chain.bjet_eta-chain.lep_eta
		#v_deta_bjet_tau[0]=chain.bjet_eta-chain.tau_eta

		#v_mttot_spec[0]=chain.MTtot




	    #Evaluate all methods
		if(chain==chainS):
			sig_hist_MLP.Fill(reader.EvaluateMVA('BDT'), fabs(chain.weight))#*chain.tauspinner_ZprimeSSM_ZprimeMass_200)
			#print("signal: filling with {}".format(reader.EvaluateMVA('MLP')))
			
			sig_hist_MTTOT.Fill(chain.MTtot, chain.weight)

			#sig_hist_BDT.Fill(reader.EvaluateMVA('BDTG'), chain.weight)
			#sig_hist_likelihood.Fill(reader.EvaluateMVA('Likelihoodain))#, chain.weight)
			#sig_hist_fisher.Fill(reader.EvaluateMVA('Fisher'))#, chain.weight)
			#print('signal event BDT score = {0}'.format(reader.EvaluateMVA('BDT ada boost')))
			#print('type = {0}'.format(type(reader.EvaluateMVA('BDT ada boost'))))
			#methodVars[0][0]= reader.EvaluateMVA('PyKeras')
			#methodVars[1][0]= reader.EvaluateMVA('BDTG')
			#methodVars[1][0]= reader.EvaluateMVA('Likelihood')
			#methodVars[2][0]= reader.EvaluateMVA('Fisher')
		elif(chain==chainB):
			bkg_hist_MLP.Fill(reader.EvaluateMVA('BDT'), fabs(chain.weight))

			bkg_hist_MTTOT.Fill(chain.MTtot,chain.weight)

			#bkg_hist_BDT.Fill(reader.EvaluateMVA('BDTG'),chain.weight)


		if(chain==chainS):
			t_sig.Fill()
		elif(chain==chainB):
			t_bkg.Fill()
		t.Fill()

sig_all = sig_hist_MLP.Integral()
bkg_all = bkg_hist_MLP.Integral()

TPR_MLP = array.array('f')
FPR_MLP = array.array('f')
TPR_MLP.append(1.)
FPR_MLP.append(0.)

TPR_BDT = array.array('f')
FPR_BDT = array.array('f')
TPR_BDT.append(1.)
FPR_BDT.append(0.)

#TPR_likelihood = array.array('f')
#FPR_likelihood = array.array('f')

#TPR_fisher = array.array('f')
#FPR_fisher = array.array('f')



print('# signal events = {0}, # bkg events = {1}'.format(sig_all, bkg_all))

for threshold in range(1,nBins):
	print(threshold)
	#threshold = number/1000.0
	#print('threshold type: {0}'.format(type(threshold)))
	#print('signal histogram integral = {0}'.format(x))
	#print('signal integral at threshold {0}: {1}'.format(threshold,sig_hist.Integral(0,threshold)))
	x_MLP = 1 - (sig_hist_MLP.Integral(0,threshold))/sig_all
	y_MLP = bkg_hist_MLP.Integral(0,threshold)/bkg_all
	#x_BDT = 1 - (sig_hist_BDT.Integral(0,threshold))/sig_all
	#y_BDT = bkg_hist_BDT.Integral(0,threshold)/bkg_all
	#x_likelihood = 1 - (sig_hist_likelihood.Integral(0,threshold))/sig_all
	#y_likelihood = bkg_hist_likelihood.Integral(0,threshold)/bkg_all
	#x_fisher = 1 - (sig_hist_fisher.Integral(0,threshold))/sig_all
	#y_fisher = bkg_hist_fisher.Integral(0,threshold)/bkg_all
	#print('({0},{1})'.format(x,y))
	TPR_MLP.append(x_MLP)
	FPR_MLP.append(y_MLP)
	#TPR_BDT.append(x_BDT)
	#FPR_BDT.append(y_BDT)
	#TPR_likelihood.append(x_likelihood)
	#FPR_likelihood.append(y_likelihood)
	#TPR_fisher.append(x_fisher)
	#FPR_fisher.append(y_fisher)

#make scatter plot

TPR_MLP.append(0.)
FPR_MLP.append(1.)
#TPR_BDT.append(0.)
#FPR_BDT.append(1.)

print('MLP: TPR = {0}, FPR = {1}'.format(TPR_MLP,FPR_MLP))
#print('BDT: TPR = {0}, FPR = {1}'.format(TPR_BDT,FPR_BDT))
##print('Likelihood: TPR = {0}, FPR = {1}'.format(TPR_likelihood,FPR_likelihood))
##print('Fisher: TPR = {0}, FPR = {1}'.format(TPR_fisher,FPR_fisher))

c_MLP = TCanvas("canvas","canvas",800,600)
gPad.SetFillColor(0)
gStyle.SetOptStat(0)
ROC_MLP = TGraph(nBins+1,TPR_MLP,FPR_MLP)
ROC_MLP.GetXaxis().SetTitle("X title")
ROC_MLP.GetYaxis().SetTitle("Y title")
ROC_MLP.SetLineWidth(2)
ROC_MLP.SetMarkerStyle(8)
ROC_MLP.Draw("APL")
##ROC_MLP.Write()
c_MLP.SaveAs("test_ROC_MLP_2500GeV.pdf")

c_MVAResponse = TCanvas("c2","c2",800,600)
#c_MVAResponse.SetLogy()
gPad.SetFillColor(0)
gStyle.SetOptStat(0)
sig_hist_MLP.SetMarkerStyle(0)
sig_hist_MLP.SetLineWidth(2)
sig_hist_MLP.SetLineColor(kBlue)
sig_hist_MLP.SetMarkerColor(kBlue)
bkg_hist_MLP.SetMarkerStyle(0)
bkg_hist_MLP.SetLineWidth(2)
bkg_hist_MLP.SetLineColor(kRed)
bkg_hist_MLP.SetMarkerColor(kRed)
bkg_hist_MLP.GetXaxis().SetTitle("MVA response")
bkg_hist_MLP.GetXaxis().SetTitle("MVA response")
bkg_hist_MLP.GetYaxis().SetTitle("events")
bkg_hist_MLP.GetYaxis().SetTitle("events")
sig_hist_MLP.Scale(1./(sig_hist_MLP.Integral()))
bkg_hist_MLP.Scale(1./(bkg_hist_MLP.Integral()))
sig_hist_MLP.Draw("hist")
bkg_hist_MLP.Draw("hist same")

leg_MLP = TLegend(0.7,0.7,0.85,0.85)       
leg_MLP.AddEntry(bkg_hist_MLP,"Z#rightarrow#tau#tau","lep")
leg_MLP.AddEntry(sig_hist_MLP,"ggH 200 GeV","lep")
leg_MLP.Draw()

c_MVAResponse.SaveAs("MVAResponse.png")



#c_BDT = TCanvas("canvas","canvas",800,600)
#ROC_BDT = TGraph(101,TPR_BDT,FPR_BDT)
#ROC_BDT.GetXaxis().SetTitle("X title");
#ROC_BDT.GetYaxis().SetTitle("Y title");
#ROC_BDT.Draw("ACP")
#ROC_BDT.Write()
#c_BDT.SaveAs("test_ROC_BDT_200GeV.pdf")



#AUC: trapezoidal rule
AUC_MLP = 0
#AUC_BDT = 0
for point in range(1,nBins+1):
	AUC_MLP = AUC_MLP + (FPR_MLP[point]+FPR_MLP[point-1])*(TPR_MLP[point-1]-TPR_MLP[point])/2
	#print(AUC_MLP)
	#AUC_BDT = AUC_BDT + (FPR_BDT[point]+FPR_BDT[point-1])*(TPR_BDT[point-1]-TPR_BDT[point])/2
	

print('MLP AUC: {0}'.format(AUC_MLP)) 
#print('BDT AUC: {0}'.format(AUC_BDT))

print("bkg in last bin: {}".format(bkg_hist_MLP.GetBinContent(8)+bkg_hist_MLP.GetBinContent(9)))

#fout.Write()
#fout.Close()
#fout_sig.Write()
#fout_sig.Close()
#fout_bkg.Write()
#fout_bkg.Close()






del reader

#TMVA::TMVAGui()
#ROOT.TMVA.TMVAGui()




