#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "globals.hh"
#include "G4GenericMessenger.hh"
#include "field.hh"
#include "detector.hh"

class G4GenericMessenger;
class MagneticField;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	~DetectorConstruction() override;
	
	G4VPhysicalVolume *Construct();
	void ConstructSDandField();
private:
	
	G4Box *MagVolume ,*Top;
	G4LogicalVolume *logicTop,*logicMid, *logicBottom, *logicWorld, *logicVolume;
	G4VPhysicalVolume *physMag, *physTop;
	G4Material *worldMat, *scintillator;
	  
	void DefineMaterials();
	void DefineCommands();
	G4GenericMessenger* fMessenger;

	static G4ThreadLocal MagneticField* fMagneticField;
	static G4ThreadLocal G4FieldManager* localFieldMgr;
    
   	G4LogicalVolume *MagLogical = nullptr;
    	
    	G4double xWorld, yWorld, zWorld;
    	
    	G4bool isAtmosphere;
    	
};

#endif
