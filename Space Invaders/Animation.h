#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <vector>

struct SDL_Rect;

class Animation
{
public:
	Animation(int num_frames, float speed = 0.1F); 

	void AddFrame(SDL_Rect frame);
	SDL_Rect& GetCurrentFrame();
	float GetCurrentFrameIndex() const;
	void ResetAnim();

private:
	float speed;
	float current_frame;
	std::vector<SDL_Rect> frames;
};

#endif // _ANIMATION_H_