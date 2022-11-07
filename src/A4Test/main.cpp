#include <AL/al.h>
#include <AL/alc.h>
#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>
#include <iostream>
#include <string>
#include <vector>

int main()
{
	const char* deviceList = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
	std::vector<std::string> devices;
	while (true)
	{
		std::size_t length = std::strlen(deviceList);
		if (length == 0)
			break;

		devices.emplace_back(deviceList, length);

		deviceList += length + 1;
	}

	ALCdevice* device = alcOpenDevice(nullptr);

	ALCcontext* context = alcCreateContext(device, nullptr);
	alcMakeContextCurrent(context);

	ALuint buffer;
	alGenBuffers(1, &buffer);

	// On va faire des trucs !
	drwav wav;
	if (!drwav_init_file(&wav, "assets/MaenderAlkoor.wav", nullptr))
	{
		std::cout << "failed to load file" << std::endl;
		return 0;
	}

	std::vector<std::int16_t> samples(wav.totalPCMFrameCount * wav.channels);
	drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, samples.data());

	alBufferData(buffer, (wav.channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, samples.data(), samples.size(), wav.sampleRate);

	drwav_uninit(&wav);

	ALuint source;
	alGenSources(1, &source);

	alSourcei(source, AL_BUFFER, buffer);
	alSourcei(source, AL_LOOPING, AL_TRUE);
	alSourcePlay(source);

	std::getchar();

	// Libération
	alDeleteBuffers(1, &buffer);

	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);

	alcCloseDevice(device);
}