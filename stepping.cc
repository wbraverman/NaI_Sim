#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
	
	
	const G4VTouchable *touchableTest = step->GetPreStepPoint()->GetTouchable();
	
	G4int copyNoTest = touchableTest->GetCopyNumber();
	

	
	G4double edep = step->GetTotalEnergyDeposit();
	
	if(volume == fScoringVolume){
		fEventAction->AddEdep(edep);
	}
	
}
