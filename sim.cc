#include <iostream>
#include <G4RunManager.hh>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "BDSMDetectorConstruction.hh"
#include "construction.hh"
#include "physics.hh" 
#include "action.hh"


int main(int argc, char** argv){
	
	#ifdef G4MULTITHREADED
		G4MTRunManager *runManager = new G4MTRunManager();
	#else 
		G4RunManager *runManager = new G4RunManager();
	#endif

	runManager->SetUserInitialization(new MyDetectorConstruction());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyActionInitialization());
	
	//runManager->Initialize();	
	
	G4UIExecutive *ui = 0;
	
	if(argc==1){ //activates if no other arguments than ./sim
		runManager->Initialize();
		ui = new G4UIExecutive(argc, argv);
	} 
	// Using this if statement allows showing of the geometry if no other command (like a macro file) is called

	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	if(ui){	
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
	}
	else{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}

	return 0;
}
