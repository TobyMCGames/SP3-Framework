#include "Text.h"

Text::Text():
	boundDialogue(Dialogue::CONVO_SENTENCES::SENTENCE_START),
	position(0,0,0),
	DetectionRange(1),
	active(true)
{
}

Text::~Text()
{
}

Dialogue::CONVO_SENTENCES Text::getBoundDialogue()
{
	return boundDialogue;
}

void Text::setDialogue(Dialogue::CONVO_SENTENCES boundDialogue)
{
	this->boundDialogue = boundDialogue;
}

Vector3 Text::getPos()
{
	return position;
}

void Text::setPos(Vector3 position)
{
	this->position = position;
}

void Text::setDetectionRange(int DetectionRange)
{
	this->DetectionRange = DetectionRange;
}

int Text::getDetectionRange()
{
	return DetectionRange;
}

bool Text::getActive()
{
	return active;
}

void Text::setActive(bool active)
{
	this->active = active;
}

