#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_03ABA3CE_3F93_404D_A92B_47E840F4FC4B
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_11C7E528_BB34_4934_BB9B_DA0A2B03C1C0
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_7787292D_B637_4957_A139_FECB77AA7241
#define _INCLUDE_GUARD_7787292D_B637_4957_A139_FECB77AA7241

#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <mutex>
#include <minwindef.h>
#include "../Exception/ExceptionLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"
#include "../Common/Common.h"
#include "../Common/CommonSTLHelper.h"
#include "../Common/CommonWindows.h"
#include "../Common/CommonSTLHelperWindows.h"

namespace YBWLib2 {
	class IUnsupportedTargetWin32ArchitectureException;
	class UnsupportedTargetWin32ArchitectureException;
	struct Win32DebuggingTargetAddressDiff;
	struct hash_Win32DebuggingTargetAddressDiff_t;
	struct Win32DebuggingTargetAddress;
	struct hash_Win32DebuggingTargetAddress_t;

	enum class Win32Architecture {
		Win32Architecture_Invalid = 0,
		Win32Architecture_x86,
		Win32Architecture_x64
	};

	/// <summary>The Win32 processor architecture of the target process is not supported.</summary>
	class IUnsupportedTargetWin32ArchitectureException : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IUnsupportedTargetWin32ArchitectureException, YBWLIB2_API, "3fc5a1e6-8a24-4b8d-b51e-33bc22b8e980");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IUnsupportedTargetWin32ArchitectureException);
		inline virtual ~IUnsupportedTargetWin32ArchitectureException() = default;
		/// <summary>Gets the image file machine word that represents the native architecture.</summary>
		/// <returns>Returns the image file machine word that represents the native architecture.</returns>
		virtual USHORT GetNativeArchitectureImageFileMachineWord() const noexcept = 0;
		/// <summary>Gets the image file machine word that represents the architecture of the current process.</summary>
		/// <returns>Returns the image file machine word that represents the architecture of the current process.</returns>
		virtual USHORT GetCurrentProcessArchitectureImageFileMachineWord() const noexcept = 0;
		/// <summary>Gets the image file machine word that represents the architecture of the target process.</summary>
		/// <returns>Returns the image file machine word that represents the architecture of the target process.</returns>
		virtual USHORT GetTargetProcessArchitectureImageFileMachineWord() const noexcept = 0;
	};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4250)
