#include "construction.hh"

#include "BDSMDetectorConstruction.hh"

#include <cmath>

#include "G4RunManager.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Transform3D.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"
#include "G4RotationMatrix.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4RegionStore.hh"
#include "G4PVDivision.hh"

using namespace CLHEP;


MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
	// Define materials 
	DefineMaterials();

	// Define volumes
	return DefineVolumes();
}



void MyDetectorConstruction::DefineMaterials()
{

	G4double atomicMass; // atomic mass
	G4double z;  // z=mean number of protons;  
	G4double density; 
	G4int numberElements;

	G4Element* H  = new G4Element( "Hydrogen"	, "H" , z=1. , atomicMass=   1.00*g/mole );
	G4Element* B = new G4Element( "Boron"		, "B", z=5., atomicMass= 10.81*g/mole );
	G4Element* C  = new G4Element( "Carbon"		, "C" , z=6. , atomicMass=  12.01*g/mole );
	G4Element* N  = new G4Element( "Nitrogen"	, "N" , z=7. , atomicMass=  14.01*g/mole );
	G4Element* O  = new G4Element( "Oxygen"  	, "O" , z=8. , atomicMass=  16.00*g/mole );
	G4Element* F  = new G4Element( "Fluorine"	, "F" , z=9. , atomicMass=  18.998*g/mole );
	G4Element* Na = new G4Element( "Sodium"		, "Na", z=11., atomicMass=  22.99*g/mole );
	G4Element* Al = new G4Element( "Aluminium"	, "Al", z=13., atomicMass=  26.98*g/mole );
	G4Element* Si = new G4Element( "Silicon"  , "Si", z=14., atomicMass= 28.09*g/mole );
	G4Element* P = new G4Element( "Phosphorus", "P", z=15., atomicMass= 30.974*g/mole );
	G4Element* S = new G4Element( "Sulfur"		, "S", z=16., atomicMass= 32.065*g/mole );
	G4Element* Ca = new G4Element( "Calcium"  , "Ca", z=20., atomicMass= 40.08*g/mole );
	G4Element* Cr = new G4Element( "Chromium"	, "Cr", z=24., atomicMass= 51.9961*g/mole );
	G4Element* Mn = new G4Element( "Manganese", "Mn", z=25., atomicMass= 54.938*g/mole );
	G4Element* Fe = new G4Element( "Iron"			, "Fe", z=26., atomicMass= 55.85*g/mole );
	G4Element* Ni = new G4Element( "Nickel"		, "Ni", z=28., atomicMass= 58.69*g/mole );
	G4Element* Mo = new G4Element( "Molybdenum", "Mo", z=42., atomicMass= 95.54*g/mole );
	G4Element* I  = new G4Element( "Iodine"		, "I" , z=53., atomicMass= 126.9*g/mole );
	G4Element* Au = new G4Element( "Gold"		, "Au", z=79., atomicMass= 196.97*g/mole );
	G4Element* Tl = new G4Element( "Thallium"	, "Tl", z=81., atomicMass= 204.383*g/mole );

	m_Vacuum = new G4Material("GalacticVacuum", z=1., atomicMass= 1.01*g/mole, density = universe_mean_density, kStateGas, 3.e-18*pascal, 2.73*kelvin);

	m_Air = new G4Material("Air", density= 1.29*mg/cm3, numberElements=2);
	m_Air->AddElement(N, 70*perCent);
	m_Air->AddElement(O, 30*perCent);

	m_Al = new G4Material( "Aluminium", density= 2.7*g/cm3, numberElements=1 );
	m_Al->AddElement( Al, 1 );

	m_LowDensityAluminum = new G4Material( "LowDensityAluminium", density= 1.4*g/cm3, numberElements=1 );
	m_LowDensityAluminum->AddElement( Al, 1 );

	m_CarbonFiber = new G4Material( "CarbonFiber", z=6., atomicMass=12.01*g/mole, density=1.8*g/cm3 );
	m_Si = new G4Material( "Silicon", z=14., atomicMass=28.09*g/mole, density=2.33*g/cm3 );
	m_SiliconPutty = new G4Material( "SiliconPutty", density= 0.5*g/cm3, numberElements=2 );
	m_SiliconPutty->AddElement( Si, 1 );// Composition specified either by fractional mass or atom counts
	m_SiliconPutty->AddElement( O, 2 );// Composition specified either by fractional mass or atom counts

	m_Au = new G4Material( "Gold", density=19.3*g/cm3, numberElements=1 );
	m_Au->AddElement( Au, 1 );

	m_Cd = new G4Material( "Cadmium", z=48., atomicMass=112.411*g/mole, density=8.650*g/cm3 );

	m_Pb = new G4Material( "Lead", z=82., atomicMass=207.2*g/mole, density=11.34*g/cm3 );

	m_PMTGlass = new G4Material( "PMTGlass", density= 2.6*g/cm3, numberElements=2 );// Approximate density. Can do better
	m_PMTGlass->AddElement( Si, 1 );
	m_PMTGlass->AddElement( O , 2 );

	m_Delrin = new G4Material( "Delrin", density= 1.415*g/cm3, numberElements=3 );
	m_Delrin->AddElement( O, 1 );// Composition specified either by fractional mass or atom counts
	m_Delrin->AddElement( C, 1 );// Composition specified either by fractional mass or atom counts
	m_Delrin->AddElement( H, 2 );// Composition specified either by fractional mass or atom counts

	m_NaI = new G4Material( "SodiumIodide", density= 3.67*g/cm3, numberElements=2 );
	m_NaI->AddElement( Na, 1 );
	m_NaI->AddElement( I, 1 );

	const G4double percentThalium = 0.5 * perCent;
	const G4double percentNa = ( 15.34 * perCent ) * ( 1.0 - percentThalium);
	const G4double percentI = ( 84.66 * perCent ) * ( 1.0 - percentThalium);	

	m_NaITl = new G4Material( "SodiumIodideWithThallium", density= 3.67*g/cm3, numberElements=3 );
	m_NaITl->AddElement( Na, percentNa );
	m_NaITl->AddElement( I, percentI );
	m_NaITl->AddElement( Tl, percentThalium );

	m_Polystyrene = new G4Material("Polystyrene", density= 1.05*g/cm3, numberElements=2);// NOTE: Mtas has Polystyrene as C9 H10 for some reason
	m_Polystyrene->AddElement(C, 8);
	m_Polystyrene->AddElement(H, 8);

	m_PPO = new G4Material("PPO", density= 1.06*g/cm3, numberElements=3);// I think this is all that is needed
	m_PPO->AddElement(C, 8);
	m_PPO->AddElement(H, 8);
	m_PPO->AddElement(O, 1);

	m_POPOP = new G4Material("POPOP", density= 1.2*g/cm3, numberElements=4);// I think this is all that is needed
	m_POPOP->AddElement(C, 24);
	m_POPOP->AddElement(H, 16);
	m_POPOP->AddElement(O, 2);
	m_POPOP->AddElement(N, 2);
	//BDSM Fast layer is Polystyrene, PPO,and POPOP, density should be that of polystyrene since it's most of the chemical makeup, still should double check that by measuring it -TR 11/3/2020
	//Polystyrene 	->C8  H8
	//PPO (1%)	->C8  H8  O
	//POPOP	(0.015%)->C24 H16 O2  N2

	G4double PercentPPO = 1.0*perCent; 
	G4double PercentPOPOP = 0.015*perCent;
	G4double PercentStyrene = 1 - (PercentPPO + PercentPOPOP);

	m_FastLayer = new G4Material("FastLayer",density=1.05*g/cm3,3);
	m_FastLayer->AddMaterial(m_Polystyrene,PercentStyrene);
	m_FastLayer->AddMaterial(m_PPO,PercentPPO);
	m_FastLayer->AddMaterial(m_POPOP,PercentPOPOP);

	G4double PercentGold = PercentPOPOP/5.0;
	PercentStyrene = 1 - (PercentGold + PercentPPO + PercentPOPOP);
	m_FastLayerDopedWithGold = new G4Material("GoldDopedFastLayer",density=1.05*g/cm3,4);
	m_FastLayerDopedWithGold->AddMaterial(m_Polystyrene,PercentStyrene);
	m_FastLayerDopedWithGold->AddMaterial(m_PPO,PercentPPO);
	m_FastLayerDopedWithGold->AddMaterial(m_POPOP,PercentPOPOP);
	m_FastLayerDopedWithGold->AddMaterial(m_Au,PercentGold);

	m_PTFE = new G4Material( "PTFETape", density= 0.8*g/cm3, numberElements=2 );//Teflon tape with 20% density of regular Teflon. HA!
	m_PTFE->AddElement( C, 2 );
	m_PTFE->AddElement( F, 4 );

	m_PCB = new G4Material( "PCB", density= 1.8*g/cm3, numberElements = 5 );
	m_PCB->AddElement( Ca, .111 );// Composition specified either by fractional mass or atom counts
	m_PCB->AddElement( Si, .257 );// Composition specified either by fractional mass or atom counts
	m_PCB->AddElement( O, .522 );// Composition specified either by fractional mass or atom counts
	m_PCB->AddElement( Al, .079 );// Composition specified either by fractional mass or atom counts
	m_PCB->AddElement( B, .031 );// Composition specified either by fractional mass or atom counts

	// Stainless steel:	Fe, 0.05% C, 17% Cr, 6% Ni, 0.8% Mo, 1.5% Si, 1.5% Mn, 0.04% P, 0.015% S, 0.11% N
	const G4double SSCarbonFraction = 0.0005;
	const G4double SSChromiumFraction = 0.17;
	const G4double SSNickelFraction = 0.06;
	const G4double SSMolybdenumFraction = 0.008;
	const G4double SSSiliconFraction = 0.015;
	const G4double SSMangneseFraction = 0.015;
	const G4double SSPhosphorusFraction = 0.0004;
	const G4double SSSulfurFraction = 0.0015;
	const G4double SSNitrogenFraction = 0.0011;
	const G4double SSIronFraction = 1.0 - SSCarbonFraction - SSChromiumFraction - SSNickelFraction - 
		SSMolybdenumFraction - SSSiliconFraction - SSMangneseFraction - SSPhosphorusFraction - SSSulfurFraction - SSNitrogenFraction;

	m_StainlessSteel = new G4Material( "StainlessSteel", density= 8.0*g/cm3, numberElements = 10 );
	m_StainlessSteel->AddElement( C, SSCarbonFraction );// Composition specified either by fractional mass or atom counts
	m_StainlessSteel->AddElement( Cr, SSChromiumFraction );// Composition specified either by fractional mass or atom counts
	m_StainlessSteel->AddElement( Ni, SSNickelFraction );// Composition specified either by fractional mass or atom counts
	m_StainlessSteel->AddElement( Mo, SSMolybdenumFraction );// Composition specified either by fractional mass or atom counts
	m_StainlessSteel->AddElement( Si, SSSiliconFraction );// Composition specified either by fractional mass or atom counts
	m_StainlessSteel->AddElement( Mn, SSMangneseFraction );// Composition specified either by fractional mass or atom counts
	m_StainlessSteel->AddElement( P, SSPhosphorusFraction );// Composition specified either by fractional mass or atom counts
	m_StainlessSteel->AddElement( S, SSSulfurFraction );// Composition specified either by fractional mass or atom counts
	m_StainlessSteel->AddElement( N, SSNitrogenFraction );// Composition specified either by fractional mass or atom counts
	m_StainlessSteel->AddElement( Fe, SSIronFraction );// Composition specified either by fractional mass or atom counts


	// Print materials
	G4cout << *(G4Material::GetMaterialTable()) << G4endl;
	
}

