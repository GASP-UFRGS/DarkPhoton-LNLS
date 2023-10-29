#include "calodetector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack();

	track->SetTrackStatus(fStopAndKill);

	if (track->GetDefinition() == G4Gamma::Definition()) {
        G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
        G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

        G4double energy = preStepPoint->GetTotalEnergy();
        G4ThreeVector posParticle = preStepPoint->GetPosition();

        G4ThreeVector detectorPos = G4ThreeVector(0, 0, 3*m);
        G4ThreeVector newPos = posParticle - detectorPos;

        G4cout << "Photon position is: " << posParticle << G4endl;
        G4cout << "Photon energy is: " << energy << G4endl;

        G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

        auto *man = G4RootAnalysisManager::Instance();

        man->FillNtupleIColumn(0, 0, evt);
        man->FillNtupleDColumn(0, 1, energy);
        man->FillNtupleDColumn(0, 2, posParticle[0]);
        man->FillNtupleDColumn(0, 3, posParticle[1]);

        if (energy <= 100*MeV) {
            man->FillNtupleDColumn(0, 4, energy);
        }
        man->AddNtupleRow(0);
    }
}
