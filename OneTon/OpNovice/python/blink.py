#!/usr/bin/env python


import ROOT
from ROOT import gROOT, TFile, gDirectory
import sys
from Capturing import Capturing


        
rfn = '../output/runX.root'
f = TFile.Open(rfn)
htree = f.Get('Hits')
s = 'fProc'
i = 0
with Capturing() as output:
    print 'hey whats happening?'

print 'output',output

g = open('junk','w')

for hev in htree:
    #print 's,hev.GetBranch(s)',s,hev.GetBranch(s)
    #print 's,hev.FindBranch(s)',s,hev.FindBranch(s)
    #print 's,hev.FindLeaf(s)',s,hev.FindLeaf(s)
    #print 's,hev.FindLeaf(s).PrintValue()',s,hev.FindLeaf(s).PrintValue()
    hev.FindBranch(s).PrintValue(0)
    with Capturing() as output:
        hev.FindBranch(s).PrintValue(0)
    print 'output', output
    i += 1
    if i>2: sys.exit('........')
