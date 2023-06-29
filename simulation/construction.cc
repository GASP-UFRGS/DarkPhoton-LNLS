#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

	G4NistManager* manager = G4NistManager::Instance();
	G4Material* vacuum = manager->FindOrBuildMaterial("G4_Galactic");
	
	// Creating a world volume:

	G4Box *solidWorld = new G4Box("solidWorld", 10*m, 10*m, 10*m);

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	

	// Simple box for detector:

	G4Box *solidVacuum = new G4Box("solidVacuum", 2*m, 2*m, 8*m);

	G4LogicalVolume *logicVacuum = new G4LogicalVolume(solidVacuum, vacuum, "logicalVacuum");

	G4VPhysicalVolume *physVacuum = new G4PVPlacement (0, G4ThreeVector(0., 0., 2*m), logicVacuum, "physVacuum", logicWorld, false, 0, true);

	// Box for lower part of the detector:

	G4Box *solidVacuumLower = new G4Box("solidVacuumLower", 2*m, 2*m, 4*m);

	G4LogicalVolume *logicVacuumLower = new G4LogicalVolume(solidVacuumLower, vacuum, "logicalVacuumLower");

	G4VPhysicalVolume *physVacuumLower = new G4PVPlacement (0, G4ThreeVector(0., -4*m, 6*m), logicVacuumLower, "physVacuumLower", logicWorld, false, 0, true); 

	//

	G4Box *solidVacuumLower2 = new G4Box("solidVacuumLower2", 2*m, 1*m, 2*m);

	G4LogicalVolume *logicVacuumLower2 = new G4LogicalVolume(solidVacuumLower2, vacuum, "logicalVacuumLower2");

	G4VPhysicalVolume *physVacuumLower2 = new G4PVPlacement (0, G4ThreeVector(0., -3*m, 0.), logicVacuumLower2, "physVacuumLower2", logicWorld, false, 0, true); 

	/* Assembly Volumes:

	G4AssemblyVolume* assemblyDetector = new G4AssemblyVolume();

	G4RotationMatrix Ra;
	G4ThreeVector Ta;
	G4Transform3D Tr;

	G4RotationMatrix Rm;

	Ta.setX(2*m); Ta.setY(0.); Ta.setZ(0.);
	Tr = G4Transform3D(Ra, Ta);
	assemblyDetector->AddPlacedVolume(logicVacuum, Tr);

	assemblyDetector->MakeImprint(logicVacuum, Tr);

	*/

	// Detector:

	G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);

	logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

	for(G4int i = 0; i < 100; i++) {
		for(G4int j = 0; j < 100; j++){
			G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/100, -0.5*m+(j+0.5)*m/100, 9.5*m), logicDetector, "physDetector", logicWorld, false, j+i*100, true);
		}
	}

	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

	logicDetector->SetSensitiveDetector(sensDet);
}
