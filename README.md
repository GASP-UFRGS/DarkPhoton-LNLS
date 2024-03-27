# DarkPhoton-LNLS

## Detector simulation for search of Dark Photon in beam-dump experiment

This project is a simplified simulation of the PADME experiment at INFN LNF using Geant4

## How to install the simulation

Users must have at least Geant4 version 11 installed.

1. Clone this project
2. If you are in /simulation create a build folder
   ```
   mkdir build
   ```
3. Inside build use
   ```
   cmake
   ```
4. Then you can run
   ```
   make
   ```
5. Finally, to start the simulation, you can run 
   ```
   ./main
   ```
   Alternatively, it is possible to run a macro file that runs 100000 events with no GUI. The data is stored in a ROOT file.
   ```
   ./main run.mac
   ```
