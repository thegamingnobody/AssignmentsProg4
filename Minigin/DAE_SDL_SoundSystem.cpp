#include "SDL_mixer.h"

#include "DAE_SDL_SoundSystem.h"

#include <iostream>

class dae::DAE_SDL_SoundSystem::SDLSoundImpl
{
public:
	SDLSoundImpl() 
		: m_Chunk()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0)
		{
			std::cout << "Opened Audio Device\n";
		}
		else
		{
			std::cout << "Unable to open Audio Device, Mix error: " << Mix_GetError() << "\n";
		}
	}
	~SDLSoundImpl()
	{
		Mix_FreeChunk(m_Chunk);
	}

	void PlaySound(const SoundId, const float volume)
	{
		std::string filePath{ "../Data/Audio/Death.wav" };

		m_Chunk = Mix_LoadWAV(filePath.c_str());
		if (m_Chunk)
		{
			Mix_VolumeChunk(m_Chunk, static_cast<int>(volume * MIX_MAX_VOLUME));
			Mix_PlayChannel(-1, m_Chunk, 0);
		}
		else
		{
			std::cout << "Unable to play sound, Mix error: " << Mix_GetError() << "\n";
		}
	}
	void StopSound(const SoundId)
	{
	}
	void StopAllSounds()
	{

	}

private:
	Mix_Chunk* m_Chunk;
};


dae::DAE_SDL_SoundSystem::DAE_SDL_SoundSystem()
{
	m_Impl = std::make_unique<SDLSoundImpl>();
}

dae::DAE_SDL_SoundSystem::~DAE_SDL_SoundSystem()
{
}

void dae::DAE_SDL_SoundSystem::PlaySound(const SoundId soundId, const float volume)
{
	m_Impl->PlaySound(soundId, volume);
}

void dae::DAE_SDL_SoundSystem::StopSound(const SoundId soundId)
{
	m_Impl->StopSound(soundId);
}

void dae::DAE_SDL_SoundSystem::StopAllSounds()
{
	m_Impl->StopAllSounds();
}

void dae::DAE_SDL_SoundSystem::Notify(const Event& event)
{
	switch (event.m_type)
	{
	case EventType::PlaySound:
	{
		auto castedArguments{ event.GetArgumentsAsTuple<const unsigned short, const float>() };
		PlaySound(std::get<0>(castedArguments), std::get<1>(castedArguments));
		break;
	}
	case EventType::StopSound:
	{
		auto castedArguments{ event.GetArgumentsAsTuple<const unsigned short>() };
		StopSound(std::get<0>(castedArguments));
		break;
	}
	case EventType::StopAllSounds:
		StopAllSounds();
		break;
	}
}
