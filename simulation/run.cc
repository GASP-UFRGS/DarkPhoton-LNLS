#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
	auto *man = G4RootAnalysisManager::Instance();

	man->OpenFile("output.root");

	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("PhotonEnergy");
	man->CreateNtupleDColumn("PhotonX");
	man->CreateNtupleDColumn("PhotonY");
	man->CreateNtupleDColumn("PhotonZ");
    man->CreateNtupleDColumn("PositronEnergy");
    man->CreateNtupleDColumn("PositronX");
    man->CreateNtupleDColumn("PositronY");
    man->CreateNtupleDColumn("PositronZ");
	man->FinishNtuple(0);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	auto *man = G4RootAnalysisManager::Instance();

	man->Write();
	man->CloseFile();
}
