#include "DetectorConstruction.hh"


G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");

    G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

    nist->FindOrBuildMaterial("G4_Si");
    auto silicon = G4Material::GetMaterial("G4_Si");

    // BGO cristal (Bi4Ge3O12)
    G4Material* BGO = new G4Material("BGO", 7.12*g/cm3, 3);
    BGO->AddElement(nist->FindOrBuildElement("Bi"), 4);
    BGO->AddElement(nist->FindOrBuildElement("Ge"), 3);
    BGO->AddElement(nist->FindOrBuildElement("O"), 12);

    // Veto: plastic scintillator bars
    G4Material* plastic = nist->FindOrBuildMaterial("G4_A-150_TISSUE");

    // World volume:
    G4Box *solidWorld = new G4Box("solidWorld", 10*m, 5*m, 10*m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    // Simple box for detector:
    G4int boxWidth = 10*cm;
    G4Box *solidVacuum = new G4Box("solidVacuum", boxWidth, boxWidth, 2*m);

    // Magnetic Field:
    auto magneticSolid = new G4Box("magneticBox", boxWidth, boxWidth, 1*m);
    magneticLogical = new G4LogicalVolume(magneticSolid, vacuum, "magneticLogical");
    new G4PVPlacement(0, G4ThreeVector(0., 0., -2*m), magneticLogical, "magneticPhysical", logicWorld, false, 0, true);

    // Lower part of detector:
    G4int trapWidth = 0.2*m;
    G4int trapHeight = 1.5*m;
    G4int trapYPos = -84*cm;

    // First trapeze:
    G4Trap *solidVacuumTrap = new G4Trap("solidVacuumTrap", trapWidth, trapHeight, 1*cm, 4.2*m); //(x width, y(height), plane, base)
    G4RotationMatrix trapRot = G4RotationMatrix();
    trapRot.rotateY(90.*deg);

    // Second trapeze:
    G4Trap *solidVacuumTrap2 = new G4Trap("solidVacuumTrap2", trapWidth, trapHeight, 1*cm, 1*m);
    G4RotationMatrix trapRot2 = G4RotationMatrix();
    trapRot2.rotateY(-90.*deg);

    //Union:
    G4RotationMatrix boxRot = G4RotationMatrix();

    G4ThreeVector boxPos = G4ThreeVector(0., 0., 1*m);
    G4ThreeVector trap1Pos = G4ThreeVector(0., trapYPos, 0.9*m);
    G4ThreeVector trap2Pos = G4ThreeVector(0., trapYPos, 2.20*m);

    G4Transform3D box = G4Transform3D(boxRot, boxPos);
    G4Transform3D trap1 = G4Transform3D(trapRot, trap1Pos);
    G4Transform3D trap2 = G4Transform3D(trapRot2, trap2Pos);

    G4MultiUnion *solidTube = new G4MultiUnion("solidTube");

    solidTube->AddNode(solidVacuum, box);
    solidTube->AddNode(solidVacuumTrap, trap1);
    solidTube->AddNode(solidVacuumTrap2, trap2);

    solidTube->Voxelize();

    G4LogicalVolume *logicalTube = new G4LogicalVolume(solidTube, vacuum, "logicalTube");

    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalTube, "physicalTube", logicWorld, false, 0, true);

    // Diamond target:

    G4Material *diamond = new G4Material("diamond", 3.515*g/cm3, 1);
    diamond->AddElement(nist->FindOrBuildElement("C"), 1);

    G4Box *solidDiamondTarget = new G4Box("solidDiamondTarget", 2*cm, 2*cm, 0.0001*m);

    G4LogicalVolume *logicalDiamondTarget = new G4LogicalVolume(solidDiamondTarget, diamond, "logicalDiamondTarget");

    G4VPhysicalVolume *physDiamond = new G4PVPlacement(0, G4ThreeVector(0., 0., -3.2*m), logicalDiamondTarget, "physDiamond", logicWorld, false, 0, true);

    // Photon detector:

    G4Box *calorimeterS = new G4Box("Calorimeter", boxWidth, boxWidth, 0.01*m);

    calorimeterLV = new G4LogicalVolume(calorimeterS, BGO, "CalorimeterLV");

    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0, 0, 3.01*m), calorimeterLV, "Calorimeter", logicWorld, false, 0, true);

    // Positron detector:

    G4Box *positronDetectorS = new G4Box("PositronDetector", boxWidth, 0.5*m, 0.01*m);

    positronDetectorLV = new G4LogicalVolume(positronDetectorS, vacuum, "PositronDetectorLV");

    auto detectorRot = new G4RotationMatrix();
    detectorRot->rotateX(-33.69*deg);

    G4VPhysicalVolume *physDetector2 = new G4PVPlacement(detectorRot, G4ThreeVector(0, -1.35*m, 2.35*m), positronDetectorLV, "PositronDetector", logicWorld, false, 0, true);

    // Fake detector:

    G4Box *fakeDetectorS = new G4Box("FakeDetector", boxWidth, 0.5*m, 0.01*m);

    fakeDetectorLV = new G4LogicalVolume(fakeDetectorS, vacuum, "FakeDetectorLV");

    G4VPhysicalVolume *physFakeDetector = new G4PVPlacement(detectorRot, G4ThreeVector(0, -1.25*m, 2.21*m), fakeDetectorLV, "FakeDetector", logicWorld, false, 0, true);

    // Visualization attributes:

    auto visAttributes = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0)); // world visualization
    visAttributes->SetVisibility(false);
    logicWorld->SetVisAttributes(visAttributes);

    visAttributes = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0)); // Diamond target - cyan
    logicalDiamondTarget->SetVisAttributes(visAttributes);

    visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0)); // Box with magnet - blue
    magneticLogical->SetVisAttributes(visAttributes);

    visAttributes = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0)); // Photon detector - yellow
    calorimeterLV->SetVisAttributes(visAttributes);

    visAttributes = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // Positron detector - red
    positronDetectorLV->SetVisAttributes(visAttributes);

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    if (G4SDManager::GetSDMpointer()->FindSensitiveDetector("Detector",0)) delete G4SDManager::GetSDMpointer()->FindSensitiveDetector("Detector");
    G4SDManager* sdMan = G4SDManager::GetSDMpointer();
    MyPositronDetector* sd = new MyPositronDetector("Detector", "DetectorCollection", this);
    sdMan->AddNewDetector(sd);
    SetSensitiveDetector(fakeDetectorLV, sd);
    G4cout << "Sensitive Detector created" << G4endl;


    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

    auto caloDetector = new G4MultiFunctionalDetector("Calorimeter");
    G4SDManager::GetSDMpointer()->AddNewDetector(caloDetector);

    G4VPrimitiveScorer* primitive;
    primitive = new G4PSEnergyDeposit("Edep");
    caloDetector->RegisterPrimitive(primitive);

    primitive = new G4PSTrackLength("TrackLength");
    auto charged = new G4SDChargedFilter("chargedFilter");
    primitive->SetFilter(charged);
    caloDetector->RegisterPrimitive(primitive);

    SetSensitiveDetector("CalorimeterLV", caloDetector);

    auto posDec = new G4MultiFunctionalDetector("PositronDetector");
    G4SDManager::GetSDMpointer()->AddNewDetector(posDec);

    primitive = new G4PSEnergyDeposit("Edep");
    posDec->RegisterPrimitive(primitive);

    primitive = new G4PSTrackLength("TrackLength");
    primitive->SetFilter(charged);
    posDec->RegisterPrimitive(primitive);

    SetSensitiveDetector("PositronDetectorLV", posDec);

    // Magnetic Field
    magField = new MagneticField();
    fieldMgr = new G4FieldManager();
    fieldMgr->SetDetectorField(magField);
    fieldMgr->CreateChordFinder(magField);

    magneticLogical->SetFieldManager(fieldMgr, true);
}
