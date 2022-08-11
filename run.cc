#include "run.hh"

RunAction::RunAction()
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{
	G4AnalysisManager *manager = G4AnalysisManager::Instance();
	manager->OpenFile("exp.root");
	
	manager->CreateNtuple("ScintillatorHits","ScintillatorHits");
	manager->CreateNtupleIColumn("fEvent");
	manager->CreateNtupleDColumn("fX");
	manager->CreateNtupleDColumn("fY");
	manager->CreateNtupleDColumn("fZ");
	manager->FinishNtuple(0);
	
	manager->CreateNtuple("TrackPosition","TrackPosition");
	manager->CreateNtupleIColumn("fEvent");
	manager->CreateNtupleDColumn("fXTrack");
	manager->CreateNtupleDColumn("fYTrack");
	manager->CreateNtupleDColumn("fZTrack");
	manager->CreateNtupleDColumn("ParticleMomentumX");
	manager->CreateNtupleDColumn("ParticleMomentumY");
	manager->CreateNtupleDColumn("ParticleMomentumZ");
	manager->CreateNtupleDColumn("ParticleMass");
	manager->CreateNtupleDColumn("EnergyDeposit");
	manager->CreateNtupleIColumn("ParticleCharge");
	manager->CreateNtupleIColumn("TrackID");
	manager->FinishNtuple(1);
	
	
	
	manager->CreateNtuple("Scoring","Scoring");
	manager->CreateNtupleDColumn("TotalEnergyDeposit");
	manager->FinishNtuple(2);	
	
}

void RunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *manager = G4AnalysisManager::Instance();
	manager->Write();
	manager->CloseFile();
}
