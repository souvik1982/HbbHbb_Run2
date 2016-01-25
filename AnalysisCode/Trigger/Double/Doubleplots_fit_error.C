TH2F* getGraph2DError(TEfficiency* efficiency,int nx, float xmin, float xmax, int ny=0, float ymin=0, float ymax=0){
    TH2F* output =  (TH2F*) efficiency->CreateHistogram();
    for (int x= 0; x<output->GetNbinsX(); x++){
        for (int y= 0; y<output->GetNbinsX(); y++){
            int bin = efficiency->GetGlobalBin(x,y);
            float value = efficiency->GetEfficiency(bin);
            float value_up = efficiency->GetEfficiencyErrorUp(bin);
            float value_down = efficiency->GetEfficiencyErrorLow(bin);
            float error = (value_up+value_down)*0.5;
            output->SetBinError(bin,error);
//            cout<< output->GetBinContent(bin) <<"\t" << value <<"\t"<<bin<<endl;
        }
    }
    return output;
//    GetGlobalBin
//    FindFixBin
//    SetPointError
}

void doFit(TF1* function,TEfficiency* efficiency,float xmin, float xmax, string fileName, TCanvas* c1){
    function->SetRange(xmin,xmax);
    efficiency->Draw("");
    gStyle->SetOptFit(0);
    efficiency->Fit(function);
    function->Draw("same");
 
    TF1* fit = (TF1*)function->Clone("fit");
    TF1* fitUp = (TF1*)function->Clone("fitUp");
    fitUp->SetLineColor(kRed);
    fitUp->SetLineStyle(2);
    TF1* fitDown = (TF1*)function->Clone("fitDown");
    fitDown->SetLineStyle(2);
    double parameters[4];
    for(int i=0; i<4; i++)  {
		parameters[i] = fit->GetParameter(i);
//		if(i!=1) fit->FixParameter( i, parameters[i] );
		}

 
    double parametersUp[4]; 
    double parametersDown[4];
	

    double looseRange=10.;
    double tightRange=10.;
    
    //print "Up/down fit"
     for(int i=0; i<4; i++) {
        double nsigma = 2;
        if (i==0){// #  x0 can go down 
            parametersUp[i] = fit->GetParameter(i) + fit->GetParError(i)*nsigma;
            parametersDown[i] = fit->GetParameter(i) - fit->GetParError(i)*nsigma;
	}
        if(i==1){
            parametersUp[i] = fit->GetParameter(i) + fit->GetParError(i)*nsigma;
            parametersDown[i] = fit->GetParameter(i) - fit->GetParError(i)*nsigma;
	}
	if(i==2){
            parametersUp[i] = fit->GetParameter(i) + fit->GetParError(i)*nsigma;
            parametersDown[i] = fit->GetParameter(i) - fit->GetParError(i)*nsigma;
	}
	if(i==3){

            parametersUp[i] = fit->GetParameter(i) + fit->GetParError(i)*nsigma;
            parametersDown[i] = fit->GetParameter(i) - fit->GetParError(i)*nsigma;
	}
        else{//: # fix the other parameters
            parametersUp[i] = fit->GetParameter(i);
            parametersDown[i] = fit->GetParameter(i);
	}
	
}
        
        for(int i=0; i<4; i++) { 
        fit->SetParameter(i,parameters[i]);
        fitUp->SetParameter(i,parametersUp[i]);
        fitDown->SetParameter(i,parametersDown[i]);
	}
	


    fit->Draw("same");
    fitUp->Draw("same");
    fitDown->Draw("same");
	 

    c1->SaveAs((fileName+".png").c_str());
//    c1->SaveAs((fileName+".C").c_str());
    c1->SaveAs((fileName+".root").c_str());
}

