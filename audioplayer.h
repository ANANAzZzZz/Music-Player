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

class AudioPlayer {
    public:
        int trackNumber;
        string trackTiming;
        string trackName;
        string fileLink;
        string currentVolume = "50";
        vector<string> files;
        bool isPlaying = false;

        void playAudio();

        void changeVolume();

        void rewindAudio();

        void closeAudio();

        void changeAudio();

        void restartAudio();

        void pauseAudio();

        void getFileNames(const string &, vector<string>);
};
