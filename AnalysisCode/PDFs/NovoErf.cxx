/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                            *
 * This code was autogenerated by RooClassFactory                            *
 ******************************************************************************/

// Your description goes here... 

#include "Riostream.h" 

#include "NovoErf.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(NovoErf) 

 NovoErf::NovoErf(const char *name, const char *title, 
                 RooAbsReal& _x,
                 RooAbsReal& _p0,
                 RooAbsReal& _p1) :

   RooAbsPdf(name,title), 
   x("x","x",this,_x),
   p0("p0","p0",this,_p0),
   p1("p1","p1",this,_p1)

 { 
 } 


 NovoErf::NovoErf(const NovoErf& other, const char* name) :  
   RooAbsPdf(other,name), 
   x("x",this,other.x),
   p0("p0",this,other.p0),
   p1("p1",this,other.p1)
 { 
 } 

Double_t NovoErf::evaluate() const
{
   Double_t result=0.5*TMath::Erf(p0*(p1-x)+1);
   return result;
}



