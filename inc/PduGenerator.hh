/*
*   File : CRTest/inc/PduGenerator.hh
*
*   Brief: Generator with Purdue Cosmic-ray Muon Model
*
*   Reference
*     S. Chatzidakis, S. Chrysikopoulou, L.H. Tsoukalas (2015)
*     S. Chatzidakis, L.H. Tsoukalas (2015)
*
*/

#ifndef CRTest_PduGenerator_h
#define CRTest_PduGenerator_h

#include "Generator.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Event.hh"
#include "Randomize.hh"

#include "TF1.h"

class PduGenerator : public Generator
{
public:
  PduGenerator();
  virtual ~PduGenerator();

public:
  virtual void GeneratePrimaries(G4Event *anEvent);

  inline void GeneratePrimaryToy(double &theta, double &phi, double &Ek);

private: // Override Base virtual method
  virtual void GeneratePosition();
  virtual void GenerateDirection();
  virtual void GenerateKineticEnergy();

private:
  static G4double PduModel(G4double*,G4double*);
  G4double GetTheta(); // muon zenith angle
  G4ThreeVector GetDirection(); // muon momentim direction

private:
  TF1 *fPduModel;
  G4double fEmin;
  G4double fEmax;
  G4double fTheta;
};

inline void PduGenerator::GeneratePrimaryToy(double &theta, double &phi, double &Ek)
{
  theta = GetTheta();
  phi = G4UniformRand() * TMath::Pi() * 2.;
  fPduModel->FixParameter(0, fTheta);
  Ek = fPduModel->GetRandom() * CLHEP::GeV;
}

#endif /*CRTest_PduGenerator_h*/