void MyDetectorConstruction::InitializeDimensions(){

	m_NaIBarHalfX = 10.16*cm/2.0;
	m_NaIBarHalfY = 5.08*cm/2.0;
	m_NaIBarHalfZ = 40.64*cm/2.0;	
	
	NaIBarReflectionThickness = 0.0134*cm;
	NaIBarThermalThickness = 0.2025*cm;
	NaIBarWaterproofThickness = 0.1016*cm;
	
	CellSizeX = (57.15/2.)*mm;
	CellSizeY = (57.15/2.)*mm;
	CellSizeZ = (50.8/2.)*mm;
	
	ChamberSize = (8.89 / 2.)*cm; // need to confirm dimensions w/ Lagy
	
	G4cout << CellSizeX << G4endl;
	G4cout << CellSizeY << G4endl;
	G4cout << CellSizeZ << G4endl;

}

void MyDetectorConstruction::ConstructNaIBarDetector() {
	//Need to make more correct. Assume it's just like MTAS in terms of the layers?
	//Build detector from outside in, need to figure out thicknesses of materials that aren't NaI which are shown below and take from saint gobain
	
	//Assume that the bar is made from 4 layers, listed below from innermost to outtermost
	//Sensitive -> NaIBar (10.16cm,5.08cm,40.64cm) take from saint gobain
	//Reflective -> Teflon (0.0134cm thick, derived by assuming the silicon putty layer is the same as in MTAS)
	//Thermal -> SiliconPutty (0.2025cm thick, assumed to be the same as in MTAS since I can't find the specifics from saint gobain)
	//Waterproof -> StainlessSteel (0.1016cm thick, take from saint gobain)
	
	//m_NaIBarHalfX = 10.16*cm/2.0;
	//m_NaIBarHalfY = 5.08*cm/2.0;
	//m_NaIBarHalfZ = 40.64*cm/2.0;

	
	//Light reflection thickness
	//G4double NaIBarReflectionThickness = 0.0134*cm;//This is the teflon wrapping

	//Light reflection thickness
	//G4double NaIBarThermalThickness = 0.2025*cm;//This is the silicon putty for thermal expansion

	//Waterproof layer thickness
	//G4double NaIBarWaterproofThickness = 0.1016*cm;//This is the stainless steel jacket

	//This is the vertical offset for all the pieces
	G4double VerticalOffset = m_NaIBarHalfY + NaIBarReflectionThickness + NaIBarThermalThickness + NaIBarWaterproofThickness + ChamberSize;
	
	G4cout << "Detector Distance: " << VerticalOffset << G4endl;

	//Need to build from outside in
	auto NaIBarWaterproof = new G4Box("NaIBarWaterproof",m_NaIBarHalfX+NaIBarReflectionThickness+NaIBarThermalThickness+NaIBarWaterproofThickness
							    ,m_NaIBarHalfY+NaIBarReflectionThickness+NaIBarThermalThickness+NaIBarWaterproofThickness
							    ,m_NaIBarHalfZ+NaIBarReflectionThickness+NaIBarThermalThickness+NaIBarWaterproofThickness);
	auto NaIBarWaterproofLV = new G4LogicalVolume(NaIBarWaterproof,GetStainlessSteel(),"NaIBarWaterProofLV");
	auto simpleBoxVisAttNaIW= new G4VisAttributes(G4Colour(0.0,1.0,1.0,1.0));
	simpleBoxVisAttNaIW->SetVisibility(true);
	NaIBarWaterproofLV->SetVisAttributes(simpleBoxVisAttNaIW);
	m_NaIBarLV.push_back(NaIBarWaterproofLV);


	//Don't place the outtermost layer until the very end
	//new G4PVPlacement(0,G4ThreeVector(0,VerticalOffset,0),NaIBarWaterproofLV,"NaIBarWaterproofPV",GetWorldLogicalVolume(),false,0,fCheckOverlaps);


	auto NaIBarThermal = new G4Box("NaIBarThermal",m_NaIBarHalfX+NaIBarReflectionThickness+NaIBarThermalThickness
						      ,m_NaIBarHalfY+NaIBarReflectionThickness+NaIBarThermalThickness
						      ,m_NaIBarHalfZ+NaIBarReflectionThickness+NaIBarThermalThickness);
	auto NaIBarThermalLV = new G4LogicalVolume(NaIBarThermal,GetSiliconPutty(),"NaIBarThermalLV");
	auto simpleBoxVisAttNaIT= new G4VisAttributes(G4Colour(1.0,1.0,0.0,1.0));
	simpleBoxVisAttNaIT->SetVisibility(true);
	NaIBarThermalLV->SetVisAttributes(simpleBoxVisAttNaIT);
	m_NaIBarLV.push_back(NaIBarThermalLV);
	new G4PVPlacement(0,G4ThreeVector(0,0,0),NaIBarThermalLV,"NaIBarThermalPV",NaIBarWaterproofLV,false,0,true);

	auto NaIBarReflective = new G4Box("NaIBarReflective",m_NaIBarHalfX+NaIBarReflectionThickness
							    ,m_NaIBarHalfY+NaIBarReflectionThickness
							    ,m_NaIBarHalfZ+NaIBarReflectionThickness);
	auto NaIBarReflectiveLV = new G4LogicalVolume(NaIBarReflective,GetPTFETape(),"NaIBarReflectiveLV");
	auto simpleBoxVisAttNaIR= new G4VisAttributes(G4Colour(1.0,0.0,1.0,1.0));
	simpleBoxVisAttNaIR->SetVisibility(true);
	NaIBarReflectiveLV->SetVisAttributes(simpleBoxVisAttNaIR);
	m_NaIBarLV.push_back(NaIBarReflectiveLV);
	new G4PVPlacement(0,G4ThreeVector(0,0,0),NaIBarReflectiveLV,"NaIBarReflectivePV",NaIBarThermalLV,false,0,true);


	//NaI itself, need to displace the centroid from (0,0,0) -> (0,LeadBrickY + m_NaIBarHalfY,0)
	auto NaIBarNaI = new G4Box("NaIBar",m_NaIBarHalfX,m_NaIBarHalfY,m_NaIBarHalfZ);	//NaI Itself, no shielding/aluminum casing/waterproofing/etc..
	NaIBarNaILV = new G4LogicalVolume(NaIBarNaI,GetSodiumIodideWithThallium(),"NaIBarLV");
	auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,0.0,1.0));
	simpleBoxVisAtt->SetVisibility(true);
	NaIBarNaILV->SetVisAttributes(simpleBoxVisAtt);
	m_NaIBarLV.push_back(NaIBarNaILV);
	new G4PVPlacement(0,G4ThreeVector(0,0,0),NaIBarNaILV,"NaIBarPV",NaIBarReflectiveLV,false,0,true);
	
	fScoringVolume = NaIBarNaILV;
	

	//This will place all the layers at once  hopefully
	detector1 = new G4PVPlacement(0,G4ThreeVector(0.,VerticalOffset,0.),m_NaIBarLV.at(0),"NaIBarWaterproofPV",GetWorldLogicalVolume(),false,1,true);
	detector2 = new G4PVPlacement(0,G4ThreeVector(0.,(-1)*VerticalOffset,0.),m_NaIBarLV.at(0),"NaIBarWaterproofPV",GetWorldLogicalVolume(),false,2,true);
	//m_NumNaI++;
	
	
}

