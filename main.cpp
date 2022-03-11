#include "audioplayer.h"

void printMenu();

int main() {
    AudioPlayer musicPlayer;
    bool firstIteration = true;
    string volume = "50";

    while (true) {
        int n;
        int counter;
        int trackNumber;
        string fileLink;

        if (!firstIteration) {
            // menu
            printMenu();

            cin >> n;

            if (isdigit(n) == n) {
                cout << "\nError. Please enter number";
                abort();
            }

        } else {
            firstIteration = false;
            vector<string> files = GetFileNames("music/");

            // output files
            cout << "\nfiles in folder 'music':" << endl;
            counter = 0;
            for (auto const file:files) {
                counter++;
                cout << counter << ". " << file << endl;
            }

            cout << "\nTo choose track press it's number." << endl;
            cin >> trackNumber;

            if (!musicPlayer.ChangeTrack(trackNumber)) {
                cout << "Enter correct track's number";
                break;
            }
        }

        // play the audio file
        if (n == 1) {
            musicPlayer.PlayAudio();

            // exit from player
        } else if (n == 2) {
            musicPlayer.CloseAudio();
            break;

            // change track
        } else if (n == 3) {
            vector<string> files = GetFileNames("music/");

            // output files
            cout << "\nfiles in folder 'music':" << endl;
            counter = 0;
            for (auto const file:files) {
                counter++;
                cout << counter << ". " << file << endl;
            }

            cout << "\nTo choose track press it's number." << endl;
            cin >> trackNumber;

            if (!musicPlayer.ChangeTrack(trackNumber)) {
                cout << "Enter correct track's number";
                break;
            }

            // restart track
        } else if (n == 4 && !musicPlayer.IsPlaying()) {
            // place track to start
            musicPlayer.RestartAudio();

            // change volume
        } else if (n == 5 && !musicPlayer.IsPlaying()) {
            cout << "\nCurrent volume is: " << volume;
            cout << "\nTo set volume press it (min - 0; max - 1000)" << endl;
            cin >> volume;

            musicPlayer.ChangeVolume(volume);

            // rewind track
        } else if (n == 6) {
            string trackTiming;

            cout << "Press second that you want to rewind: " << endl;
            cin >> trackTiming;

            musicPlayer.RewindAudio(trackTiming);
        }

        if (musicPlayer.IsPlaying()) {
            cout << "Press 0 to pause the file and press 2 to exit the file." << endl;
            cout << "To change track, change volume or start it over press pause first" << endl;
            cin >> n;

            if (n == 0) {
                //pause the audio file
                musicPlayer.PauseAudio();

            } else if (n == 2) {
                //close the audio file
                musicPlayer.CloseAudio();
                break;
            }
        }
    }
}

void printMenu() {
    cout << "-----------------------------" << endl;
    cout << "-Press 1 to play the file" << endl;
    cout << "-Press 2 to exit the file" << endl;
    cout << "-Press 3 to change track" << endl;
    cout << "-Press 4 to start track again" << endl;
    cout << "-Press 5 to change volume" << endl;
    cout << "-Press 6 to rewind track" << endl;
    cout << "-----------------------------" << endl;
}