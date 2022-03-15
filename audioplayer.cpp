#include "audioplayer.h"

vector<string> AudioPlayer::GetAvailableTracks(const string& folder) {
  vector<string> names;
  DIR* directory = opendir(folder.c_str());

  if (directory == nullptr) {
    throw invalid_argument("Unable to find directory");
  }

  dirent* ent;
  while ((ent = readdir(directory)) != nullptr) {
    if ((strcmp(ent->d_name, "..")) && (strcmp(ent->d_name, "."))) {
      names.emplace_back(ent->d_name);
    }
  }
  closedir(directory);
  return names;
}

void AudioPlayer::CloseAudio() {
  CallMciSendString("close mp3");
}

bool AudioPlayer::PlayAudio() {
  // defend clause
  if (selectedTrackName == "") {
    return false;
  }

  // save current volume
    CallMciSendString(("setAudio mp3 volume to " + currentVolume));

    // play audio
    isPlaying = true;
    CallMciSendString("play mp3");

  return true;
}

void AudioPlayer::ChangeVolume(const string& volume) {
  currentVolume = volume;
  CallMciSendString("setAudio mp3 volume to " + currentVolume);
}

bool AudioPlayer::RewindAudio(const string& trackTiming) {
  // defend clause
  if (selectedTrackName == "") {
    return false;
  }

  // rewind
  CallMciSendString(("seek mp3 to " + trackTiming + "000"));

  PlayAudio();

  return true;
}

bool AudioPlayer::ChangeTrack(const int& trackNumber) {
  vector<string> files = GetAvailableTracks("music/");

  // close previous audio
  CallMciSendString("close mp3");

  selectedTrackName = files[trackNumber - 1];
  CallMciSendString(+"open \"music/" + selectedTrackName + "\"" + " type mpegVideo alias mp3");

  PlayAudio();

  return true;
}

bool AudioPlayer::RestartAudio() {
  // defend clause
  if (selectedTrackName == "") {
    return false;
  }

  // place track to start
  CallMciSendString("seek mp3 to start");

  PlayAudio();

  return true;
}

void AudioPlayer::PauseAudio() {
  //pause the audio file
  isPlaying = false;
  CallMciSendString("pause mp3");
}

void CallMciSendString(const string& str) {
  mciSendString(str.c_str(), nullptr, 0, nullptr);
}

bool AudioPlayer::IsPlaying() {
  return isPlaying;
}