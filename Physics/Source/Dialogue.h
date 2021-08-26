#include <iostream>
#include <vector>
class Dialogue
{
public:
	enum CONVO_SENTENCES
	{
		SENTENCE_START =0,
		LEVEL_1_START =1,
		LEVEL_1_END =2,
		LEVEL_4_START =3,
		LEVEL_4_GREETINGS =4,
		/*LEVEL_4_STORY_1 =5,
		LEVEL_4_STORY_2 =6,
		LEVEL_4_END = 7,*/
		TOTAL_SENTENCE,
	};	

	const int TextSpeed = 60;
	const int maxtimer = 60;
	Dialogue();
	~Dialogue();
	bool LoadDialogue(std::string filename);
	void playDialogue(CONVO_SENTENCES currentSceneConvo,int convoindex);
	int getcurrentTextIndex();
	void setcurrenTextIndex(int currentTextIndex);
	bool getActive();
	void setActive(bool Active);
	void Update(double dt);
	void setcurrentSceneConvo(int currentSceneConvo);
	int getcurrentSceneConvo();
	std::string getCurrentText();

private:
	// vector that stores all the sentences 
	std::vector<std::vector<std::string>> dialogueList;
	// current sentence
	std::string currentText;
	// current letter
	int currentTextIndex;
	// if active then it will be updating.
	bool Active;

	// indicator to show which conversation we are having
	int currentSceneConvo;
	// indicator to show which sentence is being played
	int currentcovoIndex;
	// time until the next letter gets rendered.
	int textTimer;
};