void doFit(TF2* function,TH2F* efficiency,float xmin, float xmax,float ymin, float ymax, string fileName, TCanvas* c1){
    function->SetRange(xmin,ymin,xmax,ymax);
    efficiency->Draw("COLZ");
    efficiency->Fit(function);
    c1->SaveAs((fileName+".png").c_str());
//    c1->SaveAs((fileName+".C").c_str());
    c1->SaveAs((fileName+".root").c_str());
    function->SetMaximum(1);
    function->SetMinimum(0);
    function->Draw("COLZ");
    c1->SaveAs((fileName+"_function.png").c_str());
}

TEfficiency* getHisto(TTree* tree, string draw, int nx, float xmin, float xmax, string selection, string trigger, string title, string option="", int ny=0, float ymin=0, float ymax=0){
    selection = string("(")+selection+")";
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);
    string binning;
    if(ny==0) binning = string("(") + std::to_string(nx) + "," + std::to_string(xmin) + "," +std::to_string(xmax) + ")";
    else binning = string("(") + std::to_string(nx) + "," + std::to_string(xmin) + "," +std::to_string(xmax) + "," + std::to_string(ny) + "," + std::to_string(ymin) + "," +std::to_string(ymax) + ")";
    tree->Draw( (draw + ">> num" + binning).c_str(), (selection + "&&" + trigger).c_str() , option.c_str() );
    tree->Draw( (draw + ">> den" + binning).c_str(), (selection).c_str() , option.c_str() );
    cout << (draw + ">> num" + binning).c_str() <<endl;
    cout << (draw + ">> den" + binning).c_str() <<endl;
    cout << (selection).c_str() <<endl;
    cout << (option).c_str() <<endl;
    if(ny==0){
        TH1F* num = (TH1F*) gDirectory->Get("num");
        TH1F* den = (TH1F*) gDirectory->Get("den");
//        cout << num->GetNbinsX() <<endl;
//        cout << den->GetNbinsX() <<endl;
        TEfficiency* eff = new TEfficiency(*num,*den);
        eff->SetTitle(title.c_str());
        return eff;
    } else {
        TH2F* num = (TH2F*) gDirectory->Get("num");
        TH2F* den = (TH2F*) gDirectory->Get("den");
        TEfficiency* eff = new TEfficiency(*num,*den);
        eff->SetTitle(title.c_str());
        return eff;
    }
}

void Doubleplots_fit_error(){
    gEnv->SetValue("Hist.Binning.2D.Prof",10);
    gEnv->SetValue("Hist.Binning.3D.Profx",10);
    gEnv->SetValue("Hist.Binning.3D.Profy",10);
    gEnv->SetValue("Hist.Binning.2D.x",10);
    gEnv->SetValue("Hist.Binning.2D.y",10);

    TCanvas* c1 = new TCanvas("c1","c1");
    c1->SetGridx();
    c1->SetGridy();


    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);

    TFile *_file0 = TFile::Open("/eos/uscms/store/user/cvernier/SingleElectronVBF.root");
    TTree* tree = (TTree*) _file0->Get("tree");

    TFile* file = new TFile("test.root","recreate");

    TF1* turnonPt = new TF1("turnonPt","(0.5+0.5*TMath::Erf( (x-[0])*(x-[0]>[5])/[1] + (x-[0])*(x-[0]<[5])/[2] + [5]*(1/[1]-1/[2])*(x-[0]<[5]) ))*[4]+[3] ");
    turnonPt->SetRange(-1000,10000);
    turnonPt->SetParameters(70,20,100,0.1,0.9,5);

    TF1* turnonCSV = (TF1*) turnonPt->Clone("turnonCSV");
    turnonCSV->SetParameters(2,2,2,0,1,0);

    TF1* turnonDphi = new TF1("turnonDphi"," [2]/(1+exp([1]*(x-[0]))) +[3]");
    turnonDphi->SetParameters(1.6,0.01,1,-0.01);

    int nx=0, ny=0;
    float xmax=0, xmin=0, ymax=0, ymin=0;
    string filter="", preselection ="", variable="",title="", fileName="";
    TEfficiency* efficiency;

    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);

