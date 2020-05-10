
// Copyright (c) 2020 The YaksaFramework Authors piyoma. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef __yaksa_framework_h___
#define __yaksa_framework_h___

/*꧁༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༺TONOSHIKI PIYOMA༻༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒꧂
           
          ꧁༒༒༒༒༒༒༒༒༒༒༒༒༺☼☽☪☭----✞----☭☪☽☼༻༒༒༒༒༒༒༒༒༒༒༒༒꧂          

				✞IN HOC SIGNO VINCES✞
				Kyrie eleison, In nómine Patris, et Fílii, et Spíritus Sancti. 

                A cross-platform GUI Framework Wrapped Chromium that Can embedded All Systems and Platforms.
                eg. Windows, linux, macOS, Android, iOS, Unity, UnrealEngine4, Qt, and etc.
                2020/04/29 piyoma
                break;
                ༺GitHub https://github.com/piyoma/YaksaFramework༻    
     

		About Yaksa-Framework.h Unique Interface Define.

		///////////////////////////////////////༺TONOSHIKI PIYOMA༻///////////////////////////////////////


		This Header File implements Cross-platform Component  Design( -- call and sync-async callback -- ), 
		completely abstract,blocking the coupling between modules. 
		you can call a object simplely In any Operating Systems and Platforms, as follows:

		Foo foo;
		foo.Initialize();
		foo.asnyc_work(); // call a obj method like Yaksa.Module.Bar  or Yaksa.Module.Foo

		//Support Dynamic Load & Unload Components

		//At First should define a class like this
		//By the way, Yaksa Framework Unique Interface is Opensource code,  
		//Can Add/Extend  unlimited  C/C++ ComponentsExtensions Private or Public

		class Foo
		{
			public:
			Foo() {}
			~Foo(){}
			void asnyc_work()
			{
					
				if( component.Load(L"LocalPath", L"Yaksa.Module.Bar")  )
				{

					component.exec(value_param("FooObj"),
					value_param("bar"), 0,
					&Foo::Callee, this, 0);

				}

			}
			void Callee(type_char* obj, type_char* cmd, type_char* data_type,
					type_char* data, int len, int msgid)
			{
					//////////Do Some Asnyc Works//////////
			}

			private:
			SingleComponent<Foo>  component;
		};

		

		2020/05/01 piyoma


*/

//#define OS_ANDROID 1 //for debug test in Android Temporarily

#if defined(OS_WIN)
#include <windows.h>
#else 
#if defined(OS_LINUX)
#include <stdio.h>  
#include <stdlib.h>   
#include <dlfcn.h>   
#endif 
#endif

#include <string>

#ifdef USE_STD_FUNCTION
#include <functional>
#endif // USE_STD_FUNCTION


namespace Yaksa{

	namespace Api {


#ifndef C99_LIKE_TYPE_DEFINE
	#ifndef CXX_TYPE_DEFINE_MACRO
	#define CXX_TYPE_DEFINE_MACRO(name, type, use, cxx, \
		class_type, type_var, wrapper)
	#endif// !CXX_TYPE_DEFINE_MACRO
#else
#ifndef CXX_TYPE_DEFINE_MACRO
	#define CXX_TYPE_DEFINE_MACRO
	#endif
#endif // !C99_LIKE_DEFINE

#ifndef WRAPPER_TEMPLATE_X1
#define WRAPPER_TEMPLATE_X1(type, cxx, name, wrapper, var)\
	type<cxx name, cxx wrapper = var>
#endif // !WRAPPER_TEMPLATE_X1

#ifndef WRAPPER_TEMPLATE_X2
#define WRAPPER_TEMPLATE_X2(type, cxx, name, wrapper, var, \
		use, type_, class_type, type_var, wrapper_)\
	type<cxx name, cxx wrapper = var> \
		use type_ = cxx class_type<wrapper_, Type>::type_var;
#endif // !WRAPPER_TEMPLATE_X2

#ifndef _TYPE_TEMPLATE_
#define _TYPE_TEMPLATE_(type_)\
	WRAPPER_TEMPLATE_X1(template, typename, WrapperType, Type, type_)
