#ifndef MAGNETICFIELD_HH
#define MAGNETICFIELD_HH

#include "globals.hh"
#include "G4MagneticField.hh"
#include "G4GenericMessenger.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include <CLHEP/Units/SystemOfUnits.h>

class MagneticField : public G4MagneticField {
    public:
        MagneticField();
        ~MagneticField() override;

    void GetFieldValue(const G4double Point[4], G4double *Bfield) const override;

    void SetField(G4double val) {
        fBx = val;
    }
    G4double GetField() const {
        return fBx;
    }
    private:
        void DefineCommands();

        G4GenericMessenger *fMessenger = nullptr;
        G4double fBx = 0.5*CLHEP::tesla;
};
#endif
