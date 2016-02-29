void BiasStudies(int mass, int ievt, float scale=1)
{
  TFile *_file0 = TFile::Open(Form("mlfit_%d_mu%d.root", mass, ievt));
 
  TCanvas* c1 = new TCanvas("c1", "");
  TTree* tree_fit_sb = (TTree*) _file0->Get("tree_fit_sb;1");

  tree_fit_sb->Draw(Form("(mu-%d)/(muLoErr+muHiErr)*2>>h(20,-4,4)", ievt));

  TH1D* hist = (TH1D*) _file0->Get("h");
  TF1* funG = new TF1("funG", "[0]*TMath::Gaus(x,[1],[2])");
  //hist->SetStats(0);

  gStyle->SetOptFit(0011);

  funG->SetParName(1, "bias");
  funG->SetParName(2, "sigma");

  funG->SetParameter(0, 40.);
  funG->SetParameter(1, 0.);
  funG->SetParameter(2, 1.);
  
  hist->Fit("funG");

  std::cout<< " ASDASD"<<mass <<"   "<<ievt<<"  mean "<< funG->GetParameter(1) << " width "<<funG->GetParameter(2) <<std::endl;	


  c1->SaveAs(Form("Bias_Graviton%d_mu%d.png",mass, ievt));
  c1->SaveAs(Form("Bias_Graviton%d_mu%d.pdf",mass, ievt));

  /*tree_fit_sb->Draw(Form("mu>>hmu(20,-10.,10+%d*4.)", ievt));
  TH1D* hmu = (TH1D*) _file0->Get("hmu");
  hmu->Fit("gaus");

  hmu->SetStats(0);
  c1->SaveAs(Form("toys/Mu_Graviton%d_mu%d.png",mass, ievt));
  c1->SaveAs(Form("toys/Mu_Graviton%d_mu%d.pdf",mass, ievt));
*/
}
