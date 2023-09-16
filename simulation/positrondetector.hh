#ifndef POSITRONDETECTOR_HH
#define POSITRONDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4Gamma.hh"
#include "G4RootAnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4RootAnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

class MyPositronDetector : public G4VSensitiveDetector
{
public:
    MyPositronDetector(G4String);
    ~MyPositronDetector();

private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif
