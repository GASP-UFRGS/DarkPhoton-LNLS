#include "positrondetector.hh"

MyPositronDetector::MyPositronDetector(const G4String& name, const G4String& hitsCollectionName, MyDetectorConstruction* _det)
: G4VSensitiveDetector(name), hitsCollection(0), hcid(-1), det(_det) {
    collectionName.insert(hitsCollectionName);
    G4cout << "Creating Sensitive Detector named: " << name << G4endl;
}

MyPositronDetector::~MyPositronDetector() {}

void MyPositronDetector::Initialize(G4HCofThisEvent* hce) {
    // Create hits collection
    hitsCollection = new HitsCollection(SensitiveDetectorName, collectionName[0]);

    // Get hitsCollection id from the SDManager
    if (hcid<0) hcid = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);

    // add hitsCollection to the hc of this event
    hce->AddHitsCollection(hcid, hitsCollection);

    eventID = -1;
}

G4bool MyPositronDetector::ProcessHits(G4Step *step, G4TouchableHistory *ROhist) {
    G4double energyDep = step->GetTotalEnergyDeposit();
    const G4ParticleDefinition* particle = step->GetTrack()->GetParticleDefinition();
    G4int trackID = step->GetTrack()->GetTrackID();
    G4int eventNumber = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    Hits* hit = new Hits();

    // Energy deposit by primary particle in sensitive volume:
    G4cout << "\nThe energy deposit of the positron in fakeDetector is: " << energyDep << G4endl;

    if (trackID == 1) {
        hit->AddEnergyDeposit(energyDep);
        if (eventNumber != eventID) {
            eventID = eventNumber;
            hit->AddEventID();
        }
    }

    //Get positron when it is generated
    if (particle == G4Positron::Positron() && step->IsFirstStepInVolume()) {
        hit->AddNumberOfPositrons();
    }

    hitsCollection->insert(hit);

    G4StepPoint *preStepPoint = step->GetPreStepPoint();
    G4StepPoint *postStepPoint = step->GetPostStepPoint();

    G4double particleEnergy = preStepPoint->GetTotalEnergy();
    G4ThreeVector posParticle = preStepPoint->GetPosition();

    G4ThreeVector detectorPos = G4ThreeVector(0, -1.25*m, 2.21*m);
    G4ThreeVector newPos = posParticle - detectorPos;

    G4cout << "Particle position in positrondetector is: " << newPos << G4endl;
    G4cout << "Particle energy in positrondetector is: " << particleEnergy << G4endl;

    auto *man = G4RootAnalysisManager::Instance();
    //man->FillNtupleIColumn(1, 0, evt);

    if (particle == G4Gamma::Gamma()) {
        man->FillNtupleIColumn(0, 0, eventNumber);
        man->FillNtupleDColumn(0, 1, particleEnergy);
        man->FillNtupleDColumn(0, 2, posParticle[0]);
        man->FillNtupleDColumn(0, 3, posParticle[1]);
        //man->FillNtupleDColumn(0, 4, missMass);

        man->AddNtupleRow(0);
    }

    if (particle == G4Positron::Positron()) {
        man->FillNtupleIColumn(1, 0, eventNumber);
        man->FillNtupleDColumn(1, 1, particleEnergy);
        man->FillNtupleDColumn(1, 2, newPos[0]);
        man->FillNtupleDColumn(1, 3, newPos[1]);

        man->AddNtupleRow(1);
    }

    man->FillNtupleIColumn(2, 1, eventNumber);
    man->AddNtupleRow(2);

    return true;
}

void MyPositronDetector::EndOfEvent(G4HCofThisEvent* hce)
{}
