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

	void AddFrame(SDL_Rect frame);
	SDL_Rect& GetCurrentFrame();
	SDL_Rect& GetCurrentFrameOnce();
	float GetCurrentFrameIndex() const;
	void ResetAnim();
	bool HasAnimationEnded() const;

private:
	float speed;
	float current_frame;
public:
	std::vector<SDL_Rect> frames;
	int num_frames;
};

#endif // _ANIMATION_H_