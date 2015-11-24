<h1> Code structure of HbbHbb_Run2 </h1>

Souvik Das, Nov 2015

This package works on Heppy ntuples. There are 3 main sorts of programs in this suite as described below.

<h2> 1. Analyzers </h2>

These take Heppy ntuples as input, and output a modified set of ntuple files and histogram files for debugging and plotting.

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
<pre> MMRSelection/root -l processMMRSelection_Graviton.c </pre>

<h3> HbbHbb_LMRSelection.cc </h3>

This contains our Low Mass Regime event selection criteria.

We operate it from within the LMRSelection directory with the commands:
<pre> LMRSelection/root -l processLMRSelection_Graviton.c </pre>

<h3> HbbHbb_MeasureResolutionBias.cc </h3>

This takes ntuples produced by HbbHbb_PreSelection.cc. It creates histograms that measure the jet biases and resolutions relevant for this analysis. Histograms produced by this may be opened with the MeasureResolution/DisplayResolutionBias.cc script, that fits these biases and resolutions to characterize them. These characterizations are then fed into HbbHbb_Component_KinFit.cc.

We operate it within the MeasureResolution directory with the command:
<pre> MeasureResolution/processMeasureResolution_Graviton.c </pre>

<h2> 2. Analysis Components </h2>

These do not run standalone, but are simple common algorithms included by the main Analyzers.

<h3> HbbHbb_Component_KinFit.cc </h3>

This contains the algorithm for doing the kinematic constraint on the dijet pairs. It is called by both the HbbHbb_MMRSelection.cc and HbbHbb_LMRSelection.cc Analyzers.

<h3> HbbHbb_Component_SignalPurity.cc </h3>

This contains the algorithm that matches selected reconstructed HH candidate jets to the generator level b quarks from each Higgs. It returns an integer signifying the purity of the reconstructed sample. It is called by HbbHbb_MMRSelection.cc, HbbHbb_LMRSelection.cc and HbbHbb_MeasureResolutionBias.cc.

<h2> 3. Fitting and Plotting Scripts </h2>

<h3> DisplayJetProperties.cc </h3>

Works on Histograms files output by HbbHbb_PreSelection.cc (can also work on output of HbbHbb_MMRSelection.cc, HbbHbb_LMRSelection.cc). Plots jet properties in our events for signal, ttbar, data, etc, like the pT of the first 4 highest pT jets with |eta| < 2.5. It must be run in the same directory where the Histogram files are.

<pre> root -l -b -q DisplayJetProperties.cc++ </pre>

<h3> MeasureResolution/DisplayResolutionBias.cc </h3>

Works on the Histograms files output by HbbHbb_MeasureResolutionBias.cc. Plots the bias and resolution distributions of the relevant jets in the signal samples.

<pre> root -l -b -q MeasureResolution/DisplayResolutionBias.cc++ </pre>

<h3> DisplayKinFit.cc </h3>

<h3> DisplayPurity.cc </h3>

<h3> DisplaymH1vsmH2.cc </h3>





