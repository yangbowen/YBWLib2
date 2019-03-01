#ifndef _WIN32_WINNT
#error This header file is only to be used when you're targeting Microsoft Windows. If you are, set the targetted windows version before including this header file.
#endif

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_7FE57E16_A6C7_4720_BBEF_D96F80AAAD3E
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_60945213_0959_4DF4_A7A2_2D7B961CF50D
#define _INCLUDE_GUARD_60945213_0959_4DF4_A7A2_2D7B961CF50D

#include <minwindef.h>
#include "../YBWLib2Api.h"
#include "../DynamicType/DynamicType.h"
#include "Exception.h"

#include "../UserInterface/UserInterface.h"

namespace YBWLib2 {
#pragma region Exception interface classes
	//{ Exception interface classes

	/// <summary>An exception that occurs because of failing to call an external API. The API has provided a last-error code.</summary>
	class IExternalAPIFailureWithLastErrorException abstract : public virtual IExternalAPIFailureException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IExternalAPIFailureWithLastErrorException, YBWLIB2_API, "203beab9-64dd-45a2-b45d-c5d8cade37ea");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IExternalAPIFailureWithLastErrorException);
		inline virtual ~IExternalAPIFailureWithLastErrorException() = default;
		/// <summary>Gets the last-error code.</summary>
		virtual DWORD GetLastErrorCode() const noexcept = 0;
	};
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
	/// <summary>An exception that occurs because of failing to call an external API. The API has provided a WSA last-error code.</summary>
	class IExternalAPIFailureWithWSALastErrorException abstract : public virtual IExternalAPIFailureException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IExternalAPIFailureWithWSALastErrorException, YBWLIB2_API, "589bd947-c55c-495d-ba08-b75f56ce0413");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IExternalAPIFailureWithWSALastErrorException);
		inline virtual ~IExternalAPIFailureWithWSALastErrorException() = default;
		/// <summary>Gets the WSA last-error code.</summary>
		virtual int GetWSALastErrorCode() const noexcept = 0;
	};
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
	/// <summary>An exception that occurs because of failing to call an external API. The API has provided a NTSTATUS code.</summary>
	class IExternalAPIFailureWithNTSTATUSException abstract : public virtual IExternalAPIFailureException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IExternalAPIFailureWithNTSTATUSException, YBWLIB2_API, "f31eb703-7dce-4563-936a-fdf24620bdb8");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IExternalAPIFailureWithNTSTATUSException);
		inline virtual ~IExternalAPIFailureWithNTSTATUSException() = default;
		/// <summary>Gets the NTSTATUS code.</summary>
		virtual NTSTATUS GetNTSTATUSCode() const noexcept = 0;
	};
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
	/// <summary>An exception that occurs because of failing to call an external API. The API has provided a HRESULT code.</summary>
	class IExternalAPIFailureWithHRESULTException abstract : public virtual IExternalAPIFailureException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IExternalAPIFailureWithHRESULTException, YBWLIB2_API, "fc1a966c-160b-4770-81af-0e58d1fe433f");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IExternalAPIFailureWithHRESULTException);
		inline virtual ~IExternalAPIFailureWithHRESULTException() = default;
		/// <summary>Gets the HRESULT code.</summary>
		virtual HRESULT GetHRESULTCode() const noexcept = 0;
	};
#endif

	//}
#pragma endregion Exception classes that may be transferred across executable module boundaries.

