#include "fittedFunctions_.h"
#include "fittedFunctions2_.h"
#include "fittedFunctions3_.h"

double TurnOnDouble(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
   /* if(pt4<45) calopt4 = DoubleJet_CaloPt4l->Eval(pt4);
    else */calopt4 = DoubleJet_CaloPt4h->Eval(pt4);
    float L1;
    /*if(sumpt<120) L1 = DoubleJet_L1l->Eval(sumpt);
    else*/ L1=DoubleJet_L1h->Eval(sumpt);
	float res = L1*calopt4*DoubleJet_CaloPt2->Eval(pt2)*DoubleJet_CSV3->Eval(CSV3)*DoubleJet_PFPt4->Eval(pt4)*DoubleJet_PFPt2->Eval(pt2);
    if( res < 0 ) return 0;
    return res;
}

double TurnOnDoubleUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    /* if(pt4<45) calopt4 = DoubleJet_CaloPt4lUp->Eval(pt4);
    else*/  calopt4 = DoubleJet_CaloPt4hUp->Eval(pt4);
    float L1;
    /* if(sumpt<120) L1 = DoubleJet_L1lUp->Eval(sumpt);
    else*/  L1=DoubleJet_L1hUp->Eval(sumpt);
	float res =  L1*calopt4*DoubleJet_CaloPt2Up->Eval(pt2)*DoubleJet_CSV3Up->Eval(CSV3)*DoubleJet_PFPt4Up->Eval(pt4)*DoubleJet_PFPt2Up->Eval(pt2);
    if( res < 0 ) return 0;
    return res;
};

double TurnOnDoubleDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    /* if(pt4<45) calopt4 = DoubleJet_CaloPt4lDown->Eval(pt4);
    else*/  calopt4 = DoubleJet_CaloPt4hDown->Eval(pt4);
    float L1;
    /* if(sumpt<120) L1 = DoubleJet_L1lDown->Eval(sumpt);
    else*/  L1=DoubleJet_L1hDown->Eval(sumpt);
	float res =  L1*calopt4*DoubleJet_CaloPt2Down->Eval(pt2)*DoubleJet_CSV3Down->Eval(CSV3)*DoubleJet_PFPt4Down->Eval(pt4)*DoubleJet_PFPt2Down->Eval(pt2);
    if( res < 0 ) return 0;
    return res;
}

double TurnOnQuad(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
     /* if(pt4<70) calopt4 = QuaJet_CaloPt4l->Eval(pt4);
    else */ calopt4 = QuaJet_CaloPt4h->Eval(pt4);
    float L1;
  /*  if(sumpt<100) L1 = QuaJet_L1l->Eval(sumpt);
    else*/ L1=QuaJet_L1h->Eval(sumpt);
	float res =  L1*calopt4*QuaJet_CSV3->Eval(CSV3)*QuaJet_PFPt4->Eval(pt4);
    if( res < 0 ) return 0;
    return res;
}

double TurnOnQuadUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
     /* if(pt4<70) calopt4 = QuaJet_CaloPt4lUp->Eval(pt4);
    else  */ calopt4 = QuaJet_CaloPt4hUp->Eval(pt4);
    float L1;
    /*  if(sumpt<100) L1 = QuaJet_L1lUp->Eval(sumpt);
    else*/ L1=QuaJet_L1hUp->Eval(sumpt);
	float res =  L1*calopt4*QuaJet_CSV3Up->Eval(CSV3)*QuaJet_PFPt4Up->Eval(pt4);
    if( res < 0 ) return 0;
    return res;
}

double TurnOnQuadDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
   /*   if(pt4<70) calopt4 = QuaJet_CaloPt4lDown->Eval(pt4);
    else  */ calopt4 = QuaJet_CaloPt4hDown->Eval(pt4);
    float L1;
    /*  if(sumpt<100) L1 = QuaJet_L1lDown->Eval(sumpt);
    else*/ L1=QuaJet_L1hDown->Eval(sumpt);
	float res =  L1*calopt4*QuaJet_CSV3Down->Eval(CSV3)*QuaJet_PFPt4Down->Eval(pt4);
    if( res < 0 ) return 0;
    return res;
}

