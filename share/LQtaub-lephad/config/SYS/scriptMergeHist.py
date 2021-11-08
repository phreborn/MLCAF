if __name__ == '__main__':

  import os

  "Merge the histograms"
  campaigns = ['c16ade']
  channels = ['ehad', 'muhad']
  NCORES = 8
  variable = 'MTTOT'
  regions = []
  regions.extend(['OSBvetoSR', 'OSBtagSR'])

  root_file_name = '13TeV_OneLepton_CUT_'
  for campaign in campaigns:
    for channel in channels:
      for region in regions:
        merge_to = root_file_name
        if 'Btag' in region:
          merge_to += '1tag0jet_0ptv_'
        else:
          merge_to += '0tag0jet_0ptv_'
        if 'ehad' in channel:
          merge_to += 'ElHad_'
        else:
          merge_to += 'MuHad_' 
        merge_to += variable + '.root'
        cmd = 'hadd -f -j {0} dumpHist/{1} dumpHist/*/{2}/{3}/{2}_{4}_{3}.root'.format(NCORES, merge_to, campaign, channel, region) 
        os.system(cmd)

