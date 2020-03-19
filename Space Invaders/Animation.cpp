#include "Animation.h"

#include <SDL_rect.h>

Animation::Animation()
{
}

Animation::Animation(int num_frames, float speed) : num_frames(num_frames), speed(speed), current_frame(0.f)
{
	frames.reserve(this->num_frames);
}

Animation::Animation(int num_frames, int size, float speed) : num_frames(num_frames), speed(speed), current_frame(0.f)
{
	frames.reserve(this->num_frames);

	for (int i = 0; i < num_frames; ++i)
		frames.push_back({ i * size, 0, size, size});
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
