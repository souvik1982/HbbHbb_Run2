#include "../TDRStyle.h"
int comp_TO()
{
    TF1* QuaJet_L1B = new TF1("QuaJet_L1","(1-((0.5-(0.5*TMath::Erf((x-269.548)*((1+sq(0))/64.3428))))*0.842623))-0.157454", 50,500 );
    TF1* QuaJet_L1C = new TF1("QuaJet_L1","(1-((0.5-(0.5*TMath::Erf((x-269.048)*((1+sq(0))/64.6114))))*0.839642))-0.160377", 50,500 );
    TF1* QuaJet_L1D = new TF1("QuaJet_L1","(1-((0.5-(0.5*TMath::Erf((x-273.166)*((1+sq(0))/66.5749))))*0.872202))-0.127885", 50,500 );

    TF1* QuaJet_CaloPt4B = new TF1("QuaJet_CaloPt4","(1-((0.5-(0.5*TMath::Erf((x-30.7698)*((1+sq(0))/27.9577))))*2))-0.0227452", 25,200 );
    TF1* QuaJet_CaloPt4C = new TF1("QuaJet_CaloPt4","(1-((0.5-(0.5*TMath::Erf((x-29.6498)*((1+sq(0))/28.6924))))*2))-0.0224492", 25,200 );
    TF1* QuaJet_CaloPt4D = new TF1("QuaJet_CaloPt4","(1-((0.5-(0.5*TMath::Erf((x-30.0768)*((1+sq(0))/29.0729))))*2))-0.00832278", 25,200 );

    TF1* QuaJet_CSV3B = new TF1("QuaJet_CSV3","(1-((0.5-(0.5*TMath::Erf((x-0.861822)*((1+sq(0))/0.338825))))*0.938819))-2.44655e-10");
    TF1* QuaJet_CSV3C = new TF1("QuaJet_CSV3","(1-((0.5-(0.5*TMath::Erf((x-0.867794)*((1+sq(0))/0.338295))))*0.92719))-1.17284e-09");
    TF1* QuaJet_CSV3D = new TF1("QuaJet_CSV3","(1-((0.5-(0.5*TMath::Erf((x-0.843022)*((1+sq(0))/0.347002))))*0.919297))-1.4537e-10");


    TF1* QuaJet_PFPt4B = new TF1("QuaJet_PFPt4","(1-((0.5-(0.5*TMath::Erf((x-28.8291)*((1+sq(0))/17.4039))))*2))-0.000753323", 25,200 );
    TF1* QuaJet_PFPt4C = new TF1("QuaJet_PFPt4","(1-((0.5-(0.5*TMath::Erf((x-28.3691)*((1+sq(0))/18.3054))))*2))-0.000390085", 25,200 );
    TF1* QuaJet_PFPt4D = new TF1("QuaJet_PFPt4","(1-((0.5-(0.5*TMath::Erf((x-33.5366)*((1+sq(0))/13.5425))))*2))-1.19182e-13", 25,200 );



    gStyle->SetOptStat(0);
    //    gROOT->SetBatch();
    setTDRStyle();
    TCanvas c("c","c",800,800);
    c.cd();
    QuaJet_L1B->Draw();
    QuaJet_L1C->Draw("same");
    QuaJet_L1D->Draw("same");
    QuaJet_L1B->SetLineColor( kBlack );
    QuaJet_L1C->SetLineColor( kRed );
    QuaJet_L1D->SetLineColor( kGreen );

    c.SaveAs("comp_QJ_L1.pdf");

    QuaJet_CaloPt4B->Draw();
    QuaJet_CaloPt4C->Draw("same");
    QuaJet_CaloPt4D->Draw("same");
    QuaJet_CaloPt4B->SetLineColor( kBlack );
    QuaJet_CaloPt4C->SetLineColor( kRed );
    QuaJet_CaloPt4D->SetLineColor( kGreen );

    c.SaveAs("comp_QJ_CaloPt4.pdf");

    QuaJet_CSV3B->Draw();
    QuaJet_CSV3C->Draw("same");
    QuaJet_CSV3D->Draw("same");
    QuaJet_CSV3B->SetLineColor( kBlack );
    QuaJet_CSV3C->SetLineColor( kRed );
    QuaJet_CSV3D->SetLineColor( kGreen );

    c.SaveAs("comp_QJ_CSV3.pdf");

    QuaJet_PFPt4B->Draw();
    QuaJet_PFPt4C->Draw("same");
    QuaJet_PFPt4D->Draw("same");
    QuaJet_PFPt4B->SetLineColor( kBlack );
    QuaJet_PFPt4C->SetLineColor( kRed );
    QuaJet_PFPt4D->SetLineColor( kGreen );

    c.SaveAs("comp_QJ_PFPt4.pdf");

TF1* DoubleJet_L1B = new TF1("DoubleJet_L1","(1-((0.5-(0.5*TMath::Erf((x-269.502)/61.7696)))*0.990749))-0.00916106", 50,500);
TF1* DoubleJet_L1C = new TF1("DoubleJet_L1","(1-((0.5-(0.5*TMath::Erf((x-267.463)/61.036)))*0.965259))-0.0345786", 50,500);
TF1* DoubleJet_L1D = new TF1("DoubleJet_L1","(1-((0.5-(0.5*TMath::Erf((x-270.835)/62.4551)))*0.99053))-0.00938728", 50,500);
TF1* DoubleJet_CaloPt2B = new TF1("DoubleJet_CaloPt2","(1-((0.5-(0.5*TMath::Erf((x-90.7333)/15.999)))*0.874868))-0.0769032", 25,200);
TF1* DoubleJet_CaloPt2C = new TF1("DoubleJet_CaloPt2","(1-((0.5-(0.5*TMath::Erf((x-89.503)/16.7813)))*0.882343))-0.0733072", 25,200);
TF1* DoubleJet_CaloPt2D = new TF1("DoubleJet_CaloPt2","(1-((0.5-(0.5*TMath::Erf((x-90.0974)/16.8363)))*0.881546))-0.0654595", 25,200);
TF1* DoubleJet_CaloPt4B = new TF1("DoubleJet_CaloPt4","(1-((0.5-(0.5*TMath::Erf((x-1.46332)/33.421)))*2))-0.0093725", 25,200);
TF1* DoubleJet_CaloPt4C = new TF1("DoubleJet_CaloPt4","(1-((0.5-(0.5*TMath::Erf((x+5.88453)/39.0734)))*2))-0.00644141", 25,200);
TF1* DoubleJet_CaloPt4D = new TF1("DoubleJet_CaloPt4","(1-((0.5-(0.5*TMath::Erf((x+5.38785)/39.8142)))*2))-1.08473e-11", 25,200);
TF1* DoubleJet_CSV3B = new TF1("DoubleJet_CSV3","(1-((0.5-(0.5*TMath::Erf((x-0.868794)/0.348695)))*0.953974))-1.28995e-09");
TF1* DoubleJet_CSV3C = new TF1("DoubleJet_CSV3","(1-((0.5-(0.5*TMath::Erf((x-0.878593)/0.36211)))*0.945802))-7.64778e-10");
TF1* DoubleJet_CSV3D = new TF1("DoubleJet_CSV3","(1-((0.5-(0.5*TMath::Erf((x-0.842657)/0.293373)))*0.908824))-5.72134e-10");
TF1* DoubleJet_PFPt4B = new TF1("DoubleJet_PFPt4","(1-((0.5-(0.5*TMath::Erf((x-13.0155)/15.7164)))*1.66151))-0.000731984", 25,200);
TF1* DoubleJet_PFPt4C = new TF1("DoubleJet_PFPt4","(1-((0.5-(0.5*TMath::Erf((x-30.888)/6.19168)))*0.162489))-0.000675357", 25,200);
TF1* DoubleJet_PFPt4D = new TF1("DoubleJet_PFPt4","(1-((0.5-(0.5*TMath::Erf((x-20.1888)/9.76471)))*2))-0.000464548", 25,200);
TF1* DoubleJet_PFPt2B = new TF1("DoubleJet_PFPt2","(1-((0.5-(0.5*TMath::Erf((x-84.5527)/16.8585)))*1.00809))-0.000363484", 25,200);
TF1* DoubleJet_PFPt2C = new TF1("DoubleJet_PFPt2","(1-((0.5-(0.5*TMath::Erf((x-76.8024)/19.5322)))*1.80434))-0.000367159", 25,200);
TF1* DoubleJet_PFPt2D = new TF1("DoubleJet_PFPt2","(1-((0.5-(0.5*TMath::Erf((x-91.4797)/10.4933)))*0.626132))-2.96839e-07", 25,200);

    DoubleJet_L1B->Draw();
    DoubleJet_L1C->Draw("same");
    DoubleJet_L1D->Draw("same");
    DoubleJet_L1B->SetLineColor( kBlack );
    DoubleJet_L1C->SetLineColor( kRed );
    DoubleJet_L1D->SetLineColor( kGreen );

    c.SaveAs("comp_DJ_L1.pdf");

    DoubleJet_CaloPt4B->Draw();
    DoubleJet_CaloPt4C->Draw("same");
    DoubleJet_CaloPt4D->Draw("same");
    DoubleJet_CaloPt4B->SetLineColor( kBlack );
    DoubleJet_CaloPt4C->SetLineColor( kRed );
    DoubleJet_CaloPt4D->SetLineColor( kGreen );

    c.SaveAs("comp_DJ_CaloPt4.pdf");

    DoubleJet_CSV3B->Draw();
    DoubleJet_CSV3C->Draw("same");
    DoubleJet_CSV3D->Draw("same");
    DoubleJet_CSV3B->SetLineColor( kBlack );
    DoubleJet_CSV3C->SetLineColor( kRed );
    DoubleJet_CSV3D->SetLineColor( kGreen );

    c.SaveAs("comp_DJ_CSV3.pdf");

    DoubleJet_PFPt4B->Draw();
    DoubleJet_PFPt4C->Draw("same");
    DoubleJet_PFPt4D->Draw("same");
    DoubleJet_PFPt4B->SetLineColor( kBlack );
    DoubleJet_PFPt4C->SetLineColor( kRed );
    DoubleJet_PFPt4D->SetLineColor( kGreen );

    c.SaveAs("comp_DJ_PFPt4.pdf");

    DoubleJet_CaloPt2B->Draw();
    DoubleJet_CaloPt2C->Draw("same");
    DoubleJet_CaloPt2D->Draw("same");
    DoubleJet_CaloPt2B->SetLineColor( kBlack );
    DoubleJet_CaloPt2C->SetLineColor( kRed );
    DoubleJet_CaloPt2D->SetLineColor( kGreen );

    c.SaveAs("comp_DJ_CaloPt2.pdf");

    DoubleJet_PFPt2B->Draw();
    DoubleJet_PFPt2C->Draw("same");
    DoubleJet_PFPt2D->Draw("same");
    DoubleJet_PFPt2B->SetLineColor( kBlack );
    DoubleJet_PFPt2C->SetLineColor( kRed );
    DoubleJet_PFPt2D->SetLineColor( kGreen );

    c.SaveAs("comp_DJ_PFPt2.pdf");
    return 0;
}
