void drawBias () {
    
    gStyle->SetOptStat(1);
    gStyle->SetOptTitle(1);
    gStyle->SetFitFormat("2.2g");
    gStyle->SetPadBottomMargin(0.2);
    
    
    const int nDirs = 1;
    
    Color_t cols[nDirs] = {kBlack};//, kRed+1, kOrange-3, kGreen+1, kAzure+7 , kMagenta};
    
    
    TString dirNames[nDirs] = {"Crystal"};//,"expow2","pow1","lau1","atlas1","vvdijet1"};
    
    
    const int nPoints = 5;//46;
    TCanvas* c1[nDirs][nPoints];
    TFile * f[nDirs][nPoints];
    TTree* tree_fit_sb[nDirs][nPoints];
    
    TH1D* hists[nDirs][nPoints];
    
    TGraphErrors* biasG[nDirs];
    TGraphErrors* biasG2[nDirs];
    
    TCanvas* c2 = new TCanvas("p2","p2",700,700);
    TH1F *hr = c2->DrawFrame(250,-1,500,1);
    hr->SetXTitle("m_{X} (GeV)");
    hr->SetYTitle("mean");

    TCanvas* c2a = new TCanvas("c2a","c2a",700,700);
    TH1F *hra = c2a->DrawFrame(250,-1,500,1);
    hra->SetXTitle("m_{X} (GeV)");
    hra->SetYTitle("medians");
    
    TLegend* leg = new TLegend(0.75,0.9,0.9,0.75,"pull mean","BNDC");
    leg->SetTextFont(42);
    TLegend* leg2 = new TLegend(0.75,0.9,0.9,0.75,"medians","BNDC");
    leg2->SetTextFont(42);
    
    for (int dd=0; dd!=1; ++dd) {
        biasG[dd] = new TGraphErrors(nPoints);
        biasG2[dd] = new TGraphErrors(nPoints);
        biasG[dd]->SetMarkerColor(cols[dd]);
	biasG[dd]->SetMarkerStyle(20);
        biasG[dd]->SetLineColor(cols[dd]);
        biasG2[dd]->SetMarkerColor(cols[dd]);
	biasG2[dd]->SetMarkerStyle(20);
        biasG2[dd]->SetLineColor(cols[dd]);
        
        
        leg->AddEntry(biasG[dd],dirNames[dd],"p");
        leg2->AddEntry(biasG2[dd],dirNames[dd],"p");
        
        Double_t quantile,prob;
        prob = 0.5;
        
        for (int i=0; i!=nPoints; ++i) {
            //if (650+i*100 == 1750) continue;
 	    int mass[nPoints] ={260,270,300,350,400};
	    std::cout<<mass[i]<<std::endl;
            TString nameF = /*dirNames[dd]+*/Form("mlfitoutput%d_1.root",mass[i]);
            if (gSystem->AccessPathName(nameF)) continue;
            c1[dd][i] = new TCanvas(Form("c_%d_%d",dd,i),Form("c_%d_%d",dd,i), 700, 700);
            f[dd][i] = new TFile(nameF);
            if(!f[dd][i]) continue;
            
            tree_fit_sb[dd][i] = static_cast<TTree*>(f[dd][i]->Get("tree_fit_sb"));
            
            TString name = Form("bias_%d_GeV-",mass[i])+dirNames[dd];
            TString title = Form("bias at %d GeV for ",mass[i])+dirNames[dd];
            //if(mass[i]<350)hists[dd][i] = new TH1D(name,title+";#frac{#mu_{fit}-3.0}{#sigma_{fit}};entries/0.25",20,-5,5);
            //else 
            hists[dd][i] = new TH1D(name,title+";#frac{#mu_{fit}-1.0}{#sigma_{fit}};entries/0.25",20,-5,5);
	    hists[dd][i]->SetMarkerColor(kBlack);
	    hists[dd][i]->SetLineColor(kBlack);
            hists[dd][i]->SetMarkerStyle(20);    
            //if(mass[i]<350) tree_fit_sb[dd][i]->Draw("(mu-3.0)/muHiErr>>"+name,"fit_status >= 0","pe");
            //else
            tree_fit_sb[dd][i]->Draw("(mu-1.0)/muHiErr>>"+name,"fit_status >= 0","pe");
	     
            hists[dd][i]->Fit("gaus","LM","",-1,1);
            hists[dd][i]->GetXaxis()->SetTitleOffset(1.2);
            c1[dd][i]->SaveAs(dirNames[dd]+Form("_%d_1.pdf",mass[i]));
            
            
            biasG[dd]->SetPoint(i,mass[i],hists[dd][i]->GetFunction("gaus")->GetParameter(1));
	//    if(mass[i]==350) biasG[dd]->SetPoint(i,mass[i],hists[dd][i]->GetFunction("gaus")->GetParameter(1)/2.);
            biasG[dd]->SetPointError(i,0,hists[dd][i]->GetFunction("gaus")->GetParameter(2)/sqrt(hists[dd][i]->GetEntries()));
            
            hists[dd][i]->GetQuantiles(1,&quantile,&prob);
            biasG2[dd]->SetPoint(i,mass[i],quantile); // //GetMean
            //biasG2[dd]->SetPoint(i,650+i*100,hists[dd][i]->GetMean()); // //GetMean
            biasG2[dd]->SetPointError(i,0,hists[dd][i]->GetRMS()/sqrt(hists[dd][i]->GetEntries()));
                                    
                                                
                                                        }
                                    c2->cd();
                                    biasG[dd]->Draw("pe same");
                                    c2a->cd();
                                    biasG2[dd]->Draw("pe same");
                                }
                                    c2->cd();
                                    leg->Draw("same");
				    c2->SaveAs("Crystal_1.pdf");
                                    c2a->cd();
                                                                                 leg2->Draw("same");
				c2a->SaveAs("Crystala_1.pdf");	
                                                                                                                
                                                                                                                }
