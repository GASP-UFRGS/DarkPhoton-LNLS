#include "Hits.hh"

G4ThreadLocal G4Allocator<Hits>* HitAllocator = 0;

Hits::Hits(): G4VHit(), numberOfPositrons(0), energyDeposit(0), eventID(0)
{}

Hits::~Hits()
{}
