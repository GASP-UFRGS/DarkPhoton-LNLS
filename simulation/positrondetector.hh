#ifndef POSITRONDETECTOR_HH
#define POSITRONDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4Gamma.hh"
#include "G4Positron.hh"
#include "G4RootAnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4RootAnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include "G4HCofThisEvent.hh"
#include "G4Track.hh"

#include "DetectorConstruction.hh"
#include "Hits.hh"

class MyDetectorConstruction;
class G4String;
class G4Step;
class G4TouchableHistory;
class G4HCofThisEvent;

class MyPositronDetector : public G4VSensitiveDetector {
public:
    MyPositronDetector(const G4String& name, const G4String& hitsCollectionName, MyDetectorConstruction* det);
    ~MyPositronDetector();

    // void RegisterPrimitive(G4VPrimitiveScorer* scorer);

    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    void Initialize(G4HCofThisEvent* hce);
    void EndOfEvent(G4HCofThisEvent* hce);

private:
    G4bool photonsDetected;
    G4bool positronsDetected;

    HitsCollection* hitsCollection;
    int hcid;
    int eventID;
    MyDetectorConstruction* det;
};

#endif
