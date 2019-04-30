#!/user/bin/env python2






debug = False
info = False
doConstrain = False
ff_dict ={}

# returns normalisation and error of a background

def constrain_R_values(relConW,relConTop,relConZ,category,trigger,prong,region):

    _relConW   = [relConW[0],relConW[1]]
    _relConZ   = [relConZ[0],relConZ[1]]
    _relConTop = [relConTop[0],relConTop[1]]

    # print "R VARIATIONS ARE ON"
    # var = 0.5
    # #var = 1.5

    # fac = (1-var*_relConW[0])/(1-_relConW[0])
    # _relConZ[0] = fac*_relConZ[0]
    # _relConTop[0] = fac*_relConTop[0]
    # _relConW[0] = var*_relConW[0]

    # ff_dict[category][trigger][prong][region]['W']['R'] = tuple(_relConW)
    # ff_dict[category][trigger][prong][region]['Z']['R'] = tuple(_relConZ)
    # ff_dict[category][trigger][prong][region]['Top']['R'] = tuple(_relConTop)

    if _relConW[0] > 1.:
         _relConW[0] = 1.
         print "WARNING::: constraining R_W! to 1, "
         ff_dict[category][trigger][prong][region]['W']['R'] = tuple(_relConW)
    if _relConZ[0] > 1.:
         _relConZ[0] = 1.
         print "WARNING::: constraining R_Z! to 1, "
         ff_dict[category][trigger][prong][region]['Z']['R'] = tuple(_relConZ)
    if _relConTop[0] > 1.:
         _relConTop[0] = 1.
         print "WARNING::: constraining R_Top! to 1, "
         ff_dict[category][trigger][prong][region]['Top']['R'] = tuple(_relConTop)
    if _relConW[0] == 1.:
        _relConTop[0] = 0.
        _relConZ[0] = 0.
        ff_dict[category][trigger][prong][region]['Top']['R'] = tuple(_relConTop)
        ff_dict[category][trigger][prong][region]['Z']['R'] = tuple(_relConZ)
        print "WARNING::: constraining R_Top, R_Z to 0. ! "
    if _relConZ[0] == 1.:
        _relConTop[0] = 0.
        _relConW[0] = 0.
        ff_dict[category][trigger][prong][region]['Top']['R'] = tuple(_relConTop)
        ff_dict[category][trigger][prong][region]['W']['R'] = tuple(_relConW)
        print "WARNING::: constraining R_Top, R_W to 0. ! "
    if _relConTop[0] == 1.:
        _relConW[0] = 0.
        _relConZ[0] = 0.
        ff_dict[category][trigger][prong][region]['W']['R'] = tuple(_relConW)
        ff_dict[category][trigger][prong][region]['Z']['R'] = tuple(_relConZ)
        print "WARNING::: constraining R_W, R_Z to 0. ! "
    if _relConW[0] < 0.:
        _relConW[0] = 0.
        ff_dict[category][trigger][prong][region]['W']['R'] = tuple(_relConW)
        print "WARNING::: constraining R_W to 0.  "
    if _relConZ[0] < 0.:
        _relConZ[0] = 0.
        ff_dict[category][trigger][prong][region]['Z']['R'] = tuple(_relConZ)
        print "WARNING::: constraining R_Z to 0.  "
    if _relConTop[0] < 0.:
        _relConTop[0] = 0.
        ff_dict[category][trigger][prong][region]['Top']['R']=tuple(_relConTop)
        print "WARNING::: constraining R_Top to 0.  "

    if info: print 'relConW: ' + str(_relConW[0]) + ' +\- ' + str(_relConW[1])
    if info: print 'relConTop: ' + str(_relConTop[0]) + ' +\- ' + str(_relConTop[1])
    if info: print 'relConZ: ' + str(_relConZ[0]) + ' +\- ' + str(_relConZ[1])


    return tuple(_relConW),tuple(_relConTop),tuple(_relConZ)




def dumpValuesinTable():
    region = 'SR'
    f = open('FF_table_july.tex', 'w')
    f.write( "\\documentclass[a4paper,10pt]{article}\n")
    f.write( "\\usepackage[utf8]{inputenc}\n")
    f.write( "\\usepackage{lscape}\n")
    f.write( "\\begin{document}\n")
    f.write( "\\begin{landscape}\n")
    f.write( "\\tiny\n")
    for category in ff_dict.keys():
        f.write( '\\section{%s} \n' %(category))
        for trigger in ff_dict[category].keys():
            f.write( "%s \\\\ \n" %(trigger))
            for prong in ff_dict[category][trigger].keys():
                R_sum = 0.
                f.write( "\\noindent %s \\\\ \n" %(prong) )
                f.write( "\\begin{tabular}{l|l|l|l|l|l|l|l|l|} \n")
                f.write( " process  & $N^{fail,CR}_{Data}$ & $N^{fail,CR}_{MC,other}$ & $N^{fail,CR}_{MC,noJet}$&   $N^{fail,CR}_{MC,j\\rightarrow\\tau}$ &  $N^{fail,SR}_{MC,j\\rightarrow\\tau}$ &   $N^{fail,SR}_{Data}$ & $N^{fail,SR}_{MC,noJet}$  & R   \\\\  \n" )
                f.write( "\\hline \n")
                for bkg in ['W','Z','Top','QCD']:

                    #f.write( bkg, ff_dict[category][trigger][prong][region][bkg]
                    try:
                        R_sum = R_sum + ff_dict[category][trigger][prong][region][bkg]['R'][0]
                        if bkg == 'QCD':
                            f.write( "   %s     &      &       &       &       &      &       &       & %.3f +- %.3f   \\\\ \n"  %(bkg,
                                                                                                                                                   ff_dict[category][trigger][prong][region][bkg]['R'][0],
                                                                                                                                                   ff_dict[category][trigger][prong][region][bkg]['R'][1],
                                                                                                                                                   ))


                        else:
                            f.write( "  %s     & %.1f +- %.1f &  %.1f +- %.1f &  %.1f +- %.1f &  %.1f +- %.1f &  %.3f +- %.3f &  %.1f +- %.1f &  %.1f +- %.1f & %.3f +- %.3f \\\\ \n" %(  tuple(itertools.chain((bkg,),
                                                                                                                                                                                                                               ff_dict[category][trigger][prong][region][bkg]['sumData_CR'],
                                                                                                                                                                                                                               ff_dict[category][trigger][prong][region][bkg]['sumOtherMC_CR'],
                                                                                                                                                                                                                               ff_dict[category][trigger][prong][region][bkg]['sumNoJet_CR'],
                                                                                                                                                                                                                               ff_dict[category][trigger][prong][region][bkg]['sumJet_CR' ],
                                                                                                                                                                                                                               ff_dict[category][trigger][prong][region][bkg]['sumJet_SR'],
                                                                                                                                                                                                                               ff_dict[category][trigger][prong][region][bkg]['sumData_SR'],
                                                                                                                                                                                                                               ff_dict[category][trigger][prong][region][bkg]['sumOtherMC_SR'],
                                                                                                                                                                                                                               ff_dict[category][trigger][prong][region][bkg]['R']
                                                                                                                                                                                                                               ) ) ) )
                    except:
                        print bkg, ff_dict[category][trigger][prong][region][bkg]
                f.write( "\\hline \n")
                f.write( "   %s     &      &       &       &       &       &        &      & %.3f    \\\\ \n" %('Sum', R_sum, ))
                f.write( "\\end{tabular} \n")
                f.write( "\n")
                f.write( "\\begin{tabular}{l|l||l|l|l|l|l|l||l|l|} \n")
                f.write( " process  &  bin &  $N^{pass,CR}_{Data}$ & $N^{pass,CR}_{MC other}$ & $N^{pass,CR}_{MC, noj\\rightarrow\\tau}$ & $N^{fail,CR}_{Data}$ & $N^{fail,CR}_{MC other}$ & $N^{fail,CR}_{MC, no j\\rightarrow \\tau}$ & FF   \\\\  \n" )
                f.write( "\\hline \n")
                for i in range(1,4):
                    R_sum = 0.
                    for bkg in ['W','Z','Top','QCD']:
                        R_sum = R_sum + ff_dict[category][trigger][prong][region][bkg]['R'][0]
                        f.write( "   %s & %s  & %.1f +- %.1f & %.1f +- %.1f  & %.1f  +- %.1f & %.1f +- %.1f & %.1f +- %.1f  & %.1f +- %.1f &  %.3f +- %.3f    \\\\ \n"  %( tuple(itertools.chain((bkg,), (i,),
                                                                                                                                                                                    ff_dict[category][trigger][prong][region][bkg]['Bin_%s' %(i)]['sumTauData'],
                                                                                                                                                                                    ff_dict[category][trigger][prong][region][bkg]['Bin_%s' %(i)]['sumTauMC'],
                                                                                                                                                                                    ff_dict[category][trigger][prong][region][bkg]['Bin_%s' %(i)]['sumTauNoJet'],
                                                                                                                                                                                    ff_dict[category][trigger][prong][region][bkg]['Bin_%s' %(i)]['sumAntiTauData'],
                                                                                                                                                                                    ff_dict[category][trigger][prong][region][bkg]['Bin_%s' %(i)]['sumAntiTauMC'],
                                                                                                                                                                                    ff_dict[category][trigger][prong][region][bkg]['Bin_%s' %(i)]['sumAntiTauNoJet'],
                                                                                                                                                                                    ff_dict[category][trigger][prong][region][bkg]['Bin_%s' %(i)]['FF'] ) )
                                                                                                                                                                            ))




                    f.write( "\\hline \n")
                    f.write( "   %s  & %s   &  & & & & & & %.3f +- %.3f   \\\\ \n" %('Sum', i ,
                                                                                     ff_dict[category][trigger][prong][region]['Sum']['Bin_%s' %(i)]['FF'][0],   ff_dict[category][trigger][prong][region]['Sum']['Bin_%s' %(i)]['FF'][1]
                                                                                     #ff_dict[category][trigger][prong][region]['Sum']['Bin_2']['FF'][0],   ff_dict[category][trigger][prong][region]['Sum']['Bin_2']['FF'][1],
                                                                                     #ff_dict[category][trigger][prong][region]['Sum']['Bin_3']['FF'][0],   ff_dict[category][trigger][prong][region]['Sum']['Bin_3']['FF'][1],
                                                                                     ))
                    f.write( "\\hline \n")
                    f.write( "\\hline \n")
                f.write( "\\end{tabular} \n")
                f.write( "\n")
        f.write( "\\clearpage \n")
    f.write( "\\end{landscape} \n")
    f.write( "\\end{document} \n")



def calcKappa(background, category, prongs, trigger,region):

    processes = {'Data':'./bkg/lephad/Fake/data',
                 'W':'./bkg/lephad/Fake/mc/[WjetsMG+WjetsShEW]',
                 'Z':'./bkg/lephad/Fake/mc/[ZllMG+ZllShEW]',
                 'Ztt':'./bkg/lephad/Fake/mc/[ZttMG+ZttShEW]',
                 'Top':'./bkg/lephad/Fake/mc/Top',
                 'DiBoson':'./bkg/lephad/Fake/mc/Diboson'
                 }


    controlRegion = background+'CR'

    sumData = 0.
    sumDataErr = 0.

    sumNoJet = 0.
    sumNoJetErr = 0.

    sumJet = 0.
    sumJetErr = 0.

    sumOtherMC = 0.
    sumOtherMCErr = 0.


    for p in processes:
        path = processes[p]

        if p == 'Data':
            sumData = samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion).getCounter()
            sumDataErr = pow(samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion).getError(),2)
        elif p == background:
            sumNoJet = -1*samples.getCounter(path,'Cut'+category+'NoJet'+prongs+trigger+controlRegion).getCounter()
            sumNoJetErr = pow(samples.getCounter(path,'Cut'+category+'NoJet'+prongs+trigger+controlRegion).getError(),2)

            sumJet = -1*samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion).getCounter()
            sumJetErr = pow(samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion).getError(),2)
        else:
            sumOtherMC += -1*samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion).getCounter() + -1*samples.getCounter(path,'Cut'+category+'NoJet'+prongs+trigger+controlRegion).getCounter()
            sumOtherMCErr += pow(samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion).getError(),2) + pow(samples.getCounter(path,'Cut'+category+'NoJet'+prongs+trigger+controlRegion).getError(),2)


    if sumJet == 0:
        if debug: print background+': sumJet is 0, setting kappa and error to 0!\n'
        kappa = 0.
        kappaErr = 0.
    elif (sumData - sumOtherMC - sumNoJet == 0):
        if debug: print background+': sumData - sumOtherMC - sumNoJet is 0, setting kappa and error to 0!\n'
        kappa = 0.
        kappaErr = 0.
    else:
        kappa = (sumData - sumOtherMC - sumNoJet)/(sumJet)
        kappaErr = kappa*pow(((sumDataErr+sumOtherMCErr+sumNoJetErr)/(pow(sumData-sumOtherMC-sumNoJet,2)))+(sumJetErr/pow(sumJet,2)),0.5) #checked


    ff_dict[category][trigger][prongs][region][background].update({
            'sumJet_CR'     : (sumJet,pow(sumJetErr,0.5)),
            'sumNoJet_CR'   : (sumNoJet,pow(sumNoJetErr,0.5)),
            'sumData_CR'    : (sumData,pow(sumDataErr,0.5)),
            'sumOtherMC_CR' : (sumOtherMC,pow(sumOtherMCErr,0.5))
            })



    if info: print background + ': kappa: ' + str(kappa) + ' +\- ' + str(kappaErr)

    return (kappa, kappaErr)

# returns the relative contribution and error of a background

def calcRelCon(background,category, prongs, trigger, region):
    if debug:
        print "DEBUG: Start calcRelCon for:: %s " %(background)
    processes = {'Data':'./bkg/lephad/Fake/data',
                 'W':'./bkg/lephad/Fake/mc/[WjetsMG+WjetsShEW]',
                 'Z':'./bkg/lephad/Fake/mc/[ZllMG+ZllShEW]',
                 'Ztt':'./bkg/lephad/Fake/mc/[ZttMG+ZttShEW]',
                 'Top':'./bkg/lephad/Fake/mc/Top',
                 'DiBoson':'./bkg/lephad/Fake/mc/Diboson'
                 }

    kappa = 0.
    kappaErr = 0.

    sumData = 0.
    sumDataErr = 0.

    sumJet = 0.
    sumJetErr = 0.

    sumOtherMC = 0.
    sumOtherMCErr = 0.

    for p in processes:
        path = processes[p]

        if p == 'Data':
            sumData = samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+region).getCounter()
            sumDataErr = pow(samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+region).getError(),2)
        elif p == background:
            sumJet = -1*samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+region).getCounter()
            sumJetErr = pow(samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+region).getError(),2)

            sumOtherMC += -1*samples.getCounter(path,'Cut'+category+'NoJet'+prongs+trigger+region).getCounter()
            sumOtherMCErr += pow(samples.getCounter(path,'Cut'+category+'NoJet'+prongs+trigger+region).getError(),2)
        else:
            sumOtherMC += -1*samples.getCounter(path,'Cut'+category+'NoJet'+prongs+trigger+region).getCounter()
            sumOtherMCErr += pow(samples.getCounter(path,'Cut'+category+'NoJet'+prongs+trigger+region).getError(),2)

    # dropped k-factor calculation
    # if (region == 'SR'):
    #     kappa = calcKappa(background,category, prongs, trigger,region)
    #     kappaVal = kappa[0]
    #     kappaErr = kappa[1]
    # else:
    #     kappaVal = 1.
    #     kappaErr = 0.

    kappaDummy = calcKappa(background,category, prongs, trigger,region)

    kappaVal = 1.
    kappaErr = 0.

    if (sumData - sumOtherMC) == 0. or sumJet == 0. or kappaVal == 0.:
        if (sumData - sumOtherMC) == 0. and debug: print 'sumData - sumOtherMC is 0, setting relCon to 0!'
        relCon = 0.
        relConErr = 0.
    else:
        relCon = kappaVal*(sumJet)/(sumData - sumOtherMC)
        relConErr = relCon*pow(((sumDataErr+sumOtherMCErr)/(pow(sumData-sumOtherMC,2)))+(sumJetErr/pow(sumJet,2))+(pow(kappaErr/kappaVal,2)),0.5) #checked

    #if background == 'W':
    #    relCon = 1.5*relCon

    ff_dict[category][trigger][prongs][region][background].update({
        'R'             : (relCon, relConErr),
        'k'             : (kappaVal, kappaErr),
        'sumJet_SR'     : (sumJet,pow(sumJetErr,0.5)),
        'sumData_SR'    : (sumData,pow(sumDataErr,0.5)),
        'sumOtherMC_SR' : (sumOtherMC,pow(sumOtherMCErr,0.5))
        })

    if info: print background + ': relCon: ' + str(relCon) + ' +\- ' + str(relConErr)

    return (relCon, relConErr)

