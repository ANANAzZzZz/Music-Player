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

void callMciSendString(const string& str);

vector<string> getFileNames(const string&);

class AudioPlayer {
    public:
        string trackName;
        string fileLink;
        string currentVolume = "50";
        bool isPlaying = false;

        void playAudio();

        void changeVolume();

        void rewindAudio(string);

        void closeAudio();

        bool changeAudio(int, int);

        void restartAudio();

        void pauseAudio();
};
