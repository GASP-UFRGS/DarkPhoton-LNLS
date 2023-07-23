#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");

	G4NistManager* manager = G4NistManager::Instance();
	G4Material* vacuum = manager->FindOrBuildMaterial("G4_Galactic");
	
	// World volume: 

	G4Box *solidWorld = new G4Box("solidWorld", 8*m, 8*m, 8*m);

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	

	// Simple box for detector:

	G4Box *solidVacuum = new G4Box("solidVacuum", 1*m, 1*m, 4*m);

	G4LogicalVolume *logicVacuum = new G4LogicalVolume(solidVacuum, vacuum, "logicalVacuum");

	G4VPhysicalVolume *physVacuum = new G4PVPlacement (0, G4ThreeVector(0., 0., 3.98*m), logicVacuum, "physVacuum", logicWorld, false, 0, true);

	// Box for lower part of the detector:

	G4Box *solidVacuumLower = new G4Box("solidVacuumLower", 1*m, 1*m, 3*m);

	G4LogicalVolume *logicVacuumLower = new G4LogicalVolume(solidVacuumLower, vacuum, "logicalVacuumLower");

	G4VPhysicalVolume *physVacuumLower = new G4PVPlacement (0, G4ThreeVector(0., -2*m, 5*m), logicVacuumLower, "physVacuumLower", logicWorld, false, 0, true); 

	// Diamond target:

	G4Material *diamond = new G4Material("diamond", 3.515*g/cm3, 1);
	diamond->AddElement(nist->FindOrBuildElement("C"), 1);

	G4Box *solidDiamondTarget = new G4Box("solidDiamondTarget", 0.5*m, 0.5*m, 0.0001*m); //100 micrometers thick

	G4LogicalVolume *logicalDiamondTarget = new G4LogicalVolume(solidDiamondTarget, diamond, "logicalDiamondTarget");

	G4VPhysicalVolume *physDiamond = new G4PVPlacement(0, G4ThreeVector(0., 0., -0.0201*m), logicalDiamondTarget, "physDiamond", logicWorld, false, 0, true);

	// Detector:

	G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);

	logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector"); 

	for(G4int i = 0; i < 100; i++) {
		for(G4int j = 0; j < 100; j++) {
			G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/100, -0.5*m+(j+0.5)*m/100, 7.99*m), logicDetector, "physDetector", logicWorld, false, j+i*100, true);
		}
	}

	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

	logicDetector->SetSensitiveDetector(sensDet);
}
