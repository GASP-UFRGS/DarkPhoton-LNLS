#include "positrondetector.hh"

MyPositronDetector::MyPositronDetector(G4String name) : G4VSensitiveDetector(name)
{}

MyPositronDetector::~MyPositronDetector()
{}

G4bool MyPositronDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4double positronEnergy = preStepPoint->GetTotalEnergy();
    G4ThreeVector posParticle = preStepPoint->GetPosition();

    G4cout << "Positron position is: " << posParticle << G4endl;
    G4cout << "Positron energy is: " << positronEnergy << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    auto *man = G4RootAnalysisManager::Instance();
    //man->FillNtupleIColumn(5, evt);
    man->FillNtupleDColumn(5, positronEnergy);
    man->FillNtupleDColumn(6, posParticle[0]);
    man->FillNtupleDColumn(7, posParticle[1]);
    man->FillNtupleDColumn(8, posParticle[2]);
    man->AddNtupleRow(0);

}
