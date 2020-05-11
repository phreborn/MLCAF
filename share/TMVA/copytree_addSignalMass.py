import ROOT
from ROOT import *
import math
from array import array
from scipy import stats 


oldfile = TFile.Open("dumpNtuples/Ztautau.root")
oldtree = oldfile.NOMINAL

newfile = TFile("dumpNtuples/Ztautau_sigMass.root","RECREATE")
newtree = oldtree.CloneTree(0)

events = oldtree.GetEntries()


MassArray = array("i", [0])
signal_mass = newtree.Branch( "signal_mass" , MassArray, 'signal_mass/I' ) 


#use this for assigning masses to background:
massPoints = (200,250,300,350,400,500,600,700,800,1000,1200,1500,2000,2500)
#probability distribution:
weights = (3031.0/89231,4479.0/89231,5751.0/89231,6674.0/89231,7537.0/89231,8377.0/89231,6982.0/89231,7114.0/89231,7268.0/89231,6925.0/89231,6389.0/89231,7257.0/89231,6180.0/89231,5267.0/89231) #number signal events per mass point, divided by the total number of signal events - c16a
#(or you can normalize signal samples and use a flat probability distribution here)

distribution = stats.rv_discrete(name='distribution', values=(massPoints, weights))


#use this for assigning masses to signal:
#sigMass=200 #or any other mass


mass = 0

for i in range(events):
	oldtree.GetEntry(i)

	#bkg:
	mass=distribution.rvs(size=1)

	#sig:
	#mass = sigMass
	print(mass)

	MassArray[0] = int(mass)
	print(MassArray[0])
	newtree.Fill()



newfile.Write()
newfile.Close()


