#include <Windows.h>
#include <MMSystem.h>
#include <iostream>
#include <io.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <algorithm>

#pragma once
#pragma comment(lib, "winMM.lib")

using namespace std;

void CallMciSendString(const string &str);

vector<string> GetFileNames(const string &folder);

class AudioPlayer {

private:
    string trackName;
    string currentVolume = "50";
    bool isPlaying = false;

public:

    void PlayAudio();

    void ChangeVolume(const string &volume);

    void RewindAudio(const string &trackTiming);

    void CloseAudio();

    bool ChangeTrack(const int&);

    void RestartAudio();

    void PauseAudio();

    bool IsPlaying();
};
