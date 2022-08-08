# Geant4-Exp_1

# A detector has been created using Geant4 simulation toolkit. 
#The world volume has dimensions : 1m, 1m, 2m in x,y and z. The material chosen for world volume is G4_Galactic.
#The Detector is constructed with five individual volumes : Three out of these five volumes behave as active scintillation layers constructed with material : G4_PLASTIC_SC_VINYLTOLUENE. 
#First scintiallation layer is located at 0m,0m,0.867m. Second is located at 0m,0m,0.755m. And third is located at 0m,0m,-0.755m. 
#The dimension of each layer are : 10cm, 10cm, 1cm. Each of these layers is also divided into a detector matrix of 100*100 resulting in a position resolution of 10^(-4) each. 
#The volume contained between scintillation layer one and two is filled with magnetic field of 0.5Tesla in -x direction. It's dimensions are 10cm, 10cm, 10cm.
#The volume between layer two and three has dimensions 10cm, 10cm, 150cm. The matertial assigned to this volume is G4_Galactic.

#Cosmic Muon Shower is generated using header from EcoMug. The size of sky is 1m,1m. The position of shower source is kept right above the first scintillating layer at location : 0m,0m,0.9m.
#The theta angle i.e. angle between z-axis and x-axis for muon shower is limmited to a maximum of pi/10.

#The included root file contains information on 2000 runs.
#In the Root file, Hits Tree contains position co-ordinated -- fX, fY and fZ of the detectors a muon hits in all three layers.
#In Hits Tree EnergyDeposit includes the energy deposited by the muon in each detector and fEvent contains event number.
#Scoring Tree contains Total Energy Desposited in the detectors by the muon in a full event.
