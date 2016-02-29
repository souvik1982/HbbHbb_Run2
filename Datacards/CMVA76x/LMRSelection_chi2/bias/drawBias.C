{

int mass[5]={260, 270, 300, 350, 400};
double mu[4]={1,3,5,10};
double mean260[4] = {0.0712132 ,0.0432474,0.0329392,0.038654};
double rms260[4]={0.400623,0.340235,0.390768, 0.424983};

double mean270[4]={0.0418185,0.0449843,0.0640113,-0.00558993};
double rms270[4]={0.312645,0.299943,0.365795,0.380857};

double mean300[4]={0.0208772,0.00991396,0.0900107,0.00360616};
double rms300[4]={0.289244,0.249507,0.322378,0.422859};

double mean350[4]={-0.081992,-0.0675197,-0.10559,-0.172021};
double rms350[4]={0.218986,0.244469,0.208629,0.332029};

double mean400[4]={-0.0665465,-0.0318245,-0.0760409,-0.0935788};
double rms400[4]={0.267598,0.219374,0.215422,0.371277};

TCanvas * c = new TCanvas("c","c",700, 700);
TGraphAsymmErrors *g_bias260=new TGraphAsymmErrors(4, mu, mean260, 0, 0, rms260, rms260);
g_bias260->SetTitle("mx 260 GeV; inj #mu (pb) ; #Delta#mu (pb)");
g_bias260->SetMinimum(-1);
g_bias260->SetMaximum(1);
g_bias260->SetMarkerStyle(20);
g_bias260->Draw("ALP");

TLine *a= new TLine(mu[0],0,mu[3],0.);
a->SetLineColor(kRed+1);
a->SetLineWidth(2);
a->Draw("same");
c->SaveAs("bias260.png");

delete c;

TCanvas * c = new TCanvas("c","c",700, 700);
TGraphAsymmErrors *g_bias270=new TGraphAsymmErrors(4, mu, mean270, 0, 0, rms270, rms270);
g_bias270->SetTitle("mx 270 GeV; inj #mu (pb) ; #Delta#mu (pb)");
g_bias270->SetMinimum(-1);
g_bias270->SetMaximum(1);
g_bias270->SetMarkerStyle(20);
g_bias270->Draw("ALP");

TLine *a= new TLine(mu[0],0,mu[3],0.);
a->SetLineColor(kRed+1);
a->SetLineWidth(2);
a->Draw("same");
c->SaveAs("bias270.png");

delete c;

TCanvas * c = new TCanvas("c","c",700, 700);
TGraphAsymmErrors *g_bias300=new TGraphAsymmErrors(4, mu, mean300, 0, 0, rms300, rms300);
g_bias300->SetTitle("mx 300 GeV; inj #mu (pb) ; #Delta#mu (pb)");
g_bias300->SetMinimum(-1);
g_bias300->SetMaximum(1);
g_bias300->SetMarkerStyle(20);
g_bias300->Draw("ALP");

TLine *a= new TLine(mu[0],0,mu[3],0.);
a->SetLineColor(kRed+1);
a->SetLineWidth(2);
a->Draw("same");
c->SaveAs("bias300.png");

delete c;

TCanvas * c = new TCanvas("c","c",700, 700);
TGraphAsymmErrors *g_bias350=new TGraphAsymmErrors(4, mu, mean350, 0, 0, rms350, rms350);
g_bias350->SetTitle("mx 350 GeV; inj #mu (pb) ; #Delta#mu (pb)");
g_bias350->SetMinimum(-1);
g_bias350->SetMaximum(1);
g_bias350->SetMarkerStyle(20);
g_bias350->Draw("ALP");

TLine *a= new TLine(mu[0],0,mu[3],0.);
a->SetLineColor(kRed+1);
a->SetLineWidth(2);
a->Draw("same");
c->SaveAs("bias350.png");

delete c;


TCanvas * c = new TCanvas("c","c",700, 700);
TGraphAsymmErrors *g_bias400=new TGraphAsymmErrors(4, mu, mean400, 0, 0, rms400, rms400);
g_bias400->SetTitle("mx 400 GeV; inj #mu (pb) ; #Delta#mu (pb)");
g_bias400->SetMinimum(-1);
g_bias400->SetMaximum(1);
g_bias400->SetMarkerStyle(20);
g_bias400->Draw("ALP");

TLine *a= new TLine(mu[0],0,mu[3],0.);
a->SetLineColor(kRed+1);
a->SetLineWidth(2);
a->Draw("same");
c->SaveAs("bias400.png");

delete c;

/*TGraphAsymmErrors *g_bias270=new TGraphAsymmErrors(5, &(mu[0]), mean270, 0, 0, rms270, rms270);
TGraphAsymmErrors *g_bias300=new TGraphAsymmErrors(5, &(mu[0]), mean300, 0, 0, rms300, rms300);
TGraphAsymmErrors *g_bias350=new TGraphAsymmErrors(5, &(mu[0]), mean350, 0, 0, rms350, rms350);
TGraphAsymmErrors *g_bias400=new TGraphAsymmErrors(5, &(mu[0]), mean400, 0, 0, rms400, rms400);
*/


}