# returns fake factor and error in a controlregion

def calcFakeFactor(background, minBin, maxBin, prongs, histo, category, trigger, region): #prongs=[1Prong,3Prong], binVar=[unbinned,eta,pt]

    if debug:
        print "DEBUG: Start calcFakeFactor for:: %s " %(background)
    #dictionary of all processes and paths
    processesAntiTau = {'Data':'./bkg/lephad/Fake/data',
                        'W':'./bkg/lephad/Fake/mc/[WjetsMG+WjetsShEW]',
                        'Z':'./bkg/lephad/Fake/mc/[ZllMG+ZllShEW]',
                        'Ztt':'./bkg/lephad/Fake/mc/[ZttMG+ZttShEW]',
                        'Top':'./bkg/lephad/Fake/mc/Top',
                        'DiBoson':'./bkg/lephad/Fake/mc/Diboson'
                        }

    processesTau = {'Data':'./data',
                    'W':'./bkg/lephad/[WjetsMG+WjetsShEW]',
                    'Z':'./bkg/lephad/[ZllMG+ZllShEW]',
                    'Ztt':'./bkg/lephad/[ZttMG+ZttShEW]',
                    'Top':'./bkg/lephad/Top',
                    'DiBoson':'./bkg/lephad/Diboson'
                    }


    controlRegion = background+'CR'

    sumTauData = 0.
    sumTauDataErr = 0.
    integralTauDataErr = Double(0.)

    sumTauData = 0.
    sumTauDataErr = 0.


    sumTauNoJet = 0.
    sumTauNoJetErr = 0.
    integralTauNoJetErr = Double(0.)


    sumTauMCJet = 0.
    sumTauMCJetErr = 0.
    integralTauMCJetErr = Double(0.)

    sumTauMCNoJet = 0.
    sumTauMCNoJetErr = 0.
    integralTauMCNoJetErr = Double(0.)

    sumTauMC = 0.
    sumTauMCErr = 0.


    sumAntiTauData = 0.
    sumAntiTauDataErr = 0.
    integralAntiTauDataErr = Double(0.)

    sumAntiTauData = 0.
    sumAntiTauDataErr = 0.


    sumAntiTauNoJet = 0.
    sumAntiTauNoJetErr = 0.
    integralAntiTauNoJetErr = Double(0.)


    sumAntiTauMCJet = 0.
    sumAntiTauMCJetErr = 0.
    integralAntiTauMCJetErr = Double(0.)

    sumAntiTauMCNoJet = 0.
    sumAntiTauMCNoJetErr = 0.
    integralAntiTauMCNoJetErr = Double(0.)

    sumAntiTauMC = 0.
    sumAntiTauMCErr = 0.

    sumTau = 0.
    sumTauErr = 0.
    sumAntiTau = 0.
    sumAntiTauErr = 0.

    fakeFactor = 0.
    fakeFactorErr = 0.

    for p in processesTau:
        path = processesTau[p]

        if p == 'Data':

            histogramTauData = reader.getHistogram(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion+'/'+histo)
            sumTauData = histogramTauData.IntegralAndError(minBin,maxBin,integralTauDataErr)
            sumTauDataErr = pow(integralTauDataErr,2)

        elif p == background:

            histogramTauNoJet = reader.getHistogram(path,'Cut'+category+'NoJet'+prongs+trigger+controlRegion+'/'+histo)
            sumTauNoJet = histogramTauNoJet.IntegralAndError(minBin,maxBin,integralTauNoJetErr)
            sumTauNoJetErr = pow(integralTauNoJetErr,2)

        else:

            #dropped subtraction of j->tau MC
            #histogramTauMCJet = reader.getHistogram(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion+'/'+histo)
            #sumTauMCJet += histogramTauMCJet.IntegralAndError(minBin,maxBin,integralTauMCJetErr)
            #sumTauMCJetErr += pow(integralTauMCJetErr,2)

            histogramTauMCNoJet = reader.getHistogram(path,'Cut'+category+'NoJet'+prongs+trigger+controlRegion+'/'+histo)
            sumTauMCNoJet += histogramTauMCNoJet.IntegralAndError(minBin,maxBin,integralTauMCNoJetErr)
            sumTauMCNoJetErr += pow(integralTauMCNoJetErr,2)

    sumTauMCJet = 0.
    sumTauMCJetErr = 0.

    sumTauMC = sumTauMCJet + sumTauMCNoJet
    sumTauMCErr = sumTauMCJetErr + sumTauMCNoJetErr


    for p in processesAntiTau:
        path = processesAntiTau[p]

        if p == 'Data':

            histogramAntiTauData = reader.getHistogram(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion+'/'+histo)
            sumAntiTauData = histogramAntiTauData.IntegralAndError(minBin,maxBin,integralAntiTauDataErr)
            sumAntiTauDataErr = pow(integralAntiTauDataErr,2)

        elif p == background:

            histogramAntiTauNoJet = reader.getHistogram(path,'Cut'+category+'NoJet'+prongs+trigger+controlRegion+'/'+histo)
            sumAntiTauNoJet = -1.*histogramAntiTauNoJet.IntegralAndError(minBin,maxBin,integralAntiTauNoJetErr)
            sumAntiTauNoJetErr = pow(integralAntiTauNoJetErr,2)

        else:

            #dropped subtraction of j->tau MC
            #histogramAntiTauMCJet = reader.getHistogram(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion+'/'+histo)
            #sumAntiTauMCJet += -1.*histogramAntiTauMCJet.IntegralAndError(minBin,maxBin,integralAntiTauMCJetErr)
            #sumAntiTauMCJetErr += pow(integralAntiTauMCJetErr,2)

            histogramAntiTauMCNoJet = reader.getHistogram(path,'Cut'+category+'NoJet'+prongs+trigger+controlRegion+'/'+histo)
            sumAntiTauMCNoJet += -1.*histogramAntiTauMCNoJet.IntegralAndError(minBin,maxBin,integralAntiTauMCNoJetErr)
            sumAntiTauMCNoJetErr += pow(integralAntiTauMCNoJetErr,2)

    sumAntiTauMCJet = 0.
    sumAntiTauMCJetErr = 0.

    sumAntiTauMC = sumAntiTauMCJet + sumAntiTauMCNoJet
    sumAntiTauMCErr = sumAntiTauMCJetErr + sumAntiTauMCNoJetErr

    sumTau = sumTauData-sumTauMC-sumTauNoJet
    sumTauErr = pow(sumTauDataErr+sumTauMCErr+sumTauNoJetErr,0.5)

    sumAntiTau = sumAntiTauData-sumAntiTauMC-sumAntiTauNoJet
    sumAntiTauErr = pow(sumAntiTauDataErr+sumAntiTauMCErr+sumAntiTauNoJetErr,0.5)

    if sumAntiTau == 0.:
        if debug:
            print background + "-sumAntiTau is 0! setting FF to 0!"
            print "Bin: " + str(minBin)
            print 'sumTau: ' + str(sumTau)
            print 'sumTauData: ' + str(sumTauData)
            print 'sumTauMC: ' + str(sumTauMC)
            print 'sumTauNoJet: ' + str(sumTauNoJet)
            print 'sumAntiTau: ' + str(sumAntiTau)
            print 'sumAntiTauData: ' + str(sumAntiTauData)
            print 'sumAntiTauMC: ' + str(sumAntiTauMC)
            print 'sumAntiTauNoJet: ' + str(sumAntiTauNoJet)+'\n'
        fakeFactor = 0.
    else:
        fakeFactor = sumTau/sumAntiTau

    if fakeFactor > 0.25 or fakeFactor <= 0.:
        if debug:
            print background + "-FF smaller or equal to 0 or greater than 0.25!"
            print "FF: " + str(fakeFactor)
            print "Bin: " + str(minBin)
            print 'sumTau: ' + str(sumTau)
            print 'sumTauErr: ' + str(sumTauErr)
            print 'sumTauData: ' + str(sumTauData)
            print 'sumTauDataErr: ' + str(sumTauDataErr)
            print 'sumTauMC: ' + str(sumTauMC)
            print 'sumTauMCErr: ' + str(sumTauMCErr)
            print 'sumTauMCJet: ' + str(sumTauMCJet)
            print 'sumTauMCJetErr: ' + str(sumTauMCJetErr)
            print 'sumTauMCNoJet: ' + str(sumTauMCNoJet)
            print 'sumTauMCNoJetErr: ' + str(sumTauMCNoJetErr)
            print 'sumTauNoJet: ' + str(sumTauNoJet)
            print 'sumTauNoJetErr: ' + str(sumTauNoJetErr)
            print 'sumAntiTau: ' + str(sumAntiTau)
            print 'sumAntiTauErr: ' + str(sumAntiTauErr)
            print 'sumAntiTauData: ' + str(sumAntiTauData)
            print 'sumAntiTauDataErr: ' + str(sumAntiTauDataErr)
            print 'sumAntiTauMC: ' + str(sumAntiTauMC)
            print 'sumAntiTauMCErr: ' + str(sumAntiTauMCErr)
            print 'sumAntiTauMCJet: ' + str(sumAntiTauMCJet)
            print 'sumAntiTauMCJetErr: ' + str(sumAntiTauMCJetErr)
            print 'sumAntiTauMCNoJet: ' + str(sumAntiTauMCNoJet)
            print 'sumAntiTauMCNoJetErr: ' + str(sumAntiTauMCNoJetErr)
            print 'sumAntiTauNoJet: ' + str(sumAntiTauNoJet)
            print 'sumAntiTauNoJetErr: ' + str(sumAntiTauNoJetErr)+'\n'

    if (sumTau == 0 or sumAntiTau == 0):
        if debug:
            print 'sumTau or sumAntiTau 0: Setting FF Error to 0'
            print "FF: " + str(fakeFactor)
            print "Bin: " + str(minBin)
            print 'sumTau: ' + str(sumTau)
            print 'sumAntiTau: ' + str(sumAntiTau) + '\n'
        fakeFactorErr = 0.
    else:
        fakeFactorErr = fakeFactor*pow(pow(sumTauErr/sumTau,2) + pow(sumAntiTauErr/sumAntiTau,2),0.5)

    #print 'FFerr: ' + str(fakeFactorErr)

    ## before returning fil all data to the dict:
    #n is bin for fake calculation

    # sumTau = sumTauData-sumTauMC-sumTauNoJet
    # =============================================================
    # sumAntiTau = sumAntiTauData-sumAntiTauMC-sumAntiTauNoJet

    if doConstrain:
        if fakeFactor <= 0.:
            fakeFactor = 0.0001
            print "WARNING constrining FF to 0.0001 for %s" %(background)
        if fakeFactorErr <= 0.:
            fakeFactorErr = 0.0001


    ff_dict[category][trigger][prongs][region][background]["Bin_%s" %(minBin)] = {
        'sumTau'          : (sumTau,sumTauErr),
        'sumAntiTau'      : (sumAntiTau,sumAntiTauErr),

        'sumTauData'      : (sumTauData,pow(sumTauDataErr,0.5)),
        'sumTauMC'        : (sumTauMC,pow(sumTauMCErr,0.5)),
        'sumTauNoJet'     : (sumTauNoJet,pow(sumTauNoJetErr,0.5)),

        'sumAntiTauData'  : (sumAntiTauData,pow(sumAntiTauDataErr,0.5)),
        'sumAntiTauMC'    : (sumAntiTauMC,pow(sumAntiTauMCErr,0.5)),
        'sumAntiTauNoJet' : (sumAntiTauNoJet,pow(sumAntiTauNoJetErr,0.5)),
        'FF'              : (fakeFactor,fakeFactorErr)
        }

        #wFakeFactor = calcFakeFactor('W',n,n,prong,histo,category,trigger)
        #ff_dict[category][trigger][prong][region]['R_W'] = relConW


    # W MC

    # integralTauWErr = Double(0.)
    # integralAntiTauWErr = Double(0.)

    # histogramTauW = reader.getHistogram('./bkg/lephad/[WjetsMG+WjetsShEW]','Cut'+category+'Jet'+prongs+trigger+'WFR/'+histo)
    # sumTauW = histogramTauW.IntegralAndError(minBin,maxBin,integralTauWErr)
    # sumTauWErr = integralTauWErr
    # histogramAntiTauW = reader.getHistogram('./bkg/lephad/Fake/mc/[WjetsMG+WjetsShEW]','Cut'+category+'Jet'+prongs+trigger+'WFR/'+histo)
    # sumAntiTauW = -1.*histogramAntiTauW.IntegralAndError(minBin,maxBin,integralAntiTauWErr)
    # sumAntiTauWErr = integralAntiTauWErr

    # if sumAntiTauW == 0.:
    #     fakeFactor = 0.0001
    # else:
    #     fakeFactor = sumTauW/sumAntiTauW

    # if sumAntiTauW == 0. or sumTauW == 0.:
    #     fakeFactorErr = 0.0001
    # else:
    #     fakeFactorErr = fakeFactor*pow(pow(sumTauWErr/sumTauW,2) + pow(sumAntiTauWErr/sumAntiTauW,2),0.5)

    # if doConstrain:
    #     if fakeFactor <= 0.:
    #         fakeFactor = 0.0001
    #         print "WARNING constrining FF to 0.0001"
    #     if fakeFactorErr <= 0.:
    #         fakeFactorErr = 0.0001

    # print 'W'
    # print fakeFactor

    # TOP MC

    # integralTauTopErr = Double(0.)
    # integralAntiTauTopErr = Double(0.)

    # histogramTauTop = reader.getHistogram('./bkg/lephad/Top','Cut'+category+'Jet'+prongs+trigger+'TopCR/'+histo)
    # sumTauTop = histogramTauTop.IntegralAndError(minBin,maxBin,integralTauTopErr)
    # sumTauTopErr = integralTauTopErr
    # histogramAntiTauTop = reader.getHistogram('./bkg/lephad/Fake/mc/Top','Cut'+category+'Jet'+prongs+trigger+'TopCR/'+histo)
    # sumAntiTauTop = -1.*histogramAntiTauTop.IntegralAndError(minBin,maxBin,integralAntiTauTopErr)
    # sumAntiTauTopErr = integralAntiTauTopErr

    # if sumAntiTauTop == 0.:
    #     fakeFactor = 0.0001
    # else:
    #     fakeFactor = sumTauTop/sumAntiTauTop

    # if sumAntiTauTop == 0. or sumTauTop == 0.:
    #     fakeFactorErr = 0.0001
    # else:
    #     fakeFactorErr = fakeFactor*pow(pow(sumTauTopErr/sumTauTop,2) + pow(sumAntiTauTopErr/sumAntiTauTop,2),0.5)

    # if doConstrain:
    #     if fakeFactor <= 0.:
    #         fakeFactor = 0.0001
    #         print "WARNING constrining FF to 0.0001"
    #     if fakeFactorErr <= 0.:
    #         fakeFactorErr = 0.0001

    # print 'Top'
    # print fakeFactor

    # # Z MC

    # integralTauZErr = Double(0.)
    # integralAntiTauZErr = Double(0.)

    # histogramTauZ = reader.getHistogram('./bkg/lephad/[ZllMG+ZllShEW]','Cut'+category+'Jet'+prongs+trigger+'ZCR/'+histo)
    # sumTauZ = histogramTauZ.IntegralAndError(minBin,maxBin,integralTauZErr)
    # sumTauZErr = integralTauZErr
    # histogramAntiTauZ = reader.getHistogram('./bkg/lephad/Fake/mc/[ZllMG+ZllShEW]','Cut'+category+'Jet'+prongs+trigger+'ZCR/'+histo)
    # sumAntiTauZ = -1.*histogramAntiTauZ.IntegralAndError(minBin,maxBin,integralAntiTauZErr)
    # sumAntiTauZErr = integralAntiTauZErr

    # if sumAntiTauZ == 0.:
    #     fakeFactor = 0.0001
    # else:
    #     fakeFactor = sumTauZ/sumAntiTauZ

    # if sumAntiTauZ == 0. or sumTauZ == 0.:
    #     fakeFactorErr = 0.0001
    # else:
    #     fakeFactorErr = fakeFactor*pow(pow(sumTauZErr/sumTauZ,2) + pow(sumAntiTauZErr/sumAntiTauZ,2),0.5)

    # if doConstrain:
    #     if fakeFactor <= 0.:
    #         fakeFactor = 0.0001
    #         print "WARNING constrining FF to 0.0001"
    #     if fakeFactorErr <= 0.:
    #         fakeFactorErr = 0.0001

    # print 'Z'
    # print fakeFactor







    return (float(fakeFactor),float(fakeFactorErr))

