#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include <vector>
#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>
#include <SDL.h>
#include <A4Engine/SDLpp.hpp>
#include <A4Engine/SDLppImGui.hpp>
#include <A4Engine/SDLppRenderer.hpp>
#include <A4Engine/SDLppTexture.hpp>
#include <A4Engine/SDLppWindow.hpp>
#include <A4Engine/ResourceManager.hpp>

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
	if (!drwav_init_file(&wav, "assets/sounds/MaenderAlkoor.wav", nullptr))
	{
		std::cout << "failed to load file" << std::endl;
		return 0;
	}

	std::vector<std::int16_t> samples(wav.totalPCMFrameCount * wav.channels);
	drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, samples.data());

	/*for (size_t i = 0; i < 44100; i++)
		samples.push_back(std::sin(float(2 * 3.14159f * i / 44100 * 850)) * 32767);*/

	alBufferData(buffer,
		(wav.channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16,
		samples.data(),
		samples.size() * sizeof(std::int16_t),
		wav.sampleRate);

	drwav_uninit(&wav);

	ALuint source;
	alGenSources(1, &source);

	alSourcei(source, AL_BUFFER, buffer);
	alSourcei(source, AL_LOOPING, AL_TRUE);

	alSource3f(source, AL_POSITION, 5.f, 0.f, 0.f);

	alListener3f(AL_POSITION, 45.f, 0.f, 0.f);

	//alSourcePlay(source);

	SDLpp sdl;

	SDLppWindow window("A4Test", 1280, 720);
	SDLppRenderer renderer(window, "", SDL_RENDERER_PRESENTVSYNC);

	ResourceManager resourceManager(renderer);

	bool isOpen = true;
	while (isOpen)
	{
		SDL_Event event;
		while (sdl.PollEvent(&event))
		{
			if (event.type == SDL_WINDOWEVENT_CLOSE)
				isOpen = false;
		}
	}

	std::getchar();

	// Libérations
	alDeleteBuffers(1, &buffer);

	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);

	alcCloseDevice(device);
}