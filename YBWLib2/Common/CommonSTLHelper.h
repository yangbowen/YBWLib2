#pragma once
#include <type_traits>
#include <atomic>
#include <memory>
#include <mutex>
#include <ostream>
#include "Common.h"

namespace YBWLib2 {
	/// <summary>
	/// Reference counted object.
	/// Has a reference count of <c>1</c> when constructed.
	/// </summary>
	class ReferenceCountedObject abstract : public virtual IReferenceCountedObject {
	public:
		inline virtual ~ReferenceCountedObject() = default;
		/// <summary>
		/// Increments the reference count.
		/// This function is thread-safe.
		/// </summary>
		/// <returns>The new reference count.</returns>
		inline virtual uintptr_t IncReferenceCount() const override {
			if (this) {
				uintptr_t ret = ++this->ref_count;
				return ret;
			}
		}
		/// <summary>
		/// Decrements the reference count.
		/// Frees the object if the reference count reaches <c>0</c>.
		/// This function is thread-safe.
		/// </summary>
		/// <returns>The new reference count.</returns>
		inline virtual uintptr_t DecReferenceCount() const override {
			if (this) {
				uintptr_t ret = --this->ref_count;
				if (!ret) const_cast<ReferenceCountedObject*>(this)->DeleteMe();
				return ret;
			}
		}
	protected:
		/// <summary>
		/// Destructs the object and frees any resources allocated for the object.
		/// This function is intended to be called only by <c>DecReferenceCount</c>.
		/// </summary>
		inline virtual void DeleteMe() = 0;
	private:
		mutable ::std::atomic<uintptr_t> ref_count = 1;
	};

	/// <summary>
	/// Reference counted object that keeps an STL shared pointer of itself.
	/// Objects of this class must be managed by an STL shared pointer before <c>IncReferenceCount</c> is called.
	/// Has a reference count of <c>0</c> when constructed.
	/// </summary>
	/// <typeparam name="_Concrete_Class_Ty">The concrete class that inherits from this class.</typeparam>
	template<typename _Concrete_Class_Ty>
	class SharedPtrReferenceCountedObject abstract
		: public virtual ::std::enable_shared_from_this<_Concrete_Class_Ty>,
		public virtual IReferenceCountedObject {
	public:
		inline virtual ~SharedPtrReferenceCountedObject() = default;
		/// <summary>
		/// Increments the reference count.
		/// This function is thread-safe.
		/// </summary>
		/// <returns>The new reference count.</returns>
		inline virtual uintptr_t IncReferenceCount() const override {
			if (this) {
				::std::lock_guard<::std::mutex> lock_guard_this(this->mtx_this);
				uintptr_t ret = ++this->ref_count;
				if (ret == 1) {
					// The reference count is incremented from 0.
					// Keep a shared pointer of *this to prevent destruction.
					ptr = this->shared_from_this();
				}
				return ret;
			}
		}
		/// <summary>
		/// Decrements the reference count.
		/// Permits the object to be freed if the reference count reaches <c>0</c>.
		/// This function is thread-safe.
		/// </summary>
		/// <returns>The new reference count.</returns>
		inline virtual uintptr_t DecReferenceCount() const override {
			if (this) {
				::std::unique_lock<::std::mutex> unique_lock_this(this->mtx_this);
				uintptr_t ret = --this->ref_count;
				if (!ret) {
					// The reference count is decremented to 0.
					// If the shared pointer keeped is unique, *this, including this->mtx_this, will be destructed after clearing the shared pointer,
					// so unique_lock_this must stop owning this->mtx_this before clearing the shared pointer.
					// If the shared pointer keeped is not unique, other threads holding shared pointers to this object may access this->ref_count and/or this->ptr,
					// so unique_lock_this must lock this->mtx_this until after clearing the shared pointer.
					if (ptr.unique()) unique_lock_this = ::std::unique_lock<::std::mutex>();
					// Clear the shared pointer.
					ptr = ::std::shared_ptr<_Concrete_Class_Ty>();
				}
				return ret;
			}
		}
	private:
		mutable ::std::mutex mtx_this;
		mutable uintptr_t ref_count = 0;
		mutable ::std::shared_ptr<_Concrete_Class_Ty> ptr;
	};

	/// <summary>
	/// Reference counted object holder.
	/// Counts as one reference of the owned object until destructed.
	/// </summary>
	/// <typeparam name="_Element_Ty">The type of the object objects of this class dereferences to.</typeparam>
	template<typename _Element_Ty>
	class ReferenceCountedObjectHolder {
	public:
		struct inc_ref_count_t {};
		struct adopt_ref_count_t {};

