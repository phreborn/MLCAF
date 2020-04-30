import os

if __name__ == '__main__':
  """ Merge the Histograms """
  
  campaigns=['c16ade']
  NCORES=10

  regions=[]
  regions.extend(['sr1pBtag','sr3pBtag'])
  regions.extend(['tcr1pBtag','tcr3pBtag'])
  regions.extend(['vr1pBtag','vr3pBtag'])
  """ Merge the Histograms """
  for campaign in campaigns:
    for region in regions:
      cmd='hadd -f -j {2} dumpHist/{0}_{1}.root dumpHist/*/{0}/*/{0}*{1}*.root'.format(campaign, region, NCORES)    
      os.system(cmd)