# returns sum of the control region fake factors weighted by the relative contributions and error

###########################
##
##  Plot FF to file
##
##############################
def plotFF(hist,up,down,region, file='', name='someFF'):
    print '     Now Plotting to file '+name

    # Plot separated ff and save to pdf book
    c1 = TCanvas( 'c1', '', 200, 10, 700, 500 )
    c1.SetGrid()
    pdfname='FakeFactors/'+name+'.pdf'

    max = up.GetMaximum()
    min = down.GetMinimum()
    hist.GetYaxis().SetRangeUser(min-0.1, max+0.1);
    hist.SetStats(0)

    nBinsX=hist.GetNbinsX()
    x=array('f')
    y=array('f')
    exl=array('f')
    eyl=array('f')
    exh=array('f')
    eyh=array('f')
    for bin in range(1,nBinsX+1):
        x.append( hist.GetBinCenter(bin) )
        y.append( hist.GetBinContent(bin) )
        exl.append( hist.GetBinWidth(bin)/2. )
        eyl.append( hist.GetBinContent(bin) - down.GetBinContent(bin) )
        exh.append( hist.GetBinWidth(bin)/2. )
        eyh.append( up.GetBinContent(bin) - hist.GetBinContent(bin) )

    x.insert(0,hist.GetBinLowEdge(1)-1)
    y.insert(0,y[0])
    exl.insert(0,exl[0])
    eyl.insert(0,eyl[0])
    exh.insert(0,exh[0])
    eyh.insert(0,eyh[0])

    x.append(hist.GetBinLowEdge(nBinsX+1)+1)
    y.append(y[nBinsX])
    exl.append(exl[nBinsX])
    eyl.append(eyl[nBinsX])
    exh.append(exh[nBinsX])
    eyh.append(eyh[nBinsX])

    gr = TGraphAsymmErrors(nBinsX+2,x,y,exl,exh,eyl,eyh);
    gr.SetTitle(name);
    gr.SetFillColor(6);
    gr.SetFillStyle(3005);
    gr.SetMarkerColor(4);
    gr.SetMarkerStyle(21);
    gr.Draw("A3");

    hist.Draw('X0same')

    #ATLAS label
    ATLAS_LABEL(0.37,0.85,kBlack)
    myText(0.49,0.85,kBlack, "Internal");
    lumi = '56.9' if ("18" in region) else '44.3' if ("17" in region) else '36.2'
    myText(0.37,0.79,kBlack, '\sqrt s=13TeV, \int L dt = {:s} fb^-1'.format(lumi));

    # derive what ff is this
    text = ''
    if 'LFR' in name:
        text+='LFR'
    elif 'WFR' in name:
        text+='WFR'

    if 'ehad' in name:
        text+=' ehad'
    elif 'muhad' in name:
        text+=' muhad'
    elif 'lephad' in name:
        text+=' lephad'

    if '1p' in name:
        text += ' 1-prong'
    elif '3p' in name:
        text += ' 3-prong'

    myText(0.37,0.73,kBlack, text);

    gr.GetXaxis().SetRangeUser(hist.GetBinLowEdge(1),hist.GetBinLowEdge(nBinsX+1))
    gr.GetYaxis().SetTitle('Fake Factor')

    c1.Update()
    #c1.Print(pdfname)

    c1.Write()


############################
##
##  Lepton Fake Factor
##
############################
#calcLeptonFakeFactorFinal('Bveto','CutBvetoPassISO', 'CutBvetoFailISO' 'LeptonEtaELEFF', 'ehad','LFR')
def calcLeptonFakeFactorFinal(category, nominator, denominator, histogram, channel, region, mcsamples='?', syslist=[]):
    print '----------------------------------------------------------'
    print 'Now running '+region+' Fake Factor: '+category+'\t'+histogram+'\t'
    print '--------------------------------------------------------\n'

    histoPass = reader.getHistogram('[/data/{:s}-/bkg/{:s}/?]'.format(channel,channel),'Cut{:s}PassISO/{:s}'.format(category,histogram))
    histoFail = reader.getHistogram('[/data/{:s}-/bkg/{:s}/?]'.format(channel,channel),'Cut{:s}FailISO/{:s}'.format(category,histogram))
    if not histoPass or not histoFail:
        print 'Failed to get histograms. Skipping.'
        return

    FF_histo=histoPass.Clone()
    FF_histo.Divide(histoFail)
    FF_histo.SetName(category+channel)
    # check if there is negative entries
    nBinsX = FF_histo.GetNbinsX()
    for x in range(1,nBinsX+1):
        content = FF_histo.GetBinContent(x)
        if content < 0:
            print 'WARNING(\'Bin ({:f}) content negative, setting to zero: {:2f} -> {:f}'.format(x,content,0)
            FF_histo.SetBinContent(x,0)

    file = TFile('FakeFactors/LeptonFF'+category+channel+histogram+'.root','RECREATE')
    file.cd()
    FF_histo.Write()

    plotFF(FF_histo,region, file,'LeptonFF'+category+channel+histogram)

    file.Close()

def addOverflow(hist):
    # add overflow
    nBinsX = hist.GetNbinsX()
    hist.SetBinContent(nBinsX, hist.GetBinContent(nBinsX)+hist.GetBinContent(nBinsX+1))
    # add errors
    overError = hist.GetBinError(nBinsX+1)
    binError = hist.GetBinError(nBinsX)
    hist.SetBinError(nBinsX, sqrt(overError**2+binError**2))

def add2DOverflow(hist):
    nBinsX = hist.GetNbinsX()
    nBinsY = hist.GetNbinsY()
    for ybin in range(1,nBinsY+1):
        hist.SetBinContent(nBinsX, ybin, hist.GetBinContent(nBinsX,ybin)+hist.GetBinContent(nBinsX+1,ybin))
        # add errors
        overError = hist.GetBinError(nBinsX+1, ybin)
        binError = hist.GetBinError(nBinsX,ybin)
        hist.SetBinError(nBinsX, ybin, sqrt(overError**2+binError**2))


def doStatErrors(hist,scale=1):
    nBinsX = hist.GetNbinsX()
    for bin in range(1,nBinsX+1):
        hist.SetBinContent(bin, scale * hist.GetBinError(bin) )

def averageSys(hist1, hist2):
    nBinsX = hist1.GetNbinsX()
    if nBinsX != hist2.GetNbinsX():
        print "Error: different binning"
        return None

    # make positive
    for bin in range(0,nBinsX+1):
        hist1.SetBinContent(bin, fabs(hist1.GetBinContent(bin)))
        hist2.SetBinContent(bin, fabs(hist2.GetBinContent(bin)))
    # average
    temp = hist1.Clone()
    temp.Add(hist1,hist2,0.5,0.5)
    return temp

def doSysErrors(histError,hist1):
    # here we need to change histError - add hist1 in quadrature
    nBinsX = hist1.GetNbinsX()
    if nBinsX != histError.GetNbinsX():
        print "Error: different binning"
        return None
    # add content to histError
    for bin in range(0,nBinsX+1):
        tempError = hist1.GetBinContent(bin)
        oldError = histError.GetBinContent(bin)
        histError.SetBinContent(bin, sqrt(tempError**2+oldError**2))

def checkNegative(hist):
    nBinsX = hist.GetNbinsX()
    for bin in range(0,nBinsX+1):
        temp = hist.GetBinContent(bin)
        if temp<0:
            hist.SetBinContent(bin,0)


############################
##
##  jet-tau Fake Factor
##
##  input:
##  nominal sample
##  sys sample if needed
##  full path to nominator
##  full path to denominator
##  channel
##  mc sample names
##  othier identifiers: prong, region, etc.
##
############################
'''
FF calculation algorithm:
    nominal ff:
    get two hist with the convenient sample reader getHistogram("data/smth-bkg/smth")

    mc subtraction variation:
    get four histos (data,bkg)x(nominator,denominator)
    subtract after scaling background
    calculate sys ff
    extract differences
    do error=(sysUp+sysDown)/2

    other systematics:
    for the list of systematics, which should be in different root files,
    open file, get ff as in nominal case
    exract differences

    TODO: safety check that histos are got
'''
#calcJetFakeFactorFinal('Bveto','CutBvetoPassISO', 'CutBvetoFailISO' 'LeptonEtaELEFF', 'ehad','LFR',0.5)
# calcJetFakeFactorFinal('WFR', 'CutBvetoPassID', 'CutBvetoFailID', 'TauPtFF1p', 'lephad', 'WFR')

## examples:
## category = Bveto
## datapath = data/ehad/
## bkgpath = bkg/ehad/[Top+Diboson]
## nominator = CutBveto1pOSPassID
## denominator = CutBveto1pOSFailID
## histogram = TauPtFFBveto1p
## channel = ehad
## region = WFR

def calcJetFakeFactorFinal(category, datapath, bkgpath, nominator, denominator, histogram, channel, region, mcVar1=0.1,mcVar2=0.1, syslist=[]):
    print '----------------------------------------------------------'
    print 'Now running '+region + category+' Fake Factor: '+'\t'+channel+'\t'+histogram
    print '--------------------------------------------------------\n'
    doMCSys = True #True

    ## nominal
    histoPass = reader.getHistogram('{:s}-{:s}'.format(dataPath.format(channel),bkgpath.format(channel)),'{:s}/{:s}'.format(nominator,histogram))
    histoFail = reader.getHistogram('{:s}-{:s}'.format(dataPath.format(channel),bkgpath.format(channel)),'{:s}/{:s}'.format(denominator,histogram))

    # add overflow
    addOverflow(histoPass)
    addOverflow(histoFail)

    # calculate nominal
    FF_histo=histoPass.Clone()
    FF_histo.Divide(histoFail)
    FF_histo.SetName('{:s}FF_{:s}_{:s}'.format(category,channel,histogram))
    checkNegative(FF_histo)

    # create error hist, this should contain errors with respect to 0
    FF_histo_error = FF_histo.Clone()
    doStatErrors(FF_histo_error)

    if doMCSys:
        # get four histos
        histoDataPass = reader.getHistogram(datapath.format(channel),'{:s}/{:s}'.format(nominator,histogram))
        histoMCPass   = reader.getHistogram(bkgpath.format(channel),'{:s}/{:s}'.format(nominator,histogram))
        histoDataFail = reader.getHistogram(datapath.format(channel),'{:s}/{:s}'.format(denominator,histogram))
        histoMCFail   = reader.getHistogram(bkgpath.format(channel),'{:s}/{:s}'.format(denominator,histogram))

        # clone because will change a lot
        temp_histoDataPass = histoDataPass.Clone()
        temp_histoMCPass = histoMCPass.Clone()
        temp_histoDataFail = histoDataFail.Clone()
        temp_histoMCFail = histoMCFail.Clone()

        # scale mc
        temp_histoMCPass.Scale(1-mcVar1)
        temp_histoMCFail.Scale(1+mcVar2)

        # subtract
        temp_histoDataPass.Add(temp_histoMCPass,-1)
        temp_histoDataFail.Add(temp_histoMCFail,-1)
        # add overflow
        addOverflow(temp_histoDataPass)
        addOverflow(temp_histoDataFail)
        # calculate up variation ff
        temp_histo_up=temp_histoDataPass.Clone()
        temp_histo_up.Divide(temp_histoDataFail)
        # find difference between nominal and this
        temp_histo_up.Add(FF_histo,-1)

        # do the same for down
        # clone because will change a lot
        temp_histoDataPass = histoDataPass.Clone()
        temp_histoMCPass = histoMCPass.Clone()
        temp_histoDataFail = histoDataFail.Clone()
        temp_histoMCFail = histoMCFail.Clone()
        # scale mc
        temp_histoMCPass.Scale(1+mcVar1)
        temp_histoMCFail.Scale(1-mcVar2)

        # subtract
        temp_histoDataPass.Add(temp_histoMCPass,-1)
        temp_histoDataFail.Add(temp_histoMCFail,-1)
        # add overflow
        addOverflow(temp_histoDataPass)
        addOverflow(temp_histoDataFail)
        # calculate up variation ff
        temp_histo_down=temp_histoDataPass.Clone()
        temp_histo_down.Divide(temp_histoDataFail)
        # find difference between nominal and this
        temp_histo_down.Add(FF_histo,-1)

        # make positive definite and find average
        temp_histo_ave = averageSys(temp_histo_up, temp_histo_down)

        # add difference to error hist
        doSysErrors(FF_histo_error,temp_histo_ave)

    # at this point FF_histo_error contain stat and, if doMCSys, mc subtraction error

    # get systematic variations, assume different root files
    for sys in syslist:
        print sys
        # todo

    # calculate full error hist:
    FF_histo_up = FF_histo.Clone()
    FF_histo_up.Add(FF_histo_error)
    FF_histo_up.SetName(FF_histo.GetName()+'_up')
    checkNegative(FF_histo_up)
    FF_histo_down = FF_histo.Clone()
    FF_histo_down.Add(FF_histo_error,-1)
    FF_histo_down.SetName(FF_histo.GetName()+'_down')
    checkNegative(FF_histo_down)

    file = TFile('FakeFactors/'+region+category+channel+histogram+'.root','RECREATE')
    file.cd()
    FF_histo.Write()
    FF_histo_up.Write()
    FF_histo_down.Write()

    plotFF(FF_histo,FF_histo_up,FF_histo_down,region,file,region+category+channel+histogram)

    file.Close()

def calcQCDFakeFactorFinal(category, path, nominator, denominator, histogram, channel, region, qcdsub=False, mcVar=0.1, syslist=[]):
    print '----------------------------------------------------------'
    print 'Now running '+category+' Fake Factor: '+'\t'+histogram+'\t'+channel
    print '--------------------------------------------------------\n'
    doMCSys = False #True

    ## nominal
    print '{:s}'.format(path),'{:s}'.format(histogram)
    histoPass = reader.getHistogram('{:s}'.format(path),'{:s}/{:s}'.format(nominator,histogram))
    histoFail = reader.getHistogram('{:s}'.format(path),'{:s}/{:s}'.format(denominator,histogram))

    # add overflow
    addOverflow(histoPass)
    addOverflow(histoFail)


    channelname = channel.translate(None, delchars)
    # calculate nominal
    FF_histo=histoPass.Clone()
    FF_histo.Divide(histoFail)
    FF_histo.SetName('{:s}FF_{:s}_{:s}'.format(category,channelname,histogram))
    checkNegative(FF_histo)

    # create error hist, this should contain errors with respect to 0
    FF_histo_error = FF_histo.Clone()
    doStatErrors(FF_histo_error)

