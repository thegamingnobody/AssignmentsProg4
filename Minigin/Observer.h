#ifndef DAE_OBSERVER
#define DAE_OBSERVER

#include <tuple>
#include <any>

namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() {};

		virtual void Notify(std::any arguments) = 0;
 	};
}

#endif