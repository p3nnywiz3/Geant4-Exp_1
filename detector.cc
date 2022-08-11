#include "detector.hh"
#include "G4SystemOfUnits.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

SensitiveDetector::~SensitiveDetector()
{}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack();
	
	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();	
	
	const G4ParticleDefinition *particle = track->GetParticleDefinition(); //G4cout<< particle << G4endl;
	G4double particle_charge = particle->GetPDGCharge();
	const G4ThreeVector position = track->GetPosition();
	const G4ThreeVector momentum = track->GetMomentum();
	G4int id = track->GetTrackID();
	G4double mass = particle->GetPDGMass();
	//const G4ThreeVector momentum_dir = track->GetMomentumDirection();
	
	G4cout<< "event number : \t" << evt << G4endl;
	G4cout<<"Track position in Scintillator :" << position << G4endl;
	G4cout << "Charge :" << particle_charge << G4endl; //track->SetTrackStatus(fStopAndKill);
	G4cout << "momentum :" << momentum << G4endl;
	G4cout<< "mass: \t" << mass <<G4endl;
	G4cout<< "ID: \t" << id <<G4endl;
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	
	G4ThreeVector posMuonInitial = preStepPoint->GetPosition();
	G4ThreeVector posMuonFinal = postStepPoint->GetPosition();
	const G4VTouchable *touchable_initial = aStep->GetPreStepPoint()->GetTouchable();
	const G4VTouchable *touchable_final = aStep->GetPostStepPoint()->GetTouchable();
	
	G4double energyDeposit = aStep->GetTotalEnergyDeposit();
	
	G4VPhysicalVolume *detectorVolInitial = touchable_initial->GetVolume();
	G4ThreeVector detectorPositionInitial = detectorVolInitial->GetTranslation();
	
	G4VPhysicalVolume *detectorVolFinal = touchable_final->GetVolume();
	G4ThreeVector detectorPositionFinal = detectorVolFinal->GetTranslation();

	G4AnalysisManager *manager = G4AnalysisManager::Instance();
	
	
	manager->FillNtupleIColumn(0, 0 ,evt);
	manager->FillNtupleDColumn(0, 1,detectorPositionInitial[0]);
	manager->FillNtupleDColumn(0 ,2,detectorPositionInitial[1]);
	manager->FillNtupleDColumn(0, 3,detectorPositionInitial[2]);	
	manager->AddNtupleRow(0);
	
	manager->FillNtupleIColumn(1,0,evt);
	manager->FillNtupleDColumn(1,1,position[0]);
	manager->FillNtupleDColumn(1,2,position[1]);
	manager->FillNtupleDColumn(1,3,position[2]);
	manager->FillNtupleDColumn(1,4,momentum[0]);
	manager->FillNtupleDColumn(1,5,momentum[1]);
	manager->FillNtupleDColumn(1,6,momentum[2]);
	manager->FillNtupleDColumn(1,7,mass);
	manager->FillNtupleDColumn(1,8,energyDeposit);
	manager->FillNtupleIColumn(1,9, particle_charge);
	manager->FillNtupleIColumn(1,10,id);
	manager->AddNtupleRow(1);
	
	
	G4cout<< "Scintillator Hit fX : \t" << detectorPositionInitial[0] << "\t Scintillator Hit fY:  " << detectorPositionInitial[1] << "\t Scintillator Hit fZ:  " << detectorPositionInitial[2] << G4endl;
	
	G4cout << "\t energy deposit in each scintillator:" << energyDeposit <<  G4endl;
	
	return true;
	
}
	
	
	
	

