#include <iostream>
#include <string>
#include <cstdlib> // for system function
#include <fstream>
#include "ffmpeg_bytes.h"

using namespace std;

void create_temp_ffmpeg() {
    string temp_path = "ffmpeg_temp.exe";
    ofstream ofs(temp_path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(ffmpeg_bytes), sizeof(ffmpeg_bytes));
}

int main(int argc, char* argv[]){
    if(argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
    
    create_temp_ffmpeg();
    string input = argv[1];
    string output = argv[2];

    string command = "ffmpeg_temp -i " + input + " " + output;

    system(command.c_str());
    remove("ffmpeg_temp.exe");
    return 0;
}
