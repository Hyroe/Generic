#ifndef GENERIC_RTTI_H
#define GENERIC_RTTI_H

#include <typeinfo>
#include <string>
#include "Generic/Util/Util.h"
#include "Generic/Util/VLUI64.h"

namespace Generic {
		class GRTTI {
		public:
			template <typename T>
			static std::string typeName() {
				static std::string TypeName(typeid(T).name());
				static bool called = false;
				if (called == false)
					TypeName.erase(0, 6);
				else 
					return TypeName;
				called = true;
				return TypeName;
			}

			static Util::VLUI64 typeMask(std::uint64_t typeId) {
				static Util::VLUI64 TypeMask;
				static bool called = false;
				if (called == false)
					TypeMask.set(typeId);
				else
					return TypeMask;
				called = true;
				return TypeMask;
			}
		};
}

#endif 