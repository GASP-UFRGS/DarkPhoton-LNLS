#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4AssemblyVolume.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"
#include "G4MultiUnion.hh"
#include "G4Transform3D.hh"

#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Region.hh"

#include "calodetector.hh"
#include "positrondetector.hh"
#include "magneticfield.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();

	virtual G4VPhysicalVolume *Construct();

private:
    G4LogicalVolume *logicDetector;
    G4LogicalVolume *positronDetector;

    G4MagneticField *magField;
    G4FieldManager *fieldMgr;
    G4LogicalVolume *magneticLogical;

    G4LogicalVolume *logicWorld;

	virtual void ConstructSDandField();
};

#endif
