#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
	fEdep = 0.;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
	fEdep = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event* event)
{
	
	G4double elecEnergy = 0.511;
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	G4int EventNum = event->GetEventID();
	//G4cout << EventNum << G4endl;
	
	//G4cout << "Energy Deposition: " << fEdep << G4endl;
	
	if(fEdep > 0.){
		man->FillNtupleDColumn(1, 1, fEdep);
		man->AddNtupleRow(1); 
	}

	
	

		
}
