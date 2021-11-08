#!/user/bin/env python2

# Script to link CAF to samples stored on HDBS grid space

def getData():
    for year in ['data15','data16','data17', 'data18']:
        print('\33[96mLinking {0} samples\033[0m'.format(year))
        
        # loop through the DIDS and get replica directory on EOS
        for DID in rucioClient.list_dids(scope=scope, filters={'name':scope+'.BSMDITAU.'+year+'*'+release+'*_BS'}, type='container'):
	    os.system("mkdir -p {0}{1}/data/{2}/{3}".format(path, release, year, DID))
	    replicas = list(rucioClient.list_replicas([{'scope':scope, 'name':DID}]))
	    for f in replicas:
                if f == "":
                    continue
                if f['rses'].get('CERN-PROD_PHYS-HDBS') is None:
                    print "\033[31mERROR:", DID, ':', f['name'], "is missing\033[0m"
                else:
                    os.symlink('/' + f['rses'].get(rse)[0].split("//")[-1],path+release+'/data/'+year+'/'+DID+"/"+f['rses'].get(rse)[0].split("//")[-1].split("/")[-1])


# now do MC nom and sys
def getMC():
    for type in ['nom', 'sys']:
        if type == 'sys':
            ver = 's'
        else:
            ver = 'v'
   
        for i,campaign in enumerate(['9364', '10201', '10724']):
            print('\33[96mLinking {0} {1} samples\033[0m'.format(mc_campaigns[i], type))
            
            for DID in rucioClient.list_dids(scope=scope, filters={'name':scope+'.BSMDITAU*'+campaign+'*'+release+ver+'*_BS'}, type='container'):	
                os.system("mkdir -p {0}{1}/mc/{2}/{3}/{4}".format(path, release, mc_campaigns[i],type, DID))
	        replicas = list(rucioClient.list_replicas([{'scope':scope, 'name':DID}]))
                for f in replicas:
                    if f == "":
                        continue
                    if f['rses'].get('CERN-PROD_PHYS-HDBS') is None:
                        print "\033[31mERROR:", DID, ':', f['name'], "is missing\033[0m"
                    else:
                        os.symlink('/' + f['rses'].get(rse)[0].split("//")[-1],path+release+'/mc/'+mc_campaigns[i]+'/'+type+'/'+DID+"/"+f['rses'].get(rse)[0].split("//")[-1].split("/")[-1])


	
if __name__ =="__main__":
    
    # argument is ntuple release date
    from optparse import OptionParser
    parser=OptionParser(usage="usage: python %prog [options] REGION")
    parser.add_option("-d","--debug",  action="store_true"  ,dest="debug"  ,default=False     ,help="show DEBUG output")
    (options,args)=parser.parse_args()


    import sys

  
    if len(args)!=1:
        print 'You must submit an argument RELEASE: E.g., 201215'
        sys.exit()
    try:
        import rucio.client
    except:
        print( "\033[91mCannot import rucio.client, please use lsetup rucio\033[0m")
        sys.exit()

    import os


    scope = 'group.phys-hdbs'
    release = args[0]
    rse = 'CERN-PROD_PHYS-HDBS'
    rucioClient = rucio.client.Client()
    mc_campaigns = ['mc16a','mc16d', 'mc16e']
    path = "LQtaub-lephad/config/common/samples/inputFileLists/"
    os.system("rm -rf {0}{1}".format(path,release))

    
    # collect data samples
    getData()
    # collect MC samples
    getMC()