void MyDetectorConstruction::ConstructChamber(){


	G4NistManager *nist = G4NistManager::Instance();
	
	chamberMat = nist->FindOrBuildMaterial("G4_Al");
	chamberVac = nist->FindOrBuildMaterial("G4_Galactic");
	
	chamberHalfSizeX = (153.3/2.)*mm;
	chamberHalfSizeY = (79./2.)*mm;
	chamberHalfSizeZ = (174.4/2.)*mm;
	
	chamberThicknessHalfSize = (4.7/2.)*mm;
	 
	chamberInnerHalfSizeX = chamberHalfSizeX - chamberThicknessHalfSize;
	chamberInnerHalfSizeY = chamberHalfSizeY - chamberThicknessHalfSize;
	chamberInnerHalfSizeZ = chamberHalfSizeZ - chamberThicknessHalfSize;
	
	//Define Outer first
	G4Box *chamberBox = new G4Box("Chamber", chamberHalfSizeX, chamberHalfSizeY, chamberHalfSizeZ);
	chamberLogic = new G4LogicalVolume(chamberBox, chamberMat, "ChamberLV");
	new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), chamberLogic, "chamberPhys", GetWorldLogicalVolume(), false, 0, true);
	
	//Inner
	G4Box *chamberBoxInner = new G4Box("ChamberInner", chamberInnerHalfSizeX, chamberInnerHalfSizeY, chamberInnerHalfSizeZ);
	chamberInnerLogic = new G4LogicalVolume(chamberBoxInner, chamberVac, "ChamberInnerLV");
	new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), chamberInnerLogic, "chamberInnerPhys", chamberLogic, false, 0, true);

}


