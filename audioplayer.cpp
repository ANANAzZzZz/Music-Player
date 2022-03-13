#include "audioplayer.h"

vector<string> AudioPlayer::GetAvailableTracks(const string& folder) {
    vector<string> names;
    DIR* directory = opendir(folder.c_str());

    if (directory == nullptr) {
        throw invalid_argument("unable to find directory");
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

void AudioPlayer::PlayAudio() {
    // save current volume
    CallMciSendString(("setAudio mp3 volume to " + currentVolume));

    // play audio
    isPlaying = true;
    CallMciSendString("play mp3");
}

void AudioPlayer::ChangeVolume(const string& volume) {
    currentVolume = volume;
    CallMciSendString("setAudio mp3 volume to " + currentVolume);
}

void AudioPlayer::RewindAudio(const string& trackTiming) {
    // rewind
    CallMciSendString(("seek mp3 to " + trackTiming + "000"));

    PlayAudio();
}

bool AudioPlayer::ChangeTrack(const int& trackNumber) {
    vector<string> files = GetAvailableTracks("music/");

    // check that trackNumber is valid
    if (trackNumber > files.size() || isdigit(trackNumber) == trackNumber) {
        return false;
    }

    // close previous audio
    CallMciSendString("close mp3");

    trackName = files[trackNumber - 1];

    CallMciSendString("open music/" + trackName + " type mpegVideo alias mp3");

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

void CallMciSendString(const string& str) {
    mciSendString(str.c_str(), nullptr, 0, nullptr);
}

bool AudioPlayer::IsPlaying() {
    return isPlaying;
}