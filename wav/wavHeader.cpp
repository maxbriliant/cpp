//wavHeader.cpp

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

struct WAVHeader {
    char riff_tag[4];       // "RIFF"
    uint32_t riff_size;     // Größe der Datei - 8 Bytes
    char wave_tag[4];       // "WAVE"

    // Format Subchunk
    char fmt_tag[4];        // "fmt "
    uint32_t fmt_length;    // Länge des restlichen Format-Subchunks
    uint16_t audio_format;  // Audio-Format: 1 = PCM
    uint16_t num_channels;  // Mono = 1, Stereo = 2
    uint32_t sample_rate;   // z.B. 44100
    uint32_t byte_rate;     // sample_rate * num_channels * bits_per_sample/8
    uint16_t block_align;   // num_channels * bits_per_sample/8
    uint16_t bits_per_sample;

    // Data Subchunk (folgt nach optionalen Feldern)
    char data_tag[4];       // "data"
    uint32_t data_length;   // Größe der Audiodaten in Bytes
};

int main() {
	std::ifstream ifs{};
	ifs.open("/home/mx/Desktop/Meilssa Voice/gurke.wav", std::ios::binary);

	if (!ifs) {
		std::cerr << "Error opening file" << std::endl;
		return 1;
	}

	WAVHeader header;
	ifs.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

	if (!ifs) {
		std::cerr << "Error reading WAV header" << std::endl;
		return 1;
	}

	std::cout << "RIFF-TAG: " << std::string(header.riff_tag, 4) << "\n";
	std::cout << "WAVE-TAG: " << std::string(header.wave_tag, 4) << "\n";
	std::cout << "FMT -TAG: " << std::string(header.fmt_tag, 4) << "\n";

	return 0;
}