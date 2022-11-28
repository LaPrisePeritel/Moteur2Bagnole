#include <A4Engine/AudioSystem.hpp>

AudioSystem::AudioSystem()
{
	m_device = alcOpenDevice(nullptr);

	m_context = alcCreateContext(m_device, nullptr);
	alcMakeContextCurrent(m_context);

	alListener3f(AL_POSITION, 0.f, 0.f, 0.f);
}

AudioSystem::~AudioSystem()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(m_context);

	alcCloseDevice(m_device);
}

void AudioSystem::SetGeneralGain(float value)
{
	alListenerf(AL_GAIN, value);
}
