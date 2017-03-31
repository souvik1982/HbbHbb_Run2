 {


gStyle->SetOptFit(1111);
TFile * f = new TFile("mlfitoutput350.root");
TH1F* hist = new TH1F("hist","350 ;#frac{#mu_{fit}-1.0}{#sigma_{fit}};entries/0.25",20,-5,5);
tree_fit_sb->Draw("(mu-1)/muHiErr>>hist","fit_status >= 0","pe");
hist->GetXaxis()->SetTitleOffset(1.2);
hist->Fit("gaus","LM","",-2,2);
c1->SaveAs("test350.pdf");

TFile * f1 = new TFile("mlfitoutput270.root");
TH1F* hist1 = new TH1F("hist1","270 ;#frac{#mu_{fit}-1.0}{#sigma_{fit}};entries/0.25",20,-5,5);
tree_fit_sb->Draw("(mu-1)/muHiErr>>hist1","fit_status >= 0","pe");
hist1->GetXaxis()->SetTitleOffset(1.2);
hist1->Fit("gaus","LM","",-2,2);
c1->SaveAs("test270.pdf");

TFile * f2 = new TFile("mlfitoutput300.root");
TH1F* hist2 = new TH1F("hist2","300 ;#frac{#mu_{fit}-1.0}{#sigma_{fit}};entries/0.25",20,-5,5);
tree_fit_sb->Draw("(mu-1)/muHiErr>>hist2","fit_status >= 0","pe");
hist2->GetXaxis()->SetTitleOffset(1.2);
hist2->Fit("gaus","LM","",-2,2);
c1->SaveAs("test300.pdf");



}
