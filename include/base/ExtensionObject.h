/*
*
*
* Copyright (C) 2017 by Primoz Lavric
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#ifndef BASE_EXTENSION_OBJECT_H
#define BASE_EXTENSION_OBJECT_H
#include <map>
#include <memory>
#include <typeindex>
#include <functional>

namespace logi {

/**
 * @brief	Base class for Logi extension objects.
 */
class ExtensionObject {
public:
	/**
	 * @brief	Builds extension configuration and return void pointer to it.
	 *
	 * @return	Void pointer to the configuration structure.
	 */
	virtual void* build(void *next = nullptr) = 0;

	/**
	 * @brief	Create a copy of the object and return a unique pointer that points to it.
	 * 
	 * @return	Pointer to the object copy.
	 */
	virtual std::unique_ptr<ExtensionObject> clone() const = 0;

    /**
	 * @brief	Handles call with no extensions.
	 *
	 * @return	Null pointer.
	 */
	static void* buildExtensions() {
		return nullptr;
	}

    /**
     * @brief   Build the given ExtensionObject.
     *
     * @param	extension	ExtensionObject.
     * @return	Pointer to the built extension.
     */
    static void* buildExtensions(ExtensionObject& extension);

    /**
	 * @brief   Build the given ExtensionObject, link them and return the pointer to the first extension in linked list.
	 *
	 * @tparam	Args	    ExtensionObject type.
	 * @param	extension	Extension that will be built in this call.
	 * @param	extensions	Remaining extensions.
	 * @return	Pointer to the built extensions.
	 */
	template<typename... Args>
    static void* buildExtensions(ExtensionObject& extension, Args... extensions) {
		return extension.build(buildExtensions(extensions...));
    }

	/**
	 * @brief	Default virtual destructor.
	 */
	virtual ~ExtensionObject() = default;
};

/**
 * @brief   Copiable class used to wrapp ExtensionObject and make its usage easier.
 */
class ExtensionWrapper {
public:
    /**
     * @brief   Default constructor.
     */
	ExtensionWrapper() = default;

	/**
	 * @brief	Constructs and populates the structure.
	 *
	 * @param	extension		Unique pointer to the extension object.
	 * @param	comparator_fn	Comparator function used to compare extension objects.
	 */
	ExtensionWrapper(std::unique_ptr<ExtensionObject>&& extension, std::function<bool(const ExtensionObject&, const ExtensionObject&)> comparator_fn);

	/**
	 * @brief	Copy constructor that deep copies extension object.
	 *
	 * @param	rhs	Right hand side ExtensionEntry.
	 */
	ExtensionWrapper(const ExtensionWrapper& rhs);

	/**
	 * @brief	Copy assignment operator that deep copies extension object.
	 *
	 * @param	rhs	Right hand sied ExtensionEntry.
	 * @return	Reference to this.
	 */
	ExtensionWrapper& operator=(const ExtensionWrapper& rhs);

    /**
     * @brief   Compare the wrapped extensions.
     * 
     * @return  True if the wrapped extensions are equal.
     */
	bool operator==(const ExtensionWrapper& rhs) const;

	/**
     * @brief   Compare the wrapped extensions.
     *
     * @return  True if the wrapped extensions are not equal.
     */
	bool operator!=(const ExtensionWrapper& rhs) const;

    /**
     * @brief   Derefereneces the wrapped extension object.
     * 
     * @return  Pointer to extensions object.
     */
	ExtensionObject* operator->() const;

    /**
     * @brief   Retrieve pointer to the wrapped extension object.
     * 
     * @return  Pointer to extensions object.
     */
	ExtensionObject* get() const;

    /**
     * @brief   Create extension wrapper that wrapps the given extensions and creates comparator function used to compare it.
     *
     * @tparam	ExtensionType	
     * @param	extension	
     * @return	
     */
    template <typename ExtensionType>
	static ExtensionWrapper create(const ExtensionType& extension) {
        // Generate comparator.
		const std::function<bool(const ExtensionObject&, const ExtensionObject&)> comparator_fn = [](const ExtensionObject& lhs, const ExtensionObject& rhs) {
			const ExtensionType* lhs_ptr = dynamic_cast<const ExtensionType*>(&lhs);
			const ExtensionType* rhs_ptr = dynamic_cast<const ExtensionType*>(&lhs);

            // Left hand side pointer should always be of ExtensionType so there is no need to check if dynamic cast succeeded.
			return (rhs_ptr != nullptr) && (*lhs_ptr) == (*rhs_ptr);
		};

		return ExtensionWrapper(std::make_unique<ExtensionType>(extension), comparator_fn);
    }

private:
    /**
     * Unique pointer to the extensions.
     */
	std::unique_ptr<ExtensionObject> extension_;

    /**
     * Function used to compare two extension objects.
     */
	std::function<bool(const ExtensionObject&, const ExtensionObject&)> comparator_fn_; 
};


/**
 * @brief	Base class for Logi object that can be extended with ExtensionsObjects.
 */
class ExtendableObject {
public:
    virtual ~ExtendableObject() = default;
    /**
	 * @brief	Default constructor.
	 */
	ExtendableObject() = default;

	/**
	 * @brief	Compare extensions of two extendable objects.
	 *
	 * @param	rhs	Right hand side ExtendableObject.
	 * @return	True if all the extensions contain equal configuration
	 */
	bool operator==(const ExtendableObject& rhs) const;

	/**
	 * @brief	Check if the object has an extension of the given type.
	 *
	 * @tparam	ExtType	Extension type.
	 * @return	True if the extension is present.
	 */
	template <typename ExtType>
	bool hasExtension() const;

	/**
	 * @brief	Retrieve pointer to the extension of the given type.
	 *
	 * @tparam	ExtType	Extension type.
	 * @return	Pointer to the extension or null pointer if the extension is not present.
	 */
	template <typename ExtType>
	ExtType* getExtension();

	/**
	 * @brief	Add ExtensionObject to the ExtendableObject.	
	 *
	 * @tparam	ExtType		Type of the extension.
	 * @param	extension	Extension to be added.
	 */
	template <typename ExtType>
	void addExtension(const ExtType& extension);

protected:
	/**
	 * @brief	Builds all extensions and links them via next pointers.
	 *
	 * @return	Pointer to the first extension in the chain.
	 */
	void* buildExtensions() const;

private:
	std::map<std::type_index, ExtensionWrapper> extensions_;
};

template <typename ExtType>
bool ExtendableObject::hasExtension() const {
	return extensions_.find(typeid(ExtType)) != extensions_.end();
}

template <typename ExtType>
ExtType* ExtendableObject::getExtension() {
	auto it = extensions_.find(typeid(ExtType));
	
	if (it == extensions_.end()) {
		return nullptr;
	}

	return dynamic_cast<ExtType*>(it->second.get());
}

template <typename ExtType>
void ExtendableObject::addExtension(const ExtType& extension) {
	extensions_[typeid(ExtType)] = ExtensionWrapper::create(extension);
}

}

#endif