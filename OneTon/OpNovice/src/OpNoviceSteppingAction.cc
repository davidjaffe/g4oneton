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

#include "OnetonTrackingAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "G4UnitsTable.hh"

#include "OpNoviceRunAction.hh"

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
    if (false) {
      G4cout << " Number of Scintillation Photons in previous event: "  << fScintillationCounter << G4endl;
      G4cout << " Number of Cerenkov Photons in previous event: "       << fCerenkovCounter << G4endl;
    }
     fEventNumber = eventNumber;
     fScintillationCounter = 0;
     fCerenkovCounter = 0;
  }

  G4bool debug = false;
  G4bool boundary_debug = false;

  G4Track* track = step->GetTrack();
  G4int pdg =  track->GetDynamicParticle()->GetPDGcode();
  //  if (pdg==-11) debug = debug || true; /// DEBUG POSITRONS
  if (debug) {
    G4cout << "OpNoviceSteppingAction::UserSteppingAction Dump positron before last step " << G4endl;
    DumpUserTrackInfo( track ); /////////////////// <<<<<<<<<<<<<<<<<<< DEBUG  <<<<<<<<<<<<<
  }
  G4bool trackIsDone = track->GetTrackStatus()==fStopAndKill ; // last step for this track
  G4bool saveTrack = (track->GetParentID()==0 || ( track->GetCreatorProcess()->GetProcessName()=="Decay" ) ) ;
  G4StepPoint* preStep  = step->GetPreStepPoint();
  G4StepPoint* postStep = step->GetPostStepPoint();
  OnetonUserTrackInformation* trackInformation = (OnetonUserTrackInformation*)track->GetUserInformation();
  if (debug) G4cout << " trackInformation ptr is " << trackInformation << G4endl;
  trackInformation->SetStartVtx( track->GetVertexPosition() );
  trackInformation->SetEvtNb( eventNumber );
  if (trackInformation->GetStartMomentum()==G4ThreeVector())     trackInformation->SetStartMomentum( preStep->GetMomentum() );
  trackInformation->SetFinalMomentum( track->GetMomentum() );
  trackInformation->SetFinalVtx( track->GetPosition() ); 
  trackInformation->SetPDG(pdg );
  G4bool notNeutrino = !(abs(pdg)==12 || abs(pdg)==14);
  if (track->GetParentID()==0) {
    trackInformation->SetFateOrigin( 00 );
  }
  if (postStep) {
    if ( track->GetVolume()->GetName()=="liqcyl"){
      trackInformation->SetLiquidELoss( step->GetTotalEnergyDeposit() );
      trackInformation->SetLiquidPathLength( step->GetStepLength() );
    }
    // figure out what happened at the end of the life of this track that we want to save
    if (trackIsDone && saveTrack) {
    G4bool leftWorld = (postStep->GetStepStatus()==fWorldBoundary);
    G4bool stopped  = track->GetKineticEnergy()<=1*CLHEP::eV;
    G4bool decayed = false, annihilated = false;
    if (step->GetPostStepPoint()->GetProcessDefinedStep()) {
      G4String procName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
      annihilated = (procName=="annihil");
      decayed   = (procName=="Decay") ;
    }
    if (leftWorld || stopped || decayed || annihilated ) {
      if (leftWorld) trackInformation->SetFateOrigin( 0 );
      if (stopped)  trackInformation->SetFateOrigin( 2 );
      if (decayed)  trackInformation->SetFateOrigin( 1 );
      if (annihilated) trackInformation->SetFateOrigin( 3 );
      // fill tree
      //get run action pointer
      OpNoviceRunAction* myRunAction = (OpNoviceRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
      if (debug) {
	G4cout << " add trackInformation to tree. myRunAction=" << myRunAction << " leftWorld,stopped,decayed,annihilated " << leftWorld << stopped << decayed << annihilated << G4endl;
	G4cout << "OpNoviceSteppingAction::UserSteppingAction Dump positron after last step, prior to TallyInfo " << G4endl;
	DumpUserTrackInfo( track ); /////////////////// <<<<<<<<<<<<<<<<<<< DEBUG <<<<<<<<<<<<<
      }
      if(myRunAction && notNeutrino){ 	myRunAction->TallyInfo( trackInformation);       }
    }
    }
  }


  // postStep status = 0 implies particle left mother volume ("OutOfWorld")
  if (debug) {
    G4cout << " trackInformation " << trackInformation << " track ID " << track->GetTrackID() << " status " << track->GetTrackStatus() << " KE " << track->GetKineticEnergy() ;
    if (preStep) G4cout << " preStep: Status " << preStep->GetStepStatus() ;
    if (preStep->GetMaterial()) G4cout << " Material " << preStep->GetMaterial()->GetName() ;
    if (postStep) G4cout << " postStep: Status " << postStep->GetStepStatus() ;
    if (postStep->GetMaterial()) G4cout << " Material " << postStep->GetMaterial()->GetName() ;
    if (step->GetPostStepPoint()->GetProcessDefinedStep())      G4cout << " process " << step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4cout << G4endl;
    const std::vector<const G4Track*>* Sec = step->GetSecondaryInCurrentStep() ;
    if (Sec->size()>0){
      G4cout << "Secondaries: " ;
      for (size_t i = 0; i < Sec->size() ; i++){
	//G4cout << ((*Sec)[i])->GetDynamicParticle()->GetParticleDefinition()->GetParticleName() << " " ;
	G4cout << Sec->at(i)->GetDynamicParticle()->GetParticleDefinition()->GetParticleName()  ;
	G4cout << " id " << Sec->at(i)->GetTrackID() << " parentID " << Sec->at(i)->GetParentID()  <<  " KE " << Sec->at(i)->GetKineticEnergy()  ;
	G4cout << " status " << Sec->at(i)->GetTrackStatus() ; 
	G4cout << " creatorProc " << Sec->at(i)->GetCreatorProcess()->GetProcessName() <<  " "  ;
      }
      G4cout << G4endl;
    }

  }

  G4String ParticleName = track->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();

  // lifted from extended/optical/LXe
  G4OpBoundaryProcessStatus boundaryStatus=Undefined;
  static G4ThreadLocal G4OpBoundaryProcess* boundary=NULL;

  //find the boundary process only once
  if(!boundary){
    G4ProcessManager* pm = step->GetTrack()->GetDefinition()->GetProcessManager();
    G4int nprocesses = pm->GetProcessListLength();
    G4ProcessVector* pv = pm->GetProcessList();
    if (debug) G4cout << " processmanager " << pm << " #processes " << nprocesses << " processvector " << pv << G4endl;
    G4int i;
    for( i=0;i<nprocesses;i++){
      if (boundary_debug)  G4cout << "stepaction " << ParticleName << " process#,name " << i << ", " << (*pv)[i]->GetProcessName() << G4endl;
      if((*pv)[i]->GetProcessName()=="OpBoundary"){
        boundary = (G4OpBoundaryProcess*)(*pv)[i];
        break;
      }
    }
  }
  if (boundary_debug) G4cout << " boundary " << boundary << G4endl;
  if (boundary) {
    boundaryStatus=boundary->GetStatus();
    if (boundary_debug)  G4cout << " boundaryStatus " << boundaryStatus  << G4endl;
    G4String preProc = "NONE";
    if (preStep->GetProcessDefinedStep()) preProc = preStep->GetProcessDefinedStep()->GetProcessName();
    if (boundary_debug)  G4cout << " boundaryStatus " << boundaryStatus 
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
	if (boundary_debug) 	G4cout << " Absorption boundaryStatus " << boundaryStatus << G4endl;
	//     trackInformation->AddTrackStatusFlag(boundaryAbsorbed);
        //eventInformation->IncBoundaryAbsorption();
        break;
      case Detection: //Note, this assumes that the volume causing detection
                      //is the photocathode because it is the only one with
                      //non-zero efficiency
	if (boundary_debug) G4cout << " Detection boundaryStatus " << boundaryStatus << G4endl;
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
	if (boundary_debug) G4cout << " FresnelReflection boundaryStatus " << boundaryStatus << G4endl;
	break;

      case FresnelRefraction:
	if (boundary_debug) G4cout << " FresnelRefraction boundaryStatus " << boundaryStatus << G4endl;
	break;
      case SameMaterial:
	if (boundary_debug) G4cout << " SameMaterial boundaryStatus " << boundaryStatus << G4endl;
	break;
      case StepTooSmall:
	if (boundary_debug) G4cout << " StepTooSmall boundaryStatus " << boundaryStatus << G4endl;
	break;
      case NoRINDEX:
	if (boundary_debug) G4cout << " NoRINDEX boundaryStatus " << boundaryStatus << G4endl;
	break;

      case TotalInternalReflection:
	if (boundary_debug) G4cout << " TotalInternalReflection boundaryStatus " << boundaryStatus << G4endl;
	break;
      case LambertianReflection:
	if (boundary_debug) G4cout << " LambertianReflection boundaryStatus " << boundaryStatus << G4endl;
	break;
      case LobeReflection:
	if (boundary_debug) G4cout << " LobeReflection boundaryStatus " << boundaryStatus << G4endl;
	break;
      case SpikeReflection:
	if (boundary_debug) G4cout << " SpikeReflection boundaryStatus " << boundaryStatus << G4endl;
	break;
      case Transmission:
	if (boundary_debug) G4cout << " Transmission boundaryStatus " << boundaryStatus << G4endl;
	break;
      case BackScattering:
	if (boundary_debug) G4cout << " BackScattering boundaryStatus " << boundaryStatus << G4endl;
	break;
        //trackInformation->IncReflections();
	//        fExpectedNextStatus=StepTooSmall;
      default:
	if (boundary_debug) G4cout << " default boundaryStatus " << boundaryStatus << G4endl;
        break;
      }
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
void OpNoviceSteppingAction::DumpUserTrackInfo(const G4Track* aTrack)
{
  OnetonUserTrackInformation* info = (OnetonUserTrackInformation*)(aTrack->GetUserInformation());
  G4cout << "aTrack " << aTrack 
	 << " track info: trk# " << aTrack->GetTrackID() << " parent " << aTrack->GetParentID() 
	 << " " << aTrack->GetDynamicParticle()->GetParticleDefinition()->GetParticleName()
	 << " #DirChanges " << info->GetDirChangeCount() 
	 << " cos(ini,fin) " << info->GetCosIniFin() 
	 << " boundaryProc " << info->GetBoundaryProc()
	 << " track length " << G4BestUnit( aTrack->GetTrackLength(), "Length")
	 << " track origin " << aTrack->GetVertexPosition()
	 << " start vtx " << info->GetStartVtx()
	 << " final vtx " << info->GetFinalVtx()
	 << " start p " << info->GetStartMomentum()
	 << " final p " << info->GetFinalMomentum()
	 << " PDG " << info->GetPDG()
	 << " Fate&Origin " << info->GetFateOrigin()
	 << " evtNb " << info->GetEvtNb()
	 << " liquid pathlen " << info->GetLiquidPathLength()
	 << " liquid Eloss " << info->GetLiquidELoss()
	 << G4endl; 
    
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
