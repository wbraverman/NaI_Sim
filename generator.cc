#include "generator.hh"
#include "construction.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{

	
	fParticleGun = new G4ParticleGun(1); // There is a distinction between events and a run that I do not understand, but the 1 forces one particle per event. I think multiple events together constitute a run
	
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle("geantino"); // select beam particle
	
	fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}


void MyPrimaryGenerator:: GeneratePrimaries(G4Event *anEvent)
{	
	
	CLHEP::HepRandom::setTheSeed((unsigned)clock());
	
	G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();
	
	if(particle == G4Geantino::Geantino()){
		G4int Z = 9;  // proton number
		G4int A = 17; // nucleon number
		
		G4double charge = 0*eplus; // charge state
		G4double energy = 0*keV; // excitation energy of particle
		
		G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy); // gets relevant physics to your specified particle
		
		fParticleGun->SetParticleDefinition(ion);
		fParticleGun->SetParticleCharge(charge);
	}
	
	
	// spawn on walls of gas cell
	rand_int = G4UniformRand() * 6.;
	
	
	G4double gasHalfSizeX = ((57.15-9.652)/2.);  
	G4double gasHalfSizeY = ((57.15-9.652)/2.); 
	G4double gasHalfSizeZ = ((50.8-9.652)/2.);
	
	//G4cout << "Random Int: " << rand_int << G4endl;
	
	switch(rand_int){
		case 0:
			xpos = gasHalfSizeX*mm;
			ypos = ((gasHalfSizeY*2)*(G4UniformRand()-0.5))*mm;
			zpos = ((gasHalfSizeZ*2)*(G4UniformRand()-0.5))*mm;
			break;
		case 1:
			xpos = (-1)*gasHalfSizeX*mm;
			ypos = ((gasHalfSizeY*2)*(G4UniformRand()-0.5))*mm;
			zpos = ((gasHalfSizeZ*2)*(G4UniformRand()-0.5))*mm;
			break;
		case 2:
			xpos = ((gasHalfSizeX*2)*(G4UniformRand()-0.5))*mm;
			ypos = gasHalfSizeY*mm;
			zpos = ((gasHalfSizeZ*2)*(G4UniformRand()-0.5))*mm;
			break;
		case 3:
			xpos = ((gasHalfSizeX*2)*(G4UniformRand()-0.5))*mm;
			ypos = (-1)*gasHalfSizeY*mm;
			zpos = ((gasHalfSizeZ*2)*(G4UniformRand()-0.5))*mm;
			break;
		case 4:
			xpos = ((gasHalfSizeX*2)*(G4UniformRand()-0.5))*mm;
			ypos = ((gasHalfSizeY*2)*(G4UniformRand()-0.5))*mm;
			zpos = gasHalfSizeZ*mm;
			break;
		case 5:
			xpos = ((gasHalfSizeX*2)*(G4UniformRand()-0.5))*mm;
			ypos = ((gasHalfSizeY*2)*(G4UniformRand()-0.5))*mm;
			zpos = (-1)*gasHalfSizeZ*mm;
			break;		
	}
	
	
	
	/*
	// spawn at a random location within gas cell
	xpos = ((gasHalfSizeX*2)*(G4UniformRand()-0.5))*mm;
	ypos = ((gasHalfSizeY*2)*(G4UniformRand()-0.5))*mm;
	zpos = ((gasHalfSizeZ*2)*(G4UniformRand()-0.5))*mm;
	*/
	
	/*
	// spawn at origin
	xpos = 0.*mm;
	ypos = 0.*mm;
	zpos = 0.*mm;
	*/
	
	
	fParticleGun->SetParticleMomentum(0.*GeV); //set momentum of particle
	fParticleGun->SetParticlePosition(G4ThreeVector(xpos, ypos, zpos));
	
	fParticleGun->GeneratePrimaryVertex(anEvent);
}
