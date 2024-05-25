#ifndef SYSTEM_H
#define SYSTEM_H

namespace Generic {
	namespace ECS {
		class System
		{
			virtual void init() = 0;
		};
	}
}

#endif