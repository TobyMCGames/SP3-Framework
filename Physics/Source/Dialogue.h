#include <iostream>
#include <vector>
class Dialogue
{
public:
	enum CONVO_SENTENCES
	{
		SENTENCE_START =0,
		TUTS_TEST =1,
		TUTS_TEST2 =2,
		TUTS_PORTAL_GUN = 3,
		LONG_DIST = 4,
		TUTS_PORTAL_GUN_CP = 5,
		LEVEL_1_START =6,
		LEVEL_1_END =7,
		LEVEL_1_A_START = 8,
		LEVEL_1_A_GROW = 9,
		LEVEL_4_START = 10,
		LEVEL_4_FEELS = 11,
		LEVEL_4_YABE = 12,
		LEVEL_4_MINI = 13,
		TOTAL_SENTENCE,
	};	

	const int TextSpeed = 60;
	const int maxtimer = 60;

	Dialogue();
	~Dialogue();
	bool LoadDialogue(std::string filename);
	void playDialogue(int currentSceneConvo);
	int getcurrentTextIndex();
	void setcurrenTextIndex(int currentTextIndex);
	bool getActive();
	void setActive(bool Active);
	void Update(double dt);
	void setcurrentSceneConvo(int currentSceneConvo);
	int getcurrentSceneConvo();
	std::string getCurrentText();
	bool getEndConvo();
	void setEndConvo(bool endConvo);

private:
	// vector that stores all the sentences 
	std::vector<std::vector<std::string>> dialogueList;
	// current sentence
	std::string currentText;
	// current letter
	int currentTextIndex;
	// if active then it will be updating.
	bool Active;

	bool endConvo;

	// indicator to show which conversation we are having
	int currentSceneConvo;
	// indicator to show which sentence is being played
	int currentcovoIndex;
	// time until the next letter gets rendered.
	int textTimer;
};