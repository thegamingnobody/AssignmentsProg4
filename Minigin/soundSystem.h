#ifndef DAE_SOUNDSYSTEM
#define DAE_SOUNDSYSTEM

#include "Singleton.h"

namespace dae
{
	enum class SoundIds
	{
		test
	};

	class SoundSystem : public Singleton<SoundSystem>
	{
	public:
		virtual void play(const SoundIds soundId, const float volume) = 0;
		
	private:
		friend class Singleton<SoundSystem>;
		SoundSystem() = default;

	};
	
}

#endif