#    if doMCSys:
#        # get four histos
#        histoDataPass = reader.getHistogram('/data/{:s}'.format(channel),'{:s}/{:s}'.format(nominator,histogram))
#        histoMCPass = reader.getHistogram('/bkg/{:s}/{:s}'.format(channel,mcsamples),'{:s}/{:s}'.format(nominator,histogram))
#        histoDataFail = reader.getHistogram('/data/{:s}'.format(channel),'{:s}/{:s}'.format(denominator,histogram))
#        histoMCFail = reader.getHistogram('/bkg/{:s}/{:s}'.format(channel,mcsamples),'{:s}/{:s}'.format(denominator,histogram))
#
#        # clone because will change a lot
#        temp_histoDataPass = histoDataPass.Clone()
#        temp_histoMCPass = histoMCPass.Clone()
#        temp_histoDataFail = histoDataFail.Clone()
#        temp_histoMCFail = histoMCFail.Clone()
#
#        # scale mc
#        temp_histoMCPass.Scale(1-mcVar)
#        temp_histoMCFail.Scale(1+mcVar)
#
#        # subtract
#        temp_histoDataPass.Add(temp_histoMCPass,-1)
#        temp_histoDataFail.Add(temp_histoMCFail,-1)
#        # add overflow
#        addOverflow(temp_histoDataPass)
#        addOverflow(temp_histoDataFail)
#        # calculate up variation ff
#        temp_histo_up=temp_histoDataPass.Clone()
#        temp_histo_up.Divide(temp_histoDataFail)
#        # find difference between nominal and this
#        temp_histo_up.Add(FF_histo,-1)
#
#        # do the same for down
#        # clone because will change a lot
#        temp_histoDataPass = histoDataPass.Clone()
#        temp_histoMCPass = histoMCPass.Clone()
#        temp_histoDataFail = histoDataFail.Clone()
#        temp_histoMCFail = histoMCFail.Clone()
#        # scale mc
#        temp_histoMCPass.Scale(1+mcVar)
#        temp_histoMCFail.Scale(1-mcVar)
#
#        # subtract
#        temp_histoDataPass.Add(temp_histoMCPass,-1)
#        temp_histoDataFail.Add(temp_histoMCFail,-1)
#        # add overflow
#        addOverflow(temp_histoDataPass)
#        addOverflow(temp_histoDataFail)
#        # calculate up variation ff
#        temp_histo_down=temp_histoDataPass.Clone()
#        temp_histo_down.Divide(temp_histoDataFail)
#        # find difference between nominal and this
#        temp_histo_down.Add(FF_histo,-1)
#
#        # make positive definite and find average
#        temp_histo_ave = averageSys(temp_histo_up, temp_histo_down)
#
#        # add difference to error hist
#        doSysErrors(FF_histo_error,temp_histo_ave)

    # at this point FF_histo_error contain stat and, if doMCSys, mc subtraction error

    # get systematic variations, assume different root files
    for sys in syslist:
        print sys
        # todo

    # calculate full error hist:
    FF_histo_up = FF_histo.Clone()
    FF_histo_up.Add(FF_histo_error)
    FF_histo_up.SetName(FF_histo.GetName()+'_up')
    checkNegative(FF_histo_up)
    FF_histo_down = FF_histo.Clone()
    FF_histo_down.Add(FF_histo_error,-1)
    FF_histo_down.SetName(FF_histo.GetName()+'_down')
    checkNegative(FF_histo_down)

    file = TFile('FakeFactors/'+region+category+channelname+'.root','RECREATE')
    file.cd()
    FF_histo.Write()
    FF_histo_up.Write()
    FF_histo_down.Write()

    plotFF(FF_histo,FF_histo_up,FF_histo_down,region,file,region+category+channelname)

    file.Close()

def calcJet2DFakeFactorFinal(category, nominator, histogram, channel, region, mcVar=0.1, mcsamples='?', syslist=[]):
    print '----------------------------------------------------------'
    print 'Now running 2D jet Fake Factor: '+'\t'+histogram+'\t'+channel
    print '--------------------------------------------------------\n'
    doMCSys = False #True


    ## nominal
    histoFull = reader.getHistogram('/data/{:s}-/bkg/{:s}/{:s}'.format(channel,channel,mcsamples),'{:s}/{:s}'.format(nominator,histogram))

    channelname = channel.translate(None, delchars)
    histoFail=histoFull.ProjectionX("fail",1,1)
    addOverflow(histoFail)
    nBinsY = histoFull.GetNbinsY()
    for ybin in range(2,nBinsY+1):
        histoPass=histoFull.ProjectionX("pass"+str(ybin-1),ybin,ybin)
        addOverflow(histoPass)
        # calculate nominal
        FF_histo=histoPass.Clone()
        FF_histo.Divide(histoFail)
        FF_histo.SetName('{:s}FF_bdt{:s}_{:s}_{:s}'.format(category,str(ybin-1),channelname,histogram))
        checkNegative(FF_histo)

        # create error hist, this should contain errors with respect to 0
        FF_histo_error = FF_histo.Clone()
        doStatErrors(FF_histo_error)


        # calculate full error hist:
        FF_histo_up = FF_histo.Clone()
        FF_histo_up.Add(FF_histo_error)
        FF_histo_up.SetName(FF_histo.GetName()+'_up')
        checkNegative(FF_histo_up)
        FF_histo_down = FF_histo.Clone()
        FF_histo_down.Add(FF_histo_error,-1)
        FF_histo_down.SetName(FF_histo.GetName()+'_down')
        checkNegative(FF_histo_down)

        file = TFile('FakeFactors/'+region+category+'bdt'+str(ybin-1)+channelname+histogram+'.root','RECREATE')
        file.cd()
        FF_histo.Write()
        FF_histo_up.Write()
        FF_histo_down.Write()

        plotFF(FF_histo,FF_histo_up,FF_histo_down,region,file,region+category+'bdt'+str(ybin-1)+channelname+histogram)

        file.Close()


def calcMCFakeFactorFinal(category, nominator, denominator, histogram, channel, region, mcVar=0.1, mcsamples='?', syslist=[]):
    print '----------------------------------------------------------'
    print 'Now running MC Fake Factor: '+'\t'+histogram+'\t'+channel
    print '--------------------------------------------------------\n'

    ## nominal
    histoPass = reader.getHistogram('/bkg/{:s}/{:s}'.format(channel,mcsamples),'{:s}/{:s}'.format(nominator,histogram))
    histoFail = reader.getHistogram('/bkg/{:s}/{:s}'.format(channel,mcsamples),'{:s}/{:s}'.format(denominator,histogram))

    # add overflow
    addOverflow(histoPass)
    addOverflow(histoFail)


    channelname = channel.translate(None, delchars)
    # calculate nominal
    FF_histo=histoPass.Clone()
    FF_histo.Divide(histoFail)
    FF_histo.SetName('{:s}FF_{:s}_{:s}'.format(category,channelname,histogram))
    checkNegative(FF_histo)

    # create error hist, this should contain errors with respect to 0
    FF_histo_error = FF_histo.Clone()
    doStatErrors(FF_histo_error)

    # get systematic variations, assume different root files
    for sys in syslist:
        print sys
        # todo

    # calculate full error hist:
    FF_histo_up = FF_histo.Clone()
    FF_histo_up.Add(FF_histo_error)
    FF_histo_up.SetName(FF_histo.GetName()+'_up')
    checkNegative(FF_histo_up)
    FF_histo_down = FF_histo.Clone()
    FF_histo_down.Add(FF_histo_error,-1)
    FF_histo_down.SetName(FF_histo.GetName()+'_down')
    checkNegative(FF_histo_down)

    file = TFile('FakeFactors/'+region+category+channelname+histogram+'.root','RECREATE')
    file.cd()
    FF_histo.Write()
    FF_histo_up.Write()
    FF_histo_down.Write()

    plotFF(FF_histo,FF_histo_up,FF_histo_down,region,file, region+category+channelname+histogram)

    file.Close()

#calcDphiCorrectionFinal(Bveto, Bveto1pPass, TauMETDphiCorrection, ehad, WFR, mcVar=0.1, mcsamples='?', syslist=[]):
def calcDphiCorrectionFinal(category, datapath, bkgpath, correctionpath, cut, histogram, channel, region, mcVar=0.1, mcsamples='?', syslist=[]):
    print '----------------------------------------------------------'
    print 'Now running '+region + category+' dphi correction: '+'\t'+channel+'\t'+histogram
    print '--------------------------------------------------------\n'
    doMCSys = False
    #mcsamples = '[SherpaWjetsTruthTau+SherpaWjetsLepFake+TopTruthTau+TopLepFake+ZtautauTruthTau+ZtautauLepFake+DibosonTruthTau+DibosonLepFake+ZeeLepFake+ZmumuLepFake]'
    mcsamples = '[SherpaWjets+Top+Ztautau+Zee+Zmumu+Diboson]'

  # if qcd:
  #     qcdfile = 'output/htautau_lephad_wfr_contid/nominal_qcd.root'
  #     qcdsamples = TQSampleFolder.loadLazySampleFolder(qcdfile+':samples')
  #     qcdreader = TQSampleDataReader(qcdsamples)

  # wjetsfile = 'output/htautau_lephad_wfr_contid/nominal_applyff.root'
  # wjetssamples = TQSampleFolder.loadLazySampleFolder(wjetsfile+':samples')
  # wjetsreader = TQSampleDataReader(wjetssamples)

    ## nominal
    histoData = reader.getHistogram('{:s}-{:s}'.format(dataPath.format(channel),bkgpath.format(channel)),'{:s}/{:s}'.format(cut,histogram))
    histoCorr = reader.getHistogram(correctionpath.format(channel),'{:s}/{:s}'.format(cut,histogram))

    # calculate nominal
    dphi_histo=histoData.Clone()
    dphi_histo.Divide(histoCorr)
    dphi_histo.SetName('dphicorr_{:s}_{:s}_{:s}'.format(category,channel,histogram))
    checkNegative(dphi_histo)

    # create error hist, this should contain errors with respect to 0
    dphi_histo_error = dphi_histo.Clone()
    doStatErrors(dphi_histo_error)

    # get systematic variations, assume different root files
    for sys in syslist:
        print sys
        # todo

    # calculate full error hist:
    dphi_histo_up = dphi_histo.Clone()
    dphi_histo_up.Add(dphi_histo_error)
    dphi_histo_up.SetName(dphi_histo.GetName()+'_up')
    checkNegative(dphi_histo_up)
    dphi_histo_down = dphi_histo.Clone()
    dphi_histo_down.Add(dphi_histo_error,-1)
    dphi_histo_down.SetName(dphi_histo.GetName()+'_down')
    checkNegative(dphi_histo_down)

    file = TFile('FakeFactors/'+region+category+channel+histogram+'.root','RECREATE')
    file.cd()
    dphi_histo.Write()
    dphi_histo_up.Write()
    dphi_histo_down.Write()

    plotFF(dphi_histo,dphi_histo_up,dphi_histo_down,region,file, region+category+ch+histogram)

    file.Close()


def calcLFRDphiCorrectionFinal(category, cut, histogram, channel, region, mcVar=0.1, mcsamples='?', syslist=[]):
    print '----------------------------------------------------------'
    print 'Now running LFR dphi correction: '+'\t'+histogram+'\t'+channel+'\t'+category
    print '--------------------------------------------------------\n'
    doMCSys = False
    #mcsamples = '[SherpaWjetsTruthTau+SherpaWjetsLepFake+TopTruthTau+TopLepFake+ZtautauTruthTau+ZtautauLepFake+DibosonTruthTau+DibosonLepFake+ZeeLepFake+ZmumuLepFake]'
    mcsamples = '[SherpaWjets+Top+Ztautau+Zee+Zmumu+Diboson]'

    ## nominal
    histoData = reader.getHistogram('/data/{:s}-/bkg/{:s}/{:s}'.format(channel,channel,mcsamples),'{:s}/{:s}'.format(cut,histogram))

    histoQCD = reader.getHistogram('/bkg/{:s}/Fake'.format(channel),'{:s}/{:s}'.format(cut,histogram))



    channelname = channel.translate(None, delchars)
    # calculate nominal
    dphi_histo=histoData.Clone()
    dphi_histo.Divide(histoQCD)
    dphi_histo.SetName('dphicorr_{:s}_{:s}_{:s}'.format(category,channelname,histogram))
    checkNegative(dphi_histo)

    # create error hist, this should contain errors with respect to 0
    dphi_histo_error = dphi_histo.Clone()
    doStatErrors(dphi_histo_error)


    # get systematic variations, assume different root files
    for sys in syslist:
        print sys
        # todo

    # calculate full error hist:
    dphi_histo_up = dphi_histo.Clone()
    dphi_histo_up.Add(dphi_histo_error)
    dphi_histo_up.SetName(dphi_histo.GetName()+'_up')
    checkNegative(dphi_histo_up)
    dphi_histo_down = dphi_histo.Clone()
    dphi_histo_down.Add(dphi_histo_error,-1)
    dphi_histo_down.SetName(dphi_histo.GetName()+'_down')
    checkNegative(dphi_histo_down)

    file = TFile('FakeFactors/'+region+category+channelname+histogram+'.root','RECREATE')
    file.cd()
    dphi_histo.Write()
    dphi_histo_up.Write()
    dphi_histo_down.Write()

    plotFF(dphi_histo,dphi_histo_up,dphi_histo_down,region,file, region+category+channelname+histogram)

    file.Close()

## rqcd = n(qcd)/n(data-mc truth)
#calcRQCDFinal('Btag','/AntiID/ehad/data/','/AntiID/ehad/mc/[Top+Ztautau+Diboson+Zee+Zmumu]', '/AntiID/ehad/QCD/data','/AntiID/ehad/QCD/mc/[Top+Ztautau+Diboson+Zee+Zmumu]', '[CutBtag1p+CutBtag3p]','TauPtRQCD', 'ehad','AntiID',0.5)
def calcRQCDFinal(category, datapath, mcpaht, qcddatapath, qcdmcpath, cut, histogram, channel, region, mcVar=0.1, mcsamples='?', syslist=[]):
    print '----------------------------------------------------------'
    print 'Now running '+category+' rQCD: '+'\t'+histogram+'\t'+channel
    print '--------------------------------------------------------\n'
    doMCSys = False #True

    ## nominal
    histoQCD = reader.getHistogram('{:s}-{:s}'.format(qcddatapath,qcdmcpath),'{:s}/{:s}'.format(cut,histogram))
    histoData = reader.getHistogram('{:s}-{:s}'.format(datapath,mcpaht),'{:s}/{:s}'.format(cut,histogram))

    # add overflow
    addOverflow(histoQCD)
    addOverflow(histoData)

    # calculate nominal
    rqcd_histo=histoQCD.Clone()
    rqcd_histo.Divide(histoData)
    rqcd_histo.SetName('rqcd_{:s}_{:s}_{:s}'.format(category,channel,histogram))
    checkNegative(rqcd_histo)

    # create error hist, this should contain errors with respect to 0
    rqcd_histo_error = rqcd_histo.Clone()
    doStatErrors(rqcd_histo_error)

    if doMCSys:
        # get four histos
        histoDataDenom = reader.getHistogram('{:s}'.format(datapath),'{:s}/{:s}'.format(cut,histogram))
        histoMCDenom = reader.getHistogram('{:s}'.format(mcpaht),'{:s}/{:s}'.format(cut,histogram))
        histoDataNom = reader.getHistogram('{:s}'.format(qcddatapath),'{:s}/{:s}'.format(cut,histogram))
        histoMCNom = reader.getHistogram('{:s}'.format(qcdmcpath),'{:s}/{:s}'.format(cut,histogram))

        # clone because will change a lot
        temp_histoDataDenom = histoDataDenom.Clone()
        temp_histoMCDenom   = histoMCDenom.Clone()
        temp_histoDataNom   = histoDataNom.Clone()
        temp_histoMCNom     = histoMCNom.Clone()

        # scale mc
        temp_histoMCDenom.Scale(1-mcVar)
        temp_histoMCNom.Scale(1+mcVar)

        # subtract
        temp_histoDataDenom.Add(temp_histoMCDenom,-1)
        temp_histoDataNom.Add(temp_histoMCNom,-1)
        # add overflow
        addOverflow(temp_histoDataDenom)
        addOverflow(temp_histoDataNom)
        # calculate up variation ff
        temp_histo_up=temp_histoDataNom.Clone()
        temp_histo_up.Divide(temp_histoDataDenom)
        # find difference between nominal and this
        temp_histo_up.Add(rqcd_histo,-1)

        # do the same for down
        # clone because will change a lot
        temp_histoDataDenom = histoDataDenom.Clone()
        temp_histoMCDenom   = histoMCDenom.Clone()
        temp_histoDataNom   = histoDataNom.Clone()
        temp_histoMCNom     = histoMCNom.Clone()
        # scale mc
        temp_histoMCDenom.Scale(1+mcVar)
        temp_histoMCNom.Scale(1-mcVar)

        # subtract
        temp_histoDataDenom.Add(temp_histoMCDenom,-1)
        temp_histoDataNom.Add(temp_histoMCNom,-1)
        # add overflow
        addOverflow(temp_histoDataDenom)
        addOverflow(temp_histoDataNom)
        # calculate up variation ff
        temp_histo_down=temp_histoDataNom.Clone()
        temp_histo_down.Divide(temp_histoDataDenom)
        # find difference between nominal and this
        temp_histo_down.Add(rqcd_histo,-1)

        # make positive definite and find average
        temp_histo_ave = averageSys(temp_histo_up, temp_histo_down)

        # add difference to error hist
        doSysErrors(rqcd_histo_error,temp_histo_ave)

    # at this point FF_histo_error contain stat and, if doMCSys, mc subtraction error

    # get systematic variations, assume different root files
    for sys in syslist:
        print sys
        # todo

    # calculate full error hist:
    rqcd_histo_up = rqcd_histo.Clone()
    rqcd_histo_up.Add(rqcd_histo_error)
    rqcd_histo_up.SetName(rqcd_histo.GetName()+'_up')
    checkNegative(rqcd_histo_up)
    rqcd_histo_down = rqcd_histo.Clone()
    rqcd_histo_down.Add(rqcd_histo_error,-1)
    rqcd_histo_down.SetName(rqcd_histo.GetName()+'_down')
    checkNegative(rqcd_histo_down)

    file = TFile('FakeFactors/'+region+category+channel+histogram+'.root','RECREATE')
    file.cd()
    rqcd_histo.Write()
    rqcd_histo_up.Write()
    rqcd_histo_down.Write()

    plotFF(rqcd_histo,rqcd_histo_up,rqcd_histo_down,region,file, region+category+channel+histogram)

    file.Close()




