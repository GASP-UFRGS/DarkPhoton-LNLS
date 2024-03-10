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

class MyPositronDetector : public G4VSensitiveDetector
{
public:
    MyPositronDetector(G4String);
    ~MyPositronDetector();

    void RegisterPrimitive(G4VPrimitiveScorer* scorer);

private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif
