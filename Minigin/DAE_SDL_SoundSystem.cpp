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
		, m_RunThread(true)
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
		QuitThread();
		Mix_CloseAudio();
	}

	void PlaySound(const SoundId soundId, const float volume)
	{
		SoundInfo soundInfo{ soundId, volume };

		std::scoped_lock<std::mutex> lock(m_Mutex);
		m_SoundQueue.push(soundInfo);
	}
	void StopSound(const SoundId)
	{
	}
	void StopAllSounds()
	{

	}

	void ProcessQueue()
	{
		while (m_RunThread)
		{
			if (not (m_SoundQueue.size() > 0)) continue;

			if (not m_RunThread) continue;

			auto& soundRequest{ m_SoundQueue.front() };
			m_SoundQueue.pop();

			ProcessSound(soundRequest);
		}
	}

	void QuitThread()
	{
		std::scoped_lock<std::mutex> lock(m_Mutex);
		m_RunThread = false;
	}

private:
	void ProcessSound(SoundInfo soundInfo)
	{
		//todo: file path generator based on sound id (user geeft map mee met de id en een std string file naam?
		std::string filePath{ "../Data/Audio/Death.wav" };

		Mix_Chunk* m_Chunk{ Mix_LoadWAV(filePath.c_str()) };

		if (m_Chunk)
		{
			Mix_VolumeChunk(m_Chunk, static_cast<int>(soundInfo.m_Volume * MIX_MAX_VOLUME));
			Mix_PlayChannel(-1, m_Chunk, 0);
			Mix_FreeChunk(m_Chunk);
		}
		else
		{
			std::cout << "Unable to play sound, Mix error: " << Mix_GetError() << "\n";
		}

	}

	std::jthread m_SoundThread;
	std::queue<SoundInfo> m_SoundQueue;
	std::mutex m_Mutex;
	bool m_RunThread;
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

void dae::DAE_SDL_SoundSystem::QuitThread()
{
	m_Impl->QuitThread();
}
