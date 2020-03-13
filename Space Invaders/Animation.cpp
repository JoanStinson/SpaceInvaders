#include "Animation.h"

#include <SDL.h>

Animation::Animation(int num_frames, float speed) : frames(), speed(speed), current_frame(0.f)
{
	frames.reserve(num_frames);
}

void Animation::AddFrame(SDL_Rect frame)
{
	frames.push_back(frame);
}

SDL_Rect& Animation::GetCurrentFrame()
{
	current_frame += speed;

	if (current_frame >= frames.size())
		current_frame = 0.f;

	return frames[(int)current_frame];
}

float Animation::GetCurrentFrameIndex() const
{
	return current_frame;
}

void Animation::ResetAnim()
{
	current_frame = 0;
}
