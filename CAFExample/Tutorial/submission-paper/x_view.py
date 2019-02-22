#!/usr/bin/env python

import numpy
import ROOT

data = numpy.loadtxt("scatter_data.txt")

histo = ROOT.TH1F("", "", 20, -10, 10)
histo.SetStats(False)
for x, y in data:
    histo.Fill(x)

canvas = ROOT.TCanvas()
histo.Draw()
canvas.SaveAs("x.pdf")
