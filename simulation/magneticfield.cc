#include "magneticfield.hh"

#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

MagneticField::MagneticField() : G4MagneticField()
{}

MagneticField::~MagneticField()
{
    delete fMessenger;
}

void MagneticField::GetFieldValue(const G4double [4], double *Bfield) const {
    G4int num = -1;

    Bfield[0] = fBx * num;
    Bfield[1] = 0.;
    Bfield[2] = 0.;
}
