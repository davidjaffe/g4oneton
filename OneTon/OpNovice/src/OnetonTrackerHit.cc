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
// $Id: OnetonTrackerHit.cc 69706 2013-05-13 09:12:40Z gcosmo $
//
/// \file OnetonTrackerHit.cc
/// \brief Implementation of the OnetonTrackerHit class

#include "OnetonTrackerHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"


#include <iomanip>

G4ThreadLocal G4Allocator<OnetonTrackerHit>* OnetonTrackerHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OnetonTrackerHit::OnetonTrackerHit()
 : G4VHit(),
   fTrackID(-1), 
   fParentID(-1),
   fPmtNb(-1),
   fEop(0.), fTop(0.),
   fPos(G4ThreeVector()), fProc("NONE"), fWt(0.), fPSType(-99),
   fDirChanges(-1), 
   fCosIF(-2.),
   fbProc(-99), 
   fTrkLen(-1.),
   fTrkOrigin(G4ThreeVector()),
   fEvtNb(-1)

{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OnetonTrackerHit::~OnetonTrackerHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OnetonTrackerHit::OnetonTrackerHit(const OnetonTrackerHit& right)
  : G4VHit()
{
  fTrackID   = right.fTrackID;
  fParentID  = right.fParentID;
  fPmtNb = right.fPmtNb;
  fEop      = right.fEop;
  fTop      = right.fTop;
  fPos       = right.fPos;
  fWt        = right.fWt;
  fProc      = right.fProc;
  fPSType    = right.fPSType;
  fDirChanges= right.fDirChanges;
  fCosIF     = right.fCosIF;
  fbProc     = right.fbProc;
  fTrkLen    = right.fTrkLen;
  fTrkOrigin = right.fTrkOrigin;
  fEvtNb     = right.fEvtNb;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const OnetonTrackerHit& OnetonTrackerHit::operator=(const OnetonTrackerHit& right)
{
  fTrackID   = right.fTrackID;
  fParentID  = right.fParentID;
  fPmtNb = right.fPmtNb;
  fEop      = right.fEop;
  fTop      = right.fTop;
  fPos       = right.fPos;
  fWt        = right.fWt;
  fProc      = right.fProc;
  fPSType    = right.fPSType;
  fDirChanges= right.fDirChanges;
  fCosIF     = right.fCosIF;
  fbProc     = right.fbProc;
  fTrkLen    = right.fTrkLen;
  fTrkOrigin = right.fTrkOrigin;
  fEvtNb     = right.fEvtNb;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int OnetonTrackerHit::operator==(const OnetonTrackerHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OnetonTrackerHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(fPos);
    circle.SetScreenSize(4.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OnetonTrackerHit::Print()
{
  if (fProc=="Hodo") {
    G4cout
      << " HODO: Evt# " << fEvtNb << " trackID " << fTrackID << " PDGcode " << fPSType 
      << " parentID: " << fParentID 
      << " Hodo# " << fPmtNb
      << " Eop " << std::setw(7) << G4BestUnit(fEop,"Energy")
      << " Top " << std::setw(7) << G4BestUnit(fTop,"Time")
      << " Position "   << std::setw(7) << G4BestUnit( fPos,"Length")
      << " Origin vtx " << std::setw(7) << G4BestUnit(fTrkOrigin, "Length")
      << " TrkLen " << std::setw(7) << G4BestUnit(fTrkLen, "Length")
      << G4endl;
  }
  else {
    G4cout
      << " PMT: Evt# " << fEvtNb << " trackID " << fTrackID << " parentID: " << fParentID 
      << " optical process " << fProc << " procSubType: " << fPSType
      << " PmtNb " << fPmtNb
      << " Wt " << fWt
      << " Eop " << std::setw(7) << G4BestUnit(fEop,"Energy")
      << " Top " << std::setw(7) << G4BestUnit(fTop,"Time")
      << " Position "   << std::setw(7) << G4BestUnit( fPos,"Length")
      << " Origin vtx " << std::setw(7) << G4BestUnit(fTrkOrigin, "Length")
      << " TrkLen " << std::setw(7) << G4BestUnit(fTrkLen, "Length")
      << " #DirChanges " << fDirChanges 
      << " cos(ini,fin) "<< fCosIF
      << " boundaryProc "<< fbProc
      << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
