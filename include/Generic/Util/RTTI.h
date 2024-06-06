#ifndef GENERIC_RTTI_H
#define GENERIC_RTTI_H

#include <typeinfo>
#include <string>
#include "Generic/Util/VLUI64.h"

namespace Generic {
	class GRTTI {
	public:
		template <typename T>
		static std::string typeName() {
			static std::string&& name = typeid(T).name();
			static std::string TypeName = name.erase(0, 6);
			return TypeName;
		}

		template <typename T>
		static int typeId() {
			static int typeID = typeIDCount++;
			return typeID;
		}

		template <typename T>
		static VLUI64 typeMask() {
			static VLUI64&& TypeMask = VLUI64(typeId<T>());
			return TypeMask;
		}

		static VLUI64 typeMask(int typeId) {
			static VLUI64&& TypeMask = VLUI64(typeId);
			return TypeMask;
		}

	private:
		static int typeIDCount;
	};
}

#endif 