#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4RootAnalysisManager.hh" // In older versions it could be used g4root.hh

class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction();
    ~MyRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
