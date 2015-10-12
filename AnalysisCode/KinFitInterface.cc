#include "PhysicsTools/KinFitter/interface/TFitConstraintM.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleEtEtaPhi.h"
#include "PhysicsTools/KinFitter/interface/TKinFitter.h"

#include "TLorentzVector.h"

#include <iostream>

Double_t ErrEt(Float_t Et, Float_t Eta) {
  Double_t InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 5.6;
    b = 1.25;
    c = 0.033;
  }
  else{
    a = 4.8;
    b = 0.89;
    c = 0.043;
  }
  InvPerr2 = (a * a) + (b * b) * Et + (c * c) * Et * Et;
  return InvPerr2;
}

Double_t ErrEta(Float_t Et, Float_t Eta) {
  Double_t InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 1.215;
    b = 0.037;
    c = 7.941 * 0.0001;
  }
  else{
    a = 1.773;
    b = 0.034;
    c = 3.56 * 0.0001;
  }
  InvPerr2 = a/(Et * Et) + b/Et + c;
  return InvPerr2;
}

Double_t ErrPhi(Float_t Et, Float_t Eta) {
  Double_t InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 6.65;
    b = 0.04;
    c = 8.49 * 0.00001;
  }
  else{
    a = 2.908;
    b = 0.021;
    c = 2.59 * 0.0001;
  }
  InvPerr2 = a/(Et * Et) + b/Et + c;
  return InvPerr2;
}

/*void print(TKinFitter *fitter)
{
  std::cout << "=============================================" << std ::endl;
  std::cout << "-> Number of measured Particles  : " << fitter->nbMeasParticles() << std::endl;
  std::cout << "-> Number of unmeasured particles: " << fitter->nbUnmeasParticles() << std::endl;
  std::cout << "-> Number of constraints         : " << fitter->nbConstraints() << std::endl;
  std::cout << "-> Number of degrees of freedom  : " << fitter->getNDF() << std::endl;
  std::cout << "-> Number of parameters A        : " << fitter->getNParA() << std::endl;
  std::cout << "-> Number of parameters B        : " << fitter->getNParB() << std::endl;
  std::cout << "-> Maximum number of iterations  : " << fitter->getMaxNumberIter() << std::endl;
  std::cout << "-> Maximum deltaS                : " << fitter->getMaxDeltaS() << std::endl;
  std::cout << "-> Maximum F                     : " << fitter->getMaxF() << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std ::endl;
  std::cout << "-> Status                        : " << fitter->getStatus() << std::endl;
  std::cout << "-> Number of iterations          : " << fitter->getNbIter() << std::endl;
  std::cout << "-> S                             : " << fitter->getS() << std::endl;
  std::cout << "-> F                             : " << fitter->getF() << std::endl;
  std::cout << "=============================================" << std ::endl;
}*/