#calcFakeFactorFinal(['1Prong','3Prong'], 'TauPtVSTauJetBDTScoreTrans', category_list, ['SLT'],['TopCR','QCDCR','ZCR','WFR','SR'])
def calcFakeFactorFinal(prongs, histoname, categories, triggers, regions):

    for category in categories:
        print '-------------------------------------------------'
        print 'Now running: '+category
        print '-------------------------------------------------\n'

        prong = ''
        if '1p' in category:
            prong = '1P'
        elif '3p' in category:
            prong = '3P'
        else:
            print WARNING('can\'t figure out prongness')
        #with this line you get 2D hist with all bkg subtracted
        histo = reader.getHistogram('[/data/lephad-/bkg/lephad/?]','Cut'+category+'/'+histoname+prong)
        nBinsX = histo.GetNbinsX()
        nBinsY = histo.GetNbinsY() # First bin in Y axis is denominator

        # add overflow
        for y in range(1,nBinsY+1):
            overflow = histo.GetBinContent(nBinsX+1,y)
            lastbin = histo.GetBinContent(nBinsX,y)
            histo.SetBinContent(nBinsX,y,overflow+lastbin)

        # check if there is negative entries
        for x in range(1,nBinsX+2):
            for y in range(1,nBinsY+1):
                content = histo.GetBinContent(x,y)
                if content < 0:
                    print 'WARNING(\'Bin ({:f},{:f}) content negative, setting to zero: {:f} -> {:f}'.format(x,y,content,0)
                    histo.SetBinContent(x,y,0)

        # In order to automatically calculate stat errors we just create dummy 2D histogram
        # of the same order with all entries along x axis the same and being the first bin
        # on y axis (denominator)
        dummy_histo = histo.Clone()
        for x in range(1,nBinsX+1):
            denom = dummy_histo.GetBinContent(x,1)
            for y in range(1,nBinsY+1):
                dummy_histo.SetBinContent(x,y,denom)

        FF_histo = histo.Clone()
        FF_histo.Divide(histo,dummy_histo)
        FF_histo.SetName(category)
        FF_histo.SetTitle(category)
        FF_histo.SetOption("colztext")

        file = TFile('FakeFactors/'+regions+category+'.root','RECREATE')
        file.cd()
        FF_histo.Write()



        # Plot separated ff and save to pdf book
        c1 = TCanvas( 'c1', '', 200, 10, 700, 500 )
        c1.SetGrid()
        pdfname='FakeFactors/'+regions+category+'.pdf'
        c1.Print(pdfname+'[')

        for y in range(2,nBinsY+1):
            hist1d = FF_histo.ProjectionX('BDTbin'+str(y-1)+'_prong-'+prong,y,y)
            hist1d.SetTitle('BDTbin'+str(y-1)+'_prong-'+prong)
            hist1d.SetStats(0)
            hist1d.Write()
            hist1d.Draw()
            c1.Print(pdfname)

        c1.Print(pdfname+']')
        file.Close()
       ##print category, nBins
       #ff_dict[category] = {}
       #        if info or debug:
       #            print '-------------------------------------------------'
       #            print 'Now running: '+category
       #            print '-------------------------------------------------\n'

       #        ## fill dict with all FF info
       #        ff_dict[category][trigger][prong][region]['W']   = {}
       #        ff_dict[category][trigger][prong][region]['Z']   = {}
       #        ff_dict[category][trigger][prong][region]['Top'] = {}
       #        ff_dict[category][trigger][prong][region]['Sum'] = {}


       #        relConW   = calcRelCon('W',category,prong,trigger,region)
       #        relConTop = calcRelCon('Top',category,prong,trigger,region)
       #        relConZ   = calcRelCon('Z',category,prong,trigger,region)

       #        ## force R values to reasonable numbers
       #        if doConstrain:
       #            relConW,relConTop,relConZ = constrain_R_values(relConW,relConTop,relConZ,category,trigger,prong,region)
       #        relConQCD = (1. - relConW[0] - relConZ[0] - relConTop[0], pow(pow(relConW[1],2)+pow(relConZ[1],2)+pow(relConTop[1],2),0.5))

       #        ff_dict[category][trigger][prong][region]['QCD'] = {
       #            'R'             : relConQCD,
       #            'k'             : (0. , 0. ),
       #            'sumJet_SR'     : 0.,
       #            'sumData_SR'    : 0.,
       #            'sumOtherMC_SR' : 0.
       #            }
       #        for n in range(1,nBins+1):

       #            #print "DEBUG::: deriving FF for bin %s" %(n)
       #            wFakeFactor = calcFakeFactor('W',n,n,prong,histo,category,trigger,region)
       #            wFakeFactorVal = wFakeFactor[0]
       #            wFakeFactorErr = wFakeFactor[1]

       #            topFakeFactor = calcFakeFactor('Top',n,n,prong,histo,category,trigger,region)
       #            topFakeFactorVal = topFakeFactor[0]
       #            topFakeFactorErr = topFakeFactor[1]

       #            zFakeFactor = calcFakeFactor('Z',n,n,prong,histo,category,trigger,region)
       #            zFakeFactorVal = zFakeFactor[0]
       #            zFakeFactorErr = zFakeFactor[1]

       #            qcdFakeFactor = calcFakeFactor('QCD',n,n,prong,histo,category,trigger,region)
       #            qcdFakeFactorVal = qcdFakeFactor[0]
       #            qcdFakeFactorErr = qcdFakeFactor[1]

       #            #print type(relConW[0]), type(wFakeFactor[0]),type(relConTop[0]), type(topFakeFactor[0]),type(relConZ[0]), type(zFakeFactor[0]),type(relConQCD), type(qcdFakeFactor[0])

       #            sumFakeFactor = relConW[0]*wFakeFactor[0] + relConTop[0]*topFakeFactor[0] + relConZ[0]*zFakeFactor[0] + relConQCD[0]*qcdFakeFactor[0]
       #            sumFakeFactorErr = pow(pow(relConW[1]   *wFakeFactor[0],2)  +pow(relConW[0]  *wFakeFactor[1],2)
       #                                   +pow(relConTop[1]*topFakeFactor[0],2)+pow(relConTop[0]*topFakeFactor[1],2)
       #                                   +pow(relConZ[1]  *zFakeFactor[0],2)  +pow(relConZ[0]  *zFakeFactor[1],2)
       #                                   +pow(relConQCD[1]*qcdFakeFactor[0],2)+pow(relConQCD[0]*qcdFakeFactor[1],2),0.5)



       #            if doConstrain:
       #                if sumFakeFactor <= 0.:
       #                    sumFakeFactor = 0.0001
       #                    print "WARNING constrining sum FF to 0.0001"
       #                if sumFakeFactorErr <= 0.:
       #                    sumFakeFactorErr = 0.0001

       #            # #W MC
       #            #sumFakeFactor = wFakeFactor[0]
       #            #sumFakeFactorErr = wFakeFactor[1]

       #            # #TOP MC
       #            #sumFakeFactor = topFakeFactor[0]
       #            #sumFakeFactorErr = topFakeFactor[1]

       #            # #Z MC
       #            #sumFakeFactor = zFakeFactor[0]
       #            #sumFakeFactorErr = zFakeFactor[1]

       #            #print 'sum'
       #            #print sumFakeFactor

       #            ff_dict[category][trigger][prong][region]['Sum']['Bin_%s'%(n)] = { 'FF' : (sumFakeFactor,sumFakeFactorErr) }

       #        if info: print  'QCD: relCon: ' + str(relConQCD[0]) + ' +\- ' + str(relConQCD[1]) + '\n'
    return


def plot(prongs, histo, categories, triggers, regions):

    ## set batch mode and ATLAS Style
    gROOT.SetBatch(True)
    gROOT.ForceStyle()
    gStyle.SetPalette(1)

    c = TCanvas('c','c',600,600)
    hFile = TFile('ff_july.root','new')
    for category in categories:
        for trigger in triggers:
            dummyHisto = reader.getHistogram('./data','Cut'+category+'NoJet1Prong'+trigger+'SR/'+histo)
            nBins = dummyHisto.GetNbinsX()
            xAxis = dummyHisto.GetXaxis()
            binArray = []
            for i in range(0,nBins+1):
                upperBinEdge = xAxis.GetBinUpEdge(i)
                binArray.insert(i,upperBinEdge)
            for prong in prongs:
                h1 = TH1D('W_'+category+'_'+prong+'_'+trigger,prong,nBins,array('d',binArray))
                h2 = TH1D('Top_'+category+'_'+prong+'_'+trigger,'',nBins,array('d',binArray))
                h3 = TH1D('Z_'+category+'_'+prong+'_'+trigger,'',nBins,array('d',binArray))
                h4 = TH1D('QCD_'+category+'_'+prong+'_'+trigger,'',nBins,array('d',binArray))
                for region in regions:
                    if info or debug:
                        print '-------------------------------------------------'
                        print 'Now running: '+category+' '+prong+' '+trigger+' '+region
                        print '-------------------------------------------------\n'

                    if category == 'BOOSTCB' and prong == '1Prong' and trigger == 'SLT':
                        yRange = 0.4
                    elif category == 'BOOSTCB' and prong == '3Prong' and trigger == 'SLT':
                        yRange = 0.1
                    elif category == 'VBFCB' and prong == '1Prong' and trigger == 'SLT':
                        yRange = 0.4
                    elif category == 'VBFCB' and prong == '3Prong' and trigger == 'SLT':
                        yRange = 0.15
                    elif category == 'Preselection' and prong == '1Prong' and trigger == 'SLT':
                        yRange = 0.4
                    elif category == 'Preselection' and prong == '3Prong' and trigger == 'SLT':
                        yRange = 0.1
                    else:
                        yRange = 5.


                    #relConW = calcRelCon('W',category,prong,trigger,region)
                    #relConTop = calcRelCon('Top',category,prong,trigger,region)
                    #relConZ = calcRelCon('Z',category,prong,trigger,region)
                    #relConQCD = 1. - relConW[0] - relConZ[0] - relConTop[0]
                    #relConQCDErr = pow(pow(relConW[1],2)+pow(relConZ[1],2)+pow(relConTop[1],2),0.5)

                    ## read back values from big dict:
                    relConW      = ff_dict[category][trigger][prong][region]['W']['R']
                    relConTop    = ff_dict[category][trigger][prong][region]['Z']['R']
                    relConZ      = ff_dict[category][trigger][prong][region]['Top']['R']
                    relConQCD    = ff_dict[category][trigger][prong][region]['QCD']['R'][0]
                    relConQCDErr = ff_dict[category][trigger][prong][region]['QCD']['R'][1]


                    if info: print  'QCD: relCon: ' + str(relConQCD) + ' +\- ' + str(relConQCDErr) + '\n'


                    h5 = TH1D('Sum_'+category+'_'+prong+'_'+trigger+'_'+region,'',nBins,array('d',binArray))

                    h1.GetXaxis().SetTitle("p_{T}^{#tau} [GeV]")
                    h1.GetYaxis().SetTitle('FF')
                    h2.GetXaxis().SetTitle("p_{T}^{#tau} [GeV]")
                    h2.GetYaxis().SetTitle('FF')
                    h3.GetXaxis().SetTitle("p_{T}^{#tau} [GeV]")
                    h3.GetYaxis().SetTitle('FF')
                    h4.GetXaxis().SetTitle("p_{T}^{#tau} [GeV]")
                    h4.GetYaxis().SetTitle('FF')
                    h1.GetYaxis().SetRangeUser(0,yRange)

                    gStyle.SetOptStat(0)

                    for n in range(1,nBins+1):

                        wFakeFactor = ff_dict[category][trigger][prong][region]['W']['Bin_%s' %(n)]['FF']
                        #wFakeFactor = calcFakeFactor('W',n,n,prong,histo,category,trigger)
                        wFakeFactorVal = wFakeFactor[0]
                        wFakeFactorErr = wFakeFactor[1]

                        h1.SetLineColor(kRed)
                        h1.SetMarkerStyle(1)
                        h1.SetLineWidth(2)
                        if region == 'SR':
                            h1.AddBinContent(n,wFakeFactorVal)
                            h1.SetBinError(n,wFakeFactorErr)
                        h1.Draw('E')

                        topFakeFactor = ff_dict[category][trigger][prong][region]['Top']['Bin_%s' %(n)]['FF']
                        #topFakeFactor = calcFakeFactor('Top',n,n,prong,histo,category,trigger)
                        topFakeFactorVal = topFakeFactor[0]
                        topFakeFactorErr = topFakeFactor[1]

                        h2.SetLineColor(kBlue)
                        h2.SetMarkerStyle(1)
                        h2.SetLineWidth(2)
                        if region == 'SR':
                            h2.AddBinContent(n,topFakeFactorVal)
                            h2.SetBinError(n,topFakeFactorErr)
                        h2.Draw('SAME')

                        zFakeFactor = ff_dict[category][trigger][prong][region]['Z']['Bin_%s' %(n)]['FF']
                        #zFakeFactor = calcFakeFactor('Z',n,n,prong,histo,category,trigger)
                        zFakeFactorVal = zFakeFactor[0]
                        zFakeFactorErr = zFakeFactor[1]

                        h3.SetLineColor(kGreen)
                        h3.SetMarkerStyle(1)
                        h3.SetLineWidth(2)
                        if region == 'SR':
                            h3.AddBinContent(n,zFakeFactorVal)
                            h3.SetBinError(n,zFakeFactorErr)
                        h3.Draw('SAME')

                        qcdFakeFactor = ff_dict[category][trigger][prong][region]['QCD']['Bin_%s' %(n)]['FF']
                        #qcdFakeFactor = calcFakeFactor('QCD',n,n,prong,histo,category,trigger)
                        qcdFakeFactorVal = qcdFakeFactor[0]
                        qcdFakeFactorErr = qcdFakeFactor[1]

                        h4.SetLineColor(kMagenta)
                        h4.SetMarkerStyle(1)
                        h4.SetLineWidth(2)
                        if region == 'SR':
                            h4.AddBinContent(n,qcdFakeFactorVal)
                            h4.SetBinError(n,qcdFakeFactorErr)
                        h4.Draw('SAME')

                        #sumFakeFactor = relConW[0]*wFakeFactorVal + relConTop[0]*topFakeFactorVal + relConZ[0]*zFakeFactorVal + relConQCD*qcdFakeFactorVal
                        #errA = relConW[0]*wFakeFactorVal*pow(pow(relConW[1]/relConW[0],2) + pow(wFakeFactorErr/wFakeFactorVal,2),0.5)
                        #errB = relConTop[0]*topFakeFactorVal*pow(pow(relConTop[1]/relConTop[0],2) + pow(topFakeFactorErr/topFakeFactorVal,2),0.5)
                        #errC = relConZ[0]*zFakeFactorVal*pow(pow(relConZ[1]/relConZ[0],2) + pow(zFakeFactorErr/zFakeFactorVal,2),0.5)
                        #errD = relConQCD*qcdFakeFactorVal*pow(pow(relConQCDErr/relConQCD,2) + pow(qcdFakeFactorErr/qcdFakeFactorVal,2),0.5)
                        #sumFakeFactorErrAlt = pow(pow(errA,2)+pow(errB,2)+pow(errC,2)+pow(errD,2),0.5)
                        #sumFakeFactorErr = pow(pow(relConW[1]*wFakeFactorVal,2)+pow(relConW[0]*wFakeFactorErr,2)+pow(relConTop[1]*topFakeFactorVal,2)+pow(relConTop[0]*topFakeFactorErr,2)+pow(relConZ[1]*zFakeFactorVal,2)+pow(relConZ[0]*zFakeFactorErr,2)+pow(relConQCDErr*qcdFakeFactorVal,2)+pow(relConQCD*qcdFakeFactorErr,2),0.5)
                        ##switch to FF_dict:
                        sumFakeFactor    = ff_dict[category][trigger][prong][region]['Sum']['Bin_%s' %(n)]['FF'][0]
                        sumFakeFactorErr = ff_dict[category][trigger][prong][region]['Sum']['Bin_%s' %(n)]['FF'][1]


                        #h5.GetXaxis().SetTitle(histo)
                        h5.SetMarkerStyle(1)
                        h5.AddBinContent(n,sumFakeFactor)
                        h5.SetBinError(n,sumFakeFactorErr)
                        h5.Draw('SAME')




                    #leg = TLegend(0.1,0.7,0.48,0.9)
                    leg = TLegend(0.8,0.55,0.9,0.75)
                    leg.AddEntry(h1,'W','l')
                    leg.AddEntry(h2,'Top','l')
                    leg.AddEntry(h3,'Z','l')
                    leg.AddEntry(h4,'QCD','l')
                    leg.AddEntry(h5,'Sum','l')
                    leg.Draw('SAME')

                    ATLAS_LABEL(0.37,0.85,kBlack)
                    myText(0.55,0.85,kBlack,'Work in Progress')
                    if (category == 'BOOSTCB' and prong == '1Prong' and trigger == 'SLT' and region == 'SR'):
                        myText(0.35,0.78,kBlack,'Boosted, N_{trks} = 1, SLT')
                    elif (category == 'BOOSTCB' and prong == '3Prong' and trigger == 'SLT' and region == 'SR'):
                        myText(0.35,0.78,kBlack,'Boosted, N_{trks} = 3, SLT')
                    elif (category == 'VBFCB' and prong == '1Prong' and trigger == 'SLT' and region == 'SR'):
                        myText(0.45,0.78,kBlack,'VBF, N_{trks} = 1, SLT')
                    elif (category == 'VBFCB' and prong == '3Prong' and trigger == 'SLT' and region == 'SR'):
                        myText(0.45,0.78,kBlack,'VBF, N_{trks} = 3, SLT')
                    elif (category == 'Preselection' and prong == '1Prong' and trigger == 'SLT' and region == 'SR'):
                        myText(0.35,0.78,kBlack,'Preselection, N_{trks} = 1, SLT')
                    elif (category == 'Preselection' and prong == '3Prong' and trigger == 'SLT' and region == 'SR'):
                        myText(0.35,0.78,kBlack,'Preselection, N_{trks} = 3, SLT')

                    h5.GetXaxis().SetTitle("p_{T}^{#tau} [GeV]")
                    h5.GetYaxis().SetTitle('FF')

                    h5.SetLineColor(kBlack)
                    h5.SetLineWidth(2)
                    #h5.SetName('Sum_'+category+'_'+prong+'_'+trigger+'_'+region+'_R_dn')
                    #h5.SetTitle('Sum_'+category+'_'+prong+'_'+trigger+'_'+region+'_R_dn')
                    #h5.SetName('Sum_'+category+'_'+prong+'_'+trigger+'_'+region+'_R_up')
                    #h5.SetTitle('Sum_'+category+'_'+prong+'_'+trigger+'_'+region+'_R_up')
                    h5.SetName('Sum_'+category+'_'+prong+'_'+trigger+'_'+region)
                    h5.SetTitle('Sum_'+category+'_'+prong+'_'+trigger+'_'+region)
                    h5.Write()
                    #h5.Draw('E')
                    #c.SaveAs(prong+'_'+category+'_'+trigger+'_'+region+'_FF_july.pdf')
                    #c.SaveAs(prong+'_'+category+'_'+trigger+'_'+region+'_FF_july.eps')
    #h1.Draw('E')
    #h2.Draw('SAME')
    #h3.Draw('SAME')
    #h4.Draw('SAME')
    #h5.Draw('SAME')

                h1.Write()
                h2.Write()
                h3.Write()
                h4.Write()


    hFile.Close()

    return 'great'



