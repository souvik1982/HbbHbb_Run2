// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIscratchdImalaradIWorkingAreadIHbbHbb_Run2dIAnalysisCodedIsklimdImalaradIdOdIdOdOdIdOdOdIHbbHbb_PreSelection_cc_ACLiC_dict

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
#include "/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/sklim/malara/./../../HbbHbb_PreSelection.cc"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_HbbHbb_PreSelection_cc_ACLiC_dict_Impl() {
    static const char* headers[] = {
"./../../HbbHbb_PreSelection.cc",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/include",
"/scratch/malara/WorkingArea/CMSSW_8_0_25/src",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_8_0_25/src",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/coral/CORAL_2_3_21-ikhhed8/include/LCG",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/mctester/1.25.0a-ikhhed6/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/qt/4.8.7/include/QtDesigner",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/tauolapp/1.1.5-ikhhed5/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/charybdis/1.003-ikhhed4/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/thepeg/1.9.2p1-ikhhed4/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/sherpa/2.2.0-ikhhed7/include/SHERPA-MC",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/qt/4.8.7/include/QtOpenGL",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/qt/4.8.7/include/QtGui",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/pythia8/212-ikhhed5/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/herwig/6.521-ikhhed4/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/qt/4.8.7/include/Qt3Support",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/classlib/3.1.3-ikhhed/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/lhapdf/6.1.6-ikhhed2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/cgal/4.2-ikhhed2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/tkonlinesw/4.0.0-1-ikhhed5/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/starlight/r193-ikhhed2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/qt/4.8.7/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/qt/4.8.7/include/Qt",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/qt/4.8.7/include/QtCore",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/qt/4.8.7/include/QtXml",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/mcdb/1.0.2/interface",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/libungif/4.1.4/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/libtiff/4.0.3/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/libpng/1.6.16/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/geant4/10.00.p03-ikhhed3/include/Geant4",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/frontier_client/2.8.20-ikhhed/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/pcre/8.37/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/boost/1.57.0-ikhhed2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/xz/5.2.1/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/xrootd/4.5.0-ikhhed/include/xrootd/private",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/vdt/v0.3.2-giojec2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/valgrind/3.11.0/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/utm/r47119-xsd310-patch-ikhhed/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/toprex/4.23/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/tbb/44_20151115oss/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/tauola/27.121.5/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/sigcpp/2.6.2/include/sigc++-2.0",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/rivet/2.4.0-ikhhed3/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/sqlite/3.12.2-giojec2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/protobuf/2.4.1/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/pacparser/1.3.5/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/oracle/11.2.0.3.0__10.2.0.4.0-ikhhed/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/meschach/1.2.pCMS1/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/libhepml/0.2.1/interface",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/ktjet/1.06-ikhhed3/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/jimmy/4.2-ikhhed4/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/jemalloc/4.2.1/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/herwigpp/2.7.1-ikhhed4/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/heppdt/3.03.00-giojec/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/hector/1.3.4_patch1-ikhhed6/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gsl/1.16/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/libjpeg-turbo/1.3.1/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/giflib/4.2.3/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/xerces-c/2.8.0/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gdbm/1.10/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/freetype/2.5.3/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/fftw3/3.3.2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/fftjet/1.5.0/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/fastjet/3.1.0/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/expat/2.1.0/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/hepmc/2.06.07/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/dpm/1.8.0.1/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/dcap/2.47.8/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/libxml2/2.9.1/include/libxml2",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/curl/7.47.1/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/cppunit/1.12.1/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/clhep/2.2.0.4-ikhhed3/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/openssl/1.0.2d/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/pythia6/426/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/photos/215.5/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/zlib/1.2.8/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/libuuid/2.22.2/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/castor/2.1.13.9/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/castor/2.1.13.9/include/shift",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/cascade/2.2.04-ikhhed4/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/bz2lib/1.0.6/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/python/2.7.11-ikhhed2/include/python2.7",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gcc/5.3.0/include/c++/5.3.0",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gcc/5.3.0/include/c++/5.3.0/x86_64-pc-linux-gnu",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gcc/5.3.0/include/c++/5.3.0/backward",
"/usr/local/include",
"/usr/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/etc",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gcc/5.3.0/bin/../lib/gcc/x86_64-pc-linux-gnu/5.3.0/../../../../include/c++/5.3.0",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gcc/5.3.0/bin/../lib/gcc/x86_64-pc-linux-gnu/5.3.0/../../../../include/c++/5.3.0/x86_64-pc-linux-gnu",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gcc/5.3.0/bin/../lib/gcc/x86_64-pc-linux-gnu/5.3.0/../../../../include/c++/5.3.0/backward",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/build/interpreter/cling/include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/etc/cling",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/root-6.06.00",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/build/include",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/root-6.06.00/graf3d/g3d/inc",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/root-6.06.00/gui/gui/inc",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/root-6.06.00/io/io/inc",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/root-6.06.00/core/base/../textinput/src",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/build/core/base/",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/build/core/rint/",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/build/core/thread/",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/build/io/io/",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/root-6.06.00/hist/hist/inc",
"/build/cmsbuild/auto-builds/CMSSW_8_0_25-slc6_amd64_gcc530/build/CMSSW_8_0_25-build/BUILD/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/build/math/mathcore/",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed6/include",
"/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/sklim/malara/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "HbbHbb_PreSelection_cc_ACLiC_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "HbbHbb_PreSelection_cc_ACLiC_dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef __ACLIC__
  #define __ACLIC__ 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "./../../HbbHbb_PreSelection.cc"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"HbbHbb_PreSelection", payloadCode, "@",
"JetList", payloadCode, "@",
"fillHistogramsFromJetList", payloadCode, "@",
"fillIndexVectorFromJetList", payloadCode, "@",
"jet_btag_cut", payloadCode, "@",
"jet_eta_cut", payloadCode, "@",
"jet_pT_cut", payloadCode, "@",
"pi", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HbbHbb_PreSelection_cc_ACLiC_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HbbHbb_PreSelection_cc_ACLiC_dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HbbHbb_PreSelection_cc_ACLiC_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HbbHbb_PreSelection_cc_ACLiC_dict() {
  TriggerDictionaryInitialization_HbbHbb_PreSelection_cc_ACLiC_dict_Impl();
}
