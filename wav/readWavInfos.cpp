//readWavInfos.cpp

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>

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

int read_wav_file(std::string path, WAVHeader& header_container){
    
    std::ifstream ifs;

    ifs.open(path, std::ios::binary);
    if(!ifs) {
        std::cerr << "Open File Failed\n" << std::endl;
        return 1;
    }
    
    ifs.read(reinterpret_cast<char*>(&header_container),sizeof(WAVHeader));      
    if(!ifs) {
        std::cerr << "Reading Filstream Failed\n" << std::endl;
        return 1;
    }
    ifs.close();
    return 0;
}

// Übergebe einen Vector mit den Tags die du sehen willst
void print_wav_infos(WAVHeader header_container, std::vector<std::string> output_tags_vector){
   
   
    // Mapping der Tags zu den Struct-Membern
    std::unordered_map<std::string, std::string> tag_map = {
        {"riff_tag", std::string(header_container.riff_tag, 4)},
        {"wave_tag", std::string(header_container.wave_tag, 4)},
        {"fmt_tag", std::string(header_container.fmt_tag, 4)},
        {"data_tag", std::string(header_container.data_tag, 4)},
        {"riff_size", std::to_string(header_container.riff_size)},
        {"fmt_length", std::to_string(header_container.fmt_length)},
        {"audio_format", std::to_string(header_container.audio_format)},
        {"num_channels", std::to_string(header_container.num_channels)},
        {"sample_rate", std::to_string(header_container.sample_rate)},
        {"byte_rate", std::to_string(header_container.byte_rate)},
        {"block_align", std::to_string(header_container.block_align)},
        {"bits_per_sample", std::to_string(header_container.bits_per_sample)},
        {"data_length", std::to_string(header_container.data_length)}
    };
   
    for(auto tag : output_tags_vector){
        if(tag_map.find(tag) != tag_map.end()){
            std::cout << tag << ": " << tag_map[tag] << std::endl;
        } else {
            std::cerr << "Unbekannter Tag: " << tag << std::endl;
        }
    }
}

void calculate_wav_properties(const WAVHeader& header) {
    double byte_rate = header.sample_rate * header.num_channels * header.bits_per_sample / (double)8;
    double block_align = header.num_channels * header.bits_per_sample / (double)8;
    double num_samples = header.data_length / (double)block_align;

    std::cout << "Byte Rate: " << byte_rate << " Bytes/Sekunde" << std::endl;
    std::cout << "Block Align: " << block_align << " Bytes" << std::endl;
    std::cout << "Number of Samples: " << num_samples << std::endl;
    std::cout << "Duration: " << static_cast<double>(num_samples) / (double)header.sample_rate << " Sekunden" << std::endl;
}

void show_samples(int sample_amount, const std::string& path, const WAVHeader& header) {
    // Öffne die Datei
    std::ifstream ifs(path, std::ios::binary);
    if (!ifs) {
        std::cerr << "Error opening file: " << path << std::endl;
        return;
    }

    // Überspringe den Header (44 Bytes)
    ifs.seekg(44, std::ios::beg);

    // Lese die Daten in einen String
    std::string data(header.data_length, '\0');
    ifs.read(&data[0], header.data_length);

    if (!ifs) {
        std::cerr << "Error reading WAV data" << std::endl;
        return;
    }

    // Erstelle einen stringstream aus den Daten
    std::stringstream ss(data);

    // Berechne die Blockgröße (Bytes pro Sample-Block)
    uint16_t block_align = header.num_channels * header.bits_per_sample / 8;

    std::cout << "Showing " << sample_amount << " samples:" << std::endl;

    // Lese und zeige die Samples an
    for (int i = 0; i < sample_amount; ++i) {
        for (int ch = 0; ch < header.num_channels; ++ch) {
            if (header.bits_per_sample == 16) {
                // 16-Bit-Samples (2 Bytes pro Sample)
                int16_t sample = 0;
                ss.read(reinterpret_cast<char*>(&sample), sizeof(sample));
                std::cout << "Sample " << i << " [Channel " << ch + 1 << "]: " << sample << std::endl;
            } else if (header.bits_per_sample == 8) {
                // 8-Bit-Samples (1 Byte pro Sample)
                int8_t sample = 0;
                ss.read(reinterpret_cast<char*>(&sample), sizeof(sample));
                std::cout << "Sample " << i << " [Channel " << ch + 1 << "]: " << static_cast<int>(sample) << std::endl;
            } else {
                std::cerr << "Unsupported bit depth: " << header.bits_per_sample << std::endl;
                return;
            }
        }
    }
}

int main(){
    WAVHeader header_container;
    read_wav_file("ausgabe.wav", header_container);
    std::vector<std::string> output_tags = {"sample_rate", "bits_per_sample", "num_channels"};
    print_wav_infos( header_container, output_tags );
    calculate_wav_properties(header_container);
    show_samples(10, "ausgabe.wav", header_container);
}