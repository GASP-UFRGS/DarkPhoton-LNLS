#include "calodetector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();
    track->SetTrackStatus(fStopAndKill);

    G4cout << "TRACK IS: " << track->GetDefinition() << G4endl;
    G4cout << "G4GAMMA IS: " << G4Gamma::Definition() << G4endl;
    G4int PDGCode = track->GetDynamicParticle()->GetPDGcode();
    G4cout << "PDGCODE IS: " << PDGCode << G4endl;

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4double energy = preStepPoint->GetTotalEnergy();
    G4ThreeVector posParticle = preStepPoint->GetPosition();

    G4ThreeVector detectorPos = G4ThreeVector(0, 0, 3*m);
    G4ThreeVector newPos = posParticle - detectorPos;

    G4cout << "Particle position in calodetector is: " << posParticle << G4endl;
    G4cout << "Particle energy in calodetector is: " << energy << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    G4cout << "\n\n EVENT ID IS: " << evt << "\n\n" << G4endl;

    auto *man = G4RootAnalysisManager::Instance();
    man->FillNtupleIColumn(0, 0, evt);

    if (PDGCode == 22) {
        man->FillNtupleDColumn(0, 1, energy);
        man->FillNtupleDColumn(0, 2, posParticle[0]);
        man->FillNtupleDColumn(0, 3, posParticle[1]);

    } else {
        man->FillNtupleDColumn(0, 1, -999);
        man->FillNtupleDColumn(0, 2, -999);
        man->FillNtupleDColumn(0, 3, -999);
    }
    man->AddNtupleRow(0);

    man->FillNtupleIColumn(2, 0, evt);
    man->AddNtupleRow(2);
}
