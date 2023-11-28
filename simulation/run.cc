#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    auto *man = G4RootAnalysisManager::Instance();
    man->OpenFile("output.root");

    man->CreateNtuple("PhotonHits", "PhotonHits");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("PhotonEnergy");
    man->CreateNtupleDColumn("PhotonX");
    man->CreateNtupleDColumn("PhotonY");
    man->CreateNtupleDColumn("newPhotonEnergy");

    man->FinishNtuple(0);

    man->CreateNtuple("PositronHits", "PositronHits");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("PositronEnergy");
    man->CreateNtupleDColumn("PositronX");
    man->CreateNtupleDColumn("PositronY");

    man->FinishNtuple(1);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    auto *man = G4RootAnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}
