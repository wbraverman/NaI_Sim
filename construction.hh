#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }
	//G4LogicalVolume *GetScoringVolume2() const { return fScoringVolume2; }
	
	//G4double GetGasCellSizeX() const { return gasHalfSizeX; }
	//G4double GetGasCellSizeY() const { return gasHalfSizeY; }
	//G4double GetGasCellSizeZ() const { return gasHalfSizeZ; }
	
	virtual G4VPhysicalVolume *Construct();
private:
	G4Box *solidScintillator1, *solidScintillator2, *solidWorld, *cellSolid, *solidCellWall1, *solidCellWall2, *solidCellWall3;
	
	G4LogicalVolume *logicDetector, *logicScintillator1, *logicScintillator2, *logicWorld, *cellLogic, *logicCellWall1, *logicCellWall2, *logicCellWall3, *NaIBarNaILV, *NaIBarNaILV2,
	*fScoringVolume, *fScoringVolume2, *chamberInnerLogic, *chamberLogic;
	
	G4VPhysicalVolume *physWorld , *physScintillator1, *physScintillator2, *cellPhys, *physWall1, *physWall2, *physWall3,
	*physWall4, *physWall5, *physWall6, *detector1, *detector2;
	
	G4Material *worldMat, *NaI, *cellMat, *wallMat, *Ne, *chamberMat, *chamberVac;
	
	G4LogicalVolume* GetWorldLogicalVolume() { return m_WorldLV; }
	G4Material* GetStainlessSteel() const { return m_StainlessSteel; }
	G4Material* GetSiliconPutty() const { return m_SiliconPutty; }
	G4Material* GetPTFETape() const { return m_PTFE; }
	G4Material* GetSodiumIodideWithThallium() const { return m_NaITl; }
	


	//G4Element *Na, *I;
	
	G4VPhysicalVolume* DefineVolumes();
	void ConstructDetectorSystem();
	void ConstructLeadShielding();
	void ConstructPrototypeBDSM();
	void ConstructPrototypeFastOnlyBDSM();
	void ConstructPrototypeSolidBDSM();
	void ConstructAluminumRailing();
	void ConstructPMT();
	void ConstructSource();
	void InitializeDimensions();

	// data members
	//

	// materials
	G4Material* m_Vacuum;
	G4Material* m_PTFE;
	G4Material* m_Pb;
	G4Material* m_NaITl;
	G4Material* m_NaI;
	G4Material* m_Polystyrene;
	G4Material* m_PPO;
	G4Material* m_POPOP;
	G4Material* m_Air;
	G4Material* m_Al;
	G4Material* m_Au;
	G4Material* m_FastLayer;
	G4Material* m_FastLayerDopedWithGold;
	G4Material* m_LowDensityAluminum;
	G4Material* m_PMTGlass; 
	G4Material* m_CarbonFiber; 
	G4Material* m_Cd; 
	G4Material* m_Si; 
	G4Material* m_SiliconPutty; 
	G4Material* m_Delrin; 
	G4Material* m_PCB; 
	G4Material* m_StainlessSteel; 

	G4String m_ModelType; //Model type either LSU or MTAS
	G4LogicalVolume* m_WorldLV; //World Logical Volume
	G4VPhysicalVolume* m_WorldPV; //World Physical Volume

	//G4LogicalVolume* m_NaIBarLV; //NaI Log
	std::vector<G4LogicalVolume*> m_NaIBarLV; //NaI Log
	G4int m_NumNaI;
	//std::vector<G4VPhysicalVolume*> m_NaIBarPV; //NaI Phys Don't need to store the physical volume
	
	std::vector<G4LogicalVolume*> m_NaIBarLV2;

	G4LogicalVolume* m_BDSMFastLayerLV; //BSM Log
	G4int m_NumPlastic;
	//G4LogicalVolume* m_BDSMSlowLayerLV; //BSM slow layer logical volume
	//G4VPhysicalVolume* m_BDSMFastLayerPV; //BSM Phys Don't need to store the physical volume

	G4double m_FoilHalfX;
	G4double m_FoilHalfY;
	G4double m_FoilHalfZ;
	
	G4double gasHalfSizeX;
	G4double gasHalfSizeY;
	G4double gasHalfSizeZ;

	G4double m_TargetBackingHalfX;
	G4double m_TargetBackingHalfY;
	G4double m_TargetBackingHalfZ;
	
	G4double m_PTFEThickness; 
	G4double m_FastInnerRadius; 
	G4double m_FastOutterRadius;
	G4double m_FastHalfLength;
	
	G4double NaIBarReflectionThickness;
	G4double NaIBarThermalThickness;
	G4double NaIBarWaterproofThickness;
		
	G4double m_NaIBarHalfX;
	G4double m_NaIBarHalfY;
	G4double m_NaIBarHalfZ;
	
	G4double CellSizeX;
	G4double CellSizeY;
	G4double CellSizeZ;
	
	G4double ChamberSize;
	
	//G4double m_AluminumPlateHalfX;//NaI sits on top of 3"x3" Al plate
	//G4double m_AluminumPlateHalfY;//NaI sits on top of 3"x3" Al plate
	//G4double m_AluminumPlateHalfZ;//NaI sits on top of 3"x3" Al plate
	
	G4double m_RailHalfX;
	G4double m_RailHalfY;
	G4double m_RailHalfZ;

	G4double m_PMTHalfLength;
	G4double m_PMTRadius;
	G4double m_PMTGlassThickness;
	
	G4double m_LeadBrickXGap;	//Gap between closest brick faces
	G4double m_LeadBrickHalfX;	//Width of lead brick
	G4double m_LeadBrickHalfY;	//Height of lead brick
	G4double m_LeadBrickHalfZ;	//Length of lead brick
	
	G4double chamberHalfSizeX;
	G4double chamberHalfSizeY;
	G4double chamberHalfSizeZ;
	G4double chamberThicknessHalfSize;
	G4double chamberInnerHalfSizeX;
	G4double chamberInnerHalfSizeY;
	G4double chamberInnerHalfSizeZ;

	virtual void ConstructSDandField();
	
	void ConstructContainer();
	
	void ConstructNaIBarDetector();
	
	void ConstructNaIBarDetector2();
	
	void ConstructScintillator();
	
	void DefineMaterials(); 	
	
	void ConstructChamber();
	
	G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
	
};
#endif
