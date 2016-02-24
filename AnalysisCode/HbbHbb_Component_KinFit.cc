#include "PhysicsTools/KinFitter/interface/TFitConstraintM.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleEtEtaPhi.h"
#include "PhysicsTools/KinFitter/interface/TKinFitter.h"

#include "TLorentzVector.h"

#include <iostream>

double ErrpT_Signal(double pT, double eta)
{
  double sigmapT=0;
  if (fabs(eta)<1.4)
  {
    sigmapT = 25 + 0.0017*pT + 0.00009*pT*pT;
  }
  else
  {
    sigmapT = 19.9 + 0.045 * pT;
  }
  return sigmapT*sigmapT;
}

double ErrEta_Signal(double pT)
{
  double sigmaEta = 0.034 + (4.20/pT) + (-0.23/pow(pT,0.5));
  return sigmaEta*sigmaEta;
}

double ErrPhi_Signal(double pT)
{
  double sigmaPhi = 0.043 + (4.76/pT) + (-0.35/pow(pT,0.5));
  return sigmaPhi*sigmaPhi;
}

TLorentzVector biasEt_signal(TLorentzVector j)
{
  double pT=j.Pt();
  double eta=j.Eta();
  double newpT=-1;
  if (fabs(eta)<1.4)
  {
    newpT = pT - (-17.6 + 0.03*pT + 0.00009*pT*pT);
  }
  else
  {
    newpT = pT - (-15.4 - 0.02*pT + 0.0001*pT*pT);
  }
  
  TLorentzVector jNew;
  jNew.SetPtEtaPhiM(newpT, eta, j.Phi(), j.M());
  
  return jNew;
}

double constrainHH_signalMeasurement(TLorentzVector *j1, TLorentzVector *j2, TLorentzVector *j3, TLorentzVector *j4, double mass1=125, double mass2=125)
{
  TMatrixD m1(3,3);
  TMatrixD m2(3,3);
  TMatrixD m3(3,3);
  TMatrixD m4(3,3);
  m1.Zero();
  m2.Zero();
  m3.Zero();
  m4.Zero();
  
  m1(0,0) = ErrpT_Signal(j1->Et(), j1->Eta());
  m1(1,1) = ErrEta_Signal(j1->Et());
  m1(2,2) = ErrPhi_Signal(j1->Et());
  
  m2(0,0) = ErrpT_Signal(j2->Et(), j2->Eta());
  m2(1,1) = ErrEta_Signal(j2->Et());
  m2(2,2) = ErrPhi_Signal(j2->Et());
  
  m3(0,0) = ErrpT_Signal(j3->Et(), j3->Eta());
  m3(1,1) = ErrEta_Signal(j3->Et());
  m3(2,2) = ErrPhi_Signal(j3->Et());
  
  m4(0,0) = ErrpT_Signal(j4->Et(), j4->Eta());
  m4(1,1) = ErrEta_Signal(j4->Et());
  m4(2,2) = ErrPhi_Signal(j4->Et());
  
  // TLorentzVector j1_new=biasEt_signal(*j1);
  // TLorentzVector j2_new=biasEt_signal(*j2);
  // TLorentzVector j3_new=biasEt_signal(*j3);
  // TLorentzVector j4_new=biasEt_signal(*j4);
   
  TFitParticleEtEtaPhi *jet1 = new TFitParticleEtEtaPhi(j1, &m1);
  TFitParticleEtEtaPhi *jet2 = new TFitParticleEtEtaPhi(j2, &m2);
  TFitParticleEtEtaPhi *jet3 = new TFitParticleEtEtaPhi(j3, &m3);
  TFitParticleEtEtaPhi *jet4 = new TFitParticleEtEtaPhi(j4, &m4);
  
  TFitConstraintM *massConstraint1 = new TFitConstraintM("massConstraint1", "massConstraint1", 0, 0, mass1);
  massConstraint1->addParticles1(jet1, jet2);
  
  TFitConstraintM *massConstraint2 = new TFitConstraintM("massConstraint2", "massConstraint2", 0, 0, mass2);
  massConstraint2->addParticles1(jet3, jet4);
  
  TKinFitter *fitter = new TKinFitter("fitter", "fitter");
  fitter->addMeasParticle(jet1);
  fitter->addMeasParticle(jet2);
  fitter->addMeasParticle(jet3);
  fitter->addMeasParticle(jet4);
  fitter->addConstraint(massConstraint1);
  fitter->addConstraint(massConstraint2);
  
  fitter->setMaxNbIter(30);
  fitter->setMaxDeltaS(1e-2);
  fitter->setMaxF(1e-1);
  fitter->setVerbosity(3);
  
  fitter->fit();
  
  double chi2=fitter->getS();
  
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
  
  return chi2;
}

