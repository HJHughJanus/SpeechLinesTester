#include "script.h"
#include "keyboard.h"
#include "utils.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

void main()
{

	//checking if there is an ini file (used for drawing according information on screen)
	bool bIniExists = false, bTxtExists = false;
	bIniExists = does_file_exist(".\\SpeechLinesTester.ini");
	bTxtExists = does_file_exist(".\\SpeechLines.txt");

	//getting values from the ini or setting default values, if ini not there (default represent mod version "standard" of v1.41)
	int ini_ToggleKey = GetPrivateProfileInt("SpeechLinesTester_Configuration", "ModToggleKey", 9, ".\\SpeechLinesTester.ini");
	int ini_NextSpeechLineKey = GetPrivateProfileInt("SpeechLinesTester_Configuration", "NextSpeechLineKey", 3, ".\\SpeechLinesTester.ini");
	int ini_PrevSpeechLineKey = GetPrivateProfileInt("SpeechLinesTester_Configuration", "PreviousSpeechLineKey", 2, ".\\SpeechLinesTester.ini");
	int ini_ModEnabled = GetPrivateProfileInt("SpeechLinesTester_Configuration", "ModEnabledByDefault", 0, ".\\SpeechLinesTester.ini");
	int ini_AutoIteration = GetPrivateProfileInt("SpeechLinesTester_Configuration", "AutoIterateSpeechLines", 0, ".\\SpeechLinesTester.ini");
	int ini_IterationInterval = GetPrivateProfileInt("SpeechLinesTester_Configuration", "IterationInterval", 10000, ".\\SpeechLinesTester.ini");
	int iToggleKey = VK_F9, iNextSpeechLineKey = VK_F3, iPrevSpeechLineKey = VK_F2;
	int iSpeechLinesIndex = 0, iLastIteration = 0;
	vector<string> vSpeechLinesList;

	switch (ini_ToggleKey)
	{
	case 1:
		iToggleKey = VK_F1;
		break;
	case 2:
		iToggleKey = VK_F2;
		break;
	case 3:
		iToggleKey = VK_F3;
		break;
	case 4:
		iToggleKey = VK_F4;
		break;
	case 5:
		iToggleKey = VK_F5;
		break;
	case 6:
		iToggleKey = VK_F6;
		break;
	case 7:
		iToggleKey = VK_F7;
		break;
	case 8:
		iToggleKey = VK_F8;
		break;
	case 9:
		iToggleKey = VK_F9;
		break;
	case 10:
		iToggleKey = VK_F10;
		break;
	case 11:
		iToggleKey = VK_F11;
		break;
	case 12:
		iToggleKey = VK_F12;
		break;
	default:
		iToggleKey = VK_F9;
	}

	switch (ini_NextSpeechLineKey)
	{
	case 1:
		iNextSpeechLineKey = VK_F1;
		break;
	case 2:
		iNextSpeechLineKey = VK_F2;
		break;
	case 3:
		iNextSpeechLineKey = VK_F3;
		break;
	case 4:
		iNextSpeechLineKey = VK_F4;
		break;
	case 5:
		iNextSpeechLineKey = VK_F5;
		break;
	case 6:
		iNextSpeechLineKey = VK_F6;
		break;
	case 7:
		iNextSpeechLineKey = VK_F7;
		break;
	case 8:
		iNextSpeechLineKey = VK_F8;
		break;
	case 9:
		iNextSpeechLineKey = VK_F9;
		break;
	case 10:
		iNextSpeechLineKey = VK_F10;
		break;
	case 11:
		iNextSpeechLineKey = VK_F11;
		break;
	case 12:
		iNextSpeechLineKey = VK_F12;
		break;
	default:
		iNextSpeechLineKey = VK_F3;
	}

	switch (ini_PrevSpeechLineKey)
	{
	case 1:
		iPrevSpeechLineKey = VK_F1;
		break;
	case 2:
		iPrevSpeechLineKey = VK_F2;
		break;
	case 3:
		iPrevSpeechLineKey = VK_F3;
		break;
	case 4:
		iPrevSpeechLineKey = VK_F4;
		break;
	case 5:
		iPrevSpeechLineKey = VK_F5;
		break;
	case 6:
		iPrevSpeechLineKey = VK_F6;
		break;
	case 7:
		iPrevSpeechLineKey = VK_F7;
		break;
	case 8:
		iPrevSpeechLineKey = VK_F8;
		break;
	case 9:
		iPrevSpeechLineKey = VK_F9;
		break;
	case 10:
		iPrevSpeechLineKey = VK_F10;
		break;
	case 11:
		iPrevSpeechLineKey = VK_F11;
		break;
	case 12:
		iPrevSpeechLineKey = VK_F12;
		break;
	default:
		iPrevSpeechLineKey = VK_F2;
	}

	//is script activated by default or not
	bool bModScriptState = false;
	if (ini_ModEnabled == 1) bModScriptState = true;
	int iMsgTimeModEnabled = 0, iMsgTimeSpeechLineIndex = 0;

	if (bTxtExists)
	{
		//reading the speech lines from "SpeechLinesList.txt"
		fstream ioSpeechLinesFile;

		ioSpeechLinesFile.open("SpeechLines.txt", ios::in);

		if (ioSpeechLinesFile.is_open()) {
			string sa;
			while (getline(ioSpeechLinesFile, sa)) {
				vSpeechLinesList.push_back(sa);
			}

			ioSpeechLinesFile.close();
		}
	}


	char c[60];
	std::string sSpeechLineText = "Speech Line Name: ";

	//main script
	while (true)
	{
		//check if script is being enabled or disabled
		if (IsKeyJustUp(iToggleKey))
		{
			bModScriptState = !bModScriptState;
			iMsgTimeModEnabled = GetTickCount() + 3000;
		}

		if (IsKeyJustUp(iPrevSpeechLineKey))
		{
			iSpeechLinesIndex--;
			if (iSpeechLinesIndex < 0)
			{
				iSpeechLinesIndex = vSpeechLinesList.size() - 1;
			}
			iMsgTimeSpeechLineIndex = GetTickCount() + 3000;
		}

		if (IsKeyJustUp(iPrevSpeechLineKey))
		{
			iSpeechLinesIndex++;
			if (iSpeechLinesIndex > vSpeechLinesList.size() - 1)
			{
				iSpeechLinesIndex = 0;
			}
			iMsgTimeSpeechLineIndex = GetTickCount() + 3000;
		}

		//if script enabled, start doing your thing
		if (bModScriptState)
		{
			if (vSpeechLinesList.size() > 0)
			{
				//get all peds near player (those will be affected by the script)
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				const int ARR_SIZE = 100;
				Ped peds[ARR_SIZE];
				int count = worldGetAllPeds(peds, ARR_SIZE);

				//auto-iteration
				if (ini_AutoIteration == 1)
				{
					if (iLastIteration == 0) iLastIteration = GetTickCount();

					if (GetTickCount() > iLastIteration + ini_IterationInterval)
					{
						iSpeechLinesIndex++;
						if (iSpeechLinesIndex > vSpeechLinesList.size() - 1)
						{
							iSpeechLinesIndex = 0;
						}

						iLastIteration += ini_IterationInterval;
					}
				}

				//iterate through NPCs and make them play speech lines
				for (int i = 0; i < count; i++)
				{
					if (peds[i] != playerPed && PED::IS_PED_HUMAN(peds[i]) && !ENTITY::IS_ENTITY_DEAD(peds[i]))
					{
						PlaySpeechLine(peds[i], vSpeechLinesList.at(iSpeechLinesIndex));
						
						//on screen display of speech line name
						sSpeechLineText = "Speech Line Name: " + vSpeechLinesList.at(iSpeechLinesIndex);
						std::strcpy(c, sSpeechLineText.c_str());
						DrawText(0.55, 0.05, c);
					}
				}
			}
		}

		//draw messages on screen
		if (GetTickCount() < iMsgTimeModEnabled)
		{
			if (bModScriptState)
			{
				DrawText(0.45, 0.45, (char*)"SpeechLineTester has been ENABLED.");
				if (bIniExists) DrawText(0.58, 0.58, (char*)"ini file found.");
				else DrawText(0.58, 0.58, (char*)"ini file not found.");
				if (bTxtExists) DrawText(0.71, 0.71, (char*)"txt file found.");
				else DrawText(0.71, 0.71, (char*)"txt file not found.");
			}
			else DrawText(0.45, 0.45, (char*)"SpeechLineTester has been DISABLED.");
		}

		if (GetTickCount() < iMsgTimeSpeechLineIndex)
		{
			if (bModScriptState)
			{
				string sToPrint = "Speech Line Number: " + std::to_string(iSpeechLinesIndex);
				const int iLength = sToPrint.length();
				char* c_toPrint = new char[iLength + 1];
				strcpy(c_toPrint, sToPrint.c_str());
				DrawText(0.45, 0.70, c_toPrint);
			}
		}

		WAIT(1);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}