#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->OpenFile("output.root");
	
	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fT");
	man->FinishNtuple(0);
	
	man->CreateNtuple("NaI", "NaI");
	man->CreateNtupleDColumn("CoincEvtNum");
	man->CreateNtupleDColumn("fEdep1");
	man->FinishNtuple(1);

}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write(); 
	man->CloseFile();
}

