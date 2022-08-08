#include<iostream>
#include "G4RunManager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "physics.hh"
#include "construction.hh"
#include "action.hh"
#include "QGSP_BERT.hh"
#include "G4DecayPhysics.hh"


int main(int argc, char** argv)
{
	
	G4RunManager *runManager = new G4RunManager();
	
	runManager->SetUserInitialization(new DetectorConstruction());
	runManager->SetUserInitialization(new PhysicsList());
	runManager->SetUserInitialization(new ActionInitialization());
	
	G4VModularPhysicsList *physics = new QGSP_BERT();
	physics->RegisterPhysics(new G4DecayPhysics());
	runManager->SetUserInitialization(physics);
	
	runManager->Initialize();
	
	G4UIExecutive *ui = new G4UIExecutive(argc,argv);
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	UImanager->ApplyCommand("/vis/open OGL");
	UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
	UImanager->ApplyCommand("/vis/drawVolume");
	UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
	UImanager->ApplyCommand("/vis/scene/add/magneticField");
	UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
	UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate 1000");
	//UImanager->ApplyCommand("/vis/scene/add/axes");
	UImanager->ApplyCommand("/vis/scene/add/scale 50cm");
	UImanager->ApplyCommand("/vis/scene/add/eventID");
	UImanager->ApplyCommand("/gun/particle proton");
	UImanager->ApplyCommand("/vis/ogl/set/displayListLimit 5000000");
	
	ui->SessionStart();

return 0;
}
