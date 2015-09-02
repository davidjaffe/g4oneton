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
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef OpNoviceDetectorConstruction_h
#define OpNoviceDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class OpNoviceDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    OpNoviceDetectorConstruction();
    virtual ~OpNoviceDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
  virtual std::vector< std::vector < G4double > > GetFileInfo(G4String filename="NONE", G4double unit1=1., G4double unit2=1.);

  private:
    G4double fExpHall_x;
    G4double fExpHall_y;
    G4double fExpHall_z;
  
    G4double fcyl_innerrad, fcyl_outerrad, fcyl_z, fcyl_phimin, fcyl_deltaphi ;
    G4double fcyl_thickness;
    G4double fliq_innerrad, fliq_outerrad, fliq_z, fliq_phimin, fliq_deltaphi ;
  G4double fsheet_innerrad, fsheet_outerrad, fsheet_z, fsheet_phimin, fsheet_deltaphi, fsheet_vspace;
    G4double fPMT_outerrad,   fPMT_z    ;
  G4double ftele_thick0, ftele_width0, ftele_length0 ;

  std::vector< std::vector< G4double > > thedata;
  G4VPhysicalVolume* fexpHall_phys;

  G4int fdebug;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*OpNoviceDetectorConstruction_h*/