double constrainHH(TLorentzVector *j1, TLorentzVector *j2, TLorentzVector *j3, TLorentzVector *j4, double mass1=125, double mass2=125)
{
  gSystem->Load("libPhysicsToolsKinFitter.so");
  
  // Covariance matrices of the four jets
  TMatrixD m1(3,3);
  TMatrixD m2(3,3);
  TMatrixD m3(3,3);
  TMatrixD m4(3,3);
  m1.Zero();
  m2.Zero();
  m3.Zero();
  m4.Zero();
  
  // Dependence of the covariance matrix on Et and eta
  m1(0,0) = ErrEt(j1->Et(), j1->Eta());
  m1(1,1) = ErrEta(j1->Et(), j1->Eta());
  m1(2,2) = ErrPhi(j1->Et(), j1->Eta());
  
  m2(0,0) = ErrEt(j2->Et(), j2->Eta());
  m2(1,1) = ErrEta(j2->Et(), j2->Eta());
  m2(2,2) = ErrPhi(j2->Et(), j2->Eta());
  
  m3(0,0) = ErrEt(j3->Et(), j3->Eta());
  m3(1,1) = ErrEta(j3->Et(), j3->Eta());
  m3(2,2) = ErrPhi(j3->Et(), j3->Eta());
  
  m4(0,0) = ErrEt(j4->Et(), j4->Eta());
  m4(1,1) = ErrEta(j4->Et(), j4->Eta());
  m4(2,2) = ErrPhi(j4->Et(), j4->Eta());
  
  TFitParticleEtEtaPhi *jet1 = new TFitParticleEtEtaPhi(j1, &m1);
  TFitParticleEtEtaPhi *jet2 = new TFitParticleEtEtaPhi(j2, &m2);
  TFitParticleEtEtaPhi *jet3 = new TFitParticleEtEtaPhi(j3, &m3);
  TFitParticleEtEtaPhi *jet4 = new TFitParticleEtEtaPhi(j4, &m4);
  
  // Constrain jet1 and jet2 to one H, and jet3 and jet4 to another
  TFitConstraintM *massConstraint1 = new TFitConstraintM("massConstraint1", "massConstraint1", 0, 0, mass1);
  massConstraint1->addParticles1(jet1, jet2);
  
  TFitConstraintM *massConstraint2 = new TFitConstraintM("massConstraint2", "massConstraint2", 0, 0, mass2);
  massConstraint2->addParticles1(jet3, jet4);
  
  // Call the fitter
  TKinFitter *fitter = new TKinFitter("fitter", "fitter");
  fitter->addMeasParticle(jet1);
  fitter->addMeasParticle(jet2);
  fitter->addMeasParticle(jet3);
  fitter->addMeasParticle(jet4);
  fitter->addConstraint(massConstraint1);
  fitter->addConstraint(massConstraint2);
  
  //Set convergence criteria
  fitter->setMaxNbIter(30);
  fitter->setMaxDeltaS(1e-2);
  fitter->setMaxF(1e-1);
  fitter->setVerbosity(3);
  
  // Fit
  fitter->fit();
  
  // Return and quit
  *j1 = TLorentzVector(*(fitter->get4Vec(0)));
  *j2 = TLorentzVector(*(fitter->get4Vec(1)));
  *j3 = TLorentzVector(*(fitter->get4Vec(2)));
  *j4 = TLorentzVector(*(fitter->get4Vec(3)));
  
  delete jet1;
  delete jet2;
  delete jet3;
  delete jet4;
  delete massConstraint1;
  delete massConstraint2;
  delete fitter;
  
  return 0;
}

double constrainHH_check(TLorentzVector *j1, TLorentzVector *j2, TLorentzVector *j3, TLorentzVector *j4, double mass1=125, double mass2=125)
{
  gSystem->Load("libPhysicsToolsKinFitter.so");
  
  // Covariance matrices of the four jets
  TMatrixD m1(3,3);
  TMatrixD m2(3,3);
  TMatrixD m3(3,3);
  TMatrixD m4(3,3);
  m1.Zero();
  m2.Zero();
  m3.Zero();
  m4.Zero();
  
  // Dependence of the covariance matrix on Et and eta
  m1(0,0) = 5;
  m2(0,0) = 5;
  m3(0,0) = 5;
  m4(0,0) = 5;
  
  TFitParticleEtEtaPhi *jet1 = new TFitParticleEtEtaPhi(j1, &m1);
  TFitParticleEtEtaPhi *jet2 = new TFitParticleEtEtaPhi(j2, &m2);
  TFitParticleEtEtaPhi *jet3 = new TFitParticleEtEtaPhi(j3, &m3);
  TFitParticleEtEtaPhi *jet4 = new TFitParticleEtEtaPhi(j4, &m4);
  
  // Constrain jet1 and jet2 to one H, and jet3 and jet4 to another
  TFitConstraintM *massConstraint1 = new TFitConstraintM("massConstraint1", "massConstraint1", 0, 0, mass1);
  massConstraint1->addParticles1(jet1, jet2);
  
  TFitConstraintM *massConstraint2 = new TFitConstraintM("massConstraint2", "massConstraint2", 0, 0, mass2);
  massConstraint2->addParticles1(jet3, jet4);
  
  // Call the fitter
  TKinFitter *fitter = new TKinFitter("fitter", "fitter");
  fitter->addMeasParticle(jet1);
  fitter->addMeasParticle(jet2);
  fitter->addMeasParticle(jet3);
  fitter->addMeasParticle(jet4);
  fitter->addConstraint(massConstraint1);
  fitter->addConstraint(massConstraint2);
  
  //Set convergence criteria
  fitter->setMaxNbIter(30);
  fitter->setMaxDeltaS(1e-2);
  fitter->setMaxF(1e-1);
  fitter->setVerbosity(3);
  
  // Fit
  fitter->fit();
  
  // Return and quit
  *j1 = TLorentzVector(*(fitter->get4Vec(0)));
  *j2 = TLorentzVector(*(fitter->get4Vec(1)));
  *j3 = TLorentzVector(*(fitter->get4Vec(2)));
  *j4 = TLorentzVector(*(fitter->get4Vec(3)));
  
  delete jet1;
  delete jet2;
  delete jet3;
  delete jet4;
  delete massConstraint1;
  delete massConstraint2;
  delete fitter;
  
  return 0;
}
