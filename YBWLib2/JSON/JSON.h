#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_DF400AB1_E704_482A_8699_42E85042DA8A
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#ifndef YBWLIB2_EXCEPTION_MACROS_ENABLED
#define _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_201A7625_59CF_4B4C_A4F0_D8EE0A7DDD9A
#define YBWLIB2_EXCEPTION_MACROS_ENABLED
#endif

#ifndef _INCLUDE_GUARD_12F7E69E_86D0_4137_941F_BBDB9592C14D
#define _INCLUDE_GUARD_12F7E69E_86D0_4137_941F_BBDB9592C14D

#include <type_traits>
#include "../YBWLib2Api.h"
#include "../Common/CommonLowLevel.h"
#include "../DynamicType/DynamicType.h"
#include "../Exception/Exception.h"

namespace YBWLib2 {
	/// <summary>An exception that relates to JSON.</summary>
	class IJSONException abstract : public virtual IException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IJSONException, YBWLIB2_API, "6c604b68-7701-4e56-892e-863cc4fd87e5");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IJSONException);
		inline virtual ~IJSONException() = default;
	};

	/// <summary>An exception that occurs because of a JSON parse error.</summary>
	class IParseErrorJSONException abstract : public virtual IJSONException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IParseErrorJSONException, YBWLIB2_API, "4e22d1ad-4474-4c2c-8369-1e0c4abf543e");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IParseErrorJSONException);
		inline virtual ~IParseErrorJSONException() = default;
		/// <summary>
		/// Gets the offset of the parse error.
		/// If no meaningful parse error offset can be provided, <c>0</c> is returned.
		/// </summary>
		virtual size_t GetParseErrorOffset() const noexcept = 0;
		/// <summary>Gets the null-terminated parse error string, if available.</summary>
		/// <returns>
		/// Returns the null-terminated parse error string, in UTF-8, if available.
		/// If no meaningful parse error string can be provided, an empty pointer is returned.
		/// </returns>
		virtual const char* GetParseErrorString() const noexcept = 0;
	};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4250)
