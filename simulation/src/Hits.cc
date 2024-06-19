#include "Hits.hh"

G4ThreadLocal G4Allocator<Hits>* HitAllocator = 0;

Hits::Hits(): G4VHit(), numberOfPhotons(0), numberOfPositrons(0), energyDeposit(0), eventID(0)
{}

Hits::~Hits()
{}

void Hits::Print() {
    G4cout
        << "Current detector is: "
        << eventID
        << "\nNumber Of Photons in this event: "
        << numberOfPhotons
        << "\nNumber Of Positrons in this event: "
        << numberOfPositrons
        << "\n"
        << G4endl;
}

G4int Hits::GetNumberOfPhotons() {
    return numberOfPhotons;
}

G4int Hits::GetNumberOfPositrons() {
    return numberOfPositrons;
}

G4int Hits::GetNumberOfEvent() {
    return eventID;
}
