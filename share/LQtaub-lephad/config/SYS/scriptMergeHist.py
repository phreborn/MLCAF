if __name__ == '__main__':

  import os
  import argparse

  parser = argparse.ArgumentParser(description='Merge histogram for statistical analysis.')
  parser.add_argument('version', metavar='VERSION', type=str,
            default="st300",
            help='version to be used')
  parser.add_argument('coupling', metavar='COUPLING', type=str,
            default="1_0",
            help='coupling to be used')
  args = parser.parse_args()


  "Merge the histograms"
  campaigns = ['c16ade']
  channels = ['ehad', 'muhad']
  #channels = ['lephad']
  NCORES = 8
  variable = 'St'
  #variable = 'BjetPt'
  regions = []
  regions.extend(['OSBtagSRLowBJetPt', 'OSBtagSRHighBJetPt'])
  #regions.extend(['TFROSBtagLowBJetPt'])
  #regions.extend(['VROSBtag'])
  #regions.extend(['TCROSBtag'])
  #regions.extend(['TFROSBtag'])
  #regions.extend(['TVROSBtag'])
  #regions.extend(['LFROSBtag'])
  #regions.extend(['WFROSBtag'])
  #regions.extend(['OSBtagSR'])

  root_file_name = '13TeV_OneLepton_CUT_'
  for campaign in campaigns:
    for channel in channels:
      for region in regions:
        merge_to = root_file_name
        if 'Btag' in region:
          merge_to += '1tag0jet_0ptv_'+region+'_'
        else:
          merge_to += '0tag0jet_0ptv_'+region+'_'
        if 'ehad' in channel:
          merge_to += 'ElHad_'
        elif 'muhad' in channel:
          merge_to += 'MuHad_' 
        elif 'lephad' in channel:
          merge_to += 'LepHad_'
        merge_to += variable + '.root'
        cmd = 'hadd -f -j {0} dumpHist_{5}_l{6}/{1} dumpHist_{5}_l{6}/*/{2}/{3}/{2}_{4}_{3}.root'.format(NCORES, merge_to, campaign, channel, region, args.version, args.coupling) 
        os.system(cmd)

