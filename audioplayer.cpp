#include "audioplayer.h"

vector<string> getFileNames(const string& folder) {
    vector<string> names;
    DIR* directory = opendir(folder.c_str());

    if (directory == nullptr) {
        throw invalid_argument("unable to find directory");
    }

    struct dirent* ent;
    while ((ent = readdir(directory)) != nullptr) {
        if ((strcmp(ent->d_name, "..")) && (strcmp(ent->d_name, "."))) {
            names.emplace_back(ent->d_name);
        }
    }
    closedir(directory);
    return names;
}

void AudioPlayer::closeAudio() {
    callMciSendString("close mp3");
}

void AudioPlayer::playAudio() {
    // save current volume
    callMciSendString(("setAudio mp3 volume to " + currentVolume));

    // play audio
    isPlaying = true;
    callMciSendString("play mp3");
}

void AudioPlayer::changeVolume(const string& volume) {
    currentVolume = volume;
    callMciSendString("setAudio mp3 volume to " + currentVolume);
}

void AudioPlayer::rewindAudio(const string& trackTiming) {
    // rewind
    callMciSendString(("seek mp3 to " + trackTiming + "000"));

    isPlaying = true;
    callMciSendString("play mp3");
}

bool AudioPlayer::changeTrack(const int& trackNumber) {
    vector<string> files = getFileNames("music/");

    // check that trackNumber is valid
    if (trackNumber > files.size() || isdigit(trackNumber) == trackNumber) {
        return false;
    }

    // close previous audio
    callMciSendString("close mp3");

    trackName = files[trackNumber - 1];

    callMciSendString("open music/" + trackName + " type mpegVideo alias mp3");

    isPlaying = true;
    playAudio();

    return true;
}

void AudioPlayer::restartAudio() {
    // place track to start
    callMciSendString("seek mp3 to start");

    // save current volume
    callMciSendString(("setAudio mp3 volume to " + currentVolume));

    callMciSendString("play mp3");
    isPlaying = true;
}

void AudioPlayer::pauseAudio() {
    //pause the audio file
    isPlaying = false;
    callMciSendString("pause mp3");
}

void callMciSendString(const string& str) {
    mciSendString(str.c_str(), nullptr, 0, nullptr);
}

bool AudioPlayer::isAudioPlaying() {
    return isPlaying;
}