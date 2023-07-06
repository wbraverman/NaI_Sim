#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{} 

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{

	G4Track *track = aStep->GetTrack();
	
	//track->SetTrackStatus(fStopAndKill); // stops particle as soon as it enters detector
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); 
	// is not this simple for charged particles, this is only good for photons
	
	G4ThreeVector posParticle = preStepPoint->GetPosition(); // get position of particle when it enters the detector (probably unecessary for our application)
	G4double time = preStepPoint->GetGlobalTime();
	
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	
	G4int copyNo = touchable->GetCopyNumber();
	
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	
	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->FillNtupleIColumn(0, 0, evt);
	man->FillNtupleDColumn(0, 1, time);
	
	man->AddNtupleRow(0);
	
return true;
}
