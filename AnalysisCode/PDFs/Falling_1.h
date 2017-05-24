/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                            *
  * This code was autogenerated by RooClassFactory                            * 
 ******************************************************************************/

#ifndef FALLING_h_1
#define FALLING_h_1

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class Falling_1 : public RooAbsPdf {
public:
  Falling_1() {} ; 
  Falling_1(const char *name, const char *title,
	      RooAbsReal& _x,
	      RooAbsReal& _p0,
	      RooAbsReal& _p1,
	      RooAbsReal& _p2);
  Falling_1(const Falling_1& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new Falling_1(*this,newname); }
  inline virtual ~Falling_1() { }

protected:

  RooRealProxy x ;
  RooRealProxy p0 ;
  RooRealProxy p1 ;
  RooRealProxy p2 ;
  
  Double_t evaluate() const ;

private:

  ClassDef(Falling_1,1) // Your description goes here...
};
 
#endif
