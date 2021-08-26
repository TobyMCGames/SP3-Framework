#include "Dialogue.h"
#include <fstream>
#include "KeyboardController.h"
#include "GL\glew.h"
#include "GLFW/glfw3.h"
#include <string>
#include "Application.h"


Dialogue::Dialogue():
	currentText(""),
	currentTextIndex(0),
	currentSceneConvo(CONVO_SENTENCES::SENTENCE_START),
	Active(true),
	textTimer(maxtimer),
	currentcovoIndex(0)
{
	// initalise the lists with the neccessary sentences 
	for (int i = 0; i < TOTAL_SENTENCE; i++)
	{	
		std::vector<std::string> temp;
		dialogueList.push_back(temp);
	}
	playDialogue(CONVO_SENTENCES::LEVEL_1_START,0);
}

Dialogue::~Dialogue()
{
	for (int i = dialogueList.size()-1 ; i >=0;i--)
	{
		dialogueList.pop_back();
	}
}

bool Dialogue::LoadDialogue(std::string file_path)
{
	std::ifstream file;
	std::string ss;
	std::string value;
	file.open(file_path);
	if (!file.is_open()) {
		std::cout << "File can not be opened" << std::endl;
		return false;
	}
	std::vector<std::string> dialogue;
	
	bool placement = false;
	std::string sentenceLocation ="";
	bool recordSentence = false;
	bool placed = false;
	bool EOL = false;
	bool EndSentence = false;
	int index = -1;
	int sentenceLoc = 0;
	while (!file.eof())
	{
		char line[1024]{};
		file.getline(line, 1024);
		ss = line;
		for (int i = 0; i < ss.size(); i++)
		{
			switch (ss[i])
			{
			case '{': // start of placement
				sentenceLocation = "";
				placement = true;
				index = -1;
				break;
			case '}': // end of placement.
				placement = false;
				placed = true;
				sentenceLoc = std::stoi(sentenceLocation);
				break;
			case '[': // start of sentence
				recordSentence = true;
				dialogueList[sentenceLoc].push_back("");
				index++;
				break; 
			case ']': // end of sentence
				recordSentence = false;
				EndSentence = true;
				break;

			default:
				if (placement == true)
				{
					// currently has no error checking assuming everything is correct. 
					// need to convert char to int to store sentence location
					sentenceLocation += ss[i];
				}
				else
					if (recordSentence == true)
						value += ss[i];
				break;
			}
		}
		EOL = true;
		if (sentenceLocation != "")
		{
			int sentenceLoc = std::stoi(sentenceLocation);
			if (sentenceLoc <= SENTENCE_START || sentenceLoc >= TOTAL_SENTENCE)
			{
				std::cout << "sentence goes out of scope" << std::endl;
				return false;
			}			
			dialogueList[sentenceLoc][index] += value; // do some error checking later
			placed = false;
		
			if (EOL == true)
			{
				dialogueList[sentenceLoc][index] += " ";
				value = "";
			}
		}
	}
	return true;
}

void Dialogue::playDialogue(CONVO_SENTENCES currentSceneConvo, int currentconvoIndex)
{
	this->currentSceneConvo = currentSceneConvo;
	this->currentcovoIndex = currentconvoIndex;
	Active = true;
	currentTextIndex = 0;
}

int Dialogue::getcurrentTextIndex()
{
	return currentTextIndex;
}

void Dialogue::setcurrenTextIndex(int currentTextIndex)
{
	this->currentTextIndex = currentTextIndex;
}

bool Dialogue::getActive()
{
	return Active;
}

void Dialogue::setActive(bool Active)
{
	this->Active = Active;
}

void Dialogue::Update(double dt)
{
	static bool EMouseState = false;
	if (Application::IsMousePressed(0) && !EMouseState)
	{
		EMouseState = true;
	}
	else if (!Application::IsMousePressed(0) && EMouseState)
	{
		EMouseState = false;
		if (Active == false)
		{
			if (currentSceneConvo <= TOTAL_SENTENCE - 1)
			{
				Active = true;
				if ((currentcovoIndex + 1) <= dialogueList[currentSceneConvo].size() - 1)
				{
					currentcovoIndex += 1;
					currentTextIndex = 0;
					currentText.clear();
				}
				else if ((currentSceneConvo + 1) <= TOTAL_SENTENCE - 1)
				{
					currentTextIndex = 0;
					currentText.clear();
					currentcovoIndex = 0;
					currentSceneConvo++;
				}
				else
				{
					currentText.clear();
					Active = false;
				}
					
				textTimer = maxtimer;
			}
		}
		else
		{
			Active = false;
			//currentconvoIndex += 1;
			currentText = dialogueList[currentSceneConvo][currentcovoIndex];
		}
	}
	// change later 
	if (textTimer <= 0)
	{
		if (dialogueList[currentSceneConvo].size() != 0)
		{
			if (currentTextIndex >= dialogueList[currentSceneConvo][currentcovoIndex].size() - 1)
			{
				Active = false;
				currentTextIndex = 0;
			}
			if (Active == true)
			{
				if (dialogueList[currentSceneConvo][currentcovoIndex].size() > 0)
				{
					currentText += dialogueList[currentSceneConvo][currentcovoIndex][currentTextIndex];
					currentTextIndex += 1;
					textTimer = maxtimer;
				}
			}
		}
		else
		{
			Active = false;
		}
			
		
	}
	else
		textTimer -= TextSpeed;
}

void Dialogue::setcurrentSceneConvo(int currentSceneConvo)
{
	this->currentSceneConvo = currentSceneConvo;
}

int Dialogue::getcurrentSceneConvo()
{
	return currentSceneConvo;
}

std::string Dialogue::getCurrentText()
{
	return currentText;
}