def calcPurity(background,category, prongs, trigger):

    print '-------------------------'
    print '|'+background+'_'+category+'_'+prongs+'_'+trigger+'|'
    print '-------------------------\n'

    processesAntiTau = {'W':'./bkg/lephad/Fake/mc/[WjetsMG+WjetsShEW]',
                        'Z':'./bkg/lephad/Fake/mc/[ZllMG+ZllShEW]',
                        'Ztt':'./bkg/lephad/Fake/mc/[ZttMG+ZttShEW]',
                        'Top':'./bkg/lephad/Fake/mc/Top',
                        'DiBoson':'./bkg/lephad/Fake/mc/Diboson'
                        }

    processesTau = {'W':'./bkg/lephad/[WjetsMG+WjetsShEW]',
                    'Z':'./bkg/lephad/[ZllMG+ZllShEW]',
                    'Ztt':'./bkg/lephad/[ZttMG+ZttShEW]',
                    'Top':'./bkg/lephad/Top',
                    'DiBoson':'./bkg/lephad/Diboson'
                    }

    controlRegion = background+'CR'

    for process in [processesTau,processesAntiTau]:
        sumNoJet = 0.
        sumJet = 0.
        sumOtherMCNoJet = 0.
        sumOtherMCJet = 0.
        sumBackground = 0.
        sumOtherMC = 0.
        purity = 0.
        factor = 1.
        if 'Fake' in str(process):
            factor = -1.
            print 'AntiTau'
        else:
            print 'Tau'
        for p in process:
            path = process[p]

            if p == background:
                sumNoJet = factor*samples.getCounter(path,'Cut'+category+'NoJet'+prongs+trigger+controlRegion).getCounter()
                #print p + ' NoJet: ' + str(sumNoJet)
                sumJet = factor*samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion).getCounter()
                #print p + ' Jet: ' + str(sumJet)
            else:
                sumOtherMCNoJet += factor*samples.getCounter(path,'Cut'+category+'NoJet'+prongs+trigger+controlRegion).getCounter()
                #print p + ' NoJet: ' + str(factor*samples.getCounter(path,'Cut'+category+'NoJet'+prongs+trigger+controlRegion).getCounter())
                sumOtherMCJet += factor*samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion).getCounter()
                #print p + ' Jet: ' + str(factor*samples.getCounter(path,'Cut'+category+'Jet'+prongs+trigger+controlRegion).getCounter())

        sumBackground = sumNoJet + sumJet
        sumOtherMC = sumOtherMCNoJet + sumOtherMCJet
        purity = sumBackground/(sumBackground + sumOtherMC)
        subjtau = sumOtherMCJet/sumOtherMC

        print background + ': ' + str(sumBackground)
        print 'Other: ' + str(sumOtherMC)
        print 'Purity: ' + str(purity*100.) + "%"
        print 'Subtracted j->tau percentage: ' + str(subjtau*100) + "%\n"

#### main ####





