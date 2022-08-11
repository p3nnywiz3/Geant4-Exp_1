#include "construction.hh"
#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4GenericMessenger.hh"
#include "field.hh"
#include "G4ChordFinder.hh"
#include "G4Mag_UsualEqRhs.hh"


G4ThreadLocal MagneticField* DetectorConstruction::fMagneticField = 0;
G4ThreadLocal G4FieldManager* DetectorConstruction::localFieldMgr = 0;

DetectorConstruction::DetectorConstruction()
{
	DefineMaterials();
	
	xWorld = 2.*m;
	yWorld = 2.*m;
	zWorld = 2.*m;
}

DetectorConstruction::~DetectorConstruction()
{
	delete fMessenger;
}


void DetectorConstruction::DefineMaterials()
{
	G4NistManager *nist = G4NistManager::Instance();
	
	scintillator = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	worldMat = nist->FindOrBuildMaterial("G4_Galactic");
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
	G4Box *solidWorld = new G4Box("World",xWorld,yWorld,zWorld);
	logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0 , true);
	
	G4Box *solidVolume = new G4Box("solidVolume",0.05*m,0.05*m,0.750*m);
	logicVolume = new G4LogicalVolume(solidVolume, worldMat, "logicVolume");
	G4VPhysicalVolume *physVolume = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.), logicVolume, "physVolume", logicWorld, false, 0 , true);
	
	Top = new G4Box("Top", 0.0005*m,0.0005*m,0.005*m);
	logicTop = new G4LogicalVolume(Top, scintillator, "logicTop");
	
	G4Box *Mid = new G4Box("Mid", 0.0005*m,0.0005*m,0.005*m);
	logicMid = new G4LogicalVolume(Mid, scintillator, "logicMid");
	
	G4Box *Bottom = new G4Box("Bottom", 0.0005*m,0.0005*m,0.005*m);
	logicBottom = new G4LogicalVolume(Bottom, scintillator, "logicBottom");
	
	MagVolume = new G4Box("MagVolume", 0.05*m, 0.05*m, 0.05*m);
	MagLogical = new G4LogicalVolume(MagVolume, worldMat, "MagLogical");
	physMag = new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 0.810*m), MagLogical, "physMag", logicWorld, false, 0, true);
	
	for(int i =0; i<100; i++)
	{
		for(int j = 0; j< 100; j++)
		{
			physTop = new G4PVPlacement(0, G4ThreeVector((0.05-0.0005 - 0.0010*j)*m , (0.05-0.0005 - 0.0010*i)*m, 0.865*m), logicTop, "physTop", logicWorld,false,j+i*100,true);
			
			G4VPhysicalVolume *physMid = new G4PVPlacement(0, G4ThreeVector((0.05-0.0005 - 0.0010*j)*m , (0.05-0.0005 - 0.0010*i)*m,  0.755*m), logicMid, "physMid", logicWorld,false,j+i*100,true);
			
			G4VPhysicalVolume *physBottom = new G4PVPlacement(0, G4ThreeVector((0.05-0.0005 - 0.0010*j)*m , (0.05-0.0005 - 0.0010*i)*m, -0.755*m), logicBottom, "physBottom", logicWorld,false,j+i*100,true);
			
		}
	}
	
	
	return physWorld;

}

void DetectorConstruction::ConstructSDandField()
{
	
	SensitiveDetector *active_top = new SensitiveDetector("TopActiveLayer");
	logicTop->SetSensitiveDetector(active_top);
	
	SensitiveDetector *active_mid = new SensitiveDetector("MidActiveLayer");
	logicMid->SetSensitiveDetector(active_mid);
	
	SensitiveDetector *active_bottom = new SensitiveDetector("BottomActiveLayer");
	logicBottom->SetSensitiveDetector(active_bottom);
	
	SensitiveDetector *active_mag = new SensitiveDetector("MagneticDetector");
	MagLogical->SetSensitiveDetector(active_mag);
	
	fMagneticField = new MagneticField();
  	localFieldMgr = new G4FieldManager();
  	localFieldMgr->SetDetectorField(fMagneticField);
  	localFieldMgr->CreateChordFinder(fMagneticField);
  	G4bool forceToAllDaughters = true;
  	MagLogical->SetFieldManager(localFieldMgr, forceToAllDaughters);
}


