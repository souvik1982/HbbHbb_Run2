#include "fittedFunctions_GH.h"
#include "fittedFunctions2_GH.h"
#include "fittedFunctions3_GH.h"
#include "CSVsort.C"

double TurnOnDouble(float sumpt, float pt2, float pt4, float CSV1, float CSV2, float CSV3, float CSV4) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<-1?-1:CSV3;
    float calopt4 = DoubleJet_CaloPt4->Eval(pt4);
    float L1 = DoubleJet_L1->Eval(sumpt);
	float res = L1*calopt4*DoubleJet_CaloPt2->Eval(pt2)*CSVn(3, CSV1, CSV2, CSV3, CSV4)*DoubleJet_PFPt2->Eval(pt2)*DoubleJet_PFPt4->Eval(pt4);
    if( res < 0 ) return 0;
    return res;
}

double TurnOnDoubleUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<-1?-1:CSV3;

    CSV3 = -log(1-CSV3);
    float mu[6], sig[6];
    mu[0]=DoubleJet_L1->Eval(sumpt);
    sig[0]=DoubleJet_L1Up->Eval(sumpt)-mu[0];
    mu[1]=DoubleJet_CaloPt4->Eval(pt4);
    sig[1]=DoubleJet_CaloPt4Up->Eval(pt4)-mu[1];
    //mu[2]=CSVn(3, CSV1, CSV2, CSV3, CSV4);//DoubleJet_CSV3->Eval(CSV3);
    //sig[2]=DoubleJet_CSV3Up->Eval(CSV3)-mu[2];
    mu[2]=DoubleJet_PFPt4->Eval(pt4);
    sig[2]=DoubleJet_PFPt4Up->Eval(pt4)-mu[2];
    mu[3]=DoubleJet_PFPt2->Eval(pt2);
    sig[3]=DoubleJet_PFPt4Up->Eval(pt2)-mu[3];
    mu[4]=DoubleJet_CaloPt2->Eval(pt2);
    sig[4]=DoubleJet_CaloPt2Up->Eval(pt2)-mu[4];

    float sigma = 0, sigmaT, nom = 1;
    for( int i = 0; i < 5; i++ )
    {
        nom*=mu[i];
        sigmaT=sig[i];   
        for( int j = 0; j < 5; j++ )
            if( i != j ) sigmaT*=mu[j];
        sigma+=sigmaT*sigmaT;
    }
    float res = nom + sqrt(sigma);   

    if( res < 0 ) return 0;
    return res;
};

double TurnOnDoubleDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<-1?-1:CSV3;

    float mu[5], sig[5];
    mu[0]=DoubleJet_L1->Eval(sumpt);
    sig[0]=DoubleJet_L1Down->Eval(sumpt)-mu[0];
    mu[1]=DoubleJet_CaloPt4->Eval(pt4);
    sig[1]=DoubleJet_CaloPt4Down->Eval(pt4)-mu[1];
    //mu[2]=DoubleJet_CSV3->Eval(CSV3);
    //sig[2]=DoubleJet_CSV3Down->Eval(CSV3)-mu[2];
    mu[2]=DoubleJet_PFPt4->Eval(pt4);
    sig[2]=DoubleJet_PFPt4Down->Eval(pt4)-mu[2];
    mu[3]=DoubleJet_PFPt2->Eval(pt2);
    sig[3]=DoubleJet_PFPt4Down->Eval(pt2)-mu[3];
    mu[4]=DoubleJet_CaloPt2->Eval(pt2);
    sig[4]=DoubleJet_CaloPt2Down->Eval(pt2)-mu[4];

    float sigma = 0, sigmaT, nom = 1;
    for( int i = 0; i < 5; i++ )
    {
        nom*=mu[i];
        sigmaT=sig[i];   
        for( int j = 0; j < 5; j++ )
            if( i != j ) sigmaT*=mu[j];
        sigma+=sigmaT*sigmaT;
    }
    float res = nom - sqrt(sigma);   


    if( res < 0 ) return 0;
    return res;
}

double QuaJet_L1_(float sumpt){
    return QuaJet_L1->Eval(sumpt);
}
double TurnOnQuad(float sumpt, float pt2, float pt4, float CSV1, float CSV2, float CSV3, float CSV4) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<-1?-1:CSV3;
    float calopt4 = QuaJet_CaloPt4->Eval(pt4);
    float L1  =QuaJet_L1->Eval(sumpt);
//    L1  =1;
//    calopt4 = 1;
    
	float res =  L1*calopt4*CSVn(3, CSV1, CSV2, CSV3, CSV4)*QuaJet_PFPt4->Eval(pt4);
//	float res =  QuaJet_CSV3->Eval(CSV3)*QuaJet_PFPt4->Eval(pt4);
    if( res < 0 ) return 0;
    return res;
}

double TurnOnQuadUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<-1?-1:CSV3;
    float mu[4], sig[4];
    mu[0]=QuaJet_L1->Eval(sumpt);
    sig[0]=QuaJet_L1Up->Eval(sumpt)-mu[0];
    mu[1]=QuaJet_CaloPt4->Eval(pt4);
    sig[1]=QuaJet_CaloPt4Up->Eval(pt4)-mu[1];
    //mu[2]=QuaJet_CSV3->Eval(CSV3);
    //sig[2]=QuaJet_CSV3Up->Eval(CSV3)-mu[2];
    mu[2]=QuaJet_PFPt4->Eval(pt4);
    sig[2]=QuaJet_PFPt4Up->Eval(pt4)-mu[2];

    float sigma = 0, sigmaT, nom = 1;
    for( int i = 0; i < 3; i++ )
    {
        nom*=mu[i];
        sigmaT=sig[i];   
        for( int j = 0; j < 3; j++ )
            if( i != j ) sigmaT*=mu[j];
        sigma+=sigmaT*sigmaT;
    }
    float res = nom + sqrt(sigma);    

    if( res < 0 ) return 0;
    return res;
}

double TurnOnQuadDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<-1?-1:CSV3;

    float mu[4], sig[4];
    mu[0]=QuaJet_L1->Eval(sumpt);
    sig[0]=QuaJet_L1Down->Eval(sumpt)-mu[0];
    mu[1]=QuaJet_CaloPt4->Eval(pt4);
    sig[1]=QuaJet_CaloPt4Down->Eval(pt4)-mu[1];
 //   mu[2]=QuaJet_CSV3->Eval(CSV3);
 //   sig[2]=QuaJet_CSV3Down->Eval(CSV3)-mu[2];
    mu[2]=QuaJet_PFPt4->Eval(pt4);
    sig[2]=QuaJet_PFPt4Down->Eval(pt4)-mu[2];

    float sigma = 0, sigmaT, nom = 1;
    for( int i = 0; i < 3; i++ )
    {
        nom*=mu[i];
        sigmaT=sig[i];   
        for( int j = 0; j < 3; j++ )
            if( i != j ) sigmaT*=mu[j];
        sigma+=sigmaT*sigmaT;
    }
    float res = nom - sqrt(sigma);  

    if( res < 0 ) return 0;
    return res;
}

double QaD_TurnOnQuad(float sumpt, float pt2, float pt4, float CSV1, float CSV2, float CSV3, float CSV4) {
	float res =  QaD_DoubleJet_L1->Eval(sumpt)*QaD_DoubleJet_PFPt2->Eval(pt2)*QaD_DoubleJet_CaloPt2->Eval(pt2);//*CSVn(3, CSV1, CSV2, CSV3, CSV4);
    if( res < 0 ) return 0;
    return res;
}

double QaD_TurnOnQuadUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<-1?-1:CSV3;

    float mu[4], sig[4];
 //   mu[0]=QaD_QuaJet_L1->Eval(sumpt);
 //   sig[0]=QaD_QuaJet_L1Up->Eval(sumpt)-mu[0];
    mu[1]=QaD_DoubleJet_CaloPt2->Eval(pt2);
    sig[1]=QaD_DoubleJet_CaloPt2Up->Eval(pt2)-mu[1];
   // mu[2]=QaD_QuaJet_CSV3->Eval(CSV3);
  //  sig[2]=QaD_QuaJet_CSV3Up->Eval(CSV3)-mu[2];
    mu[2]=QaD_DoubleJet_PFPt2->Eval(pt2);
    sig[2]=QaD_DoubleJet_PFPt2Up->Eval(pt2)-mu[2];

    float sigma = 0, sigmaT, nom = 1;
    for( int i = 1; i < 3; i++ )
    {
        nom*=mu[i];
        sigmaT=sig[i];   
        for( int j = 1; j < 3; j++ )
            if( i != j ) sigmaT*=mu[j];
        sigma+=sigmaT*sigmaT;
    }
    float res = nom + sqrt(sigma);  

    if( res < 0 ) return 0;
    return res;
}

double QaD_TurnOnQuadDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<-1?-1:CSV3;
    CSV3 = -log(1-CSV3);
    float mu[4], sig[4];
 //   mu[0]=QaD_QuaJet_L1->Eval(sumpt);
 //   sig[0]=QaD_QuaJet_L1Down->Eval(sumpt)-mu[0];
    mu[1]=QaD_DoubleJet_CaloPt2->Eval(pt2);
    sig[1]=QaD_DoubleJet_CaloPt2Down->Eval(pt2)-mu[1];
  //  mu[2]=QaD_QuaJet_CSV3->Eval(CSV3);
  //  sig[2]=QaD_QuaJet_CSV3Down->Eval(CSV3)-mu[2];
    mu[2]=QaD_DoubleJet_PFPt2->Eval(pt2);
    sig[2]=QaD_DoubleJet_PFPt2Down->Eval(pt2)-mu[2];

    float sigma = 0, sigmaT, nom = 1;
    for( int i = 1; i < 3; i++ )
    {
        nom*=mu[i];
        sigmaT=sig[i];   
        for( int j = 1; j < 3; j++ )
            if( i != j ) sigmaT*=mu[j];
        sigma+=sigmaT*sigmaT;
    }
    float res = nom - sqrt(sigma);  

    if( res < 0 ) return 0;
    return res;
}


