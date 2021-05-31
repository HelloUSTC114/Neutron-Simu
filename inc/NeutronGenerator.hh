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
#include "TGraph.h"

#include "TF1.h"

class NeutronGenerator : public Generator
{
public:
  NeutronGenerator();
  virtual ~NeutronGenerator();

public:
  virtual void GeneratePrimaries(G4Event *anEvent) override;
  inline void GeneratePrimaryToy(double &theta, double &phi, double &Ek);

private: // Override Base virtual method
  virtual void GeneratePosition() override;
  virtual void GenerateDirection() override;
  virtual void GenerateKineticEnergy() override;

private:
  G4double GetTheta();          // muon zenith angle
  G4ThreeVector GetDirection(); // muon momentim direction

  static double NeutronSpectrum(double *x, double *par);

private:
  G4double fEmin;
  G4double fEmax;
  G4double fTheta;

  static double ftgx[184];
  static double ftgy[184];

public:
  static TGraph *ftg;
  TF1 *fNeuEne;
};

inline void NeutronGenerator::GeneratePrimaryToy(double &theta, double &phi, double &Ek)
{
  theta = GetTheta();
  phi = G4UniformRand() * TMath::Pi() * 2.;
  Ek = fNeuEne->GetRandom() * CLHEP::MeV;
}

#endif /*CRTest_NeutronGenerator_h*/