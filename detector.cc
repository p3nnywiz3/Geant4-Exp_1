#include "detector.hh"
#include "G4SystemOfUnits.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

SensitiveDetector::~SensitiveDetector()
{}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack();
	//track->SetTrackStatus(fStopAndKill);
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	
	G4ThreeVector posMuonInitial = preStepPoint->GetPosition();
	G4ThreeVector posMuonFinal = postStepPoint->GetPosition();
	const G4VTouchable *touchable_initial = aStep->GetPreStepPoint()->GetTouchable();
	const G4VTouchable *touchable_final = aStep->GetPostStepPoint()->GetTouchable();
	
	G4double energyDeposit = aStep->GetTotalEnergyDeposit();
	//G4int detectorNumberInitial, detectorNumberFinal;
	
	//detectorNumberInitial = touchable_initial->GetCopyNumber();
	//detectorNumberFinal = touchable_final->GetCopyNumber();
	
	G4VPhysicalVolume *detectorVolInitial = touchable_initial->GetVolume();
	G4ThreeVector detectorPositionInitial = detectorVolInitial->GetTranslation();
	
	G4VPhysicalVolume *detectorVolFinal = touchable_final->GetVolume();
	G4ThreeVector detectorPositionFinal = detectorVolFinal->GetTranslation();
	
	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	G4AnalysisManager *manager = G4AnalysisManager::Instance();
	
	
	manager->FillNtupleIColumn(0, 0 ,evt);
	manager->FillNtupleDColumn(0, 1,detectorPositionInitial[0]);
	manager->FillNtupleDColumn(0 ,2,detectorPositionInitial[1]);
	manager->FillNtupleDColumn(0, 3,detectorPositionInitial[2]);
	manager->FillNtupleDColumn(0,4,energyDeposit);	
	manager->AddNtupleRow(0);
	
	G4cout<< "initial : \t" << detectorPositionInitial[0] << "\t" << detectorPositionInitial[1] << "\t" << detectorPositionInitial[2] << G4endl;
	
	return true;
	
}
	
	
	
	

