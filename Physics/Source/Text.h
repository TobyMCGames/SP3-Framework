#ifndef TEXT_H
#define TEXT_H
#include "Vector3.h"
#include "Dialogue.h"

class Text
{
private:
	Dialogue::CONVO_SENTENCES boundDialogue;
	Vector3 position;
	int DetectionRange;
	bool active;

public:
	Text();
	~Text();
	Dialogue::CONVO_SENTENCES getBoundDialogue();
	void setDialogue(Dialogue::CONVO_SENTENCES boundDialogue);	
	Vector3 getPos();
	void setPos(Vector3 position);
	void setDetectionRange(int DetectionRange);
	int getDetectionRange();
	bool getActive();
	void setActive(bool active);

};
#endif