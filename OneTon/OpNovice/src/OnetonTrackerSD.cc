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
// $Id: OnetonTrackerSD.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file OnetonTrackerSD.cc
/// \brief Implementation of the OnetonTrackerSD class

#include "OnetonTrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "G4VProcess.hh"

#include "G4UserRunAction.hh"
#include "OpNoviceRunAction.hh"
#include "G4RunManager.hh"

#include "G4UnitsTable.hh"

#include "OnetonUserTrackInformation.hh"

//#include "G4Material.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OnetonTrackerSD::OnetonTrackerSD(const G4String& name,
                         const G4String& hitsCollectionName) 
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
  G4cout << "OnetonTrackerSD name " << name << " hitsCollectionName " << hitsCollectionName << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OnetonTrackerSD::~OnetonTrackerSD() 
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OnetonTrackerSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection

  fHitsCollection = new OnetonTrackerHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce

  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 
  // G4cout << "OnetonTrackerSD::Initialize hcID " << hcID << " SensitiveDetectorName " << SensitiveDetectorName << " collectionName[0] " << collectionName[0] << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool OnetonTrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{ 

  G4int eventNumber = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  //G4cout << "\n event# " << eventNumber << "\n " << G4endl;

  G4bool debug = false;

  G4bool killIt = true; // does true kill particle?
  OnetonTrackerHit* newHit = new OnetonTrackerHit(); // might not use this

  //need to know if this is an optical photon
  G4bool opticalPhoton = aStep->GetTrack()->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition();

  G4bool goodHit = opticalPhoton; // all OP are good, only particles leaving energy in hodo are good

  if( !opticalPhoton) { // not an optical photon, create newhit for particles that deposit energy in a hodoscope
    killIt = false;
    G4double Edep = aStep->GetTotalEnergyDeposit() - aStep->GetNonIonizingEnergyDeposit(); // ionizing energy deposited
    G4Track* aTrack = aStep->GetTrack();
    if ( Edep>0 && aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume(0)->GetName()=="Hodo" ) {
      newHit->SetEop( Edep );
      newHit->SetTop(  aTrack->GetGlobalTime() );
      newHit->SetPmtNb ( aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber(0) );
      newHit->SetPos ( aStep->GetPostStepPoint()->GetPosition());
      newHit->SetTrkLen( aTrack->GetTrackLength() ) ;
      newHit->SetTrkOrigin( aTrack->GetVertexPosition() ) ;
      newHit->SetEvtNb( eventNumber );
      newHit->SetWeight( 1. );
      newHit->SetTrackID(  aTrack->GetTrackID() );
      newHit->SetParentID( aTrack->GetParentID());
      newHit->SetProc( "Hodo" );
      newHit->SetProcessSubType( aTrack->GetDynamicParticle()->GetPDGcode() );
      goodHit = true;
    }
    /// 
    if (debug) {
      G4Material* matt1 = aStep->GetPreStepPoint()->GetMaterial();
      G4Material* matt2 = aStep->GetPostStepPoint()->GetMaterial();
      assert(matt1);
      assert(matt2);
      G4cout << " track# " << aTrack->GetTrackID() << " name " << aTrack->GetDynamicParticle()->GetParticleDefinition()->GetParticleName()
	     << " pre-step material " << matt1->GetName()
	     << " post-step material " << matt2->GetName()
	     << " Edep_tot " << aStep->GetTotalEnergyDeposit() << " Edep_nonion " << aStep->GetNonIonizingEnergyDeposit()
	     << " time " << aTrack->GetGlobalTime() << " KE " << aTrack->GetDynamicParticle()->GetKineticEnergy()
	     << " copy # " << aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber(0)
	     << " volume0 " << aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume(0)->GetName()
	     << " volume1 " << aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume(1)->GetName()
	     << G4endl;
    }


    //return false;
  }
  else { // processing of optical photon

    // check to see if this optical photon has already been added to the hits collection.
    G4int TrackID = aStep->GetTrack()->GetTrackID();
    G4int nofHits = fHitsCollection->entries();
    for ( G4int i=0; i<nofHits; i++ ) {
      if ((*fHitsCollection)[i]->GetTrackID()==TrackID) {
	G4cout << " OnetonTrackerSD::ProcessHits ERROR This TrackID " << TrackID << " has already been processed !!!!! " << G4endl;
	aStep->GetTrack()->GetDynamicParticle()->DumpInfo();
      }
    }

    // determine the weight = quantum efficiency to assign to this OP from the OP energy
    // need to get the post-step material since photocathode is a surface and OP apparently doesn't stop "in" a surface
    double Eop = aStep->GetTrack()->GetDynamicParticle()->GetKineticEnergy();
    G4Material* mat = aStep->GetPostStepPoint()->GetMaterial();
    assert(mat && "No material associated with step");
    if (debug) G4cout << " material " << mat->GetName() <<  G4endl;
    G4MaterialPropertiesTable* MPT = mat->GetMaterialPropertiesTable();
    assert(MPT && "No materials properties table associated with material");
    G4MaterialPropertyVector* QE = MPT->GetProperty("QUANTUM_EFFICIENCY");
    assert(QE  && "No quantum efficiency in material properties table");

    //OnetonTrackerHit* newHit = new OnetonTrackerHit();

    newHit->SetEvtNb( eventNumber );

    newHit->SetWeight( QE->Value(Eop) );
    newHit->SetTrackID(  TrackID );
    newHit->SetParentID( aStep->GetTrack()->GetParentID());

    newHit->SetPmtNb(aStep->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1)); // use replica instead of copy number
    newHit->SetEop( Eop );
    newHit->SetTop(aStep->GetTrack()->GetGlobalTime() );
    newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());
    // fun fact: if OP created with gun, then there is no creator process!
    std::string ProcName = "NONE";
    G4int ProcSubType = -99;
    if (aStep->GetTrack()->GetCreatorProcess()) {
      ProcName = aStep->GetTrack()->GetCreatorProcess()->GetProcessName();
      ProcSubType = aStep->GetTrack()->GetCreatorProcess()->GetProcessSubType();
    }
    newHit->SetProc( ProcName );
    newHit->SetiProc( ProcName );
    newHit->SetProcessSubType( ProcSubType );


    OnetonUserTrackInformation* info = (OnetonUserTrackInformation*)(aStep->GetTrack()->GetUserInformation());
    if (debug) G4cout << "aStep->GetTrack() " << aStep->GetTrack() 
		      << "track info: trk# " << aStep->GetTrack()->GetTrackID() << " parent " << aStep->GetTrack()->GetParentID() 
		      << " " << aStep->GetTrack()->GetDynamicParticle()->GetParticleDefinition()->GetParticleName()
		      << " #DirChanges " << info->GetDirChangeCount() 
		      << " cos(ini,fin) " << info->GetCosIniFin() 
		      << " boundaryProc " << info->GetBoundaryProc()
		      << " track length " << G4BestUnit( aStep->GetTrack()->GetTrackLength(), "Length")
		      << " track origin " << aStep->GetTrack()->GetVertexPosition()
		      << G4endl; 

    newHit->SetDirChanges( info->GetDirChangeCount() ) ;
    newHit->SetCosIF( info->GetCosIniFin() ) ;
    newHit->SetbProc( info->GetBoundaryProc() ) ;
    newHit->SetTrkLen( aStep->GetTrack()->GetTrackLength() ) ;
    newHit->SetTrkOrigin( aStep->GetTrack()->GetVertexPosition() ) ;


  }
  if (goodHit) {
      fHitsCollection->insert( newHit );

      // debugging output
      if (debug) newHit->Print();
      if (debug) aStep->GetTrack()->GetDynamicParticle()->DumpInfo();

      // fill tree
      //get run action pointer
      OpNoviceRunAction* myRunAction = (OpNoviceRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
      if (debug) G4cout << " add newHit to tree. myRunAction=" << myRunAction << G4endl;
      if(myRunAction){
	myRunAction->Tally( newHit);
      }
      if (debug) G4cout << " added newHit to tree. killIt " << killIt << G4endl;

      //   prevent this OP from propagating further and being double counted
      //aStep->GetTrack()->SetTrackStatus(fStopAndKill);
  }
  return killIt; //true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OnetonTrackerSD::EndOfEvent(G4HCofThisEvent*)
{
  if ( verboseLevel>2 ) { 
     G4int nofHits = fHitsCollection->entries();
     G4cout << G4endl
            << "-------->Hits Collection: in this event they are " << nofHits 
            << " hits in PMTs: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  }
  /* THIS CODE REPEATED IN OpNoviceRun
  // do some counting of hits, unweighted and weighted, by process
  std::map<G4int, G4double> PMThits, PMTwts,  PMThitsC, PMTwtsC;
  G4int N = fHitsCollection->entries();
  for ( G4int i=0; i<N; i++) {
    G4int pn = (*fHitsCollection)[i]->GetPmtNb();
    if (PMThits.find(pn)==PMThits.end()) { 
      PMThits[pn] = 0.0;
      PMTwts[pn]  = 0.0;
      PMThitsC[pn]= 0.0;
      PMTwtsC[pn] = 0.0;
    }
    PMThits[pn] += 1.;
    PMTwts[pn]  += (*fHitsCollection)[i]->GetWeight();
    if ( (*fHitsCollection)[i]->GetProc()=="Cerenkov" ) {
      PMThitsC[pn] += 1.;
      PMTwtsC[pn]  += (*fHitsCollection)[i]->GetWeight();
    }
  }
  for (std::map<G4int, G4double>::const_iterator it = PMThits.begin(); it != PMThits.end(); ++it){
    G4cout << "PMT# " << it->first 
	   << " #hits= " << it->second 
	   << " #Cer.hits= " << PMThitsC.find(it->first)->second
	   << " sum wts " << PMTwts.find(it->first)->second
	   << " sum Cer.wts " << PMTwtsC.find(it->first)->second
	   << G4endl;
  }
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
