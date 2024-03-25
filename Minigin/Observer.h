#ifndef DAE_OBSERVER
#define DAE_OBSERVER

#include <tuple>

namespace dae
{
	template <class... Arguments>
	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void Notify(std::tuple<Arguments...> arguments) = 0;
 	};
}

#endif