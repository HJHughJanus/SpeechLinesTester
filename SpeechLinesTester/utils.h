#pragma once
#include "script.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <fstream>

using namespace std;


struct ScriptedSpeechParams
{
	const char* speechName;
	const Any* voiceName;
	alignas(8) int v3;
	alignas(8) Hash speechParamHash;
	alignas(8) Entity entity;
	alignas(8) BOOL v6;
	alignas(8) int v7;
	alignas(8) int v8;
};

void DrawText(float x, float y, char* str)
{
	UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, (char*)"LITERAL_STRING", str), x, y);
}

bool does_file_exist(const char* fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

bool PlaySpeechLine(Ped ped, string speechline)
{
	ScriptedSpeechParams params{ speechline.c_str(), 0, 1, 0x67F3AB43, 0, true, 1, 1 };
	if (!AUDIO::IS_ANY_SPEECH_PLAYING(ped))
	{
		if (AUDIO::x_PLAY_AMBIENT_SPEECH1(ped, (Any*)&params)) return true;
		else return false;
	}
}