#include "audioplayer.h"

vector<string> getFileNames(const string& folder) {
    vector<string> names;
    DIR* directory = opendir(folder.c_str());

    if (directory == nullptr) {
        abort();
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

void AudioPlayer::changeVolume() {
    string volumeLink;

    volumeLink = "setAudio mp3 volume to " + currentVolume;
    callMciSendString(volumeLink);

    isPlaying = true;
    callMciSendString("play mp3");
}

void AudioPlayer::rewindAudio(string trackTiming) {
    // rewind
    callMciSendString(("seek mp3 to " + trackTiming + "000"));

    isPlaying = true;
    callMciSendString("play mp3");
}

bool AudioPlayer::changeAudio(int trackNumber, int counter) {
    vector<string> files = getFileNames("music/");

    // check that trackNumber is valid
    if (trackNumber > counter || isdigit(trackNumber) == trackNumber) {
        return false;
    }

    // close previous audio
    callMciSendString("close mp3");

    trackName = files[trackNumber - 1];

    fileLink = "open music/" + trackName + " type mpegVideo alias mp3";
    callMciSendString(fileLink);

    isPlaying = true;
    playAudio();
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