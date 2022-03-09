#include "audioplayer.h"


void AudioPlayer::getFileNames(const string &folder, vector<string>) {
    vector<string> names;
    DIR* directory = opendir(folder.c_str());

    if (directory == nullptr) {
        abort();
    }

    struct dirent *ent;
    while ((ent = readdir(directory)) != nullptr) {
        if ((strcmp(ent->d_name, "..")) && (strcmp(ent->d_name, "."))) {
            names.emplace_back(ent->d_name);
        }
    }
    closedir(directory);
    files = names;
}


void AudioPlayer::closeAudio() {
    mciSendString("close mp3", nullptr, 0, nullptr);
}


void AudioPlayer::playAudio() {
    // save current volume
    mciSendStringA(("setAudio mp3 volume to " + currentVolume).c_str(), nullptr, 0, nullptr);

    // play audio
    isPlaying = true;
    mciSendString("play mp3", nullptr, 0, nullptr);

}


void AudioPlayer::changeVolume() {
    string volumeLink;

    volumeLink = "setAudio mp3 volume to " + currentVolume;
    mciSendStringA(volumeLink.c_str(), nullptr, 0, nullptr);

    isPlaying = true;
    mciSendString("play mp3", nullptr, 0, nullptr);


}


void AudioPlayer::rewindAudio() {
    // rewind
    mciSendString(("seek mp3 to " + trackTiming + "000").c_str(), nullptr, 0, nullptr);

    isPlaying = true;
    mciSendString("play mp3", nullptr, 0, nullptr);

}


void AudioPlayer::changeAudio() {

    // close previous audio
    mciSendString("close mp3", nullptr, 0, nullptr);

    trackName = files[trackNumber - 1];

    fileLink = "open music/" + trackName + " type mpegVideo alias mp3";
    mciSendString(fileLink.c_str(), nullptr, 0, nullptr);

    isPlaying = true;
    playAudio();
}


void AudioPlayer::restartAudio() {
    // place track to start
    mciSendString("seek mp3 to start", nullptr, 0, nullptr);

    // save current volume
    mciSendStringA(("setAudio mp3 volume to " + currentVolume).c_str(), nullptr, 0, nullptr);

    mciSendString("play mp3", nullptr, 0, nullptr);
    isPlaying = true;
}


void AudioPlayer::pauseAudio() {
    //pause the audio file
    isPlaying = false;
    mciSendString("pause mp3", nullptr, 0, nullptr);
}

