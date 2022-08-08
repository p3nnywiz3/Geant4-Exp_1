#include "generator.hh"
#include "G4SystemOfUnits.hh"

PrimaryGenerator::PrimaryGenerator()
{ 
	fMuonGen.SetUseSky();
	fMuonGen.SetSkySize({1.*m,1.*m});
	fMuonGen.SetSkyCenterPosition({{0.,0.,0.9*m}});
	fMuonGen.SetMaximumTheta(M_PI/10);
	
	fParticleGun = new G4ParticleGun(1);
	mu_minus = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
	mu_plus = G4ParticleTable::GetParticleTable()->FindParticle("mu+");
}

PrimaryGenerator::~PrimaryGenerator()
{
	delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	
	fMuonGen.Generate();
	std::array<double,3> muon_pos = fMuonGen.GetGenerationPosition();
	double muon_mom = fMuonGen.GetGenerationMomentum();
	double muon_theta = fMuonGen.GetGenerationTheta();
	double muon_phi = fMuonGen.GetGenerationPhi();
	
	if(fMuonGen.GetCharge()<0) { fParticleGun->SetParticleDefinition(mu_minus);}
	else {fParticleGun->SetParticleDefinition(mu_plus);}
	fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.9*m));
	fParticleGun->SetParticleMomentum(G4ParticleMomentum(muon_mom*sin(muon_theta)*cos(muon_phi)*GeV, muon_mom*sin(muon_theta)*sin(muon_phi)*GeV , muon_mom*cos(muon_theta)*GeV));
	
	//G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	//G4String particleName = "proton";
	//G4ParticleDefinition *particle = particleTable->FindParticle("proton");
	
	//G4ThreeVector pos(0.,0.,-0.7*km);
	//G4ThreeVector mom(0.,0.,1.);
	
	//fParticleGun->SetParticlePosition(pos);
	//fParticleGun->SetParticleMomentumDirection(mom);
	//fParticleGun->SetParticleMomentum(100*GeV);
	//fParticleGun->SetParticleDefinition(particle);
	
	fParticleGun->GeneratePrimaryVertex(anEvent);
	
}