#endif // !_TYPE_TEMPLATE_

#ifndef _TYPE_DEFNE_MACRO_
#define _TYPE_DEFNE_MACRO_(TYPE, use, class_type, cxx, type_var)\
	use TYPE = cxx class_type<WrapperType, Type>::type_var;
#endif // !_TYPE_DEFNE_MACRO_

/*
		//////////////////༺CODE DESCRIPTION༻//////////////////

		#define _YAKSA_DEFINE_TYPE_(TYPE, type_)\
	_TYPE_TEMPLATE_(type_)## _TYPE_DEFNE_MACRO_(TYPE, \
		using, TemplateType, typename, _Type)

		In Clang++ ocurred error: 
		" pasting formed 'cxx', an invalid preprocessing token "
		so Need special treatment

*/
#if defined(OS_WIN)
#ifndef _YAKSA_DEFINE_TYPE_ 
#define _YAKSA_DEFINE_TYPE_(TYPE, type_)\
	WRAPPER_TEMPLATE_X2(template, typename, WrapperType, Type, type_, \
		using, TYPE, TemplateType, _Type, WrapperType)
#endif // !_YAKSA_DEFINE_TYPE_
#else 
#if defined(OS_ANDROID)
#ifndef _YAKSA_DEFINE_TYPE_ 
#define _YAKSA_DEFINE_TYPE_(TYPE, type_)\
	WRAPPER_TEMPLATE_X2(template, typename, WrapperType, Type, type_, \
		using, TYPE, TemplateType, _Type, WrapperType)
#endif // !_YAKSA_DEFINE_TYPE_
#endif
#endif 
#ifndef YAKSA_DEFINE_TYPE
#define YAKSA_DEFINE_TYPE(NAME, obj, type_def, type, ptr_def, ptr);\
				_YAKSA_DEFINE_TYPE_(NAME, obj) \
				_YAKSA_DEFINE_TYPE_(type_def, type) \
				_YAKSA_DEFINE_TYPE_(ptr_def, ptr) 

#endif // !YAKSA_DEFINE_TYPE


	template<typename Type> struct TypeTemplate {
		using  Type_ = Type;
	};
	template<typename ClassType, typename Type> struct TemplateType {

		using _ClassType = typename TypeTemplate<ClassType>::Type_;
		using _ClassPtr = typename TypeTemplate<_ClassType*>::Type_;
		using _Type = typename TypeTemplate<Type>::Type_;
		using _TypePtr = typename TypeTemplate<Type*>::Type_;

	};
#if defined(OS_WIN)
	_YAKSA_DEFINE_TYPE_(ViewTypeDefine, HWND)
#else
	_YAKSA_DEFINE_TYPE_(ViewTypeDefine, void*)
#endif

#if defined(OS_WIN)
		_YAKSA_DEFINE_TYPE_(ModuleHandleDefine, HMODULE)
#else
		_YAKSA_DEFINE_TYPE_(ModuleHandleDefine, void*)
#endif

	YAKSA_DEFINE_TYPE(WideStringTypeDefine, std::wstring, WCharTypeDefine, wchar_t, WCharTypePtrDefine, wchar_t*)
	YAKSA_DEFINE_TYPE(StringTypeDefine, std::string, CharTypeDefine, char, CharTypePtrDefine, char*)


	template <typename Type,
		typename WrapperType =
		TemplateType<Type, void>,
