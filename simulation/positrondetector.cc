#include "positrondetector.hh"

MyPositronDetector::MyPositronDetector(G4String name) : G4VSensitiveDetector(name)
{}

MyPositronDetector::~MyPositronDetector()
{}

void MyPositronDetector::RegisterPrimitive(G4VPrimitiveScorer *scorer)
{}

G4bool MyPositronDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();
    track->SetTrackStatus(fStopAndKill);

    G4int PDGCode = track->GetDynamicParticle()->GetPDGcode();

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4double positronEnergy = preStepPoint->GetTotalEnergy();
    G4ThreeVector posParticle = preStepPoint->GetPosition();

    G4ThreeVector detectorPos = G4ThreeVector(0, -1.25*m, 2.21*m);
    G4ThreeVector newPos = posParticle - detectorPos;

    G4cout << "Particle position in positrondetector is: " << newPos << G4endl;
    G4cout << "Particle energy in positrondetector is: " << positronEnergy << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    //G4cout << "\n\n EVENT ID IS: " << evt << G4endl;

    auto *man = G4RootAnalysisManager::Instance();
    //man->FillNtupleIColumn(1, 0, evt);

    if (track->GetDefinition() == G4Positron::Definition()) {

        man->FillNtupleDColumn(1, 1, positronEnergy);
        man->FillNtupleDColumn(1, 2, newPos[0]);
        man->FillNtupleDColumn(1, 3, newPos[1]);

    }
    man->AddNtupleRow(1);

    man->FillNtupleIColumn(2, 1, evt);
    man->AddNtupleRow(2);
}
