#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_A0D466D9_27E9_4A77_A650_5F73D60D681B
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_40F0D75B_0EC7_43AA_83C8_7060F605D819
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_FCB9CBBB_1B6A_466D_B0A3_1F8D486DC614
#define _INCLUDE_GUARD_FCB9CBBB_1B6A_466D_B0A3_1F8D486DC614

#include <cstdarg>
#include <cstdlib>
#include <type_traits>
#include <new>
#include <memory>
#include <exception>
#include <minwindef.h>
#include "../YBWLib2Api.h"
#include "../Common/CommonLowLevel.h"
#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "../DynamicType/DynamicTypeHighLevel.h"
#include "../JSON/JSON.h"
#include "UserInterface.h"

namespace YBWLib2 {
	/// <summary>Gets a Windows message string.</summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="str_out">
	/// A pointer to a buffer that receives the message string.
	/// Must be at least <c>size_max_str_out</c> <c>char</c>s large.
	/// The string will be null-terminated.
	/// </param>
	/// <param name="size_max_str_out">The size, in <c>char</c>s, including the terminating null character, of the buffer pointed to by <c>str_out</c>.</param>
	/// <param name="is_system_message_table_used">
	/// Whether the system message table should be searched.
	/// Either this parameter or <paramref name="is_module_message_table_searched" /> must have a value of <c>true</c>.
	/// If both are <c>true</c>, the module message table takes precedence.
	/// </param>
	/// <param name="is_module_message_table_searched">
	/// Whether the message table in the module with the specified module handle should be searched.
	/// Either this parameter or <paramref name="is_system_message_table_used" /> must have a value of <c>true</c>.
	/// If both are <c>true</c>, the module message table takes precedence.
	/// </param>
	/// <param name="hmod">
	/// The module handle of the module that contains message definitions to be searched, if <paramref name="is_module_message_table_searched" /> is set to <c>true</c>.
	/// Otherwise, this parameter is ignored.
	/// </param>
	/// <param name="messageid">The message identifier.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE GetWindowsMessageStringUTF8(
		const rawallocator_t* rawallocator,
		char* str_out,
		size_t size_max_str_out,
		bool is_system_message_table_searched,
		bool is_module_message_table_searched,
		HMODULE hmod,
		DWORD messageid
	) noexcept;

	/// <summary>A default implementation of a string template parameter that represents a last-error code.</summary>
	class LastErrorStringTemplateParameter : public virtual StringTemplateParameter {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(LastErrorStringTemplateParameter, , "3cd963ef-f37d-4c13-9283-b8999432f99c");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(LastErrorStringTemplateParameter);
		/// <summary>Constructs an <c>LastErrorStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_size_name_parameter">The size (in <c>char</c>s) of the name, in UTF-8, of this parameter.</param>
		/// <param name="_lasterr">The last-error code.</param>
		inline LastErrorStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char* _name_parameter,
			size_t _size_name_parameter,
			DWORD _lasterr
		) noexcept(false) : StringTemplateParameter(_rawallocator, _name_parameter, _size_name_parameter), lasterr(_lasterr) {}
		/// <summary>Constructs an <c>LastErrorStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_lasterr">The last-error code.</param>
		template<size_t count_char_name_parameter>
		inline LastErrorStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char(&_name_parameter)[count_char_name_parameter],
			DWORD _lasterr
		) noexcept(false) : LastErrorStringTemplateParameter(_rawallocator, _name_parameter, count_char_name_parameter - 1, _lasterr) {}
		inline LastErrorStringTemplateParameter(const LastErrorStringTemplateParameter& x) noexcept(false)
			: StringTemplateParameter(static_cast<const StringTemplateParameter&>(x)), lasterr(x.lasterr) {}
		inline LastErrorStringTemplateParameter(LastErrorStringTemplateParameter&& x) noexcept(false)
			: StringTemplateParameter(static_cast<StringTemplateParameter&&>(::std::move(x))), lasterr(::std::move(x.lasterr)) {}
		inline virtual ~LastErrorStringTemplateParameter() {
			this->lasterr = 0;
		}
		inline LastErrorStringTemplateParameter& operator=(const LastErrorStringTemplateParameter& x) noexcept(false) {
			static_cast<StringTemplateParameter&>(*this) = static_cast<const StringTemplateParameter&>(x);
			this->lasterr = x.lasterr;
			return *this;
		}
		inline LastErrorStringTemplateParameter& operator=(LastErrorStringTemplateParameter&& x) noexcept(false) {
			static_cast<StringTemplateParameter&>(*this) = static_cast<StringTemplateParameter&&>(::std::move(x));
			this->lasterr = ::std::move(x.lasterr);
			return *this;
		}
		/// <summary>Gets whether this parameter may be used as a part of the generated string.</summary>
		inline virtual bool IsAvailableAsGeneratedStringPart() const noexcept override { return true; }
		/// <summary>Gets the part of the generated string that this parameter represents.</summary>
		/// <param name="str_options">
		/// Pointer to an option string, in UTF-8, provided by the string template.
		/// Option strings are not null-terminated.
		/// If no option string is provided, pass an empty pointer or a pointer to an empty string.
		/// No options are supported for this type of string template parameter currently.
		/// The option string for this type is reserved. Always pass an empty pointer or a pointer to an empty string.
		/// </param>
		/// <param name="size_str_options">
		/// The size (in <c>char</c>s) of the option string, in UTF-8.
		/// Option strings are not null-terminated.
		/// If no option string is provided, pass <c>0</c>.
		/// No options are supported for this type of string template parameter currently.
		/// The option string for this type is reserved. Always pass an empty pointer or a pointer to an empty string.
		/// </param>
		/// <param name="str_out_ret">
		/// Pointer to a pointer variable that receives a pointer to the part of the generated string, in UTF-8.
		/// After successfully returning from this member function, <c>*str_out_ret</c> will be set to the part of the generated string.
		/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*str_out_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
		/// If <paramref name="_rawallocator" /> is specified and not empty, the buffer for the part of the generated string will be allocated using <paramref name="_rawallocator" />.
		/// Otherwise, the buffer for the part of the generated string will be allocated using the raw allocator returned by <c>this->GetRawAllocator()</c>.
		/// </param>
		/// <param name="size_str_out_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the part of the generated string, in UTF-8, including the terminating null character, if any.
		/// After successfully returning from this member function, <c>*size_str_out_ret</c> will be set to the size (in <c>char</c>s) of the part of the generated string.
		/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
		/// </param>
		/// <param name="should_null_terminate">Whether a terminating null character should be added to the end of the part of the generated string.</param>
		/// <param name="_rawallocator">
		/// An optional pointer to a <c>rawallocator_t</c> object for allocating memory used by this function, including the memory for <c>*str_out_ret</c>.
		/// If not specified or empty, <c>this->GetRawAllocator()</c> will be used instead.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory, instead of memory allocated using the raw allocator <paramref name="_rawallocator" /> or the one returned by <c>this->GetRawAllocator()</c>.
		/// </returns>
		[[nodiscard]] virtual IException* GenerateString(
			const char* str_options,
			size_t size_str_options,
			char** str_out_ret,
			size_t* size_str_out_ret,
			bool should_null_terminate,
			const rawallocator_t* _rawallocator = nullptr
		) const noexcept override;
		/// <summary>Gets the last-error code.</summary>
		inline DWORD GetLastErrorCode() const noexcept { return this->lasterr; }
	protected:
		DWORD lasterr;
	};
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_WSA
	/// <summary>A default implementation of a string template parameter that represents a WSA last-error code.</summary>
	class WSALastErrorStringTemplateParameter : public virtual StringTemplateParameter {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(WSALastErrorStringTemplateParameter, , "ce383ddf-7982-4d3d-bf4e-239a876d45ba");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(WSALastErrorStringTemplateParameter);
		/// <summary>Constructs an <c>WSALastErrorStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_size_name_parameter">The size (in <c>char</c>s) of the name, in UTF-8, of this parameter.</param>
		/// <param name="_wsalasterr">The WSA last-error code.</param>
		inline WSALastErrorStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char* _name_parameter,
			size_t _size_name_parameter,
			int _wsalasterr
		) noexcept(false) : StringTemplateParameter(_rawallocator, _name_parameter, _size_name_parameter), wsalasterr(_wsalasterr) {}
		/// <summary>Constructs an <c>WSALastErrorStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_wsalasterr">The WSA last-error code.</param>
		template<size_t count_char_name_parameter>
		inline WSALastErrorStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char(&_name_parameter)[count_char_name_parameter],
			DWORD _wsalasterr
		) noexcept(false) : WSALastErrorStringTemplateParameter(_rawallocator, _name_parameter, count_char_name_parameter - 1, _wsalasterr) {}
		inline WSALastErrorStringTemplateParameter(const WSALastErrorStringTemplateParameter& x) noexcept(false)
			: StringTemplateParameter(static_cast<const StringTemplateParameter&>(x)), wsalasterr(x.wsalasterr) {}
		inline WSALastErrorStringTemplateParameter(WSALastErrorStringTemplateParameter&& x) noexcept(false)
			: StringTemplateParameter(static_cast<StringTemplateParameter&&>(::std::move(x))), wsalasterr(::std::move(x.wsalasterr)) {}
		inline virtual ~WSALastErrorStringTemplateParameter() {
			this->wsalasterr = 0;
		}
		inline WSALastErrorStringTemplateParameter& operator=(const WSALastErrorStringTemplateParameter& x) noexcept(false) {
			static_cast<StringTemplateParameter&>(*this) = static_cast<const StringTemplateParameter&>(x);
			this->wsalasterr = x.wsalasterr;
			return *this;
		}
		inline WSALastErrorStringTemplateParameter& operator=(WSALastErrorStringTemplateParameter&& x) noexcept(false) {
			static_cast<StringTemplateParameter&>(*this) = static_cast<StringTemplateParameter&&>(::std::move(x));
			this->wsalasterr = ::std::move(x.wsalasterr);
			return *this;
		}
		/// <summary>Gets whether this parameter may be used as a part of the generated string.</summary>
		inline virtual bool IsAvailableAsGeneratedStringPart() const noexcept override { return true; }
		/// <summary>Gets the part of the generated string that this parameter represents.</summary>
		/// <param name="str_options">
		/// Pointer to an option string, in UTF-8, provided by the string template.
		/// Option strings are not null-terminated.
		/// If no option string is provided, pass an empty pointer or a pointer to an empty string.
		/// No options are supported for this type of string template parameter currently.
		/// The option string for this type is reserved. Always pass an empty pointer or a pointer to an empty string.
		/// </param>
		/// <param name="size_str_options">
		/// The size (in <c>char</c>s) of the option string, in UTF-8.
		/// Option strings are not null-terminated.
		/// If no option string is provided, pass <c>0</c>.
		/// No options are supported for this type of string template parameter currently.
		/// The option string for this type is reserved. Always pass an empty pointer or a pointer to an empty string.
		/// </param>
		/// <param name="str_out_ret">
		/// Pointer to a pointer variable that receives a pointer to the part of the generated string, in UTF-8.
		/// After successfully returning from this member function, <c>*str_out_ret</c> will be set to the part of the generated string.
		/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*str_out_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
		/// If <paramref name="_rawallocator" /> is specified and not empty, the buffer for the part of the generated string will be allocated using <paramref name="_rawallocator" />.
		/// Otherwise, the buffer for the part of the generated string will be allocated using the raw allocator returned by <c>this->GetRawAllocator()</c>.
		/// </param>
		/// <param name="size_str_out_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the part of the generated string, in UTF-8, including the terminating null character, if any.
		/// After successfully returning from this member function, <c>*size_str_out_ret</c> will be set to the size (in <c>char</c>s) of the part of the generated string.
		/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
		/// </param>
		/// <param name="should_null_terminate">Whether a terminating null character should be added to the end of the part of the generated string.</param>
		/// <param name="_rawallocator">
		/// An optional pointer to a <c>rawallocator_t</c> object for allocating memory used by this function, including the memory for <c>*str_out_ret</c>.
		/// If not specified or empty, <c>this->GetRawAllocator()</c> will be used instead.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory, instead of memory allocated using the raw allocator <paramref name="_rawallocator" /> or the one returned by <c>this->GetRawAllocator()</c>.
		/// </returns>
		[[nodiscard]] virtual IException* GenerateString(
			const char* str_options,
			size_t size_str_options,
			char** str_out_ret,
			size_t* size_str_out_ret,
			bool should_null_terminate,
			const rawallocator_t* _rawallocator = nullptr
		) const noexcept override;
		/// <summary>Gets the WSA last-error code.</summary>
		inline int GetWSALastErrorCode() const noexcept { return this->wsalasterr; }
	protected:
		int wsalasterr;
	};
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_NTSTATUS
	/// <summary>A default implementation of a string template parameter that represents an NTSTATUS code.</summary>
	class NTSTATUSStringTemplateParameter : public virtual StringTemplateParameter {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(NTSTATUSStringTemplateParameter, , "db4f7a2f-ba4a-4ca5-8e09-b8fd4520faf4");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(NTSTATUSStringTemplateParameter);
		/// <summary>Constructs an <c>NTSTATUSStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_size_name_parameter">The size (in <c>char</c>s) of the name, in UTF-8, of this parameter.</param>
		/// <param name="_ntstatus">The NTSTATUS code.</param>
		inline NTSTATUSStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char* _name_parameter,
			size_t _size_name_parameter,
			NTSTATUS _ntstatus
		) noexcept(false) : StringTemplateParameter(_rawallocator, _name_parameter, _size_name_parameter), ntstatus(_ntstatus) {}
		/// <summary>Constructs an <c>NTSTATUSStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_ntstatus">The NTSTATUS code.</param>
		template<size_t count_char_name_parameter>
		inline NTSTATUSStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char(&_name_parameter)[count_char_name_parameter],
			NTSTATUS _ntstatus
		) noexcept(false) : NTSTATUSStringTemplateParameter(_rawallocator, _name_parameter, count_char_name_parameter - 1, _ntstatus) {}
		inline NTSTATUSStringTemplateParameter(const NTSTATUSStringTemplateParameter& x) noexcept(false)
			: StringTemplateParameter(static_cast<const StringTemplateParameter&>(x)), ntstatus(x.ntstatus) {}
		inline NTSTATUSStringTemplateParameter(NTSTATUSStringTemplateParameter&& x) noexcept(false)
			: StringTemplateParameter(static_cast<StringTemplateParameter&&>(::std::move(x))), ntstatus(::std::move(x.ntstatus)) {}
		inline virtual ~NTSTATUSStringTemplateParameter() {
			this->ntstatus = 0;
		}
		inline NTSTATUSStringTemplateParameter& operator=(const NTSTATUSStringTemplateParameter& x) noexcept(false) {
			static_cast<StringTemplateParameter&>(*this) = static_cast<const StringTemplateParameter&>(x);
			this->ntstatus = x.ntstatus;
			return *this;
		}
		inline NTSTATUSStringTemplateParameter& operator=(NTSTATUSStringTemplateParameter&& x) noexcept(false) {
			static_cast<StringTemplateParameter&>(*this) = static_cast<StringTemplateParameter&&>(::std::move(x));
			this->ntstatus = ::std::move(x.ntstatus);
			return *this;
		}
		/// <summary>Gets whether this parameter may be used as a part of the generated string.</summary>
		inline virtual bool IsAvailableAsGeneratedStringPart() const noexcept override { return true; }
		/// <summary>Gets the part of the generated string that this parameter represents.</summary>
		/// <param name="str_options">
		/// Pointer to an option string, in UTF-8, provided by the string template.
		/// Option strings are not null-terminated.
		/// If no option string is provided, pass an empty pointer or a pointer to an empty string.
		/// No options are supported for this type of string template parameter currently.
		/// The option string for this type is reserved. Always pass an empty pointer or a pointer to an empty string.
		/// </param>
		/// <param name="size_str_options">
		/// The size (in <c>char</c>s) of the option string, in UTF-8.
		/// Option strings are not null-terminated.
		/// If no option string is provided, pass <c>0</c>.
		/// No options are supported for this type of string template parameter currently.
		/// The option string for this type is reserved. Always pass an empty pointer or a pointer to an empty string.
		/// </param>
		/// <param name="str_out_ret">
		/// Pointer to a pointer variable that receives a pointer to the part of the generated string, in UTF-8.
		/// After successfully returning from this member function, <c>*str_out_ret</c> will be set to the part of the generated string.
		/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*str_out_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
		/// If <paramref name="_rawallocator" /> is specified and not empty, the buffer for the part of the generated string will be allocated using <paramref name="_rawallocator" />.
		/// Otherwise, the buffer for the part of the generated string will be allocated using the raw allocator returned by <c>this->GetRawAllocator()</c>.
		/// </param>
		/// <param name="size_str_out_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the part of the generated string, in UTF-8, including the terminating null character, if any.
		/// After successfully returning from this member function, <c>*size_str_out_ret</c> will be set to the size (in <c>char</c>s) of the part of the generated string.
		/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
		/// </param>
		/// <param name="should_null_terminate">Whether a terminating null character should be added to the end of the part of the generated string.</param>
		/// <param name="_rawallocator">
		/// An optional pointer to a <c>rawallocator_t</c> object for allocating memory used by this function, including the memory for <c>*str_out_ret</c>.
		/// If not specified or empty, <c>this->GetRawAllocator()</c> will be used instead.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory, instead of memory allocated using the raw allocator <paramref name="_rawallocator" /> or the one returned by <c>this->GetRawAllocator()</c>.
		/// </returns>
		[[nodiscard]] virtual IException* GenerateString(
			const char* str_options,
			size_t size_str_options,
			char** str_out_ret,
			size_t* size_str_out_ret,
			bool should_null_terminate,
			const rawallocator_t* _rawallocator = nullptr
		) const noexcept override;
		/// <summary>Gets the NTSTATUS code.</summary>
		inline NTSTATUS GetNTSTATUSCode() const noexcept { return this->ntstatus; }
	protected:
		NTSTATUS ntstatus;
	};
