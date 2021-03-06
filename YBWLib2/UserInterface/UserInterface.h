#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_9F76487C_A292_4CF5_B1D1_20D77EF404DF
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_B0C4C67D_ECAF_416E_87D6_C710651BDB04
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_F7AE97C5_EBD9_44EF_AD66_A7C5FF8234D5
#define _INCLUDE_GUARD_F7AE97C5_EBD9_44EF_AD66_A7C5FF8234D5

#include <cstdint>
#include <cstdarg>
#include <cstdlib>
#include <type_traits>
#include <new>
#include <memory>
#include <initializer_list>
#include <exception>
#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include "../YBWLib2Api.h"
#include "../Common/CommonLowLevel.h"
#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "../Common/Common.h"
#include "../DynamicType/DynamicTypeHighLevel.h"
#include "../JSON/JSON.h"

namespace YBWLib2 {
	class FixedStringTemplateConstructorJSONSAXHandler;
	class SubstitutionStringTemplateConstructorJSONSAXHandler;

	/// <summary>
	/// Format data into a UTF-8 string.
	/// Works like the C library function <c>vsnprintf</c>, except that the output string and format string are in UTF-8.
	/// Using the character or string format specifier (%c, %C, %s and %S) in the format string causes undefined behaviour and should be avoided.
	/// </summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="str_out">
	/// A pointer to a buffer that receives the output string.
	/// Must be at least <c>size_max_str_out</c> <c>char</c>s large.
	/// The string will be null-terminated.
	/// </param>
	/// <param name="size_max_str_out">The size, in <c>char</c>s, including the terminating null character, of the buffer pointed to by <c>str_out</c>.</param>
	/// <param name="str_format">Pointer to the null-terminated format string.</param>
	/// <param name="size_str_format">The size, in <c>char</c>s, including the terminating null character, of the format string pointed to by <c>str_format</c>.</param>
	/// <param name="arglist">The argument list.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE VsnPrintfUtf8(
		const rawallocator_t* rawallocator,
		char* str_out,
		size_t size_max_str_out,
		const char* str_format,
		size_t size_str_format,
		va_list arglist
	) noexcept;

	/// <summary>
	/// Format data into a UTF-8 string.
	/// Works like the C library function <c>snprintf</c>, except that the output string and format string are in UTF-8.
	/// Using the character or string format specifier (%c, %C, %s and %S) in the format string causes undefined behaviour and should be avoided.
	/// </summary>
	/// <param name="rawallocator">Pointer to an <c>rawallocator_t</c> object for allocating memory used by the function.</param>
	/// <param name="str_out">
	/// A pointer to a buffer that receives the output string.
	/// Must be at least <c>size_max_str_out</c> <c>char</c>s large.
	/// The string will be null-terminated.
	/// </param>
	/// <param name="size_max_str_out">The size, in <c>char</c>s, including the terminating null character, of the buffer pointed to by <c>str_out</c>.</param>
	/// <param name="str_format">Pointer to the null-terminated format string.</param>
	/// <param name="size_str_format">The size, in <c>char</c>s, including the terminating null character, of the format string pointed to by <c>str_format</c>.</param>
	/// <returns>
	/// Returns a pointer to the exception object if the function fails.
	/// Returns an empty pointer otherwise.
	/// The caller is responsible for destructing and freeing the object pointed to.
	/// </returns>
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE_VARARG SnPrintfUtf8(
		const rawallocator_t* rawallocator,
		char* str_out,
		size_t size_max_str_out,
		const char* str_format,
		size_t size_str_format,
		...
	) noexcept;

	/// <summary>A runtime parameter for <c>IStringTemplate</c> that may decide the string generation behaviour of the string template.</summary>
	class IStringTemplateParameter abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IStringTemplateParameter, YBWLIB2_API, "8a03c540-dc45-4456-b726-f4df2cb28d9d");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IStringTemplateParameter);
		inline IStringTemplateParameter() noexcept = default;
		inline IStringTemplateParameter(const IStringTemplateParameter&) noexcept = default;
		inline IStringTemplateParameter(IStringTemplateParameter&&) noexcept = default;
		inline virtual ~IStringTemplateParameter() = default;
		inline IStringTemplateParameter& operator=(const IStringTemplateParameter&) noexcept = default;
		inline IStringTemplateParameter& operator=(IStringTemplateParameter&&) noexcept = default;
		/// <summary>
		/// Gets a pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object will survive for at least the lifetime of this object.
		/// </summary>
		virtual const rawallocator_t* GetRawAllocator() const noexcept = 0;
		/// <summary>
		/// Gets the name of this parameter.
		/// Parameter names are not null-terminated.
		/// </summary>
		/// <returns>Returns the name, in UTF-8, of this parameter.</returns>
		virtual const char* GetParameterName() const noexcept = 0;
		/// <summary>
		/// Gets the size (in <c>char</c>s) of the name of this parameter.
		/// Parameter names are not null-terminated.
		/// </summary>
		/// <returns>Returns the size (in <c>char</c>s) of the name, in UTF-8, of this parameter.</returns>
		virtual size_t GetParameterNameSize() const noexcept = 0;
		/// <summary>Gets whether this parameter may be used as a part of the generated string.</summary>
		virtual bool IsAvailableAsGeneratedStringPart() const noexcept = 0;
		/// <summary>Gets the part of the generated string that this parameter represents.</summary>
		/// <param name="str_options">
		/// Pointer to an option string, in UTF-8, provided by the string template.
		/// Option strings are not null-terminated.
		/// If no option string is provided, pass an empty pointer or a pointer to an empty string.
		/// </param>
		/// <param name="size_str_options">
		/// The size (in <c>char</c>s) of the option string, in UTF-8.
		/// Option strings are not null-terminated.
		/// If no option string is provided, pass <c>0</c>.
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
		) const noexcept = 0;
	};

	/// <summary>A runtime parameter list for <c>IStringTemplate</c> that may decide the string generation behaviour of the string template.</summary>
	class IStringTemplateParameterList abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IStringTemplateParameterList, YBWLIB2_API, "daf121e5-d295-4a60-9eba-632ee2802d7d");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IStringTemplateParameterList);
		inline IStringTemplateParameterList() noexcept = default;
		/// <summary>
		/// Copy-constructs the parameter list.
		/// No deep copies will be performed for the parameters (which implies that the parameter objects will retain their raw allocators).
		/// </summary>
		inline IStringTemplateParameterList(const IStringTemplateParameterList&) noexcept = default;
		/// <summary>
		/// Move-constructs the parameter list.
		/// No deep moves will be performed for the parameters (which implies that the parameter objects will retain their raw allocators).
		/// </summary>
		inline IStringTemplateParameterList(IStringTemplateParameterList&&) noexcept = default;
		inline virtual ~IStringTemplateParameterList() = default;
		/// <summary>
		/// Copy-assigns the parameter list.
		/// No deep copies will be performed for the parameters (which implies that the parameter objects will retain their raw allocators).
		/// </summary>
		inline IStringTemplateParameterList& operator=(const IStringTemplateParameterList&) noexcept = default;
		/// <summary>
		/// Move-assigns the parameter list.
		/// No deep moves will be performed for the parameters (which implies that the parameter objects will retain their raw allocators).
		/// </summary>
		inline IStringTemplateParameterList& operator=(IStringTemplateParameterList&&) noexcept = default;
		/// <summary>
		/// Gets a pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object will survive for at least the lifetime of this object.
		/// </summary>
		virtual const rawallocator_t* GetRawAllocator() const noexcept = 0;
		/// <summary>Gets the parameter with the specified name in this parameter list.</summary>
		/// <param name="_name_parameter">
		/// The name, in UTF-8, of the parameter.
		/// Parameter names are not null-terminated.
		/// </param>
		/// <param name="_size_name_parameter">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the parameter.
		/// Parameter names are not null-terminated.
		/// </param>
		/// <param name="parameter_ret">
		/// Pointer to a pointer variable that receives a pointer to the parameter with the specified name.
		/// After successfully returning from this member function, <c>*parameter_ret</c> will be set to the parameter with the specified name.
		/// Any value originally in <c>*parameter_ret</c> will be discarded (without destructing or freeing the object pointed to by it, if any).
		/// The caller should not destruct or free the object pointed to by the new <c>*parameter_ret</c> after a successful call.
		/// If there wasn't a parameter with the specified name in this parameter list, <c>*parameter_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="_rawallocator">
		/// An optional pointer to a <c>rawallocator_t</c> object for allocating memory used by this function, NOT INCLUDING the memory for <c>*parameter_ret</c>.
		/// If not specified or empty, <c>this->GetRawAllocator()</c> will be used instead.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory, instead of memory allocated using the raw allocator <paramref name="_rawallocator" /> or the one returned by <c>this->GetRawAllocator()</c>.
		/// </returns>
		[[nodiscard]] virtual IException* GetParameterByName(
			const char* _name_parameter,
			size_t _size_name_parameter,
			const IStringTemplateParameter** parameter_ret,
			const rawallocator_t* _rawallocator = nullptr
		) const noexcept = 0;
		/// <summary>Adds a parameter into this parameter list.</summary>
		/// <param name="_parameter">
		/// Pointer to the parameter to be added.
		/// The parameter will not be owned by this object, instead, only a pointer is stored.
		/// The parameter object must survive for at least the lifetime of this object.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory, instead of memory allocated using the raw allocator returned by <c>this->GetRawAllocator()</c>.
		/// </returns>
		[[nodiscard]] virtual IException* AddParameter(const IStringTemplateParameter* _parameter) noexcept = 0;
		/// <summary>
		/// Removes the parameter with the specified name from this parameter list.
		/// This function does not destruct or free the parameter object.
		/// It only removes it from this parameter list.
		/// </summary>
		/// <param name="_name_parameter">
		/// The name, in UTF-8, of the parameter.
		/// Parameter names are not null-terminated.
		/// </param>
		/// <param name="_size_name_parameter">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the parameter.
		/// Parameter names are not null-terminated.
		/// </param>
		/// <param name="_rawallocator">
		/// An optional pointer to a <c>rawallocator_t</c> object for allocating memory used by this function.
		/// If not specified or empty, <c>this->GetRawAllocator()</c> will be used instead.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory, instead of memory allocated using the raw allocator <paramref name="_rawallocator" /> or the one returned by <c>this->GetRawAllocator()</c>.
		/// </returns>
		[[nodiscard]] virtual IException* RemoveParameterByName(
			const char* _name_parameter,
			size_t _size_name_parameter,
			const rawallocator_t* _rawallocator = nullptr
		) noexcept = 0;
	};

	/// <summary>A string template that may be used to generate strings at runtime.</summary>
	class IStringTemplate abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IStringTemplate, YBWLIB2_API, "9867605c-bdca-494f-b81d-c72508b5b1b8");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IStringTemplate);
		inline IStringTemplate() noexcept = default;
		inline IStringTemplate(const IStringTemplate&) noexcept = default;
		inline IStringTemplate(IStringTemplate&&) noexcept = default;
		inline virtual ~IStringTemplate() = default;
		inline IStringTemplate& operator=(const IStringTemplate&) noexcept = default;
		inline IStringTemplate& operator=(IStringTemplate&&) noexcept = default;
		/// <summary>
		/// Gets a pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object will survive for at least the lifetime of this object.
		/// </summary>
		virtual const rawallocator_t* GetRawAllocator() const noexcept = 0;
		/// <summary>Generates a string using this string template and the specified parameter list.</summary>
		/// <param name="parameter_list">Pointer to a parameter list that may decide the string generation behaviour.</param>
		/// <param name="str_out_ret">
		/// Pointer to a pointer variable that receives a pointer to the generated string, in UTF-8.
		/// After successfully returning from this member function, <c>*str_out_ret</c> will be set to the generated string.
		/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*str_out_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
		/// If <paramref name="_rawallocator" /> is specified and not empty, the buffer for the part of the generated string will be allocated using <paramref name="_rawallocator" />.
		/// Otherwise, the buffer for the part of the generated string will be allocated using the raw allocator returned by <c>this->GetRawAllocator()</c>.
		/// </param>
		/// <param name="size_str_out_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the generated string, in UTF-8, including the terminating null character, if any.
		/// After successfully returning from this member function, <c>*size_str_out_ret</c> will be set to the size (in <c>char</c>s) of the generated string.
		/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
		/// </param>
		/// <param name="should_null_terminate">Whether a terminating null character should be added to the end of the generated string.</param>
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
			const IStringTemplateParameterList* parameter_list,
			char** str_out_ret,
			size_t* size_str_out_ret,
			bool should_null_terminate,
			const rawallocator_t* _rawallocator = nullptr
		) const noexcept = 0;
		/// <summary>Generates a string using this string template and the specified parameter list.</summary>
		/// <param name="parameter_list">Reference to a parameter list that may decide the string generation behaviour.</param>
		/// <param name="str_out_ret">
		/// Pointer to a pointer variable that receives a pointer to the generated string, in UTF-8.
		/// After successfully returning from this member function, <c>*str_out_ret</c> will be set to the generated string.
		/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*str_out_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
		/// If <paramref name="_rawallocator" /> is specified and not empty, the buffer for the part of the generated string will be allocated using <paramref name="_rawallocator" />.
		/// Otherwise, the buffer for the part of the generated string will be allocated using the raw allocator returned by <c>this->GetRawAllocator()</c>.
		/// </param>
		/// <param name="size_str_out_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the generated string, in UTF-8, including the terminating null character, if any.
		/// After successfully returning from this member function, <c>*size_str_out_ret</c> will be set to the size (in <c>char</c>s) of the generated string.
		/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
		/// </param>
		/// <param name="should_null_terminate">Whether a terminating null character should be added to the end of the generated string.</param>
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
		[[nodiscard]] inline IException* GenerateString(
			const IStringTemplateParameterList& parameter_list,
			char** str_out_ret,
			size_t* size_str_out_ret,
			bool should_null_terminate,
			const rawallocator_t* _rawallocator = nullptr
		) const noexcept {
			return this->GenerateString(&parameter_list, str_out_ret, size_str_out_ret, should_null_terminate, _rawallocator);
		}
	};

	/// <summary>
	/// A default implementation of <c>IStringTemplateParameter</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IStringTemplateParameter</c>.
	/// </summary>
	class StringTemplateParameter : public virtual IStringTemplateParameter {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(StringTemplateParameter, , "50af4469-4808-42f4-a5ff-fc1b3ae6787d");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(StringTemplateParameter);
		/// <summary>Constructs an <c>StringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_size_name_parameter">The size (in <c>char</c>s) of the name, in UTF-8, of this parameter.</param>
		inline StringTemplateParameter(const rawallocator_t* _rawallocator, const char* _name_parameter, size_t _size_name_parameter) noexcept(false) : rawallocator(_rawallocator) {
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringTemplateParameter, StringTemplateParameter));
			if (!_name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringTemplateParameter, StringTemplateParameter));
			this->size_name_parameter = _size_name_parameter;
			this->name_parameter = reinterpret_cast<char*>(this->rawallocator->Allocate(this->size_name_parameter * sizeof(char), alignof(char[])));
			if (!this->name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			if (this->size_name_parameter) memcpy(this->name_parameter, _name_parameter, this->size_name_parameter * sizeof(char));
		}
		inline StringTemplateParameter(const StringTemplateParameter& x) noexcept(false) : rawallocator(x.rawallocator) {
			if (!x.name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->size_name_parameter = x.size_name_parameter;
			this->name_parameter = reinterpret_cast<char*>(this->rawallocator->Allocate(this->size_name_parameter * sizeof(char), alignof(char[])));
			if (!this->name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			if (this->size_name_parameter) memcpy(this->name_parameter, x.name_parameter, this->size_name_parameter * sizeof(char));
		}
		inline StringTemplateParameter(StringTemplateParameter&& x) noexcept(false) : rawallocator(::std::move(x.rawallocator)) {
			if (!x.name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->name_parameter = ::std::move(x.name_parameter);
			this->size_name_parameter = ::std::move(x.size_name_parameter);
			x.rawallocator = nullptr;
			x.name_parameter = nullptr;
			x.size_name_parameter = 0;
		}
		inline virtual ~StringTemplateParameter() {
			if (this->name_parameter) {
				this->rawallocator->Deallocate(this->name_parameter, this->size_name_parameter * sizeof(char));
				this->name_parameter = nullptr;
			}
			this->size_name_parameter = 0;
		}
		inline StringTemplateParameter& operator=(const StringTemplateParameter& x) noexcept(false) {
			if (this->name_parameter) {
				this->rawallocator->Deallocate(this->name_parameter, this->size_name_parameter * sizeof(char));
				this->name_parameter = nullptr;
			}
			this->size_name_parameter = 0;
			static_cast<IStringTemplateParameter&>(*this) = static_cast<const IStringTemplateParameter&>(x);
			this->rawallocator = x.rawallocator;
			if (!x.name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->size_name_parameter = x.size_name_parameter;
			this->name_parameter = reinterpret_cast<char*>(this->rawallocator->Allocate(this->size_name_parameter * sizeof(char), alignof(char[])));
			if (!this->name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			if (this->size_name_parameter) memcpy(this->name_parameter, x.name_parameter, this->size_name_parameter * sizeof(char));
			return *this;
		}
		inline StringTemplateParameter& operator=(StringTemplateParameter&& x) noexcept(false) {
			if (this->name_parameter) {
				this->rawallocator->Deallocate(this->name_parameter, this->size_name_parameter * sizeof(char));
				this->name_parameter = nullptr;
			}
			this->size_name_parameter = 0;
			static_cast<IStringTemplateParameter&>(*this) = static_cast<IStringTemplateParameter&&>(::std::move(x));
			this->rawallocator = ::std::move(x.rawallocator);
			if (!x.name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->name_parameter = ::std::move(x.name_parameter);
			this->size_name_parameter = ::std::move(x.size_name_parameter);
			x.rawallocator = nullptr;
			x.name_parameter = nullptr;
			x.size_name_parameter = 0;
			return *this;
		}
		/// <summary>
		/// Gets a pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object will survive for at least the lifetime of this object.
		/// </summary>
		inline virtual const rawallocator_t* GetRawAllocator() const noexcept override { return this->rawallocator; }
		/// <summary>
		/// Gets the name of this parameter.
		/// Parameter names are not null-terminated.
		/// </summary>
		/// <returns>Returns the name, in UTF-8, of this parameter.</returns>
		inline virtual const char* GetParameterName() const noexcept override { return this->name_parameter; }
		/// <summary>
		/// Gets the size (in <c>char</c>s) of the name of this parameter.
		/// Parameter names are not null-terminated.
		/// </summary>
		/// <returns>Returns the size (in <c>char</c>s) of the name, in UTF-8, of this parameter.</returns>
		inline virtual size_t GetParameterNameSize() const noexcept override { return this->size_name_parameter; }
		/// <summary>Gets whether this parameter may be used as a part of the generated string.</summary>
		virtual bool IsAvailableAsGeneratedStringPart() const noexcept override = 0;
		/// <summary>Gets the part of the generated string that this parameter represents.</summary>
		/// <param name="str_options">
		/// Pointer to an option string, in UTF-8, provided by the string template.
		/// Option strings are not null-terminated.
		/// If no option string is provided, pass an empty pointer or a pointer to an empty string.
		/// </param>
		/// <param name="size_str_options">
		/// The size (in <c>char</c>s) of the option string, in UTF-8.
		/// Option strings are not null-terminated.
		/// If no option string is provided, pass <c>0</c>.
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
		) const noexcept override = 0;
	protected:
		const rawallocator_t* rawallocator = nullptr;
		char* name_parameter = nullptr;
		size_t size_name_parameter = 0;
	};

	/// <summary>A default implementation of a string template parameter that represents a UTF-8 string itself.</summary>
	class StringStringTemplateParameter : public virtual StringTemplateParameter {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(StringStringTemplateParameter, , "e71987e4-bb8e-4839-b772-7659a2a3fd3d");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(StringStringTemplateParameter);
		/// <summary>Constructs an <c>StringStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_size_name_parameter">The size (in <c>char</c>s) of the name, in UTF-8, of this parameter.</param>
		/// <param name="_str_value">The string value, in UTF-8, of this parameter.</param>
		/// <param name="_size_str_value">The size (in <c>char</c>s) of the string value, in UTF-8, of this parameter.</param>
		inline StringStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char* _name_parameter,
			size_t _size_name_parameter,
			const char* _str_value = nullptr,
			size_t _size_str_value = 0
		) noexcept(false) : StringTemplateParameter(_rawallocator, _name_parameter, _size_name_parameter) {
			if (_size_str_value && !_str_value) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, StringStringTemplateParameter));
			this->size_str_value = _size_str_value;
			this->str_value = reinterpret_cast<char*>(this->rawallocator->Allocate(this->size_str_value * sizeof(char), alignof(char[])));
			if (!this->str_value) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			if (this->size_str_value) memcpy(this->str_value, _str_value, this->size_str_value * sizeof(char));
		}
		/// <summary>Constructs an <c>StringStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_str_value">The string value, in UTF-8, of this parameter.</param>
		/// <param name="_size_str_value">The size (in <c>char</c>s) of the string value, in UTF-8, of this parameter.</param>
		template<size_t count_char_name_parameter>
		inline StringStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char(&_name_parameter)[count_char_name_parameter],
			const char* _str_value = nullptr,
			size_t _size_str_value = 0
		) noexcept(false) : StringStringTemplateParameter(_rawallocator, _name_parameter, count_char_name_parameter - 1, _str_value, _size_str_value) {}
		/// <summary>Constructs an <c>StringStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_str_value">The string value, in UTF-8, of this parameter.</param>
		template<size_t count_char_name_parameter, size_t count_char_str_value>
		inline StringStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char(&_name_parameter)[count_char_name_parameter],
			const char(&_str_value)[count_char_str_value]
		) noexcept(false) : StringStringTemplateParameter(_rawallocator, _name_parameter, count_char_name_parameter - 1, _str_value, count_char_str_value - 1) {}
		inline StringStringTemplateParameter(const StringStringTemplateParameter& x) noexcept(false) : StringTemplateParameter(static_cast<const StringTemplateParameter&>(x)) {
			if (!x.str_value) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->size_str_value = x.size_str_value;
			this->str_value = reinterpret_cast<char*>(this->rawallocator->Allocate(this->size_str_value * sizeof(char), alignof(char[])));
			if (!this->str_value) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			if (this->size_str_value) memcpy(this->str_value, x.str_value, this->size_str_value * sizeof(char));
		}
		inline StringStringTemplateParameter(StringStringTemplateParameter&& x) noexcept(false) : StringTemplateParameter(static_cast<StringTemplateParameter&&>(::std::move(x))) {
			if (!x.str_value) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->str_value = ::std::move(x.str_value);
			this->size_str_value = ::std::move(x.size_str_value);
			x.str_value = nullptr;
			x.size_str_value = 0;
		}
		inline virtual ~StringStringTemplateParameter() {
			if (this->size_str_value) {
				this->rawallocator->Deallocate(this->str_value, this->size_str_value * sizeof(char));
				this->str_value = nullptr;
			}
			this->size_str_value = 0;
		}
		inline StringStringTemplateParameter& operator=(const StringStringTemplateParameter& x) noexcept(false) {
			if (this->size_str_value) {
				this->rawallocator->Deallocate(this->str_value, this->size_str_value * sizeof(char));
				this->str_value = nullptr;
			}
			this->size_str_value = 0;
			static_cast<StringTemplateParameter&>(*this) = static_cast<const StringTemplateParameter&>(x);
			if (!x.str_value) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->size_str_value = x.size_str_value;
			this->str_value = reinterpret_cast<char*>(this->rawallocator->Allocate(this->size_str_value * sizeof(char), alignof(char[])));
			if (!this->str_value) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			if (this->size_str_value) memcpy(this->str_value, x.str_value, this->size_str_value * sizeof(char));
			return *this;
		}
		inline StringStringTemplateParameter& operator=(StringStringTemplateParameter&& x) noexcept(false) {
			if (this->size_str_value) {
				this->rawallocator->Deallocate(this->str_value, this->size_str_value * sizeof(char));
				this->str_value = nullptr;
			}
			this->size_str_value = 0;
			static_cast<StringTemplateParameter&>(*this) = static_cast<StringTemplateParameter&&>(::std::move(x));
			if (!x.str_value) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->str_value = ::std::move(x.str_value);
			this->size_str_value = ::std::move(x.size_str_value);
			x.str_value = nullptr;
			x.size_str_value = 0;
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
		[[nodiscard]] inline virtual IException* GenerateString(
			const char* str_options,
			size_t size_str_options,
			char** str_out_ret,
			size_t* size_str_out_ret,
			bool should_null_terminate,
			const rawallocator_t* _rawallocator = nullptr
		) const noexcept override {
			static_cast<void>(str_options);
			if (size_str_options) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
			if (!str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
			if (!size_str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringStringTemplateParameter, GenerateString);
			*str_out_ret = nullptr;
			*size_str_out_ret = 0;
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &str_out_ret, &size_str_out_ret, &should_null_terminate, &_rawallocator, &err_inner]() noexcept(false)->void {
					if (!_rawallocator) _rawallocator = this->GetRawAllocator();
					*size_str_out_ret = should_null_terminate ? this->size_str_value + 1 : this->size_str_value;
					*str_out_ret = reinterpret_cast<char*>(_rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
					if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
					if (this->size_str_value) {
						if (!this->str_value) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
						memcpy(*str_out_ret, this->str_value, this->size_str_value * sizeof(char));
					}
					if (should_null_terminate) (*str_out_ret)[this->size_str_value] = 0;
				});
			if (err) {
				if (err_inner) {
					delete err_inner;
					err_inner = nullptr;
				}
				if (*str_out_ret) {
					_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
					*str_out_ret = nullptr;
					*size_str_out_ret = 0;
				}
				return err;
			}
			if (err_inner) {
				if (*str_out_ret) {
					_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
					*str_out_ret = nullptr;
					*size_str_out_ret = 0;
				}
				return err_inner;
			}
			return nullptr;
		}
	protected:
		char* str_value = nullptr;
		size_t size_str_value = 0;
	};

	/// <summary>A default implementation of a string template parameter that represents a memory address.</summary>
	class AddressStringTemplateParameter : public virtual StringTemplateParameter {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(AddressStringTemplateParameter, , "e1bce3de-f5f4-4375-a127-46fa41b4d3dd");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(AddressStringTemplateParameter);
		/// <summary>Constructs an <c>AddressStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_size_name_parameter">The size (in <c>char</c>s) of the name, in UTF-8, of this parameter.</param>
		/// <param name="_address">The memory address.</param>
		inline AddressStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char* _name_parameter,
			size_t _size_name_parameter,
			uintptr_t _address
		) noexcept(false) : StringTemplateParameter(_rawallocator, _name_parameter, _size_name_parameter), address(_address) {}
		/// <summary>Constructs an <c>AddressStringTemplateParameter</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_name_parameter">The name, in UTF-8, of this parameter.</param>
		/// <param name="_address">The memory address.</param>
		template<size_t count_char_name_parameter>
		inline AddressStringTemplateParameter(
			const rawallocator_t* _rawallocator,
			const char(&_name_parameter)[count_char_name_parameter],
			uintptr_t _address
		) noexcept(false) : AddressStringTemplateParameter(_rawallocator, _name_parameter, count_char_name_parameter - 1, _address) {}
		inline AddressStringTemplateParameter(const AddressStringTemplateParameter& x) noexcept(false)
			: StringTemplateParameter(static_cast<const StringTemplateParameter&>(x)), address(x.address) {}
		inline AddressStringTemplateParameter(AddressStringTemplateParameter&& x) noexcept(false)
			: StringTemplateParameter(static_cast<StringTemplateParameter&&>(::std::move(x))), address(::std::move(x.address)) {}
		inline virtual ~AddressStringTemplateParameter() {
			this->address = 0;
		}
		inline AddressStringTemplateParameter& operator=(const AddressStringTemplateParameter& x) noexcept(false) {
			static_cast<StringTemplateParameter&>(*this) = static_cast<const StringTemplateParameter&>(x);
			this->address = x.address;
			return *this;
		}
		inline AddressStringTemplateParameter& operator=(AddressStringTemplateParameter&& x) noexcept(false) {
			static_cast<StringTemplateParameter&>(*this) = static_cast<StringTemplateParameter&&>(::std::move(x));
			this->address = ::std::move(x.address);
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
		/// <summary>Gets the memory address.</summary>
		inline uintptr_t GetAddress() const noexcept { return this->address; }
	protected:
		uintptr_t address;
	};

	/// <summary>
	/// A default implementation of <c>IStringTemplateParameterList</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IStringTemplateParameterList</c>.
	/// </summary>
	class StringTemplateParameterList : public virtual IStringTemplateParameterList {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(StringTemplateParameterList, , "b671e5eb-89a3-4037-b96f-26f2041b709d");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(StringTemplateParameterList);
		/// <summary>Constructs an <c>StringTemplateParameterList</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		inline StringTemplateParameterList(const rawallocator_t* _rawallocator) noexcept(false)
			: rawallocator(_rawallocator),
			objholder_map_parameter(_rawallocator, objholder_rawallocator_t<map_parameter_t>::construct_obj, allocator_rawallocator_t<value_map_parameter_t>(*_rawallocator)) {
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringTemplateParameterList, StringTemplateParameterList));
		}
		/// <summary>Constructs an <c>StringTemplateParameterList</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_parameter">
		/// An initializer list of pointers to the parameters to be added.
		/// The parameters will not be owned by this object, instead, only pointers are stored.
		/// The parameter objects must survive for at least the lifetime of this object.
		/// </param>
		inline StringTemplateParameterList(const rawallocator_t* _rawallocator, const ::std::initializer_list<const IStringTemplateParameter*>& il_parameter) noexcept(false)
			: rawallocator(_rawallocator),
			objholder_map_parameter(_rawallocator, objholder_rawallocator_t<map_parameter_t>::construct_obj, allocator_rawallocator_t<value_map_parameter_t>(*_rawallocator)) {
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringTemplateParameterList, StringTemplateParameterList));
			try {
				for (const IStringTemplateParameter* val_parameter : il_parameter) {
					IException* err = this->AddParameter(val_parameter);
					if (err) throw(err);
				}
			} catch (::std::exception& err) {
				throw(YBWLIB2_EXCEPTION_CREATE_STL_EXCEPTION_EXCEPTION(err));
			}
		}
		/// <summary>
		/// Copy-constructs the parameter list.
		/// No deep copies will be performed for the parameters (which implies that the parameter objects will retain their raw allocators).
		/// </summary>
		inline StringTemplateParameterList(const StringTemplateParameterList& x) noexcept(false)
			: rawallocator(x.rawallocator), objholder_map_parameter(x.objholder_map_parameter) {}
		/// <summary>
		/// Move-constructs the parameter list.
		/// No deep moves will be performed for the parameters (which implies that the parameter objects will retain their raw allocators).
		/// </summary>
		inline StringTemplateParameterList(StringTemplateParameterList&& x) noexcept
			: rawallocator(x.rawallocator), objholder_map_parameter(::std::move(x.objholder_map_parameter)) {}
		inline virtual ~StringTemplateParameterList() {}
		/// <summary>
		/// Copy-assigns the parameter list.
		/// No deep copies will be performed for the parameters (which implies that the parameter objects will retain their raw allocators).
		/// </summary>
		inline StringTemplateParameterList& operator=(const StringTemplateParameterList& x) noexcept(false) {
			this->objholder_map_parameter.free();
			static_cast<IStringTemplateParameterList&>(*this) = static_cast<const IStringTemplateParameterList&>(x);
			this->rawallocator = x.rawallocator;
			this->objholder_map_parameter = x.objholder_map_parameter;
			return *this;
		}
		/// <summary>
		/// Move-assigns the parameter list.
		/// No deep moves will be performed for the parameters (which implies that the parameter objects will retain their raw allocators).
		/// </summary>
		inline StringTemplateParameterList& operator=(StringTemplateParameterList&& x) noexcept(false) {
			this->objholder_map_parameter.free();
			static_cast<IStringTemplateParameterList&>(*this) = static_cast<IStringTemplateParameterList&&>(::std::move(x));
			this->rawallocator = ::std::move(x.rawallocator);
			x.rawallocator = nullptr;
			this->objholder_map_parameter = ::std::move(x.objholder_map_parameter);
			x.objholder_map_parameter.free();
			return *this;
		}
		/// <summary>
		/// Gets a pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object will survive for at least the lifetime of this object.
		/// </summary>
		inline virtual const rawallocator_t* GetRawAllocator() const noexcept override { return this->rawallocator; }
		/// <summary>Gets the parameter with the specified name in this parameter list.</summary>
		/// <param name="_name_parameter">
		/// The name, in UTF-8, of the parameter.
		/// Parameter names are not null-terminated.
		/// </param>
		/// <param name="_size_name_parameter">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the parameter.
		/// Parameter names are not null-terminated.
		/// </param>
		/// <param name="parameter_ret">
		/// Pointer to a pointer variable that receives a pointer to the parameter with the specified name.
		/// After successfully returning from this member function, <c>*parameter_ret</c> will be set to the parameter with the specified name.
		/// Any value originally in <c>*parameter_ret</c> will be discarded (without destructing or freeing the object pointed to by it, if any).
		/// The caller should not destruct or free the object pointed to by the new <c>*parameter_ret</c> after a successful call.
		/// If there wasn't a parameter with the specified name in this parameter list, <c>*parameter_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="_rawallocator">
		/// An optional pointer to a <c>rawallocator_t</c> object for allocating memory used by this function, NOT INCLUDING the memory for <c>*parameter_ret</c>.
		/// If not specified or empty, <c>this->GetRawAllocator()</c> will be used instead.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory, instead of memory allocated using the raw allocator <paramref name="_rawallocator" /> or the one returned by <c>this->GetRawAllocator()</c>.
		/// </returns>
		[[nodiscard]] inline virtual IException* GetParameterByName(
			const char* _name_parameter,
			size_t _size_name_parameter,
			const IStringTemplateParameter** parameter_ret,
			const rawallocator_t* _rawallocator = nullptr
		) const noexcept override {
			if (!_name_parameter) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringTemplateParameterList, GetParameterByName);
			if (!parameter_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringTemplateParameterList, GetParameterByName);
			*parameter_ret = nullptr;
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &_name_parameter, &_size_name_parameter, &parameter_ret, &_rawallocator, &err_inner]() noexcept(false)->void {
					static_cast<void>(err_inner);
					if (!_rawallocator) _rawallocator = this->GetRawAllocator();
					allocator_rawallocator_t<string_name_parameter_t::value_type> allocator_name_parameter(*_rawallocator);
					map_parameter_t::const_iterator it_map_parameter = this->objholder_map_parameter->find(string_name_parameter_t(_name_parameter, _size_name_parameter, allocator_name_parameter));
					if (it_map_parameter != this->objholder_map_parameter->cend()) *parameter_ret = it_map_parameter->second;
				});
			if (err) {
				if (err_inner) {
					delete err_inner;
					err_inner = nullptr;
				}
				return err;
			} else {
				return err_inner;
			}
		}
		/// <summary>Adds a parameter into this parameter list.</summary>
		/// <param name="_parameter">
		/// Pointer to the parameter to be added.
		/// The parameter will not be owned by this object, instead, only a pointer is stored.
		/// The parameter object must survive for at least the lifetime of this object.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory, instead of memory allocated using the raw allocator returned by <c>this->GetRawAllocator()</c>.
		/// </returns>
		[[nodiscard]] inline virtual IException* AddParameter(const IStringTemplateParameter* _parameter) noexcept override {
			if (!_parameter) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringTemplateParameterList, AddParameter);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &_parameter, &err_inner]() noexcept(false)->void {
					const char* name_parameter = _parameter->GetParameterName();
					size_t size_name_parameter = _parameter->GetParameterNameSize();
					if (!name_parameter) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringTemplateParameterList, AddParameter); return; }
					if (!this->objholder_map_parameter->emplace(string_name_parameter_t(name_parameter, size_name_parameter, this->objholder_map_parameter->get_allocator()), _parameter).second) {
						err_inner = YBWLIB2_EXCEPTION_CREATE_KEY_ALREADY_EXIST_EXCEPTION();
						return;
					}
				});
			if (err) {
				if (err_inner) {
					delete err_inner;
					err_inner = nullptr;
				}
				return err;
			} else {
				return err_inner;
			}
		}
		/// <summary>
		/// Removes the parameter with the specified name from this parameter list.
		/// This function does not destruct or free the parameter object.
		/// It only removes it from this parameter list.
		/// </summary>
		/// <param name="_name_parameter">
		/// The name, in UTF-8, of the parameter.
		/// Parameter names are not null-terminated.
		/// </param>
		/// <param name="_size_name_parameter">
		/// The size (in <c>char</c>s) of the name, in UTF-8, of the parameter.
		/// Parameter names are not null-terminated.
		/// </param>
		/// <param name="_rawallocator">
		/// An optional pointer to a <c>rawallocator_t</c> object for allocating memory used by this function.
		/// If not specified or empty, <c>this->GetRawAllocator()</c> will be used instead.
		/// </param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory, instead of memory allocated using the raw allocator <paramref name="_rawallocator" /> or the one returned by <c>this->GetRawAllocator()</c>.
		/// </returns>
		[[nodiscard]] inline virtual IException* RemoveParameterByName(
			const char* _name_parameter,
			size_t _size_name_parameter,
			const rawallocator_t* _rawallocator = nullptr
		) noexcept override {
			if (!_name_parameter) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringTemplateParameterList, RemoveParameterByName);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &_name_parameter, &_size_name_parameter, &_rawallocator, &err_inner]() noexcept(false)->void {
					if (!_rawallocator) _rawallocator = this->GetRawAllocator();
					if (!this->objholder_map_parameter->erase(string_name_parameter_t(_name_parameter, _size_name_parameter, allocator_rawallocator_t<string_name_parameter_t::value_type>(*_rawallocator)))) {
						err_inner = YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION();
						return;
					}
				});
			if (err) {
				if (err_inner) {
					delete err_inner;
					err_inner = nullptr;
				}
				return err;
			} else {
				return err_inner;
			}
		}
	protected:
		using string_name_parameter_t = ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>;
		using value_map_parameter_t = ::std::pair<const string_name_parameter_t, const IStringTemplateParameter*>;
		using map_parameter_t = ::std::unordered_map<string_name_parameter_t, const IStringTemplateParameter*, ::std::hash<string_name_parameter_t>, ::std::equal_to<string_name_parameter_t>, allocator_rawallocator_t<value_map_parameter_t>>;
		const rawallocator_t* rawallocator = nullptr;
		objholder_rawallocator_t<map_parameter_t> objholder_map_parameter;
	};

	/// <summary>
	/// A default implementation of <c>IStringTemplate</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IStringTemplate</c>.
	/// </summary>
	class StringTemplate abstract : public virtual IStringTemplate {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(StringTemplate, , "43251d67-18cf-4202-84be-32ada6d6cc82");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(StringTemplate);
		/// <summary>Constructs an <c>StringTemplate</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		inline StringTemplate(const rawallocator_t* _rawallocator) noexcept(false) : rawallocator(_rawallocator) {
			if (!_rawallocator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::StringTemplate, StringTemplate));
		}
		inline StringTemplate(const StringTemplate& x) noexcept : rawallocator(x.rawallocator) {}
		inline StringTemplate(StringTemplate&& x) noexcept : rawallocator(::std::move(x.rawallocator)) {
			x.rawallocator = nullptr;
		}
		inline virtual ~StringTemplate() {}
		inline StringTemplate& operator=(const StringTemplate& x) noexcept {
			static_cast<IStringTemplate&>(*this) = static_cast<const IStringTemplate&>(x);
			this->rawallocator = x.rawallocator;
			return *this;
		}
		inline StringTemplate& operator=(StringTemplate&& x) noexcept {
			static_cast<IStringTemplate&>(*this) = static_cast<IStringTemplate&&>(::std::move(x));
			this->rawallocator = ::std::move(x.rawallocator);
			x.rawallocator = nullptr;
			return *this;
		}
		/// <summary>
		/// Gets a pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object will survive for at least the lifetime of this object.
		/// </summary>
		inline virtual const rawallocator_t* GetRawAllocator() const noexcept override { return this->rawallocator; }
		/// <summary>Generates a string using this string template and the specified parameter list.</summary>
		/// <param name="parameter_list">Pointer to a parameter list that may decide the string generation behaviour.</param>
		/// <param name="str_out_ret">
		/// Pointer to a pointer variable that receives a pointer to the generated string, in UTF-8.
		/// After successfully returning from this member function, <c>*str_out_ret</c> will be set to the generated string.
		/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*str_out_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
		/// If <paramref name="_rawallocator" /> is specified and not empty, the buffer for the part of the generated string will be allocated using <paramref name="_rawallocator" />.
		/// Otherwise, the buffer for the part of the generated string will be allocated using the raw allocator returned by <c>this->GetRawAllocator()</c>.
		/// </param>
		/// <param name="size_str_out_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the generated string, in UTF-8, including the terminating null character, if any.
		/// After successfully returning from this member function, <c>*size_str_out_ret</c> will be set to the size (in <c>char</c>s) of the generated string.
		/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
		/// </param>
		/// <param name="should_null_terminate">Whether a terminating null character should be added to the end of the generated string.</param>
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
		[[nodiscard]] inline virtual IException* GenerateString(
			const IStringTemplateParameterList* parameter_list,
			char** str_out_ret,
			size_t* size_str_out_ret,
			bool should_null_terminate,
			const rawallocator_t* _rawallocator = nullptr
		) const noexcept override = 0;
	protected:
		const rawallocator_t* rawallocator = nullptr;
	};

	/// <summary>
	/// String template from JSON SAX generator constructor.
	/// The pointer to the raw allocator is passed as a parameter using <c>RawAllocatorParameterIndexedDataEntry</c>.
	/// The pointer to the <c>IJSONSAXGenerator</c> object that generates the JSON value representation of the template is passed as a parameter using <c>JSONSAXGeneratorParameterIndexedDataEntry</c>.
	/// </summary>
	constexpr PersistentID PersistentID_ConstructorID_StringTemplateFromJSONSAXGenerator = PersistentID(UUIDFromUUIDString_CompileTime("2a02e0f3-3fc8-46c8-8d85-13b624bf5d35"));
	/// <summary>
	/// String template from JSON SAX generator constructor.
	/// The pointer to the raw allocator is passed as a parameter using <c>RawAllocatorParameterIndexedDataEntry</c>.
	/// The pointer to the <c>IJSONSAXGenerator</c> object that generates the JSON value representation of the template is passed as a parameter using <c>JSONSAXGeneratorParameterIndexedDataEntry</c>.
	/// </summary>
	extern YBWLIB2_API ConstructorID ConstructorID_StringTemplateFromJSONSAXGenerator;

	template<typename T_Class>
	::std::array<::std::pair<PersistentID, DynamicTypeClassSpecificCreateObjectDelegate<T_Class>>, 0x3> GetStringTemplateDefaultClassSpecificCreateDelegateArray() {
		::std::array<::std::pair<PersistentID, DynamicTypeClassSpecificCreateObjectDelegate<T_Class>>, 0x3> arr_delegate_create;
		size_t idx_delegate_create = 0;
		arr_delegate_create[idx_delegate_create++] =
			::std::pair<PersistentID, DynamicTypeClassSpecificCreateObjectDelegate<T_Class>>(
				PersistentID_ConstructorID_StringTemplateFromJSONSAXGenerator,
				DynamicTypeClassSpecificCreateObjectDelegate<T_Class>(
					[](uintptr_t, uintptr_t, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->T_Class* {
						if (!_indexeddatastore_parameters) abort();
						return new T_Class(
							RawAllocatorParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters).rawalloctor,
							JSONSAXGeneratorParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters).jsonsaxgenerator
						);
					}
					)
				);
		arr_delegate_create[idx_delegate_create++] =
			::std::pair<PersistentID, DynamicTypeClassSpecificCreateObjectDelegate<T_Class>>(
				PersistentID_ConstructorID_Copy,
				DynamicTypeClassSpecificCreateObjectDelegate<T_Class>(
					[](uintptr_t, uintptr_t, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->T_Class* {
						if (!_indexeddatastore_parameters) abort();
						T_Class* ptr_obj_from = reinterpret_cast<T_Class*>(ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters).uintptr_ptr_obj);
						if (!ptr_obj_from) throw(new InvalidParameterException(nullptr, 0));
						return new T_Class(*ptr_obj_from);
					}
					)
				);
		arr_delegate_create[idx_delegate_create++] =
			::std::pair<PersistentID, DynamicTypeClassSpecificCreateObjectDelegate<T_Class>>(
				PersistentID_ConstructorID_Move,
				DynamicTypeClassSpecificCreateObjectDelegate<T_Class>(
					[](uintptr_t, uintptr_t, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->T_Class* {
						if (!_indexeddatastore_parameters) abort();
						T_Class* ptr_obj_from = reinterpret_cast<T_Class*>(ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters).uintptr_ptr_obj);
						if (!ptr_obj_from) throw(new InvalidParameterException(nullptr, 0));
						return new T_Class(::std::move(*ptr_obj_from));
					}
					)
				);
		assert(idx_delegate_create == arr_delegate_create.size());
		return arr_delegate_create;
	}

	template<typename T_Class>
	::std::array<::std::pair<PersistentID, DynamicTypeClassSpecificPlacementCreateObjectDelegate<T_Class>>, 0x3> GetStringTemplateDefaultClassSpecificPlacementCreateDelegateArray() {
		::std::array<::std::pair<PersistentID, DynamicTypeClassSpecificPlacementCreateObjectDelegate<T_Class>>, 0x3> arr_delegate_placement_create;
		size_t idx_delegate_placement_create = 0;
		arr_delegate_placement_create[idx_delegate_placement_create++] =
			::std::pair<PersistentID, DynamicTypeClassSpecificPlacementCreateObjectDelegate<T_Class>>(
				PersistentID_ConstructorID_StringTemplateFromJSONSAXGenerator,
				DynamicTypeClassSpecificPlacementCreateObjectDelegate<T_Class>(
					[](uintptr_t, uintptr_t, void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->T_Class* {
						if (!_indexeddatastore_parameters) abort();
						return new(_ptr_placement) T_Class(
							RawAllocatorParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters).rawalloctor,
							JSONSAXGeneratorParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters).jsonsaxgenerator
						);
					}
					)
				);
		arr_delegate_placement_create[idx_delegate_placement_create++] =
			::std::pair<PersistentID, DynamicTypeClassSpecificPlacementCreateObjectDelegate<T_Class>>(
				PersistentID_ConstructorID_Copy,
				DynamicTypeClassSpecificPlacementCreateObjectDelegate<T_Class>(
					[](uintptr_t, uintptr_t, void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->T_Class* {
						if (!_indexeddatastore_parameters) abort();
						T_Class* ptr_obj_from = reinterpret_cast<T_Class*>(ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters).uintptr_ptr_obj);
						if (!ptr_obj_from) throw(new InvalidParameterException(nullptr, 0));
						return new(_ptr_placement) T_Class(*ptr_obj_from);
					}
					)
				);
		arr_delegate_placement_create[idx_delegate_placement_create++] =
			::std::pair<PersistentID, DynamicTypeClassSpecificPlacementCreateObjectDelegate<T_Class>>(
				PersistentID_ConstructorID_Move,
				DynamicTypeClassSpecificPlacementCreateObjectDelegate<T_Class>(
					[](uintptr_t, uintptr_t, void* _ptr_placement, IndexedDataStore* _indexeddatastore_parameters) noexcept(false)->T_Class* {
						if (!_indexeddatastore_parameters) abort();
						T_Class* ptr_obj_from = reinterpret_cast<T_Class*>(ObjectPointerFromParameterIndexedDataEntry::CopyFromStore(*_indexeddatastore_parameters).uintptr_ptr_obj);
						if (!ptr_obj_from) throw(new InvalidParameterException(nullptr, 0));
						return new(_ptr_placement) T_Class(::std::move(*ptr_obj_from));
					}
					)
				);
		assert(idx_delegate_placement_create == arr_delegate_placement_create.size());
		return arr_delegate_placement_create;
	}

	/// <summary>A default implementation of a string template that generates a fixed string independent of the string template parameter(s).</summary>
	class FixedStringTemplate : public virtual StringTemplate {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(FixedStringTemplate, , "e1bfd083-8545-4abf-850c-8982f513c733");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(FixedStringTemplate);
		/// <summary>Constructs an <c>FixedStringTemplate</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="_str_value">The fixed string, in UTF-8, to be generated by this string template.</param>
		/// <param name="_size_str_value">The size (in <c>char</c>s) of the fixed string, in UTF-8, to be generated by this string template.</param>
		inline FixedStringTemplate(
			const rawallocator_t* _rawallocator,
			const char* _str_value = nullptr,
			size_t _size_str_value = 0
		) noexcept(false) : StringTemplate(_rawallocator) {
			if (_size_str_value && !_str_value) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::FixedStringTemplate, FixedStringTemplate));
			this->size_str_value = _size_str_value;
			this->str_value = reinterpret_cast<char*>(this->rawallocator->Allocate(this->size_str_value * sizeof(char), alignof(char[])));
			if (!this->str_value) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			if (this->size_str_value) memcpy(this->str_value, _str_value, this->size_str_value * sizeof(char));
		}
		/// <summary>Constructs an <c>FixedStringTemplate</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="jsonsaxgenerator">A pointer to a JSON SAX generator that provides a JSON value that represents to this string template.</param>
		FixedStringTemplate(
			const rawallocator_t* _rawallocator,
			IJSONSAXGenerator* jsonsaxgenerator
		) noexcept(false);
		inline FixedStringTemplate(const FixedStringTemplate& x) noexcept(false) : StringTemplate(static_cast<const StringTemplate&>(x)) {
			if (!x.str_value) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->size_str_value = x.size_str_value;
			this->str_value = reinterpret_cast<char*>(this->rawallocator->Allocate(this->size_str_value * sizeof(char), alignof(char[])));
			if (!this->str_value) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			if (this->size_str_value) memcpy(this->str_value, x.str_value, this->size_str_value * sizeof(char));
		}
		inline FixedStringTemplate(FixedStringTemplate&& x) noexcept(false) : StringTemplate(static_cast<StringTemplate&&>(::std::move(x))) {
			if (!x.str_value) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->str_value = ::std::move(x.str_value);
			this->size_str_value = ::std::move(x.size_str_value);
			x.str_value = nullptr;
			x.size_str_value = 0;
		}
		inline virtual ~FixedStringTemplate() {
			if (this->size_str_value) {
				this->rawallocator->Deallocate(this->str_value, this->size_str_value * sizeof(char));
				this->str_value = nullptr;
			}
			this->size_str_value = 0;
		}
		inline FixedStringTemplate& operator=(const FixedStringTemplate& x) noexcept(false) {
			if (this->size_str_value) {
				this->rawallocator->Deallocate(this->str_value, this->size_str_value * sizeof(char));
				this->str_value = nullptr;
			}
			this->size_str_value = 0;
			static_cast<StringTemplate&>(*this) = static_cast<const StringTemplate&>(x);
			if (!x.str_value) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->size_str_value = x.size_str_value;
			this->str_value = reinterpret_cast<char*>(this->rawallocator->Allocate(this->size_str_value * sizeof(char), alignof(char[])));
			if (!this->str_value) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
			if (this->size_str_value) memcpy(this->str_value, x.str_value, this->size_str_value * sizeof(char));
			return *this;
		}
		inline FixedStringTemplate& operator=(FixedStringTemplate&& x) noexcept(false) {
			if (this->size_str_value) {
				this->rawallocator->Deallocate(this->str_value, this->size_str_value * sizeof(char));
				this->str_value = nullptr;
			}
			this->size_str_value = 0;
			static_cast<StringTemplate&>(*this) = static_cast<StringTemplate&&>(::std::move(x));
			if (!x.str_value) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
			this->str_value = ::std::move(x.str_value);
			this->size_str_value = ::std::move(x.size_str_value);
			x.str_value = nullptr;
			x.size_str_value = 0;
			return *this;
		}
		/// <summary>Generates a string using this string template and the specified parameter list.</summary>
		/// <param name="parameter_list">
		/// Pointer to a parameter list that may decide the string generation behaviour.
		/// This type of string template ignores the parameter list.
		/// </param>
		/// <param name="str_out_ret">
		/// Pointer to a pointer variable that receives a pointer to the generated string, in UTF-8.
		/// After successfully returning from this member function, <c>*str_out_ret</c> will be set to the generated string.
		/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*str_out_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
		/// If <paramref name="_rawallocator" /> is specified and not empty, the buffer for the part of the generated string will be allocated using <paramref name="_rawallocator" />.
		/// Otherwise, the buffer for the part of the generated string will be allocated using the raw allocator returned by <c>this->GetRawAllocator()</c>.
		/// </param>
		/// <param name="size_str_out_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the generated string, in UTF-8, including the terminating null character, if any.
		/// After successfully returning from this member function, <c>*size_str_out_ret</c> will be set to the size (in <c>char</c>s) of the generated string.
		/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
		/// </param>
		/// <param name="should_null_terminate">Whether a terminating null character should be added to the end of the generated string.</param>
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
		[[nodiscard]] inline virtual IException* GenerateString(
			const IStringTemplateParameterList* parameter_list,
			char** str_out_ret,
			size_t* size_str_out_ret,
			bool should_null_terminate,
			const rawallocator_t* _rawallocator = nullptr
		) const noexcept override {
			static_cast<void>(parameter_list);
			if (!str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::FixedStringTemplate, GenerateString);
			if (!size_str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::FixedStringTemplate, GenerateString);
			*str_out_ret = nullptr;
			*size_str_out_ret = 0;
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &str_out_ret, &size_str_out_ret, &should_null_terminate, &_rawallocator, &err_inner]() noexcept(false)->void {
					if (!_rawallocator) _rawallocator = this->GetRawAllocator();
					*size_str_out_ret = should_null_terminate ? this->size_str_value + 1 : this->size_str_value;
					*str_out_ret = reinterpret_cast<char*>(_rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
					if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
					if (this->size_str_value) {
						if (!this->str_value) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
						memcpy(*str_out_ret, this->str_value, this->size_str_value * sizeof(char));
					}
					if (should_null_terminate) (*str_out_ret)[this->size_str_value] = 0;
				});
			if (err) {
				if (err_inner) {
					delete err_inner;
					err_inner = nullptr;
				}
				if (*str_out_ret) {
					_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
					*str_out_ret = nullptr;
					*size_str_out_ret = 0;
				}
				return err;
			}
			if (err_inner) {
				if (*str_out_ret) {
					_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
					*str_out_ret = nullptr;
					*size_str_out_ret = 0;
				}
				return err_inner;
			}
			return nullptr;
		}
	protected:
		char* str_value = nullptr;
		size_t size_str_value = 0;
	};

	/// <summary>A default implementation of a string template that generates a string, optionally with elements in it substituted by the string template parameter(s).</summary>
	class SubstitutionStringTemplate : public virtual StringTemplate {
		friend SubstitutionStringTemplateConstructorJSONSAXHandler;
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(SubstitutionStringTemplate, , "2a489e78-61b3-4da1-b7a2-d6fa6f73cb7d");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(SubstitutionStringTemplate);
		/// <summary>Constructs an <c>SubstitutionStringTemplate</c> object.</summary>
		/// <param name="_rawallocator">
		/// A pointer to a <c>rawallocator_t</c> object for allocating memory used by this class.
		/// The <c>rawallocator_t</c> object must survive for at least the lifetime of this object and any objects copied or moved from this object.
		/// </param>
		/// <param name="jsonsaxgenerator">A pointer to a JSON SAX generator that provides a JSON value that represents to this string template.</param>
		SubstitutionStringTemplate(
			const rawallocator_t* _rawallocator,
			IJSONSAXGenerator* jsonsaxgenerator
		) noexcept(false);
		inline SubstitutionStringTemplate(const SubstitutionStringTemplate& x) noexcept(false)
			: StringTemplate(static_cast<const StringTemplate&>(x)),
			objholder_vec_element(x.objholder_vec_element) {}
		inline SubstitutionStringTemplate(SubstitutionStringTemplate&& x) noexcept(false)
			: StringTemplate(static_cast<StringTemplate&&>(::std::move(x))),
			objholder_vec_element(::std::move(x.objholder_vec_element)) {}
		inline virtual ~SubstitutionStringTemplate() {}
		inline SubstitutionStringTemplate& operator=(const SubstitutionStringTemplate& x) noexcept(false) {
			this->objholder_vec_element.free();
			static_cast<StringTemplate&>(*this) = static_cast<const StringTemplate&>(x);
			this->objholder_vec_element = x.objholder_vec_element;
			return *this;
		}
		inline SubstitutionStringTemplate& operator=(SubstitutionStringTemplate&& x) noexcept(false) {
			this->objholder_vec_element.free();
			static_cast<StringTemplate&>(*this) = static_cast<StringTemplate&&>(::std::move(x));
			this->objholder_vec_element = ::std::move(x.objholder_vec_element);
			x.objholder_vec_element.free();
			return *this;
		}
		/// <summary>Generates a string using this string template and the specified parameter list.</summary>
		/// <param name="parameter_list">
		/// Pointer to a parameter list that may decide the string generation behaviour.
		/// The parameters may be used to substitute certain elements in the generated string.
		/// </param>
		/// <param name="str_out_ret">
		/// Pointer to a pointer variable that receives a pointer to the generated string, in UTF-8.
		/// After successfully returning from this member function, <c>*str_out_ret</c> will be set to the generated string.
		/// Any value originally in <c>*str_out_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*str_out_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*str_out_ret</c>.
		/// If <paramref name="_rawallocator" /> is specified and not empty, the buffer for the part of the generated string will be allocated using <paramref name="_rawallocator" />.
		/// Otherwise, the buffer for the part of the generated string will be allocated using the raw allocator returned by <c>this->GetRawAllocator()</c>.
		/// </param>
		/// <param name="size_str_out_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the generated string, in UTF-8, including the terminating null character, if any.
		/// After successfully returning from this member function, <c>*size_str_out_ret</c> will be set to the size (in <c>char</c>s) of the generated string.
		/// Any value originally in <c>*size_str_out_ret</c> will be discarded.
		/// </param>
		/// <param name="should_null_terminate">Whether a terminating null character should be added to the end of the generated string.</param>
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
		[[nodiscard]] inline virtual IException* GenerateString(
			const IStringTemplateParameterList* parameter_list,
			char** str_out_ret,
			size_t* size_str_out_ret,
			bool should_null_terminate,
			const rawallocator_t* _rawallocator = nullptr
		) const noexcept override {
			if (!str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplate, GenerateString);
			if (!size_str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplate, GenerateString);
			*str_out_ret = nullptr;
			*size_str_out_ret = 0;
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &parameter_list, &str_out_ret, &size_str_out_ret, &should_null_terminate, &_rawallocator, &err_inner]() noexcept(false)->void {
					if (!_rawallocator) _rawallocator = this->GetRawAllocator();
					using string_str_out_element_t = ::std::basic_string<char, ::std::char_traits<char>, allocator_rawallocator_t<char>>;
					using vec_str_out_element_t = ::std::vector<string_str_out_element_t, allocator_rawallocator_t<string_str_out_element_t>>;
					allocator_rawallocator_t<string_str_out_element_t> allocator_vec_vec_str_out_element(*_rawallocator);
					vec_str_out_element_t vec_str_out_element(allocator_vec_vec_str_out_element);
					vec_str_out_element.reserve(this->objholder_vec_element->size());
					for (const element_t& val_element : *this->objholder_vec_element) {
						char* str_out_element = nullptr;
						size_t size_str_out_element = 0;
						try {
							IException* err = val_element.GenerateString(parameter_list, &str_out_element, &size_str_out_element, _rawallocator);
							if (err) throw(err);
							vec_str_out_element.emplace_back(str_out_element, size_str_out_element, allocator_rawallocator_t<string_str_out_element_t::value_type>(*_rawallocator));
							if (str_out_element) {
								_rawallocator->Deallocate(str_out_element, size_str_out_element * sizeof(char));
								str_out_element = nullptr;
							}
							size_str_out_element = 0;
						} catch (...) {
							if (str_out_element) {
								_rawallocator->Deallocate(str_out_element, size_str_out_element * sizeof(char));
								str_out_element = nullptr;
							}
							size_str_out_element = 0;
							throw;
						}
					}
					for (const string_str_out_element_t& val_str_out_element : vec_str_out_element) {
						*size_str_out_ret += val_str_out_element.size();
					}
					if (should_null_terminate)
						++*size_str_out_ret;
					if (*size_str_out_ret) {
						*str_out_ret = reinterpret_cast<char*>(_rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
						if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
						*size_str_out_ret = 0;
						for (const string_str_out_element_t& val_str_out_element : vec_str_out_element) {
							memcpy(*str_out_ret + *size_str_out_ret, val_str_out_element.data(), val_str_out_element.size() * sizeof(char));
							*size_str_out_ret += val_str_out_element.size();
						}
						if (should_null_terminate) {
							(*str_out_ret)[*size_str_out_ret] = 0;
							++*size_str_out_ret;
						}
					}
				});
			if (err) {
				if (err_inner) {
					delete err_inner;
					err_inner = nullptr;
				}
				if (*str_out_ret) {
					_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
					*str_out_ret = nullptr;
					*size_str_out_ret = 0;
				}
				return err;
			}
			if (err_inner) {
				if (*str_out_ret) {
					_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
					*str_out_ret = nullptr;
					*size_str_out_ret = 0;
				}
				return err_inner;
			}
			return nullptr;
		}
	protected:
		enum ElementType : uint32_t {
			ElementType_Raw = 0,
			ElementType_Substitute
		};
		class element_t final {
		public:
			ElementType type_element;
			const rawallocator_t* rawallocator = nullptr;
			union {
				struct {
					char* str_value;
					size_t size_str_value;
				} content_raw;
				struct {
					char* name_parameter;
					size_t size_name_parameter;
					char* str_options;
					size_t size_str_options;
				} content_substitute;
			};
			inline element_t(const rawallocator_t* _rawallocator, const char* _str_value, size_t _size_str_value) noexcept(false)
				: type_element(ElementType_Raw), rawallocator(_rawallocator) {
				if (_size_str_value && !_str_value) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplate::element_t, element_t));
				this->content_raw.size_str_value = _size_str_value;
				this->content_raw.str_value = reinterpret_cast<char*>(this->rawallocator->Allocate(this->content_raw.size_str_value * sizeof(char), alignof(char[])));
				if (!this->content_raw.str_value) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
				if (this->content_raw.size_str_value) memcpy(this->content_raw.str_value, _str_value, this->content_raw.size_str_value * sizeof(char));
			}
			inline element_t(const rawallocator_t* _rawallocator, char* _name_parameter, size_t _size_name_parameter, char* _str_options, size_t _size_str_options) noexcept(false)
				: type_element(ElementType_Substitute), rawallocator(_rawallocator) {
				if (_size_name_parameter && !_name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplate::element_t, element_t));
				if (_size_str_options && !_str_options) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplate::element_t, element_t));
				{
					this->content_substitute.size_name_parameter = _size_name_parameter;
					this->content_substitute.name_parameter = reinterpret_cast<char*>(this->rawallocator->Allocate(this->content_substitute.size_name_parameter * sizeof(char), alignof(char[])));
					if (!this->content_substitute.name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
					if (this->content_substitute.size_name_parameter) memcpy(this->content_substitute.name_parameter, _name_parameter, this->content_substitute.size_name_parameter * sizeof(char));
				}
				{
					this->content_substitute.size_str_options = _size_str_options;
					this->content_substitute.str_options = reinterpret_cast<char*>(this->rawallocator->Allocate(this->content_substitute.size_str_options * sizeof(char), alignof(char[])));
					if (!this->content_substitute.str_options) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
					if (this->content_substitute.size_str_options) memcpy(this->content_substitute.str_options, _str_options, this->content_substitute.size_str_options * sizeof(char));
				}
			}
			inline element_t(const element_t& x) noexcept(false) : type_element(x.type_element), rawallocator(x.rawallocator) {
				switch (this->type_element) {
				case ElementType_Raw: {
					if (!x.content_raw.str_value) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
					this->content_raw.size_str_value = x.content_raw.size_str_value;
					this->content_raw.str_value = reinterpret_cast<char*>(this->rawallocator->Allocate(this->content_raw.size_str_value * sizeof(char), alignof(char[])));
					if (!this->content_raw.str_value) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
					if (this->content_raw.size_str_value) memcpy(this->content_raw.str_value, x.content_raw.str_value, this->content_raw.size_str_value * sizeof(char));
					break;
				}
				case ElementType_Substitute: {
					{
						if (!x.content_substitute.name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
						this->content_substitute.size_name_parameter = x.content_substitute.size_name_parameter;
						this->content_substitute.name_parameter = reinterpret_cast<char*>(this->rawallocator->Allocate(this->content_substitute.size_name_parameter * sizeof(char), alignof(char[])));
						if (!this->content_substitute.name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
						if (this->content_substitute.size_name_parameter) memcpy(this->content_substitute.name_parameter, x.content_substitute.name_parameter, this->content_substitute.size_name_parameter * sizeof(char));
					}
					{
						if (!x.content_substitute.str_options) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
						this->content_substitute.size_str_options = x.content_substitute.size_str_options;
						this->content_substitute.str_options = reinterpret_cast<char*>(this->rawallocator->Allocate(this->content_substitute.size_str_options * sizeof(char), alignof(char[])));
						if (!this->content_substitute.str_options) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
						if (this->content_substitute.size_str_options) memcpy(this->content_substitute.str_options, x.content_substitute.str_options, this->content_substitute.size_str_options * sizeof(char));
					}
					break;
				}
				default: {
					throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				}
				}
			}
			inline element_t(element_t&& x) noexcept(false) : type_element(x.type_element), rawallocator(x.rawallocator) {
				switch (this->type_element) {
				case ElementType_Raw: {
					if (!x.content_raw.str_value) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
					this->content_raw.str_value = x.content_raw.str_value;
					this->content_raw.size_str_value = x.content_raw.size_str_value;
					x.content_raw.str_value = nullptr;
					x.content_raw.size_str_value = 0;
					break;
				}
				case ElementType_Substitute: {
					{
						if (!x.content_substitute.name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
						this->content_substitute.name_parameter = x.content_substitute.name_parameter;
						this->content_substitute.size_name_parameter = x.content_substitute.size_name_parameter;
						x.content_substitute.name_parameter = nullptr;
						x.content_substitute.size_name_parameter = 0;
					}
					{
						if (!x.content_substitute.str_options) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
						this->content_substitute.str_options = x.content_substitute.str_options;
						this->content_substitute.size_str_options = x.content_substitute.size_str_options;
						x.content_substitute.str_options = nullptr;
						x.content_substitute.size_str_options = 0;
					}
					break;
				}
				default: {
					throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				}
				}
			}
			inline ~element_t() {
				switch (this->type_element) {
				case ElementType_Raw: {
					if (this->content_raw.size_str_value) {
						this->rawallocator->Deallocate(this->content_raw.str_value, this->content_raw.size_str_value * sizeof(char));
						this->content_raw.str_value = nullptr;
					}
					this->content_raw.size_str_value = 0;
					break;
				}
				case ElementType_Substitute: {
					{
						if (this->content_substitute.size_name_parameter) {
							this->rawallocator->Deallocate(this->content_substitute.name_parameter, this->content_substitute.size_name_parameter * sizeof(char));
							this->content_substitute.name_parameter = nullptr;
						}
						this->content_substitute.size_name_parameter = 0;
					}
					{
						if (this->content_substitute.size_str_options) {
							this->rawallocator->Deallocate(this->content_substitute.str_options, this->content_substitute.size_str_options * sizeof(char));
							this->content_substitute.str_options = nullptr;
						}
						this->content_substitute.size_str_options = 0;
					}
					break;
				}
				}
			}
			inline element_t& operator=(const element_t& x) noexcept(false) {
				switch (this->type_element) {
				case ElementType_Raw: {
					if (this->content_raw.size_str_value) {
						this->rawallocator->Deallocate(this->content_raw.str_value, this->content_raw.size_str_value * sizeof(char));
						this->content_raw.str_value = nullptr;
					}
					this->content_raw.size_str_value = 0;
					break;
				}
				case ElementType_Substitute: {
					{
						if (this->content_substitute.size_name_parameter) {
							this->rawallocator->Deallocate(this->content_substitute.name_parameter, this->content_substitute.size_name_parameter * sizeof(char));
							this->content_substitute.name_parameter = nullptr;
						}
						this->content_substitute.size_name_parameter = 0;
					}
					{
						if (this->content_substitute.size_str_options) {
							this->rawallocator->Deallocate(this->content_substitute.str_options, this->content_substitute.size_str_options * sizeof(char));
							this->content_substitute.str_options = nullptr;
						}
						this->content_substitute.size_str_options = 0;
					}
					break;
				}
				default: {
					throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				}
				}
				this->type_element = x.type_element;
				this->rawallocator = x.rawallocator;
				switch (this->type_element) {
				case ElementType_Raw: {
					if (!x.content_raw.str_value) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
					this->content_raw.size_str_value = x.content_raw.size_str_value;
					this->content_raw.str_value = reinterpret_cast<char*>(this->rawallocator->Allocate(this->content_raw.size_str_value * sizeof(char), alignof(char[])));
					if (!this->content_raw.str_value) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
					if (this->content_raw.size_str_value) memcpy(this->content_raw.str_value, x.content_raw.str_value, this->content_raw.size_str_value * sizeof(char));
					break;
				}
				case ElementType_Substitute: {
					{
						if (!x.content_substitute.name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
						this->content_substitute.size_name_parameter = x.content_substitute.size_name_parameter;
						this->content_substitute.name_parameter = reinterpret_cast<char*>(this->rawallocator->Allocate(this->content_substitute.size_name_parameter * sizeof(char), alignof(char[])));
						if (!this->content_substitute.name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
						if (this->content_substitute.size_name_parameter) memcpy(this->content_substitute.name_parameter, x.content_substitute.name_parameter, this->content_substitute.size_name_parameter * sizeof(char));
					}
					{
						if (!x.content_substitute.str_options) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
						this->content_substitute.size_str_options = x.content_substitute.size_str_options;
						this->content_substitute.str_options = reinterpret_cast<char*>(this->rawallocator->Allocate(this->content_substitute.size_str_options * sizeof(char), alignof(char[])));
						if (!this->content_substitute.str_options) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
						if (this->content_substitute.size_str_options) memcpy(this->content_substitute.str_options, x.content_substitute.str_options, this->content_substitute.size_str_options * sizeof(char));
					}
					break;
				}
				default: {
					throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				}
				}
				return *this;
			}
			inline element_t& operator=(element_t&& x) noexcept(false) {
				switch (this->type_element) {
				case ElementType_Raw: {
					if (this->content_raw.size_str_value) {
						this->rawallocator->Deallocate(this->content_raw.str_value, this->content_raw.size_str_value * sizeof(char));
						this->content_raw.str_value = nullptr;
					}
					this->content_raw.size_str_value = 0;
					break;
				}
				case ElementType_Substitute: {
					{
						if (this->content_substitute.size_name_parameter) {
							this->rawallocator->Deallocate(this->content_substitute.name_parameter, this->content_substitute.size_name_parameter * sizeof(char));
							this->content_substitute.name_parameter = nullptr;
						}
						this->content_substitute.size_name_parameter = 0;
					}
					{
						if (this->content_substitute.size_str_options) {
							this->rawallocator->Deallocate(this->content_substitute.str_options, this->content_substitute.size_str_options * sizeof(char));
							this->content_substitute.str_options = nullptr;
						}
						this->content_substitute.size_str_options = 0;
					}
					break;
				}
				default: {
					throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				}
				}
				this->type_element = ::std::move(x.type_element);
				this->rawallocator = ::std::move(x.rawallocator);
				switch (this->type_element) {
				case ElementType_Raw: {
					if (!x.content_raw.str_value) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
					this->content_raw.str_value = ::std::move(x.content_raw.str_value);
					this->content_raw.size_str_value = ::std::move(x.content_raw.size_str_value);
					x.content_raw.str_value = nullptr;
					x.content_raw.size_str_value = 0;
					break;
				}
				case ElementType_Substitute: {
					{
						if (!x.content_substitute.name_parameter) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
						this->content_substitute.name_parameter = ::std::move(x.content_substitute.name_parameter);
						this->content_substitute.size_name_parameter = ::std::move(x.content_substitute.size_name_parameter);
						x.content_substitute.name_parameter = nullptr;
						x.content_substitute.size_name_parameter = 0;
					}
					{
						if (!x.content_substitute.str_options) throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
						this->content_substitute.str_options = ::std::move(x.content_substitute.str_options);
						this->content_substitute.size_str_options = ::std::move(x.content_substitute.size_str_options);
						x.content_substitute.str_options = nullptr;
						x.content_substitute.size_str_options = 0;
					}
					break;
				}
				default: {
					throw(YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION());
				}
				}
				return *this;
			}
			[[nodiscard]] IException* GenerateString(
				const IStringTemplateParameterList* parameter_list,
				char** str_out_ret,
				size_t* size_str_out_ret,
				const rawallocator_t* _rawallocator
			) const noexcept {
				if (!str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::FixedStringTemplate::element_t, GenerateString);
				if (!size_str_out_ret) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::FixedStringTemplate::element_t, GenerateString);
				*str_out_ret = nullptr;
				*size_str_out_ret = 0;
				switch (this->type_element) {
				case ElementType_Raw: {
					static_cast<void>(parameter_list);
					IException* err_inner = nullptr;
					IException* err = WrapFunctionCatchExceptions(
						[this, &str_out_ret, &size_str_out_ret, &_rawallocator, &err_inner]() noexcept(false)->void {
							if (!_rawallocator) _rawallocator = this->rawallocator;
							*size_str_out_ret = this->content_raw.size_str_value;
							*str_out_ret = reinterpret_cast<char*>(_rawallocator->Allocate(*size_str_out_ret * sizeof(char), alignof(char[])));
							if (!*str_out_ret) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
							if (this->content_raw.size_str_value) {
								if (!this->content_raw.str_value) { err_inner = YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION(); return; }
								memcpy(*str_out_ret, this->content_raw.str_value, this->content_raw.size_str_value * sizeof(char));
							}
						});
					if (err) {
						if (err_inner) {
							delete err_inner;
							err_inner = nullptr;
						}
						if (*str_out_ret) {
							_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
						}
						return err;
					}
					if (err_inner) {
						if (*str_out_ret) {
							_rawallocator->Deallocate(*str_out_ret, *size_str_out_ret);
							*str_out_ret = nullptr;
							*size_str_out_ret = 0;
						}
						return err_inner;
					}
					return nullptr;
				}
				case ElementType_Substitute: {
					if (!parameter_list) return YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::FixedStringTemplate::element_t, GenerateString);
					const IStringTemplateParameter* parameter = nullptr;
					IException* err = parameter_list->GetParameterByName(this->content_substitute.name_parameter, this->content_substitute.size_name_parameter, &parameter, _rawallocator);
					if (err) return err;
					if (!parameter) return YBWLIB2_EXCEPTION_CREATE_KEY_NOT_EXIST_EXCEPTION();
					return parameter->GenerateString(this->content_substitute.str_options, this->content_substitute.size_str_options, str_out_ret, size_str_out_ret, false, _rawallocator);
				}
				default:
					return YBWLIB2_EXCEPTION_CREATE_UNEXPECTED_EXCEPTION_EXCEPTION();
				}
			}
		};
		using vec_element_t = ::std::vector<element_t, allocator_rawallocator_t<element_t>>;
		objholder_rawallocator_t<vec_element_t> objholder_vec_element;
	};

	void YBWLIB2_CALLTYPE UserInterface_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE UserInterface_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE UserInterface_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE UserInterface_RealUnInitModuleLocal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_B0C4C67D_ECAF_416E_87D6_C710651BDB04
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_B0C4C67D_ECAF_416E_87D6_C710651BDB04
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_9F76487C_A292_4CF5_B1D1_20D77EF404DF
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_9F76487C_A292_4CF5_B1D1_20D77EF404DF
#endif
