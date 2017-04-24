TF1* DoubleJet_L1 = new TF1("DoubleJet_L1","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-260.145)/79.0451)*(x>260.145))+(((x-260.145)/(79.0451-13.5273))*(x<=260.145)))*0.99883))))-4.9788e-13)");
TF1* DoubleJet_L1Up = new TF1("DoubleJet_L1Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-259.772)/79.0451)*(x>259.772))+(((x-259.772)/(79.0451-13.5273))*(x<=259.772)))*0.99883))))+0.02)");
TF1* DoubleJet_L1Down = new TF1("DoubleJet_L1Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-260.518)/79.0451)*(x>260.518))+(((x-260.518)/(79.0451-13.5273))*(x<=260.518)))*0.99883))))-0.02)");
TF1* DoubleJet_CaloPt4 = new TF1("DoubleJet_CaloPt4","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-14.674)/19.5798)*(x>14.674))+(((x-14.674)/(19.5798+0))*(x<=14.674)))*2))))-0.505361)");
TF1* DoubleJet_CaloPt4Up = new TF1("DoubleJet_CaloPt4Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-14.5472)/19.5798)*(x>14.5472))+(((x-14.5472)/(19.5798+0))*(x<=14.5472)))*2))))-0.485361)");
TF1* DoubleJet_CaloPt4Down = new TF1("DoubleJet_CaloPt4Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-14.8018)/19.5798)*(x>14.8018))+(((x-14.8018)/(19.5798+0))*(x<=14.8018)))*2))))-0.525361)");
TF1* DoubleJet_CaloPt2 = new TF1("DoubleJet_CaloPt2","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-85.4249)/21.9235)*(x>85.4249))+(((x-85.4249)/(21.9235-4.98956))*(x<=85.4249)))*0.986604))))-7.18314e-14)");
TF1* DoubleJet_CaloPt2Up = new TF1("DoubleJet_CaloPt2Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-85.2301)/21.9235)*(x>85.2301))+(((x-85.2301)/(21.9235-4.98956))*(x<=85.2301)))*0.986604))))+0.02)");
TF1* DoubleJet_CaloPt2Down = new TF1("DoubleJet_CaloPt2Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-85.6189)/21.9235)*(x>85.6189))+(((x-85.6189)/(21.9235-4.98956))*(x<=85.6189)))*0.986604))))-0.02)");
TF1* DoubleJet_CSV3 = new TF1("DoubleJet_CSV3","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x+0.881966)/1.06283)*(x>-0.881966))+(((x+0.881966)/(1.06283-0.509543))*(x<=-0.881966)))*2))))-0.601322)");
TF1* DoubleJet_CSV3Up = new TF1("DoubleJet_CSV3Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x+0.988735)/1.06283)*(x>-0.988735))+(((x+0.988735)/(1.06283-0.509543))*(x<=-0.988735)))*2))))-0.581322)");
TF1* DoubleJet_CSV3Down = new TF1("DoubleJet_CSV3Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x+0.767245)/1.06283)*(x>-0.767245))+(((x+0.767245)/(1.06283-0.509543))*(x<=-0.767245)))*2))))-0.621322)");
TF1* DoubleJet_PFPt4 = new TF1("DoubleJet_PFPt4","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-17.5882)/13.5261)*(x>17.5882))+(((x-17.5882)/(13.5261-6.48476))*(x<=17.5882)))*0.996927))))-0)");
TF1* DoubleJet_PFPt4Up = new TF1("DoubleJet_PFPt4Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-17.1056)/13.5261)*(x>17.1056))+(((x-17.1056)/(13.5261-6.48476))*(x<=17.1056)))*0.996927))))+0.02)");
TF1* DoubleJet_PFPt4Down = new TF1("DoubleJet_PFPt4Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-18.0869)/13.5261)*(x>18.0869))+(((x-18.0869)/(13.5261-6.48476))*(x<=18.0869)))*0.996927))))-0.02)");
TF1* DoubleJet_PFPt2 = new TF1("DoubleJet_PFPt2","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-84.3457)/14.819)*(x>84.3457))+(((x-84.3457)/(14.819+16.2574))*(x<=84.3457)))*0.995488))))-0)");
TF1* DoubleJet_PFPt2Up = new TF1("DoubleJet_PFPt2Up","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-84.3464)/14.819)*(x>84.3464))+(((x-84.3464)/(14.819+16.2574))*(x<=84.3464)))*0.995488))))+0.02)");
TF1* DoubleJet_PFPt2Down = new TF1("DoubleJet_PFPt2Down","min(1.,(1-(0.5-(0.5*(TMath::Erf((((x-84.3464)/14.819)*(x>84.3464))+(((x-84.3464)/(14.819+16.2574))*(x<=84.3464)))*0.995488))))-0.02)");