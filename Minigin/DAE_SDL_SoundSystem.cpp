#include "SDL_mixer.h"

#include "DAE_SDL_SoundSystem.h"

#include <iostream>
#include <queue>
#include <mutex>

class dae::DAE_SDL_SoundSystem::SDLSoundImpl
{
public:
	SDLSoundImpl() 
		: m_SoundThread()
		, m_SoundQueue()
		, m_Mutex()
		, m_ConditionalVar()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0)
		{
			std::cout << "Opened Audio Device\n";
		}
		else
		{
			std::cout << "Unable to open Audio Device, Mix error: " << Mix_GetError() << "\n";
		}

		m_SoundThread = std::jthread(&SDLSoundImpl::ProcessQueue, this);
	}
	~SDLSoundImpl()
	{
		//Mix_FreeChunk(m_Chunk);
	}

	void PlaySound(const SoundId soundId, const float volume)
	{
		SoundInfo soundInfo{ soundId, volume };

		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_SoundQueue.push(soundInfo);
		}
		m_ConditionalVar.notify_one();
	}
	void StopSound(const SoundId)
	{
	}
	void StopAllSounds()
	{

	}

	void ProcessQueue()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock{ m_Mutex };
			m_ConditionalVar.wait(lock, [&] { return (m_SoundQueue.size() > 0); });
			ProcessSound(m_SoundQueue.front());
			m_SoundQueue.pop();
		}

	}

private:
	void ProcessSound(SoundInfo soundInfo)
	{
		//todo: file path generator based on sound id (user geeft map mee met de id en een std string file naam?
		std::string filePath{ "../Data/Audio/Death.wav" };

		Mix_Chunk* m_Chunk = Mix_LoadWAV(filePath.c_str());

		if (m_Chunk)
		{
			Mix_VolumeChunk(m_Chunk, static_cast<int>(soundInfo.m_Volume * MIX_MAX_VOLUME));
			Mix_PlayChannel(-1, m_Chunk, 0);
		}
		else
		{
			std::cout << "Unable to play sound, Mix error: " << Mix_GetError() << "\n";
		}
	}

	std::jthread m_SoundThread;
	std::queue<SoundInfo> m_SoundQueue;
	std::mutex m_Mutex;
	std::condition_variable m_ConditionalVar;
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