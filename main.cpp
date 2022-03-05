#include <Windows.h>
#include <MMSystem.h>
#include <iostream>
#include <io.h>
#include "dirent.h"
#include <vector>

#pragma comment(lib, "winMM.lib")

using namespace std;

void getFileNames(string, vector<string> *);

string changeVolume(string currentVolume);


int main() {
    int n, trackNumber, counter = 0;
    string trackName, fileLink, currentVolume;
    vector<string> files;
    bool isPlaying = false;

    // get file names from folder
    getFileNames("music/", &files);

    // output for files
    cout << "Files in folder 'music':\n" << endl;
    for (auto const &file: files) {
        counter++;
        cout << counter << ". " << file << endl;
    }
    cout << endl;

    // set volume
    currentVolume = "50";

    // choose audio file
    cout << "To choose track press it's number." << endl;
    cin >> trackNumber;

    // check trackNumber is correct
    if (trackNumber > counter || isdigit(trackNumber) == trackNumber) {
        cout << "Press correct track's number";
        return 1;
    }
    trackName = files[trackNumber - 1];
    fileLink = "open music/" + trackName + " type mpegVideo alias mp3";


    // infinity loop
    while (true) {
        // open .mp3 file
        mciSendString(fileLink.c_str(), nullptr, 0, nullptr);

        // menu
        cout << "-----------------------------" << endl;
        cout << "-Press 1 to play the file" << endl;
        cout << "-Press 2 to exit the file" << endl;
        cout << "-Press 3 to change track" << endl;
        cout << "-Press 4 to start track again" << endl;
        cout << "-Press 5 to change volume" << endl;
        cout << "-----------------------------" << endl;

        cin >> n;

            // play the audio file
        if (n == 1) {

            // save current volume
            mciSendStringA(("setAudio mp3 volume to " + currentVolume).c_str(), nullptr, 0, nullptr);

            mciSendString("play mp3", nullptr, 0, nullptr);
            isPlaying = true;
            cout << "Audio file playing...\n\n";

            // close the file and get out of the loop
        } else if (n == 2) {
            mciSendString("close mp3", nullptr, 0, nullptr);
            break;

            // change track
        } else if (n == 3) {
            mciSendString("close mp3", nullptr, 0, nullptr);

            cout << "\nfiles in folder 'music':" << endl;
            counter = 0;
            for (auto const &file: files) {
                counter++;
                cout << counter << ". " << file << endl;
            }
            cout << "\nTo choose track press it's number." << endl;
            cin >> trackNumber;

            trackName = files[trackNumber - 1];
            fileLink = "open music/" + trackName + " type mpegVideo alias mp3";
            mciSendString(fileLink.c_str(), nullptr, 0, nullptr);

            // save current volume
            mciSendStringA(("setAudio mp3 volume to " + currentVolume).c_str(), nullptr, 0, nullptr);

            mciSendString("play mp3", nullptr, 0, nullptr);

            isPlaying = true;

            cout << "Audio file playing...\n\n";

            // restart track
        } else if (n == 4 && !isPlaying) {
            // place track to start
            mciSendString("seek mp3 to start", nullptr, 0, nullptr);

            // save current volume
            mciSendStringA(("setAudio mp3 volume to " + currentVolume).c_str(), nullptr, 0, nullptr);

            mciSendString("play mp3", nullptr, 0, nullptr);

            isPlaying = true;


            // change volume
        } else if (n == 5 && !isPlaying) {
            currentVolume = changeVolume(currentVolume);

            isPlaying = true;
        }


        if (isPlaying) {
            cout << "Press 0 to pause the file and press 2 to exit the file." << endl;
            cout << "To change track, change volume or start it over press pause first" << endl;
            cin >> n;

            if (n == 0) {
                //pause the audio file
                isPlaying = false;
                mciSendString("pause mp3", nullptr, 0, nullptr);

            } else if (n == 2) {
                //close the audio file
                mciSendString("close mp3", nullptr, 0, nullptr);
                break;
            }

        }
    }
    return 0;
}

void getFileNames(string folder, vector<string> *files) {
    vector<string> names;
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(folder.c_str())) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != nullptr) {
            if (!(strcmp(ent->d_name, "..")) || !(strcmp(ent->d_name, "."))) {
                (void) 0;
            } else {
                names.emplace_back(ent->d_name);
            }
        }
        closedir(dir);
        *files = names;
    }
}


string changeVolume(string currentVolume) {
    string volumeLink;

    cout << "\nCurrent volume is: " << currentVolume;
    cout << "\nTo set volume press it (min - 0; max - 1000)" << endl;
    cin >> currentVolume;

    volumeLink = "setAudio mp3 volume to " + currentVolume;
    mciSendStringA(volumeLink.c_str(), nullptr, 0, nullptr);
    mciSendString("play mp3", nullptr, 0, nullptr);

    return currentVolume;
}