/*
		//////////////////༺CODE DESCRIPTION༻//////////////////

		For the purpose of Neat and Order
		Finally Register All defined basic types in WrapperType
		If you do n’t like this way,
		I will append a macro definition to isolate these later
*/
		typename NativeViewType = ViewTypeDefine<Type>,
		typename NativeModuleHandle = ModuleHandleDefine<Type>,
		typename WCharStrType = WideStringTypeDefine<Type>,
		typename CharStrType = StringTypeDefine<Type>,
		typename CharType = CharTypeDefine<Type> > struct WrapperTypes {

		using _Myt = WrapperType;
		using _NativeViewType = NativeViewType;
		using _NativeModuleHandle = NativeModuleHandle;
		using _CharStrType = CharStrType;
		using _WCharStrType = WCharStrType;
		using _CharType = CharType;
	};
	template<typename L>
	struct TypeLambdaTraits : TypeLambdaTraits<decltype(&L::operator())> {};
	template<typename C, typename R, typename... A>
	struct TypeLambdaTraits<R(C::*)(A...) const> {
	};
	template<typename C, typename R, typename A>
	struct TypeLambdaTraits<R(C::*)(A) const> {
		static const bool valid = true;
		using TypeArg = typename std::remove_const<typename std::remove_reference<A>::type>::type;
		using TypeR = R;
	};
#ifndef C99_LIKE_TYPE_DEFINE

	using NativeView = WrapperTypes<void>::_NativeViewType;
	using NativeModuleHandle = WrapperTypes<void>::_NativeModuleHandle;
	using String = WrapperTypes<void>::_CharStrType;
	using WString = WrapperTypes<void>::_WCharStrType;
	using type_char = WrapperTypes<void>::_CharType;

#else

	typedef WrapperTypes<void>::_NativeViewType NativeView;
	typedef WrapperTypes<void>::_NativeModuleHandle NativeModuleHandle;
	typedef WrapperTypes<void>::_CharStrType String;
	typedef WrapperTypes<void>::_WCharStrType WString;
	typedef WrapperTypes<void>::_CharType type_char;

#endif // !C99_LIKE_DEFINE


#if defined(OS_WIN)
#if defined(YAKSA_BUILD)
	extern "C" int __declspec(dllexport)
		cdecl YaksaExec(void* obj, void* cmd, void* arg,
			void* callback, void* obj_invoke, int msgid);
#else
	extern "C" int __declspec(dllimport)
		cdecl YaksaExec(void* obj, void* cmd, void* arg,
			void* callback, void* obj_invoke, int msgid);
#endif
#endif //OS_WIN

#ifndef _STRING_Const_Ptr_
#define _STRING_Const_Ptr_(var)  var.c_str()
#endif

//////////MACRO FIN//////////

	typedef int(*InitPackageModule)(void* callback);

	typedef  int(*execPackageObjectFunc)(void* obj, void* cmd, void* arg,
		void* callback, void* obj_invoke, int msgid);

	typedef int(*onPackageCallback) (type_char* obj, type_char* cmd, type_char* data_type,
		type_char* data, int len, int msgid);

	typedef int(*typeCallback) (type_char* obj, type_char* cmd, type_char* data_type,
		type_char* data, int len, int msgid);


	template <typename type = type_char * , typename value_type = const char*>
	type cast_type(value_type v)
	{
		return reinterpret_cast<type>(const_cast<char*>(v));
	}
	template <typename const_type = const void*>
	inline type_char * cast_type(void* v)
	{
		return reinterpret_cast<type_char*>(v);
	}
#ifndef value_param

#define  value_param(v) cast_type<>(v)

#endif

	template <typename type> class defineTemplate
	{
	public:
		typedef  type* defineType;
		typedef  typeCallback callbackType;

		static type* GetInstance()
		{

			static type* instance = nullptr;

			if (instance == nullptr)
			{

				instance = new (std::nothrow) type();

			}
			return instance;
		}

		static callbackType GetObject()
		{
			defineType obj = type::GetInstance();

			if (obj)
			{
				return obj->Get();
			}
			return nullptr;
		}
		static int message_id()
		{
			defineType obj = type::GetInstance();

			if (obj)
			{
				return obj->msg_id();
			}
			return 0;
		}
	};
	class getPackageCallback :
		public defineTemplate<getPackageCallback>
	{
	public:

		getPackageCallback() :message_id_(0), other_module(nullptr) {};

		virtual ~getPackageCallback() {};


		typeCallback Get() { return other_module; };
		void Set(typeCallback v) { other_module = v; };

		int msg_id()
		{
			message_id_ += 1;
			return message_id_;
		}

	private:

		int message_id_;
		typeCallback other_module;
	};

