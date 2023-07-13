#include "detector.hh"

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

		G4cout << "Particle position: " << posParticle << G4endl;
		G4cout << "Particle energy is: " << energy << G4endl;
	}	
}
