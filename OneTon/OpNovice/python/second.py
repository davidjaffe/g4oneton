#!/user/bin/env python
'''
20150623 process hists produced by oneton.py
'''
import ROOT
import math
import roottools # copied from DybPython 20150623


class second():

    def __init__(self):
        return

    def happy(self,x):
        return min(9999.9,max(-999.9,x))

    def reader(self):
    ##### main stuff here
        rflist = ['../hists/sidebyside_config7_muons_100MeV-10GeV_20150623_142404.root']

        debug = len(rflist)<2

        # initializations
        #fitter = gfit.gfit()
        #drawer = draw.draw()
        #calibrater = calibrate.calibrate()

        results = {}
        for rfn in rflist:
            print '\n\n -------------------- Open',rfn
            file0 = ROOT.TFile.Open(rfn)

            hout = {}
            # get list of all objects
            objlist = []
            for dirpath,subdirs,objs in roottools.walk(file0):
                for o in objs:
                    objlist.append(o)

        hdict = {}
        for obj in objlist:
            name = obj.GetName()
            title  = obj.GetTitle()
            hdict[name] = obj
            #print name,title
        return
if __name__ == '__main__':
    s = second()
    s.reader()
#    args = sys.argv
