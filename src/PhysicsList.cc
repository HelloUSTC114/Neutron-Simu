/**
*   FILE : CRTest/src/PhysicsList.cc
*   Brief: Implementation of class PhysicsList
*/

#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"

#include "G4EmExtraPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"

#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList()
    : G4VModularPhysicsList(), 
	fEmPhys(NULL), fOpPhys(NULL), fLimiterPhys(NULL)
{
	// Similar with CMS
	fEmPhys = new G4EmStandardPhysics_option1;
	RegisterPhysics(fEmPhys);

	fOpPhys = new G4OpticalPhysics;
	RegisterPhysics(fOpPhys);

	fDecayPhys = new G4DecayPhysics;
	RegisterPhysics(fDecayPhys);

	fLimiterPhys = new G4StepLimiterPhysics;
	RegisterPhysics(fLimiterPhys);

	RegisterPhysics(new G4HadronPhysicsQGSP_BERT_HP);

	RegisterPhysics(new G4EmExtraPhysics);
	RegisterPhysics(new G4HadronElasticPhysicsHP );
	RegisterPhysics(new G4StoppingPhysics);
	RegisterPhysics(new G4IonPhysics);
	RegisterPhysics(new G4NeutronTrackingCut);

    
    SetDefaultCutValue(0.7*mm);

	Print();
}

PhysicsList::~PhysicsList()
{
	G4cout << "[-] INFO - PhysicsList deleted. " << G4endl;
}

void PhysicsList::Print(){
	G4cout << G4endl
		<< "[-] INFO - Physics List Registered : " << G4endl;
	if(fEmPhys)
		G4cout << " |  + " << fEmPhys->GetPhysicsName() << G4endl;
	if(fOpPhys)
		G4cout << " |  + " << fOpPhys->GetPhysicsName() << G4endl;
	if(fDecayPhys)
		G4cout << " |  + " << fDecayPhys->GetPhysicsName() << G4endl;
	if(fLimiterPhys)
		G4cout << " |  + " << fLimiterPhys->GetPhysicsName() << G4endl;
}