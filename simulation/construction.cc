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
    G4Box *solidWorld = new G4Box("solidWorld", 10*m, 5*m, 10*m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    // Simple box for detector:
    G4int boxWidth = 10*cm;

    G4Box *solidVacuum = new G4Box("solidVacuum", boxWidth, boxWidth, 2*m);

    G4LogicalVolume *logicVacuum = new G4LogicalVolume(solidVacuum, vacuum, "logicalVacuum");

    G4VPhysicalVolume *physVacuum = new G4PVPlacement (0, G4ThreeVector(0., 0., 1*m), logicVacuum, "physVacuum", logicWorld, false, 0, true);

    // Magnetic Field:

    auto magneticSolid = new G4Box("magneticBox", boxWidth, boxWidth, 1*m);

    magneticLogical = new G4LogicalVolume(magneticSolid, vacuum, "magneticLogical");

    new G4PVPlacement(0, G4ThreeVector(0., 0., -2*m), magneticLogical, "magneticPhysical", logicWorld, false, 0, true);

    // Lower part of detector:

    G4int trapWidth = 20*cm;
    G4int trapHeight = 1.5*m;

    G4int trapYPos = -85*cm;

    G4Trap *solidVacuumTrap = new G4Trap("solidVacuumTrap", trapWidth, trapHeight, 1*cm, 4.2*m); //(x width, y(height), plane, base)

    G4LogicalVolume *logicVacuumTrap = new G4LogicalVolume(solidVacuumTrap, vacuum, "logicalVacuumTrap");

    auto trapRot = new G4RotationMatrix();
    trapRot->rotateY(270.*deg);

    G4VPhysicalVolume *physVacuumTrap = new G4PVPlacement(trapRot, G4ThreeVector(0., trapYPos, 0.9*m), logicVacuumTrap, "physVacuumTrap", logicWorld, false, 0, true);

    // Second trapeze:

    G4Trap *solidVacuumTrap2 = new G4Trap("solidVacuumTrap2", trapWidth, trapHeight, 1*cm, 1*m);

    G4LogicalVolume *logicVacuumTrap2 = new G4LogicalVolume(solidVacuumTrap2, vacuum, "logicalVacuumTrap2");

    auto trapRot2 = new G4RotationMatrix();
    trapRot2->rotateY(90.*deg);

    G4VPhysicalVolume *physVacuumTrap2 = new G4PVPlacement(trapRot2, G4ThreeVector(0., trapYPos, 2.20*m), logicVacuumTrap2, "physVacuumTrap2", logicWorld, false, 0, true);

    // Diamond target:

    G4Material *diamond = new G4Material("diamond", 3.515*g/cm3, 1);
    diamond->AddElement(nist->FindOrBuildElement("C"), 1);

    G4Box *solidDiamondTarget = new G4Box("solidDiamondTarget", 2*cm, 2*cm, 0.0001*m);

    G4LogicalVolume *logicalDiamondTarget = new G4LogicalVolume(solidDiamondTarget, diamond, "logicalDiamondTarget");

    G4VPhysicalVolume *physDiamond = new G4PVPlacement(0, G4ThreeVector(0., 0., -3.2*m), logicalDiamondTarget, "physDiamond", logicWorld, false, 0, true);

    // Photon detector:

    G4Box *solidDetector = new G4Box("solidDetector", boxWidth, boxWidth, 0.01*m);

    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0, 0, 3.01*m), logicDetector, "physDetector", logicWorld, false, 0, true);

    // Positron detector:

    G4Box *solidDetector2 = new G4Box("solidDetector2", boxWidth, 0.5*m, 0.01*m);

    positronDetector = new G4LogicalVolume(solidDetector2, worldMat, "positronDetector");

    auto detectorRot = new G4RotationMatrix();
    detectorRot->rotateX(-33.69*deg);

    G4VPhysicalVolume *physDetector2 = new G4PVPlacement(detectorRot, G4ThreeVector(0, -1.25*m, 2.21*m), positronDetector, "physDetector2", logicWorld, false, 0, true);

    // Visualization attributes:

    auto visAttributes = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0)); // world visualization
    visAttributes->SetVisibility(false);
    logicWorld->SetVisAttributes(visAttributes);

    visAttributes = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0)); // Diamond target - cyan
    logicalDiamondTarget->SetVisAttributes(visAttributes);

    visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0)); // Box with magnet - blue
    magneticLogical->SetVisAttributes(visAttributes);

    visAttributes = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0)); // Photon detector - yellow
    logicDetector->SetVisAttributes(visAttributes);

    visAttributes = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // Positron detector - red
    positronDetector->SetVisAttributes(visAttributes);

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    MyPositronDetector *posDetector = new MyPositronDetector("PositronDetector");

    logicDetector->SetSensitiveDetector(sensDet);
    positronDetector->SetSensitiveDetector(posDetector);

    magField = new MagneticField();
    fieldMgr = new G4FieldManager();
    fieldMgr->SetDetectorField(magField);
    fieldMgr->CreateChordFinder(magField);

    magneticLogical->SetFieldManager(fieldMgr, true);
}
