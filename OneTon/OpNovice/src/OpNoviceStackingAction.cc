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
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "OpNoviceStackingAction.hh"

#include "OnetonUserTrackInformation.hh"

#include "G4VProcess.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceStackingAction::OpNoviceStackingAction()
  : G4UserStackingAction(),
    fprescaleFactor(0.), fthresFactor(-1.), // FIXME: OPTICAL PHOTON PRESCALE FACTOR SHOULD BE DYNAMIC 
    fScintillationCounter(0), fkilledScintillationCounter(0), fCerenkovCounter(0),    fkilledCerenkovCounter(0)
{

  if (fprescaleFactor>0.) fthresFactor = 1.-1./fprescaleFactor;
  G4cout << " >>>> OpNoviceStackingAction: prescaleFactor " << fprescaleFactor << " thresFactor " << fthresFactor 
	 << ". Kill optical photon if uniform random number (0,1) < thresFactor. " 	 << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceStackingAction::~OpNoviceStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
OpNoviceStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{

  //  initialize user info for track regardless of type
  OnetonUserTrackInformation* trackInfo = new OnetonUserTrackInformation();
  G4Track* theTrack = (G4Track*)aTrack;
  theTrack->SetUserInformation(trackInfo);
 
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      G4bool killed = G4UniformRand()<fthresFactor ; // FIXME: OPTICAL PHOTON PRESCALE FACTOR SHOULD BE DYNAMIC 
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation"){
	fScintillationCounter++;
	if (killed) fkilledScintillationCounter++;
      }
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov"){
        fCerenkovCounter++;
	if (killed) fkilledCerenkovCounter++;
      }
      if (killed) return fKill; // kill this optical photon
    }
  }
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceStackingAction::NewStage()
{
  G4double frac = -1.;
  if (fScintillationCounter + fCerenkovCounter > 0){
    if (fScintillationCounter>0) frac = float(fScintillationCounter-fkilledScintillationCounter)/float(fScintillationCounter);
    G4cout << "Scint OP/evt= "
	   << fScintillationCounter 
	   << " killed: "<< fkilledScintillationCounter 
	   << " propagated (fraction): " << fScintillationCounter-fkilledScintillationCounter << "("<< frac <<")" ;
    //	 << G4endl;
    frac = -1.;
    if (fCerenkovCounter>0) frac = float(fCerenkovCounter-fkilledCerenkovCounter)/float(fCerenkovCounter);
    G4cout << " Cer OP/evt= "
	   << fCerenkovCounter 
	   << " killed: "<< fkilledCerenkovCounter 
	   << " propagated (fraction): " << fCerenkovCounter-fkilledCerenkovCounter << "("<< frac <<")"
	   << G4endl;
    fScintillationCounter = fkilledScintillationCounter = fCerenkovCounter = fkilledCerenkovCounter = 0;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceStackingAction::PrepareNewEvent()
{
  fScintillationCounter = 0;
  fCerenkovCounter = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
