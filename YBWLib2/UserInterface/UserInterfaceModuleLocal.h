#ifndef _INCLUDE_GUARD_D07AE856_589D_4687_A307_4FD3B73DB5A5
#define _INCLUDE_GUARD_D07AE856_589D_4687_A307_4FD3B73DB5A5

#ifndef YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#define YBWLIB2_DYNAMIC_TYPE_MACROS_ENABLED
#endif

#include "../DynamicType/DynamicType.h"
#include "UserInterface.h"

namespace YBWLib2 {
	class SubstitutionStringTemplateConstructorJSONSAXHandler final : public virtual IJSONSAXHandler {
	public:
		YBWLIB2_DYNAMIC_TYPE_DECLARE_NO_CLASS(SubstitutionStringTemplateConstructorJSONSAXHandler);
		YBWLIB2_DYNAMIC_TYPE_DECLARE_IOBJECT_INHERIT(SubstitutionStringTemplateConstructorJSONSAXHandler);
		static constexpr char key_name_parameter[] = YBWLIB2_TO_UTF8("name_parameter");
		static constexpr char key_options[] = YBWLIB2_TO_UTF8("options");
		enum State : uint32_t {
			State_Initial = 0,
			State_Complete,
			State_InElementArray,
			State_InSubstituteElementObject,
			State_AwaitingParameterNameValueInSubstituteElementObject,
			State_AwaitingOptionsValueInSubstituteElementObject
		} state = State_Initial;
		const rawallocator_t* rawallocator = nullptr;
		SubstitutionStringTemplate::vec_element_t* vec_element = nullptr;
		inline SubstitutionStringTemplateConstructorJSONSAXHandler(const rawallocator_t* _rawallocator, SubstitutionStringTemplate::vec_element_t* _vec_element) : rawallocator(_rawallocator), vec_element(_vec_element) {}
		SubstitutionStringTemplateConstructorJSONSAXHandler(const SubstitutionStringTemplateConstructorJSONSAXHandler&) = delete;
		SubstitutionStringTemplateConstructorJSONSAXHandler(SubstitutionStringTemplateConstructorJSONSAXHandler&&) = delete;
		inline virtual ~SubstitutionStringTemplateConstructorJSONSAXHandler() {
			this->ClearSubstituteElementTempValues();
		}
		SubstitutionStringTemplateConstructorJSONSAXHandler& operator=(const SubstitutionStringTemplateConstructorJSONSAXHandler&) = delete;
		SubstitutionStringTemplateConstructorJSONSAXHandler& operator=(SubstitutionStringTemplateConstructorJSONSAXHandler&&) = delete;
		inline virtual bool Null() override { return false; }
		inline virtual bool Bool(bool value) override {
			static_cast<void>(value);
			return false;
		}
		inline virtual bool Int(int value) override {
			static_cast<void>(value);
			return false;
		}
		inline virtual bool Uint(unsigned value) override {
			static_cast<void>(value);
			return false;
		}
		inline virtual bool Int64(int64_t value) override {
			static_cast<void>(value);
			return false;
		}
		inline virtual bool Uint64(uint64_t value) override {
			static_cast<void>(value);
			return false;
		}
		inline virtual bool Double(double value) override {
			static_cast<void>(value);
			return false;
		}
		inline virtual bool RawNumber(const char* value, size_t size_value, bool should_copy) override {
			static_cast<void>(value);
			static_cast<void>(size_value);
			static_cast<void>(should_copy);
			return false;
		}
		inline virtual bool String(const char* value, size_t size_value, bool should_copy) override {
			static_cast<void>(should_copy);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &value, &size_value, &err_inner]()->void {
					switch (this->state) {
					case State_InElementArray: {
						this->vec_element->emplace_back(this->rawallocator, value, size_value);
						return;
					}
					case State_AwaitingParameterNameValueInSubstituteElementObject: {
						if (size_value && !value) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplateConstructorJSONSAXHandler, String); return; }
						this->size_name_parameter_value_temp_element_substitute = size_value;
						this->name_parameter_value_temp_element_substitute = reinterpret_cast<char*>(this->rawallocator->Allocate(this->size_name_parameter_value_temp_element_substitute * sizeof(char)));
						if (!this->name_parameter_value_temp_element_substitute) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
						if (this->size_name_parameter_value_temp_element_substitute) memcpy(this->name_parameter_value_temp_element_substitute, value, this->size_name_parameter_value_temp_element_substitute * sizeof(char));
						return;
					}
					case State_AwaitingOptionsValueInSubstituteElementObject: {
						if (size_value && !value) { err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplateConstructorJSONSAXHandler, String); return; }
						this->size_str_options_value_temp_element_substitute = size_value;
						this->str_options_value_temp_element_substitute = reinterpret_cast<char*>(this->rawallocator->Allocate(this->size_str_options_value_temp_element_substitute * sizeof(char)));
						if (!this->str_options_value_temp_element_substitute) { err_inner = YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION(); return; }
						if (this->size_str_options_value_temp_element_substitute) memcpy(this->str_options_value_temp_element_substitute, value, this->size_str_options_value_temp_element_substitute * sizeof(char));
						return;
					}
					default:
					{
						err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplateConstructorJSONSAXHandler, String);
						return;
					}
					}
				});
			if (err) {
				if (err_inner) {
					delete err_inner;
					err_inner = nullptr;
				}
				delete err;
				err = nullptr;
				return false;
			} else if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
				return false;
			} else return true;
		}
		inline virtual bool StartObject() override {
			if (this->state == State_InElementArray) {
				this->state = State_InSubstituteElementObject;
				return true;
			} else return false;
		}
		inline virtual bool Key(const char* value, size_t size_value, bool should_copy) override {
			static_cast<void>(should_copy);
			if (this->state == State_InSubstituteElementObject) {
				if (size_value == sizeof(key_name_parameter) / sizeof(char) - 1 && !strncmp(value, key_name_parameter, size_value)) {
					this->state = State_AwaitingParameterNameValueInSubstituteElementObject;
					return true;
				} else if (size_value == sizeof(key_options) / sizeof(char) - 1 && !strncmp(value, key_options, size_value)) {
					this->state = State_AwaitingOptionsValueInSubstituteElementObject;
					return true;
				} else return false;
			} else return false;
		}
		inline virtual bool EndObject(size_t count_member) override {
			static_cast<void>(count_member);
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &err_inner]()->void {
					if (this->state == State_InSubstituteElementObject) {
						this->vec_element->emplace_back(
							this->rawallocator,
							this->name_parameter_value_temp_element_substitute,
							this->size_name_parameter_value_temp_element_substitute,
							this->str_options_value_temp_element_substitute,
							this->size_str_options_value_temp_element_substitute
						);
						this->state = State_InElementArray;
					} else {
						err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplateConstructorJSONSAXHandler, EndObject);
						return;
					}
				});
			if (err) {
				if (err_inner) {
					delete err_inner;
					err_inner = nullptr;
				}
				delete err;
				err = nullptr;
				return false;
			} else if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
				return false;
			} else return true;
		}
		inline virtual bool StartArray() override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &err_inner]()->void {
					if (this->state == State_Initial) {
						this->state = State_InElementArray;
						this->vec_element->clear();
					} else {
						err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplateConstructorJSONSAXHandler, StartArray);
						return;
					}
				});
			if (err) {
				if (err_inner) {
					delete err_inner;
					err_inner = nullptr;
				}
				delete err;
				err = nullptr;
				return false;
			} else if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
				return false;
			} else return true;
		}
		inline virtual bool EndArray(size_t count_element) override {
			IException* err_inner = nullptr;
			IException* err = WrapFunctionCatchExceptions(
				[this, &count_element, &err_inner]()->void {
					if (this->state == State_InElementArray && this->vec_element->size() == count_element) {
						this->state = State_Complete;
					} else {
						err_inner = YBWLIB2_EXCEPTION_CREATE_INVALID_CALL_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplateConstructorJSONSAXHandler, EndArray);
						return;
					}
				});
			if (err) {
				if (err_inner) {
					delete err_inner;
					err_inner = nullptr;
				}
				delete err;
				err = nullptr;
				return false;
			} else if (err_inner) {
				delete err_inner;
				err_inner = nullptr;
				return false;
			} else return true;
		}
		inline bool IsComplete() const noexcept { return this->state == State_Complete; }
	private:
		char* name_parameter_value_temp_element_substitute = nullptr;
		size_t size_name_parameter_value_temp_element_substitute = 0;
		char* str_options_value_temp_element_substitute = nullptr;
		size_t size_str_options_value_temp_element_substitute = 0;
		inline void ClearSubstituteElementTempValueParameterName() noexcept {
			if (this->name_parameter_value_temp_element_substitute) {
				if (!this->rawallocator->Deallocate(this->name_parameter_value_temp_element_substitute, this->size_name_parameter_value_temp_element_substitute * sizeof(char))) abort();
				this->name_parameter_value_temp_element_substitute = nullptr;
			}
			this->size_name_parameter_value_temp_element_substitute = 0;
		}
		inline void ClearSubstituteElementTempValueOptions() noexcept {
			if (this->str_options_value_temp_element_substitute) {
				if (!this->rawallocator->Deallocate(this->str_options_value_temp_element_substitute, this->size_str_options_value_temp_element_substitute * sizeof(char))) abort();
				this->str_options_value_temp_element_substitute = nullptr;
			}
			this->size_str_options_value_temp_element_substitute = 0;
		}
		inline void ClearSubstituteElementTempValues() noexcept {
			this->ClearSubstituteElementTempValueParameterName();
			this->ClearSubstituteElementTempValueOptions();
		}
	};

	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringTemplateParameter, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringStringTemplateParameter, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringTemplateParameterList, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(StringTemplate, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(FixedStringTemplate, );
	YBWLIB2_DYNAMIC_TYPE_IMPLEMENT_CLASS(SubstitutionStringTemplate, );

	SubstitutionStringTemplate::SubstitutionStringTemplate(
		const rawallocator_t* _rawallocator,
		IJSONSAXGenerator* jsonsaxgenerator
	) noexcept(false) : StringTemplate(_rawallocator) {
		if (!jsonsaxgenerator) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplate, SubstitutionStringTemplate));
		this->vec_element = reinterpret_cast<vec_element_t*>(this->rawallocator->Allocate(sizeof(vec_element_t)));
		if (!this->vec_element) throw(YBWLIB2_EXCEPTION_CREATE_MEMORY_ALLOC_FAILURE_EXCEPTION());
		try {
			this->vec_element = ::std::launder(new (this->vec_element) vec_element_t(allocator_rawallocator_t<element_t>(this->rawallocator)));
		} catch (::std::exception& err) {
			throw(YBWLIB2_EXCEPTION_CREATE_STL_EXCEPTION_EXCEPTION(err));
		}
		SubstitutionStringTemplateConstructorJSONSAXHandler jsonsaxhandler_temp(this->rawallocator, this->vec_element);
		if (jsonsaxgenerator->IsIterative()) {
			while (!jsonsaxgenerator->IsIterativeComplete() && !jsonsaxhandler_temp.IsComplete()) {
				IException* err = jsonsaxgenerator->GenerateIterativeNext(&jsonsaxhandler_temp);
				if (err) throw(err);
			}
			if (!jsonsaxhandler_temp.IsComplete()) throw(YBWLIB2_EXCEPTION_CREATE_INVALID_PARAMETER_EXCEPTION_CLASS(::YBWLib2::SubstitutionStringTemplate, SubstitutionStringTemplate));
		} else {
			IException* err = jsonsaxgenerator->Generate(&jsonsaxhandler_temp);
			if (err) throw(err);
		}
	}

	void YBWLIB2_CALLTYPE UserInterface_RealInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<IStringTemplateParameter>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IStringTemplateParameter)), module_info_current);
		GetDynamicTypeThisClassObject<IStringTemplateParameterList>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IStringTemplateParameterList)), module_info_current);
		GetDynamicTypeThisClassObject<IStringTemplate>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(IStringTemplate)), module_info_current);
		StringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<StringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<StringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<StringTemplateParameter, IStringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(StringTemplateParameter));
		StringStringTemplateParameter::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<StringStringTemplateParameter>(),
			IsDynamicTypeModuleLocalClass<StringStringTemplateParameter>(),
			{ DynamicTypeBaseClassDef<StringStringTemplateParameter, StringTemplateParameter, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(StringStringTemplateParameter));
		StringTemplateParameterList::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<StringTemplateParameterList>(),
			IsDynamicTypeModuleLocalClass<StringTemplateParameterList>(),
			{ DynamicTypeBaseClassDef<StringTemplateParameterList, IStringTemplateParameterList, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(StringTemplateParameterList));
		StringTemplate::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<StringTemplate>(),
			IsDynamicTypeModuleLocalClass<StringTemplate>(),
			{ DynamicTypeBaseClassDef<StringTemplate, IStringTemplate, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(StringTemplate));
		FixedStringTemplate::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<FixedStringTemplate>(),
			IsDynamicTypeModuleLocalClass<FixedStringTemplate>(),
			{ DynamicTypeBaseClassDef<FixedStringTemplate, StringTemplate, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(FixedStringTemplate),
			DynamicTypeGetCreateObjectFnptr<FixedStringTemplate>(il_fnptr_create_Default_StringTemplate<FixedStringTemplate>.begin(), il_fnptr_create_Default_StringTemplate<FixedStringTemplate>.end()),
			DynamicTypeGetPlacementCreateObjectFnptr<FixedStringTemplate>(il_fnptr_create_Default_StringTemplate<FixedStringTemplate>.begin(), il_fnptr_create_Default_StringTemplate<FixedStringTemplate>.end()),
			DynamicTypeGetDefaultDeleteObjectFnptr<FixedStringTemplate>());
		SubstitutionStringTemplate::DynamicTypeThisClassObject = new DynamicTypeClassObj(
			GetDynamicTypeThisClassID<SubstitutionStringTemplate>(),
			IsDynamicTypeModuleLocalClass<SubstitutionStringTemplate>(),
			{ DynamicTypeBaseClassDef<SubstitutionStringTemplate, StringTemplate, DynamicTypeBaseClassFlag_VirtualBase> },
			0, sizeof(SubstitutionStringTemplate),
			DynamicTypeGetCreateObjectFnptr<SubstitutionStringTemplate>(il_fnptr_create_Default_StringTemplate<SubstitutionStringTemplate>.begin(), il_fnptr_create_Default_StringTemplate<SubstitutionStringTemplate>.end()),
			DynamicTypeGetPlacementCreateObjectFnptr<SubstitutionStringTemplate>(il_fnptr_placement_create_Default_StringTemplate<SubstitutionStringTemplate>.begin(), il_fnptr_placement_create_Default_StringTemplate<SubstitutionStringTemplate>.end()),
			DynamicTypeGetDefaultDeleteObjectFnptr<SubstitutionStringTemplate>());
		GetDynamicTypeThisClassObject<StringTemplateParameter>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(StringTemplateParameter)), module_info_current);
		GetDynamicTypeThisClassObject<StringStringTemplateParameter>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(StringStringTemplateParameter)), module_info_current);
		GetDynamicTypeThisClassObject<StringTemplateParameterList>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(StringTemplateParameterList)), module_info_current);
		GetDynamicTypeThisClassObject<StringTemplate>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(StringTemplate)), module_info_current);
		GetDynamicTypeThisClassObject<FixedStringTemplate>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(FixedStringTemplate)), module_info_current);
		GetDynamicTypeThisClassObject<SubstitutionStringTemplate>()->RegisterTypeInfoWrapper(wrapper_type_info_t(typeid(SubstitutionStringTemplate)), module_info_current);
	}

	void YBWLIB2_CALLTYPE UserInterface_RealUnInitModuleLocal() noexcept {
		GetDynamicTypeThisClassObject<SubstitutionStringTemplate>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<FixedStringTemplate>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<StringTemplate>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<StringTemplateParameterList>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<StringStringTemplateParameter>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<StringTemplateParameter>()->UnRegisterTypeInfoWrapper(module_info_current);
		delete SubstitutionStringTemplate::DynamicTypeThisClassObject;
		SubstitutionStringTemplate::DynamicTypeThisClassObject = nullptr;
		delete FixedStringTemplate::DynamicTypeThisClassObject;
		FixedStringTemplate::DynamicTypeThisClassObject = nullptr;
		delete StringTemplate::DynamicTypeThisClassObject;
		StringTemplate::DynamicTypeThisClassObject = nullptr;
		delete StringTemplateParameterList::DynamicTypeThisClassObject;
		StringTemplateParameterList::DynamicTypeThisClassObject = nullptr;
		delete StringStringTemplateParameter::DynamicTypeThisClassObject;
		StringStringTemplateParameter::DynamicTypeThisClassObject = nullptr;
		delete StringTemplateParameter::DynamicTypeThisClassObject;
		StringTemplateParameter::DynamicTypeThisClassObject = nullptr;
		GetDynamicTypeThisClassObject<IStringTemplate>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IStringTemplateParameterList>()->UnRegisterTypeInfoWrapper(module_info_current);
		GetDynamicTypeThisClassObject<IStringTemplateParameter>()->UnRegisterTypeInfoWrapper(module_info_current);
	}
}

#endif
