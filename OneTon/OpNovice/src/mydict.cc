// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dOdOdIsrcdImydict

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
#include "../include/OnetonTrackerHit.hh"
#include "G4VHit.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "G4Types.hh"
#include "tls.hh"
#include "templates.hh"
#include "G4ExceptionSeverity.hh"
#include "G4THitsCollection.hh"
#include "G4VHitsCollection.hh"
#include "G4Allocator.hh"
#include "G4AllocatorPool.hh"
#include "/Users/djaffe/work/GEANT4work/geant4.10.1-install/include/Geant4/G4ThreeVector.hh"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Utility/defs.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *OnetonTrackerHit_Dictionary();
   static void OnetonTrackerHit_TClassManip(TClass*);
   static void *new_OnetonTrackerHit(void *p = 0);
   static void *newArray_OnetonTrackerHit(Long_t size, void *p);
   static void delete_OnetonTrackerHit(void *p);
   static void deleteArray_OnetonTrackerHit(void *p);
   static void destruct_OnetonTrackerHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OnetonTrackerHit*)
   {
      ::OnetonTrackerHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::OnetonTrackerHit),0);
      static ::ROOT::TGenericClassInfo 
         instance("OnetonTrackerHit", "../include/OnetonTrackerHit.hh", 44,
                  typeid(::OnetonTrackerHit), DefineBehavior(ptr, ptr),
                  &OnetonTrackerHit_Dictionary, isa_proxy, 0,
                  sizeof(::OnetonTrackerHit) );
      instance.SetNew(&new_OnetonTrackerHit);
      instance.SetNewArray(&newArray_OnetonTrackerHit);
      instance.SetDelete(&delete_OnetonTrackerHit);
      instance.SetDeleteArray(&deleteArray_OnetonTrackerHit);
      instance.SetDestructor(&destruct_OnetonTrackerHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OnetonTrackerHit*)
   {
      return GenerateInitInstanceLocal((::OnetonTrackerHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::OnetonTrackerHit*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *OnetonTrackerHit_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::OnetonTrackerHit*)0x0)->GetClass();
      OnetonTrackerHit_TClassManip(theClass);
   return theClass;
   }

   static void OnetonTrackerHit_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *CLHEPcLcLHep3Vector_Dictionary();
   static void CLHEPcLcLHep3Vector_TClassManip(TClass*);
   static void *new_CLHEPcLcLHep3Vector(void *p = 0);
   static void *newArray_CLHEPcLcLHep3Vector(Long_t size, void *p);
   static void delete_CLHEPcLcLHep3Vector(void *p);
   static void deleteArray_CLHEPcLcLHep3Vector(void *p);
   static void destruct_CLHEPcLcLHep3Vector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CLHEP::Hep3Vector*)
   {
      ::CLHEP::Hep3Vector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::CLHEP::Hep3Vector),0);
      static ::ROOT::TGenericClassInfo 
         instance("CLHEP::Hep3Vector", "ThreeVector.h", 41,
                  typeid(::CLHEP::Hep3Vector), DefineBehavior(ptr, ptr),
                  &CLHEPcLcLHep3Vector_Dictionary, isa_proxy, 0,
                  sizeof(::CLHEP::Hep3Vector) );
      instance.SetNew(&new_CLHEPcLcLHep3Vector);
      instance.SetNewArray(&newArray_CLHEPcLcLHep3Vector);
      instance.SetDelete(&delete_CLHEPcLcLHep3Vector);
      instance.SetDeleteArray(&deleteArray_CLHEPcLcLHep3Vector);
      instance.SetDestructor(&destruct_CLHEPcLcLHep3Vector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CLHEP::Hep3Vector*)
   {
      return GenerateInitInstanceLocal((::CLHEP::Hep3Vector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CLHEP::Hep3Vector*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *CLHEPcLcLHep3Vector_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::CLHEP::Hep3Vector*)0x0)->GetClass();
      CLHEPcLcLHep3Vector_TClassManip(theClass);
   return theClass;
   }

   static void CLHEPcLcLHep3Vector_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_OnetonTrackerHit(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::OnetonTrackerHit : new ::OnetonTrackerHit;
   }
   static void *newArray_OnetonTrackerHit(Long_t nElements, void *p) {
      return p ? new(p) ::OnetonTrackerHit[nElements] : new ::OnetonTrackerHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_OnetonTrackerHit(void *p) {
      delete ((::OnetonTrackerHit*)p);
   }
   static void deleteArray_OnetonTrackerHit(void *p) {
      delete [] ((::OnetonTrackerHit*)p);
   }
   static void destruct_OnetonTrackerHit(void *p) {
      typedef ::OnetonTrackerHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::OnetonTrackerHit

namespace ROOT {
   // Wrappers around operator new
   static void *new_CLHEPcLcLHep3Vector(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::CLHEP::Hep3Vector : new ::CLHEP::Hep3Vector;
   }
   static void *newArray_CLHEPcLcLHep3Vector(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::CLHEP::Hep3Vector[nElements] : new ::CLHEP::Hep3Vector[nElements];
   }
   // Wrapper around operator delete
   static void delete_CLHEPcLcLHep3Vector(void *p) {
      delete ((::CLHEP::Hep3Vector*)p);
   }
   static void deleteArray_CLHEPcLcLHep3Vector(void *p) {
      delete [] ((::CLHEP::Hep3Vector*)p);
   }
   static void destruct_CLHEPcLcLHep3Vector(void *p) {
      typedef ::CLHEP::Hep3Vector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CLHEP::Hep3Vector

namespace {
  void TriggerDictionaryInitialization_mydict_Impl() {
    static const char* headers[] = {
"../include/OnetonTrackerHit.hh",
"G4VHit.hh",
"globals.hh",
"G4ios.hh",
"G4Types.hh",
"tls.hh",
"templates.hh",
"G4ExceptionSeverity.hh",
"G4THitsCollection.hh",
"G4VHitsCollection.hh",
"G4Allocator.hh",
"G4AllocatorPool.hh",
"/Users/djaffe/work/GEANT4work/geant4.10.1-install/include/Geant4/G4ThreeVector.hh",
"CLHEP/Vector/ThreeVector.h",
"CLHEP/Utility/defs.h",
0
    };
    static const char* includePaths[] = {
"/Users/djaffe/work/ROOT_v6.02.05work/root-6.02.05-install/include",
"/Users/djaffe/work/GIT/G4ONETON/OneTon/OpNovice/OpNovice-build/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$../include/OnetonTrackerHit.hh")))  OnetonTrackerHit;
namespace CLHEP{class __attribute__((annotate("$clingAutoload$../include/OnetonTrackerHit.hh")))  Hep3Vector;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "../include/OnetonTrackerHit.hh"
#include "G4VHit.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "G4Types.hh"
#include "tls.hh"
#include "templates.hh"
#include "G4ExceptionSeverity.hh"
#include "G4THitsCollection.hh"
#include "G4VHitsCollection.hh"
#include "G4Allocator.hh"
#include "G4AllocatorPool.hh"
#include "/Users/djaffe/work/GEANT4work/geant4.10.1-install/include/Geant4/G4ThreeVector.hh"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Utility/defs.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"CLHEP::Hep3Vector", payloadCode, "@",
"OnetonTrackerHit", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("mydict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_mydict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_mydict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_mydict() {
  TriggerDictionaryInitialization_mydict_Impl();
}