#endif
#ifndef YBWLIB2_EXCEPTION_WINDOWS_NO_HRESULT
	/// <summary>A default implementation of a string template parameter that represents an HRESULT code.</summary>
	class HRESULTStringTemplateParameter : public virtual StringTemplateParameter {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(HRESULTStringTemplateParameter, , "45d46d03-73ae-4a62-9a25-8a8b23bdd11e");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(HRESULTStringTemplateParameter);
		/// <summary>Constructs an <c>HRESULTStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_size_name_parameter">The size (in <c>char</c>s) of the name, in UTF-8, of this parameter.</param>
		/// <param name="_hresult">The HRESULT code.</param>
		inline HRESULTStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char* _name_parameter,
			size_t _size_name_parameter,
			HRESULT _hresult
		) noexcept(false) : StringTemplateParameter(_rawallocator, _name_parameter, _size_name_parameter), hresult(_hresult) {}
		/// <summary>Constructs an <c>HRESULTStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_hresult">The HRESULT code.</param>
		template<size_t count_char_name_parameter>
		inline HRESULTStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char(&_name_parameter)[count_char_name_parameter],
			HRESULT _hresult
		) noexcept(false) : HRESULTStringTemplateParameter(_rawallocator, _name_parameter, count_char_name_parameter - 1, _hresult) {}
		inline HRESULTStringTemplateParameter(const HRESULTStringTemplateParameter& x) noexcept(false)
			: StringTemplateParameter(static_cast<const StringTemplateParameter&>(x)), hresult(x.hresult) {}
		inline HRESULTStringTemplateParameter(HRESULTStringTemplateParameter&& x) noexcept(false)
			: StringTemplateParameter(static_cast<StringTemplateParameter&&>(::std::move(x))), hresult(::std::move(x.hresult)) {}
		inline virtual ~HRESULTStringTemplateParameter() {
			this->hresult = 0;
		}
		inline HRESULTStringTemplateParameter& operator=(const HRESULTStringTemplateParameter& x) noexcept(false) {
			static_cast<StringTemplateParameter&>(*this) = static_cast<const StringTemplateParameter&>(x);
			this->hresult = x.hresult;
			return *this;
		}
		inline HRESULTStringTemplateParameter& operator=(HRESULTStringTemplateParameter&& x) noexcept(false) {
			static_cast<StringTemplateParameter&>(*this) = static_cast<StringTemplateParameter&&>(::std::move(x));
			this->hresult = ::std::move(x.hresult);
			return *this;
		}
		/// <summary>Gets whether this parameter may be used as a part of the generated string.</summary>
		inline virtual bool IsAvailableAsGeneratedStringPart() const noexcept override { return true; }
		/// <summary>Gets the part of the generated string that this parameter represents.</summary>
		/// <param name="str_options">
		/// Pointer to an option string, in UTF-8, provided by the string template.
		/// Option strings are not null-terminated.
		/// If no option string is provided, pass an empty pointer or a pointer to an empty string.
		/// No options are supported for this type of string template parameter currently.
		/// The option string for this type is reserved. Always pass an empty pointer or a pointer to an empty string.
		/// </param>
		/// <param name="size_str_options">
		/// The size (in <c>char</c>s) of the option string, in UTF-8.
		/// Option strings are not null-terminated.
		/// If no option string is provided, pass <c>0</c>.
		/// No options are supported for this type of string template parameter currently.
		/// The option string for this type is reserved. Always pass an empty pointer or a pointer to an empty string.
		/// </param>
		/// <param name="str_out_ret">
		/// Pointer to a pointer variable that receives a pointer to the part of the generated string, in UTF-8.
		/// After successfully returning from this member function, <c>*str_out_ret</c> will be set to the part of the generated string.
		/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*str_out_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
		/// If <paramref name="_rawallocator" /> is specified and not empty, the buffer for the part of the generated string will be allocated using <paramref name="_rawallocator" />.
		/// Otherwise, the buffer for the part of the generated string will be allocated using the raw allocator returned by <c>this->GetRawAllocator()</c>.
		/// </param>
		/// <param name="size_str_out_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the part of the generated string, in UTF-8, including the terminating null character, if any.
		/// After successfully returning from this member function, <c>*size_str_out_ret</c> will be set to the size (in <c>char</c>s) of the part of the generated string.
		/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
		/// </param>
		/// <param name="should_null_terminate">Whether a terminating null character should be added to the end of the part of the generated string.</param>
		/// <param name="_rawallocator">
		/// An optional pointer to a <c>rawallocator_t</c> object for allocating memory used by this function, including the memory for <c>*str_out_ret</c>.
		/// If not specified or empty, <c>this->GetRawAllocator()</c> will be used instead.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory, instead of memory allocated using the raw allocator <paramref name="_rawallocator" /> or the one returned by <c>this->GetRawAllocator()</c>.
		/// </returns>
		[[nodiscard]] virtual IException* GenerateString(
			const char* str_options,
			size_t size_str_options,
			char** str_out_ret,
			size_t* size_str_out_ret,
			bool should_null_terminate,
			const rawallocator_t* _rawallocator = nullptr
		) const noexcept override;
		/// <summary>Gets the HRESULT code.</summary>
		inline HRESULT GetHRESULTCode() const noexcept { return this->hresult; }
	protected:
		HRESULT hresult;
	};
#endif

	void YBWLIB2_CALLTYPE UserInterfaceWindows_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE UserInterfaceWindows_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE UserInterfaceWindows_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE UserInterfaceWindows_RealUnInitModuleLocal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_40F0D75B_0EC7_43AA_83C8_7060F605D819
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_40F0D75B_0EC7_43AA_83C8_7060F605D819
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_A0D466D9_27E9_4A77_A650_5F73D60D681B
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_A0D466D9_27E9_4A77_A650_5F73D60D681B
#endif
