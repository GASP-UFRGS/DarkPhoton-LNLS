// includes Hit and HitsCollection objects

#ifndef HIT_HH
#define HIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"

#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4Threading.hh"

#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

class Hits: public G4VHit {
public:
    Hits();
    virtual ~Hits();

    void Print() override;

    // Operators
    inline void *operator new(size_t);
    inline void operator delete(void*);

    inline void AddEnergyDeposit(double e) { energyDeposit += e; }
    inline void AddNumberOfPhotons() {numberOfPhotons += 1;}
    inline void AddNumberOfPositrons() {numberOfPositrons += 1;}
    inline void AddEventID() { eventID += 1; }
    inline double GetEnergyDeposit() {return energyDeposit;}
    inline int GetNumberOfPhotons() {return numberOfPhotons;}
    inline int GetNumberOfPositrons() {return numberOfPositrons;}
    inline int GetNumberOfEvent() { return eventID; }

private:
    int numberOfPhotons;
    int numberOfPositrons;
    double energyDeposit;
    int eventID;
};

typedef G4THitsCollection<Hits> HitsCollection;

extern G4ThreadLocal G4Allocator<Hits>* HitAllocator;

inline void* Hits::operator new(size_t)
{
    if (!HitAllocator) {
        HitAllocator = new G4Allocator<Hits>;
    }
    void *hit;
    hit = (void *) HitAllocator->MallocSingle();
    return hit;
}

inline void Hits::operator delete(void *aHit)
{
    if (!HitAllocator) {
        HitAllocator = new G4Allocator<Hits>;
    }
    HitAllocator->FreeSingle((Hits*) aHit);
}

#endif
