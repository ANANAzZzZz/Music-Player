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

void callMciSendString(const string &str);

vector<string> getFileNames(const string &);

class AudioPlayer {

private:
    string trackName;
    string fileLink;
    string currentVolume = "50";
    bool isPlaying = false;

public:

    void playAudio();

    void changeVolume(const string&);

    void rewindAudio(const string&);

    void closeAudio();

    bool changeAudio(int);

    void restartAudio();

    void pauseAudio();

    bool isAudioPlaying();
};
