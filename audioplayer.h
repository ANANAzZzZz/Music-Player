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

class AudioPlayer {
 private:
  string selectedTrackName;
  int currentVolume = 50;
  bool isPlaying = false;

 public:
  void CallMciSendString(const string& str) const;
  vector<string> GetAvailableTracks(const string& folder) const;
  bool ChangeVolume(const int volume);
  void RewindAudio(const string& trackTiming);
  void CloseAudio() const;
  bool ChangeTrack(const int trackNumber);
  void RestartAudio();
  void PlayAudio();
  void PauseAudio();
  bool IsPlaying() const;
  int GetVolumeValue() const;
  bool IsTrackChosen() const;
};
