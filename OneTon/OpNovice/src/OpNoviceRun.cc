//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: OpNoviceRun.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file OpNoviceRun.cc
/// \brief Implementation of the OpNoviceRun class

#include "OpNoviceRun.hh"

#include "OneTonTrackerSD.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceRun::OpNoviceRun()
 : G4Run(), 
   fGoodEvents(0)
{ }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceRun::~OpNoviceRun()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceRun::RecordEvent(const G4Event* event)
{
  G4int evtNb = event->GetEventID();
  
  G4cout << "---> end of event: " << evtNb ; // nPMT

  
  //Hits collections
  //  
  G4HCofThisEvent* HCE = event->GetHCofThisEvent();
  if(!HCE) return;
  OnetonTrackerHitsCollection* HC = (OnetonTrackerHitsCollection*)(HCE->GetHC(0));

  // get the PMT numbers from the SD manager
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  const G4String detName =  "Oneton/PMT";
  OnetonTrackerSD* aPmtSD  = static_cast<OnetonTrackerSD*>(SDman->FindSensitiveDetector(detName));

  G4int nPMT = aPmtSD->PMTnumbers.size();
  G4cout << " nPMT " << nPMT ; // nHits

  // do some counting of hits, unweighted and weighted, by process
  // initialize all maps to zero entries for each PMT
  std::map<G4int, G4double> PMThits, PMTwts,  PMThitsC, PMTwtsC;
  for (G4int i=0; i< nPMT;i++) {
    G4int pn = aPmtSD->PMTnumbers[i];
    PMThits[pn] = 0.0;
    PMTwts[pn]  = 0.0;
    PMThitsC[pn]= 0.0;
    PMTwtsC[pn] = 0.0;
  }
 
  G4int N = HC->entries();
  G4cout << " nHit " << N ; // totWt
  G4double totWt = 0.;
  for ( G4int i=0; i<N; i++) {
    G4int pn = (*HC)[i]->GetPmtNb();
    if (PMThits.find(pn)==PMThits.end()) { 
      G4cout << " OpNoviceRun::RecordEvent ERROR for PMT# " << pn << " it is not in the list of PMT numbers for this sensitive detector " << G4endl;
    }
    PMThits[pn] += 1.;
    PMTwts[pn]  += (*HC)[i]->GetWeight();
    totWt       += (*HC)[i]->GetWeight();
    if ( (*HC)[i]->GetProc()=="Cerenkov" ) {
      PMThitsC[pn] += 1.;
      PMTwtsC[pn]  += (*HC)[i]->GetWeight();
    }
  }
  G4cout << " nWt " << totWt << G4endl;
	 //G4cout << "\n From RecordEvent " << G4endl;
  for (std::map<G4int, G4double>::const_iterator it = PMThits.begin(); it != PMThits.end(); ++it){
    if (false) G4cout << "PMT# " << it->first 
		      << " #hits= " << it->second 
		      << " #Cer.hits= " << PMThitsC.find(it->first)->second
		      << " sum wts " << PMTwts.find(it->first)->second
		      << " sum Cer.wts " << PMTwtsC.find(it->first)->second
		      << G4endl;

    // store per event info 
    PMThpe[it->first].push_back(it->second);
    PMTwpe[it->first].push_back(PMTwts.find(it->first)->second);
    PMThpeC[it->first].push_back(PMThitsC.find(it->first)->second);
    PMTwpeC[it->first].push_back(PMTwtsC.find(it->first)->second);

  }
  

  
  G4Run::RecordEvent(event);      
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceRun::Merge(const G4Run* aRun)
{
  const OpNoviceRun* localRun = static_cast<const OpNoviceRun*>(aRun);
  fGoodEvents += localRun->fGoodEvents;

  G4Run::Merge(aRun); 
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
