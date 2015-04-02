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

#include "OpNoviceDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh" // for vacuum 
#include "OnetonTrackerSD.hh"

#include <fstream>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceDetectorConstruction::OpNoviceDetectorConstruction()
 : G4VUserDetectorConstruction()
{
  fExpHall_x = fExpHall_y = fExpHall_z = 0.5*(8.*12.*2.54*cm); // dark box
  // acrylic vessel
  fcyl_innerrad = 0*cm;
  fcyl_outerrad = 0.5*(1045.8*mm);
  fcyl_z        = 0.5*(1300.8*mm);
  fcyl_phimin   = 0.*deg;
  
  fcyl_deltaphi   = 360.*deg;
  fcyl_thickness = 25.4*mm;
  // liquid filling of acrylic vessel
  fliq_innerrad = 0*cm;
  fliq_outerrad = fcyl_outerrad - fcyl_thickness;
  fliq_z        = fcyl_z - fcyl_thickness;
  fliq_phimin   = 0.*deg;
  fliq_deltaphi   = 360.*deg;
  // teflon sheet
  fsheet_outerrad = fliq_outerrad;
  fsheet_innerrad = fliq_outerrad - 1./8.*25.4*mm;
  fsheet_z        = fliq_z;
  fsheet_phimin   = 0.*deg;
  fsheet_deltaphi   = 360.*deg;
  // PMT : dimensions of R7723 from Hamamatsu spec sheet
  fPMT_outerrad = 0.5*52.*mm;
  fPMT_z = 0.5*112.*mm;
  // increase debug output with larger positive integer values
  fdebug = 0; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceDetectorConstruction::~OpNoviceDetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceDetectorConstruction::ConstructSDandField()
{
  // Sensitive detectors

  G4String PmtSDname = "Oneton/PMT";
  OnetonTrackerSD* aPmtSD = new OnetonTrackerSD(PmtSDname,"PmtHitsCollection");

  // Setting aTrackerSD to all logical volumes with the same name 
  // of "PMTpc_log" = PMT photocathode logical volume
  SetSensitiveDetector("PMTpc_log", aPmtSD, true);

  // get PMT numbers = copy/replica numbers and store them
  // loop over volumes. daughters are physical volumes
  G4LogicalVolume* myLVolume = fexpHall_phys->GetLogicalVolume(); 
  for (G4int i=0; i < myLVolume->GetNoDaughters(); i++)  {
    if (fdebug>0) G4cout << "daughter i="<<i<< " " <<myLVolume->GetDaughter(i)->GetName() << G4endl;
    if (myLVolume->GetDaughter(i)->GetName() == "PMT"){
      G4int cn = myLVolume->GetDaughter(i)->GetCopyNo();
      if (fdebug>0) G4cout << " copy# " << cn << G4endl;
      aPmtSD->PMTnumbers.push_back(cn);
    }
  }
  G4cout << " OpNoviceDetectorConstruction::ConstructSDandField: number of PMTs is " << aPmtSD->PMTnumbers.size() << G4endl;
    

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


std::vector< std::vector < G4double > > OpNoviceDetectorConstruction::GetFileInfo(G4String filename, G4double unit1, G4double unit2 ){
  assert(filename!="NONE" && "OpNoviceDetectorConstruction::GetFileInfo No file name") ;
  std::ifstream infile(filename);
  std::vector<G4double> V1;
  std::vector<G4double> V2;
  G4double a,b;
  G4String line;
  while( getline(infile, line) ){
    if (fdebug>2) { G4cout << " line " << line << G4endl; } ;
      if (line.find("#")!=0) {
	if (fdebug>2) {G4cout << " parsed " << line.substr(0, line.find(",")) << " " << line.substr( line.find(","),20) << G4endl; };
	a = atof((line.substr(0, line.find(","))).c_str());
	b = atof((line.substr(line.find(",")+1,20)).c_str());
	V1.push_back(a*unit1);
	V2.push_back(b*unit2);
      }
  }
  infile.close();
  thedata.push_back(V1);
  thedata.push_back(V2);
  return thedata;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* OpNoviceDetectorConstruction::Construct()
{

// ------------- Materials -------------

  G4double a, z, density;
  G4int nelements;

// Air
//
  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

  G4Material* air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  air->AddElement(N, 70.*perCent);
  air->AddElement(O, 30.*perCent);


// Water
//
  G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);

  G4Material* water = new G4Material("Water", density= 1.0*g/cm3, nelements=2);
  water->AddElement(H, 2);
  water->AddElement(O, 1);

// Vacuum
//
  G4Material* Vacuum = new G4Material("Vacuum", density=universe_mean_density, nelements=1);
  Vacuum->AddElement(H, 2);

  // pyrex : taken from Daya Bay
  G4Element* Si = new G4Element("Silicon", "Si", z=14, a=28.090*g/mole);
  G4Isotope* B10= new G4Isotope("Boron10", 5, 10, 10.0*g/mole); // guess at a
  G4Isotope* B11= new G4Isotope("Boron11", 5, 11, 11.0*g/mole); // guess at a
  G4Element* B  = new G4Element("Boron", "B", 2);
  G4Element* Na = new G4Element("Sodium", "Na", z=11, a=22.99*g/mole);
  B->AddIsotope(B10, 0.20);
  B->AddIsotope(B11, 0.80);
  G4Material* PyrexSiO2 = new G4Material("PyrexSiO2", density=2.23*g/cm3, nelements=2);
  PyrexSiO2->AddElement(Si,1);
  PyrexSiO2->AddElement(O ,2);
  G4Material* PyrexNa2O = new G4Material("PyrexNa2O", density=2.23*g/cm3, nelements=2);
  PyrexNa2O->AddElement(Na,2);
  PyrexNa2O->AddElement(O ,1);
  G4Material* PyrexB2O2 = new G4Material("PyrexB2O2", density=2.23*g/cm3, nelements=2);
  PyrexB2O2->AddElement(B,2);
  PyrexB2O2->AddElement(O,2);
  G4Material* pyrex = new G4Material("Pyrex", 2.23*g/cm3, 3);
  pyrex->AddMaterial(PyrexSiO2, 0.80);
  pyrex->AddMaterial(PyrexB2O2, 0.13);
  pyrex->AddMaterial(PyrexNa2O, 0.07);

  // acrylic : taken from Daya Bay. elemental composition from wikipedia
  G4Element* C = new G4Element("Carbon","C",z=6,a=12.0*g/mole);
  G4Material* Acrylic = new G4Material("Acrylic", density=1.18*g/cm3, nelements=3);
  Acrylic->AddElement(C,5);
  Acrylic->AddElement(O,2);
  Acrylic->AddElement(H,8);

  // teflon : taken from Daya Bay. fluorine from wikipedia
  G4Element* F = new G4Element("Fluorine","F",z=9,a=18.9984*g/mole);
  G4Material* Teflon = new G4Material("Teflon",density=2.2*g/cm3, nelements=2);
  Teflon->AddElement(C,2);
  Teflon->AddElement(F,2);

  // photocathode : just use aluminum
  G4Element* Al = new G4Element("Aluminum", "Al", z=13,a=26.98*g/mole);
  G4Material* Photocathode = new G4Material("Photocathode",density=2.70*g/cm3, nelements=1);
  Photocathode->AddElement(Al,1);

//
// ------------ Generate & Add Material Properties Table ------------
//
  G4double photonEnergy[] =
            { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
              2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
              2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
              2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
              2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
              3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
              3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
              3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };

  const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);

//
// Water
//
  G4double refractiveIndex1[] =
            { 1.3435, 1.344,  1.3445, 1.345,  1.3455,
              1.346,  1.3465, 1.347,  1.3475, 1.348,
              1.3485, 1.3492, 1.35,   1.3505, 1.351,
              1.3518, 1.3522, 1.3530, 1.3535, 1.354,
              1.3545, 1.355,  1.3555, 1.356,  1.3568,
              1.3572, 1.358,  1.3585, 1.359,  1.3595,
              1.36,   1.3608};

  assert(sizeof(refractiveIndex1) == sizeof(photonEnergy));

  G4double absorption[] =
           {3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
           15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
           45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
           52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
           30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
           17.500*m, 14.500*m };

  assert(sizeof(absorption) == sizeof(photonEnergy));

  G4double scintilFast[] =
            { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00 };

  assert(sizeof(scintilFast) == sizeof(photonEnergy));

  G4double scintilSlow[] =
            { 0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00,
              7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 4.00,
              3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00,
              4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
              7.00, 6.00, 5.00, 4.00 };

  assert(sizeof(scintilSlow) == sizeof(photonEnergy));

  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();

  myMPT1->AddProperty("RINDEX",       photonEnergy, refractiveIndex1,nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("ABSLENGTH",    photonEnergy, absorption,     nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("FASTCOMPONENT",photonEnergy, scintilFast,     nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("SLOWCOMPONENT",photonEnergy, scintilSlow,     nEntries)
        ->SetSpline(true);

  myMPT1->AddConstProperty("SCINTILLATIONYIELD",100./MeV);
  myMPT1->AddConstProperty("RESOLUTIONSCALE",1.0);
  myMPT1->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
  myMPT1->AddConstProperty("SLOWTIMECONSTANT",10.*ns);
  myMPT1->AddConstProperty("YIELDRATIO",0.8);

  G4double energy_water[] = {
     1.56962*eV, 1.58974*eV, 1.61039*eV, 1.63157*eV,
     1.65333*eV, 1.67567*eV, 1.69863*eV, 1.72222*eV,
     1.74647*eV, 1.77142*eV, 1.7971 *eV, 1.82352*eV,
     1.85074*eV, 1.87878*eV, 1.90769*eV, 1.93749*eV,
     1.96825*eV, 1.99999*eV, 2.03278*eV, 2.06666*eV,
     2.10169*eV, 2.13793*eV, 2.17543*eV, 2.21428*eV,
     2.25454*eV, 2.29629*eV, 2.33962*eV, 2.38461*eV,
     2.43137*eV, 2.47999*eV, 2.53061*eV, 2.58333*eV,
     2.63829*eV, 2.69565*eV, 2.75555*eV, 2.81817*eV,
     2.88371*eV, 2.95237*eV, 3.02438*eV, 3.09999*eV,
     3.17948*eV, 3.26315*eV, 3.35134*eV, 3.44444*eV,
     3.54285*eV, 3.64705*eV, 3.75757*eV, 3.87499*eV,
     3.99999*eV, 4.13332*eV, 4.27585*eV, 4.42856*eV,
     4.59258*eV, 4.76922*eV, 4.95999*eV, 5.16665*eV,
     5.39129*eV, 5.63635*eV, 5.90475*eV, 6.19998*eV
  };

  const G4int numentries_water = sizeof(energy_water)/sizeof(G4double);

  //assume 100 times larger than the rayleigh scattering for now.
  G4double mie_water[] = {
     167024.4*m, 158726.7*m, 150742  *m,
     143062.5*m, 135680.2*m, 128587.4*m,
     121776.3*m, 115239.5*m, 108969.5*m,
     102958.8*m, 97200.35*m, 91686.86*m,
     86411.33*m, 81366.79*m, 76546.42*m,
     71943.46*m, 67551.29*m, 63363.36*m,
     59373.25*m, 55574.61*m, 51961.24*m,
     48527.00*m, 45265.87*m, 42171.94*m,
     39239.39*m, 36462.50*m, 33835.68*m,
     31353.41*m, 29010.30*m, 26801.03*m,
     24720.42*m, 22763.36*m, 20924.88*m,
     19200.07*m, 17584.16*m, 16072.45*m,
     14660.38*m, 13343.46*m, 12117.33*m,
     10977.70*m, 9920.416*m, 8941.407*m,
     8036.711*m, 7202.470*m, 6434.927*m,
     5730.429*m, 5085.425*m, 4496.467*m,
     3960.210*m, 3473.413*m, 3032.937*m,
     2635.746*m, 2278.907*m, 1959.588*m,
     1675.064*m, 1422.710*m, 1200.004*m,
     1004.528*m, 833.9666*m, 686.1063*m
  };

  assert(sizeof(mie_water) == sizeof(energy_water));

  G4bool UseMIE = false;
  if (UseMIE) {
    // gforward, gbackward, forward backward ratio
    G4double mie_water_const[3]={0.99,0.99,0.8};
    
    myMPT1->AddProperty("MIEHG",energy_water,mie_water,numentries_water)->SetSpline(true);
    myMPT1->AddConstProperty("MIEHG_FORWARD",mie_water_const[0]);
    myMPT1->AddConstProperty("MIEHG_BACKWARD",mie_water_const[1]);
    myMPT1->AddConstProperty("MIEHG_FORWARD_RATIO",mie_water_const[2]);
  }
  if (fdebug>-1) { // always print water properties
    G4cout << "Water G4MaterialPropertiesTable" << G4endl;
    myMPT1->DumpTable();
  };
  water->SetMaterialPropertiesTable(myMPT1);

  // Set the Birks Constant for the Water scintillator

  water->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

//
// Air : change from unity to 1.000273 to agree with Daya Bay
//
  G4double Eair[] = {1.55*eV, 15.5*eV};
  G4double refractiveIndex2[] = {1.000273, 1.000273};

  G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", Eair , refractiveIndex2, 2);

  if (fdebug>1) {
  G4cout << "Air G4MaterialPropertiesTable" << G4endl;
  myMPT2->DumpTable();
  };
  air->SetMaterialPropertiesTable(myMPT2);
//
// vacuum (inside a PMT)
//
  G4double Evacuum[] = {1.55*eV, 15.5*eV};
  G4double vacuum_ior[] = {1.0, 1.0};
  G4double vacuum_abslen[] = {1.e20*km, 1.e20*km};
  G4MaterialPropertiesTable* MPTvacuum = new G4MaterialPropertiesTable();
  MPTvacuum->AddProperty("RINDEX", Evacuum, vacuum_ior, 2);
  MPTvacuum->AddProperty("ABSLENGTH", Evacuum, vacuum_abslen, 2);
  Vacuum->SetMaterialPropertiesTable(MPTvacuum);
//
// Teflon : 
//
  G4double Eteflon[] = {1.55*eV, 15.5*eV};
  G4double teflon_abs[] = {0.001*mm, 0.001*mm};
  G4MaterialPropertiesTable* MPTteflon = new G4MaterialPropertiesTable();
  MPTteflon->AddProperty("ABSLENGTH",Eteflon,teflon_abs, 2);
  if (fdebug>1) {
  G4cout << "Teflon G4MaterialPropertiesTable"<<G4endl;
  MPTteflon->DumpTable();
  };
  Teflon->SetMaterialPropertiesTable(MPTteflon);

//
// Photocathode : absorb all optical photons
// "EFFICIENCY" has a special meaning for optical photons. 
// in /examples/extended/optical/LXe it appears to be efficiency for detection
//
  G4double Ephotocathode[] = {1.55*eV, 15.5*eV};

  G4OpticalSurface* photocath_opsurf = new G4OpticalSurface("photocath_opsurf", glisur,polished,dielectric_metal);// from /examples/extended/optical/LXe
  G4double photocath_eff[]={1.,1.}; // from /examples/extended/optical/LXe : "enables 'detection' of photons"
  G4double photocath_refl[]={0.,0.};
  G4MaterialPropertiesTable* MPTphotocathode = new G4MaterialPropertiesTable();

  MPTphotocathode->AddProperty("EFFICIENCY",Ephotocathode,photocath_eff, 2); // from /examples/extended/optical/LXe
  MPTphotocathode->AddProperty("REFLECTIVITY",Ephotocathode,photocath_refl, 2); // from /examples/extended/optical/LXe

  // read QE and add as property of photocathode
  thedata = GetFileInfo("../../../../ONETON/InputData/QE_R7723_sorted.txt", 1.*nm, 1.e-2); // file has wavelength in nm, QE in percent
  const G4int dsize = thedata.at(0).size();
  if (fdebug>2) { G4cout << " size of wl,qe for PMT " << dsize << G4endl; } ;
  G4double wl, qe;
  G4double Eqe[dsize], QE[dsize];
  for (G4int i=0;i<dsize;i++){
    wl = thedata.at(0).at(i);
    qe = thedata.at(1).at(i);
    Eqe[i] = 1239.84187*nm*eV/wl;
    QE[i] = qe;
    if (fdebug>2) { G4cout << " i " << i << " wl " << wl << " E(eV) " << Eqe[i]/eV << " qe " << qe << G4endl; } ;
  }
  MPTphotocathode->AddProperty("QUANTUM_EFFICIENCY",Eqe,QE,dsize);

  photocath_opsurf->SetMaterialPropertiesTable(MPTphotocathode);// from /examples/extended/optical/LXe

  if (fdebug>0) {
  G4cout << "Photocathode G4MaterialPropertiesTable"<<G4endl;
  MPTphotocathode->DumpTable();
  };
  Photocathode->SetMaterialPropertiesTable(MPTphotocathode);//redundant??

//  
// acrylic from Daya Bay
//
  G4double E_abslen_acrylic[] = { 1.55*eV, 1.61*eV, 2.07*eV, 2.48*eV, 3.76*eV, 4.13*eV, 6.20*eV, 10.33*eV,15.5*eV};
  G4double abslen_acrylic[]   = { 8.0e3*mm,8.0e3*mm,8.0e3*mm,8.0e3*mm,8.0e3*mm,8.0e3*mm,8.0e-3*mm,8.0e-3*mm,8.0e-3*mm};
  assert(sizeof(E_abslen_acrylic) == sizeof(abslen_acrylic) );
  G4double E_rayleigh_acrylic[] = { 1.55*eV, 1.7714*eV, 2.102*eV, 2.255*eV, 2.531*eV, 2.884*eV, 3.024*eV, 4.133*eV, 6.20*eV,10.33*eV, 15.5*eV};
  G4double rayleigh_acrylic[] = { 500.0*m,   300.0*m,   170.0*m,  100.0*m,  62.0*m,   42.0*m,   30.0*m,   7.6*m,    0.85*m, 0.85*m,   0.85*m};
  assert(sizeof(E_rayleigh_acrylic) == sizeof(rayleigh_acrylic) );
  G4double E_ior_acrylic[] = { 
    1.55*eV,1.79505*eV,2.10499*eV,2.27077*eV,2.55111*eV,2.84498*eV,3.06361*eV,4.13281*eV,6.20*eV,6.526*eV,6.889*eV,7.294*eV,7.75*eV,8.267*eV,8.857*eV,9.538*eV,10.33*eV,15.5*eV
  };
  G4double ior_acrylic[] = {
    1.4878, 1.4895,    1.4925,    1.4946,    1.4986,    1.5022,    1.5065,    1.5358,    1.6279, 1.6270,  1.5359,  1.5635,  1.793,  1.7199,  1.6739,  1.5635,  1.462,   1.462
  };
  assert(sizeof(E_ior_acrylic) == sizeof(ior_acrylic) );
  G4MaterialPropertiesTable* MPTacrylic = new G4MaterialPropertiesTable();
  G4int Num = sizeof(abslen_acrylic)/sizeof(G4double);
  MPTacrylic->AddProperty("ABSLENGTH",E_abslen_acrylic,abslen_acrylic, Num );
  Num = sizeof(rayleigh_acrylic)/sizeof(G4double);
  MPTacrylic->AddProperty("RAYLEIGH",E_rayleigh_acrylic,rayleigh_acrylic, Num );
  Num = sizeof(ior_acrylic)/sizeof(G4double);
  MPTacrylic->AddProperty("RINDEX",E_ior_acrylic,ior_acrylic, Num );
  if (fdebug>1) {
    G4cout << "Acrylic G4MaterialPropertiesTable" << G4endl;
    MPTacrylic->DumpTable();
  };
  Acrylic->SetMaterialPropertiesTable(MPTacrylic);
  
//
// pyrex from Daya Bay
//
  G4double energy_abslen_glass[] = {  1.55*eV, 1.61*eV, 2.07*eV, 2.48*eV, 3.56*eV, 4.13*eV, 6.20*eV, 10.33*eV, 15.5*eV };
  G4double abslen_glass[] = {  0.1e-3*mm, 0.5e3*mm, 1.0e3*mm, 2.0e3*mm, 1.0e3*mm, 1.0e3*mm, 1.0e3*mm, 1.0e3*mm, 1.0e3*mm };
  const G4int num_abslen_glass = sizeof(energy_abslen_glass)/sizeof(G4double);
  assert( sizeof(energy_abslen_glass) == sizeof(abslen_glass) );

  G4double energy_refractiveIndex_glass[] = { 1.55*eV, 2.07*eV, 4.13*eV, 6.20*eV, 10.33*eV, 15.5*eV };
  G4double refractiveIndex_glass[] =        { 1.458,   1.458,   1.458,   1.458,   1.458,    1.458   };
  const G4int num_refractiveIndex_glass = sizeof(energy_refractiveIndex_glass)/sizeof(G4double);
  assert( sizeof(energy_refractiveIndex_glass) == sizeof(refractiveIndex_glass) );

  G4MaterialPropertiesTable* glassMPT = new G4MaterialPropertiesTable();
  glassMPT->AddProperty("ABSLEN", energy_abslen_glass, abslen_glass, num_abslen_glass);
  glassMPT->AddProperty("RINDEX", energy_refractiveIndex_glass, refractiveIndex_glass, num_refractiveIndex_glass);
  pyrex->SetMaterialPropertiesTable(glassMPT);
//
// ------------- Volumes --------------

// The experimental Hall
//
  G4Box* expHall_box = new G4Box("World",fExpHall_x,fExpHall_y,fExpHall_z);

  G4LogicalVolume* expHall_log
    = new G4LogicalVolume(expHall_box,air,"World",0,0,0);

  G4VPhysicalVolume* expHall_phys
    = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);
  fexpHall_phys = expHall_phys;
// The Water Tank
//
/*
  G4Box* waterTank_box = new G4Box("Tank",fTank_x,fTank_y,fTank_z);

  G4LogicalVolume* waterTank_log
    = new G4LogicalVolume(waterTank_box,water,"Tank",0,0,0);

  G4VPhysicalVolume* waterTank_phys
    = new G4PVPlacement(0,G4ThreeVector(),waterTank_log,"Tank",
                        expHall_log,false,0);
*/
// acrylic cylinder (liquid will be placed inside)
  G4Tubs* acrylic_cyl  = new G4Tubs("acrylic_cyl", fcyl_innerrad, fcyl_outerrad, fcyl_z, fcyl_phimin, fcyl_deltaphi );
  G4LogicalVolume* cyl_log = new G4LogicalVolume(acrylic_cyl, Acrylic,"acrylcyl",0,0,0);
  G4VPhysicalVolume* cyl_phys = new G4PVPlacement(0,G4ThreeVector(),cyl_log,"acrylcyl",expHall_log,false,0);
  G4VisAttributes* cyl_att = new G4VisAttributes( G4Colour( 0.,0.,1.,0.2) ); // blue, almost transparent
  cyl_att->SetForceSolid(true);
  cyl_log->SetVisAttributes(cyl_att);

// water cylinder inside glass vial
  G4Tubs* liquid_cyl = new G4Tubs("liquid_cyl",  fliq_innerrad, fliq_outerrad, fliq_z, fliq_phimin, fliq_deltaphi );
  G4LogicalVolume* liqcyl_log = new G4LogicalVolume(liquid_cyl,water,"liqcyl",0,0,0);
  G4VPhysicalVolume* liqcyl_phys = new G4PVPlacement(0,G4ThreeVector(),liqcyl_log,"liqcyl",cyl_log,false,0);

  // FIXME : IMPLEMENTATION OF BLACK TEFLON SHEET SHOULD BE DYNAMIC
  if (0) {
  // black teflon sheet    
    G4Tubs* ptfe_tube = new G4Tubs("ptfe_tube", fsheet_innerrad, fsheet_outerrad, fsheet_z, fsheet_phimin, fsheet_deltaphi);
    G4LogicalVolume* ptfetube_log = new G4LogicalVolume(ptfe_tube,Teflon,"ptfetube", 0,0,0);
    //    G4VPhysicalVolume* ptfetube_phys = new G4PVPlacement(0,G4ThreeVector(),ptfetube_log,"ptfetube",cyl_log,false,0);
    new G4PVPlacement(0,G4ThreeVector(),ptfetube_log,"ptfetube",cyl_log,false,0);
    G4VisAttributes* ptfetube_att = new G4VisAttributes( G4Colour( 0.,1.,0.,0.2) ); // green, almost transparent
    ptfetube_att->SetForceSolid(true);
    ptfetube_log->SetVisAttributes(ptfetube_att);
    G4cout << "\n ++++++ BLACK TEFLON LINER ENABLED ++++++ \n" << G4endl;

  }
  else { G4cout << "\n ++++++ NO BLACK TEFLON LINER ++++++ \n" << G4endl; }
//
// make a 2" PMT: OD = 52mm, height = 112mm from Hamamatsu spec sheet
  G4Tubs* PMT = new G4Tubs("PMT", 0.,fPMT_outerrad, fPMT_z, 0.*deg, 360.*deg);
  G4LogicalVolume* PMT_log = new G4LogicalVolume(PMT,pyrex,"PMT", 0,0,0);

// place PMTs at the bottom of the acrylic vessel. should be in contact with vessel.
// use copy number to distinguish position (<100 = bottom)
  G4double zbottom = -fcyl_z - fPMT_z;
  new G4PVPlacement(0, G4ThreeVector(0.,0.,zbottom),                 PMT_log, "PMT", expHall_log,false,0); // center
  new G4PVPlacement(0, G4ThreeVector(fliq_outerrad/2., 0., zbottom), PMT_log, "PMT", expHall_log,false,1); // +x,0
  new G4PVPlacement(0, G4ThreeVector(-fliq_outerrad/2., 0.,zbottom), PMT_log, "PMT", expHall_log,false,2); // -x,0
  new G4PVPlacement(0, G4ThreeVector(0.,fliq_outerrad/2.,  zbottom), PMT_log, "PMT", expHall_log,false,3); // 0,+y
  new G4PVPlacement(0, G4ThreeVector(0.,-fliq_outerrad/2., zbottom), PMT_log, "PMT", expHall_log,false,4); // 0,-y

// place PMTs at top of acrylic vessel, in contact with vessel. copy numbers (100-199 = top)
  G4double ztop = fcyl_z + fPMT_z;
  G4RotationMatrix* rotD3 = new G4RotationMatrix();
  rotD3->rotateY(180.*deg);
  new G4PVPlacement(rotD3, G4ThreeVector(0.,0.,ztop),                 PMT_log, "PMT", expHall_log,false,100);
  new G4PVPlacement(rotD3, G4ThreeVector(fliq_outerrad/2., 0., ztop), PMT_log, "PMT", expHall_log,false,101);
  new G4PVPlacement(rotD3, G4ThreeVector(-fliq_outerrad/2., 0.,ztop), PMT_log, "PMT", expHall_log,false,102);
  new G4PVPlacement(rotD3, G4ThreeVector(0.,fliq_outerrad/2.,  ztop), PMT_log, "PMT", expHall_log,false,103);
  new G4PVPlacement(rotD3, G4ThreeVector(0.,-fliq_outerrad/2., ztop), PMT_log, "PMT", expHall_log,false,104);
  
  // make PMTs reddish in visualization
  G4VisAttributes* PMT_att = new G4VisAttributes( G4Colour(1.,0.,0., 0.3) ); // red, almost transparent
  PMT_att->SetForceSolid(true);
  PMT_log->SetVisAttributes(PMT_att);

  // internal vacuum in PMT
  G4Tubs* PMTvac = new G4Tubs("PMTvac",0.,fPMT_outerrad-1.*mm, fPMT_z-1.*mm, 0.*deg,360.*deg);
  G4LogicalVolume* PMTvac_log = new G4LogicalVolume(PMTvac,Vacuum,"PMTvac",0,0,0);
  //  G4VPhysicalVolume* PMTvac_phys = new G4PVPlacement(0,G4ThreeVector(),PMTvac_log,"PMTvac",PMT_log,false,0);
  new G4PVPlacement(0,G4ThreeVector(),PMTvac_log,"PMTvac",PMT_log,false,0);
  // photocathode in PMT
  G4Tubs* PMTpc  = new G4Tubs("PMTpc",0.,fPMT_outerrad-1.*mm, 0.5*2.5*mm, 0.*deg,360.*deg);
  G4LogicalVolume* PMTpc_log  = new G4LogicalVolume(PMTpc, Photocathode,"PMTpc_log",0,0,0);
  new G4LogicalSkinSurface("photocath_surf",PMTpc_log,photocath_opsurf);
  new G4PVPlacement(0,G4ThreeVector(0.,0.,fPMT_z-1.*mm-0.5*2.5*mm),PMTpc_log,"PMTpc",PMTvac_log,false,0); // was placed in PMT_log
  G4VisAttributes* PMTpc_att = new G4VisAttributes( G4Colour(1.,0.,1., 0.3) ); // magenta, partially transparent
  PMTpc_att->SetForceSolid(true);
  PMTpc_log->SetVisAttributes(PMTpc_att);
//
  G4bool useSurfaces = false;
  if (!useSurfaces) G4cout << "SUPPRESS use of surfaces " << G4endl;
  if (useSurfaces) {
// ------------- Surfaces --------------
//
// Water Tank
//
    G4OpticalSurface* opWaterSurface = new G4OpticalSurface("WaterSurface");
    opWaterSurface->SetType(dielectric_dielectric);
    opWaterSurface->SetFinish(ground);
    opWaterSurface->SetModel(unified);

    new G4LogicalBorderSurface("WaterSurface",
			       cyl_phys,liqcyl_phys,opWaterSurface);

// Air Bubble
//

    G4OpticalSurface* opAirSurface = new G4OpticalSurface("AirSurface");
    opAirSurface->SetType(dielectric_dielectric);
    opAirSurface->SetFinish(polished);
    opAirSurface->SetModel(glisur);
/*
  G4LogicalSkinSurface* airSurface =
          new G4LogicalSkinSurface("AirSurface", bubbleAir_log, opAirSurface);

  G4OpticalSurface* opticalSurface = dynamic_cast <G4OpticalSurface*>
        (airSurface->GetSurface(bubbleAir_log)->GetSurfaceProperty());

  if (opticalSurface) opticalSurface->DumpInfo();
*/
//
// Generate & Add Material Properties Table attached to the optical surfaces
//
    const G4int num = 2;
    G4double ephoton[num] = {2.034*eV, 4.136*eV};
    
  //OpticalWaterSurface
    G4double refractiveIndex[num] = {1.35, 1.40};
    G4double specularLobe[num]    = {0.3, 0.3};
    G4double specularSpike[num]   = {0.2, 0.2};
    G4double backScatter[num]     = {0.2, 0.2};
    
    G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();

    myST1->AddProperty("RINDEX",                ephoton, refractiveIndex, num);
    myST1->AddProperty("SPECULARLOBECONSTANT",  ephoton, specularLobe,    num);
    myST1->AddProperty("SPECULARSPIKECONSTANT", ephoton, specularSpike,   num);
    myST1->AddProperty("BACKSCATTERCONSTANT",   ephoton, backScatter,     num);

    G4cout << "Water Surface G4MaterialPropertiesTable" << G4endl;
    myST1->DumpTable();

    opWaterSurface->SetMaterialPropertiesTable(myST1);

  //OpticalAirSurface
    G4double reflectivity[num] = {0.3, 0.5};
    G4double efficiency[num]   = {0.8, 1.0};
    
    G4MaterialPropertiesTable *myST2 = new G4MaterialPropertiesTable();

    myST2->AddProperty("REFLECTIVITY", ephoton, reflectivity, num);
    myST2->AddProperty("EFFICIENCY",   ephoton, efficiency,   num);
    
    G4cout << "Air Surface G4MaterialPropertiesTable" << G4endl;
    myST2->DumpTable();

    opAirSurface->SetMaterialPropertiesTable(myST2);
  }

//always return the physical World
  return expHall_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
