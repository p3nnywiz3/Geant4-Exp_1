#include "run.hh"

RunAction::RunAction()
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{
	G4AnalysisManager *manager = G4AnalysisManager::Instance();
	manager->OpenFile("exp.root");
	
	manager->CreateNtuple("Hits","Hits");
	manager->CreateNtupleIColumn("fEvent");
	manager->CreateNtupleDColumn("fX");
	manager->CreateNtupleDColumn("fY");
	manager->CreateNtupleDColumn("fZ");
	manager->CreateNtupleDColumn("EnergyDeposit");
	manager->FinishNtuple(0);
	
	manager->CreateNtuple("Scoring","Scoring");
	manager->CreateNtupleDColumn("TotalEnergyDeposit");
	manager->FinishNtuple(1);	
	
}

void RunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *manager = G4AnalysisManager::Instance();
	manager->Write();
	manager->CloseFile();
}