#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr)
#endif

#define DATA_DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&); \
	void operator=(const TypeName&)
#define  DATA_CONNECTOR_OBJ_NAME(NAME) virtual const char* obj_id() \
	override {return NAME;}
#ifndef DATA_DECL
#define  DATA_DECL(name) void name(type_char* obj, type_char* cmd, type_char* data_type,\
type_char* data, int len, int msgid);
#endif

#ifndef EXPORT_DECL
#define  EXPORT_DECL(name, ret, ...) void name(type_char* obj, type_char* cmd, type_char* data_type,\
type_char* data, int len, int msgid);
#endif

#ifndef dataPackageExec
#define  dataPackageExec(func, obj, cmd, arg, callback, handler, msgid, type) \
	func(obj, cmd, arg, callback, dataBind<type>(callback, this), msgid)
#endif

#ifndef CallExec //local 
#define CallExec(obj, cmd, arg, handler)\
	dataPackageExec(YaksaCall, obj, cmd, arg, nullptr, handler, -1, nullptr, -1)
#endif 

#ifndef YaksaDispatchEvent
#define YaksaDispatchEvent(obj, event_name, arg)\
	dataPackageExec(YaksaCall, obj, event_name, arg, nullptr, nullptr, -1, nullptr, -1)
#endif 

#ifndef CallRPC //remote
#define RpcExec(obj, cmd, arg, handler)\
	dataPackageExec(YaksaCall, obj, cmd, arg, nullptr, handler, -1, nullptr, -1)
#endif 

#ifndef dataExecNULL
#define  dataExecNULL(YaksaCall, obj, cmd, arg) \
	func(obj, cmd, arg, 0, 0, 0);
#endif

#ifndef YaksaCallee
#define YaksaCallee(type, callback, callee)\
	dataBind<type>(callback, callee)
