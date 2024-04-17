#include "EventAction.hh"

#include "G4RootAnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"

#include "Randomize.hh"
#include <iomanip>

G4THitsMap<G4double>*
EventAction::GetHitsCollection(G4int hcID, const G4Event *event) const {
    auto hitsCollection = static_cast<G4THitsMap<G4double>*>(event->GetHCofThisEvent()->GetHC(hcID));
    if ( ! hitsCollection ) {
        G4ExceptionDescription msg;
        msg << "Cannot access hitsCollection ID " << hcID;
        G4Exception("EventAction::GetHitsCollection()", "MyCode0003", FatalException, msg);
    }
    return hitsCollection;
}

G4double EventAction::GetSum(G4THitsMap<G4double>* hitsMap) const {
    G4double sumValue = 0.;
    for ( auto it : *hitsMap->GetMap() ) {
        // hitsMap->GetMap() returns the map of std::map<G4int, G4double*>
        sumValue += *(it.second);
    }
    return sumValue;
}

void EventAction::PrintEventStatistics(G4double fAbsoEdepHCID, G4double fAbsoTrackLengthHCID, G4double fGapEdepHCID, G4double fGapTrackLengthHCID) const
{
    // Print event statistics
    G4cout
        << "   Absorber: total energy: "
        << std::setw(7) << G4BestUnit(fAbsoEdepHCID, "Energy")
        << "       total track length: "
        << std::setw(7) << G4BestUnit(fAbsoTrackLengthHCID, "Length")
        << G4endl
        << "        Gap: total energy: "
        << std::setw(7) << G4BestUnit(fGapEdepHCID, "Energy")
        << "       total track length: "
        << std::setw(7) << G4BestUnit(fGapTrackLengthHCID, "Length")
        << G4endl;
}

void EventAction::BeginOfEventAction(const G4Event*) {}

void EventAction::EndOfEventAction(const G4Event* event) {
    // Get hist collections IDs
    if ( fAbsoEdepHCID == -1 ) {
        fAbsoEdepHCID
                = G4SDManager::GetSDMpointer()->GetCollectionID("Calorimeter/Edep");
        fGapEdepHCID
                = G4SDManager::GetSDMpointer()->GetCollectionID("PositronDetector/Edep");
        fAbsoTrackLengthHCID
                = G4SDManager::GetSDMpointer()->GetCollectionID("Calorimeter/TrackLength");
        fGapTrackLengthHCID
                = G4SDManager::GetSDMpointer()->GetCollectionID("PositronDetector/TrackLength");
    }

    // Get sum values from hits collections
    auto absoEdep = GetSum(GetHitsCollection(fAbsoEdepHCID, event));
    auto gapEdep = GetSum(GetHitsCollection(fGapEdepHCID, event));
    auto absoTrackLength = GetSum(GetHitsCollection(fAbsoTrackLengthHCID, event));
    auto gapTrackLength = GetSum(GetHitsCollection(fGapTrackLengthHCID, event));

    // Retrieve primary vertex
    G4PrimaryVertex* primaryVertex = event->GetPrimaryVertex(0);

    // Acces primary particles generated in this vertex
    G4PrimaryParticle* primaryParticle = primaryVertex->GetPrimary();
    G4String particleName = primaryParticle->GetParticleDefinition()->GetParticleName();


    // get analysis manager
    auto *man = G4RootAnalysisManager::Instance();

    auto eventID = event->GetEventID();


    G4cout << "The energy deposit in calodetector (EventAction) is: " << absoEdep << G4endl;
    G4cout << "The energy deposit in positrondetector (EventAction) is: " << absoEdep << G4endl;

    man->FillNtupleIColumn(3, 0, eventID);
    man->FillNtupleDColumn(3, 1, absoEdep);
    man->FillNtupleDColumn(3, 2, gapEdep);
    man->FillNtupleDColumn(3, 3, absoTrackLength);
    man->FillNtupleDColumn(3, 4, gapTrackLength);

    man->AddNtupleRow(3);

    man->FillNtupleIColumn(4, 0, eventID);

    man->AddNtupleRow(4);

    //print per event (modulo n)
    //auto eventID = event->GetEventID();
    auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
        G4cout << "---> End of event: " << eventID << G4endl;
        PrintEventStatistics(fAbsoEdepHCID, fAbsoTrackLengthHCID, fGapEdepHCID, fGapTrackLengthHCID);
    }
}
