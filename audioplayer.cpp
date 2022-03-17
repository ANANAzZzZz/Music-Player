#include "audioplayer.h"

vector<string> AudioPlayer::GetAvailableTracks(const string& folder) const {
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

void AudioPlayer::CloseAudio() const {
  CallMciSendString("close mp3");
}

void AudioPlayer::PlayAudio() {
  // save current volume
  CallMciSendString("setAudio mp3 volume to " + to_string(currentVolume));

  // play audio
  isPlaying = true;
  CallMciSendString("play mp3");
}

bool AudioPlayer::ChangeVolume(const int volume) {
  if (volume > 1000 || volume < 0) {
    return false;
  }

  currentVolume = volume;
  CallMciSendString("setAudio mp3 volume to " + to_string(currentVolume));

  return true;
}

void AudioPlayer::RewindAudio(const string& trackTiming) {
  // rewind
  CallMciSendString(("seek mp3 to " + trackTiming + "000"));

  PlayAudio();
}

bool AudioPlayer::ChangeTrack(const int trackNumber) {
  vector<string> files = GetAvailableTracks("music/");

  if (trackNumber < 0 || trackNumber > files.size()) {
    return false;
  }

  // close previous audio
  CallMciSendString("close mp3");

  selectedTrackName = files[trackNumber - 1];
  CallMciSendString(+"open \"music/" + selectedTrackName + "\"" + " type mpegVideo alias mp3");

  PlayAudio();

  return true;
}

void AudioPlayer::RestartAudio() {
  // place track to start
  CallMciSendString("seek mp3 to start");

  PlayAudio();
}

void AudioPlayer::PauseAudio() {
  //pause the audio file
  isPlaying = false;
  CallMciSendString("pause mp3");
}

void AudioPlayer::CallMciSendString(const string& str) const {
  mciSendString(str.c_str(), nullptr, 0, nullptr);
}

bool AudioPlayer::IsPlaying() const {
  return isPlaying;
}

int AudioPlayer::GetVolumeValue() const {
  return currentVolume;
}

bool AudioPlayer::IsTrackChosen() const {
  return selectedTrackName != "";
}