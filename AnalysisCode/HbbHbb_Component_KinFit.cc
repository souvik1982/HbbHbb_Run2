#include "PhysicsTools/KinFitter/interface/TFitConstraintM.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleEt.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleEtEtaPhi.h"
#include "PhysicsTools/KinFitter/interface/TKinFitter.h"

#include "TLorentzVector.h"

#include <iostream>

double ErrEt_Signal(double ET, double eta)
{
  double sigmapT=0;
  if (fabs(eta)<1.4)
  {
    sigmapT = 18.5 + 0.042 * ET;
  }
  else
  {
    sigmapT = 18 + 0.037 * ET;
  }
  return sigmapT*sigmapT;
}

double ErrEta_Signal(double ET)
{
  double sigmaEta = 0.024 + (2.91/ET);
  return sigmaEta*sigmaEta;
}

double ErrPhi_Signal(double ET)
{
  double sigmaPhi=0.029 + (2.71/ET);
  return sigmaPhi*sigmaPhi;
}

TLorentzVector biasEt_signal(TLorentzVector j)
{
  double pT=j.Pt();
  double eta=j.Eta();
  double newpT=-1;
  if (fabs(eta)<1.4)
  {
    newpT = pT - (-14.6 + 0.016*pT + 0.00016*pT*pT);
  }
  else
  {
    newpT = pT - (-12.6 - 0.0039*pT + 0.00024*pT*pT);
  }
  
  TLorentzVector jNew;
  jNew.SetPtEtaPhiM(newpT, eta, j.Phi(), j.M());
  
  return jNew;
}

double constrainHH_signalMeasurement(TLorentzVector *j1, TLorentzVector *j2, TLorentzVector *j3, TLorentzVector *j4, double mass1=125, double mass2=125)
{
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
  m1(0,0) = ErrEt_Signal(j1->Et(), j1->Eta());
  m1(1,1) = ErrEta_Signal(j1->Et());
  m1(2,2) = ErrPhi_Signal(j1->Et());
  
  m2(0,0) = ErrEt_Signal(j2->Et(), j2->Eta());
  m2(1,1) = ErrEta_Signal(j2->Et());
  m2(2,2) = ErrPhi_Signal(j2->Et());
  
  m3(0,0) = ErrEt_Signal(j3->Et(), j3->Eta());
  m3(1,1) = ErrEta_Signal(j3->Et());
  m3(2,2) = ErrPhi_Signal(j3->Et());
  
  m4(0,0) = ErrEt_Signal(j4->Et(), j4->Eta());
  m4(1,1) = ErrEta_Signal(j4->Et());
  m4(2,2) = ErrPhi_Signal(j4->Et());
  
  // Correct the jet energies for bias
  TLorentzVector j1_new=biasEt_signal(*j1);
  TLorentzVector j2_new=biasEt_signal(*j2);
  TLorentzVector j3_new=biasEt_signal(*j3);
  TLorentzVector j4_new=biasEt_signal(*j4);
  
  TFitParticleEtEtaPhi *jet1 = new TFitParticleEtEtaPhi(&j1_new, &m1);
  TFitParticleEtEtaPhi *jet2 = new TFitParticleEtEtaPhi(&j2_new, &m2);
  TFitParticleEtEtaPhi *jet3 = new TFitParticleEtEtaPhi(&j3_new, &m3);
  TFitParticleEtEtaPhi *jet4 = new TFitParticleEtEtaPhi(&j4_new, &m4);
  
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
  
  // chi^2
  double chi2=fitter->getS();
  
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
  
  return chi2;
}