#endif
	/// <summary>
	/// A default implementation of <c>IJSONException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IJSONException</c>.
	/// </summary>
	class JSONException
		: public virtual Exception,
		public virtual IJSONException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(JSONException, , "b3549309-4fdd-483c-810e-1247d13aaa8b");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(JSONException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		inline JSONException() noexcept = default;
		inline virtual ~JSONException() = default;
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
	};

	/// <summary>
	/// A default implementation of <c>IParseErrorJSONException</c>.
	/// One executable module should NOT be allowed to access objects created by other executable modules using this type.
	/// Instead, access by <c>IParseErrorJSONException</c>.
	/// </summary>
	class ParseErrorJSONException
		: public virtual JSONException,
		public virtual IParseErrorJSONException {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_MODULE_LOCAL(ParseErrorJSONException, , "2cd35585-2444-474c-acdc-11553254e810");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(ParseErrorJSONException);
		static YBWLIB2_API IStringTemplate* strtmpl_description;
		/// <summary>Constructs an <c>ParseErrorJSONException</c> object.</summary>
		/// <param name="_offset_parse_error">
		/// The offset of the parse error, if available.
		/// If no meaningful parse error offset can be provided, pass <c>0</c>.
		/// </param>
		/// <param name="_str_parse_error">
		/// The null-terminated parse error string, if available.
		/// If no meaningful parse error string can be provided, pass an empty pointer.
		/// </param>
		inline ParseErrorJSONException(size_t _offset_parse_error, const char* _str_parse_error) noexcept : offset_parse_error(_offset_parse_error) {
			if (_str_parse_error) {
				size_t size_str_parse_error = strlen(_str_parse_error);
				this->str_parse_error = reinterpret_cast<char*>(ExceptionAllocateMemory((size_str_parse_error + 1) * sizeof(char), alignof(char[])));
				memcpy(this->str_parse_error, _str_parse_error, (size_str_parse_error + 1) * sizeof(char));
			}
		}
		inline virtual ~ParseErrorJSONException() {
			if (this->str_parse_error) {
				ExceptionFreeMemory(this->str_parse_error);
				this->str_parse_error = nullptr;
			}
		}
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
		/// <summary>
		/// Gets the offset of the parse error.
		/// If no meaningful parse error offset can be provided, <c>0</c> is returned.
		/// </summary>
		inline virtual size_t GetParseErrorOffset() const noexcept override {
			return this->offset_parse_error;
		}
		/// <summary>Gets the null-terminated parse error string, if available.</summary>
		/// <returns>
		/// Returns the null-terminated parse error string, in UTF-8, if available.
		/// If no meaningful parse error string can be provided, an empty pointer is returned.
		/// </returns>
		inline virtual const char* GetParseErrorString() const noexcept override {
			return this->str_parse_error ? this->str_parse_error : nullptr;
		}
	protected:
		size_t offset_parse_error = 0;
		char* str_parse_error = nullptr;
	};
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	/// <summary>
	/// JSON SAX handler interface.
	/// Satisfies <c>::rapidjson::Handler</c> concept.
	/// See RapidJSON document for JSON SAX.
	/// </summary>
	class IJSONSAXHandler abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IJSONSAXHandler, YBWLIB2_API, "86281f2a-7d71-48b4-ab0b-024482b85862");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IJSONSAXHandler);
		inline virtual ~IJSONSAXHandler() = default;
		virtual bool Null() = 0;
		virtual bool Bool(bool value) = 0;
		virtual bool Int(int value) = 0;
		virtual bool Uint(unsigned value) = 0;
		virtual bool Int64(int64_t value) = 0;
		virtual bool Uint64(uint64_t value) = 0;
		virtual bool Double(double value) = 0;
		virtual bool RawNumber(const char* value, size_t size_value, bool should_copy) = 0;
		virtual bool String(const char* value, size_t size_value, bool should_copy) = 0;
		virtual bool StartObject() = 0;
		virtual bool Key(const char* value, size_t size_value, bool should_copy) = 0;
		virtual bool EndObject(size_t count_member) = 0;
		virtual bool StartArray() = 0;
		virtual bool EndArray(size_t count_element) = 0;
	};

	/// <summary>JSON SAX generator interface.</summary>
	class IJSONSAXGenerator abstract : public virtual IDynamicTypeObject {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_CLASS_GLOBAL(IJSONSAXGenerator, YBWLIB2_API, "0f935097-d8a0-4bfb-a884-a3668e383784");
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INLINE(IJSONSAXGenerator);
		inline virtual ~IJSONSAXGenerator() = default;
		/// <summary>Whether this generator generates JSON SAX events one at a time.</summary>
		virtual bool IsIterative() const noexcept = 0;
		/// <summary>
		/// Generates all available events sequentially and dispatches them to <paramref name="jsonsaxhandler" />.
		/// Only allowed when <c>this->IsIterative()</c> returns <c>false</c>.
		/// </summary>
		/// <param name="jsonsaxhandler">The JSON SAX handler that receives the generated events.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory.
		/// </returns>
		[[nodiscard]] virtual IException* Generate(IJSONSAXHandler* jsonsaxhandler) noexcept = 0;
		/// <summary>
		/// Whether there're no more events to be generated by this generator.
		/// Only allowed when <c>this->IsIterative()</c> returns <c>true</c>.
		/// </summary>
		virtual bool IsIterativeComplete() const noexcept = 0;
		/// <summary>
		/// Generates a single event and dispatches it to <paramref name="jsonsaxhandler" />.
		/// Only allowed when <c>this->IsIterative()</c> returns <c>true</c>.
		/// </summary>
		/// <param name="jsonsaxhandler">The JSON SAX handler that receives the generated event.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory.
		/// </returns>
		[[nodiscard]] virtual IException* GenerateIterativeNext(IJSONSAXHandler* jsonsaxhandler) noexcept = 0;
	};

	/// <summary>
	/// An implementation for <c>IJSONSAXHandler</c> that wraps a JSON SAX handler that satisfies <c>::rapidjson::Handler</c> concept.
	/// Satisfies <c>::rapidjson::Handler</c> concept.
	/// </summary>
	template<typename T_Wrapped>
	class JSONSAXHandlerWrapper : public virtual IJSONSAXHandler {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(JSONSAXHandlerWrapper);
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(JSONSAXHandlerWrapper);
		explicit JSONSAXHandlerWrapper(T_Wrapped& _wrapped) : wrapped(&_wrapped) {}
		inline virtual ~JSONSAXHandlerWrapper() { this->wrapped = nullptr; }
		virtual bool Null() override { return this->wrapped->Null(); }
		virtual bool Bool(bool value) override { return this->wrapped->Bool(value); }
		virtual bool Int(int value) override { return this->wrapped->Int(value); }
		virtual bool Uint(unsigned value) override { return this->wrapped->Uint(value); }
		virtual bool Int64(int64_t value) override { return this->wrapped->Int64(value); }
		virtual bool Uint64(uint64_t value) override { return this->wrapped->Uint64(value); }
		virtual bool Double(double value) override { return this->wrapped->Double(value); }
		virtual bool RawNumber(const char* value, size_t size_value, bool should_copy) override { return this->wrapped->RawNumber(value, size_value, should_copy); }
		virtual bool String(const char* value, size_t size_value, bool should_copy) override { return this->wrapped->String(value, size_value, should_copy); }
		virtual bool StartObject() override { return this->wrapped->StartObject(); }
		virtual bool Key(const char* value, size_t size_value, bool should_copy) override { return this->wrapped->Key(value, size_value, should_copy); }
		virtual bool EndObject(size_t count_member) override { return this->wrapped->EndObject(count_member); }
		virtual bool StartArray() override { return this->wrapped->StartArray(); }
		virtual bool EndArray(size_t count_element) override { return this->wrapped->EndArray(count_element); }
	protected:
		T_Wrapped* wrapped;
	};

	/// <summary>An implementation for <c>IJSONSAXGenerator</c> that wraps a <c>::rapidjson::GenericReader</c> object.</summary>
	template<typename T_Wrapped, unsigned flags_rapidjson_parse, typename T_Stream_Input, typename T_Fn_Get_Parse_Error>
	class ReaderJSONSAXGeneratorWrapper : public virtual IJSONSAXGenerator {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(ReaderJSONSAXGeneratorWrapper);
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(ReaderJSONSAXGeneratorWrapper);
		static_assert(
			!(::std::is_pointer_v<T_Fn_Get_Parse_Error> && ::std::is_function_v<::std::remove_pointer_t<T_Fn_Get_Parse_Error>>),
			"The function type should be used instead of the function pointer type as the actual template parameter for T_Fn_Get_Parse_Error."
			);
		explicit ReaderJSONSAXGeneratorWrapper(
			T_Wrapped& _wrapped,
			T_Stream_Input& _stream_input,
			T_Fn_Get_Parse_Error& _fn_get_parse_error,
			bool _is_iterative
		) : wrapped(&_wrapped), stream_input(&_stream_input), fn_get_parse_error(&_fn_get_parse_error), is_iterative(_is_iterative) {}
		inline virtual ~ReaderJSONSAXGeneratorWrapper() {
			this->wrapped = nullptr;
			this->stream_input = nullptr;
			this->fn_get_parse_error = nullptr;
		}
		/// <summary>Whether this generator generates JSON SAX events one at a time.</summary>
		inline virtual bool IsIterative() const noexcept override { return this->is_iterative; }
		/// <summary>
		/// Generates all available events sequentially and dispatches them to <paramref name="jsonsaxhandler" />.
		/// Only allowed when <c>this->IsIterative()</c> returns <c>false</c>.
		/// </summary>
		/// <param name="jsonsaxhandler">The JSON SAX handler that receives the generated events.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory.
		/// </returns>
		[[nodiscard]] inline virtual IException* Generate(IJSONSAXHandler* jsonsaxhandler) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &jsonsaxhandler, &err_inner]() noexcept(false)->void {
					if (!this->wrapped->Parse<flags_rapidjson_parse, T_Stream_Input, IJSONSAXHandler>(*this->stream_input, *jsonsaxhandler)) {
						err_inner = new ParseErrorJSONException(this->wrapped->GetErrorOffset(), (*this->fn_get_parse_error)(this->wrapped->GetParseErrorCode()));
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
		/// Whether there're no more events to be generated by this generator.
		/// Only allowed when <c>this->IsIterative()</c> returns <c>true</c>.
		/// </summary>
		inline virtual bool IsIterativeComplete() const noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &err_inner]() noexcept(false)->void {
					static_cast<void>(err_inner);
					return this->wrapped->IterativeParseComplete();
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
		/// Generates a single event and dispatches it to <paramref name="jsonsaxhandler" />.
		/// Only allowed when <c>this->IsIterative()</c> returns <c>true</c>.
		/// </summary>
		/// <param name="jsonsaxhandler">The JSON SAX handler that receives the generated event.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory.
		/// </returns>
		[[nodiscard]] inline virtual IException* GenerateIterativeNext(IJSONSAXHandler* jsonsaxhandler) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &jsonsaxhandler, &err_inner]() noexcept(false)->void {
					if (!this->wrapped->IterativeParseNext<flags_rapidjson_parse, T_Stream_Input, IJSONSAXHandler>(*this->stream_input, *jsonsaxhandler)) {
						err_inner = new ParseErrorJSONException(this->wrapped->GetErrorOffset(), (*this->fn_get_parse_error)(this->wrapped->GetParseErrorCode()));
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
		T_Wrapped* wrapped;
		T_Stream_Input* stream_input;
		T_Fn_Get_Parse_Error* fn_get_parse_error;
		const bool is_iterative;
	};

	/// <summary>An implementation for <c>IJSONSAXGenerator</c> that wraps a <c>::rapidjson::GenericValue</c> object.</summary>
	template<typename T_Wrapped>
	class ValueJSONSAXGeneratorWrapper : public virtual IJSONSAXGenerator {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(ValueJSONSAXGeneratorWrapper);
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(ValueJSONSAXGeneratorWrapper);
		explicit ValueJSONSAXGeneratorWrapper(T_Wrapped& _wrapped) : wrapped(&_wrapped) {}
		inline virtual ~ValueJSONSAXGeneratorWrapper() {
			this->wrapped = nullptr;
		}
		/// <summary>Whether this generator generates JSON SAX events one at a time.</summary>
		inline virtual bool IsIterative() const noexcept override { return false; }
		/// <summary>
		/// Generates all available events sequentially and dispatches them to <paramref name="jsonsaxhandler" />.
		/// Only allowed when <c>this->IsIterative()</c> returns <c>false</c>.
		/// </summary>
		/// <param name="jsonsaxhandler">The JSON SAX handler that receives the generated events.</param>
		/// <returns>
		/// Returns a pointer to the exception object if the function fails.
		/// Returns an empty pointer otherwise.
		/// The caller is responsible for destructing and freeing the object pointed to.
		/// The exception object is created in exception handling dedicated memory.
		/// </returns>
		[[nodiscard]] inline virtual IException* Generate(IJSONSAXHandler* jsonsaxhandler) noexcept override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &jsonsaxhandler, &err_inner]() noexcept(false)->void {
					if (!this->wrapped->Accept(*jsonsaxhandler)) {
						err_inner = new JSONException();
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
		/// <summary>Unavailable in this class.</summary>
		inline virtual bool IsIterativeComplete() const noexcept override {
			return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ValueJSONSAXGeneratorWrapper, IsIterative);
		}
		/// <summary>Unavailable in this class.</summary>
		[[nodiscard]] inline virtual IException* GenerateIterativeNext(IJSONSAXHandler* jsonsaxhandler) noexcept override {
			static_cast<void>(jsonsaxhandler);
			return YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::ValueJSONSAXGeneratorWrapper, GenerateIterativeNext);
		}
	protected:
		T_Wrapped* wrapped;
	};

	class JSONSAXGeneratorParameterIndexedDataEntry final {
	public:
		static constexpr PersistentID persistentid_entryid = PersistentID(UUIDFromUUIDString_CompileTime("e95a6b6a-2c71-414e-8f3c-b49b9f9471ad"));
		static YBWLIB2_API IndexedDataEntryID entryid;
		inline static JSONSAXGeneratorParameterIndexedDataEntry* CopyFromStore(const IndexedDataStore& _indexeddatastore, void* _ptr_placement) noexcept {
			if (!_ptr_placement) abort();
			const IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(JSONSAXGeneratorParameterIndexedDataEntry::entryid);
			if (_indexeddatarawvalue) {
				return new(_ptr_placement) JSONSAXGeneratorParameterIndexedDataEntry(*_indexeddatarawvalue);
			} else {
				return nullptr;
			}
		}
		static JSONSAXGeneratorParameterIndexedDataEntry CopyFromStore(const IndexedDataStore& _indexeddatastore) noexcept(false);
		inline static JSONSAXGeneratorParameterIndexedDataEntry* MoveFromStore(IndexedDataStore& _indexeddatastore, void* _ptr_placement) noexcept {
			if (!_ptr_placement) abort();
			IndexedDataRawValue* _indexeddatarawvalue = _indexeddatastore.GetRawValueByEntryID(JSONSAXGeneratorParameterIndexedDataEntry::entryid);
			if (_indexeddatarawvalue) {
				JSONSAXGeneratorParameterIndexedDataEntry* ret = new(_ptr_placement) JSONSAXGeneratorParameterIndexedDataEntry(::std::move(*_indexeddatarawvalue));
				_indexeddatastore.RemoveEntryByEntryID(JSONSAXGeneratorParameterIndexedDataEntry::entryid);
				return ret;
			} else {
				return nullptr;
			}
		}
		static JSONSAXGeneratorParameterIndexedDataEntry MoveFromStore(IndexedDataStore& _indexeddatastore) noexcept(false);
		inline static void AddToStore(IndexedDataStore& _indexeddatastore, JSONSAXGeneratorParameterIndexedDataEntry&& _entry) noexcept {
			_indexeddatastore.AddEntry(JSONSAXGeneratorParameterIndexedDataEntry::entryid, static_cast<IndexedDataRawValue>(_entry));
		}
		inline static void RemoveFromStore(IndexedDataStore& _indexeddatastore) noexcept {
			_indexeddatastore.RemoveEntryByEntryID(JSONSAXGeneratorParameterIndexedDataEntry::entryid);
		}
		IJSONSAXGenerator* jsonsaxgenerator = nullptr;
		inline explicit constexpr JSONSAXGeneratorParameterIndexedDataEntry(IJSONSAXGenerator* _jsonsaxgenerator) noexcept : jsonsaxgenerator(_jsonsaxgenerator) {}
		inline constexpr JSONSAXGeneratorParameterIndexedDataEntry(const JSONSAXGeneratorParameterIndexedDataEntry& x) noexcept : jsonsaxgenerator(x.jsonsaxgenerator) {}
		inline constexpr JSONSAXGeneratorParameterIndexedDataEntry(JSONSAXGeneratorParameterIndexedDataEntry&& x) noexcept : jsonsaxgenerator(x.jsonsaxgenerator) {
			x.jsonsaxgenerator = nullptr;
		}
		inline ~JSONSAXGeneratorParameterIndexedDataEntry() {
			this->jsonsaxgenerator = nullptr;
		}
		inline JSONSAXGeneratorParameterIndexedDataEntry& operator=(const JSONSAXGeneratorParameterIndexedDataEntry& x) noexcept {
			this->jsonsaxgenerator = x.jsonsaxgenerator;
			return *this;
		}
		inline JSONSAXGeneratorParameterIndexedDataEntry& operator=(JSONSAXGeneratorParameterIndexedDataEntry&& x) noexcept {
			this->jsonsaxgenerator = ::std::move(x.jsonsaxgenerator);
			x.jsonsaxgenerator = nullptr;
			return *this;
		}
	private:
		inline explicit JSONSAXGeneratorParameterIndexedDataEntry(const IndexedDataRawValue& _indexeddatarawvalue) : jsonsaxgenerator(reinterpret_cast<IJSONSAXGenerator*>(_indexeddatarawvalue.contextvalue)) {}
		inline explicit JSONSAXGeneratorParameterIndexedDataEntry(IndexedDataRawValue&& _indexeddatarawvalue) : jsonsaxgenerator(::std::move(reinterpret_cast<IJSONSAXGenerator*>(_indexeddatarawvalue.contextvalue))) {
			_indexeddatarawvalue.contextvalue = 0;
		}
		inline operator IndexedDataRawValue() const noexcept { return IndexedDataRawValue(nullptr, reinterpret_cast<uintptr_t>(this->jsonsaxgenerator)); }
	};
	static_assert(::std::is_standard_layout_v<JSONSAXGeneratorParameterIndexedDataEntry>, "JSONSAXGeneratorParameterIndexedDataEntry is not standard-layout.");

	void YBWLIB2_CALLTYPE JSON_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE JSON_RealUnInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE JSON_RealInitModuleLocal() noexcept;
	void YBWLIB2_CALLTYPE JSON_RealUnInitModuleLocal() noexcept;

	void YBWLIB2_CALLTYPE JSONUserInterface_RealInitGlobal() noexcept;
	void YBWLIB2_CALLTYPE JSONUserInterface_RealUnInitGlobal() noexcept;
}

#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_201A7625_59CF_4B4C_A4F0_D8EE0A7DDD9A
#undef YBWLIB2_EXCEPTION_MACROS_ENABLED
#include "../Exception/ExceptionMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_EXCEPTION_MACROS_ENABLED_201A7625_59CF_4B4C_A4F0_D8EE0A7DDD9A
#endif

#ifdef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_DF400AB1_E704_482A_8699_42E85042DA8A
#undef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#include "../DynamicType/DynamicTypeMacroUndef.h"
#undef _MACRO_DEFINE_TEMP_YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED_DF400AB1_E704_482A_8699_42E85042DA8A
#endif
