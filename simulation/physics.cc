#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
	RegisterPhysics (new G4EmStandardPhysics());
	RegisterPhysics (new G4OpticalPhysics());

	RegisterPhysics (new G4EmExtraPhysics());
	RegisterPhysics (new G4DecayPhysics());
	RegisterPhysics (new G4IonPhysics());
	RegisterPhysics (new G4StoppingPhysics());
	RegisterPhysics (new G4HadronElasticPhysics());
	RegisterPhysics (new G4HadronElasticPhysicsHP());

	RegisterPhysics (new G4HadronPhysicsQGSP_BERT());
	RegisterPhysics (new G4HadronPhysicsQGSP_BIC());
}

MyPhysicsList::~MyPhysicsList()
{}