double constrainHH_afterRegression(TLorentzVector *j1, TLorentzVector *j2, TLorentzVector *j3, TLorentzVector *j4, double mass1=125, double mass2=125)
{
  TMatrixD m1(3,3);
  TMatrixD m2(3,3);
  TMatrixD m3(3,3);
  TMatrixD m4(3,3);
  m1.Zero();
  m2.Zero();
  m3.Zero();
  m4.Zero();
  
  m1(0,0) = ErrpT_Signal(j1->Et(), j1->Eta());
  m1(1,1) = ErrEta_Signal(j1->Et());
  m1(2,2) = ErrPhi_Signal(j1->Et());
  
  m2(0,0) = ErrpT_Signal(j2->Et(), j2->Eta());
  m2(1,1) = ErrEta_Signal(j2->Et());
  m2(2,2) = ErrPhi_Signal(j2->Et());
  
  m3(0,0) = ErrpT_Signal(j3->Et(), j3->Eta());
  m3(1,1) = ErrEta_Signal(j3->Et());
  m3(2,2) = ErrPhi_Signal(j3->Et());
  
  m4(0,0) = ErrpT_Signal(j4->Et(), j4->Eta());
  m4(1,1) = ErrEta_Signal(j4->Et());
  m4(2,2) = ErrPhi_Signal(j4->Et());
  
  TFitParticleEtEtaPhi *jet1 = new TFitParticleEtEtaPhi(j1, &m1);
  TFitParticleEtEtaPhi *jet2 = new TFitParticleEtEtaPhi(j2, &m2);
  TFitParticleEtEtaPhi *jet3 = new TFitParticleEtEtaPhi(j3, &m3);
  TFitParticleEtEtaPhi *jet4 = new TFitParticleEtEtaPhi(j4, &m4);
  
  TFitConstraintM *massConstraint1 = new TFitConstraintM("massConstraint1", "massConstraint1", 0, 0, mass1);
  massConstraint1->addParticles1(jet1, jet2);
  
  TFitConstraintM *massConstraint2 = new TFitConstraintM("massConstraint2", "massConstraint2", 0, 0, mass2);
  massConstraint2->addParticles1(jet3, jet4);
  
  TKinFitter *fitter = new TKinFitter("fitter", "fitter");
  fitter->addMeasParticle(jet1);
  fitter->addMeasParticle(jet2);
  fitter->addMeasParticle(jet3);
  fitter->addMeasParticle(jet4);
  fitter->addConstraint(massConstraint1);
  fitter->addConstraint(massConstraint2);
  
  fitter->setMaxNbIter(30);
  fitter->setMaxDeltaS(1e-2);
  fitter->setMaxF(1e-1);
  fitter->setVerbosity(3);
  
  fitter->fit();
  
  double chi2=fitter->getS();
  
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
  
  return chi2;
}

double constrainHH_check(TLorentzVector *j1, TLorentzVector *j2, TLorentzVector *j3, TLorentzVector *j4, double mass1=125, double mass2=125)
{
  TMatrixD m1(3,3);
  TMatrixD m2(3,3);
  TMatrixD m3(3,3);
  TMatrixD m4(3,3);
  m1.Zero();
  m2.Zero();
  m3.Zero();
  m4.Zero();
  
  m1(0,0) = 5;
  m1(1,1) = 0.1;
  m1(2,2) = 0.1;
  
  m2(0,0) = 5;
  m2(1,1) = 0.1;
  m2(2,2) = 0.1;
  
  m3(0,0) = 5;
  m3(1,1) = 0.1;
  m3(2,2) = 0.1;
  
  m4(0,0) = 5;
  m4(1,1) = 0.1;
  m4(2,2) = 0.1;
  
  TFitParticleEtEtaPhi *jet1 = new TFitParticleEtEtaPhi(j1, &m1);
  TFitParticleEtEtaPhi *jet2 = new TFitParticleEtEtaPhi(j2, &m2);
  TFitParticleEtEtaPhi *jet3 = new TFitParticleEtEtaPhi(j3, &m3);
  TFitParticleEtEtaPhi *jet4 = new TFitParticleEtEtaPhi(j4, &m4);
  
  TFitConstraintM *massConstraint1 = new TFitConstraintM("massConstraint1", "massConstraint1", 0, 0, mass1);
  massConstraint1->addParticles1(jet1, jet2);
  
  TFitConstraintM *massConstraint2 = new TFitConstraintM("massConstraint2", "massConstraint2", 0, 0, mass2);
  massConstraint2->addParticles1(jet3, jet4);
  
  TKinFitter *fitter = new TKinFitter("fitter", "fitter");
  fitter->addMeasParticle(jet1);
  fitter->addMeasParticle(jet2);
  fitter->addMeasParticle(jet3);
  fitter->addMeasParticle(jet4);
  fitter->addConstraint(massConstraint1);
  fitter->addConstraint(massConstraint2);
  
  fitter->setMaxNbIter(30);
  fitter->setMaxDeltaS(1e-2);
  fitter->setMaxF(1e-1);
  fitter->setVerbosity(3);
  
  fitter->fit();
  
  double chi2=fitter->getS();
  
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
  
  return chi2;
}
