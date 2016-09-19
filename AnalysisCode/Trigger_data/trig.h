#include "fittedFunctions_.h"
#include "fittedFunctions2_.h"
#include "fittedFunctions3_.h"

double TurnOnDouble(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4 = DoubleJet_CaloPt4h->Eval(pt4);
    float L1 = DoubleJet_L1h->Eval(sumpt);
	float res = L1*calopt4*DoubleJet_CaloPt2->Eval(pt2)*DoubleJet_CSV3->Eval(CSV3)*DoubleJet_PFPt4->Eval(pt4)*DoubleJet_PFPt2->Eval(pt2);
    if( res < 0 ) return 0;
    return res;
}

double TurnOnDoubleUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;

    float mu[6], sig[6];
    mu[0]=DoubleJet_L1h->Eval(sumpt);
    sig[0]=DoubleJet_L1hUp->Eval(sumpt)-mu[0];
    mu[1]=DoubleJet_CaloPt4h->Eval(pt4);
    sig[1]=DoubleJet_CaloPt4hUp->Eval(pt4)-mu[1];
    mu[2]=DoubleJet_CSV3->Eval(CSV3);
    sig[2]=DoubleJet_CSV3Up->Eval(CSV3)-mu[2];
    mu[3]=DoubleJet_PFPt4->Eval(pt4);
    sig[3]=DoubleJet_PFPt4Up->Eval(pt4)-mu[3];
    mu[4]=DoubleJet_PFPt2->Eval(pt2);
    sig[4]=DoubleJet_PFPt4Up->Eval(pt2)-mu[4];
    mu[5]=DoubleJet_CaloPt2->Eval(pt2);
    sig[5]=DoubleJet_CaloPt2Up->Eval(pt2)-mu[5];

    float sigma = 0, sigmaT, nom = 1;
    for( int i = 0; i < 6; i++ )
    {
        nom*=mu[i];
        sigmaT=sig[i];   
        for( int j = 0; j < 6; j++ )
            if( i != j ) sigmaT*=mu[j];
        sigma+=sigmaT*sigmaT;
    }
    float res = nom + sqrt(sigma);   

    if( res < 0 ) return 0;
    return res;
};

double TurnOnDoubleDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;

    float mu[6], sig[6];
    mu[0]=DoubleJet_L1h->Eval(sumpt);
    sig[0]=DoubleJet_L1hDown->Eval(sumpt)-mu[0];
    mu[1]=DoubleJet_CaloPt4h->Eval(pt4);
    sig[1]=DoubleJet_CaloPt4hDown->Eval(pt4)-mu[1];
    mu[2]=DoubleJet_CSV3->Eval(CSV3);
    sig[2]=DoubleJet_CSV3Down->Eval(CSV3)-mu[2];
    mu[3]=DoubleJet_PFPt4->Eval(pt4);
    sig[3]=DoubleJet_PFPt4Down->Eval(pt4)-mu[3];
    mu[4]=DoubleJet_PFPt2->Eval(pt2);
    sig[4]=DoubleJet_PFPt4Down->Eval(pt2)-mu[4];
    mu[5]=DoubleJet_CaloPt2->Eval(pt2);
    sig[5]=DoubleJet_CaloPt2Down->Eval(pt2)-mu[5];

    float sigma = 0, sigmaT, nom = 1;
    for( int i = 0; i < 6; i++ )
    {
        nom*=mu[i];
        sigmaT=sig[i];   
        for( int j = 0; j < 6; j++ )
            if( i != j ) sigmaT*=mu[j];
        sigma+=sigmaT*sigmaT;
    }
    float res = nom - sqrt(sigma);   


    if( res < 0 ) return 0;
    return res;
}

double TurnOnQuad(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4 = QuaJet_CaloPt4h->Eval(pt4);
    float L1  =QuaJet_L1h->Eval(sumpt);
	float res =  L1*calopt4*QuaJet_CSV3->Eval(CSV3)*QuaJet_PFPt4->Eval(pt4);
    if( res < 0 ) return 0;
    return res;
}

double TurnOnQuadUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float mu[4], sig[4];
    mu[0]=QuaJet_L1h->Eval(sumpt);
    sig[0]=QuaJet_L1hUp->Eval(sumpt)-mu[0];
    mu[1]=QuaJet_CaloPt4h->Eval(pt4);
    sig[1]=QuaJet_CaloPt4hUp->Eval(pt4)-mu[1];
    mu[2]=QuaJet_CSV3->Eval(CSV3);
    sig[2]=QuaJet_CSV3Up->Eval(CSV3)-mu[2];
    mu[3]=QuaJet_PFPt4->Eval(pt4);
    sig[3]=QuaJet_PFPt4Up->Eval(pt4)-mu[3];

    float sigma = 0, sigmaT, nom = 1;
    for( int i = 0; i < 4; i++ )
    {
        nom*=mu[i];
        sigmaT=sig[i];   
        for( int j = 0; j < 4; j++ )
            if( i != j ) sigmaT*=mu[j];
        sigma+=sigmaT*sigmaT;
    }
    float res = nom + sqrt(sigma);    

    if( res < 0 ) return 0;
    return res;
}

double TurnOnQuadDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;

    float mu[4], sig[4];
    mu[0]=QuaJet_L1h->Eval(sumpt);
    sig[0]=QuaJet_L1hDown->Eval(sumpt)-mu[0];
    mu[1]=QuaJet_CaloPt4h->Eval(pt4);
    sig[1]=QuaJet_CaloPt4hDown->Eval(pt4)-mu[1];
    mu[2]=QuaJet_CSV3->Eval(CSV3);
    sig[2]=QuaJet_CSV3Down->Eval(CSV3)-mu[2];
    mu[3]=QuaJet_PFPt4->Eval(pt4);
    sig[3]=QuaJet_PFPt4Down->Eval(pt4)-mu[3];

    float sigma = 0, sigmaT, nom = 1;
    for( int i = 0; i < 4; i++ )
    {
        nom*=mu[i];
        sigmaT=sig[i];   
        for( int j = 0; j < 4; j++ )
            if( i != j ) sigmaT*=mu[j];
        sigma+=sigmaT*sigmaT;
    }
    float res = nom - sqrt(sigma);  

    if( res < 0 ) return 0;
    return res;
}

double QaD_TurnOnQuad(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    /*  if(pt4<55) calopt4 = QaD_QuaJet_CaloPt4l->Eval(pt4);
    else  */ calopt4 = QaD_QuaJet_CaloPt4h->Eval(pt4);
    float L1;
    /*   if(sumpt<210) L1 = QaD_QuaJet_L1l->Eval(sumpt);
    else  */ L1=QaD_QuaJet_L1h->Eval(sumpt);
	float res =  L1*calopt4*QaD_QuaJet_CSV3->Eval(CSV3)*QaD_QuaJet_PFPt4->Eval(pt4);
    if( res < 0 ) return 0;
    return res;
}

double QaD_TurnOnQuadUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;

    float mu[4], sig[4];
    mu[0]=QaD_QuaJet_L1h->Eval(sumpt);
    sig[0]=QaD_QuaJet_L1hUp->Eval(sumpt)-mu[0];
    mu[1]=QaD_QuaJet_CaloPt4h->Eval(pt4);
    sig[1]=QaD_QuaJet_CaloPt4hUp->Eval(pt4)-mu[1];
    mu[2]=QaD_QuaJet_CSV3->Eval(CSV3);
    sig[2]=QaD_QuaJet_CSV3Up->Eval(CSV3)-mu[2];
    mu[3]=QaD_QuaJet_PFPt4->Eval(pt4);
    sig[3]=QaD_QuaJet_PFPt4Up->Eval(pt4)-mu[3];

    float sigma = 0, sigmaT, nom = 1;
    for( int i = 0; i < 4; i++ )
    {
        nom*=mu[i];
        sigmaT=sig[i];   
        for( int j = 0; j < 4; j++ )
            if( i != j ) sigmaT*=mu[j];
        sigma+=sigmaT*sigmaT;
    }
    float res = nom + sqrt(sigma);  

    if( res < 0 ) return 0;
    return res;
}

double QaD_TurnOnQuadDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float mu[4], sig[4];
    mu[0]=QaD_QuaJet_L1h->Eval(sumpt);
    sig[0]=QaD_QuaJet_L1hDown->Eval(sumpt)-mu[0];
    mu[1]=QaD_QuaJet_CaloPt4h->Eval(pt4);
    sig[1]=QaD_QuaJet_CaloPt4hDown->Eval(pt4)-mu[1];
    mu[2]=QaD_QuaJet_CSV3->Eval(CSV3);
    sig[2]=QaD_QuaJet_CSV3Down->Eval(CSV3)-mu[2];
    mu[3]=QaD_QuaJet_PFPt4->Eval(pt4);
    sig[3]=QaD_QuaJet_PFPt4Down->Eval(pt4)-mu[3];

    float sigma = 0, sigmaT, nom = 1;
    for( int i = 0; i < 4; i++ )
    {
        nom*=mu[i];
        sigmaT=sig[i];   
        for( int j = 0; j < 4; j++ )
            if( i != j ) sigmaT*=mu[j];
        sigma+=sigmaT*sigmaT;
    }
    float res = nom - sqrt(sigma);  

    if( res < 0 ) return 0;
    return res;
}


