#pragma once

#include <A4Engine/Export.hpp>
#include <entt/fwd.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <dr_wav.h>

class A4ENGINE_API AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();

	void SetGeneralGain(float value);

private:
	ALCdevice* m_device;
	ALCcontext* m_context;
};


