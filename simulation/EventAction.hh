#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"

#include "G4THitsMap.hh"
#include "globals.hh"

//namespace simulation
//{

class EventAction : public G4UserEventAction
{
    public:
        EventAction() = default;
        ~EventAction() override = default;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    private:
        // methods
        G4THitsMap<G4double>* GetHitsCollection(G4int hcID, const G4Event* event) const;
        G4double GetSum(G4THitsMap<G4double>* hitsMap) const;
        void PrintEventStatistics(G4double absoEdep, G4double absoTrackLength, G4double gapEdep, G4double gapTrackLength) const;
        // data members
        //G4int evtID = -1;
        G4int fAbsoEdepHCID = -1;
        G4int fGapEdepHCID = -1;
        G4int fAbsoTrackLengthHCID = -1;
        G4int fGapTrackLengthHCID = -1;
};
//}

#endif
