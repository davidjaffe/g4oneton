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
#include "CLHEP/Vector/ThreeVector.h"
#include "../include/OnetonUserTrackInformation.hh"
#include "/Users/djaffe/work/ROOT_v6.02.05work/root-6.02.05-install/include/RConfig.h"

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
         instance("OnetonTrackerHit", "../include/OnetonTrackerHit.hh", 46,
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
   static TClass *OnetonUserTrackInformation_Dictionary();
   static void OnetonUserTrackInformation_TClassManip(TClass*);
   static void *new_OnetonUserTrackInformation(void *p = 0);
   static void *newArray_OnetonUserTrackInformation(Long_t size, void *p);
   static void delete_OnetonUserTrackInformation(void *p);
   static void deleteArray_OnetonUserTrackInformation(void *p);
   static void destruct_OnetonUserTrackInformation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OnetonUserTrackInformation*)
   {
      ::OnetonUserTrackInformation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::OnetonUserTrackInformation),0);
      static ::ROOT::TGenericClassInfo 
         instance("OnetonUserTrackInformation", "../include/OnetonUserTrackInformation.hh", 52,
                  typeid(::OnetonUserTrackInformation), DefineBehavior(ptr, ptr),
                  &OnetonUserTrackInformation_Dictionary, isa_proxy, 0,
                  sizeof(::OnetonUserTrackInformation) );
      instance.SetNew(&new_OnetonUserTrackInformation);
      instance.SetNewArray(&newArray_OnetonUserTrackInformation);
      instance.SetDelete(&delete_OnetonUserTrackInformation);
      instance.SetDeleteArray(&deleteArray_OnetonUserTrackInformation);
      instance.SetDestructor(&destruct_OnetonUserTrackInformation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OnetonUserTrackInformation*)
   {
      return GenerateInitInstanceLocal((::OnetonUserTrackInformation*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::OnetonUserTrackInformation*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *OnetonUserTrackInformation_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::OnetonUserTrackInformation*)0x0)->GetClass();
      OnetonUserTrackInformation_TClassManip(theClass);
   return theClass;
   }

   static void OnetonUserTrackInformation_TClassManip(TClass* ){
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
   static void *new_OnetonUserTrackInformation(void *p) {
      return  p ? new(p) ::OnetonUserTrackInformation : new ::OnetonUserTrackInformation;
   }
   static void *newArray_OnetonUserTrackInformation(Long_t nElements, void *p) {
      return p ? new(p) ::OnetonUserTrackInformation[nElements] : new ::OnetonUserTrackInformation[nElements];
   }
   // Wrapper around operator delete
   static void delete_OnetonUserTrackInformation(void *p) {
      delete ((::OnetonUserTrackInformation*)p);
   }
   static void deleteArray_OnetonUserTrackInformation(void *p) {
      delete [] ((::OnetonUserTrackInformation*)p);
   }
   static void destruct_OnetonUserTrackInformation(void *p) {
      typedef ::OnetonUserTrackInformation current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::OnetonUserTrackInformation

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
"CLHEP/Vector/ThreeVector.h",
"../include/OnetonUserTrackInformation.hh",
"/Users/djaffe/work/ROOT_v6.02.05work/root-6.02.05-install/include/RConfig.h",
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
class __attribute__((annotate("$clingAutoload$../include/OnetonUserTrackInformation.hh")))  OnetonUserTrackInformation;
namespace CLHEP{class __attribute__((annotate("$clingAutoload$../include/OnetonTrackerHit.hh")))  Hep3Vector;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "../include/OnetonTrackerHit.hh"
#include "CLHEP/Vector/ThreeVector.h"
#include "../include/OnetonUserTrackInformation.hh"
#include "/Users/djaffe/work/ROOT_v6.02.05work/root-6.02.05-install/include/RConfig.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"CLHEP::Hep3Vector", payloadCode, "@",
"OnetonTrackerHit", payloadCode, "@",
"OnetonUserTrackInformation", payloadCode, "@",
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
