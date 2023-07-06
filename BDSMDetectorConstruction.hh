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
/// \file BDSMDetectorConstruction.hh
/// \brief Definition of the BDSMDetectorConstruction class

#ifndef BDSMDetectorConstruction_h
#define BDSMDetectorConstruction_h 1

#include <vector>
#include <utility>

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4Cache.hh"
#include "globals.hh"
//#include "BDSMScintSD.hh"
//#include "BDSMPlasticSD.hh"


class G4VPhysicalVolume;
class G4Material;

class BDSMDetectorConstruction : public G4VUserDetectorConstruction {
	public:
		BDSMDetectorConstruction();
		BDSMDetectorConstruction(G4String);
		virtual ~BDSMDetectorConstruction();
		virtual G4VPhysicalVolume* Construct();

		// get methods
		//
		G4String GetModelType() const { return m_ModelType; }
		//void SetModelType(G4String val) { val.toUpper(); m_ModelType = val; }
		//inline const G4VPhysicalVolume* GetNaIPV() const { return m_NaIBarPV;}  //m_Detectors.at(0).second; }
		//inline const G4VPhysicalVolume* GetBDSMPV() const { return m_BDSMFastLayerPV; } //m_Detectors.at(1).second; }
		G4LogicalVolume* GetWorldLogicalVolume() { return m_WorldLV; }
		G4VPhysicalVolume* GetWorldPhysicalVolume() { return m_WorldPV; }

		G4Material* GetLead() const { return m_Pb; }
		G4Material* GetSodiumIodideWithThallium() const { return m_NaITl; }
		G4Material* GetSodiumIodide() const { return m_NaI; }
		G4Material* GetPolystyrene() const { return m_Polystyrene; }
		G4Material* GetPPO() const { return m_PPO; }
		G4Material* GetPOPOP() const { return m_POPOP; }
		G4Material* GetAir() const { return m_Air; }
		G4Material* GetAluminum() const { return m_Al; }
		G4Material* GetLowDensityAluminum() const { return m_LowDensityAluminum; }
		G4Material* GetGold() const { return m_Au; }
		G4Material* GetVacuum() const { return m_Vacuum; }
		G4Material* GetPTFETape() const { return m_PTFE; }
		G4Material* GetBDSMFastLayer() const { return m_FastLayer; }
		G4Material* GetBDSMFastLayerDopedWithGold() const { return m_FastLayerDopedWithGold; }
		G4Material* GetPMTGlass() const { return m_PMTGlass; }
		G4Material* GetCarbonFiber() const { return m_CarbonFiber; }
		G4Material* GetCadmium() const { return m_Cd; }
		G4Material* GetSilicon() const { return m_Si; }
		G4Material* GetStainlessSteel() const { return m_StainlessSteel; }
		G4Material* GetSiliconPutty() const { return m_SiliconPutty; }
		G4Material* GetDelrin() const { return m_Delrin; }
		G4Material* GetPCB() const { return m_PCB; }

		G4int GetNumNaIDetectors() const { return m_NumNaI; }
		G4int GetNumPlasticDetectors() const { return m_NumPlastic; }

		G4LogicalVolume* GetNaIVolume(G4int ii) { return m_NaIBarLV.at(ii); }

		static BDSMDetectorConstruction* GetInstance();

	private:
		// methods
		//
		void DefineMaterials();
		G4VPhysicalVolume* DefineVolumes();
		void ConstructDetectorSystem();
		void ConstructLeadShielding();
		void ConstructNaIBarDetector();
		void ConstructPrototypeBDSM();
		void ConstructPrototypeFastOnlyBDSM();
		void ConstructPrototypeSolidBDSM();
		void ConstructAluminumRailing();
		void ConstructPMT();
		void ConstructSource();
		void ConstructSDandField();
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

		G4LogicalVolume* m_BDSMFastLayerLV; //BSM Log
		G4int m_NumPlastic;
		//G4LogicalVolume* m_BDSMSlowLayerLV; //BSM slow layer logical volume
		//G4VPhysicalVolume* m_BDSMFastLayerPV; //BSM Phys Don't need to store the physical volume

		G4double m_FoilHalfX;
		G4double m_FoilHalfY;
		G4double m_FoilHalfZ;

		G4double m_TargetBackingHalfX;
		G4double m_TargetBackingHalfY;
		G4double m_TargetBackingHalfZ;
	
		G4double m_PTFEThickness; 
		G4double m_FastInnerRadius; 
		G4double m_FastOutterRadius;
		G4double m_FastHalfLength;
		
		G4double m_NaIBarHalfX;
		G4double m_NaIBarHalfY;
		G4double m_NaIBarHalfZ;
	
		G4double m_AluminumPlateHalfX;//NaI sits on top of 3"x3" Al plate
		G4double m_AluminumPlateHalfY;//NaI sits on top of 3"x3" Al plate
		G4double m_AluminumPlateHalfZ;//NaI sits on top of 3"x3" Al plate
	
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

		//G4Cache<BDSMPlasticSD*> m_BDSMFastLayer; //Sensitive detectors
		//G4Cache<BDSMScintSD*> m_NaIBar; //Sensitive detectors

		G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
		static BDSMDetectorConstruction* instance;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

