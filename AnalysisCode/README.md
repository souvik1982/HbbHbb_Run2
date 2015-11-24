<h1> Code structure of HbbHbb_Run2 </h1>

Souvik Das, Nov 2015

This package works on Heppy ntuples. There are two main sorts of programs in
this suite described below.

<h2> 1. Analyzers </h2>

<h3> HbbHbb_PreSelection.cc </h3>

This takes the Heppy ntuple files as input and extracts the branches required for this analysis. It also only keeps events with the basic preselection criteria: There has to be 3 or more jets with |eta| < 2.5, pT > 40 GeV, and btag-CSV > 0.6. This speeds up our analysis, especially when working with large data samples, considerably.

This is run with the scripts: <br/>
<pre> 
 source processPreSelection_Graviton.sh
 source processPreSelection_ttbar.sh
 source processPreSelection_QCD_HT.sh
 source processPreSelection_Data.sh 
</pre>

<h3> HbbHbb_MMRSelection.cc </h3>

This takes ntuples produced by HbbHbb_PreSelection.cc. It contains our Medium Mass Regime event selection criteria. Finds dijet pairs with the smallest difference in mH1 - mH2, and dR < 1.5 between the jets in a dijet. Corrects and kinematically constrains di-jet masses to mH = 125 GeV. Selects events with (mH1, mH2) within a 17.5 GeV circular window around (125 GeV, 125 GeV) as our signal events. It outputs histograms that can then be used by the fitting and plotting scripts.

We operate it from within the MMRSelection directory with the commands:
<ul>
  <li> <pre> MMRSelection/root -l processMMRSelection_Graviton.c </pre> </li>
</ul>

<h3> HbbHbb_LMRSelection.cc </h3>

<h3> HbbHbb_MeasureResolutionBias.cc </h3>

<h3> HbbHbb_Component_KinFit.cc </h3>

<h3> HbbHbb_Component_SignalPurity.cc </h3>

<h2> 2. Fitting and Plotting Scripts </h2>

<h3> DisplayJetProperties.cc </h3>

<h3> DisplayKinFit.cc </h3>

<h3> DisplayPurity.cc </h3>

<h3> DisplaymH1vsmH2.cc </h3>