#endif // !YaksaCallback

	struct IFunction_OwnedObject
	{
	
		virtual void* CloneToEmptyStorage(void* Storage) const = 0;

		virtual void* GetAddress() = 0;

		virtual void Destroy() = 0;

		virtual ~IFunction_OwnedObject() = default;
	};
	struct FFunctionStorage
	{
		FFunctionStorage()
			: HeapAllocation(nullptr)
		{
		}

		FFunctionStorage(FFunctionStorage&& Other)
			: HeapAllocation(Other.HeapAllocation)
		{
			Other.HeapAllocation = nullptr;
		}

		FFunctionStorage(const FFunctionStorage& Other) = delete;
		FFunctionStorage& operator=(FFunctionStorage&& Other) = delete;
		FFunctionStorage& operator=(const FFunctionStorage& Other) = delete;

		void* BindCopy(const FFunctionStorage& Other)
		{
			void* NewObj = Other.GetBoundObject()->CloneToEmptyStorage(this);
			return NewObj;
		}

		IFunction_OwnedObject* GetBoundObject() const
		{
			IFunction_OwnedObject* Result = (IFunction_OwnedObject*)HeapAllocation;

			return Result;
		}

		void* GetPtr() const
		{
			return ((IFunction_OwnedObject*)HeapAllocation)->GetAddress();
		}

		void Unbind()
		{
			IFunction_OwnedObject* Owned = GetBoundObject();
			Owned->Destroy();
		}

		void* HeapAllocation;

	};

	class dataObjEventHandler;

	class dataRefBase
	{
	public:
		bool HasOneRef() const { return ref_count_ == 1; }
		unsigned int GetRefCounted() { return ref_count_; }
	protected:
		dataRefBase() : ref_count_(0) {};
		virtual ~dataRefBase() {};

		virtual void add_ref() const
		{
			++ref_count_; //maybe unsafe
		}

		virtual bool release() const
		{

			if (--ref_count_ == 0)
			{
				return true;
			}
			return false;
		}

	private:
		mutable int ref_count_;
		DATA_DISALLOW_COPY_AND_ASSIGN(dataRefBase);
	};
	template<typename T>
	class dataRefCounter : public dataRefBase
	{
	public:
		dataRefCounter() {}
		~dataRefCounter() {}

		void AddRef() const
		{
			dataRefBase::add_ref();
		}

		void Release() const
		{
			if (dataRefBase::release())
			{
				delete static_cast<const T*>(this);
			}
		}

	private:
		DATA_DISALLOW_COPY_AND_ASSIGN(dataRefCounter<T>);
	};
	template<typename type>
	class dataObj
		: public dataRefCounter<type>
	{
	public:

		dataObj() {}
		~dataObj() {}
		virtual void exec(void* obj, void* cmd, void* arg,
			void* callback, void* obj_invoke, int msgid) {};
		virtual void addCallee(type_char* id, dataObjEventHandler* handler) {}
		virtual const char* obj_id() { return ""; }

	};

	class  dataObjEventHandler
		: public  dataObj<dataObjEventHandler>
	{
	public:

		dataObjEventHandler()
		{
			AddRef();
		};

		virtual ~dataObjEventHandler() {};

		virtual void invoke(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid) = 0;

	};
	template<typename P, typename T>
	class objEventHandlerImpl : public dataObjEventHandler
	{
	public:
		typedef void (T::* Sig)(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid);

		 //Currently not use std::function

#ifdef USE_STD_FUNCTION
		typedef std::function<void(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid)> stdSig;
#endif

		objEventHandlerImpl(P* obj, Sig sig) : obj_(obj), func_(sig) {};

		virtual void invoke(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid)
		{
			(obj_->*func_)(obj, cmd, data_type, data, len, msgid);

			//Release();
		};

	private:
		T*  obj_;
		Sig func_;
	};

	template <typename P, typename T = P>
	objEventHandlerImpl<P, T>* dataBind(void (T::* sig)(type_char* obj, type_char* cmd, type_char* data_type,
		type_char* data, int len, int msgid), P* o)
	{
		return new objEventHandlerImpl<P, T>(o, sig);
	};
	
	template<typename type = dataObjEventHandler>
	class dataPackageTemplate {
	public:
		typedef dataObjEventHandler objType;
		typedef objType* poiter_type;
		typedef poiter_type objCallbackType_;
	};
	typedef dataPackageTemplate<> dataPackage;

	typedef dataPackage::objCallbackType_ objCallbackType;
	template <typename T>
	class TypeCast {
		typedef void (T::* sig)(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid); 
	};
	template<typename Obj> class SingleComponent{
	public:

#ifdef USE_STD_FUNCTION
		typedef std::function<void(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid)> stdSig;
#endif

		typedef void (Obj::* Sig)(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid);

		SingleComponent() {};
		~SingleComponent() {};

#if defined(OS_WIN)
		bool Load(WString path, WString module_name){

			NativeModuleHandle module
				= nullptr;
			WString dllPath =
				path + module_name; 
			dllPath += L".dll";
			module = LoadLibraryW(
				_STRING_Const_Ptr_(dllPath)
			);
			if (module)
			{
					execPackageObj
						= (execPackageObjectFunc)
						GetProcAddress(module, "YaksaExec");

				return true;
			}
			return false;
		 }
#else
		bool Load(type_char* path, type_char*module_name) {

#if defined(OS_LINUX)

			NativeModuleHandle module
				= nullptr;
			type_str dllPath = path;
			path += module_name;
			dllPath += L".so";
			module = dlopen(_STRING_Const_Ptr_(dllPath), RTLD_LAZY);

			);
			if (module)
			{
				execPackageObjectFunc execPackageObj
					= (execPackageObjectFunc)
					dlsym(module, "YaksaExec");

				return true;
			}
			return false;
#else
			return false;
#endif
		
		}
#endif
		
		void exec(void* obj, void* cmd, void* arg,
			Sig callback, Obj* caller, int msgid)
		{
			if (execPackageObj) {

				execPackageObj(obj, cmd, arg, YaksaCallee(Obj, callback, caller), 0, msgid);
			}
		}
	private:
		execPackageObjectFunc execPackageObj = nullptr;
	};

	}//Api

}//Yaksa

#endif
