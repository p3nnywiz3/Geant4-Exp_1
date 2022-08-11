#include "event.hh"
#include "G4RunManager.hh"
#include "stepping.hh"

EventAction::EventAction(RunAction*)
{
	fEdep = 0.;
	//energyDeposit = 0.;
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
	fEdep = 0.;
	//energyDeposit = 0.;
	
}

void EventAction::EndOfEventAction(const G4Event*)
{
	G4cout<<"Energy deposition in whole event :    " << fEdep << G4endl;
	
	G4AnalysisManager *manager = G4AnalysisManager::Instance();

	//G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	//manager->FillNtupleIColumn(2,0,evt);
	//manager->FillNtupleDColumn(2,1,energyDeposit);
	//manager->AddNtupleRow(2);
	
	manager->FillNtupleDColumn(2, 0 , fEdep*MeV);
	manager->AddNtupleRow(2);
}
