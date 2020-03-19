#include "Animation.h"

#include <SDL_rect.h>

Animation::Animation(int num_frames, float speed) : frames(), speed(speed), current_frame(0.f), num_frames(num_frames)
{
	frames.reserve(this->num_frames);
}

void Animation::AddFrame(SDL_Rect frame)
{
	frames.push_back(frame);
}

SDL_Rect& Animation::GetCurrentFrame()//TODO pass deltatimehere
{
	current_frame += speed;

	if (current_frame >= frames.size())
		current_frame = 0.f;

	return frames[(int)current_frame];
}

SDL_Rect& Animation::GetCurrentFrameOnce()
{
	current_frame += speed;

	if (current_frame >= frames.size())
		return frames[num_frames-1];

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

bool Animation::HasAnimationEnded() const
{
	return current_frame >= frames.size();
}
