#ifndef DAE_SDL_SOUNDSYSTEM
#define DAE_SDL_SOUNDSYSTEM

#include "soundSystem.h"
#include <memory>

namespace dae
{
	class DAE_SDL_SoundSystem final : public SoundSystem
	{
	public:
		DAE_SDL_SoundSystem();
		~DAE_SDL_SoundSystem() override;

		DAE_SDL_SoundSystem(const DAE_SDL_SoundSystem& other) = delete;
		DAE_SDL_SoundSystem(DAE_SDL_SoundSystem&& other) = delete;
		DAE_SDL_SoundSystem& operator=(const DAE_SDL_SoundSystem& other) = delete;
		DAE_SDL_SoundSystem& operator=(DAE_SDL_SoundSystem&& other) = delete;

		void PlaySound(const SoundId soundId, const float volume) override;
		void StopSound(const SoundId soundId) override;
		void StopAllSounds() override;

	private:
		class SDLSoundImpl;
		std::unique_ptr<SDLSoundImpl> m_Impl;
	};
}

#endif