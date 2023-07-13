#include "generator.hh"

#include <random>

MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName="e+";
	G4ParticleDefinition *particle = particleTable->FindParticle("e+");

	G4double randomX = rand() % 10 + (-5);
	G4double randomY = rand() % 10 + (-5);

	G4double posX = randomX/10.;
	G4double posY = randomY/10.;

	G4ThreeVector pos(posX*m, posY*m,-1*m);
	G4ThreeVector mom(0.,0.,1);

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(550.*MeV);
	fParticleGun->SetParticleDefinition(particle);

	fParticleGun->GeneratePrimaryVertex(anEvent);
}