import os

if __name__ == '__main__':
  """ Merge the Histograms """
  
  campaigns=['c16ade']
  NCORES=10

  regions=[]
  regions.extend(['OSBvetoSR1p','OSBvetoSR3p','OSBtagSR1p','OSBtagSR3p'])
  """ Merge the Histograms """
  for campaign in campaigns:
    for region in regions:
      cmd='hadd -f -j {2} dumpHist/{0}_{1}.root dumpHist/*/{0}/*/{0}*{1}*.root'.format(campaign, region, NCORES)    
      os.system(cmd)
