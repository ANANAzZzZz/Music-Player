#pragma once
#include <Windows.h>
#include <MMSystem.h>
#include <iostream>
#include <io.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <algorithm>

#pragma comment(lib, "winMM.lib")

using namespace std;

void CallMciSendString(const string& str);

class AudioPlayer {
 private:
  string selectedTrackName;
  int currentVolume = 50;
  bool isPlaying = false;

 public:
  vector<string> GetAvailableTracks(const string& folder);
  bool ChangeVolume(int volume);
  bool RewindAudio(const string& trackTiming);
  void CloseAudio();
  bool ChangeTrack(const int& trackNumber);
  bool RestartAudio();
  bool PlayAudio();
  void PauseAudio();
  bool IsPlaying();
};
