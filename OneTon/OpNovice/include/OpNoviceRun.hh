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
// $Id: OpNoviceRun.hh 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file OpNoviceRun.hh
/// \brief Definition of the OpNoviceRun class

#ifndef OpNoviceRun_h
#define OpNoviceRun_h 1

#include "G4Run.hh"
#include "globals.hh"
#include <map>
#include <vector>

/// Run class
///
/// In RecordEvent() there is collected information event per event 
/// from Hits Collections, and accumulated statistic for the run 

class OpNoviceRun : public G4Run
{
  public:
    OpNoviceRun();
    virtual ~OpNoviceRun();

    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);
    
  public:
    G4int GetNbGoodEvents() const { return fGoodEvents; }
    std::map<G4int, std::vector<G4double> > PMThpe, PMTwpe,  PMThpeC, PMTwpeC;
    
  private:
  G4int fGoodEvents;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
