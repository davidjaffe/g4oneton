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
// $Id: OpNoviceSteppingAction.cc 71007 2013-06-09 16:14:59Z maire $
//
/// \file OpNoviceSteppingAction.cc
/// \brief Implementation of the OpNoviceSteppingAction class

#include "OpNoviceSteppingAction.hh"

#include "OnetonUserTrackInformation.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "G4UnitsTable.hh"

// lifted from examples/extended/optical/LXe
#include "G4SteppingManager.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
// end lift

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


OpNoviceSteppingAction::OpNoviceSteppingAction()
: G4UserSteppingAction()
{ 
  fScintillationCounter = 0;
  fCerenkovCounter      = 0;
  fEventNumber = -1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceSteppingAction::~OpNoviceSteppingAction()
{ ; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceSteppingAction::UserSteppingAction(const G4Step* step)
{
  G4int eventNumber = G4RunManager::GetRunManager()->
                                              GetCurrentEvent()->GetEventID();

  if (eventNumber != fEventNumber) {
     G4cout << " Number of Scintillation Photons in previous event: "
            << fScintillationCounter << G4endl;
     G4cout << " Number of Cerenkov Photons in previous event: "
            << fCerenkovCounter << G4endl;
     fEventNumber = eventNumber;
     fScintillationCounter = 0;
     fCerenkovCounter = 0;
  }

  G4bool debug = false;

  G4Track* track = step->GetTrack();
  G4StepPoint* preStep  = step->GetPreStepPoint();
  G4StepPoint* postStep = step->GetPostStepPoint();
  OnetonUserTrackInformation* trackInformation = (OnetonUserTrackInformation*)track->GetUserInformation();
  if (debug)   G4cout << " trackInformation " << trackInformation 
	 << " track->GetUserInformation() " << track->GetUserInformation() << G4endl;

  G4String ParticleName = track->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();

  // lifted from extended/optical/LXe
  G4OpBoundaryProcessStatus boundaryStatus=Undefined;
  static G4ThreadLocal G4OpBoundaryProcess* boundary=NULL;

  //find the boundary process only once
  if(!boundary){
    G4ProcessManager* pm = step->GetTrack()->GetDefinition()->GetProcessManager();
    G4int nprocesses = pm->GetProcessListLength();
    G4ProcessVector* pv = pm->GetProcessList();
    G4int i;
    for( i=0;i<nprocesses;i++){
      if (debug)  G4cout << "stepaction " << ParticleName << " process#,name " << i << ", " << (*pv)[i]->GetProcessName() << G4endl;
      if((*pv)[i]->GetProcessName()=="OpBoundary"){
        boundary = (G4OpBoundaryProcess*)(*pv)[i];
        break;
      }
    }
  }
    boundaryStatus=boundary->GetStatus();
    G4String preProc = "NONE";
    if (preStep->GetProcessDefinedStep()) preProc = preStep->GetProcessDefinedStep()->GetProcessName();
    if (debug)  G4cout << " boundaryStatus " << boundaryStatus 
	   << " dot products, current " << step->GetPreStepPoint()->GetMomentumDirection().dot( step->GetPostStepPoint()->GetMomentumDirection() ) 
	   << " wrt initial " << step->GetPreStepPoint()->GetMomentumDirection().dot( track->GetVertexMomentumDirection() )
	   << " track length " << G4BestUnit( track->GetTrackLength(), "Length")
	   << " track origin " << track->GetVertexPosition()
	   << " original dir " << track->GetVertexMomentumDirection()
	   << " preStep  process " << preProc
	   << " postStep process " << postStep->GetProcessDefinedStep()->GetProcessName()
	   << G4endl;
    trackInformation->IncDirChanges( step->GetPreStepPoint()->GetMomentumDirection().dot( step->GetPostStepPoint()->GetMomentumDirection() )  );
    trackInformation->SetCosIniFin( step->GetPreStepPoint()->GetMomentumDirection().dot( track->GetVertexMomentumDirection() ) );
    trackInformation->SetBoundaryProc( boundaryStatus );
      switch(boundaryStatus){
      case Absorption:
	if (debug) 	G4cout << " Absorption boundaryStatus " << boundaryStatus << G4endl;
	//     trackInformation->AddTrackStatusFlag(boundaryAbsorbed);
        //eventInformation->IncBoundaryAbsorption();
        break;
      case Detection: //Note, this assumes that the volume causing detection
                      //is the photocathode because it is the only one with
                      //non-zero efficiency
	if (debug) G4cout << " Detection boundaryStatus " << boundaryStatus << G4endl;
	break;
        /*{
        //Triger sensitive detector manually since photon is
        //absorbed but status was Detection
        G4SDManager* SDman = G4SDManager::GetSDMpointer();
        G4String sdName="/LXeDet/pmtSD";
        LXePMTSD* pmtSD = (LXePMTSD*)SDman->FindSensitiveDetector(sdName);
        if(pmtSD)pmtSD->ProcessHits_constStep(theStep,NULL);
        trackInformation->AddTrackStatusFlag(hitPMT);
        break;
        }*/
      case FresnelReflection:
	if (debug) G4cout << " FresnelReflection boundaryStatus " << boundaryStatus << G4endl;
	break;

      case FresnelRefraction:
	if (debug) G4cout << " FresnelRefraction boundaryStatus " << boundaryStatus << G4endl;
	break;
      case SameMaterial:
	if (debug) G4cout << " SameMaterial boundaryStatus " << boundaryStatus << G4endl;
	break;
      case StepTooSmall:
	if (debug) G4cout << " StepTooSmall boundaryStatus " << boundaryStatus << G4endl;
	break;
      case NoRINDEX:
	if (debug) G4cout << " NoRINDEX boundaryStatus " << boundaryStatus << G4endl;
	break;

      case TotalInternalReflection:
	if (debug) G4cout << " TotalInternalReflection boundaryStatus " << boundaryStatus << G4endl;
	break;
      case LambertianReflection:
	if (debug) G4cout << " LambertianReflection boundaryStatus " << boundaryStatus << G4endl;
	break;
      case LobeReflection:
	if (debug) G4cout << " LobeReflection boundaryStatus " << boundaryStatus << G4endl;
	break;
      case SpikeReflection:
	if (debug) G4cout << " SpikeReflection boundaryStatus " << boundaryStatus << G4endl;
	break;
      case Transmission:
	if (debug) G4cout << " Transmission boundaryStatus " << boundaryStatus << G4endl;
	break;
      case BackScattering:
	if (debug) G4cout << " BackScattering boundaryStatus " << boundaryStatus << G4endl;
	break;
        //trackInformation->IncReflections();
	//        fExpectedNextStatus=StepTooSmall;
      default:
	G4cout << " default boundaryStatus " << boundaryStatus << G4endl;
        break;
      }

  // --- end lifted from...


  if (ParticleName == "opticalphoton") return;

  const std::vector<const G4Track*>* secondaries =
                                            step->GetSecondaryInCurrentStep();

  if (secondaries->size()>0) {
     for(unsigned int i=0; i<secondaries->size(); ++i) {
        if (secondaries->at(i)->GetParentID()>0) {
           if(secondaries->at(i)->GetDynamicParticle()->GetParticleDefinition()
               == G4OpticalPhoton::OpticalPhotonDefinition()){
              if (secondaries->at(i)->GetCreatorProcess()->GetProcessName()
               == "Scintillation")fScintillationCounter++;
              if (secondaries->at(i)->GetCreatorProcess()->GetProcessName()
               == "Cerenkov")fCerenkovCounter++;
           }
        }
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
