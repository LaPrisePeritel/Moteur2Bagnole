#pragma once

#include <A4Engine/Export.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <dr_wav.h>
#include <iostream>
#include <vector>
#include <A4Engine/Vector3.hpp>

class A4ENGINE_API AudioClip
{
public:
	AudioClip() = default;
	AudioClip(const AudioClip&) = default;
	AudioClip(AudioClip&& audioClip) = default;
	~AudioClip() = default;

	std::vector<std::int16_t> GetSamples() const;
	ALuint GetBuffer() const;
	ALuint GetSource() const;

	void Play();
	void Clear();

	void SetGain(float value);
	void SetLooping(bool value);
	void SetSourcePosition(Vector3f value);
	void SetSourceVelocity(Vector3f value);

	bool IsValid() const;

	AudioClip& operator=(const AudioClip&) = delete;
	AudioClip& operator=(AudioClip&& audioClip) noexcept;

	static AudioClip LoadFromFile(const char* filepath);
private:
	AudioClip(const char* filepath);

	bool isValid;

	std::vector<std::int16_t> m_samples;
	ALuint m_buffer;
	ALuint m_source;
};