#pragma region Exception implementation classes
	//{ Exception implementation classes

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4250)
#endif
	/// <summary>
	/// A default implementation of <c>IExternalAPIFailureWithLastErrorException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IExternalAPIFailureWithLastErrorException</c>.
	/// </summary>
	class ExternalAPIFailureWithLastErrorException
		: public virtual ExternalAPIFailureException,
		public virtual IExternalAPIFailureWithLastErrorException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(ExternalAPIFailureWithLastErrorException, , "fead69a8-4bff-4eaf-95a9-c235784a827d");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ExternalAPIFailureWithLastErrorException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>ExternalAPIFailureWithLastErrorException</c> object.</summary>
		/// <param name="_name_api">
		/// The name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_size_name_api">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, pass <c>0</c>.
		/// </param>
		/// <param name="_address_api">
		/// The address to the external API, if available.
		/// If no meaningful address can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_lasterr">The last-error code.</param>
		inline ExternalAPIFailureWithLastErrorException(const char* _name_api, size_t _size_name_api, const void* _address_api, DWORD _lasterr) noexcept
			: ExternalAPIFailureException(_name_api, _size_name_api, _address_api),
			lasterr(_lasterr) {}
		inline virtual ~ExternalAPIFailureWithLastErrorException() = default;
		/// <summary>Gets the last-error code.</summary>
		inline virtual DWORD GetLastErrorCode() const noexcept override { return this->lasterr; }
	protected:
		const DWORD lasterr;
	};
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
	/// <summary>
	/// A default implementation of <c>IExternalAPIFailureWithWSALastErrorException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IExternalAPIFailureWithWSALastErrorException</c>.
	/// </summary>
	class ExternalAPIFailureWithWSALastErrorException
		: public virtual ExternalAPIFailureException,
		public virtual IExternalAPIFailureWithWSALastErrorException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(ExternalAPIFailureWithWSALastErrorException, , "c341f9cf-e4f5-411f-b983-cdf780406870");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ExternalAPIFailureWithWSALastErrorException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>ExternalAPIFailureWithWSALastErrorException</c> object.</summary>
		/// <param name="_name_api">
		/// The name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_size_name_api">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, pass <c>0</c>.
		/// </param>
		/// <param name="_address_api">
		/// The address to the external API, if available.
		/// If no meaningful address can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_wsalasterr">The WSA last-error code.</param>
		inline ExternalAPIFailureWithWSALastErrorException(const char* _name_api, size_t _size_name_api, const void* _address_api, int _wsalasterr) noexcept
			: ExternalAPIFailureException(_name_api, _size_name_api, _address_api),
			wsalasterr(_wsalasterr) {}
		inline virtual ~ExternalAPIFailureWithWSALastErrorException() = default;
		/// <summary>Gets the WSA last-error code.</summary>
		inline virtual int GetWSALastErrorCode() const noexcept override { return this->wsalasterr; }
	protected:
		const int wsalasterr;
	};
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
	/// <summary>
	/// A default implementation of <c>IExternalAPIFailureWithNTSTATUSException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IExternalAPIFailureWithNTSTATUSException</c>.
	/// </summary>
	class ExternalAPIFailureWithNTSTATUSException
		: public virtual ExternalAPIFailureException,
		public virtual IExternalAPIFailureWithNTSTATUSException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(ExternalAPIFailureWithNTSTATUSException, , "74ddcd1a-b4b4-403e-a868-fb8f0be9c1e1");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ExternalAPIFailureWithNTSTATUSException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>ExternalAPIFailureWithNTSTATUSException</c> object.</summary>
		/// <param name="_name_api">
		/// The name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_size_name_api">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, pass <c>0</c>.
		/// </param>
		/// <param name="_address_api">
		/// The address to the external API, if available.
		/// If no meaningful address can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_ntstatus">The NTSTATUS code.</param>
		inline ExternalAPIFailureWithNTSTATUSException(const char* _name_api, size_t _size_name_api, const void* _address_api, NTSTATUS _ntstatus) noexcept
			: ExternalAPIFailureException(_name_api, _size_name_api, _address_api),
			ntstatus(_ntstatus) {}
		inline virtual ~ExternalAPIFailureWithNTSTATUSException() = default;
		/// <summary>Gets the NTSTATUS code.</summary>
		inline virtual NTSTATUS GetNTSTATUSCode() const noexcept override { return this->ntstatus; }
	protected:
		const NTSTATUS ntstatus;
	};
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
	/// <summary>
	/// A default implementation of <c>IExternalAPIFailureWithHRESULTException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IExternalAPIFailureWithHRESULTException</c>.
	/// </summary>
	class ExternalAPIFailureWithHRESULTException
		: public virtual ExternalAPIFailureException,
		public virtual IExternalAPIFailureWithHRESULTException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(ExternalAPIFailureWithHRESULTException, , "6b2bb9f9-4db4-4f3f-83a2-14d03f6d5ae9");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ExternalAPIFailureWithHRESULTException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>ExternalAPIFailureWithHRESULTException</c> object.</summary>
		/// <param name="_name_api">
		/// The name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_size_name_api">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the external API, if available.
		/// If no meaningful name can be provided, pass <c>0</c>.
		/// </param>
		/// <param name="_address_api">
		/// The address to the external API, if available.
		/// If no meaningful address can be provided, pass an empty pointer.
		/// </param>
		/// <param name="_hresult">The HRESULT code.</param>
		inline ExternalAPIFailureWithHRESULTException(const char* _name_api, size_t _size_name_api, const void* _address_api, HRESULT _hresult) noexcept
			: ExternalAPIFailureException(_name_api, _size_name_api, _address_api),
			hresult(_hresult) {}
		inline virtual ~ExternalAPIFailureWithHRESULTException() = default;
		/// <summary>Gets the HRESULT code.</summary>
		inline virtual HRESULT GetHRESULTCode() const noexcept override { return this->hresult; }
	protected:
		const HRESULT hresult;
	};
