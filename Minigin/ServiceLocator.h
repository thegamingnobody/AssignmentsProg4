#ifndef DAE_SERVICELOCATOR
#define DAE_SERVICELOCATOR

#include <memory>
#include "soundSystem.h"

namespace dae
{
	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem() { return *m_SoundSystemInstance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem) 
		{
			if (soundSystem != nullptr)
			{
				m_SoundSystemInstance = std::move(soundSystem); 
			}
		}
	private:
		static std::unique_ptr<SoundSystem> m_SoundSystemInstance;
	};

}


#endif