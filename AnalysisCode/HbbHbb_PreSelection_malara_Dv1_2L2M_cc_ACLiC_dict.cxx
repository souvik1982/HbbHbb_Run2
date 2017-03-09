// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIscratchdImalaradIWorkingAreadIHbbHbb_Run2dIAnalysisCodedIHbbHbb_PreSelection_malara_Dv1_2L2M_cc_ACLiC_dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/HbbHbb_PreSelection_malara_Dv1_2L2M.cc"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_HbbHbb_PreSelection_malara_Dv1_2L2M_cc_ACLiC_dict_Impl() {
    static const char* headers[] = {
"/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/HbbHbb_PreSelection_malara_Dv1_2L2M.cc",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include",
"/scratch/malara/WorkingArea/backup/CMSSW_7_4_7/src",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/cms/cmssw/CMSSW_7_4_7/src",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/cms/coral/CORAL_2_3_21-odfocd8/include/LCG",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/mctester/1.25.0a-odfocd5/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/qt/4.8.1-cms/include/QtDesigner",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/tauolapp/1.1.5-koleij/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/charybdis/1.003-koleij/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/thepeg/1.9.2p1-koleij/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/sherpa/2.1.1-odfocd2/include/SHERPA-MC",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/qt/4.8.1-cms/include/QtOpenGL",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/qt/4.8.1-cms/include/QtGui",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/pythia8/205-koleij/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/herwig/6.521-koleij/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/qt/4.8.1-cms/include/QtScript",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/qt/4.8.1-cms/include/Qt3Support",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/classlib/3.1.3-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/lhapdf/6.1.5-koleij/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/cgal/4.2-jlbgio/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/tkonlinesw/2.7.0-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/qt/4.8.1-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/qt/4.8.1-cms/include/Qt",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/qt/4.8.1-cms/include/QtCore",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/qt/4.8.1-cms/include/QtXml",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/mcdb/1.0.2-cms/interface",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/libungif/4.1.4-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/libtiff/3.9.4-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/libpng/1.6.16/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/geant4/10.00.p02-cms/include/Geant4",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/frontier_client/2.8.11/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/evtgenlhc/9.1-cms",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/pcre/7.9__8.33-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/boost/1.57.0-jlbgio/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/xz/5.0.3__5.1.2alpha-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/xrootd/4.0.4-odfocd/include/xrootd/private",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/cms/vdt/v0.3.2-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/valgrind/3.10.1/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/toprex/4.23-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/tbb/43_20141023oss/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/tauola/27.121.5-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/sigcpp/2.2.10-cms/include/sigc++-2.0",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/rivet/2.2.1-odfocd/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/sqlite/3.7.17-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/protobuf/2.4.1-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/pacparser/1.3.1-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/oracle/11.2.0.3.0__10.2.0.4.0-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/meschach/1.2.pCMS1-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/libhepml/0.2.1-cms/interface",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/ktjet/1.06-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/jimmy/4.2-koleij/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/jemalloc/3.5.0-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/libxml2/2.7.7-cms/include/libxml2",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/herwigpp/2.7.1-koleij/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/heppdt/3.03.00-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/hector/1_3_4-odfocd6/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/gsl/1.10-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/libjpg/8b-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/xerces-c/2.8.0-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/gdbm/1.10-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fftw3/3.3.2-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fftjet/1.5.0-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.1.0-odfocd/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/expat/2.0.1-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/hepmc/2.06.07-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/dpm/1.8.0.1-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/dcap/2.47.8-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/db4/4.4.20-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/curl/7.28.0-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/cppunit/1.12.1-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/clhep/2.1.4.1-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/openssl/0.9.8e__1.0.1-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/pythia6/426-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/photos/215.5-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/zlib/1.2.8-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/libuuid/2.22.2-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/castor/2.1.13.9-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/castor/2.1.13.9-cms/include/shift",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/cascade/2.2.04-koleij/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/bz2lib/1.0.5-cms/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/python/2.7.6-cms/include/python2.7",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/gcc/4.9.1-cms/include/c++/4.9.1",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/gcc/4.9.1-cms/include/c++/4.9.1/x86_64-redhat-linux-gnu",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/gcc/4.9.1-cms/include/c++/4.9.1/backward",
"/usr/local/include",
"/usr/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/etc",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/gcc/4.9.1-cms/bin/../lib/gcc/x86_64-redhat-linux-gnu/4.9.1/../../../../include/c++/4.9.1",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/gcc/4.9.1-cms/bin/../lib/gcc/x86_64-redhat-linux-gnu/4.9.1/../../../../include/c++/4.9.1/x86_64-redhat-linux-gnu",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/gcc/4.9.1-cms/bin/../lib/gcc/x86_64-redhat-linux-gnu/4.9.1/../../../../include/c++/4.9.1/backward",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/etc/cling",
"/build/cmsbuild/auto-builds/CMSSW_7_4_7-slc6_amd64_gcc491/build/CMSSW_7_4_7-build/BUILD/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/root-6.02.00",
"/build/cmsbuild/auto-builds/CMSSW_7_4_7-slc6_amd64_gcc491/build/CMSSW_7_4_7-build/BUILD/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/root-6.02.00/",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include",
"/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/sklim/malara/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef __ACLIC__
  #define __ACLIC__ 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/HbbHbb_PreSelection_malara_Dv1_2L2M.cc"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"HbbHbb_PreSelection_malara_Dv1_2L2M", payloadCode, "@",
"JetList", payloadCode, "@",
"fillHistogramsFromJetList", payloadCode, "@",
"fillIndexVectorFromJetList", payloadCode, "@",
"jet_btag_cut_L", payloadCode, "@",
"jet_btag_cut_M", payloadCode, "@",
"jet_btag_cut_T", payloadCode, "@",
"jet_btag_cut_max", payloadCode, "@",
"jet_btag_cut_min", payloadCode, "@",
"jet_eta_cut", payloadCode, "@",
"jet_pT_cut", payloadCode, "@",
"pi", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HbbHbb_PreSelection_malara_Dv1_2L2M_cc_ACLiC_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HbbHbb_PreSelection_malara_Dv1_2L2M_cc_ACLiC_dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HbbHbb_PreSelection_malara_Dv1_2L2M_cc_ACLiC_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HbbHbb_PreSelection_malara_Dv1_2L2M_cc_ACLiC_dict() {
  TriggerDictionaryInitialization_HbbHbb_PreSelection_malara_Dv1_2L2M_cc_ACLiC_dict_Impl();
}
