#include <TLorentzVector.h>

int purityTest(TLorentzVector j[4], TLorentzVector b[4], int jMatchedbindex[4])
{
  int purity=-2; // reflects how many jets are matched. 
  // If -1, that means multiple b were matched most closely to the same j
  
  int nMatches=0;
  for (unsigned int i_j=0; i_j<4; ++i_j)
  {
    double mindR=0.4;
    for (unsigned int i_b=0; i_b<4; ++i_b)
    {
      double dR=j[i_j].DeltaR(b[i_b]);
      if (dR<mindR)
      {
        mindR=dR;
        jMatchedbindex[i_j]=i_b;
      } 
    }
    if (jMatchedbindex[i_j]!=-1) // Match has happened
    {
      for (unsigned int i_i_j=0; i_i_j<i_j; ++i_i_j)
      {
        if (jMatchedbindex[i_j]==jMatchedbindex[i_i_j]) return -1;
      }
      ++nMatches;
    }
  }
  
  return nMatches;
}
