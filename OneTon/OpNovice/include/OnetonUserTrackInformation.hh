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
// $Id: OnetonUserTrackInformation.hh 68752 2013-04-05 10:23:47Z gcosmo $
//
/// \file optical/Oneton/include/OnetonUserTrackInformation.hh
/// \brief Definition of the OnetonUserTrackInformation class
//
#include "G4VUserTrackInformation.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

#ifndef OnetonUserTrackInformation_h
#define OnetonUserTrackInformation_h 1

enum OnetonTrackStatus { active=1, hitPMT=2, absorbed=4, boundaryAbsorbed=8,
                      hitSphere=16, inactive=14};

/*OnetonTrackStatus:
  active: still being tracked
  hitPMT: stopped by being detected in a PMT
  absorbed: stopped by being absorbed with G4OpAbsorbtion
  boundaryAbsorbed: stopped by being aborbed with G4OpAbsorbtion
  hitSphere: track hit the sphere at some point
  inactive: track is stopped for some reason
   -This is the sum of all stopped flags so can be used to remove stopped flags
 
*/

class OnetonUserTrackInformation : public G4VUserTrackInformation
{
  public:

    OnetonUserTrackInformation();
    virtual ~OnetonUserTrackInformation();


  void IncDirChanges(G4double cosdir ){ if (cosdir<cos(0.001)) fDirChanges++;}
  G4int GetDirChangeCount()const {return fDirChanges;}
  
  void SetCosIniFin( G4double inifin ) { fCosIniFin = inifin;};
  G4double GetCosIniFin() const { return fCosIniFin;};

  void SetBoundaryProc( G4int bp ) { fBoundaryProc = bp;};
  G4int GetBoundaryProc() const {return fBoundaryProc;};

  void SetLiquidPathLength( G4double pl ) { fLiqPathLen += pl;};
  G4double GetLiquidPathLength() const {return fLiqPathLen;};

  void SetLiquidELoss( G4double el ) { fLiqELoss += el ;};
  G4double GetLiquidELoss() const {return fLiqELoss;};

  void SetFateOrigin( G4int fo ) { fFateOrigin = fo || fFateOrigin;};
  G4int GetFateOrigin() const {return fFateOrigin ;};

  void SetEvtNb( G4int rn ) { fEvtNb = rn;};
  G4int GetEvtNb() const {return fEvtNb;};

  void SetStartVtx( G4ThreeVector sv ) { fStartVtx = sv;};
  G4ThreeVector GetStartVtx() const {return fStartVtx;};
  void SetFinalVtx( G4ThreeVector fv ) { fFinalVtx = fv;};
  G4ThreeVector GetFinalVtx() const {return fFinalVtx;};
  void SetStartMomentum( G4ThreeVector sp ) {fStartP = sp;};
  G4ThreeVector GetStartMomentum() const {return fStartP;};
  void SetFinalMomentum( G4ThreeVector sp ) {fFinalP = sp;};
  G4ThreeVector GetFinalMomentum() const {return fFinalP;};
  
  void SetPDG( G4int pdg) {fPDG = pdg;};
  G4int GetPDG() const {return fPDG;};
  


  //  inline virtual void Print() const{};

  private:


  G4int fDirChanges;
  G4double fCosIniFin;
  G4int fBoundaryProc;
  G4double fLiqPathLen, fLiqELoss;
  G4int fFateOrigin;
  G4int fEvtNb;
  G4ThreeVector fStartVtx, fStartP, fFinalVtx, fFinalP;
  G4int fPDG;
};

#endif