/*
double QaD_TurnOnDouble(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<45) calopt4 = QaD_DoubleJet_CaloPt4l->Eval(pt4);
    else calopt4 = QaD_DoubleJet_CaloPt4h->Eval(pt4);
    float L1;
    if(sumpt<120) L1 = QaD_DoubleJet_L1l->Eval(sumpt);
    else L1=QaD_DoubleJet_L1h->Eval(sumpt);
	float res =  L1*calopt4*QaD_DoubleJet_CaloPt2->Eval(pt2)*QaD_DoubleJet_CSV3->Eval(CSV3)*QaD_DoubleJet_PFPt4->Eval(pt4)*QaD_DoubleJet_PFPt2->Eval(pt2);
    if( res < 0 ) return 0;
    return res;
}

double QaD_TurnOnDoubleUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<45) calopt4 = QaD_DoubleJet_CaloPt4lUp->Eval(pt4);
    else calopt4 = QaD_DoubleJet_CaloPt4hUp->Eval(pt4);
    float L1;
    if(sumpt<120) L1 = QaD_DoubleJet_L1lUp->Eval(sumpt);
    else L1=QaD_DoubleJet_L1hUp->Eval(sumpt);
	float res =  L1*calopt4*QaD_DoubleJet_CaloPt2Up->Eval(pt2)*QaD_DoubleJet_CSV3Up->Eval(CSV3)*QaD_DoubleJet_PFPt4Up->Eval(pt4)*QaD_DoubleJet_PFPt2Up->Eval(pt2);
    if( res < 0 ) return 0;
    return res;
};

double QaD_TurnOnDoubleDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<45) calopt4 = QaD_DoubleJet_CaloPt4lDown->Eval(pt4);
    else calopt4 = QaD_DoubleJet_CaloPt4hDown->Eval(pt4);
    float L1;
    if(sumpt<120) L1 = QaD_DoubleJet_L1lDown->Eval(sumpt);
    else L1=QaD_DoubleJet_L1hDown->Eval(sumpt);
	float res =  L1*calopt4*QaD_DoubleJet_CaloPt2Down->Eval(pt2)*QaD_DoubleJet_CSV3Down->Eval(CSV3)*QaD_DoubleJet_PFPt4Down->Eval(pt4)*QaD_DoubleJet_PFPt2Down->Eval(pt2);
    if( res < 0 ) return 0;
    return res;
}*/

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
    float calopt4;
    /*     if(pt4<55) calopt4 = QaD_QuaJet_CaloPt4lUp->Eval(pt4);
    else  */  calopt4 = QaD_QuaJet_CaloPt4hUp->Eval(pt4);
    float L1;
    /*   if(sumpt<210) L1 = QaD_QuaJet_L1lUp->Eval(sumpt);
    else */  L1=QaD_QuaJet_L1hUp->Eval(sumpt);
	float res =  L1*calopt4*QaD_QuaJet_CSV3Up->Eval(CSV3)*QaD_QuaJet_PFPt4Up->Eval(pt4);
    if( res < 0 ) return 0;
    return res;
}

double QaD_TurnOnQuadDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    /*   if(pt4<55) calopt4 = QaD_QuaJet_CaloPt4lDown->Eval(pt4);
    else  */ calopt4 = QaD_QuaJet_CaloPt4hDown->Eval(pt4);
    float L1;
     /*  if(sumpt<210) L1 = QaD_QuaJet_L1lDown->Eval(sumpt);
    else */  L1=QaD_QuaJet_L1hDown->Eval(sumpt);
	float res =  L1*calopt4*QaD_QuaJet_CSV3Down->Eval(CSV3)*QaD_QuaJet_PFPt4Down->Eval(pt4);
    if( res < 0 ) return 0;
    return res;
}


