#include <A4Engine/AudioClip.hpp>

AudioClip::AudioClip(const char* filepath)
{
	drwav wav;
	if (!drwav_init_file(&wav, filepath, nullptr))
	{
		std::cout << "failed to load file" << std::endl;
		isValid = false;
		return;
	}

	m_samples = std::vector<std::int16_t>(wav.totalPCMFrameCount * wav.channels);
	drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, m_samples.data());
	
	alGenBuffers(1, &m_buffer);

	alBufferData(m_buffer,
		(wav.channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16,
		m_samples.data(),
		m_samples.size() * sizeof(std::int16_t),
		wav.sampleRate);

	alGenSources(1, &m_source);
	alSourcei(m_source, AL_BUFFER, m_buffer);

	drwav_uninit(&wav);
	isValid = true;
}

std::vector<std::int16_t> AudioClip::GetSamples() const
{
	return m_samples;
}

ALuint AudioClip::GetBuffer() const
{
	return m_buffer;
}

ALuint AudioClip::GetSource() const
{
	return m_source;
}

void AudioClip::Play()
{
	alSourcePlay(m_source);
}

void AudioClip::Clear()
{
	alDeleteBuffers(1, &m_buffer);
	alDeleteSources(1, &m_source);
}

void AudioClip::SetGain(float value)
{
	alSourcef(m_source, AL_GAIN, value);
}

void AudioClip::SetLooping(bool value)
{
	alSourcei(m_source, AL_LOOPING, value);
}

void AudioClip::SetSourcePosition(Vector3f value)
{
	alSource3f(m_source, AL_POSITION, value.x, value.y, value.z);
}

void AudioClip::SetSourceVelocity(Vector3f value)
{
	alSource3f(m_source, AL_VELOCITY, value.x, value.y, value.z);
}

AudioClip AudioClip::LoadFromFile(const char* filepath)
{
	return AudioClip(filepath);
}

bool AudioClip::IsValid() const
{
	return isValid;
}

AudioClip& AudioClip::operator=(AudioClip&& audioClip) noexcept
{
	m_samples = std::move(audioClip.m_samples);
	m_buffer = std::move(audioClip.m_buffer);
	m_source = std::move(audioClip.m_source);

	return *this;
}