#endif
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	//}
#pragma endregion Exception classes that provide a default implementation but may not be transferred across executable modules without using an exception interface class pointer.

	void YBWLIB2_CALLTYPE ExceptionWindows_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE ExceptionWindows_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE ExceptionWindows_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE ExceptionWindows_RealUnInitModuleLocal() noexcept;

	void YBWLIB2_CALLTYPE ExceptionWindowsUserInterface_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE ExceptionWindowsUserInterface_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE ExceptionWindowsUserInterface_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE ExceptionWindowsUserInterface_RealUnInitModuleLocal() noexcept;
}

#endif

#ifdef YBWLIB2_EXCEPTION_MACROS_ENABLED

#ifndef YBWLIB2_EXCEPTION_MACROS_DEFINED_WINDOWS

#pragma region Default exception implementation objects creating macros
//{ Default exception implementation objects creating macros

#define YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_LAST_ERROR_EXCEPTION(apiname) (new ::YBWLib2::ExternalAPIFailureWithLastErrorException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(apiname)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(apiname))) / sizeof(char)) - 1, &(apiname), GetLastError()))

#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
#define YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_WSA_LAST_ERROR_EXCEPTION(apiname) (new ::YBWLib2::ExternalAPIFailureWithWSALastErrorException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(apiname)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(apiname))) / sizeof(char)) - 1, &(apiname), WSAGetLastError()))
#endif

#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
#define YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_NTSTATUS_EXCEPTION(apiname, ntstatus) (new ::YBWLib2::ExternalAPIFailureWithLastErrorException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(apiname)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(apiname))) / sizeof(char)) - 1, &(apiname), (ntstatus)))
#endif

#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
#define YBWLIB2_EXCEPTION_CREATE_EXTERNAL_API_FAILURE_WITH_HRESULT_EXCEPTION(apiname, hresult) (new ::YBWLib2::ExternalAPIFailureWithLastErrorException(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(apiname)), (sizeof(YBWLIB2_TO_UTF8(YBWLIB2_STRINGIZE(apiname))) / sizeof(char)) - 1, &(apiname), (hresult)))
#endif

//}
#pragma endregion These macros are used to create exception objects with the above default implementation.

#define YBWLIB2_EXCEPTION_MACROS_DEFINED_WINDOWS
#endif

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_7FE57E16_A6C7_4720_BBEF_D96F80AAAD3E
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_7FE57E16_A6C7_4720_BBEF_D96F80AAAD3E
#endif
