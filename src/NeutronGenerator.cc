/**
*   FILE : CRTest/src/NeutronGenerator.cc
*   Brief: Implementation of class NeutronGenerator
*/

#include "NeutronGenerator.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

#include "TMath.h"
#include "TF1.h"

NeutronGenerator::NeutronGenerator() : Generator(), fTheta(0.)
{
    // Initilized muon spectrum function
    auto pNeutron = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
    fParticleGun->SetParticleDefinition(pNeutron);
    assert(pNeutron != NULL);

    fEmin = 0 * MeV; // GeV - [TODO] change to G4SystemOfUnits?
    fEmax = 10 * MeV;
}

NeutronGenerator::~NeutronGenerator()
{
}

void NeutronGenerator::GeneratePosition()
{

    G4ThreeVector position = GetWorldBoundary();
    position.setX(position.x() * (1 - 2 * G4UniformRand()));
    position.setY(position.y() * (1 - 2 * G4UniformRand()));
    position.setZ(-position.z());

    if (fTriggerMode)
    {
        position.setX(fXmin + (fXmax - fXmin) * G4UniformRand());
        position.setY(fYmin + (fYmax - fYmin) * G4UniformRand());
    }

    fParticleGun->SetParticlePosition(position);
}

void NeutronGenerator::GenerateDirection()
{

    // muon momentum direction
    fTheta = this->GetTheta();

    G4double phi = G4UniformRand() * TMath::Pi() * 2.;
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(
        TMath::Sin(fTheta) * TMath::Cos(phi),
        TMath::Sin(fTheta) * TMath::Sin(phi),
        TMath::Cos(fTheta)));
}

void NeutronGenerator::GenerateKineticEnergy()
{
    // muon kinetic energy
    fParticleGun->SetParticleEnergy(G4UniformRand() * (fEmax - fEmin) + fEmin);
}

void NeutronGenerator::GeneratePrimaries(G4Event *anEvent)
{
    Generate();
    if (fTriggerMode)
    {
        G4int count = 1;
        G4ThreeVector boundary = GetWorldBoundary();
        while (!CheckEndpoint(boundary.z()) && count < 1000)
        {
            Generate();
            count++;
        }
        // [TODO] : #ifdef CRTest_VERBOSE/DEBUG
        if (count > 100)
            G4cout << "[+] WARNING - BAD trigger efficiency. "
                   << "Samples : " << count << "- by " << __func__ << G4endl;
    }
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

// Accept-Reject method to sample muon zenith angle
G4double NeutronGenerator::GetTheta()
{
    using namespace TMath;
    // // [TODO] create a general A-R method in class Generator
    // G4double rnd, theta, val;
    // do
    // {
    //   // [TODO] change to CLHEP or G4
    //   theta = G4UniformRand() * TMath::Pi() / 2.;
    // 	// Zenith angular distribution
    //   val = Sin(theta) * Cos(theta) * Cos(theta) * Cos(theta);
    //   rnd = G4UniformRand();
    // } while (rnd > val);

    // Use Inverse function method
    double rnd = G4UniformRand();
    double theta = TMath::ACos(TMath::Power(1 - rnd, 1.0 / 3));
    return theta;
}

G4ThreeVector NeutronGenerator::GetDirection()
{
    // [TODO] create a general method in class Generator
    using namespace TMath;

    G4double theta = this->GetTheta();
    G4double phi = G4UniformRand() * Pi() * 2.;

    return G4ThreeVector(
        Cos(theta) * Cos(phi),
        Cos(theta) * Sin(phi),
        Sin(theta));
}