#endif
	/// <summary>
	/// A default implementation of <c>IUnsupportedTargetWin32ArchitectureException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IUnsupportedTargetWin32ArchitectureException</c>.
	/// </summary>
	class UnsupportedTargetWin32ArchitectureException
		: public virtual Exception,
		public virtual IUnsupportedTargetWin32ArchitectureException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(UnsupportedTargetWin32ArchitectureException, , "bde4d166-b08d-4d0b-bee3-e20c98401c3a");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(UnsupportedTargetWin32ArchitectureException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>UnsupportedTargetWin32ArchitectureException</c> object.</summary>
		/// <param name="_file">
		/// Pointer to the <c>IFile</c> object related to the exception.
		/// The constructed object increments and keeps one reference count of the <c>IFile</c> object.
		/// </param>
		inline UnsupportedTargetWin32ArchitectureException(USHORT _machine_native, USHORT _machine_process_current, USHORT _machine_process_target) noexcept
			: machine_native(_machine_native),
			machine_process_current(_machine_process_current),
			machine_process_target(_machine_process_target) {}
		inline virtual ~UnsupportedTargetWin32ArchitectureException() = default;
		/// <summary>
		/// Gets a human-readable description for this exception.
		/// The underlying cause is not included.
		/// <c>GetDescriptionTotal</c> normally calls this member function.
		/// </summary>
		/// <param name="description_ret">
		/// Pointer to a pointer variable that receives a pointer to the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*description_ret</c> will be set to the description string for this exception.
		/// The object on which this function is called does not own the buffer pointed to by the new <c>*description_ret</c> after a successful call.
		/// The caller is responsible for freeing the memory pointed to by <c>*description_ret</c>.
		/// The memory will be allocated using <c>ExceptionAllocateMemory</c>.
		/// Any value originally in <c>*description_ret</c> will be discarded (without freeing the memory pointed to by it, if any).
		/// If there wasn't a human-readable description available for this exception, <c>*description_ret</c> will be set to an empty pointer.
		/// </param>
		/// <param name="size_description_ret">
		/// Pointer to a variable that receives the size (in <c>char</c>s) of the description string, in UTF-8, for this exception.
		/// After successfully returning from this member function, <c>*size_description_ret</c> will be set to the size (in <c>char</c>s) of the description string for this exception.
		/// Any value originally in <c>*size_description_ret</c> will be discarded.
		/// If there wasn't a human-readable description available for this exception, <c>*size_description_ret</c> will be set to <c>0</c>.
		/// </param>
		/// <param name="is_successful_ret">
		/// Optional pointer to a variable that receives whether the call is successful.
		/// If this pointer is supplied, <c>*is_successful_ret</c> will be set to <c>true</c> if the call succeeds, and <c>false</c> otherwise.
		/// Any value originally in <c>*is_successful_ret</c> will be discarded.
		/// If this pointer is empty, it will be ignored by this function.
		/// </param>
		/// <returns>
		/// If the call is successful, The pointer <c>this</c> is returned.
		/// Otherwise, the function becomes responsible for destructing and freeing the object on which the function is called itself,
		/// and returns a pointer to a newly-created exception object (which has a base class of <c>IDoubleExceptionException</c>) that represents the failure.
		/// Either way, the caller should stop managing the object using the pointer on which this function is called, and start managing the object pointed to by the returned pointer.
		/// </returns>
		[[nodiscard]] virtual IException* GetDescriptionSingleLevel(char** description_ret, size_t* size_description_ret, bool* is_successful_ret = nullptr) noexcept override;
		/// <summary>Gets the image file machine word that represents the native architecture.</summary>
		/// <returns>Returns the image file machine word that represents the native architecture.</returns>
		inline virtual USHORT GetNativeArchitectureImageFileMachineWord() const noexcept override { return this->machine_native; }
		/// <summary>Gets the image file machine word that represents the architecture of the current process.</summary>
		/// <returns>Returns the image file machine word that represents the architecture of the current process.</returns>
		inline virtual USHORT GetCurrentProcessArchitectureImageFileMachineWord() const noexcept override { return this->machine_process_current; }
		/// <summary>Gets the image file machine word that represents the architecture of the target process.</summary>
		/// <returns>Returns the image file machine word that represents the architecture of the target process.</returns>
		inline virtual USHORT GetTargetProcessArchitectureImageFileMachineWord() const noexcept override { return this->machine_process_target; }
	protected:
		USHORT machine_native = IMAGE_FILE_MACHINE_UNKNOWN;
		USHORT machine_process_current = IMAGE_FILE_MACHINE_UNKNOWN;
		USHORT machine_process_target = IMAGE_FILE_MACHINE_UNKNOWN;
	};
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	extern YBWLIB2_API HMODULE hmod_kernel32;
	extern YBWLIB2_API BOOL(WINAPI* fnptr_IsWow64Process)(_In_ HANDLE hProcess, _Out_ PBOOL Wow64Process);
	extern YBWLIB2_API BOOL(WINAPI* fnptr_IsWow64Process2)(_In_ HANDLE hProcess, _Out_ USHORT* pProcessMachine, _Out_opt_ USHORT* pNativeMachine);
	extern YBWLIB2_API rawallocator_t* rawallocator_virtual_Win32;

	struct Win32DebuggingTargetAddressDiff final {
		friend struct Win32DebuggingTargetAddress;
		static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");
		struct from_min_t {};
		struct from_max_t {};
		struct from_unsigned_int_t {};
		struct from_signed_int_t {};
		static constexpr from_min_t from_min {};
		static constexpr from_max_t from_max {};
		static constexpr from_unsigned_int_t from_unsigned_int {};
		static constexpr from_signed_int_t from_signed_int {};
		/// <summary>
		/// Constructs a <c>Win32DebuggingTargetAddressDiff</c> object.
		/// The constructed object represents a target address difference of <c>0</c>.
		/// </summary>
		explicit Win32DebuggingTargetAddressDiff(Win32Architecture _architecture) noexcept(false);
		/// <summary>Constructs a <c>Win32DebuggingTargetAddressDiff</c> object that represents the negative address difference with maximal magnitude in the specified architecture.</summary>
		inline Win32DebuggingTargetAddressDiff(Win32Architecture _architecture, from_min_t) noexcept(false) : Win32DebuggingTargetAddressDiff(_architecture) {
			this->SetMin();
		}
		/// <summary>Constructs a <c>Win32DebuggingTargetAddressDiff</c> object that represents the positive address difference with maximal magnitude in the specified architecture.</summary>
		inline Win32DebuggingTargetAddressDiff(Win32Architecture _architecture, from_max_t) noexcept(false) : Win32DebuggingTargetAddressDiff(_architecture) {
			this->SetMax();
		}
		/// <summary>Constructs a <c>Win32DebuggingTargetAddressDiff</c> object that represents the unsigned integer in the specified buffer.</summary>
		/// <param name="buf_uint">
		/// An unsigned integer buffer that specifies the value.
		/// The value must be stored in machine byte order of the CURRENT process.
		/// If the value is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_uint">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_uint</c>.</param>
		inline Win32DebuggingTargetAddressDiff(Win32Architecture _architecture, from_unsigned_int_t, const void* buf_uint, size_t size_buf_uint) noexcept(false) : Win32DebuggingTargetAddressDiff(_architecture) {
			this->SetUint(buf_uint, size_buf_uint);
		}
		/// <summary>Constructs a <c>Win32DebuggingTargetAddressDiff</c> object that represents the signed integer in the specified buffer.</summary>
		/// <param name="buf_sint">
		/// A signed integer buffer that specifies the value.
		/// The value must be stored in machine byte order of the CURRENT process.
		/// If the value has a magnitude that's too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_sint">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_sint</c>.</param>
		inline Win32DebuggingTargetAddressDiff(Win32Architecture _architecture, from_signed_int_t, const void* buf_sint, size_t size_buf_sint) noexcept(false) : Win32DebuggingTargetAddressDiff(_architecture) {
			this->SetSint(buf_sint, size_buf_sint);
		}
		/// <summary>Constructs a <c>Win32DebuggingTargetAddressDiff</c> object that represents the specified integer.</summary>
		template <typename _Int_Ty>
		inline Win32DebuggingTargetAddressDiff(Win32Architecture _architecture, _Int_Ty value) noexcept(false) : Win32DebuggingTargetAddressDiff(_architecture) {
			this->SetInt(value);
		}
		Win32DebuggingTargetAddressDiff(const Win32DebuggingTargetAddressDiff& x) noexcept(false);
		Win32DebuggingTargetAddressDiff(Win32DebuggingTargetAddressDiff&& x) noexcept(false);
		~Win32DebuggingTargetAddressDiff();
		Win32DebuggingTargetAddressDiff& operator=(const Win32DebuggingTargetAddressDiff& x) noexcept(false);
		Win32DebuggingTargetAddressDiff& operator=(Win32DebuggingTargetAddressDiff&& x) noexcept(false);
		bool operator==(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		inline bool operator!=(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) { return !this->operator==(r); }
		bool operator<(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		inline bool operator<=(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) { return !r.operator<(*this); }
		inline bool operator>(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) { return r.operator<(*this); }
		inline bool operator>=(const Win32DebuggingTargetAddressDiff& r) const noexcept(false) { return !this->operator<(r); }
		Win32DebuggingTargetAddressDiff operator+() const noexcept(false);
		Win32DebuggingTargetAddressDiff operator-() const noexcept(false);
		Win32DebuggingTargetAddressDiff operator+(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		Win32DebuggingTargetAddressDiff operator-(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		Win32DebuggingTargetAddressDiff operator*(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		Win32DebuggingTargetAddressDiff operator/(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		Win32DebuggingTargetAddressDiff operator%(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		Win32DebuggingTargetAddressDiff operator~() const noexcept(false);
		Win32DebuggingTargetAddressDiff operator&(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		Win32DebuggingTargetAddressDiff operator|(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		Win32DebuggingTargetAddressDiff operator^(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		Win32DebuggingTargetAddressDiff operator<<(uint8_t r) const noexcept(false);
		Win32DebuggingTargetAddressDiff operator>>(uint8_t r) const noexcept(false);
		inline Win32DebuggingTargetAddressDiff& operator++() noexcept(false) {
			return *this += Win32DebuggingTargetAddressDiff(this->architecture, 1);
		}
		inline Win32DebuggingTargetAddressDiff& operator--() noexcept(false) {
			return *this -= Win32DebuggingTargetAddressDiff(this->architecture, 1);
		}
		inline Win32DebuggingTargetAddressDiff operator++(int) noexcept(false) {
			Win32DebuggingTargetAddressDiff ret(*this);
			*this += Win32DebuggingTargetAddressDiff(this->architecture, 1);
			return ret;
		}
		inline Win32DebuggingTargetAddressDiff operator--(int) noexcept(false) {
			Win32DebuggingTargetAddressDiff ret(*this);
			*this -= Win32DebuggingTargetAddressDiff(this->architecture, 1);
			return ret;
		}
		inline Win32DebuggingTargetAddressDiff& operator+=(const Win32DebuggingTargetAddressDiff& r) noexcept(false) { return *this = *this + r; }
		inline Win32DebuggingTargetAddressDiff& operator-=(const Win32DebuggingTargetAddressDiff& r) noexcept(false) { return *this = *this - r; }
		inline Win32DebuggingTargetAddressDiff& operator*=(const Win32DebuggingTargetAddressDiff& r) noexcept(false) { return *this = *this * r; }
		inline Win32DebuggingTargetAddressDiff& operator/=(const Win32DebuggingTargetAddressDiff& r) noexcept(false) { return *this = *this / r; }
		inline Win32DebuggingTargetAddressDiff& operator%=(const Win32DebuggingTargetAddressDiff& r) noexcept(false) { return *this = *this % r; }
		inline Win32DebuggingTargetAddressDiff& operator&=(const Win32DebuggingTargetAddressDiff& r) noexcept(false) { return *this = *this & r; }
		inline Win32DebuggingTargetAddressDiff& operator|=(const Win32DebuggingTargetAddressDiff& r) noexcept(false) { return *this = *this | r; }
		inline Win32DebuggingTargetAddressDiff& operator^=(const Win32DebuggingTargetAddressDiff& r) noexcept(false) { return *this = *this ^ r; }
		inline Win32DebuggingTargetAddressDiff& operator<<=(uint8_t r) noexcept(false) { return *this = *this << r; }
		inline Win32DebuggingTargetAddressDiff& operator>>=(uint8_t r) noexcept(false) { return *this = *this >> r; }
		inline Win32Architecture GetWin32Architecture() const noexcept(false) { return this->architecture; }
		bool IsEmpty() const noexcept(false);
		bool IsMin() const noexcept(false);
		bool IsMax() const noexcept(false);
		size_t Hash() const noexcept(false);
		inline explicit operator bool() const noexcept(false) { return !this->IsEmpty(); }
		/// <summary>Gets the value as an unsigned integer and writes it into the specified buffer.</summary>
		/// <param name="buf_uint_to">
		/// An unsigned integer buffer that receives the value.
		/// The value must be stored in machine byte order of the CURRENT process.
		/// </param>
		/// <param name="size_buf_uint_to">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_uint_to</c>.
		/// If the buffer is insufficient to contain the value, the function call will fail.
		/// </param>
		void GetUint(void* buf_uint_to, size_t size_buf_uint_to) const noexcept(false);
		/// <summary>Gets the value as a signed integer and writes it into the specified buffer.</summary>
		/// <param name="buf_sint_to">
		/// A signed integer buffer that receives the value.
		/// The value must be stored in machine byte order of the CURRENT process.
		/// </param>
		/// <param name="size_buf_sint_to">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_sint_to</c>.
		/// If the buffer is insufficient to contain the value, the function call will fail.
		/// </param>
		void GetSint(void* buf_sint_to, size_t size_buf_sint_to) const noexcept(false);
		/// <summary>Gets the value as an integer.</summary>
		template <typename _Int_Ty>
		inline void GetInt(_Int_Ty& value) const noexcept(false) {
			static_assert(::std::is_object_v<_Int_Ty>, "The specified integer type is not an object type.");
			static_assert(::std::is_integral_v<_Int_Ty>, "The specified integer type is not integral.");
			if constexpr (::std::is_unsigned_v<_Int_Ty>) {
				this->GetUint(&value, sizeof(value));
			} else if constexpr (::std::is_signed_v<_Int_Ty>) {
				this->GetSint(&value, sizeof(value));
			} else {
				static_assert(false, "The specified integer type is neither unsigned nor signed.");
			}
		}
		void SetEmpty() noexcept(false);
		void SetMin() noexcept(false);
		void SetMax() noexcept(false);
		/// <summary>Sets the value to the unsigned integer in the specified buffer.</summary>
		/// <param name="buf_uint_from">
		/// An unsigned integer buffer that specifies the value.
		/// The value must be stored in machine byte order of the CURRENT process.
		/// If the value is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_uint_from">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_uint_from</c>.</param>
		void SetUint(const void* buf_uint_from, size_t size_buf_uint_from) noexcept(false);
		/// <summary>Sets the value to the signed integer in the specified buffer.</summary>
		/// <param name="buf_sint_from">
		/// A signed integer buffer that specifies the value.
		/// The value must be stored in machine byte order of the CURRENT process.
		/// If the value has a magnitude that's too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_sint_from">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_sint_from</c>.</param>
		void SetSint(const void* buf_sint_from, size_t size_buf_sint_from) noexcept(false);
		/// <summary>Sets the value to the specified integer.</summary>
		template <typename _Int_Ty>
		inline void SetInt(_Int_Ty value) noexcept(false) {
			static_assert(::std::is_object_v<_Int_Ty>, "The specified integer type is not an object type.");
			static_assert(::std::is_integral_v<_Int_Ty>, "The specified integer type is not integral.");
			if constexpr (::std::is_unsigned_v<_Int_Ty>) {
				this->SetUint(&value, sizeof(value));
			} else if constexpr (::std::is_signed_v<_Int_Ty>) {
				this->SetSint(&value, sizeof(value));
			} else {
				static_assert(false, "The specified integer type is neither unsigned nor signed.");
			}
		}
	protected:
		Win32Architecture architecture = Win32Architecture::Win32Architecture_Invalid;
		bool is_negative = false;
		union {
			uint32_t uint32;
			uint64_t uint64;
		};
	};
	static_assert(::std::is_standard_layout_v<Win32DebuggingTargetAddressDiff>, "Win32DebuggingTargetAddressDiff is not standard-layout.");

	template<>
	struct hash<Win32DebuggingTargetAddressDiff> {
		inline size_t operator()(const Win32DebuggingTargetAddressDiff& x) const {
			return x.Hash();
		}
	};

	struct Win32DebuggingTargetAddress final {
		friend struct Win32DebuggingTargetAddressDiff;
		static_assert(sizeof(uint8_t) == 1, "The size of uint8_t is not 1.");
		struct from_min_t {};
		struct from_max_t {};
		struct from_unsigned_int_t {};
		struct from_raw_target_address_t {};
		struct from_raw_current_process_address_t {};
		static constexpr from_min_t from_min {};
		static constexpr from_max_t from_max {};
		static constexpr from_unsigned_int_t from_unsigned_int {};
		static constexpr from_raw_target_address_t from_raw_target_address {};
		static constexpr from_raw_current_process_address_t from_raw_current_process_address {};
		/// <summary>Gets the size of raw target addresses in the specified architecture.</summary>
		static size_t GetRawTargetAddressSize(Win32Architecture architecture) noexcept(false);
		/// <summary>
		/// Constructs a <c>Win32DebuggingTargetAddress</c> object.
		/// The constructed object represents a target address of <c>0</c>.
		/// </summary>
		explicit Win32DebuggingTargetAddress(Win32Architecture _architecture) noexcept(false);
		/// <summary>
		/// Constructs a <c>Win32DebuggingTargetAddress</c> object that represents the lowest address in the specified architecture.
		/// This lowest address value may or may not be valid. It's only guranteed to be representable in the data type.
		/// </summary>
		inline Win32DebuggingTargetAddress(Win32Architecture _architecture, from_min_t) noexcept(false) : Win32DebuggingTargetAddress(_architecture) {
			this->SetMin();
		}
		/// <summary>
		/// Constructs a <c>Win32DebuggingTargetAddress</c> object that represents the highest address in the specified architecture.
		/// This highest address value may or may not be valid. It's only guranteed to be representable in the data type.
		/// </summary>
		inline Win32DebuggingTargetAddress(Win32Architecture _architecture, from_max_t) noexcept(false) : Win32DebuggingTargetAddress(_architecture) {
			this->SetMax();
		}
		/// <summary>Constructs a <c>Win32DebuggingTargetAddress</c> object that represents the unsigned integer in the specified buffer.</summary>
		/// <param name="buf_uint">
		/// An unsigned integer buffer that specifies the value.
		/// The value must be stored in machine byte order of the CURRENT process.
		/// If the value is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_uint">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_uint</c>.</param>
		inline Win32DebuggingTargetAddress(Win32Architecture _architecture, from_unsigned_int_t, const void* buf_uint, size_t size_buf_uint) noexcept(false) : Win32DebuggingTargetAddress(_architecture) {
			this->SetUint(buf_uint, size_buf_uint);
		}
		/// <summary>Constructs a <c>Win32DebuggingTargetAddress</c> object that represents the raw target address in the specified buffer.</summary>
		/// <param name="buf_rawtargetaddress">
		/// A buffer that specifies the raw target address.
		/// The raw target address must be stored in machine byte order of the TARGET process.
		/// </param>
		/// <param name="size_buf_rawtargetaddress">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_rawtargetaddress</c>.
		/// If the size doesn't match the size of the raw target address of the architecture, the function call will fail.
		/// </param>
		inline Win32DebuggingTargetAddress(Win32Architecture _architecture, from_raw_target_address_t, const void* buf_rawtargetaddress, size_t size_buf_rawtargetaddress) noexcept(false) : Win32DebuggingTargetAddress(_architecture) {
			this->SetRawTargetAddress(buf_rawtargetaddress, size_buf_rawtargetaddress);
		}
		/// <summary>
		/// Constructs a <c>Win32DebuggingTargetAddress</c> object that represents the raw address represented by the specified pointer value.
		/// This function is supported only in certain combinations of current process architecture and target process architecture.
		/// </summary>
		/// <param name="rawcurrentprocessaddress">
		/// A pointer value that represents the raw address.
		/// Usually, this pointer cannot be meaningfully dereferenced.
		/// </param>
		inline Win32DebuggingTargetAddress(Win32Architecture _architecture, from_raw_current_process_address_t, const volatile void* rawcurrentprocessaddress) noexcept(false) : Win32DebuggingTargetAddress(_architecture) {
			this->SetRawCurrentProcessAddress(rawcurrentprocessaddress);
		}
		/// <summary>Constructs a <c>Win32DebuggingTargetAddress</c> object that represents the specified unsigned integer.</summary>
		template <typename _Int_Ty>
		inline Win32DebuggingTargetAddress(Win32Architecture _architecture, _Int_Ty value) noexcept(false) : Win32DebuggingTargetAddress(_architecture) {
			this->SetInt(value);
		}
		Win32DebuggingTargetAddress(const Win32DebuggingTargetAddress& x) noexcept(false);
		Win32DebuggingTargetAddress(Win32DebuggingTargetAddress&& x) noexcept(false);
		~Win32DebuggingTargetAddress();
		Win32DebuggingTargetAddress& operator=(const Win32DebuggingTargetAddress& x) noexcept(false);
		Win32DebuggingTargetAddress& operator=(Win32DebuggingTargetAddress&& x) noexcept(false);
		bool operator==(const Win32DebuggingTargetAddress& r) const noexcept(false);
		inline bool operator!=(const Win32DebuggingTargetAddress& r) const noexcept(false) { return !this->operator==(r); }
		bool operator<(const Win32DebuggingTargetAddress& r) const noexcept(false);
		inline bool operator<=(const Win32DebuggingTargetAddress& r) const noexcept(false) { return !r.operator<(*this); }
		inline bool operator>(const Win32DebuggingTargetAddress& r) const noexcept(false) { return r.operator<(*this); }
		inline bool operator>=(const Win32DebuggingTargetAddress& r) const noexcept(false) { return !this->operator<(r); }
		Win32DebuggingTargetAddressDiff operator-(const Win32DebuggingTargetAddress& r) const noexcept(false);
		Win32DebuggingTargetAddress operator+(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		Win32DebuggingTargetAddress operator-(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		Win32DebuggingTargetAddressDiff operator%(const Win32DebuggingTargetAddressDiff& r) const noexcept(false);
		inline Win32DebuggingTargetAddress& operator+=(const Win32DebuggingTargetAddressDiff& r) noexcept(false) { return *this = *this + r; }
		inline Win32DebuggingTargetAddress& operator-=(const Win32DebuggingTargetAddressDiff& r) noexcept(false) { return *this = *this - r; }
		inline Win32Architecture GetWin32Architecture() const noexcept(false) { return this->architecture; }
		bool IsEmpty() const noexcept(false);
		bool IsMin() const noexcept(false);
		bool IsMax() const noexcept(false);
		size_t Hash() const noexcept(false);
		inline explicit operator bool() const noexcept(false) { return !this->IsEmpty(); }
		/// <summary>Gets the value as an unsigned integer and writes it into the specified buffer.</summary>
		/// <param name="buf_uint_to">
		/// An unsigned integer buffer that receives the value.
		/// The value must be stored in machine byte order of the CURRENT process.
		/// </param>
		/// <param name="size_buf_uint_to">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_uint_to</c>.
		/// If the buffer is insufficient to contain the value, the function call will fail.
		/// </param>
		void GetUint(void* buf_uint_to, size_t size_buf_uint_to) const noexcept(false);
		/// <summary>Gets the value as a raw target address and writes it into the specified buffer.</summary>
		/// <param name="buf_rawtargetaddress_to">
		/// A buffer that receives the raw target address.
		/// The raw target address will be stored in machine byte order of the TARGET process.
		/// </param>
		/// <param name="size_buf_rawtargetaddress_to">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_rawtargetaddress_to</c>.
		/// If the size doesn't match the size of the raw target addresses of the architecture, the function call will fail.
		/// </param>
		void GetRawTargetAddress(void* buf_rawtargetaddress_to, size_t size_buf_rawtargetaddress_to) const noexcept(false);
		/// <summary>
		/// Gets the value as a pointer.
		/// This function is supported only in certain combinations of current process architecture and target process architecture.
		/// </summary>
		/// <returns>
		/// A pointer value that represents the raw address.
		/// Usually, this pointer cannot be meaningfully dereferenced.
		/// </returns>
		void* GetRawCurrentProcessAddress() const noexcept(false);
		/// <summary>Gets the value as an integer.</summary>
		template <typename _Int_Ty>
		inline void GetInt(_Int_Ty& value) const noexcept(false) {
			static_assert(::std::is_object_v<_Int_Ty>, "The specified integer type is not an object type.");
			static_assert(::std::is_integral_v<_Int_Ty>, "The specified integer type is not integral.");
			if constexpr (::std::is_unsigned_v<_Int_Ty>) {
				this->GetUint(&value, sizeof(value));
			} else {
				static_assert(false, "The specified integer type is not unsigned.");
			}
		}
		void SetEmpty() noexcept(false);
		void SetMin() noexcept(false);
		void SetMax() noexcept(false);
		/// <summary>Sets the value to the unsigned integer in the specified buffer.</summary>
		/// <param name="buf_uint_from">
		/// An unsigned integer buffer that specifies the value.
		/// The value must be stored in machine byte order of the CURRENT process.
		/// If the value is too large, the function call will fail.
		/// </param>
		/// <param name="size_buf_uint_from">The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_uint_from</c>.</param>
		void SetUint(const void* buf_uint_from, size_t size_buf_uint_from) noexcept(false);
		/// <summary>Sets the value to the raw target address in the specified buffer.</summary>
		/// <param name="buf_rawtargetaddress_from">
		/// A buffer that specifies the raw target address.
		/// The raw target address must be stored in machine byte order of the TARGET process.
		/// </param>
		/// <param name="size_buf_rawtargetaddress_from">
		/// The size (in <c>uint8_t</c>s) of the buffer pointed to by <c>buf_rawtargetaddress_from</c>.
		/// If the size doesn't match the size of the raw target addresses of the architecture, the function call will fail.
		/// </param>
		void SetRawTargetAddress(const void* buf_rawtargetaddress_from, size_t size_buf_rawtargetaddress_from) noexcept(false);
		/// <summary>
		/// Sets the value to the raw address represented by the specified pointer value.
		/// This function is supported only in certain combinations of current process architecture and target process architecture.
		/// </summary>
		/// <param name="rawcurrentprocessaddress">
		/// A pointer value that represents the raw address.
		/// Usually, this pointer cannot be meaningfully dereferenced.
		/// </param>
		void SetRawCurrentProcessAddress(const volatile void* rawcurrentprocessaddress) noexcept(false);
		/// <summary>Sets the value to the specified integer.</summary>
		template <typename _Int_Ty>
		inline void SetInt(_Int_Ty value) noexcept(false) {
			static_assert(::std::is_object_v<_Int_Ty>, "The specified integer type is not an object type.");
			static_assert(::std::is_integral_v<_Int_Ty>, "The specified integer type is not integral.");
			if constexpr (::std::is_unsigned_v<_Int_Ty>) {
				this->SetUint(&value, sizeof(value));
			} else {
				static_assert(false, "The specified integer type is not unsigned.");
			}
		}
	protected:
		Win32Architecture architecture = Win32Architecture::Win32Architecture_Invalid;
		union {
			uint32_t uint32;
			uint64_t uint64;
		};
	};
	static_assert(::std::is_standard_layout_v<Win32DebuggingTargetAddress>, "Win32DebuggingTargetAddress is not standard-layout.");

	inline Win32DebuggingTargetAddress operator+(const Win32DebuggingTargetAddressDiff& l, const Win32DebuggingTargetAddress& r) noexcept(false) { return r + l; }

	template<>
	struct hash<Win32DebuggingTargetAddress> {
		inline size_t operator()(const Win32DebuggingTargetAddress& x) const {
			return x.Hash();
		}
	};

	/// <summary>
	/// Suspends all threads in a process except those specified.
	/// The threads are resumed when the object is destructed.
	/// </summary>
	class Win32DebuggingSuspendThreadsInProcess final {
	public:
		inline Win32DebuggingSuspendThreadsInProcess() noexcept {}
		/// <summary>Constructs a <c>Win32DebuggingSuspendThreadsInProcess</c> object.</summary>
		/// <param name="_win32handleholder_process">A handle to the target process, in which the threads are to be suspended.</param>
		/// <param name="_vec_threadid_exempted">
		/// A vector of thread IDs of threads that should be exempted from being suspended.
		/// The current thread is automatically exempted even if it's not included in this vector.
		/// </param>
		/// <param name="_vec_range_targetaddress_code_lock">
		/// The locked code target address range vector.
		/// Each element in the vector represents a range [first, second) in the virtual memory space of the target.
		/// The program counters of the threads to be suspended will be checked against the ranges.
		/// If the program counter of one of the threads happens to be in one of the ranges,
		/// the thread will be resumed and suspended again until it's program counter is no longer in the ranges.
		/// Overlapping ranges will be automatically merged.
		/// </param>
		Win32DebuggingSuspendThreadsInProcess(
			const Win32HandleHolder& _win32handleholder_process = Win32HandleHolder(Win32HandleHolder::view_handle, GetCurrentProcess()),
			const ::std::unordered_set<DWORD>& _vec_threadid_exempted = ::std::unordered_set<DWORD>(),
			const ::std::vector<::std::pair<Win32DebuggingTargetAddress, Win32DebuggingTargetAddress>> _vec_range_targetaddress_code_lock = ::std::vector<::std::pair<Win32DebuggingTargetAddress, Win32DebuggingTargetAddress>>()
		) noexcept(false);
		Win32DebuggingSuspendThreadsInProcess(const Win32DebuggingSuspendThreadsInProcess&) = delete;
		Win32DebuggingSuspendThreadsInProcess(Win32DebuggingSuspendThreadsInProcess&& x) noexcept(false);
		inline ~Win32DebuggingSuspendThreadsInProcess() {
			if (this->win32handleholder_process) this->ResumeThreads();
		}
		Win32DebuggingSuspendThreadsInProcess& operator=(const Win32DebuggingSuspendThreadsInProcess&) = delete;
		Win32DebuggingSuspendThreadsInProcess& operator=(Win32DebuggingSuspendThreadsInProcess&& x) noexcept(false);
		inline bool GetHasSuspended() const noexcept { return this->has_suspended; }
		/// <summary>Adds a thread that should be exempted from being suspended.</summary>
		/// <param name="threadid">The thread ID of the thread.</param>
		void AddExemptedThread(DWORD threadid) noexcept(false);
		/// <summary>Removes a thread from those that should be exempted from being suspended.</summary>
		/// <param name="threadid">The thread ID of the thread.</param>
		void RemoveExemptedThread(DWORD threadid) noexcept(false);
		void SuspendThreads() noexcept(false);
		void ResumeThreads() noexcept;
		void UpdateThreadSuspendResume() noexcept(false);
	protected:
		using set_threadid_exempted_t = ::std::unordered_set<DWORD>;
		using map_targetaddress_code_lock_t = ::std::map<Win32DebuggingTargetAddress, bool>;
		using list_thread_suspended_t = ::std::list<::std::pair<Win32HandleHolder, Win32DebuggingTargetAddress>>;
		static constexpr DWORD timeduration_sleep_retry_suspend = 100;
		bool has_suspended = false;
		Win32HandleHolder win32handleholder_process;
		Win32Architecture architecture = Win32Architecture::Win32Architecture_Invalid;
		set_threadid_exempted_t set_threadid_exempted;
		map_targetaddress_code_lock_t map_targetaddress_code_lock;
		list_thread_suspended_t list_thread_suspended;
	};

	class IWin32DebuggingTargetMemoryRegionInfo : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IWin32DebuggingTargetMemoryRegionInfo, YBWLIB2_API, "6983c737-136b-4b60-a3dd-4500e18a0c4b");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IWin32DebuggingTargetMemoryRegionInfo);
		inline virtual ~IWin32DebuggingTargetMemoryRegionInfo() = default;
		virtual Win32Architecture GetWin32Architecture() const noexcept = 0;
		/// <summary>Gets the base address of the memory region.</summary>
		/// <param name="targetaddress_ret">A pointer to a pointer variable that receives a pointer to the base address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetBaseAddress(const Win32DebuggingTargetAddress** targetaddress_ret) const noexcept = 0;
		/// <summary>Gets the allocation base address of the memory region.</summary>
		/// <param name="targetaddress_ret">A pointer to a pointer variable that receives a pointer to the allocation base address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetAllocationBaseAddress(const Win32DebuggingTargetAddress** targetaddress_ret) const noexcept = 0;
		/// <summary>Gets the size of the memory region.</summary>
		/// <param name="size_ret">A pointer to a pointer variable that receives a pointer to the memory region size.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetSize(const Win32DebuggingTargetAddressDiff** size_ret) const noexcept = 0;
		/// <summary>Gets the memory protection of the memory region.</summary>
		/// <param name="protect_ret">A pointer to a variable that receives the memory protection.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetProtect(DWORD* protect_ret) const noexcept = 0;
		/// <summary>Gets the allocation memory protection of the memory region.</summary>
		/// <param name="protect_ret">A pointer to a variable that receives the allocation memory protection.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetAllocationProtect(DWORD* protect_ret) const noexcept = 0;
		/// <summary>Gets the state of the memory region.</summary>
		/// <param name="state_ret">A pointer to a variable that receives the state.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetState(DWORD* state_ret) const noexcept = 0;
		/// <summary>Gets the type of the memory region.</summary>
		/// <param name="type_ret">A pointer to a variable that receives the type.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetType(DWORD* type_ret) const noexcept = 0;
		/// <summary>
		/// Sets the memory region base address that's represented by this object.
		/// This does NOT necessarily change the memory region in the target process.
		/// </summary>
		/// <param name="_targetaddress">A pointer to the base address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetBaseAddress(const Win32DebuggingTargetAddress* _targetaddress) noexcept = 0;
		/// <summary>
		/// Sets the memory region allocation base address that's represented by this object.
		/// This does NOT necessarily change the memory region in the target process.
		/// </summary>
		/// <param name="_targetaddress">A pointer to the allocation base address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetAllocationBaseAddress(const Win32DebuggingTargetAddress* _targetaddress) noexcept = 0;
		/// <summary>
		/// Sets the memory region size that's represented by this object.
		/// This does NOT necessarily change the memory region in the target process.
		/// </summary>
		/// <param name="_size">A pointer to the memory region size.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetSize(const Win32DebuggingTargetAddressDiff* _size) noexcept = 0;
		/// <summary>
		/// Sets the memory region memory protection that's represented by this object.
		/// This does NOT necessarily change the memory region in the target process.
		/// </summary>
		/// <param name="_protect">The memory protection.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetProtect(DWORD _protect) noexcept = 0;
		/// <summary>
		/// Sets the memory region allocation memory protection that's represented by this object.
		/// This does NOT necessarily change the memory region in the target process.
		/// </summary>
		/// <param name="_protect">The allocation memory protection.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetAllocationProtect(DWORD _protect) noexcept = 0;
		/// <summary>
		/// Sets the memory region state that's represented by this object.
		/// This does NOT necessarily change the memory region in the target process.
		/// </summary>
		/// <param name="_state">The state.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetState(DWORD _state) noexcept = 0;
		/// <summary>
		/// Sets the memory region type that's represented by this object.
		/// This does NOT necessarily change the memory region in the target process.
		/// </summary>
		/// <param name="_type">The type.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetType(DWORD _type) noexcept = 0;
		/// <summary>Gets the base address of the memory region.</summary>
		/// <returns>Pointer to the base address.</returns>
		[[nodiscard]] inline const Win32DebuggingTargetAddress* GetBaseAddress() const noexcept(false) {
			const Win32DebuggingTargetAddress* targetaddress = nullptr;
			IException* err = this->GetBaseAddress(&targetaddress);
			if (err) throw(err);
			return targetaddress;
		}
		/// <summary>Gets the allocation base address of the memory region.</summary>
		/// <returns>Pointer to the allocation base address.</returns>
		[[nodiscard]] inline const Win32DebuggingTargetAddress* GetAllocationBaseAddress() const noexcept(false) {
			const Win32DebuggingTargetAddress* targetaddress = nullptr;
			IException* err = this->GetAllocationBaseAddress(&targetaddress);
			if (err) throw(err);
			return targetaddress;
		}
		/// <summary>Gets the size of the memory region.</summary>
		/// <returns>Pointer to the memory region size.</returns>
		[[nodiscard]] inline const Win32DebuggingTargetAddressDiff* GetSize() const noexcept(false) {
			const Win32DebuggingTargetAddressDiff* size = nullptr;
			IException* err = this->GetSize(&size);
			if (err) throw(err);
			return size;
		}
		/// <summary>Gets the memory protection of the memory region.</summary>
		/// <returns>The memory protection.</returns>
		[[nodiscard]] inline DWORD GetProtect() const noexcept(false) {
			DWORD protect = 0;
			IException* err = this->GetProtect(&protect);
			if (err) throw(err);
			return protect;
		}
		/// <summary>Gets the allocation memory protection of the memory region.</summary>
		/// <returns>The allocation memory protection.</returns>
		[[nodiscard]] inline DWORD GetAllocationProtect() const noexcept(false) {
			DWORD protect = 0;
			IException* err = this->GetAllocationProtect(&protect);
			if (err) throw(err);
			return protect;
		}
		/// <summary>Gets the state of the memory region.</summary>
		/// <param name="state_ret">A pointer to a variable that receives </param>
		/// <returns>The state.</returns>
		[[nodiscard]] inline DWORD GetState() const noexcept(false) {
			DWORD state = 0;
			IException* err = this->GetState(&state);
			if (err) throw(err);
			return state;
		}
		/// <summary>Gets the type of the memory region.</summary>
		/// <param name="type_ret">A pointer to a variable that receives </param>
		/// <returns>The type.</returns>
		[[nodiscard]] inline DWORD GetType() const noexcept(false) {
			DWORD type = 0;
			IException* err = this->GetType(&type);
			if (err) throw(err);
			return type;
		}
	};

	class Win32DebuggingTargetMemoryRegionInfo : public virtual IWin32DebuggingTargetMemoryRegionInfo {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(Win32DebuggingTargetMemoryRegionInfo, , "ed262840-9a56-4aca-9ca3-b401fbe965d7");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(Win32DebuggingTargetMemoryRegionInfo);
		template<typename _Memory_Basic_Information_Ty>
		inline static Win32DebuggingTargetMemoryRegionInfo FromMemoryBasicInformation(Win32Architecture architecture, const _Memory_Basic_Information_Ty& memory_basic_information) {
			Win32DebuggingTargetAddress addr_base(architecture);
			Win32DebuggingTargetAddress addr_base_alloc(architecture);
			if constexpr (::std::is_integral_v<decltype(memory_basic_information.BaseAddress)> && ::std::is_unsigned_v<decltype(memory_basic_information.BaseAddress)>) {
				addr_base = Win32DebuggingTargetAddress(architecture, memory_basic_information.BaseAddress);
			} else if constexpr (::std::is_pointer_v<decltype(memory_basic_information.BaseAddress)>) {
				uintptr_t uintptr_addr_base = reinterpret_cast<uintptr_t>(memory_basic_information.BaseAddress);
				addr_base = Win32DebuggingTargetAddress(architecture, Win32DebuggingTargetAddress::from_unsigned_int, &uintptr_addr_base, sizeof(uintptr_t));
			} else {
				static_assert(false, "The type of the BaseAddress field of the memory basic information is neither an unsigned integral type nor a pointer type.");
			}
			if constexpr (::std::is_integral_v<decltype(memory_basic_information.AllocationBase)> && ::std::is_unsigned_v<decltype(memory_basic_information.AllocationBase)>) {
				addr_base_alloc = Win32DebuggingTargetAddress(architecture, memory_basic_information.AllocationBase);
			} else if constexpr (::std::is_pointer_v<decltype(memory_basic_information.AllocationBase)>) {
				uintptr_t uintptr_addr_base_alloc = reinterpret_cast<uintptr_t>(memory_basic_information.AllocationBase);
				addr_base_alloc = Win32DebuggingTargetAddress(architecture, Win32DebuggingTargetAddress::from_unsigned_int, &uintptr_addr_base_alloc, sizeof(uintptr_t));
			} else {
				static_assert(false, "The type of the AllocationBase field of the memory basic information is neither an unsigned integral type nor a pointer type.");
			}
			return Win32DebuggingTargetMemoryRegionInfo(
				architecture,
				addr_base,
				addr_base_alloc,
				Win32DebuggingTargetAddressDiff(architecture, memory_basic_information.RegionSize),
				memory_basic_information.Protect,
				memory_basic_information.AllocationProtect,
				memory_basic_information.State,
				memory_basic_information.Type
			);
		}
		explicit Win32DebuggingTargetMemoryRegionInfo(Win32Architecture _architecture) noexcept(false);
		Win32DebuggingTargetMemoryRegionInfo(
			Win32Architecture _architecture,
			const Win32DebuggingTargetAddress& _addr_base,
			const Win32DebuggingTargetAddress& _addr_base_alloc,
			const Win32DebuggingTargetAddressDiff& _size,
			DWORD _protect,
			DWORD _protect_alloc,
			DWORD _state,
			DWORD _type
		) noexcept(false);
		Win32DebuggingTargetMemoryRegionInfo(const Win32DebuggingTargetMemoryRegionInfo& x) noexcept(false);
		Win32DebuggingTargetMemoryRegionInfo(Win32DebuggingTargetMemoryRegionInfo&& x) noexcept(false);
		virtual ~Win32DebuggingTargetMemoryRegionInfo();
		Win32DebuggingTargetMemoryRegionInfo& operator=(const Win32DebuggingTargetMemoryRegionInfo& x) noexcept(false);
		Win32DebuggingTargetMemoryRegionInfo& operator=(Win32DebuggingTargetMemoryRegionInfo&& x) noexcept(false);
		inline virtual Win32Architecture GetWin32Architecture() const noexcept override { return this->architecture; }
		/// <summary>Gets the base address of the memory region.</summary>
		/// <param name="targetaddress_ret">A pointer to a pointer variable that receives a pointer to the base address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetBaseAddress(const Win32DebuggingTargetAddress** targetaddress_ret) const noexcept override;
		/// <summary>Gets the allocation base address of the memory region.</summary>
		/// <param name="targetaddress_ret">A pointer to a pointer variable that receives a pointer to the allocation base address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetAllocationBaseAddress(const Win32DebuggingTargetAddress** targetaddress_ret) const noexcept override;
		/// <summary>Gets the size of the memory region.</summary>
		/// <param name="size_ret">A pointer to a pointer variable that receives a pointer to the memory region size.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetSize(const Win32DebuggingTargetAddressDiff** size_ret) const noexcept override;
		/// <summary>Gets the memory protection of the memory region.</summary>
		/// <param name="protect_ret">A pointer to a variable that receives the memory protection.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetProtect(DWORD* protect_ret) const noexcept override;
		/// <summary>Gets the allocation memory protection of the memory region.</summary>
		/// <param name="protect_ret">A pointer to a variable that receives the allocation memory protection.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetAllocationProtect(DWORD* protect_ret) const noexcept override;
		/// <summary>Gets the state of the memory region.</summary>
		/// <param name="state_ret">A pointer to a variable that receives the state.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetState(DWORD* state_ret) const noexcept override;
		/// <summary>Gets the type of the memory region.</summary>
		/// <param name="type_ret">A pointer to a variable that receives the type.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetType(DWORD* type_ret) const noexcept override;
		/// <summary>
		/// Sets the memory region base address that's represented by this object.
		/// This does NOT change the memory region in the target process.
		/// </summary>
		/// <param name="targetaddress">A pointer to the base address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetBaseAddress(const Win32DebuggingTargetAddress* _targetaddress) noexcept override;
		/// <summary>
		/// Sets the memory region allocation base address that's represented by this object.
		/// This does NOT change the memory region in the target process.
		/// </summary>
		/// <param name="targetaddress">A pointer to the allocation base address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetAllocationBaseAddress(const Win32DebuggingTargetAddress* _targetaddress) noexcept override;
		/// <summary>
		/// Sets the memory region size that's represented by this object.
		/// This does NOT change the memory region in the target process.
		/// </summary>
		/// <param name="size">A pointer to the memory region size.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetSize(const Win32DebuggingTargetAddressDiff* _size) noexcept override;
		/// <summary>
		/// Sets the memory region memory protection that's represented by this object.
		/// This does NOT change the memory region in the target process.
		/// </summary>
		/// <param name="protect">The memory protection.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetProtect(DWORD _protect) noexcept override;
		/// <summary>
		/// Sets the memory region allocation memory protection that's represented by this object.
		/// This does NOT change the memory region in the target process.
		/// </summary>
		/// <param name="protect">The allocation memory protection.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetAllocationProtect(DWORD _protect) noexcept override;
		/// <summary>
		/// Sets the memory region state that's represented by this object.
		/// This does NOT change the memory region in the target process.
		/// </summary>
		/// <param name="state">The state.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetState(DWORD _state) noexcept override;
		/// <summary>
		/// Sets the memory region type that's represented by this object.
		/// This does NOT change the memory region in the target process.
		/// </summary>
		/// <param name="type">The type.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetType(DWORD _type) noexcept override;
	protected:
		Win32Architecture architecture = Win32Architecture::Win32Architecture_Invalid;
		Win32DebuggingTargetAddress addr_base;
		Win32DebuggingTargetAddress addr_base_alloc;
		Win32DebuggingTargetAddressDiff size;
		DWORD protect = 0;
		DWORD protect_alloc = 0;
		DWORD state = 0;
		DWORD type = 0;
	};

	class IWin32DebuggingTargetExecutableModuleInfo : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IWin32DebuggingTargetExecutableModuleInfo, YBWLIB2_API, "4f3bbd6c-b994-4b48-a5e8-9fdd11fe646e");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IWin32DebuggingTargetExecutableModuleInfo);
		inline virtual ~IWin32DebuggingTargetExecutableModuleInfo() = default;
		virtual Win32Architecture GetWin32Architecture() const noexcept = 0;
		/// <summary>Gets the base address of the executable module in the memory.</summary>
		/// <param name="targetaddress_ret">A pointer to a pointer variable that receives a pointer to the base address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetBaseAddress(const Win32DebuggingTargetAddress** targetaddress_ret) const noexcept = 0;
		/// <summary>Gets the size of the executable module in the memory.</summary>
		/// <param name="size_ret">A pointer to a pointer variable that receives a pointer to the executable module size.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetSize(const Win32DebuggingTargetAddressDiff** size_ret) const noexcept = 0;
		/// <summary>Gets the name of the module.</summary>
		/// <param name="name_module_ret">A pointer to a pointer variable that receives a pointer to the module name string.</param>
		/// <param name="size_name_module_ret">A pointer to a variable that receives the size (in <c>char</c>s) of the module name string, in UTF-8.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetModuleName(const char** name_module_ret, size_t* size_name_module_ret) const noexcept = 0;
		/// <summary>Gets the path of the module.</summary>
		/// <param name="path_module_ret">A pointer to a pointer variable that receives a pointer to the module path string.</param>
		/// <param name="size_path_module_ret">A pointer to a variable that receives the size (in <c>char</c>s) of the module path string, in UTF-8.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetModulePath(const char** path_module_ret, size_t* size_path_module_ret) const noexcept = 0;
		/// <summary>
		/// Sets the executable module base address in the memory that's represented by this object.
		/// This does NOT necessarily change the executable module in the target process.
		/// </summary>
		/// <param name="_targetaddress">A pointer to the base address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetBaseAddress(const Win32DebuggingTargetAddress* _targetaddress) noexcept = 0;
		/// <summary>
		/// Sets the executable module size in the memory that's represented by this object.
		/// This does NOT necessarily change the executable module in the target process.
		/// </summary>
		/// <param name="_size">A pointer to the executable module size.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetSize(const Win32DebuggingTargetAddressDiff* _size) noexcept = 0;
		/// <summary>
		/// Sets the name of the module.
		/// This does NOT necessarily change the executable module in the target process.
		/// </summary>
		/// <param name="_name_module">A pointer to the module name string.</param>
		/// <param name="_size_name_module">The size (in <c>char</c>s) of the module name string, in UTF-8.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetModuleName(const char* _name_module, size_t _size_name_module) noexcept = 0;
		/// <summary>
		/// Sets the path of the module.
		/// This does NOT necessarily change the executable module in the target process.
		/// </summary>
		/// <param name="_path_module">A pointer to the module path string.</param>
		/// <param name="_size_path_module">The size (in <c>char</c>s) of the module path string, in UTF-8.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetModulePath(const char* _path_module, size_t _size_path_module) noexcept = 0;
		/// <summary>Gets the base address of the executable module in the memory.</summary>
		/// <param name="targetaddress_ret">A pointer to a pointer variable that receives a pointer to the base address.</param>
		/// <returns></returns>
		[[nodiscard]] inline const Win32DebuggingTargetAddress* GetBaseAddress() const noexcept(false) {
			const Win32DebuggingTargetAddress* targetaddress = nullptr;
			IException* err = this->GetBaseAddress(&targetaddress);
			if (err) throw(err);
			return targetaddress;
		}
		/// <summary>Gets the size of the executable module in the memory.</summary>
		/// <param name="size_ret">A pointer to a pointer variable that receives a pointer to the executable module size.</param>
		/// <returns></returns>
		[[nodiscard]] inline const Win32DebuggingTargetAddressDiff* GetSize() const noexcept(false) {
			const Win32DebuggingTargetAddressDiff* size = nullptr;
			IException* err = this->GetSize(&size);
			if (err) throw(err);
			return size;
		}
	};

	class Win32DebuggingTargetExecutableModuleInfo : public virtual IWin32DebuggingTargetExecutableModuleInfo {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(Win32DebuggingTargetExecutableModuleInfo, , "db41f044-2aef-4204-b38e-755e236ec8e1");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(Win32DebuggingTargetExecutableModuleInfo);
		template<typename _Module_Entry_32_Ty>
		inline static Win32DebuggingTargetExecutableModuleInfo FromModuleEntry32(Win32Architecture architecture, const _Module_Entry_32_Ty& module_entry_32) {
			return Win32DebuggingTargetExecutableModuleInfo(architecture, module_entry_32);
		}
		explicit Win32DebuggingTargetExecutableModuleInfo(Win32Architecture _architecture) noexcept(false);
		Win32DebuggingTargetExecutableModuleInfo(
			Win32Architecture _architecture,
			const Win32DebuggingTargetAddress& _addr_base,
			const Win32DebuggingTargetAddressDiff& _size,
			const char* _name_module,
			size_t _size_name_module,
			const char* _path_module,
			size_t _size_path_module
		) noexcept(false);
		Win32DebuggingTargetExecutableModuleInfo(const Win32DebuggingTargetExecutableModuleInfo& x) noexcept(false);
		Win32DebuggingTargetExecutableModuleInfo(Win32DebuggingTargetExecutableModuleInfo&& x) noexcept(false);
		virtual ~Win32DebuggingTargetExecutableModuleInfo();
		Win32DebuggingTargetExecutableModuleInfo& operator=(const Win32DebuggingTargetExecutableModuleInfo& x) noexcept(false);
		Win32DebuggingTargetExecutableModuleInfo& operator=(Win32DebuggingTargetExecutableModuleInfo&& x) noexcept(false);
		inline virtual Win32Architecture GetWin32Architecture() const noexcept override { return this->architecture; }
		/// <summary>Gets the base address of the executable module in the memory.</summary>
		/// <param name="targetaddress_ret">A pointer to a pointer variable that receives a pointer to the base address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetBaseAddress(const Win32DebuggingTargetAddress** targetaddress_ret) const noexcept override;
		/// <summary>Gets the size of the executable module in the memory.</summary>
		/// <param name="size_ret">A pointer to a pointer variable that receives a pointer to the executable module size.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetSize(const Win32DebuggingTargetAddressDiff** size_ret) const noexcept override;
		/// <summary>Gets the name of the module.</summary>
		/// <param name="name_module_ret">A pointer to a pointer variable that receives a pointer to the module name string.</param>
		/// <param name="size_name_module_ret">A pointer to a variable that receives the size (in <c>char</c>s) of the module name string, in UTF-8.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetModuleName(const char** name_module_ret, size_t* size_name_module_ret) const noexcept override;
		/// <summary>Gets the path of the module.</summary>
		/// <param name="path_module_ret">A pointer to a pointer variable that receives a pointer to the module path string.</param>
		/// <param name="size_path_module_ret">A pointer to a variable that receives the size (in <c>char</c>s) of the module path string, in UTF-8.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetModulePath(const char** path_module_ret, size_t* size_path_module_ret) const noexcept override;
		/// <summary>
		/// Sets the executable module base address in the memory that's represented by this object.
		/// This does NOT necessarily change the executable module in the target process.
		/// </summary>
		/// <param name="_targetaddress">A pointer to the base address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetBaseAddress(const Win32DebuggingTargetAddress* _targetaddress) noexcept override;
		/// <summary>
		/// Sets the executable module size in the memory that's represented by this object.
		/// This does NOT necessarily change the executable module in the target process.
		/// </summary>
		/// <param name="_size">A pointer to the executable module size.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetSize(const Win32DebuggingTargetAddressDiff* _size) noexcept override;
		/// <summary>
		/// Sets the name of the module.
		/// This does NOT necessarily change the executable module in the target process.
		/// </summary>
		/// <param name="_name_module">A pointer to the module name string.</param>
		/// <param name="_size_name_module">The size (in <c>char</c>s) of the module name string, in UTF-8.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetModuleName(const char* _name_module, size_t _size_name_module) noexcept override;
		/// <summary>
		/// Sets the path of the module.
		/// This does NOT necessarily change the executable module in the target process.
		/// </summary>
		/// <param name="_path_module">A pointer to the module path string.</param>
		/// <param name="_size_path_module">The size (in <c>char</c>s) of the module path string, in UTF-8.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetModulePath(const char* _path_module, size_t _size_path_module) noexcept override;
	protected:
		Win32Architecture architecture = Win32Architecture::Win32Architecture_Invalid;
		Win32DebuggingTargetAddress addr_base;
		Win32DebuggingTargetAddressDiff size;
		objholder_rawallocator_t<char[]> name_module;
		objholder_rawallocator_t<char[]> path_module;
	};

	class IWin32DebuggingTargetExportSymbolInfo : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IWin32DebuggingTargetExportSymbolInfo, YBWLIB2_API, "1ac67357-d392-4e35-a002-bd1e933a2e7c");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IWin32DebuggingTargetExportSymbolInfo);
		inline virtual ~IWin32DebuggingTargetExportSymbolInfo() = default;
		virtual Win32Architecture GetWin32Architecture() const noexcept = 0;
		/// <summary>Gets a pointer to an <c>IWin32DebuggingTargetExecutableModuleInfo</c> object that provides various information about the executable module that contains the export.</summary>
		/// <param name="info_module_ret">A pointer to a pointer variable that receives a pointer to the <c>IWin32DebuggingTargetExecutableModuleInfo</c> object.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetExportModuleInfo(const IWin32DebuggingTargetExecutableModuleInfo** info_module_ret) const noexcept = 0;
		/// <summary>Gets the ordinal of the export.</summary>
		/// <param name="ordinal_ret">A pointer to a variable that receives the ordinal.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetExportOrdinal(DWORD* ordinal_ret) const noexcept = 0;
		/// <summary>Gets whether the export has a name.</summary>
		/// <param name="has_name_ret">A pointer to a variable that receives whether the export has a name.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetHasExportName(bool* has_name_ret) const noexcept = 0;
		/// <summary>
		/// Gets the name of the export.
		/// This function fails when the export doesn't have a name.
		/// </summary>
		/// <param name="name_export_ret">A pointer to a pointer variable that receives a pointer to the export name string, in ASCII.</param>
		/// <param name="size_name_export_ret">A pointer to a variable that receives the size (in <c>char</c>s) of the export name string, in ASCII.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetExportName(const char** name_export_ret, size_t* size_name_export_ret) const noexcept = 0;
		/// <summary>Gets the relative virtual address (RVA) of the export.</summary>
		/// <param name="rva_ret">A pointer to a pointer variable that receives a pointer to the RVA.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetExportRva(const Win32DebuggingTargetAddressDiff** rva_ret) const noexcept = 0;
		/// <summary>Gets whether the export has a forwarder RVA (or an export RVA).</summary>
		/// <param name="is_forwarder_ret">A pointer to a variable that receives whether the export has a forwarder RVA.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetIsExportForwarder(bool* is_forwarder_ret) const noexcept = 0;
		/// <summary>
		/// Gets the forward string of the export.
		/// This function fails when the export has an export RVA instead of a forwarder RVA.
		/// </summary>
		/// <param name="str_forward_export_ret">A pointer to a pointer variable that receives a pointer to the export forward string, in ASCII.</param>
		/// <param name="size_str_forward_export_ret">A pointer to a variable that receives the size (in <c>char</c>s) of the export forward string, in ASCII.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetExportForwardString(const char** str_forward_export_ret, size_t* size_str_forward_export_ret) const noexcept = 0;
		/// <summary>Gets whether the resolved address of the export has been set.</summary>
		/// <param name="is_set_addr_resolved_ret">A pointer to a variable that receives whether the resolved address of the export has been set.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetIsExportResolvedAddressSet(bool* is_set_addr_resolved_ret) const noexcept = 0;
		/// <summary>
		/// Gets the address to which the export resolves.
		/// This function fails if the resolved address of the export has not been set yet.
		/// </summary>
		/// <param name="rva_ret">A pointer to a pointer variable that receives a pointer to the address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetResolvedAddress(const Win32DebuggingTargetAddress** targetaddress_ret) const noexcept = 0;
		/// <summary>
		/// Clears the address to which the export resolves.
		/// This does NOT necessarily change the export in the target process.
		/// </summary>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* ClearResolvedAddress() noexcept = 0;
		/// <summary>
		/// Sets the address to which the export resolves.
		/// This does NOT necessarily change the export in the target process.
		/// </summary>
		/// <param name="_targetaddress">A pointer to the address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetResolvedAddress(const Win32DebuggingTargetAddress* _targetaddress) noexcept = 0;
		/// <summary>Gets a pointer to an <c>IWin32DebuggingTargetExecutableModuleInfo</c> object that provides various information about the executable module that contains the export.</summary>
		/// <returns>Pointer to the <c>IWin32DebuggingTargetExecutableModuleInfo</c> object.</returns>
		[[nodiscard]] inline const IWin32DebuggingTargetExecutableModuleInfo* GetExportModuleInfo() const noexcept(false) {
			const IWin32DebuggingTargetExecutableModuleInfo* info_module = nullptr;
			IException* err = this->GetExportModuleInfo(&info_module);
			if (err) throw(err);
			return info_module;
		}
		/// <summary>Gets the ordinal of the export.</summary>
		/// <returns>The ordinal.</returns>
		[[nodiscard]] inline DWORD GetExportOrdinal() const noexcept(false) {
			DWORD ordinal = 0;
			IException* err = this->GetExportOrdinal(&ordinal);
			if (err) throw(err);
			return ordinal;
		}
		/// <summary>Gets whether the export has a name.</summary>
		/// <returns>Whether the export has a name.</returns>
		[[nodiscard]] inline bool GetHasExportName() const noexcept(false) {
			bool has_name = false;
			IException* err = this->GetHasExportName(&has_name);
			if (err) throw(err);
			return has_name;
		}
		/// <summary>Gets the relative virtual address (RVA) of the export.</summary>
		/// <returns>Pointer to the RVA.</returns>
		[[nodiscard]] inline const Win32DebuggingTargetAddressDiff* GetExportRva() const noexcept(false) {
			const Win32DebuggingTargetAddressDiff* rva = nullptr;
			IException* err = this->GetExportRva(&rva);
			if (err) throw(err);
			return rva;
		}
		/// <summary>Gets whether the export has a forwarder RVA (or an export RVA).</summary>
		/// <param name="is_forwarder_ret">A pointer to a variable that receives </param>
		/// <returns>Whether the export has a forwarder RVA.</returns>
		[[nodiscard]] inline bool GetIsExportForwarder() const noexcept(false) {
			bool is_forwarder = false;
			IException* err = this->GetIsExportForwarder(&is_forwarder);
			if (err) throw(err);
			return is_forwarder;
		}
		/// <summary>Gets whether the resolved address of the export has been set.</summary>
		/// <returns>Whether the resolved address of the export has been set.</returns>
		[[nodiscard]] inline bool GetIsExportResolvedAddressSet() const noexcept(false) {
			bool is_set_addr_resolved = false;
			IException* err = this->GetIsExportResolvedAddressSet(&is_set_addr_resolved);
			if (err) throw(err);
			return is_set_addr_resolved;
		}
		/// <summary>
		/// Gets the address to which the export resolves.
		/// This function fails if the resolved address of the export has not been set yet.
		/// </summary>
		/// <returns>Pointer to the address.</returns>
		[[nodiscard]] inline const Win32DebuggingTargetAddress* GetResolvedAddress() const noexcept(false) {
			const Win32DebuggingTargetAddress* targetaddress = nullptr;
			IException* err = this->GetResolvedAddress(&targetaddress);
			if (err) throw(err);
			return targetaddress;
		}
	};

	class Win32DebuggingTargetExportSymbolInfo : public virtual IWin32DebuggingTargetExportSymbolInfo {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(Win32DebuggingTargetExportSymbolInfo, , "1f66aee9-5fb9-48ec-ad60-d8b2f4526d4b");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(Win32DebuggingTargetExportSymbolInfo);
		explicit Win32DebuggingTargetExportSymbolInfo(Win32Architecture _architecture) noexcept(false);
		Win32DebuggingTargetExportSymbolInfo(
			Win32Architecture _architecture,
			const ::std::shared_ptr<IWin32DebuggingTargetExecutableModuleInfo>& _info_module_export,
			DWORD _ordinal_export,
			const Win32DebuggingTargetAddressDiff& _rva_export
		) noexcept(false);
		Win32DebuggingTargetExportSymbolInfo(
			Win32Architecture _architecture,
			const ::std::shared_ptr<IWin32DebuggingTargetExecutableModuleInfo>& _info_module_export,
			DWORD _ordinal_export,
			const char* _name_export,
			size_t _size_name_export,
			const Win32DebuggingTargetAddressDiff& _rva_export
		) noexcept(false);
		Win32DebuggingTargetExportSymbolInfo(
			Win32Architecture _architecture,
			const ::std::shared_ptr<IWin32DebuggingTargetExecutableModuleInfo>& _info_module_export,
			DWORD _ordinal_export,
			const Win32DebuggingTargetAddressDiff& _rva_export,
			const char* _str_forward_export,
			size_t _size_str_forward_export
		) noexcept(false);
		Win32DebuggingTargetExportSymbolInfo(
			Win32Architecture _architecture,
			const ::std::shared_ptr<IWin32DebuggingTargetExecutableModuleInfo>& _info_module_export,
			DWORD _ordinal_export,
			const char* _name_export,
			size_t _size_name_export,
			const Win32DebuggingTargetAddressDiff& _rva_export,
			const char* _str_forward_export,
			size_t _size_str_forward_export
		) noexcept(false);
		Win32DebuggingTargetExportSymbolInfo(const Win32DebuggingTargetExportSymbolInfo& x) noexcept(false);
		Win32DebuggingTargetExportSymbolInfo(Win32DebuggingTargetExportSymbolInfo&& x) noexcept(false);
		virtual ~Win32DebuggingTargetExportSymbolInfo();
		Win32DebuggingTargetExportSymbolInfo& operator=(const Win32DebuggingTargetExportSymbolInfo& x) noexcept(false);
		Win32DebuggingTargetExportSymbolInfo& operator=(Win32DebuggingTargetExportSymbolInfo&& x) noexcept(false);
		inline virtual Win32Architecture GetWin32Architecture() const noexcept override { return this->architecture; }
		/// <summary>Gets a pointer to an <c>IWin32DebuggingTargetExecutableModuleInfo</c> object that provides various information about the executable module that contains the export.</summary>
		/// <param name="info_module_ret">A pointer to a pointer variable that receives a pointer to the <c>IWin32DebuggingTargetExecutableModuleInfo</c> object.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetExportModuleInfo(const IWin32DebuggingTargetExecutableModuleInfo** info_module_ret) const noexcept override;
		/// <summary>Gets the ordinal of the export.</summary>
		/// <param name="ordinal_ret">A pointer to a variable that receives the ordinal.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetExportOrdinal(DWORD* ordinal_ret) const noexcept override;
		/// <summary>Gets whether the export has a name.</summary>
		/// <param name="has_name_ret">A pointer to a variable that receives whether the export has a name.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetHasExportName(bool* has_name_ret) const noexcept override;
		/// <summary>
		/// Gets the name of the export.
		/// This function fails when the export doesn't have a name.
		/// </summary>
		/// <param name="name_export_ret">A pointer to a pointer variable that receives a pointer to the export name string, in ASCII.</param>
		/// <param name="size_name_export_ret">A pointer to a variable that receives the size (in <c>char</c>s) of the export name string, in ASCII.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetExportName(const char** name_export_ret, size_t* size_name_export_ret) const noexcept override;
		/// <summary>Gets the relative virtual address (RVA) of the export.</summary>
		/// <param name="rva_ret">A pointer to a pointer variable that receives a pointer to the RVA.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetExportRva(const Win32DebuggingTargetAddressDiff** rva_ret) const noexcept override;
		/// <summary>Gets whether the export has a forwarder RVA (or an export RVA).</summary>
		/// <param name="is_forwarder_ret">A pointer to a variable that receives whether the export has a forwarder RVA.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetIsExportForwarder(bool* is_forwarder_ret) const noexcept override;
		/// <summary>
		/// Gets the forward string of the export.
		/// This function fails when the export has an export RVA instead of a forwarder RVA.
		/// </summary>
		/// <param name="str_forward_export_ret">A pointer to a pointer variable that receives a pointer to the export forward string, in ASCII.</param>
		/// <param name="size_str_forward_export_ret">A pointer to a variable that receives the size (in <c>char</c>s) of the export forward string, in ASCII.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetExportForwardString(const char** str_forward_export_ret, size_t* size_str_forward_export_ret) const noexcept override;
		/// <summary>Gets whether the resolved address of the export has been set.</summary>
		/// <param name="is_set_addr_resolved_ret">A pointer to a variable that receives whether the resolved address of the export has been set.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetIsExportResolvedAddressSet(bool* is_set_addr_resolved_ret) const noexcept override;
		/// <summary>
		/// Gets the address to which the export resolves.
		/// This function fails if the resolved address of the export has not been set yet.
		/// </summary>
		/// <param name="rva_ret">A pointer to a pointer variable that receives a pointer to the address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetResolvedAddress(const Win32DebuggingTargetAddress** targetaddress_ret) const noexcept override;
		/// <summary>
		/// Clears the address to which the export resolves.
		/// This does NOT change the export in the target process.
		/// </summary>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* ClearResolvedAddress() noexcept override;
		/// <summary>
		/// Sets the address to which the export resolves.
		/// This does NOT change the export in the target process.
		/// </summary>
		/// <param name="_targetaddress">A pointer to the address.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* SetResolvedAddress(const Win32DebuggingTargetAddress* _targetaddress) noexcept override;
	protected:
		Win32Architecture architecture = Win32Architecture::Win32Architecture_Invalid;
		::std::shared_ptr<IWin32DebuggingTargetExecutableModuleInfo> info_module_export;
		DWORD ordinal_export = 0;
		bool has_name_export = false;
		objholder_rawallocator_t<char[]> name_export;
		Win32DebuggingTargetAddressDiff rva_export;
		bool is_forwarder_export = false;
		objholder_rawallocator_t<char[]> str_forward_export;
		bool is_set_addr_resolved = false;
		Win32DebuggingTargetAddress addr_resolved;
	};

	class IWin32DebuggingProcess : public virtual IReferenceCountedObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IWin32DebuggingProcess, YBWLIB2_API, "8baa6f1c-de0d-4154-9693-97d047e9e426");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IWin32DebuggingProcess);
		inline virtual ~IWin32DebuggingProcess() = default;
		virtual Win32Architecture GetWin32Architecture() const noexcept = 0;
		/// <summary>Gets a pointer to an <c>Win32HandleHolder</c> object that holds the Win32 handle to the process.</summary>
		/// <param name="win32handleholder_ret">A pointer to a pointer variable that receives a pointer to the <c>Win32HandleHolder</c> object.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetProcessWin32HandleHolder(const Win32HandleHolder** win32handleholder_ret) const noexcept = 0;
		/// <summary>Gets a pointer to an <c>Win32HandleHolder</c> object that holds the Win32 handle to the process.</summary>
		/// <returns>Pointer to the <c>Win32HandleHolder</c> object.</returns>
		[[nodiscard]] inline const Win32HandleHolder* GetProcessWin32HandleHolder() const noexcept(false) {
			const Win32HandleHolder* win32handleholder = false;
			IException* err = this->GetProcessWin32HandleHolder(&win32handleholder);
			if (err) throw(err);
			return win32handleholder;
		}
	};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4250)
