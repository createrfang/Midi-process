#include"MidiFile.h"
#include"Options.h"
#include <iostream>
#include <iomanip>


using namespace std;

int main(int argc, char** argv) {
	Options options;
	options.process(argc, argv);
	MidiFile midifile;
	string fn;
	
	if (options.getArgCount() > 0) {
		fn = options.getArg(1);
		midifile.read(options.getArg(1));
	}
	else {
		cin >> fn;
		midifile.read(fn);
	}
	string ofn = "result_";
	ofn.append(fn, 0, fn.size() - 4);
	ofn.append(".txt");
	fstream output;
	output.open(ofn, ios::out);
	int tracks = midifile.getTrackCount();
	cout << "TPQ: " << midifile.getTicksPerQuarterNote() << endl;
	output << "TPQ: " << midifile.getTicksPerQuarterNote() << endl;
	if (tracks > 1) {
		cout << "TRACKS: " << tracks << endl;
		output << "TRACKS: " << tracks << endl;
	}
	for (int track = 0; track < tracks; track++) {
		if (tracks > 1) {
			cout << "\nTrack " << track << endl;
			output << "\nTrack " << track << endl;
		}
		for (int event = 0; event < midifile[track].size(); event++) {
			cout << dec << midifile[track][event].tick;
			output << dec << midifile[track][event].tick;
			cout << '\t' << hex;
			output << '\t' << hex;
			for (int i = 0; i<midifile[track][event].size(); i++) {
				cout << (int)midifile[track][event][i] << ' ';
				output << (int)midifile[track][event][i] << ' ';
			}
			cout << endl;
			output << endl;
		}
	}

	return 0;
}