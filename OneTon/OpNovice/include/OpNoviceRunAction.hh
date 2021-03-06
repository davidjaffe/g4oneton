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
// $Id: OpNoviceRunAction.hh 70599 2013-06-03 11:14:56Z gcosmo $
//
/// \file OpNoviceRunAction.hh
/// \brief Definition of the OpNoviceRunAction class

#ifndef OpNoviceRunAction_h
#define OpNoviceRunAction_h 1

#include "G4UserRunAction.hh"
#include "OnetonTrackerHit.hh"
#include "OnetonUserTrackInformation.hh"
#include "globals.hh"

#include "TH1.h"


class G4Run;

class TTree;
class TFile;

/// Run action class

class OpNoviceRunAction : public G4UserRunAction
{
public:
  OpNoviceRunAction();
  virtual ~OpNoviceRunAction();
    
  virtual G4Run* GenerateRun();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);
  virtual void Tally( OnetonTrackerHit*);
  virtual void TallyInfo( OnetonUserTrackInformation*);
private:
  TFile* rootFile;
  G4String rootFileName;
  TTree* rootTree1;
  TTree* rootTree2;
  TTree* rootTree3;
  TTree* rootTree4;
  OnetonTrackerHit* newHit =0;
  std::vector<OnetonTrackerHit*> bunchOfHits;
  OnetonUserTrackInformation* info=0;
  G4bool useTree;
  G4bool debug;


  // for rootTree3. shameless copy of OnetonTrackerHit, vectors altered
  G4int         fTrackID;
  G4int         fParentID;
  G4int         fPmtNb;
  G4double      fEop;
  G4double      fTop;
  G4double      fPosX,fPosY,fPosZ;
  std::string      fProc;
  G4double      fWt;
  G4int         fPSType; // process subtype
  G4double fDirChanges; // # of times OP changes directions
  G4double fCosIF;  // cosine(initial OP direction, final OP direction)
  G4int    fbProc; // boundary process
  G4double fTrkLen; // OP path length
  G4double fTrkOriginX,fTrkOriginY,fTrkOriginZ; // OP origin
  G4int    fEvtNb;
  G4int    fiProc;

  // for rootTree4. copy of OnetonUserTrackInformation, vectors altered
  // G4int fDirChanges; also in dumHits
  G4double fCosIniFin;
  G4int fBoundaryProc;
  G4double fLiqPathLen, fLiqELoss;
  G4int fFateOrigin;
  //  G4int fEvtNb; also in dumHits
  G4double fStartVtxX, fStartPX, fFinalVtxX, fFinalPX;
  G4double fStartVtxY, fStartPY, fFinalVtxY, fFinalPY;
  G4double fStartVtxZ, fStartPZ, fFinalVtxZ, fFinalPZ;
  G4int fPDG;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

