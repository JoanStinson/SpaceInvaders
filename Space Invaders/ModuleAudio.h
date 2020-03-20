#ifndef _MODULEAUDIO_H_
#define _MODULEAUDIO_H_

#include "Module.h"

#include <vector>

struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

class ModuleAudio : public Module
{
public:
	ModuleAudio(bool start_enabled = true);
	~ModuleAudio();

	bool Init() override;
	bool CleanUp() override;

public:
	bool PlayMusic(const char* path, float fade_time = 2.f);
	void PauseMusic();
	void ResumeMusic();
	void StopMusic();

	unsigned int LoadSfx(const char* path);
	bool PlaySfx(unsigned int sfx, int repeat = 0);

private:
	Mix_Music* music = nullptr;
	std::vector<Mix_Chunk*>	sfxs;
};

#endif // _MODULEAUDIO_H_