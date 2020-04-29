
// Copyright (c) 2011 The YaksaFramework Authors piyoma. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef __yaksa_framework_h___
#define __yaksa_framework_h___

////--꧁༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༺TONOSHIKI PIYOMA༻༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒꧂
////           
////                  A cross-platform GUI Framework Wrapped Chromium that Can embedded All Systems and Platforms.
////                  eg. Windows, linux, macOS, Android, iOS, Unity, UnrealEngine4, Qt, and etc.
////                  2020/04/29 piyoma
////
////                  ༺GitHub https://github.com/piyoma/YaksaFramework༻    
////                                                
////--꧁༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒꧂


#if defined(OS_WIN)
#include <windows.h>
#endif

#include <string>

namespace Yaksa{

	namespace dataConnectApi {

	template<typename type> struct template_type {
		using  type_t = type;
	};
	template<typename ClassType,
		typename Type> struct TemplateType {

		using _ClassType = typename template_type<ClassType>::type_t;
		using _ClassPtr = typename template_type<_ClassType *>::type_t;
		using _Type = typename template_type<Type>::type_t;
		using _TypePtr = typename template_type<Type*>::type_t;

	};
#if defined(OS_WIN)
	template <typename WrapperType, typename Type = HWND>
	using ViewTypeDefine =
		typename TemplateType<WrapperType, Type>::_Type;
#else
	template <typename WrapperType, typename Type = void*>
	using ViewTypeDefine =
		typename TemplateType<WrapperType, Type>::_Type;
#endif

	template <typename WrapperType, typename Type = std::wstring>
	using WideStringTypeDefine =
		typename TemplateType<WrapperType, Type>::_Type;
	template <typename WrapperType, typename Type = wchar_t>
	using WCharTypeDefine =
		typename TemplateType<WrapperType, Type>::_Type;
	template <typename WrapperType, typename Type = wchar_t>
	using WCharTypePtrDefine =
		typename TemplateType<WrapperType, Type>::_Type*;

	template <typename WrapperType, typename Type = std::string>
	using StringTypeDefine =
		typename TemplateType<WrapperType, Type>::_Type;
	template <typename WrapperType, typename Type = char>
	using CharTypeDefine =
		typename TemplateType<WrapperType, Type>::_Type;
	template <typename WrapperType, typename Type = char>
	using CharTypePtrDefine =
		typename TemplateType<WrapperType, Type>::_Type*;

	template <typename Type,
		typename WrapperType =
		TemplateType<Type, void>,
		typename NativeViewType = ViewTypeDefine<Type>,
		typename WCharStrType = WideStringTypeDefine<Type>,
		typename CharType = CharTypeDefine<Type>,
		typename NativeViewType_ = NativeViewType,
		typename WCharStrType_ = WCharStrType,
		typename CharType_ = CharType>struct WrapperTypes {

		using _Myt = WrapperType;
		using _NativeViewType = NativeViewType;
		using _WCharStrType = WCharStrType_;
		using _CharType = CharType_;
	};

	using WindowType = WrapperTypes<void>::_NativeViewType;
	using wstrType = WrapperTypes<void>::_WCharStrType;
	using type_char = WrapperTypes<void>::_CharType;

#if defined(DATA_PACKAGE_BUILD)
	extern "C" int __declspec(dllexport)
		cdecl execPackageObject(void* obj, void* cmd, void* arg,
			void* callback, void* obj_invoke, int msgid);
#else


#endif
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
			++ref_count_;
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
	class dataObj
		: public dataRefCounter<dataObj>
	{
	public:

		dataObj() {}
		~dataObj() {}
		virtual void AddEventHandler(dataObjEventHandler* handler) {}
		virtual const char* obj_id() { return ""; }

	};

	class  dataObjEventHandler
		: public  dataObj
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


		objEventHandlerImpl(P* obj, Sig sig) : obj_(obj), func_(sig) {};

		virtual void invoke(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid)
		{
			(obj_->*func_)(obj, cmd, data_type, data, len, msgid);

			Release();
		};

	private:
		Sig func_;
		T*  obj_;
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
			type_char* data, int len, int msgid);;
	};
#ifndef DATA_DECL
#define  DATA_DECL(name) void name(type_char* obj, type_char* cmd, type_char* data_type,\
type_char* data, int len, int msgid);
#endif

#ifndef dataPackageExec
#define  dataPackageExec(func, obj, cmd, arg, callback, handler, msgid, caller, type) \
	func(obj, cmd, arg, callback, dataBind<type>(&handler, caller), msgid);
#endif

#ifndef dataExecNULL
#define  dataExecNULL(func, obj, cmd, arg) \
	func(obj, cmd, arg, 0, 0, 0);
#endif

	}//dataConnectApi

}//Yaksa

#endif
