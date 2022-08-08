#ifndef FIELD_HH
#define FIELD_HH

#include "globals.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4MagneticField.hh"
#include "G4TransportationManager.hh"
#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include <CLHEP/Units/SystemOfUnits.h>


class G4GenericMessenger;

class MagneticField : public G4MagneticField
{
  public:
    MagneticField();
    ~MagneticField() override;

    void GetFieldValue(const G4double point[4],double* bField ) const override;

    void SetField(G4double val) { fBy = val; }
    G4double GetField() const { return fBy; }

  private:
    void DefineCommands();

    G4GenericMessenger* fMessenger = nullptr;
    G4double fBy = -0.5*CLHEP::tesla;
};

#endif
