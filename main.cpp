#include "audioplayer.h"

int main() {
    AudioPlayer musicPlayer;
    bool firstIteration = true;

    while (true) {
        int n, counter, trackNumber;
        string fileLink;

        if (!firstIteration) {
            // menu
            cout << "-----------------------------" << endl;
            cout << "-Press 1 to play the file" << endl;
            cout << "-Press 2 to exit the file" << endl;
            cout << "-Press 3 to change track" << endl;
            cout << "-Press 4 to start track again" << endl;
            cout << "-Press 5 to change volume" << endl;
            cout << "-Press 6 to rewind track" << endl;
            cout << "-----------------------------" << endl;

            cin >> n;

            if (isdigit(n) == n) {
                cout << "\nError. Please enter number";
                abort();
            }

        } else {
            firstIteration = false;
            vector<string> files = getFileNames("music/");

            // output files
            cout << "\nfiles in folder 'music':" << endl;
            counter = 0;
            for (auto const file:files) {
                counter++;
                cout << counter << ". " << file << endl;
            }

            cout << "\nTo choose track press it's number." << endl;
            cin >> trackNumber;

            // check that trackNumber is valid
            if (trackNumber > counter || isdigit(trackNumber) == trackNumber) {
                cout << "Press correct track's number";
                break;
            }

            musicPlayer.changeAudio(trackNumber);
        }

        // play the audio file
        if (n == 1) {
            musicPlayer.playAudio();

            // exit from player
        } else if (n == 2) {
            musicPlayer.closeAudio();
            break;

            // change track
        } else if (n == 3) {
            vector<string> files = getFileNames("music/");
            // get file names from folder
            getFileNames("music/");

            // output files
            cout << "\nfiles in folder 'music':" << endl;
            counter = 0;
            for (auto const file:files) {
                counter++;
                cout << counter << ". " << file << endl;
            }

            cout << "\nTo choose track press it's number." << endl;
            cin >> trackNumber;

            // check that trackNumber is valid
            if (trackNumber > counter || isdigit(trackNumber) == trackNumber) {
                cout << "Press correct track's number";
                break;
            }

            musicPlayer.changeAudio(trackNumber);

            // restart track
        } else if (n == 4 && !musicPlayer.isPlaying) {
            // place track to start
            musicPlayer.restartAudio();

            // change volume
        } else if (n == 5 && !musicPlayer.isPlaying) {
            cout << "\nCurrent volume is: " << musicPlayer.currentVolume;
            cout << "\nTo set volume press it (min - 0; max - 1000)" << endl;
            cin >> musicPlayer.currentVolume;

            musicPlayer.changeVolume();

            // rewind track
        } else if (n == 6) {
            string trackTiming;

            cout << "Press second that you want to rewind: " << endl;
            cin >> trackTiming;

            musicPlayer.rewindAudio(trackTiming);
        }

        if (musicPlayer.isPlaying) {
            cout << "Press 0 to pause the file and press 2 to exit the file." << endl;
            cout << "To change track, change volume or start it over press pause first" << endl;
            cin >> n;

            if (n == 0) {
                //pause the audio file
                musicPlayer.pauseAudio();

            } else if (n == 2) {
                //close the audio file
                musicPlayer.closeAudio();
                break;
            }
        }
    }
}