void MyDetectorConstruction::ConstructContainer(){
	
	G4NistManager *nist = G4NistManager::Instance();
	
	cellMat = nist->FindOrBuildMaterial("G4_Al");
	
	//outer dimensions
	G4double cellHalfSizeX = (57.15/2.)*mm;  // cell length
	G4double cellHalfSizeY = (57.15/2.)*mm; // outer dimension facing detector
	G4double cellHalfSizeZ = (50.8/2.)*mm; // cell height	
	
	
	G4Box *cellBox = new G4Box("Cell", cellHalfSizeX, cellHalfSizeY, cellHalfSizeZ);
	cellLogic = new G4LogicalVolume(cellBox, cellMat, "CellLV");
	cellPhys = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), cellLogic, "cellPhys", chamberInnerLogic , false, 0, true);
	
	
	auto cellGas = nist->FindOrBuildMaterial("G4_Ne");
	
	// inner dimensions to determine thickness (currently 0.38" thick, need to check that)
	gasHalfSizeX = ((57.15-9.652)/2.)*mm;  
	gasHalfSizeY = ((57.15-9.652)/2.)*mm; 
	gasHalfSizeZ = ((50.8-9.652)/2.)*mm;
	
	G4Box *gasVol = new G4Box("Gas", gasHalfSizeX, gasHalfSizeY, gasHalfSizeZ);
	auto *gasLogic = new G4LogicalVolume(gasVol, cellGas, "GasLV");
	//new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), gasLogic, "gasPhys", cellLogic, false, 0, true); 
	new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), gasLogic, "gasPhys", cellLogic, false, 0, true); 
	
	

}


G4VPhysicalVolume* MyDetectorConstruction::DefineVolumes() {

	InitializeDimensions();

	G4NistManager *nist = G4NistManager::Instance();
	
	G4double WorldSizeHalfX = 0.25*m;
	G4double WorldSizeHalfY = 0.25*m;
	G4double WorldSizeHalfZ = 0.25*m;
	

	G4Box* WorldBox = new G4Box("World",WorldSizeHalfX,WorldSizeHalfY,WorldSizeHalfZ);
	m_WorldLV = new G4LogicalVolume(WorldBox,m_Air,"WorldLV",0,0,0);
	m_WorldPV = new G4PVPlacement(0,G4ThreeVector(0.0,0.0,0.0),m_WorldLV,"WorldPV",0,0,0);
	


	//ConstructDetectorSystem();
	//m_WorldLV->SetVisAttributes(G4VisAttributes::GetInvisible());
	
	ConstructNaIBarDetector();
	
	ConstructChamber();
	
	ConstructContainer();

	return m_WorldPV;
}


void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	
	NaIBarNaILV->SetSensitiveDetector(sensDet);
	//NaIBarNaILV2->SetSensitiveDetector(sensDet);
}



