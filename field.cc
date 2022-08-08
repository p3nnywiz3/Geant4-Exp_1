#include "field.hh"
#include "G4GenericMessenger.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4UniformMagField.hh"
#include "G4MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

MagneticField::MagneticField()
{
  
  DefineCommands();
}



MagneticField::~MagneticField()
{
  delete fMessenger;
}

void MagneticField::GetFieldValue(const G4double [4],double *bField) const
{
  bField[0] = fBy;
  bField[1] = 0.;
  bField[2] = 0.;
}


void MagneticField::DefineCommands()
{
  
  fMessenger = new G4GenericMessenger(this,
                                      "/exp/field/",
                                      "Field control");

  // fieldValue command
  auto& valueCmd
    = fMessenger->DeclareMethodWithUnit("value","tesla",
                                &MagneticField::SetField,
                                "Set field strength.");
  valueCmd.SetParameterName("field", true);
  valueCmd.SetDefaultValue("-0.5");
}
