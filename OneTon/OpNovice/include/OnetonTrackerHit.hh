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
// $Id: OnetonTrackerHit.hh 69706 2013-05-13 09:12:40Z gcosmo $
//
/// \file OnetonTrackerHit.hh
/// \brief Definition of the OnetonTrackerHit class

#ifndef OnetonTrackerHit_h
#define OnetonTrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

//#include "structHit.hh"

/// Tracker hit class
///
/// It defines data members to store the properties of optical photons

class OnetonTrackerHit : public G4VHit
{
  public:
    OnetonTrackerHit();
    OnetonTrackerHit(const OnetonTrackerHit&);
    virtual ~OnetonTrackerHit();

    // operators
    const OnetonTrackerHit& operator=(const OnetonTrackerHit&);
    G4int operator==(const OnetonTrackerHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw();
    virtual void Print();

    // Set methods
  void SetTrackID  (G4int track)      { fTrackID = track; };
  void SetParentID (G4int parent)     { fParentID= parent; };
  void SetPmtNb   (G4int chamb)       { fPmtNb = chamb; };
  void SetEop     (G4double eop)      { fEop = eop; };
  void SetTop     (G4double top)      { fTop = top; } ; 
  void SetPos     (G4ThreeVector xyz) { fPos = xyz; };
  void SetProc    (std::string proc)     { fProc= proc; };
  void SetiProc   (std::string proc)    {
    if (proc=="Scintillation") { 
      fiProc = 1 ;
    } 
    else if (proc=="Cerenkov") { 
      fiProc = 2 ;
    }  else { 
      fiProc = 3;
    }
  };
  void SetiProc   (G4int ip)          { fiProc = ip;};
  void SetWeight  (G4double wt)       { fWt  = wt;  };
  void SetProcessSubType (G4int pst)  { fPSType = pst; } ;


  void SetDirChanges( G4double dc)      { fDirChanges = dc   ; } ; 
  void SetCosIF( G4double cif)          { fCosIF      = cif  ; } ;
  void SetbProc( G4int bp )             { fbProc      = bp   ; } ;
  void SetTrkLen( G4double tl )         { fTrkLen     = tl   ; } ; 
  void SetTrkOrigin( G4ThreeVector xyz) { fTrkOrigin  = xyz  ; } ; 
  void SetEvtNb( G4int n )              { fEvtNb      = n    ; } ;


  // Get methods
  G4int GetTrackID() const     { return fTrackID; };
  G4int GetParentID() const  { return fParentID; };
  G4int GetPmtNb() const   { return fPmtNb; };
  G4double GetEop() const     { return fEop; };
  G4double GetTop() const     { return fTop; };
  G4ThreeVector GetPos() const { return fPos; };
  std::string GetProc() const { return fProc;} ;
  G4int GetiProc() const {return fiProc;};
  G4double GetWeight() const { return fWt;} ;
  G4int GetProcessSubType() const { return fPSType;} ;
  G4double GetDirChanges() const { return fDirChanges;} ;
  G4double GetCosIF() const      { return fCosIF ; } ;
  G4int    GetbProc() const      { return fbProc ; } ;
  G4double GetTrkLen() const     { return fTrkLen; } ; 
  G4ThreeVector GetTrkOrigin()   { return fTrkOrigin; } ;
  G4int    GetEvtNb() const      { return fEvtNb; } ;

private:

  G4int         fTrackID;
  G4int         fParentID;
  G4int         fPmtNb;
  G4double      fEop;
  G4double      fTop;
  G4ThreeVector fPos;
  std::string      fProc;
  G4double      fWt;
  G4int         fPSType; // process subtype
  G4double fDirChanges; // # of times OP changes directions
  G4double fCosIF;  // cosine(initial OP direction, final OP direction)
  G4int    fbProc; // boundary process
  G4double fTrkLen; // OP path length
  G4ThreeVector fTrkOrigin; // OP origin
  G4int    fEvtNb;
  G4int    fiProc;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<OnetonTrackerHit> OnetonTrackerHitsCollection;

extern G4ThreadLocal G4Allocator<OnetonTrackerHit>* OnetonTrackerHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* OnetonTrackerHit::operator new(size_t)
{
  if(!OnetonTrackerHitAllocator)
      OnetonTrackerHitAllocator = new G4Allocator<OnetonTrackerHit>;
  return (void *) OnetonTrackerHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void OnetonTrackerHit::operator delete(void *hit)
{
  OnetonTrackerHitAllocator->FreeSingle((OnetonTrackerHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
