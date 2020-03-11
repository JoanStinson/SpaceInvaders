#ifndef _MODULEAUDIO_H_
#define _MODULEAUDIO_H_

#include "Module.h"

#include <vector>

#define FADE_TIME 2.0F

struct _Mix_Music;
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
	bool PlayMusic(const char* path, float fade_time = FADE_TIME);
	void PauseMusic();
	void ResumeMusic();
	void StopMusic();

	unsigned int LoadFx(const char* path);
	bool PlayFx(unsigned int fx, int repeat = 0);

private:
	Mix_Music* music = nullptr;
	std::vector<Mix_Chunk*>	fx;
};

#endif // _MODULEAUDIO_H_