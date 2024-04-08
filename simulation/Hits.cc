#include "Hits.hh"

G4ThreadLocal G4Allocator<Hits>* HitAllocator = 0;

Hits::Hits(): G4VHit(), numberOfPhotons(0), numberOfPositrons(0), energyDeposit(0), eventID(0)
{}

Hits::~Hits()
{}

void Hits::Print() {
    G4cout
        << "Current event is: "
        << eventID
        << "\nNumber Of Photons in this event: "
        <<  numberOfPhotons
        << "\nNumber Of Positrons in this event: "
        << numberOfPositrons
        << "\n"
        << G4endl;
}
