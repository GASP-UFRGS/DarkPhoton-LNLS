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
	man->CreateNtupleDColumn("photonEnergy");
	man->CreateNtupleDColumn("photonX");
	man->CreateNtupleDColumn("photonY");
	man->CreateNtupleDColumn("photonZ");
    man->CreateNtupleDColumn("posistronEnergy");
    man->CreateNtupleDColumn("positronX");
    man->CreateNtupleDColumn("positronY");
    man->CreateNtupleDColumn("positronZ");
	man->FinishNtuple(0);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	auto *man = G4RootAnalysisManager::Instance();

	man->Write();
	man->CloseFile();
}
