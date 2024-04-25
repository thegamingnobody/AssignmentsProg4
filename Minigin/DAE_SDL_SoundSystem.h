#ifndef DAE_SDL_SOUNDSYSTEM
#define DAE_SDL_SOUNDSYSTEM

#include "soundSystem.h"
#include <memory>

namespace dae
{
	class DAE_SDL_SoundSystem : public SoundSystem
	{
	public:
		void play(const SoundIds soundId, const float volume) override;
	private:
		class SDLSoundImpl;
		std::unique_ptr<SDLSoundImpl> m_Impl;
	};
}

#endif