#endif
	class Win32DebuggingProcess
		: public virtual ReferenceCountedObject,
		public virtual IWin32DebuggingProcess {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(Win32DebuggingProcess, , "97c29945-80bb-49ff-902d-8715e4007205");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(Win32DebuggingProcess);
		static Win32Architecture GetProcessWin32Architecture(const Win32HandleHolder& _win32handleholder_process) noexcept(false);
		explicit Win32DebuggingProcess(const Win32HandleHolder& _win32handleholder_process) noexcept(false);
		Win32DebuggingProcess(const Win32DebuggingProcess& x) = delete;
		Win32DebuggingProcess(Win32DebuggingProcess&& x) = delete;
		virtual ~Win32DebuggingProcess();
		Win32DebuggingProcess& operator=(const Win32DebuggingProcess& x) = delete;
		Win32DebuggingProcess& operator=(Win32DebuggingProcess&& x) = delete;
		inline virtual void DeleteMe() noexcept override { delete this; }
		inline virtual Win32Architecture GetWin32Architecture() const noexcept override { return this->architecture; }
		/// <summary>Gets a pointer to an <c>Win32HandleHolder</c> object that holds the Win32 handle to the process.</summary>
		/// <param name="win32handleholder_ret">A pointer to a pointer variable that receives a pointer to the <c>Win32HandleHolder</c> object.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// </returns>
		[[nodiscard]] virtual IException* GetProcessWin32HandleHolder(const Win32HandleHolder** win32handleholder_ret) const noexcept override;
	protected:
		Win32Architecture architecture = Win32Architecture::Win32Architecture_Invalid;
		Win32HandleHolder win32handleholder_process;
		DWORD processid = 0;
	};
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Win32DebuggingReadTargetMemory(Win32Architecture architecture, const Win32HandleHolder* win32handleholder_process, void* buf, size_t size, const Win32DebuggingTargetAddress* targetaddress) noexcept;
	[[nodiscard]] YBWLIB2_API IException* YBWLIB2_CALLTYPE Win32DebuggingWriteTargetMemory(Win32Architecture architecture, const Win32HandleHolder* win32handleholder_process, const void* buf, size_t size, const Win32DebuggingTargetAddress* targetaddress) noexcept;

	inline void Win32DebuggingReadTargetMemory(Win32Architecture architecture, const Win32HandleHolder& win32handleholder_process, void* buf, size_t size, const Win32DebuggingTargetAddress& targetaddress) noexcept(false) {
		IException* err = Win32DebuggingReadTargetMemory(architecture, &win32handleholder_process, buf, size, &targetaddress);
		if (err) throw(err);
	}

	inline void Win32DebuggingWriteTargetMemory(Win32Architecture architecture, const Win32HandleHolder& win32handleholder_process, const void* buf, size_t size, const Win32DebuggingTargetAddress& targetaddress) noexcept(false) {
		IException* err = Win32DebuggingWriteTargetMemory(architecture, &win32handleholder_process, buf, size, &targetaddress);
		if (err) throw(err);
	}

	Win32DebuggingTargetMemoryRegionInfo Win32DebuggingQueryTargetMemoryRegion(Win32Architecture architecture, const Win32HandleHolder& win32handleholder_process, const Win32DebuggingTargetAddress& targetaddress) noexcept(false);
	::std::vector<Win32DebuggingTargetMemoryRegionInfo> Win32DebuggingListTargetMemoryRegions(Win32Architecture architecture, const Win32HandleHolder& win32handleholder_process) noexcept(false);
	::std::vector<Win32DebuggingTargetExecutableModuleInfo> Win32DebuggingListTargetExecutableModules(Win32Architecture architecture, const Win32HandleHolder& win32handleholder_process) noexcept(false);
	::std::vector<Win32DebuggingTargetExportSymbolInfo> Win32DebuggingListTargetExportSymbolsInTargetExecutableModule(const ::std::shared_ptr<Win32DebuggingTargetExecutableModuleInfo>& targetexecutablemoduleinfo, const void* buf_module, size_t size_buf_module) noexcept(false);

	void YBWLIB2_CALLTYPE DebuggingWindows_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE DebuggingWindows_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE DebuggingWindows_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE DebuggingWindows_RealUnInitModuleLocal() noexcept;

	void YBWLIB2_CALLTYPE DebuggingWindowsUserInterface_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE DebuggingWindowsUserInterface_RealUnInitGlobal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_11C7E528_BB34_4934_BB9B_DA0A2B03C1C0
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_11C7E528_BB34_4934_BB9B_DA0A2B03C1C0
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_03ABA3CE_3F93_404D_A92B_47E840F4FC4B
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_03ABA3CE_3F93_404D_A92B_47E840F4FC4B
#endif
