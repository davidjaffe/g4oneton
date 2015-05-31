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
// $Id: OpNoviceRunAction.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file OpNoviceRunAction.cc
/// \brief Implementation of the OpNoviceRunAction class

#include "OpNoviceRunAction.hh"
//#include "OpNovicePrimaryGeneratorAction.hh"
#include "PrimaryGeneratorAction.hh" 
#include "OpNoviceRun.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4UserRunAction.hh"

//#include "TH1.h"

#include "TFile.h"
#include <sstream>
#include "TTree.h"
#include "TROOT.h"


#include <map>
#include <vector>
#include <iomanip>
using std::setw;
using std::setprecision;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceRunAction::OpNoviceRunAction()
 : G4UserRunAction()
{  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceRunAction::~OpNoviceRunAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* OpNoviceRunAction::GenerateRun()
{ return new OpNoviceRun; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceRunAction::BeginOfRunAction(const G4Run* run)
{ 
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
  
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  rootFileName = "../output/runX.root";
  rootFile = new TFile(rootFileName.c_str(),"RECREATE","Oneton Sim Output");
  rootTree = new TTree("Results", "Tree of results from Oneton sim.");
//  OnetonTrackerHit* aHit = new OnetonTrackerHit();

  // initialize pointers according to https://root.cern.ch/root/htmldoc/TTree.html, pointers should not be destroyed until TTree deleted
  //OnetonTrackerHit* aHit = 0;
  rootTree->Branch("newHit","OnetonTrackerHit", &newHit);
  //  OnetonUserTrackInformation* tInfo = 0;
  rootTree->Branch("info","OnetonUserTrackInformation", &info);

}

void OpNoviceRunAction::Tally( OnetonTrackerHit* aHit)
{
  G4cout << "RunAction::Tally newHit" << G4endl;
  newHit = aHit;
  rootTree->Fill();
}
void OpNoviceRunAction::TallyInfo( OnetonUserTrackInformation* tInfo)
{
  G4cout << "RunAction::TallyInfo" << G4endl;
  info = tInfo;
  rootTree->Fill();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  rootFile->Write();
  rootFile->Close();
  
  /*
  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const OpNovicePrimaryGeneratorAction* generatorAction
    = static_cast<const OpNovicePrimaryGeneratorAction*>(
        G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String partName;
  if (generatorAction) 
  {
    G4ParticleDefinition* particle 
      = generatorAction->GetParticleGun()->GetParticleDefinition();
    partName = particle->GetParticleName();
  }  
  */
  //results
  //
  const OpNoviceRun* onRun = static_cast<const OpNoviceRun*>(run);
  G4int nbGoodEvents = onRun->GetNbGoodEvents();
        
  //print
  //
  if (IsMaster())
  {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------"
     << G4endl
     << "  The run was " << nofEvents << " events with " << nbGoodEvents << " good events " << G4endl;
  }
  else
  {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------"
     << G4endl
     << "  The run was " << nofEvents << G4endl;
  }      

  if (0){

    G4cout << "\n End of run info " << G4endl;

    std::map<G4int, G4double> Ahpe, Awpe, AhpeC, AwpeC ;
    // hits per event
    for (std::map<G4int, std::vector<G4double> >::const_iterator it = onRun->PMThpe.begin(); it != onRun->PMThpe.end(); ++it){
      G4cout << "PMT# " << it->first << " #hits= " ;
      G4double sum = 0.;
      for ( std::vector<G4double>::const_iterator kt = it->second.begin(); kt != it->second.end(); ++kt){
	G4cout << *kt << " " ;
	sum += *kt;
      }		
      G4cout	   << G4endl;
      Ahpe[it->first] = sum/float(nofEvents);
    }
    // weights per event
    for (std::map<G4int, std::vector<G4double> >::const_iterator it = onRun->PMTwpe.begin(); it != onRun->PMTwpe.end(); ++it){
      G4cout << "PMT# " << it->first << " wts= " ;
      G4double sum = 0.;
      for ( std::vector<G4double>::const_iterator kt = it->second.begin(); kt != it->second.end(); ++kt){
	G4cout << *kt << " " ;
	sum += *kt;
      }							 
      G4cout	   << G4endl;
      Awpe[it->first] = sum/float(nofEvents);
    }
    // Cerenkov hits per event
    for (std::map<G4int, std::vector<G4double> >::const_iterator it = onRun->PMThpeC.begin(); it != onRun->PMThpeC.end(); ++it){
      G4cout << "PMT# " << it->first << " #Cer,hits= " ;
      G4double sum = 0.;
      for ( std::vector<G4double>::const_iterator kt = it->second.begin(); kt != it->second.end(); ++kt){
	G4cout << *kt << " " ;
	sum += *kt;
      }							 
      G4cout	   << G4endl;
      AhpeC[it->first] = sum/float(nofEvents);
    }
    // Cerenkov weights per event
    for (std::map<G4int, std::vector<G4double> >::const_iterator it = onRun->PMTwpeC.begin(); it != onRun->PMTwpeC.end(); ++it){
      G4cout << "PMT# " << it->first << " Cer.wts= " ;
      G4double sum = 0.;
      for ( std::vector<G4double>::const_iterator kt = it->second.begin(); kt != it->second.end(); ++kt){
	G4cout << *kt << " " ;
	sum += *kt;
      }							 
      G4cout	   << G4endl;
      AwpeC[it->first] = sum/float(nofEvents);
    }
  
    // report averages per event
    G4cout << "\n Summary data for " << nofEvents << " events " << G4endl;
    G4cout << setw(4) << "PMT" 
	   << setw(9) << "hits/evt"
	   << setw(9) << "Wts/evt"
	   << setw(9) << "Cer/evt"
	   << setw(9) << "CerW/evt"
	   << setw(9) << "Sci/evt"
	   << setw(9) << "SciW/evt" 
	   << G4endl;
    G4int isz = 3;
    for (std::map<G4int, G4double>::const_iterator it=Ahpe.begin(); it != Ahpe.end(); ++it){
      G4cout << setw(4) << it->first 
	     << setw(9) << setprecision(isz) << it->second                  << setw(9) << setprecision(isz) << Awpe[it->first] 
	     << setw(9) << setprecision(isz) << AhpeC[it->first]            << setw(9) << setprecision(isz) << AwpeC[it->first]
	     << setw(9) << setprecision(isz) << it->second-AhpeC[it->first] << setw(9) << setprecision(isz) << Awpe[it->first] - AwpeC[it->first] 
	     << G4endl;
    }
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
