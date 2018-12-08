#!/usr/bin/env python

import numpy
import ROOT

data = numpy.loadtxt("scatter_data.txt")

histo = ROOT.TH2F("", "", 20, -10, 10, 20, -10, 10)
histo.SetStats(False)
for x, y in data:
    histo.Fill(x, y)

canvas = ROOT.TCanvas()
histo.Draw("colz")
canvas.SaveAs("top.pdf")