		constexpr inc_ref_count_t inc_ref_count {};
		constexpr adopt_ref_count_t adopt_ref_count {};

		using element_type = _Element_Ty;
		constexpr ReferenceCountedObjectHolder() noexcept {}
		constexpr ReferenceCountedObjectHolder(nullptr_t) noexcept : ReferenceCountedObjectHolder() {}
		/// <summary>
		/// Constructs a <c>ReferenceCountedObjectHolder</c> that manages the object the specified pointer points to, incrementing the object's reference count.
		/// Use this function on an existing pointer that has no reference counts reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline explicit ReferenceCountedObjectHolder(_Element_From_Ty* p, inc_ref_count_t) {
			if (p) {
				const IReferenceCountedObject* _ptr_owned = p;
				_ptr_owned->IncReferenceCount();
				this->ptr_stored = p;
				this->ptr_owned = _ptr_owned;
			}
		}
		/// <summary>
		/// Constructs a <c>ReferenceCountedObjectHolder</c> that manages the object the specified pointer points to, without changing the object's reference count.
		/// Use this function on a freshly obtained pointer that has one reference count reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline explicit ReferenceCountedObjectHolder(_Element_From_Ty*&& p, adopt_ref_count_t) {
			if (p) {
				this->ptr_stored = p;
				this->ptr_owned = p;
			}
		}
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline ReferenceCountedObjectHolder(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) {
			if (x.ptr_owned) {
				x.ptr_owned->IncReferenceCount();
				this->ptr_owned = x.ptr_owned;
			}
			if (x.ptr_stored) this->ptr_stored = x.ptr_stored;
		}
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline ReferenceCountedObjectHolder(ReferenceCountedObjectHolder<_Element_From_Ty>&& x) {
			if (x.ptr_stored) this->ptr_stored = x.ptr_stored;
			this->ptr_owned = x.ptr_owned;
			x.ptr_stored = nullptr;
			x.ptr_owned = nullptr;
		}
		template<typename _Element_From_Ty>
		inline ReferenceCountedObjectHolder(const ReferenceCountedObjectHolder<_Element_From_Ty>& x, _Element_Ty* p) {
			const IReferenceCountedObject* _ptr_owned = x.ptr_owned;
			if (_ptr_owned) {
				_ptr_owned->IncReferenceCount();
				this->ptr_owned = _ptr_owned;
			}
			if (p) this->ptr_stored = p;
		}
		inline ReferenceCountedObjectHolder(const ReferenceCountedObjectHolder& x) {
			if (x.ptr_owned) {
				x.ptr_owned->IncReferenceCount();
				this->ptr_owned = x.ptr_owned;
			}
			this->ptr_stored = x.ptr_stored;
		}
		inline ReferenceCountedObjectHolder(ReferenceCountedObjectHolder&& x) {
			this->ptr_stored = x.ptr_stored;
			this->ptr_owned = x.ptr_owned;
			x.ptr_stored = nullptr;
			x.ptr_owned = nullptr;
		}
		inline virtual ~ReferenceCountedObjectHolder() {
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			if (_ptr_owned) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
		}
		inline _Element_Ty* get() const noexcept { return this->ptr_stored; }
		inline explicit operator bool() const noexcept { return this->ptr_stored; }
		inline _Element_Ty& operator*() const noexcept { return *this->ptr_stored; }
		inline _Element_Ty* operator->() const noexcept { return this->ptr_stored; }
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline ReferenceCountedObjectHolder& operator=(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) noexcept {
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			if (_ptr_owned) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
			if (x.ptr_owned) {
				x.ptr_owned->IncReferenceCount();
				this->ptr_owned = x.ptr_owned;
			}
			if (x.ptr_stored) this->ptr_stored = x.ptr_stored;
		}
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline ReferenceCountedObjectHolder& operator=(ReferenceCountedObjectHolder<_Element_From_Ty>&& x) noexcept {
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			if (_ptr_owned) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
			if (x.ptr_stored) this->ptr_stored = x.ptr_stored;
			this->ptr_owned = x.ptr_owned;
			x.ptr_stored = nullptr;
			x.ptr_owned = nullptr;
		}
		inline ReferenceCountedObjectHolder& operator=(const ReferenceCountedObjectHolder& x) noexcept {
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			if (_ptr_owned) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
			if (x.ptr_owned) {
				x.ptr_owned->IncReferenceCount();
				this->ptr_owned = x.ptr_owned;
			}
			this->ptr_stored = x.ptr_stored;
		}
		inline ReferenceCountedObjectHolder& operator=(ReferenceCountedObjectHolder&& x) noexcept {
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			if (_ptr_owned) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
			this->ptr_stored = x.ptr_stored;
			this->ptr_owned = x.ptr_owned;
			x.ptr_stored = nullptr;
			x.ptr_owned = nullptr;
		}
		inline bool owner_before(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) const { return this->ptr_owned < x.ptr_owned; }
		inline void reset() noexcept {}
		/// <summary>
		/// Makes this object manages the object the specified pointer points to, incrementing the later object's reference count.
		/// Use this function on an existing pointer that has no reference counts reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline void reset(_Element_From_Ty* p, inc_ref_count_t) {
			const IReferenceCountedObject* _ptr_owned_old = this->ptr_owned;
			if (_ptr_owned_old) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned_old->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
			if (p) {
				const IReferenceCountedObject* _ptr_owned = p;
				_ptr_owned->IncReferenceCount();
				this->ptr_stored = p;
				this->ptr_owned = _ptr_owned;
			}
		}
		/// <summary>
		/// Makes this object manage the object the specified pointer points to, without changing the later object's reference count.
		/// Use this function on a freshly obtained pointer that has one reference count reserved for the caller.
		/// </summary>
		template<typename _Element_From_Ty, ::std::enable_if_t<::std::is_convertible_v<_Element_From_Ty*, _Element_Ty*>, int> = 0>
		inline void reset(_Element_From_Ty*&& p, adopt_ref_count_t) {
			const IReferenceCountedObject* _ptr_owned_old = this->ptr_owned;
			if (_ptr_owned_old) {
				this->ptr_stored = nullptr;
				this->ptr_owned = nullptr;
				_ptr_owned_old->DecReferenceCount();
			} else {
				this->ptr_stored = nullptr;
			}
			if (p) {
				this->ptr_stored = p;
				this->ptr_owned = p;
			}
		}
		inline void swap(ReferenceCountedObjectHolder& x) noexcept {
			_Element_Ty* _ptr_stored = this->ptr_stored;
			const IReferenceCountedObject* _ptr_owned = this->ptr_owned;
			this->ptr_stored = x.ptr_stored;
			this->ptr_owned = x.ptr_owned;
			x.ptr_stored = _ptr_stored;
			x.ptr_owned = _ptr_owned;
		}
	private:
		_Element_Ty* ptr_stored = nullptr;
		const IReferenceCountedObject* ptr_owned = nullptr;
	};
	template<typename _Char_Ty, typename _Traits_Ty, typename _Element_Ty>
	inline ::std::basic_ostream<_Char_Ty, _Traits_Ty>& operator<<(::std::basic_ostream<_Char_Ty, _Traits_Ty>& os, const ReferenceCountedObjectHolder<_Element_Ty>& x) {
		return os << x.get();
	}
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator==(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() == r.get(); }
	template<typename _Element_Ty>
	inline bool operator==(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr == r.get(); }
	template<typename _Element_Ty>
	inline bool operator==(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() == nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator!=(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() != r.get(); }
	template<typename _Element_Ty>
	inline bool operator!=(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr != r.get(); }
	template<typename _Element_Ty>
	inline bool operator!=(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() != nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator<(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() < r.get(); }
	template<typename _Element_Ty>
	inline bool operator<(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr < r.get(); }
	template<typename _Element_Ty>
	inline bool operator<(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() < nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator<=(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() <= r.get(); }
	template<typename _Element_Ty>
	inline bool operator<=(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr <= r.get(); }
	template<typename _Element_Ty>
	inline bool operator<=(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() <= nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator>(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() > r.get(); }
	template<typename _Element_Ty>
	inline bool operator>(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr > r.get(); }
	template<typename _Element_Ty>
	inline bool operator>(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() > nullptr; }
	template<typename _Element_L_Ty, typename _Element_R_Ty>
	inline bool operator>=(const ReferenceCountedObjectHolder<_Element_L_Ty>& l, const ReferenceCountedObjectHolder<_Element_R_Ty>& r) { return l.get() >= r.get(); }
	template<typename _Element_Ty>
	inline bool operator>=(nullptr_t, const ReferenceCountedObjectHolder<_Element_Ty>& r) { return nullptr >= r.get(); }
	template<typename _Element_Ty>
	inline bool operator>=(const ReferenceCountedObjectHolder<_Element_Ty>& l, nullptr_t) { return l.get() >= nullptr; }
	template<typename _Element_Ty>
	inline void swap(ReferenceCountedObjectHolder<_Element_Ty>& l, ReferenceCountedObjectHolder<_Element_Ty>& r) { l.swap(r); }
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ReferenceCountedObjectHolder<_Element_To_Ty> static_pointer_cast(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) {
		return x ? ReferenceCountedObjectHolder<_Element_To_Ty>(x, static_cast<_Element_To_Ty*>(x.get())) : ReferenceCountedObjectHolder<_Element_To_Ty>();
	}
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ReferenceCountedObjectHolder<_Element_To_Ty> const_pointer_cast(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) {
		return x ? ReferenceCountedObjectHolder<_Element_To_Ty>(x, const_cast<_Element_To_Ty*>(x.get())) : ReferenceCountedObjectHolder<_Element_To_Ty>();
	}
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ReferenceCountedObjectHolder<_Element_To_Ty> reinterpret_pointer_cast(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) {
		return x ? ReferenceCountedObjectHolder<_Element_To_Ty>(x, reinterpret_cast<_Element_To_Ty*>(x.get())) : ReferenceCountedObjectHolder<_Element_To_Ty>();
	}
	template<typename _Element_To_Ty, typename _Element_From_Ty>
	inline ReferenceCountedObjectHolder<_Element_To_Ty> dynamic_pointer_cast(const ReferenceCountedObjectHolder<_Element_From_Ty>& x) {
		if (x) {
			_Element_To_Ty* p = dynamic_cast<_Element_To_Ty*>(x.get());
			if (p) {
				return ReferenceCountedObjectHolder<_Element_To_Ty>(x, p);
			}
		}
		return ReferenceCountedObjectHolder<_Element_To_Ty>();
	}

	/// <summary>An object that implements <c>ILockableObject</c> and wraps an STL <c>Lockable</c> object.</summary>
	/// <typeparam name="_Ty">The type of the wrapped object.</typeparam>
	template<typename _Ty>
	class LockableObjectFromSTLWrapper : public virtual ILockableObject {
	public:
		using wrapped_type = _Ty;
		template<typename _Args_Ty...>
		inline explicit LockableObjectFromSTLWrapper(_Args_Ty... args) : obj(::std::forward<_Args_Ty>(args)...) {}
		inline virtual ~LockableObjectFromSTLWrapper() = default;
		/// <summary>Get a reference to the wrapped object.</summary>
		inline ::std::remove_reference_t<_Ty>& GetWrappedLockableObject() { return this->obj; }
		/// <summary>Get a reference to the wrapped object.</summary>
		inline const ::std::remove_reference_t<_Ty>& GetWrappedLockableObject() const { return this->obj; }
		/// <summary>Locks the object. Blocks if necessary.</summary>
		inline virtual void Lock() override { this->obj.lock(); }
		/// <summary>Tries to lock the object. Fail immediately if it's already locked by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		inline virtual bool TryLock() override { return this->obj.try_lock(); }
		/// <summary>Unlocks the object.</summary>
		inline virtual void Unlock() override noexcept { this->obj.unlock(); }
	private:
		_Ty obj;
	};

	/// <summary>An object that wraps a reference to an <c>ILockableObject</c> object and behaves like an STL <c>Lockable</c> object.</summary>
	class LockableObjectToSTLWrapper {
	public:
		inline explicit LockableObjectToSTLWrapper(ILockableObject& x) : obj(x) {}
		inline virtual ~LockableObjectToSTLWrapper() = default;
		/// <summary>Get a reference to the wrapped object.</summary>
		inline ILockableObject& GetWrappedLockableObject() const { return this->obj; }
		/// <summary>Locks the object. Blocks if necessary.</summary>
		inline virtual void lock() { this->obj.Lock(); }
		/// <summary>Tries to lock the object. Fail immediately if it's already locked by another thread.</summary>
		/// <returns>
		/// Returns <c>true</c> if the object is successfully locked.
		/// Returns <c>false</c> if the object isn't successfully locked.
		/// </returns>
		inline virtual bool try_lock() { return this->obj.TryLock(); }
		/// <summary>Unlocks the object.</summary>
		inline virtual void unlock() noexcept { this->obj.Unlock(); }
	private:
		ILockableObject& obj;
	};
}