///////////////////////////////////////////////////////



    nx=100, xmin=0, xmax=400;
    variable="Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3]";
    filter="ntrgObjects_hltQuadCentralJet30>=1";
    preselection="HLT_BIT_HLT_Ele23_WPLoose_Gsf_v && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4";
    title= "L1 trigger turn-on; p^{T}_{1}+p^{T}_{2}+p^{T}_{3} ; Efficiency";
    fileName= "L1Pt1PtPt3Pt4";
    TH2F* graph2D;
    efficiency = getHisto(tree,variable,nx,xmin,xmax,preselection,filter,title);
    TF1* tnL1Pt1PtPt3Pt4 = (TF1*) turnonPt->Clone("tnL1Pt1PtPt3Pt4");
//    tnL1Pt1PtPt3Pt4->SetParameters(145,75,190,0.01,2,15);
    doFit(tnL1Pt1PtPt3Pt4,efficiency,xmin,xmax, fileName, c1);

///////////////////////////////////////////////////////
    turnonPt->SetParameters(50,20,12,0,1,12);

    nx=100, xmin=0, xmax=100;
    variable="Jet_pt[3]";
    preselection=preselection+"&&"+filter;
    filter="(ntrgObjects_hltQuadCentralJet30>=4)";
    title= "Calo p^{T}_{4} turn-on; p^{T}_{4} ; Efficiency";
    fileName= "CaloPt4";
    efficiency = getHisto(tree,variable,nx,xmin,xmax,preselection,filter,title);
    TF1* tnCaloPt4 = (TF1*) turnonPt->Clone("tnCaloPt4");
    tnCaloPt4->SetParameters(4,20,160,0,1,2);
    doFit(tnCaloPt4,efficiency,xmin,xmax, fileName, c1);

/////////////////////////////////////////////////////
    nx=150, xmin=30, xmax=180;
    variable="Jet_pt[1]";
    preselection=preselection+"&&"+filter;
    filter="(ntrgObjects_hltDoubleCentralJet90>=2)";
    title= "Calo p^{T}_{2} turn-on; p^{T}_{2} ; Efficiency";
    fileName= "CaloPt2";
    efficiency = getHisto(tree,variable,nx,xmin,xmax,preselection,filter,title);
    TF1* tnCaloPt2 = (TF1*) turnonPt->Clone("tnCaloPt2");
    //tnCaloPt2->SetParameters(4,20,160,0,1,2);
    doFit(tnCaloPt2,efficiency,xmin,xmax, fileName, c1);


////////////////////////////////////////////////////

    nx=20, xmin=0, xmax=8;
    ny=0, ymin=0, ymax=0;
    variable="-log(1-CSV[2]+1.e-7)";
    preselection=preselection+"&&"+filter;
    filter="(ntrgObjects_hltTripleCSV0p67>=3)";
    title= "Calo CSV_{3} turn-on; -Log(1-CSV_{3}) ; Efficiency";
    fileName= "CaloCSV3";
    efficiency = getHisto(tree,variable,nx,xmin,xmax,preselection,filter,title);
    TF1* tnCaloCSV3 = (TF1*) turnonPt->Clone("tnCaloCSV3");
    tnCaloCSV3->SetParameters(-0.4,2.8,10,-2.7,3.7,1.8);
    doFit(tnCaloCSV3,efficiency,xmin,xmax, fileName, c1);

///////////////////////////////////////////////////////


    nx=25, xmin=20, xmax=120;
    variable="Jet_pt[3]";
    preselection=preselection+"&&"+filter;
    filter="(ntrgObjects_hltQuadPFCentralJetLooseID30>=4)";
    title= "PF p^{T}_{4} turn-on; p^{T}_{4} ; Efficiency";
    fileName= "PFPt4";
    efficiency = getHisto(tree,variable,nx,xmin,xmax,preselection,filter,title);
    TF1* tnPFPt4 = (TF1*) tnCaloPt4->Clone("tnPFPt4");
    doFit(tnPFPt4,efficiency,xmin,xmax, fileName, c1);

