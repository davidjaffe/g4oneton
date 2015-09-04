#!/usr/bin/env python
'''
analysis of oneton simulation ttrees 
'''

import ROOT
from ROOT import gROOT, TFile, gDirectory
import sys
import math


class oneton():

    def __init__(self,input_rfn='../output/runX.root',EventsToProcess=-1):

        self.debug_dumping = True #False
        
        self.rfn = input_rfn #'../output/runX.root'
        self.hfn = input_rfn.replace('output','hists')
        if self.hfn==self.rfn:
            words = 'oneton__init__ ERROR Input and output file names are IDENTICAL: ' + self.rfn
            sys.exit(words)

        self.maxEvents = EventsToProcess

        # use for unpacking 
        #  i = integer, d = double
        self.hits_vlist = ['fTrackID','fParentID', 'fPmtNb', 'fEop', 'fTop',   'fPosX','fPosY','fPosZ',  'fiProc', 'fWt', 'fPSType',\
                      'fDirChanges','fCosIF','fbProc', 'fTrkLen', 'fTrkOriginX','fTrkOriginY','fTrkOriginZ','fEvtNb']
        self.hits_vtype= ['i','i','i','d','d','d','d','d','i','d','i','d','d','i','d','d','d','d','i']
        self.tracks_vlist = [ 'fDirChanges', 'fCosIniFin', 'fBoundaryProc','fLiqPathLen', 'fLiqELoss', 'fFateOrigin','fEvtNb',\
                              'fStartVtxX','fStartVtxY','fStartVtxZ', 'fStartPX','fStartPY','fStartPZ',\
                              'fFinalVtxX','fFinalVtxY','fFinalVtxZ', 'fFinalPX','fFinalPY','fFinalPZ',\
                              'fPDG' ]
        self.tracks_vtype = ['i','d','i','d','d','i','i','d','d','d','d','d','d','d','d','d','d','d','d','i']

        # for grouping hodo hits
        self.deltaT_hodo = 1.0 # ns
        self.hodo_numbers = [0,1, 2,3, 10]
        self.hodo_numbers_above = [0,1,2,3]

        self.pmt_numbers = [0,1,2,3,4, 100,101,102,103,104]

        self.det_numbers = {}
        self.det_numbers['PMT'] = self.pmt_numbers
        self.det_numbers['HODO'] = self.hodo_numbers
        
        # classifying hits (defined in OnetonTrackerHit.hh)
        self.hitTypeMap = {-1 : 'HODO', 1 : 'Scint', 2 : 'Cerenkov', 3 : 'Other'}
        self.detTypeMap = {'HODO': 'HODO', 'Scint':'PMT', 'Cerenkov':'PMT', 'Other':'PMT', 'PMT':'PMT'}
        self.hitTypes = []
        for i in self.hitTypeMap: self.hitTypes.append( self.hitTypeMap[i] )
        
        # cuts
        self.minMuonMom = 1000. # MeV/c
        
        return

    def firstTry(self):

        # book hists
        hdict = self.book()
        
        # open the file
        myfile = TFile( self.rfn )
        print "file",self.rfn,"is open"

        # get the trees from the input file
        _tTree = myfile.Get('dumTracks')
        _hTree = myfile.Get('dumHits')
        print 'Pointers to _hTree',_hTree,'_tTree',_tTree,
        if self.maxEvents>0:
            print 'Maximum # of events to process',self.maxEvents
        else:
            print ''

        # for testing.........
        testHits = testTree = False
        if testHits or testTree : self.testingMode(_hTree,_tTree,testHits,testTree)

        # processing of events
        debug = False
        nH = _hTree.GetEntriesFast()
        jH = 0
        nT = _tTree.GetEntriesFast()
        jT = 0
        keepGoing = True
        evtN = 0
        while keepGoing:
            jH,hEvent = self.getNextEvent(jH,nH,_hTree,evtN)
            lH = len(hEvent)
            jT,tEvent = self.getNextEvent(jT,nT,_tTree,evtN)
            lT = len(tEvent)
            if (evtN<10000 and evtN%1000==0) or (evtN%10000==0): print 'Event#',evtN,'#hits',lH,'#tracks',lT
            if lH>0 or lT>0:
                if (debug): print 'evtN',evtN,
                hodos, lHodo = {}, {}
                pmts = {}
                for i in self.hodo_numbers: lHodo[i] = 0

                if lH>0:
                    if (debug): print 'hEvtNb',hEvent[0]['fEvtNb'],'#hits',lH,
                    for hitType in self.hitTypes:
                        if hitType=='HODO':
                            pmts[hitType] = hodos = self.makeHodoHits(hEvent,hitType=hitType)
                        else:
                            pmts[hitType] = self.makeHodoHits(hEvent,hitType=hitType)
                    for i in self.hodo_numbers:
                        lHodo[i] = i in hodos

                    for i in self.hodo_numbers: 
                        Th = 0
                        for evt in hEvent:
                            if i==evt['fPmtNb']: Th+=1
                        hs = 'Hph'
                        hdict[hs].Fill(float(i),float(Th))
                        Rh = 0
                        if i in hodos: Rh = len(hodos[i])
                        hs = 'RHph'
                        hdict[hs].Fill(float(i),float(Rh))
                        hdict['RvTh_'+str(i)].Fill(float(Th),float(Rh))
                if self.debug_dumping:
                    print '\n'
                    self.dump(hEvent)
                    for hitType in self.hitTypes:
                        self.dumpHodos(pmts[hitType],hitType=hitType)
                    self.dump(tEvent)
                if debug : 
                    for q in hodos:
                        print 'hodo#',q,'hits',len(hodos[q]),
                        for x in hodos[q]: print 'T,E',x[0],x[1],
                if debug: print ''
                for iEvent in range(lT):
                    if (debug) : print 'tEvtNb',tEvent[iEvent]['fEvtNb'],'#tracks',lT
                    xgen,ygen = tEvent[iEvent]['fStartVtxX'],tEvent[iEvent]['fStartVtxY']
                    xfin,yfin = tEvent[iEvent]['fFinalVtxX'],tEvent[iEvent]['fFinalVtxY']
                    pdg = tEvent[iEvent]['fPDG']
                    muon = abs(pdg)==13
                    Ptot = self.getMag(tEvent[iEvent],'fStartP')
                    muonGtCut = muon and Ptot>self.minMuonMom
                    theta = self.getTheta(tEvent[iEvent],'fStartP')
                    cost = self.getCosTheta(tEvent[iEvent],'fStartP')
                    phi   = self.getPhi(tEvent[iEvent],'fStartP')
                    Eliq = tEvent[iEvent]['fLiqELoss']
                    Lpath = tEvent[iEvent]['fLiqPathLen']
                    #print 'xgen,ygen,xfin,yfin,pdg,theta,cost,phi,Eliq,Lpath',xgen,ygen,xfin,yfin,pdg,theta,cost,phi,Eliq,Lpath

                    hdict['Eliq_gen'].Fill(Eliq)
                    hdict['Lpath_gen'].Fill(Lpath)
                    hdict['pdg_gen'].Fill(pdg)
                    hdict['P_gen'].Fill(Ptot)
                    stgVar =     [ ['pdg_acc',   [pdg]],\
                                   ['P_acc',     [Ptot]],\
                                   ['Eliq_acc',  [Eliq]],\
                                   ['Lpath_acc', [Lpath]],\
                                   ]
                    if muon:
                        hdict['yvx_gen'].Fill(xgen,ygen)
                        hdict['yvx_final_gen'].Fill(xfin,yfin)
                        hdict['tvx_gen'].Fill(xgen,theta)
                        hdict['tvy_gen'].Fill(ygen,theta)
                        hdict['fvx_gen'].Fill(xgen,phi)
                        hdict['fvy_gen'].Fill(ygen,phi)
                        hdict['theta_gen'].Fill(theta)
                        hdict['ctvf_gen'].Fill(cost,phi)
                        muonsV  = [ ['yvx_acc',   [xgen,  ygen] ],\
                                    ['theta_acc', [theta]],\
                                    ['yvx_final_acc',[xfin,yfin]],\
                                    ['ctvf_acc',  [cost,  phi]]\
                                    ]
                        if muonGtCut:
                            muonsV.append( ['yvx_Pcut_acc', [xgen,ygen]] )
                            muonsV.append( ['yvx_final_Pcut_acc', [xfin,yfin]])
                            hdict['yvx_Pcut_gen'].Fill(xgen,ygen)
                            hdict['yvx_final_Pcut_gen'].Fill(xfin,yfin)
                        stgVar.extend( muonsV )

                    # fill acceptance histograms
                    for sV in stgVar:
                        s = sV[0] # string
                        V = sV[1] # variable(s)
                        for key in hdict:
                            if s in key:
                                hoNums = self.keyParse(s,key) # list of hodos to check for hits
                                good = True
                                for h in hoNums: good = good and lHodo[h]
                                if good:
                                    if len(V)==1: hdict[key].Fill(V[0])
                                    if len(V)==2: hdict[key].Fill(V[0],V[1])

                            
                evtN += 1
                keepGoing = self.maxEvents<0 or evtN<self.maxEvents
            else:
                keepGoing = False


        hf = ROOT.TFile.Open(self.hfn,'recreate')
        hf.cd()
        for h in hdict: hdict[h].Write()
        hf.Close()
        print 'write hists to',self.hfn
        return
    def book(self):
        '''
        book a bunch of hists. hists are stored in output dictionary
        '''
        hdict = {}
        # hodoscope hit distributions
        nx, xmi, xma = 11,-0.5,10.5
        ny, ymi, yma = 51,-0.5,50.5
        hdict['Hph'] = ROOT.TH2F('Hph','Total hits per hodo',nx,xmi,xma,ny,ymi,yma)
        hdict['RHph']= ROOT.TH2F('RHph','Resolved hits per hodo',nx,xmi,xma,ny,ymi,yma)
        nx, xmi, xma = 51,-0.5,50.5
        ny, ymi, yma = 51,-0.5,50.5
        for h in self.hodo_numbers:
            sh = str(h)
            hdict['RvTh_'+sh] = ROOT.TH2F('RvTh_'+sh,'Resolved vs total hits hodo'+sh,nx,xmi,xma,ny,ymi,yma)
            
        # acceptance of hodoscopes
        nx, xmi, xma = 100,-20.,620.
        ny, ymi, yma = 100,-200.,200.
        pstr = str(self.minMuonMom) + ' MeV/c'
        for bt,bs in zip(['generated muon Y vs X','generated muon Y vs X P>'+pstr], ['yvx_acc', 'yvx_Pcut_acc']):
            gs = bs.replace('acc','gen')
            hdict[gs] = ROOT.TH2F(gs,bt + ' all',nx,xmi,xma, ny,ymi,yma)
            for h1 in [0,2]:
                s1 = str(h1)
                t1 = ' acc by hodo' + str(h1)
                key = bs+s1
                title = bt+t1
                hdict[key] = ROOT.TH2F(key,title,nx,xmi,xma, ny,ymi,yma)
                r2 = self.hAbove(h1)
                for h2 in r2:
                    s2 = '_'+str(h2)
                    t2 = s2
                    key = bs+s1+s2
                    title = bt+t1+t2
                    hdict[key] = ROOT.TH2F(key,title,nx,xmi,xma, ny,ymi,yma)
                    r3 = self.uniqList(h2,r2)
                    r3.append(10)
                    for h3 in r3:
                        if h3>h1 and h3>h2:
                            s3 = '_'+str(h3)
                            t3 = s3
                            key = bs+s1+s2+s3
                            title = bt+t1+t2+t3
                            hdict[key] = ROOT.TH2F(key,title,nx,xmi,xma, ny,ymi,yma)
                            #print 'key',key,'title',title
            hdict[bs+'0_2_1_3'] = ROOT.TH2F(bs+'0_2_1_3',bt+'0_2_1_3',nx,xmi,xma, ny,ymi,yma)

        hdict['tvx_gen'] = ROOT.TH2F('tvx_gen','Theta vs x generated muon',100,-20.,620., 100,1.8,3.2)
        hdict['tvy_gen'] = ROOT.TH2F('tvy_gen','Theta vs y generated muon',100,-200.,200., 100,1.8,3.2)
        hdict['fvx_gen'] = ROOT.TH2F('fvx_gen','Phi vs x generated muon',100,-20.,620., 100,-math.pi,math.pi)
        hdict['fvy_gen'] = ROOT.TH2F('fvy_gen','Phi vs y generated muon',100,-200.,200., 100,-math.pi,math.pi)
        
        nxCT, xmiCT, xmaCT, nyF, ymiF, ymaF = 100,-1.,-0.8, 100,-math.pi,math.pi

        r = 8.*12.*25.4/2. # 8' x 12" x 25.4mm/in /2 = half-width of dark box
        for bt,bs in zip(['generated muon final Y v X, accepted by hodo','generated muon final Y v X, Pmu>'+pstr+' accepted by hodo','generated muon Phi v cos(theta), accepted by hodo'], ['yvx_final_acc','yvx_final_Pcut_acc','ctvf_acc']):
            gs = bs.replace('acc','gen')
            nx, xmi, xma, ny, ymi, yma  = 100,-r,r, 100,-r,r
            if 'ctvf' in bs: nx, xmi, xma, ny, ymi, yma = nxCT, xmiCT, xmaCT, nyF, ymiF, ymaF
            hdict[gs] = ROOT.TH2F(gs,bt.replace('accepted by hodo','all'),nx,xmi,xma,ny,ymi,yma)
            for h1 in [0,2]:
                s1 = str(h1)
                #hdict[cs+s1] = ROOT.TH2F(cs+s1,ct+s1,nxCT, xmiCT, xmaCT, nyF, ymiF, ymaF )
                for h2 in self.hAbove(h1):
                    s2 = '_'+str(h2)
                    hdict[bs+s1+s2] = ROOT.TH2F(bs+s1+s2,bt+s1+s2,nx,xmi,xma,ny,ymi,yma)
                    if (str(h2) not in '0_2') and (bs+'0_2'+s2 not in hdict):
                        hdict[bs+'0_2'+s2] = ROOT.TH2F(bs+'0_2'+s2,bt+'0_2'+s2,nx,xmi,xma,ny,ymi,yma)
            hdict[bs+'0_2_1_3'] = ROOT.TH2F(bs+'0_2_1_3',bt+'0_2_1_3',nx,xmi,xma, ny,ymi,yma)


                
        nx, xmi, xma = 100,1.8,3.2
        hdict['theta_gen'] = ROOT.TH1F('theta_gen','theta muon generation',nx,xmi,xma)
        bt = 'theta accepted by hodo'
        bs = 'theta_acc'
        nxp, xmip, xmap = 31,-15.5,15.5
        hdict['pdg_gen']   = ROOT.TH1F('pdg_gen','PDG code of generated particles',nxp,xmip,xmap)
        pt = 'PDG code accepted by hodo'
        ps = 'pdg_acc'
        nxE, xmiE, xmaE = 100, 0., 500.
        hdict['Eliq_gen'] = ROOT.TH1F('Eliq_gen','Energy deposited(MeV) in liquid generation',nxE,xmiE,xmaE)
        et = 'Energy deposited(MeV) in liquid, accepted by hodo'
        es = 'Eliq_acc'
        nxL, xmiL, xmaL = 100, 0., 2000.
        hdict['Lpath_gen'] = ROOT.TH1F('Lpath_gen','Path length(mm) in liquid generation',nxL,xmiL,xmaL)
        lt = 'Path length(mm) in liquid, accepted by hodo'
        ls = 'Lpath_acc'
        nxQ, xmiQ, xmaQ = 100, 0., 10000.
        hdict['P_gen'] = ROOT.TH1F('P_gen','Momentum(MeV) at generation',nxQ,xmiQ,xmaQ)
        qt = 'Momentum(MeV) at generation, accepted by hodo'
        qs = 'P_acc'
        for h1 in [0,2]:
            s1 = str(h1)
            t1 = ' acc by hodo'+s1
            key = bs+s1
            title = bt+t1
            hdict[key] = ROOT.TH1F(key,title,nx,xmi,xma)
            hdict[ps+s1] = ROOT.TH1F(ps+s1,pt+t1,nxp,xmip,xmap)
            hdict[qs+s1] = ROOT.TH1F(qs+s1,qt+t1,nxQ,xmiQ,xmaQ)
            for h2 in self.hAbove(h1):
                s2 = '_'+str(h2)
                t2 = s2
                key = bs+s1+s2
                title = bt+t1+t2
                hdict[key] = ROOT.TH1F(key,title,nx,xmi,xma)
                hdict[ps+s1+s2] = ROOT.TH1F(ps+s1+s2,pt+t1+t2,nxp,xmip,xmap)
                hdict[qs+s1+s2] = ROOT.TH1F(qs+s1+s2,qt+t1+t2,nxQ,xmiQ,xmaQ)
                hdict[es+s1+s2] = ROOT.TH1F(es+s1+s2,et+t1+t2,nxE,xmiE,xmaE)
                hdict[ls+s1+s2] = ROOT.TH1F(ls+s1+s2,lt+t1+t2,nxL,xmiL,xmaL)


        return hdict
    def keyParse(self, s, key):
        '''
        if string s is in key, then determine list of hodoscope numbers separated by underscores
        after removing s from key.
        return empty list if s not in key
        '''
        L = []
        if s in key:
            b = key.replace(s,'')
            for a in b.split('_'): L.append(int(a))
        return L
    def hAbove(self,h):
        return self.uniqList(h,self.hodo_numbers_above)
    def uniqList(self,h,oldlist):
        '''
        make new list from oldlist, omitting entry h if it is in oldlist.
        do not change content of oldlist.
        '''
        newlist = list( oldlist )
        if h in newlist: newlist.remove(h)
        return newlist
    def useHit(self, hit, hitType='HODO'):
        '''
        return True if hit is the desired type
        types = HODO, PMT, and PMT subclasses Cerenkov, Scint, Other
        '''
        ihit = hit['fiProc']
        if ihit in self.hitTypeMap:
            t = self.hitTypeMap[ihit]
            if t==hitType: return True
            d = self.detTypeMap[t]
            if d==hitType: return True
        return False
    def makeHodoHits(self, hEvent, hitType='HODO'):
        '''
        return a dictionary of hodoscope hits with key=hodo or PMT number, value = list of list[time,energy]
        group together hits in hodoscopes or PMTs in an event
        for PMTs, sort by type of incident light
        hEvent is a list of dictonaries
        '''
        debug = False
        HH = {}
        for hit in hEvent:
            if self.useHit(hit, hitType):
                hodoNumber = hit['fPmtNb']
                if hodoNumber in HH:
                    HH[hodoNumber].append(hit)
                else:
                    HH[hodoNumber] = [hit]
        hodos = {}
        if self.detTypeMap[hitType]=='PMT' : var = 'fWt'  # sum weights (weight is quantum efficiency given wavelength)
        if self.detTypeMap[hitType]=='HODO': var = 'fEop' # sum energy deposits
        for hodoNumber in HH:
            if debug:
                print '\nhodoNumber',hodoNumber,'pre-sort'
                for b in HH[hodoNumber]:
                    for s in ['fPmtNb','fTop',var]: print s,b[s],
                    print ''

            HH[hodoNumber].sort(key=lambda x: x['fTop'] )  # sort hits by time
            hodos[hodoNumber] = []
            for dep in HH[hodoNumber]:
                if len(hodos[hodoNumber])==0:
                    hodos[hodoNumber].append( [dep['fTop'],dep[var]] )
                else:
                    lastHit = hodos[hodoNumber][-1]
                    if lastHit[0]-dep['fTop']<self.deltaT_hodo:
                        lastHit[1] += dep[var] # add energy or weight to previous deposit
                    else:
                        hodos[hodoNumber].append( [dep['fTop'],dep[var]] )
            if debug:
                print '\nhodoNumber',hodoNumber,'post sort'
                for b in HH[hodoNumber]:
                    for s in ['fPmtNb','fTop',var]: print s,b[s],
                    print ''
                print 'hodos[hodoNumber]',hodos[hodoNumber]
        return hodos
    def dumpHodos(self, hodos, hitType):
        '''
        dump hodo or PMT hits
        '''
        d = self.detTypeMap[hitType]
        eTitle = self.Etitle(hitType)
        if d=='PMT': eTitle = 'sumWt' 
        d_numbers = self.det_numbers[d]
        s = ''
        gotOne = False
        for ih in d_numbers:
            if ih in hodos:
                s += '#'+str(ih) + ' '
                for hit in hodos[ih]:
                    if d=='HODO': s += '({:>4d},{:4.1f}) '.format(int(self.Efunction(hit[1],hitType)+0.5),hit[0])
                    if d=='PMT' : s += '({:4.2f},{:4.1f}) '.format(hit[1],hit[0])
                gotOne = True
            else:
                s += '#'+str(ih) + ' no hit '
        if len(s)>0 and gotOne:
            s = d+'Num '+ hitType+'('+eTitle+', T ns) ' + s
        else:
            s = d + ' no ' + hitType + ' hits'
        print s

            
        return
    def getMag(self,evt,var):
        m = 0.
        for v in ['X','Y','Z']:
            vv = var+v
            m += evt[vv]*evt[vv]
        return math.sqrt(m)
    def getCosTheta(self,evt,var):
        m = self.getMag(evt,var)
        if m<=0:
            print 'getCosTheta: ERROR',var,'has magnitude',m,'dump to follow'
            print 'getCosTheta: evt',evt
            self.dump(evt)
            sys.exit('Figure this out first')
        
        return evt[var+'Z']/m
    def getTheta(self,evt,var):
        return math.acos(self.getCosTheta(evt,var))
    def getPhi(self,evt,var):
        return math.atan2(evt[var+'Y'],evt[var+'X'])
    def getNextEvent(self, j,n,tree,evtN):
        '''
        get the next event (a list) for event# evtN from the input tree given the current entry number j and
        the total number of entries n
        Return a zero length list if there are no more events
        '''
        Event = []
        while j<n:
            if tree.LoadTree(j)<0 : return j,Event
            nb = tree.GetEntry(j)
            EvtNb = self.getEvtNb(tree)
            if EvtNb==evtN:
                Event.append(self.unpackBag(tree))
            else:
                return j,Event
            j += 1
        return j,Event
    def getEvtNb(self, tree):
        return int(tree.FindLeaf('fEvtNb').GetValue(0))
    def unpackBag(self, ev):
        #print 'unpackBag:ev,ev.GetName()',ev,ev.GetName()
        if ev.GetName()=='dumHits': return self.unpackHit(ev)
        if ev.GetName()=='dumTracks': return self.unpackTrack(ev)
        return None
    def unpackTrack(self,tev):
        '''
        unpack entry tev in TTree dumTracks based on known variable types
        '''
        Track = self.unpack(tev,self.tracks_vlist,self.tracks_vtype)
        return Track
    def unpackHit(self,hev):
        '''
        unpack entry hev in TTree dumHits based on known variable types
        '''
        Hit = self.unpack(hev,self.hits_vlist,self.hits_vtype)
        return Hit
    def unpack(self,ev,vlist,vtype):
        '''
        return dictionary of variable_name,variable_value pairs
        '''
        D = {}
        for v,t in zip(vlist,vtype):
            B = ev.FindLeaf(v)
            #print 'unpack: v,ev.FindLeaf(v)',v,B
            if t=='i':
                D[v] = int(B.GetValue(0))
            elif t=='d':
                D[v] = B.GetValue(0)
            elif t=='v':
                for r in ['X','Y','Z']:
                    D[v+r] = B.FindLeaf(v+r).GetValue(0)
            else:
                pass
        return D
    def Efunction(self, E, hitType):
        '''
        convert energy in MeV to keV (hitType==HODO) or wavelength(nm) (hitType==PMT)
        '''
        if self.detTypeMap[hitType]=='HODO': return E*1000.
        if self.detTypeMap[hitType]=='PMT' and E>0.:
            hc = 1239.842
            return hc/(E*1e6)
        return -99.
    def Etitle(self, hitType):
        '''
        Give appropriate title for energy variable.
        For PMTs, energy in MeV will be converted wavelength in nm
        For Hodos, energy is returned in keV
        '''
        d = self.detTypeMap[hitType]
        if d=='HODO': return 'EkeV'
        if d=='PMT' : return 'WLnm'
        return 'Etitle ERROR. Unknown hitType ' + hitType
    def dump(self,evtDict):
        '''
        Dump contents of list of dictionaries of either hits or tracks.
        No dump if list length is zero
        '''
        if len(evtDict)==0: return
        #### Hits?
        if 'fiProc' in evtDict[0]:
            for hitType in ['PMT', 'HODO']:
                printHdr = True
                for evt in evtDict:
                    if (evt['fiProc']>0 and hitType=='PMT') or (evt['fiProc']<0 and hitType=='HODO') :
                        if printHdr:
                            eTitle  = self.Etitle(hitType)
                            print '{:>6} {:>6} {:>3} {:>4} {:>4} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} Evt# {:<8d} {:<}'\
                                .format('Tid','Pid','PMT',eTitle,'Tns','hXmm','hYmm','hZmm','vXmm','vYmm','vZmm',evtDict[0]['fEvtNb'],hitType)
                        printHdr = False
                        print '{:>6d} {:>6d} {:>3d} {:4d} {:>4.1f} {:>5d} {:>5d} {:>5d} {:>5d} {:>5d} {:>5d}'\
                              .format(evt['fTrackID'],evt['fParentID'],evt['fPmtNb'],\
                                      int(self.Efunction(evt['fEop'],hitType)+.5),evt['fTop'],\
                                      int(evt['fPosX']),int(evt['fPosY']),int(evt['fPosZ']),\
                                      int(evt['fTrkOriginX']),int(evt['fTrkOriginY']),int(evt['fTrkOriginZ']) )
            return
        ### Tracks?
        if 'fPDG' in evtDict[0]:
            print '{:>3} {:>4} {:>4} {:>3} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>6} {:>6} {:>6} {:>6} {:>6} {:>6} Evt# {:<8d}'\
                  .format('PDG','Eliq','Lliq','FO','iXmm','iYmm','iZmm','fXmm','fYmm','fZmm','iPXMeV','iPYMeV','iPZMeV','fPXMeV',\
                          'fPYMeV','fPZMeV',evtDict[0]['fEvtNb'])
            for evt in evtDict:
                print '{:>3d} {:>4d} {:>4d} {:>3d} {:>5d} {:>5d} {:>5d} {:>5d} {:>5d} {:>5d} {:>6.1f} {:>6.1f} {:>6.1f} {:>6.1f} {:>6.1f} {:>6.1f}'\
                .format(evt['fPDG'],int(evt['fLiqELoss']+0.5),int(evt['fLiqPathLen']),evt['fFateOrigin'],\
                        int(evt['fStartVtxX']),int(evt['fStartVtxY']),int(evt['fStartVtxZ']),\
                        int(evt['fFinalVtxX']),int(evt['fFinalVtxY']),int(evt['fFinalVtxZ']),\
                        evt['fStartPX'],evt['fStartPY'],evt['fStartPZ'],evt['fFinalPX'],evt['fFinalPY'],evt['fFinalPZ'])
            return
        ### Should not happen
        print 'onton.dump ERROR unknown evtDict',evtDict
        sys.exit('oneton.dump Unknown argument')
        return
    def testingMode(self,_hTree,_tTree,testHit,testTrack):
        '''
        initially used to test how to get contents of trees       
        '''
        if (testHit):
            i = 0
            for hev in _hTree:
                print 'print tree...'
                hev.Print()
                print 'dump tree...'
                hev.Dump()
                print 'hev.FindBranch("newHit")',hev.FindBranch("newHit")
                print 'hev.GetBranch("newHit")',hev.GetBranch("newHit")
                print 'hev.FindObject("newHit")',hev.FindObject("newHit")
                print 'Dumping....'
                hev.FindBranch("newHit").Dump()

                for v in self.hits_vlist:
                    print 'v,hev.FindObject(v)',v,hev.FindObject(v)
                    print 'v,hev.FindBranch(v)',v,hev.FindBranch(v)
                    print 'v,hev.FindLeaf(v)',v,hev.FindLeaf(v)
                    print 'v,hev.GetBranch(v)',v,hev.GetBranch(v)
                    print 'v,hev.GetLeaf(v)',v,hev.GetLeaf(v)

                    print 'v,hev.FindBranch.FindObject(v)',v,hev.FindBranch("newHit").FindObject(v)
                    print 'v,hev.FindBranch.FindBranch(v)',v,hev.FindBranch("newHit").FindBranch(v)
                    print 'v,hev.FindBranch.FindLeaf(v)',v,hev.FindBranch("newHit").FindLeaf(v)
                    w = 'newHit.' + v
                    print 'w,hev.FindObject(w)',w,hev.FindObject(w)
                    print 'w,hev.FindBranch(w)',w,hev.FindBranch(w)

                print '...................'
                Hit = self.unpackHit(hev)
                print '++++++ i',i,
                for v in Hit: print v,Hit[v],
                print ''
                i += 1
        if (testTrack):
            i = 0
            for tev in _tTree:
                Track = self.unpackTrack(tev)
                print '+++ i',i,
                for v in Track: print v,Track[v],
                print ''
                i += 1
        return
                
if __name__ == '__main__':
    args = sys.argv
    maxEvents = -1
    if len(args)>1:
        if len(args)>2: maxEvents = int(args[2])
        ot = oneton(input_rfn=args[1],EventsToProcess=maxEvents)
    else:
        ot = oneton()
    ot.firstTry()
