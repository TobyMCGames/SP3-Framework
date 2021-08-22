#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(int row, int col)
	: sprite(nullptr)
	, row(row)
	, col(col)
	, currentTime(0)
	, currentFrame(0)
	, playCount(0)
	, currentAnimation("")
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
SpriteAnimation::~SpriteAnimation()
{
	//Loop through the animation list
	for (auto iter = animationList.begin(); iter != animationList.end(); ++iter)
	{
		if (iter->second != NULL)
		{
			//delete the animation
			delete iter->second;
		}
	}
	//Remove everything
	animationList.clear();
}

/******************************************************************************/
/*!
\brief
Update the current frame of the current animation

param dt - the delta time

\exception None
\return None
*/
/******************************************************************************/
void SpriteAnimation::Update(double dt)
{
	//Check if the current animation is active
	if (animationList[currentAnimation]->animActive)
	{
		//Add the delta time
		currentTime += static_cast<float>(dt);

		//Get the number of frame to get the frame per second
		int numFrame = animationList[currentAnimation]->frames.size();
		float frameTime = animationList[currentAnimation]->animTime / numFrame;

		//Set the current frame based on the current time
		currentFrame = animationList[currentAnimation]->frames[fmin((int)animationList[currentAnimation]->frames.size() - 1, static_cast<int>(currentTime / frameTime))];

		//check if the current time is more than the total animated time
		if (currentTime >= animationList[currentAnimation]->animTime)
		{
			//if it is less than the repeat count, increase the count and repeat
			if (playCount < animationList[currentAnimation]->repeatCount)
			{
				++playCount;
				currentTime = 0;
				currentFrame = animationList[currentAnimation]->frames[0];
			}
			//if we repeat count is 0 or we have reach same number of play count
			else
			{
				animationList[currentAnimation]->animActive = false;
				animationList[currentAnimation]->ended = true;
			}

			//If the animaton is infinite
			if (animationList[currentAnimation]->repeatCount == -1)
			{
				currentTime = 0.f;
				currentFrame = animationList[currentAnimation]->frames[0];
				animationList[currentAnimation]->animActive = true;
				animationList[currentAnimation]->ended = false;
			}
		}
	}
}

/******************************************************************************/
/*!
\brief
Render the Sprite Animation

param None

\exception None
\return None
*/
/******************************************************************************/
void SpriteAnimation::Render()
{
	
}

/******************************************************************************/
/*!
\brief
Add an animation to the Sprite Animation by defining the start and the end

param anim_name - the name of the animation

param start - the starting frame based on the sprite sheet

param end - the ending frame based on the sprite sheet

\exception None
\return None
*/
/******************************************************************************/
void SpriteAnimation::AddAnimation(std::string anim_name, int start, int end)
{
	CAnimation* anim = new CAnimation();

	//Check if start is more than end
	//Swap over if it is
	if (start > end)
		std::swap(start, end);

	//Add in all the frames in the range
	for (int i = start; i <= end; ++i)
	{
		anim->AddFrame(i);
	}

	//Link the animation to the animation list
	animationList[anim_name] = anim;
	//Set the current animation if it does not exisit
	if (currentAnimation == "")
	{
		currentAnimation = anim_name;
	}
	animationList[anim_name]->animActive = false;
}

/******************************************************************************/
/*!
\brief
Add an animation to the Sprite Animation by defining the frame values

param anim_name - the name of the animation

param count - the number of frame in the animation

param ... - the frames

\exception None
\return None
*/
/******************************************************************************/
void SpriteAnimation::AddSequeneAnimation(std::string anim_name, int count ...)
{
	CAnimation* anim = new CAnimation();

	va_list args;
	va_start(args, count);
	//Add the frames based on the input
	for (int i = 0; i < count; ++i)
	{
		int value = va_arg(args, int);
		anim->AddFrame(value);
	}
	va_end(args);

	//Link the animation to the animation list
	animationList[anim_name] = anim;
	//Set the current animation if it does not exisit
	if (currentAnimation == "")
	{
		currentAnimation = anim_name;
	}
	animationList[anim_name]->animActive = false;
}

/******************************************************************************/
/*!
\brief
Play the animation based on the given name

param anim_name - the name of the animation

param repeat - the number of repeats (-1 for infinite looping)

param time - the total time of the animation

\exception None
\return None
*/
/******************************************************************************/
void SpriteAnimation::PlayAnimation(std::string anim_name, int repeat, float time)
{
	//Check if the anim name exist 
	if (animationList[anim_name] != nullptr)
	{
		currentAnimation = anim_name;
		animationList[anim_name]->Set(repeat, time, true);
	}
}

/******************************************************************************/
/*!
\brief
Resume the current animation if it is Paused

\exception None
\return None
*/
/******************************************************************************/
void SpriteAnimation::Resume()
{
	animationList[currentAnimation]->animActive = true;
}

/******************************************************************************/
/*!
\brief
Pause the current animation

\exception None
\return None
*/
/******************************************************************************/
void SpriteAnimation::Pause()
{
	animationList[currentAnimation]->animActive = false;
}

/******************************************************************************/
/*!
\brief
Reset the current animation

\exception None
\return None
*/
/******************************************************************************/
void SpriteAnimation::Reset()
{
	currentFrame = animationList[currentAnimation]->frames[0];
	playCount = 0;
}