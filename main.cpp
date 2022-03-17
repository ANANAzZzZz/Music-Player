#include "audioplayer.h"

void PrintMenu();

void PrintAvailableTracks(const AudioPlayer& audioPlayer);

int main() {
  AudioPlayer audioPlayer;
  bool firstIteration = true;
  int volume = 50;

  while (true) {
    int n;
    int counter;
    int trackNumber;

    if (!firstIteration) {
      // menu
      PrintMenu();

      cin >> n;

      if (isdigit(n) == n) {
        cout << "\nError. Please enter number";
        return 1;
      }

    } else {
      firstIteration = false;

      PrintAvailableTracks(audioPlayer);

      cout << "\nTo choose track press it's number." << endl;
      cin >> trackNumber;

      audioPlayer.ChangeTrack(trackNumber);
    }

    // play the audio file
    if (n == 1) {
      if (!audioPlayer.PlayAudio()) {
        cout << "Unable to find track" << endl;
        break;
      }

      // exit from player
    } else if (n == 2) {
      audioPlayer.CloseAudio();
      break;

      // change track
    } else if (n == 3) {
      PrintAvailableTracks(audioPlayer);

      cout << "\nTo choose track press it's number." << endl;
      cin >> trackNumber;

      audioPlayer.ChangeTrack(trackNumber);

      // restart track
    } else if (n == 4 && !audioPlayer.IsPlaying()) {

      if (!audioPlayer.RestartAudio()) {
        cout << "Unable to find track";
        break;
      }

      // change volume
    } else if (n == 5 && !audioPlayer.IsPlaying()) {
      if (!audioPlayer.ChangeVolume(volume)) {
        cout << "Unable to find track";
        break;
      }

      cout << "\nCurrent volume is: " << volume;
      cout << "\nTo set volume press it (min - 0; max - 1000)" << endl;
      cin >> volume;
      audioPlayer.ChangeVolume(volume);

      // rewind track
    } else if (n == 6) {
      string trackTiming;

      cout << "Press second that you want to rewind: " << endl;
      cin >> trackTiming;

      if (!audioPlayer.RewindAudio(trackTiming)) {
        cout << "Unable to find track";
        break;
      }
    }

    if (audioPlayer.IsPlaying()) {
      cout << "Press 0 to pause the file and press 2 to exit the file." << endl;
      cout << "To change track, change volume or start it over press pause first" << endl;
      cin >> n;

      if (n == 0) {
        //pause the audio file
        audioPlayer.PauseAudio();

      } else if (n == 2) {
        //close the audio file
        audioPlayer.CloseAudio();
        break;
      }
    }
  }
}

void PrintMenu() {
  cout << "-----------------------------" << endl;
  cout << "-Input 1 to play the file" << endl;
  cout << "-Input 2 to exit the file" << endl;
  cout << "-Input 3 to change track" << endl;
  cout << "-Input 4 to start track again" << endl;
  cout << "-Input 5 to change volume" << endl;
  cout << "-Input 6 to rewind track" << endl;
  cout << "-----------------------------" << endl;
}

// output files
void PrintAvailableTracks(const AudioPlayer& audioPlayer) {
  int counter = 0;
  const auto files = audioPlayer.GetAvailableTracks("music/");

  cout << "\nfiles in folder 'music':" << endl;
  for (auto const file: files) {
    counter++;
    cout << counter << ". " << file << endl;
  }
}