////////////////////////////////////////////////
    nx=10, xmin=80, xmax=180;
    variable="Jet_pt[1]";
    preselection=preselection+"&&"+filter;
    filter="(ntrgObjects_hltDoublePFCentralJetLooseID90>=2)";
    title= "PF p^{T}_{2} turn-on; p^{T}_{2} ; Efficiency";
    fileName= "PFPt2";
    efficiency = getHisto(tree,variable,nx,xmin,xmax,preselection,filter,title);
    TF1* tnPFPt2 = (TF1*) tnCaloPt2->Clone("tnPFPt2");
    //tnPFPt2->SetParameters( 2.59999e+00, 2.25792e+01,-5.18454e+04,-4.53102e+03, 4.53202e+03, 0.00000e+00); 
    //tnPFPt2->SetParameters( 2.32528e-01 , 5.83071e+01 ,-2.67834e+02 ,-1.32842e+01 , 1.42933e+01 ,-8.21258e+01 );
    tnPFPt2->SetParameters(2.50961e+00, 5.63960e+01,-3.21610e+04,-1.32368e+01, 1.42427e+01, 0.00000e+00	);
    //tnPFPt2->SetParameters(-1.13862e+02 , 7.42174e+01 ,-2.86264e+05 ,-4.53102e+03 , 4.53202e+03 , 0.00000e+00 );
    //
    /*tnPFPt2->SetParameter(  0,7.56835e+01);
    tnPFPt2->SetParameter(  1,2.46977e+01);
	
    tnPFPt2->SetParameter(  2, -4.82774e+05); 
    tnPFPt2->SetParameter(  3, 3.18418e-03  );
    tnPFPt2->SetParameter(  4, 9.98558e-01 );
    tnPFPt2->SetParameter(  5, 0.00000e+00 );
    *///tnPFPt2->SetParameters(  7.56835e+01 , 2.46977e+01 ,-4.82774e+05 , 3.18418e-03 , 9.98558e-01 , 0.00000e+00 );//-1.04275e+02 , 7.00286e+01 ,-4.54482e+05  , -4.53102e+03 ,  4.53202e+03 ,  0.00000e+00 );
    doFit(tnPFPt2,efficiency,xmin,xmax, fileName, c1);
    //tnPFPt2->SetParameter(3,0.);
    //tnPFPt2->SetParameter(4,1.);
    //tnPFPt2->SetParameter(5,0.);	
	

    ofstream myfile;
    myfile.open ("fittedFunctions.h");

    myfile << "float tnL1Pt1PtPt3Pt4(float x){\n\treturn "<< tnL1Pt1PtPt3Pt4->GetExpFormula("P") <<" ; }\n\n";

    myfile << "float tnCaloPt4(float x){\n\treturn "<< tnCaloPt4->GetExpFormula("P") <<" ; }\n\n";
    myfile << "float tnCaloPt2(float x){\n\treturn "<< tnCaloPt2->GetExpFormula("P") <<" ; }\n\n";	

    myfile << "float tnCaloCSV3(float x){\n\treturn "<< tnCaloCSV3->GetExpFormula("P") <<" ; }\n\n";

    myfile << "float tnPFPt4(float x){\n\treturn "<< tnPFPt4->GetExpFormula("P") <<" ; }\n\n";
    myfile << "float tnPFPt2(float x){\n\treturn "<< tnPFPt2->GetExpFormula("P") <<" ; }\n\n";	
    
    
    myfile << "float DoubleTriggerWeight(float pt1, float pt2, float pt3, float pt4 , float CSV3){\n\tif(isnan(CSV3)) CSV3=0;\n\tCSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;\n\treturn tnL1Pt1PtPt3Pt4(pt1+pt2+pt3+pt4)*tnCaloPt4(pt4)*tnCaloPt2(pt2)*tnPFPt4(pt4)*tnPFPt2(pt2)*tnCaloCSV3(-log(1-CSV3+1.e-7)) ; }\n\n";

    myfile.close();
}
