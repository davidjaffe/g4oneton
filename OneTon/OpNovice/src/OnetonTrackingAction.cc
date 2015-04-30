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
// $Id: OnetonTrackingAction.cc 66526 2012-12-19 13:41:33Z ihrivnac $
//
/// \file Oneton/src/OnetonTrackingAction.cc
/// \brief Implementation of the OnetonTrackingAction class
//

#include "OnetonTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4UnitsTable.hh"

#include "OnetonUserTrackInformation.hh"

OnetonTrackingAction::OnetonTrackingAction(){
  G4cout << " Hello from OnetonTrackingAction " << G4endl;
}
OnetonTrackingAction::~OnetonTrackingAction(){
}

void OnetonTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
  /*  // Create trajectory only for primaries
  if(aTrack->GetParentID()==0)
  { fpTrackingManager->SetStoreTrajectory(true); }
  else
  { fpTrackingManager->SetStoreTrajectory(false); }
  */
}
void OnetonTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
  G4bool debug = false;
  OnetonUserTrackInformation* info = (OnetonUserTrackInformation*)(aTrack->GetUserInformation());
  if (debug) G4cout << "aTrack " << aTrack << G4endl;
  if (debug) G4cout << "track info: trk# " << aTrack->GetTrackID() << " parent " << aTrack->GetParentID() 
	 << " " << aTrack->GetDynamicParticle()->GetParticleDefinition()->GetParticleName()
	 << " #DirChanges " << info->GetDirChangeCount() 
	 << " cos(ini,fin) " << info->GetCosIniFin() 
	 << " boundaryProc " << info->GetBoundaryProc()
	 << " track length " << G4BestUnit( aTrack->GetTrackLength(), "Length")
	 << " track origin " << aTrack->GetVertexPosition()

	 << G4endl; 
    
}



