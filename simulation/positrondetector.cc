#include "positrondetector.hh"

MyPositronDetector::MyPositronDetector(G4String name) : G4VSensitiveDetector(name)
{}

MyPositronDetector::~MyPositronDetector()
{}

G4bool MyPositronDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill);

    if (track->GetDefinition() == G4Positron::Definition()) {

        G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
        G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

        G4double positronEnergy = preStepPoint->GetTotalEnergy();
        G4ThreeVector posParticle = preStepPoint->GetPosition();

        G4ThreeVector detectorPos = G4ThreeVector(0, -1.25*m, 2.21*m);
        G4ThreeVector newPos = posParticle - detectorPos;

        G4cout << "Positron position is: " << newPos << G4endl;
        G4cout << "Positron energy is: " << positronEnergy << G4endl;

        G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

        auto *man = G4RootAnalysisManager::Instance();
        man->FillNtupleIColumn(1, 0, evt);
        man->FillNtupleDColumn(1, 1, positronEnergy);
        man->FillNtupleDColumn(1, 2, newPos[0]);
        man->FillNtupleDColumn(1, 3, newPos[1]);

        man->AddNtupleRow(1);
    }
}