if __name__=='__main__':

    from optparse import OptionParser

    parser=OptionParser(usage="usage: python %prog [options] REGION")
    parser.add_option("-p","--plot", action="store_true"  ,dest="plot"  ,default=False     ,help="plot FF histos")
    parser.add_option("-t","--table", action="store_true"  ,dest="table"  ,default=False     ,help="dump info in latex table")
    parser.add_option("-i","--info",  action="store_true"  ,dest="info"  ,default=False     ,help="show INFO output")
    parser.add_option("-d","--debug",  action="store_true"  ,dest="debug"  ,default=False     ,help="show DEBUG output")
    parser.add_option("-f","--file",  type="string"    ,dest="sFile"  ,default="output/htautau_lephad_wfr/nominal_ff.root"    ,help="input file for FF calculation")
    parser.add_option("-c","--constrain", action="store_true"  ,dest="constrain"  ,default=False     ,help="force R and FF to positive numbers")

    (options,args)=parser.parse_args()

    import sys
    # argument
    if len(args)==0:
        print 'You must submit an argument REGION: \n\t WFR; \n\t LFR; \n\t etc.'
        sys.exit()
    region = args[0]

    from QFramework import *
    from math import *
    from ROOT import *
    from array import array
    import itertools

    ROOT.gROOT.LoadMacro("scripts/AtlasStyle/AtlasStyle.C")
    ROOT.gROOT.LoadMacro("scripts/AtlasStyle/AtlasUtils.C")
    ROOT.gROOT.SetBatch(kTRUE)
    SetAtlasStyle()

    # options
    debug = options.debug
    info = options.info
    doConstrain = options.constrain

    # decide which file is needed:
    if region == 'WFR':
        sFile = 'sampleFolders/analyzed/samples-analyzed-htautau_lephad_wfr.root'
    elif region == 'LFR':
        sFile = 'sampleFolders/analyzed/samples-analyzed-htautau_lephad_lfr.root'
    elif region == 'WFRcontid':
        sFile = 'output/htautau_lephad_wfr_contid/nominal.root'
    elif region == 'WFRdphiCorr':
        sFile = 'output/htautau_lephad_wfr/nominal.root'
    #sFile = options.sFile
    #sFile = 'output/htautau_lephad_wfr/nominal.root'
    #sFile = 'output/htautau_lephad_wfr_contid/nominal.root'
    #sFile = 'output/htautau_lephad_sswcr_contid/nominal_ff.root'
    #sFile = 'output/htautau_lephad_sswcr/nominal_ff.root'
    #sFile = 'output/htautau_lephad_ssoswcr/nominal_ff.root'
    #sFile = 'output/htautau_lephad_wfr_contid/nominal.root'
    #sFile = 'output/htautau_lephad_lfr/nominal.root'
    #sFile = 'output/htautau_lephad_lfr/nominal_applyff.root'
    #sFile = 'output/htautau_lephad_qcdcr/nominal_ff.root'
    #sFile = 'output/htautau_lephad_qcdcr/nominal.root'
    #sFile = 'output/htautau_lephad_vr/nominal_rqcd.root'

    #get the sample folder:
    sFolder = 'samples'
    samples = TQSampleFolder.loadLazySampleFolder(sFile+':'+sFolder)
    reader = TQSampleDataReader(samples)



    #category_list = ['BOOSTCB','BOOSTHIGHCB','BOOSTLOWCB','VBFCB','VBFTIGHTCB','VBFLOOSECB','Preselection']
    #category_list = ['VBFCB']
    #category_list = ['BOOSTCB','BOOSTHIGHCB','BOOSTLOWCB','VBFCB','VBFTIGHTCB','VBFLOOSECB','Preselection']
    category_list = ['Bveto1p','Bveto3p','Btag1p','Btag3p']

    for category in category_list:
        ff_dict[category] = {}

    ###############################calcFakeFactorFinal(['1Prong','3Prong'], 'TauPtVSTauJetBDTScoreTrans', category_list, ['SLT'],'WFR')


    if options.plot:
        plot(['1Prong','3Prong'], 'tauPt', category_list, ['SLT'],['TopCR','QCDCR','ZCR','WFR','SR'])
        #plot(['1Prong','3Prong'], 'tauPt', category_list, ['SLT'],['SR'])
    if options.table:
        dumpValuesinTable()


    if region == 'WFR':
        #dataPath = 'data/{:s}/data17*'
        ##bkgPath = 'bkg/{:s}/[Top+Ztautau+Zee+Zmumu+Diboson+Fake/data]'
        #bkgPath = 'bkg/{:s}/[Ztautau]'
        #calcJetFakeFactorFinal('2017Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR')
        #calcJetFakeFactorFinal('2017Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'ehad', 'WFR')
        #calcJetFakeFactorFinal('2017Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'muhad', 'WFR')
        #calcJetFakeFactorFinal('2017Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'lephad', 'WFR')
        #calcJetFakeFactorFinal('2017Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'ehad', 'WFR')
        #calcJetFakeFactorFinal('2017Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'muhad', 'WFR')

        #calcJetFakeFactorFinal('2017Btag', dataPath, bkgPath, 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR')
        #calcJetFakeFactorFinal('2017Btag', dataPath, bkgPath, 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'ehad', 'SSWFR')
        #calcJetFakeFactorFinal('2017Btag', dataPath, bkgPath, 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'muhad', 'SSWFR')
        #calcJetFakeFactorFinal('2017Btag', dataPath, bkgPath, 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR')
        #calcJetFakeFactorFinal('2017Btag', dataPath, bkgPath, 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'ehad', 'SSWFR')
        #calcJetFakeFactorFinal('2017Btag', dataPath, bkgPath, 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'muhad', 'SSWFR')

        #calcJetFakeFactorFinal('2017Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'lephad', 'WFR')
        #calcJetFakeFactorFinal('2017Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'lephad', 'WFR')
        #calcJetFakeFactorFinal('2017Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'lephad', 'WFR')
        #calcJetFakeFactorFinal('2017Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'lephad', 'WFR')
        #calcJetFakeFactorFinal('2017Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'lephad', 'WFR')
        #calcJetFakeFactorFinal('2017Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'lephad', 'WFR')

        dataPath = 'data/{:s}/c16a/[data15*+data16*]'
        bkgPath = 'bkg/{:s}/c16a/[Top+Ztautau+Zee+Zmumu+Diboson+Fake/data/[data15*+data16*]]'
        # lephad 
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR15',0.1,0.1)
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'lephad', 'WFR15',0.1,0.1)

        #calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR15',0.1,0.1)
        #calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR15',0.1,0.1)

        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'lephad', 'WFR15',0.1,0.1)
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'lephad', 'WFR15',0.1,0.1)
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'lephad', 'WFR15',0.1,0.1)
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'lephad', 'WFR15',0.1,0.1)
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'lephad', 'WFR15',0.1,0.1)
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'lephad', 'WFR15',0.1,0.1)

        # ehad 
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'ehad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'ehad', 'WFR15',0.1,0.1)

        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'ehad', 'SSWFR15',0.1,0.1)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'ehad', 'SSWFR15',0.1,0.1)

        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'ehad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'ehad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'ehad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'ehad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'ehad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'ehad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi4', 'ehad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi4', 'ehad', 'WFR15',0.1,0.1)

        # muhad 
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'muhad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'muhad', 'WFR15',0.1,0.1)

        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'muhad', 'SSWFR15',0.1,0.1)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'muhad', 'SSWFR15',0.1,0.1)

        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'muhad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'muhad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'muhad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'muhad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'muhad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'muhad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi4', 'muhad', 'WFR15',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi4', 'muhad', 'WFR15',0.1,0.1)

        dataPath = 'data/{:s}/c16d/[data17*]'
        bkgPath = 'bkg/{:s}/c16d/[Top+Ztautau+Zee+Zmumu+Diboson+Fake/data/[data17*]]'
        # lephad
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR17',0.1,0.1)
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'lephad', 'WFR17',0.1,0.1)

        #calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR17',0.1,0.1)
        #calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR17',0.1,0.1)

        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'lephad', 'WFR17',0.1,0.1)
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'lephad', 'WFR17',0.1,0.1)
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'lephad', 'WFR17',0.1,0.1)
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'lephad', 'WFR17',0.1,0.1)
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'lephad', 'WFR17',0.1,0.1)
        #calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'lephad', 'WFR17',0.1,0.1)

        # ehad
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'ehad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'ehad', 'WFR17',0.1,0.1)

        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'ehad', 'SSWFR17',0.1,0.1)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'ehad', 'SSWFR17',0.1,0.1)

        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'ehad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'ehad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'ehad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'ehad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'ehad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'ehad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi4', 'ehad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi4', 'ehad', 'WFR17',0.1,0.1)

        # muhad
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'muhad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'muhad', 'WFR17',0.1,0.1)

        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'muhad', 'SSWFR17',0.1,0.1)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'muhad', 'SSWFR17',0.1,0.1)

        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'muhad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'muhad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'muhad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'muhad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'muhad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'muhad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi4', 'muhad', 'WFR17',0.1,0.1)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi4', 'muhad', 'WFR17',0.1,0.1)


        dataPath = 'data/{:s}/c16e/[data18*]'
        bkgPath = 'bkg/{:s}/c16e/[Top+Ztautau+Zee+Zmumu+Diboson+Fake/data/[data18*]]'
        # lephad
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'lephad', 'WFR18')

        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR18')
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR18')

        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'lephad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'lephad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'lephad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'lephad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'lephad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'lephad', 'WFR18')

        # ehad
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'ehad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'ehad', 'WFR18')

        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'ehad', 'SSWFR18')
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'ehad', 'SSWFR18')

        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'ehad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'ehad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'ehad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'ehad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'ehad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'ehad', 'WFR18')

        # muhad
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'muhad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'muhad', 'WFR18')

        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'muhad', 'SSWFR18')
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'muhad', 'SSWFR18')

        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'muhad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'muhad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'muhad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'muhad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'muhad', 'WFR18')
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'muhad', 'WFR18')


    elif region == 'LFR':
        dataPath = 'data/{:s}/c16a/[data15*+data16*]'
        #bkgPath = 'mc16a/{:s}/[Top+Ztautau+Zee+Zmumu+Diboson]'#+SherpaWjets]'
        bkgPath = 'bkg/{:s}/c16a/[Top+Ztautau+Zee+Zmumu+Diboson+SherpaWjets]'

        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtELEBVETOFF', 'ehad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtELEBTAGFF','ehad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtMUONFF','muhad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtMUONFF', 'muhad','LFR15',0.1,0.2)
	#muhad FFs missing - will try to add them now
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi1ELEBVETOFF', 'ehad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi2ELEBVETOFF', 'ehad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi3ELEBVETOFF', 'ehad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi4ELEBVETOFF', 'ehad','LFR15',0.1,0.2)

	#adding muon ffs, but not sure about naming scheme
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi1MUONBVETOFF', 'muhad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi2MUONBVETOFF', 'muhad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi3MUONBVETOFF', 'muhad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi4MUONBVETOFF', 'muhad','LFR15',0.1,0.2)


        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi1ELEBTAGFF', 'ehad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi2ELEBTAGFF', 'ehad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi3ELEBTAGFF', 'ehad','LFR15',0.1,0.2)

        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi1MUONBTAGFF', 'muhad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi2MUONBTAGFF', 'muhad','LFR15',0.1,0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi3MUONBTAGFF', 'muhad','LFR15',0.1,0.2)

	#now adding 2017

        dataPath = 'data/{:s}/c16d/[data17*]'
        #bkgPath = 'mc16c/{:s}/[Top+Ztautau+Zee+Zmumu+Diboson]'#+SherpaWjets]'
        bkgPath = 'bkg/{:s}/c16d/[Top+Ztautau+Zee+Zmumu+Diboson+SherpaWjets]'

        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtELEBVETOFF', 'ehad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtELEBTAGFF','ehad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtMUONFF','muhad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtMUONFF', 'muhad','LFR17',0.1,0.2)

        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi1ELEBVETOFF', 'ehad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi2ELEBVETOFF', 'ehad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi3ELEBVETOFF', 'ehad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi4ELEBVETOFF', 'ehad','LFR17',0.1,0.2)

        #adding muon ffs, but not sure about naming scheme
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi1MUONBVETOFF', 'muhad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi2MUONBVETOFF', 'muhad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi3MUONBVETOFF', 'muhad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi4MUONBVETOFF', 'muhad','LFR17',0.1,0.2)


        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi1ELEBTAGFF', 'ehad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi2ELEBTAGFF', 'ehad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi3ELEBTAGFF', 'ehad','LFR17',0.1,0.2)

        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi1MUONBTAGFF', 'muhad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi2MUONBTAGFF', 'muhad','LFR17',0.1,0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi3MUONBTAGFF', 'muhad','LFR17',0.1,0.2)

    #now adding 2018

        dataPath = 'data/{:s}/c16e/[data18*]'
        #bkgPath = 'mc16c/{:s}/[Top+Ztautau+Zee+Zmumu+Diboson]'#+SherpaWjets]'
        bkgPath = 'bkg/{:s}/c16e/[Top+Ztautau+Zee+Zmumu+Diboson+SherpaWjets]'

        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtELEBVETOFF', 'ehad','LFR18',0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtELEBTAGFF','ehad','LFR18',0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtMUONFF','muhad','LFR18',0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtMUONFF', 'muhad','LFR18',0.2)

        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi1ELEBVETOFF', 'ehad','LFR18',0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi2ELEBVETOFF', 'ehad','LFR18',0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi3ELEBVETOFF', 'ehad','LFR18',0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi4ELEBVETOFF', 'ehad','LFR18',0.2)

        #adding muon ffs, but not sure about naming scheme
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi1MUONBVETOFF', 'muhad','LFR18',0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi2MUONBVETOFF', 'muhad','LFR18',0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi3MUONBVETOFF', 'muhad','LFR18',0.2)
        calcJetFakeFactorFinal('Bveto', dataPath, bkgPath, 'CutBvetoBDTSLPassISO', 'CutBvetoBDTSLFailISO', 'LeptonPtDphi4MUONBVETOFF', 'muhad','LFR18',0.2)


        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi1ELEBTAGFF', 'ehad','LFR18',0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi2ELEBTAGFF', 'ehad','LFR18',0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi3ELEBTAGFF', 'ehad','LFR18',0.2)

        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi1MUONBTAGFF', 'muhad','LFR18',0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi2MUONBTAGFF', 'muhad','LFR18',0.2)
        calcJetFakeFactorFinal('Btag', dataPath, bkgPath, 'CutBtagBDTSLPassISO', 'CutBtagBDTSLFailISO', 'LeptonPtDphi3MUONBTAGFF', 'muhad','LFR18',0.2)


    elif region == 'WFRcontid':
        dataPath = 'data/{:s}'
        bkgPath = 'bkg/{:s}/[Top+Ztautau+Zee+Zmumu+Diboson+Fake/data]'
        calcJetFakeFactorFinal('BvetoBDT1', dataPath, bkgPath, 'CutBveto1pBDT1', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT2', dataPath, bkgPath, 'CutBveto1pBDT2', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT3', dataPath, bkgPath, 'CutBveto1pBDT3', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT4', dataPath, bkgPath, 'CutBveto1pBDT4', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR15')

        calcJetFakeFactorFinal('BvetoBDT1', dataPath, bkgPath, 'CutBveto3pBDT1', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT2', dataPath, bkgPath, 'CutBveto3pBDT2', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT3', dataPath, bkgPath, 'CutBveto3pBDT3', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'lephad', 'WFR15')

        calcJetFakeFactorFinal('BtagBDT1', dataPath, bkgPath, 'CutBtag1pBDT1', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR15')
        calcJetFakeFactorFinal('BtagBDT2', dataPath, bkgPath, 'CutBtag1pBDT2', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR15')
        calcJetFakeFactorFinal('BtagBDT3', dataPath, bkgPath, 'CutBtag1pBDT3', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR15')
        calcJetFakeFactorFinal('BtagBDT4', dataPath, bkgPath, 'CutBtag1pBDT4', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR15')

        calcJetFakeFactorFinal('BtagBDT1', dataPath, bkgPath, 'CutBtag3pBDT1', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR15')
        calcJetFakeFactorFinal('BtagBDT2', dataPath, bkgPath, 'CutBtag3pBDT2', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR15')
        calcJetFakeFactorFinal('BtagBDT3', dataPath, bkgPath, 'CutBtag3pBDT3', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR15')

        calcJetFakeFactorFinal('BvetoBDT1', dataPath, bkgPath, 'CutBveto1pBDT1', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT1', dataPath, bkgPath, 'CutBveto1pBDT1', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT1', dataPath, bkgPath, 'CutBveto1pBDT1', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT2', dataPath, bkgPath, 'CutBveto1pBDT2', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT2', dataPath, bkgPath, 'CutBveto1pBDT2', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT2', dataPath, bkgPath, 'CutBveto1pBDT2', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT3', dataPath, bkgPath, 'CutBveto1pBDT3', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT3', dataPath, bkgPath, 'CutBveto1pBDT3', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT3', dataPath, bkgPath, 'CutBveto1pBDT3', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT4', dataPath, bkgPath, 'CutBveto1pBDT4', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi1', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT4', dataPath, bkgPath, 'CutBveto1pBDT4', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi2', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT4', dataPath, bkgPath, 'CutBveto1pBDT4', 'CutBveto1pOSFailID', 'TauPtFFBveto1pDphi3', 'lephad', 'WFR15')

        calcJetFakeFactorFinal('BvetoBDT1', dataPath, bkgPath, 'CutBveto3pBDT1', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT1', dataPath, bkgPath, 'CutBveto3pBDT1', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT1', dataPath, bkgPath, 'CutBveto3pBDT1', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT2', dataPath, bkgPath, 'CutBveto3pBDT2', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT2', dataPath, bkgPath, 'CutBveto3pBDT2', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT2', dataPath, bkgPath, 'CutBveto3pBDT2', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT3', dataPath, bkgPath, 'CutBveto3pBDT3', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi1', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT3', dataPath, bkgPath, 'CutBveto3pBDT3', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi2', 'lephad', 'WFR15')
        calcJetFakeFactorFinal('BvetoBDT3', dataPath, bkgPath, 'CutBveto3pBDT3', 'CutBveto3pOSFailID', 'TauPtFFBveto3pDphi3', 'lephad', 'WFR15')

    elif region == 'WFRdphiCorr':
        dataPath = 'data/{:s}'
        bkgPath = 'bkg/{:s}/[Top+Ztautau+Zee+Zmumu+Diboson+Fake/data]'
        correctionPath = ''
        calcDphiCorrectionFinal('Bveto1p', dataPath, bkgPath, correctionPath, 'CutBveto1pPassID', 'TauMETDphiCorrection', 'lephad', 'WFRdphiCorr')

    #calcDphiCorrectionFinal('Bveto1p', 'CutBveto1pPassID', 'TauMETDphiCorrection', 'ehad', 'WFRdphi')
    ## function calcRQCDFinal(sensible category tag, data path, mc path, qcd data path, qcd mc path, cut name, histogram, channel, sensible region tag, mc subtraction variation)
    ##calcRQCDFinal('Btag','/AntiID/ehad/data/','/AntiID/ehad/mc/[Top+Ztautau+Diboson+Zee+Zmumu]', '/AntiID/ehad/QCD/data','/AntiID/ehad/QCD/mc/[Top+Ztautau+Diboson+Zee+Zmumu]', '[CutBtag1p+CutBtag3p]','TauPtRQCD', 'ehad','AntiID',0.2)
    ##calcRQCDFinal('Btag','/AntiID/muhad/data/','/AntiID/muhad/mc/[Top+Ztautau+Diboson+Zee+Zmumu]', '/AntiID/muhad/QCD/data','/AntiID/muhad/QCD/mc/[Top+Ztautau+Diboson+Zee+Zmumu]', '[CutBtag1p+CutBtag3p]','TauPtRQCD', 'muhad','AntiID',0.2)
    ##calcRQCDFinal('Bveto','/AntiID/ehad/data/','/AntiID/ehad/mc/[Top+Ztautau+Diboson+Zee+Zmumu]', '/AntiID/ehad/QCD/data','/AntiID/ehad/QCD/mc/[Top+Ztautau+Diboson+Zee+Zmumu]', '[CutBveto1p+CutBveto3p]','TauPtRQCD', 'ehad','AntiID',0.2)
    ##calcRQCDFinal('Bveto','/AntiID/muhad/data/','/AntiID/muhad/mc/[Top+Ztautau+Diboson+Zee+Zmumu]', '/AntiID/muhad/QCD/data','/AntiID/muhad/QCD/mc/[Top+Ztautau+Diboson+Zee+Zmumu]', '[CutBveto1p+CutBveto3p]','TauPtRQCD', 'muhad','AntiID',0.2)
    ##calcRQCDFinal('Btag','CutBtag','TauPtRQCD', 'muhad','VRAntiID',0.5)
    ##calcRQCDFinal('Btag','CutBtag','TauPtRQCD', 'ehad','VRAntiID',0.5)
    ##calcRQCDFinal('Bveto','CutBveto','TauPtRQCD', 'muhad','VRAntiID',0.5)
    ##calcRQCDFinal('Bveto','CutBveto','TauPtRQCD', 'ehad','VRAntiID',0.5)

    #############################
    ####
    #### QCD FF
    ####
    ###############################
    #calcQCDFakeFactorFinal('Bveto1p', 'data/[ehad+muhad]/ - /bkg/[ehad+muhad]/[Top+Ztautau+Diboson+Zee+Zmumu]', 'CutBveto1pOSPassID', 'CutBveto1pOSFailID','TauPtFFBveto1p', 'lephad', 'QCDCR')
    #calcQCDFakeFactorFinal('Bveto1pSS', 'data/[ehad+muhad]/ - /bkg/[ehad+muhad]/[Top+Ztautau+Diboson+Zee+Zmumu]', 'CutBveto1pSSPassID', 'CutBveto1pSSFailID','TauPtFFBveto1p', 'lephad', 'QCDCR')
    #
    #calcQCDFakeFactorFinal('Bveto3p', 'data/[ehad+muhad]/ - /bkg/[ehad+muhad]/[Top+Ztautau+Diboson+Zee+Zmumu]', 'CutBveto3pOSPassID', 'CutBveto3pOSFailID','TauPtFFBveto3p', 'lephad', 'QCDCR')
    #calcQCDFakeFactorFinal('Bveto3pSS', 'data/[ehad+muhad]/ - /bkg/[ehad+muhad]/[Top+Ztautau+Diboson+Zee+Zmumu]', 'CutBveto3pSSPassID', 'CutBveto3pSSFailID','TauPtFFBveto3p', 'lephad', 'QCDCR')
    #
    #
    #calcQCDFakeFactorFinal('Btag1p', 'data/[ehad+muhad]/ - /bkg/[ehad+muhad]/[Top+Ztautau+Diboson+Zee+Zmumu]', 'CutBtag1pOSPassID', 'CutBtag1pOSFailID','TauPtFFBtag1p', 'lephad', 'QCDCR')
    #calcQCDFakeFactorFinal('Btag1pSS', 'data/[ehad+muhad]/ - /bkg/[ehad+muhad]/[Top+Ztautau+Diboson+Zee+Zmumu]', 'CutBtag1pSSPassID', 'CutBtag1pSSFailID','TauPtFFBtag1p', 'lephad', 'QCDCR')
    #
    #calcQCDFakeFactorFinal('Btag3p', 'data/[ehad+muhad]/ - /bkg/[ehad+muhad]/[Top+Ztautau+Diboson+Zee+Zmumu]', 'CutBtag3pOSPassID', 'CutBtag3pOSFailID','TauPtFFBtag3p', 'lephad', 'QCDCR')
    #calcQCDFakeFactorFinal('Btag3pSS', 'data/[ehad+muhad]/ - /bkg/[ehad+muhad]/[Top+Ztautau+Diboson+Zee+Zmumu]', 'CutBtag3pSSPassID', 'CutBtag3pSSFailID','TauPtFFBtag3p', 'lephad', 'QCDCR')

    #############################
    ####
    #### OS WJETS FF
    #### some no qcd
    ####
    #<<<<<<< HEAD:share/scripts/calculateFakeFactorContID.py
    ###############################
    #calcJetFakeFactorFinal('BvetoBDT1', 'CutBveto1pBDT1', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR')
    #calcJetFakeFactorFinal('BvetoBDT2', 'CutBveto1pBDT2', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR')
    #calcJetFakeFactorFinal('BvetoBDT3', 'CutBveto1pBDT3', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR')
    #calcJetFakeFactorFinal('BvetoBDT4', 'CutBveto1pBDT4', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR')
    #
    #calcJetFakeFactorFinal('BvetoBDT1', 'CutBveto3pBDT1', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'lephad', 'WFR')
    #calcJetFakeFactorFinal('BvetoBDT2', 'CutBveto3pBDT2', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'lephad', 'WFR')
    #calcJetFakeFactorFinal('BvetoBDT3', 'CutBveto3pBDT3', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'lephad', 'WFR')
    #
    #calcJetFakeFactorFinal('BtagBDT1', 'CutBtag1pBDT1', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR')
    #calcJetFakeFactorFinal('BtagBDT2', 'CutBtag1pBDT2', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR')
    #calcJetFakeFactorFinal('BtagBDT3', 'CutBtag1pBDT3', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR')
    #calcJetFakeFactorFinal('BtagBDT4', 'CutBtag1pBDT4', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR')
    #
    #calcJetFakeFactorFinal('BtagBDT1', 'CutBtag3pBDT1', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR')
    #calcJetFakeFactorFinal('BtagBDT2', 'CutBtag3pBDT2', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR')
    #calcJetFakeFactorFinal('BtagBDT3', 'CutBtag3pBDT3', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR')
    ##############################
    #
    ################################
    ####
    #### SS TOP FF,
    #### some should not include qcd
    ####
    ################################
    #calcJetFakeFactorFinal('BtagBDT1', 'CutBtag1pBDT1', 'CutBtag1pFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR')
    ##calcJetFakeFactorFinal('BtagBDT2', 'CutBtag1pBDT2', 'CutBtag1pFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR',False)
    ##calcJetFakeFactorFinal('BtagBDT3', 'CutBtag1pBDT3', 'CutBtag1pFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR',False)
    ##calcJetFakeFactorFinal('BtagBDT4', 'CutBtag1pBDT4', 'CutBtag1pFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR',False)
    #
    ##calcJetFakeFactorFinal('BtagBDT1', 'CutBtag3pBDT1', 'CutBtag3pFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR')
    ##calcJetFakeFactorFinal('BtagBDT2', 'CutBtag3pBDT2', 'CutBtag3pFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR')
    ##calcJetFakeFactorFinal('BtagBDT3', 'CutBtag3pBDT3', 'CutBtag3pFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR')
    #################################
    #
    ##calcJetFakeFactorFinal('BvetoBDT1', 'CutBveto3pBDT1', 'CutBveto3pFailID', 'TauPtFF3p', 'lephad', 'WFR')
    ##calcJetFakeFactorFinal('BvetoBDT1', 'CutBveto3pBDT1', 'CutBveto3pFailID', 'TauPtFF3p', 'ehad', 'WFR')
    ##calcJetFakeFactorFinal('BvetoBDT1', 'CutBveto3pBDT1', 'CutBveto3pFailID', 'TauPtFF3p', 'muhad', 'WFR')
    ##calcJetFakeFactorFinal('BvetoBDT2', 'CutBveto3pBDT2', 'CutBveto3pFailID', 'TauPtFF3p', 'lephad', 'WFR')
    ##calcJetFakeFactorFinal('BvetoBDT2', 'CutBveto3pBDT2', 'CutBveto3pFailID', 'TauPtFF3p', 'ehad', 'WFR')
    ##calcJetFakeFactorFinal('BvetoBDT2', 'CutBveto3pBDT2', 'CutBveto3pFailID', 'TauPtFF3p', 'muhad', 'WFR')
    ##calcJetFakeFactorFinal('BvetoBDT3', 'CutBveto3pBDT3', 'CutBveto3pFailID', 'TauPtFF3p', 'lephad', 'WFR')
    ##calcJetFakeFactorFinal('BvetoBDT3', 'CutBveto3pBDT3', 'CutBveto3pFailID', 'TauPtFF3p', 'ehad', 'WFR')
    ##calcJetFakeFactorFinal('BvetoBDT3', 'CutBveto3pBDT3', 'CutBveto3pFailID', 'TauPtFF3p', 'muhad', 'WFR')
    #
    ##calcJetFakeFactorFinal('Bveto', 'CutBveto3pPassID', 'CutBveto3pFailID', 'TauPtFF3p', 'lephad', 'WFR')
    #=======
    #### the right ones for d-d OS bveto Wjets ff
    ####
    #calcJetFakeFactorFinal('Bveto', 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR')
    #calcJetFakeFactorFinal('Bveto', 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'ehad', 'WFR')
    #calcJetFakeFactorFinal('Bveto', 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'muhad', 'WFR')
    #calcJetFakeFactorFinal('BvetoQcdSub', 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'lephad', 'WFR',True)
    #calcJetFakeFactorFinal('BvetoQcdSub', 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'ehad', 'WFR',True)
    #calcJetFakeFactorFinal('BvetoQcdSub', 'CutBveto1pOSPassID', 'CutBveto1pOSFailID', 'TauPtFFBveto1p', 'muhad', 'WFR',True)

    #calcJetFakeFactorFinal('Bveto', 'CutBveto3pOSPassID', 'CutBveto3pOSFailID', 'TauPtFFBveto3p', 'lephad', 'WFR')

    #calcJetFakeFactorFinal('Bveto', 'CutBveto1pPassID', 'CutBveto1pFailID', 'TauPtFF1p', 'ehad', 'WFR')
    #calcJetFakeFactorFinal('Bveto', 'CutBveto1pPassID', 'CutBveto1pFailID', 'TauPtFF1p', 'muhad', 'WFR')
    #>>>>>>> NominalAnalysis:share/scripts/calculateFakeFactor.py
    ##calcJetFakeFactorFinal('Bveto', 'CutBveto3pPassID', 'CutBveto3pFailID', 'TauPtFF3p', 'ehad', 'WFR')
    ##calcJetFakeFactorFinal('Bveto', 'CutBveto3pPassID', 'CutBveto3pFailID', 'TauPtFF3p', 'muhad', 'WFR')
    ##calcJetFakeFactorFinal('Btag', 'CutBtag1pPassID', 'CutBtag1pFailID', 'TauPtFFBtag1p', 'lephad', 'WFR')
    ##calcJetFakeFactorFinal('Btag', 'CutBtag3pPassID', 'CutBtag3pFailID', 'TauPtFFBtag3p', 'lephad', 'WFR')
    #
    #calcJetFakeFactorFinal('Btag', 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR')
    #calcJetFakeFactorFinal('Btag', 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR')
    ##calcJetFakeFactorFinal('Bveto', 'CutBveto1pPassID', 'CutBveto1pFailID', 'TauPtFF1p', 'muhad', 'SSWFR')
    ##calcJetFakeFactorFinal('Bveto', 'CutBveto3pPassID', 'CutBveto3pFailID', 'TauPtFF3p', 'lephad', 'SSWFR')
    ##calcJetFakeFactorFinal('Bveto', 'CutBveto3pPassID', 'CutBveto3pFailID', 'TauPtFF3p', 'ehad', 'SSWFR')
    ##calcJetFakeFactorFinal('Bveto', 'CutBveto3pPassID', 'CutBveto3pFailID', 'TauPtFF3p', 'muhad', 'SSWFR')
    #
    ####
    #### the right ones for d-d SS btag Top ff
    ####
    ##calcJetFakeFactorFinal('Btag', 'CutBtag1pPassID', 'CutBtag1pFailID', 'TauPtFFBtag1p', 'lephad', 'SSWFR')
    ##calcJetFakeFactorFinal('Btag', 'CutBtag3pPassID', 'CutBtag3pFailID', 'TauPtFFBtag3p', 'lephad', 'SSWFR')
    #<<<<<<< HEAD:share/scripts/calculateFakeFactorContID.py
    ##calcJet2DFakeFactorFinal('Bveto', 'CutBveto', 'TauPtvsBDTFF1p', 'lephad', 'WFR')
    ##calcJet2DFakeFactorFinal('Bveto', 'CutBveto', 'TauPtvsBDTFF3p', 'lephad', 'WFR')
    ##calcJet2DFakeFactorFinal('Btag', 'CutBtag', 'TauPtvsBDTFFBtag1p', 'lephad', 'SSWFR')
    ##calcJet2DFakeFactorFinal('Btag', 'CutBtag', 'TauPtvsBDTFFBtag3p', 'lephad', 'SSWFR')
    #=======
    #
    ##calcJetFakeFactorFinal('Btag', 'CutBtag1pPassID', 'CutBtag1pFailID', 'TauPtFFBtag1p', 'ehad', 'SSWFR')
    ##calcJetFakeFactorFinal('Btag', 'CutBtag3pPassID', 'CutBtag3pFailID', 'TauPtFFBtag3p', 'ehad', 'SSWFR')
    ##calcJetFakeFactorFinal('Btag', 'CutBtag1pPassID', 'CutBtag1pFailID', 'TauPtFFBtag1p', 'muhad', 'SSWFR')
    ##calcJetFakeFactorFinal('Btag', 'CutBtag3pPassID', 'CutBtag3pFailID', 'TauPtFFBtag3p', 'muhad', 'SSWFR')
    #
    #>>>>>>> NominalAnalysis:share/scripts/calculateFakeFactor.py
    ##calcMCFakeFactorFinal('Btag', 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauPtFFBtag1p', 'lephad', 'MCSSWFR')
    ##calcMCFakeFactorFinal('Btag', 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauPtFFBtag3p', 'lephad', 'MCSSWFR')
    ##calcMCFakeFactorFinal('Btag', 'CutBtag1pOSPassID', 'CutBtag1pOSFailID', 'TauPtFFBtag1p', 'lephad', 'MCOSWFR')
    ##calcMCFakeFactorFinal('Btag', 'CutBtag3pOSPassID', 'CutBtag3pOSFailID', 'TauPtFFBtag3p', 'lephad', 'MCOSWFR')
    ##
    ##calcMCFakeFactorFinal('Btag1p', 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauTracks', 'lephad', 'MCSSWFR')
    ##calcMCFakeFactorFinal('Btag3p', 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauTracks', 'lephad', 'MCSSWFR')
    ##calcMCFakeFactorFinal('Btag1p', 'CutBtag1pOSPassID', 'CutBtag1pOSFailID', 'TauTracks', 'lephad', 'MCOSWFR')
    ##calcMCFakeFactorFinal('Btag3p', 'CutBtag3pOSPassID', 'CutBtag3pOSFailID', 'TauTracks', 'lephad', 'MCOSWFR')
    ##calcMCFakeFactorFinal('Btag1p', 'CutBtag1pSSPassID', 'CutBtag1pSSFailID', 'TauMETDphi', 'lephad', 'MCSSWFR')
    ##calcMCFakeFactorFinal('Btag3p', 'CutBtag3pSSPassID', 'CutBtag3pSSFailID', 'TauMETDphi', 'lephad', 'MCSSWFR')
    ##calcMCFakeFactorFinal('Btag1p', 'CutBtag1pOSPassID', 'CutBtag1pOSFailID', 'TauMETDphi', 'lephad', 'MCOSWFR')
    ##calcMCFakeFactorFinal('Btag3p', 'CutBtag3pOSPassID', 'CutBtag3pOSFailID', 'TauMETDphi', 'lephad', 'MCOSWFR')
    #
    ##calcDphiCorrectionFinal('Bveto1p', 'CutBveto1pPassID', 'TauMETDphiCorrection', 'ehad', 'WFRdphi')
    ##calcDphiCorrectionFinal('Bveto1p', 'CutBveto1pPassID', 'TauMETDphiCorrection', 'muhad', 'WFRdphi')
    ##calcDphiCorrectionFinal('Bveto1p', 'CutBveto1pPassID', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    ##calcDphiCorrectionFinal('Bveto3p', 'CutBveto3pPassID', 'TauMETDphiCorrection', 'ehad', 'WFRdphi')
    ##calcDphiCorrectionFinal('Bveto3p', 'CutBveto3pPassID', 'TauMETDphiCorrection', 'muhad', 'WFRdphi')
    ##calcDphiCorrectionFinal('Bveto3p', 'CutBveto3pPassID', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    ##calcDphiCorrectionFinal('Bveto', '[CutBveto3pPassID+CutBveto1pPassID]', 'TauMETDphiCorrection', 'ehad', 'WFRdphi')
    ##calcDphiCorrectionFinal('Bveto', '[CutBveto3pPassID+CutBveto1pPassID]', 'TauMETDphiCorrection', 'muhad', 'WFRdphi')
    #<<<<<<< HEAD:share/scripts/calculateFakeFactorContID.py
    ##calcDphiCorrectionFinal('Bveto', '[CutBveto3pPassID+CutBveto1pPassID]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    #
    ################################
    ####
    #### BVETOFF dphi Corrections,
    #### some should not include qcd
    ####
    ################################
    #calcDphiCorrectionFinal('Bveto1pBDT1', '[CutBveto1pBDT1]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi',False)
    #calcDphiCorrectionFinal('Bveto1pBDT2', '[CutBveto1pBDT2]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    #calcDphiCorrectionFinal('Bveto1pBDT3', '[CutBveto1pBDT3]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi',False)
    #calcDphiCorrectionFinal('Bveto1pBDT4', 'CutBveto1pBDT4', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    #calcDphiCorrectionFinal('Bveto3pBDT123', '[CutBveto3pBDT1+CutBveto3pBDT2+CutBveto3pBDT3]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi',False)
    #################################
    ##calcDphiCorrectionFinal('Bveto3pBDT1', '[CutBveto3pBDT1]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    ##calcDphiCorrectionFinal('BvetoBDT2', '[CutBveto1pBDT2+CutBveto3pBDT2]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    ##calcDphiCorrectionFinal('Bveto3pBDT2', '[CutBveto3pBDT2]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    ##calcDphiCorrectionFinal('BvetoBDT3', '[CutBveto1pBDT3+CutBveto3pBDT3]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    ##calcDphiCorrectionFinal('Bveto3pBDT3', '[CutBveto3pBDT3]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    ##calcDphiCorrectionFinal('BvetoNOqcd3pBDT1', '[CutBveto3pBDT1]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi',False)
    ##calcDphiCorrectionFinal('BvetoNOqcd3pBDT2', '[CutBveto3pBDT2]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi',False)
    ##calcDphiCorrectionFinal('BvetoNOqcd3pBDT3', '[CutBveto3pBDT3]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi',False)
    ##calcDphiCorrectionFinal('Bveto1pBDT12', '[CutBveto1pBDT1+CutBveto1pBDT2]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    ##calcDphiCorrectionFinal('Bveto1pBDT34', '[CutBveto1pBDT3+CutBveto1pBDT4]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    #
    #
    #=======
    #calcDphiCorrectionFinal('Bveto', '[CutBveto3pPassID+CutBveto1pPassID]', 'TauMETDphiCorrection', 'lephad', 'WFRdphi')
    #
    #calcLFRDphiCorrectionFinal('Bveto', 'CutSLBveto', 'LepMETDphiBvetoCorrectionELE', 'ehad', 'LFRdphi')
    #calcLFRDphiCorrectionFinal('Bveto', 'CutSLBveto', 'LepMETDphiBvetoCorrectionMUON', 'muhad', 'LFRdphi')
    #calcLFRDphiCorrectionFinal('Btag', 'CutSLBtag', 'LepMETDphiBtagCorrectionELE', 'ehad', 'LFRdphi')
    #calcLFRDphiCorrectionFinal('Btag', 'CutSLBtag', 'LepMETDphiBtagCorrectionMUON', 'muhad', 'LFRdphi')
    #>>>>>>> NominalAnalysis:share/scripts/calculateFakeFactor.py
    #
    ##calcJetFakeFactorFinal('Bveto', 'CutBvetoPassID', 'CutBvetoFailID', 'TauPtFF1p', '[ehad+muhad]', 'QCDCR')
    ##calcJetFakeFactorFinal('Bveto', 'CutBvetoPassID', 'CutBvetoFailID', 'TauPtFF3p', '[ehad+muhad]', 'QCDCR')
    ##calcJetFakeFactorFinal('Btag', 'CutBtagPassID', 'CutBtagFailID', 'TauPtFF1p', '[ehad+muhad]', 'QCDCR')
    ##calcJetFakeFactorFinal('Btag', 'CutBtagPassID', 'CutBtagFailID', 'TauPtFF3p', '[ehad+muhad]', 'QCDCR')
    #
    ##calcFakeFactorFinal(['3Prong'], 'tauPt', ['BOOSTMVA','VBFMVA'], ['SLT','TLT'],['SR'])
    ##calcFakeFactorFinal(['1Prong','3Prong'], 'tauPt', ['BOOSTCB','VBFCB'], ['SLT','TLT'],['SR'])
    ##calcFakeFactorFinal(['1Prong','3Prong'], 'tauPt', ['BOOSTMVA','VBFMVA'], ['SLT'],['SR'])



    #purity calculation

    # background_list = ['Top','Z','W']
    # category_list = ['VBFCB','BOOSTCB']
    # prong_list = ['1Prong','3Prong']
    # trigger_list = ['SLT']


    # for background in background_list:
    #     for category in category_list:
    #         for prong in prong_list:
    #             for trigger in trigger_list:
    #                 calcPurity(background,category,prong,trigger)
