#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <vector>

struct SDL_Rect;

class Animation
{
public:
	Animation();
	Animation(int num_frames, float speed = 0.5f); 
	Animation(int num_frames, int size, float speed = 0.5f);

	void AddFrame(const SDL_Rect& frame);
	SDL_Rect& GetCurrentFrame();
	SDL_Rect& GetCurrentFrameOnce();
	float GetCurrentFrameIndex() const;
	void ResetAnim();
	bool HasAnimationEnded() const;

private:
	int num_frames;

	float speed;
	float current_frame = 0.f;

	std::vector<SDL_Rect> frames;
};

#endif // _ANIMATION_H_