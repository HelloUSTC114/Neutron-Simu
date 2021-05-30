/*
*   File : CRTest/inc/NeutronGenerator.hh
*
*   Brief: Generator with Purdue Cosmic-ray Muon Model
*
*   Reference
*     S. Chatzidakis, S. Chrysikopoulou, L.H. Tsoukalas (2015)
*     S. Chatzidakis, L.H. Tsoukalas (2015)
*
*/

#ifndef CRTest_NeutronGenerator_h
#define CRTest_NeutronGenerator_h

#include "Generator.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Event.hh"
#include "Randomize.hh"

#include "TF1.h"

class NeutronGenerator : public Generator
{
public:
  NeutronGenerator();
  virtual ~NeutronGenerator();

public:
  virtual void GeneratePrimaries(G4Event *anEvent) override;


private: // Override Base virtual method
  virtual void GeneratePosition() override;
  virtual void GenerateDirection() override;
  virtual void GenerateKineticEnergy() override;

private:
  G4double GetTheta(); // muon zenith angle
  G4ThreeVector GetDirection(); // muon momentim direction

private:
  G4double fEmin;
  G4double fEmax;
  G4double fTheta;
};


#endif /*CRTest_NeutronGenerator_h*/