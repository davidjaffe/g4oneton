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
// $Id: OpNoviceRunAction.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file OpNoviceRunAction.cc
/// \brief Implementation of the OpNoviceRunAction class

#include "OpNoviceRunAction.hh"
//#include "OpNovicePrimaryGeneratorAction.hh"
#include "PrimaryGeneratorAction.hh" 
#include "OpNoviceRun.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4UserRunAction.hh"

//#include "TH1.h"

#include "TFile.h"
#include <sstream>
#include "TTree.h"
#include "TROOT.h"


#include <map>
#include <vector>
#include <iomanip>
#include <stdlib.h> // getenv
using std::setw;
using std::setprecision;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceRunAction::OpNoviceRunAction()
 : G4UserRunAction()
{  
  useTree = true;
  debug   = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceRunAction::~OpNoviceRunAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* OpNoviceRunAction::GenerateRun()
{ return new OpNoviceRun; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceRunAction::BeginOfRunAction(const G4Run* run)
{ 

  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

  
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  if (useTree) {
    G4cout << "OpNoviceRunAction::BeginOfRunAction PWD=" << std::getenv("PWD") << G4endl;
    rootFileName = std::getenv("OUTPUT_ROOT_FILE");
    G4cout << "OpNoviceRunAction::BeginOfRunAction rootFileName=" << rootFileName << G4endl;
    //G4String nothing = std::getenv("THIS_WILL_GIVE_A_NULL_POINTER_BECAUSE_IT_IS_NOT_DEFINED");
    //if (rootFileName==nothing) rootFileName = "../output/runX.root"; 
    rootFile = new TFile(rootFileName.c_str(),"RECREATE","Oneton Sim Output");
    G4cout << "Opened ROOT output file " << rootFileName << G4endl;
    //    rootTree1 = new TTree("Hits", "Oneton hits");
    //rootTree2 = new TTree("Tracks", "Oneton tracks");
    rootTree3 = new TTree("dumHits","Oneton hits w/o object");
    rootTree4 = new TTree("dumTracks","Oneton hits w/o object");
    
    
    // initialize pointers according to https://root.cern.ch/root/htmldoc/TTree.html, pointers should not be destroyed until TTree deleted
    //rootTree1->Branch("newHit","OnetonTrackerHit", &newHit);
    //rootTree2->Branch("info","OnetonUserTrackInformation", &info);

    rootTree3->Branch("fEvtNb",&fEvtNb,"fEvtNb/I");
    rootTree3->Branch("fTrackID",&fTrackID,"fTrackID/I");
    rootTree3->Branch("fParentID",&fParentID,"fParentID/I");
    rootTree3->Branch("fPmtNb",&fPmtNb,"fPmtNb/I");
    rootTree3->Branch("fPSType",&fPSType,"fPSType/I");
    rootTree3->Branch("fbProc",&fbProc,"fbProc/I");
    rootTree3->Branch("fiProc",&fiProc,"fiProc/I");
    rootTree3->Branch("fEop",&fEop,"fEop/D");
    rootTree3->Branch("fTop",&fTop,"fTop/D");
    rootTree3->Branch("fWt",&fWt,"fWt/D");
    rootTree3->Branch("fDirChanges",&fDirChanges,"fDirChanges/D");
    rootTree3->Branch("fCosIF",&fCosIF,"fCosIF/D");
    rootTree3->Branch("fTrkLen",&fTrkLen,"fTrkLen/D");
    //    rootTree3->Branch("fProc",fProc,"fProc/C"); // no & for C?
    rootTree3->Branch("fPosX",&fPosX,"fPosX/D");
    rootTree3->Branch("fPosY",&fPosY,"fPosY/D");
    rootTree3->Branch("fPosZ",&fPosZ,"fPosZ/D");
    rootTree3->Branch("fTrkOriginX",&fTrkOriginX,"fTrkOriginX/D");
    rootTree3->Branch("fTrkOriginY",&fTrkOriginY,"fTrkOriginY/D");
    rootTree3->Branch("fTrkOriginZ",&fTrkOriginZ,"fTrkOriginZ/D");

    rootTree4->Branch("fDirChanges",&fDirChanges,"fDirChanges/I");
    rootTree4->Branch("fPDG",&fPDG,"fPDG/I");
    rootTree4->Branch("fBoundaryProc",&fBoundaryProc,"fBoundaryProc/I");
    rootTree4->Branch("fFateOrigin",&fFateOrigin,"fFateOrigin/I");
    rootTree4->Branch("fEvtNb",&fEvtNb,"fEvtNb/I");

    rootTree4->Branch("fLiqPathLen",&fLiqPathLen,"fLiqPathLen/D");
    rootTree4->Branch("fLiqELoss",&fLiqELoss,"fLiqELoss/D");
    rootTree4->Branch("fCosIniFin",&fCosIniFin,"fCosIniFin/D");
    rootTree4->Branch("fStartVtxX",&fStartVtxX,"fStartVtxX/D");
    rootTree4->Branch("fStartPX",&fStartPX,"fStartPX/D");
    rootTree4->Branch("fFinalVtxX",&fFinalVtxX,"fFinalVtxX/D");
    rootTree4->Branch("fFinalPX",&fFinalPX,"fFinalPX/D");

    rootTree4->Branch("fStartVtxY",&fStartVtxY,"fStartVtxY/D");
    rootTree4->Branch("fStartPY",&fStartPY,"fStartPY/D");
    rootTree4->Branch("fFinalVtxY",&fFinalVtxY,"fFinalVtxY/D");
    rootTree4->Branch("fFinalPY",&fFinalPY,"fFinalPY/D");

    rootTree4->Branch("fStartVtxZ",&fStartVtxZ,"fStartVtxZ/D");
    rootTree4->Branch("fStartPZ",&fStartPZ,"fStartPZ/D");
    rootTree4->Branch("fFinalVtxZ",&fFinalVtxZ,"fFinalVtxZ/D");
    rootTree4->Branch("fFinalPZ",&fFinalPZ,"fFinalPZ/D");

  }
}

void OpNoviceRunAction::Tally( OnetonTrackerHit* aHit)
{
  if (useTree) {
    if (debug) G4cout << "RunAction::Tally newHit" << G4endl;
    newHit = aHit;
    //rootTree1->Fill();
    fEvtNb =        newHit->GetEvtNb();
    fTrackID =      newHit->GetTrackID();
    fParentID =     newHit->GetParentID();
    fPmtNb =        newHit->GetPmtNb();
    fEop =          newHit->GetEop();
    fTop =          newHit->GetTop();
    fPosX =          newHit->GetPos().getX();
    fPosY =          newHit->GetPos().getY();
    fPosZ =          newHit->GetPos().getZ();
    fProc =         newHit->GetProc();
    fWt =           newHit->GetWeight();
    fPSType =       newHit->GetProcessSubType();
    fDirChanges =   newHit->GetDirChanges(); 
    fCosIF =        newHit->GetCosIF();
    fbProc =        newHit->GetbProc();
    fTrkLen =       newHit->GetTrkLen(); // OP path length
    fTrkOriginX =    newHit->GetTrkOrigin().getX(); // OP origin (3vector)
    fTrkOriginY =    newHit->GetTrkOrigin().getY(); // OP origin (3vector)
    fTrkOriginZ =    newHit->GetTrkOrigin().getZ(); // OP origin (3vector)
    fiProc =        newHit->GetiProc();


    rootTree3->Fill();
  }
  else  {
    if (debug) G4cout << "RunAction::Tally not using tree " << G4endl;
  }
}
void OpNoviceRunAction::TallyInfo( OnetonUserTrackInformation* tInfo)
{
  if (useTree) {
    if (debug) G4cout << "RunAction::TallyInfo" << G4endl;
    info = tInfo;
    //rootTree2->Fill();

    fDirChanges =     info->GetDirChangeCount();
    fCosIniFin =      info->GetCosIniFin();
    fBoundaryProc =   info->GetBoundaryProc();
    fLiqPathLen =     info->GetLiquidPathLength();
    fLiqELoss =       info->GetLiquidELoss();
    fFateOrigin =     info->GetFateOrigin();
    fEvtNb =          info->GetEvtNb();
    fStartVtxX =      info->GetStartVtx().getX();
    fStartPX =        info->GetStartMomentum().getX();
    fFinalVtxX =      info->GetFinalVtx().getX();
    fFinalPX =        info->GetFinalMomentum().getX();

    fStartVtxY =      info->GetStartVtx().getY();
    fStartPY =        info->GetStartMomentum().getY();
    fFinalVtxY =      info->GetFinalVtx().getY();
    fFinalPY =        info->GetFinalMomentum().getY();

    fStartVtxZ =      info->GetStartVtx().getZ();
    fStartPZ =        info->GetStartMomentum().getZ();
    fFinalVtxZ =      info->GetFinalVtx().getZ();
    fFinalPZ =        info->GetFinalMomentum().getZ();
    fPDG =            info->GetPDG();
  rootTree4->Fill();
  }
  else {
    if (debug) G4cout << "RunAction::TallyInfo not using tree " << G4endl;
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  if (useTree) {
    rootFile->Write();
    rootFile->Close();
  }
  
  /*
  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const OpNovicePrimaryGeneratorAction* generatorAction
    = static_cast<const OpNovicePrimaryGeneratorAction*>(
        G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String partName;
  if (generatorAction) 
  {
    G4ParticleDefinition* particle 
      = generatorAction->GetParticleGun()->GetParticleDefinition();
    partName = particle->GetParticleName();
  }  
  */
  //results
  //
  const OpNoviceRun* onRun = static_cast<const OpNoviceRun*>(run);
  G4int nbGoodEvents = onRun->GetNbGoodEvents();
        
  //print
  //
  if (IsMaster())
  {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------"
     << G4endl
     << "  The run was " << nofEvents << " events with " << nbGoodEvents << " good events " << G4endl;
  }
  else
  {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------"
     << G4endl
     << "  The run was " << nofEvents << G4endl;
  }      

  if (0){

    G4cout << "\n End of run info " << G4endl;

    std::map<G4int, G4double> Ahpe, Awpe, AhpeC, AwpeC ;
    // hits per event
    for (std::map<G4int, std::vector<G4double> >::const_iterator it = onRun->PMThpe.begin(); it != onRun->PMThpe.end(); ++it){
      G4cout << "PMT# " << it->first << " #hits= " ;
      G4double sum = 0.;
      for ( std::vector<G4double>::const_iterator kt = it->second.begin(); kt != it->second.end(); ++kt){
	G4cout << *kt << " " ;
	sum += *kt;
      }		
      G4cout	   << G4endl;
      Ahpe[it->first] = sum/float(nofEvents);
    }
    // weights per event
    for (std::map<G4int, std::vector<G4double> >::const_iterator it = onRun->PMTwpe.begin(); it != onRun->PMTwpe.end(); ++it){
      G4cout << "PMT# " << it->first << " wts= " ;
      G4double sum = 0.;
      for ( std::vector<G4double>::const_iterator kt = it->second.begin(); kt != it->second.end(); ++kt){
	G4cout << *kt << " " ;
	sum += *kt;
      }							 
      G4cout	   << G4endl;
      Awpe[it->first] = sum/float(nofEvents);
    }
    // Cerenkov hits per event
    for (std::map<G4int, std::vector<G4double> >::const_iterator it = onRun->PMThpeC.begin(); it != onRun->PMThpeC.end(); ++it){
      G4cout << "PMT# " << it->first << " #Cer,hits= " ;
      G4double sum = 0.;
      for ( std::vector<G4double>::const_iterator kt = it->second.begin(); kt != it->second.end(); ++kt){
	G4cout << *kt << " " ;
	sum += *kt;
      }							 
      G4cout	   << G4endl;
      AhpeC[it->first] = sum/float(nofEvents);
    }
    // Cerenkov weights per event
    for (std::map<G4int, std::vector<G4double> >::const_iterator it = onRun->PMTwpeC.begin(); it != onRun->PMTwpeC.end(); ++it){
      G4cout << "PMT# " << it->first << " Cer.wts= " ;
      G4double sum = 0.;
      for ( std::vector<G4double>::const_iterator kt = it->second.begin(); kt != it->second.end(); ++kt){
	G4cout << *kt << " " ;
	sum += *kt;
      }							 
      G4cout	   << G4endl;
      AwpeC[it->first] = sum/float(nofEvents);
    }
  
    // report averages per event
    G4cout << "\n Summary data for " << nofEvents << " events " << G4endl;
    G4cout << setw(4) << "PMT" 
	   << setw(9) << "hits/evt"
	   << setw(9) << "Wts/evt"
	   << setw(9) << "Cer/evt"
	   << setw(9) << "CerW/evt"
	   << setw(9) << "Sci/evt"
	   << setw(9) << "SciW/evt" 
	   << G4endl;
    G4int isz = 3;
    for (std::map<G4int, G4double>::const_iterator it=Ahpe.begin(); it != Ahpe.end(); ++it){
      G4cout << setw(4) << it->first 
	     << setw(9) << setprecision(isz) << it->second                  << setw(9) << setprecision(isz) << Awpe[it->first] 
	     << setw(9) << setprecision(isz) << AhpeC[it->first]            << setw(9) << setprecision(isz) << AwpeC[it->first]
	     << setw(9) << setprecision(isz) << it->second-AhpeC[it->first] << setw(9) << setprecision(isz) << Awpe[it->first] - AwpeC[it->first] 
	     << G4endl;
    }
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
