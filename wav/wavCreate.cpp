#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdint>

typedef struct WAV_HEADER {
    uint8_t RIFF[4] = {'R', 'I', 'F', 'F'};
    uint32_t ChunkSize;
    uint8_t WAVE[4] = {'W', 'A', 'V', 'E'};
    uint8_t fmt[4] = {'f', 'm', 't', ' '};
    uint32_t Subchunk1Size = 16;
    uint16_t AudioFormat = 1;
    uint16_t NumOfChan = 1;
    uint32_t SamplesPerSec = 44100;
    uint32_t bytesPerSec = 44100 * 2;
    uint16_t blockAlign = 2;
    uint16_t bitsPerSample = 16;
    uint8_t Subchunk2ID[4] = {'d', 'a', 't', 'a'};
    uint32_t Subchunk2Size;
} wav_hdr;

// 🎯 Berechne ChunkSize & Subchunk2Size basierend auf Dauer
void aktualisiereHeaderMitDauer(wav_hdr& header, int sekunden) {
    uint32_t numSamples = header.SamplesPerSec * sekunden;
    uint16_t bytesPerSample = (header.bitsPerSample / 8) * header.NumOfChan;
    header.Subchunk2Size = numSamples * bytesPerSample;
    header.ChunkSize = 36 + header.Subchunk2Size;
}

// ✍️ Schreibe WAV-Datei mit Sinus oder Stille
void schreibeWavDatei(const std::string& dateiname, int sekunden, bool sinus = true, double freq = 440.0) {
    wav_hdr header;
    aktualisiereHeaderMitDauer(header, sekunden);

    std::ofstream ofs(dateiname, std::ios::binary);
    if (!ofs) {
        std::cerr << "Fehler beim Öffnen der Datei!" << std::endl;
        return;
    }

    // Header schreiben
    ofs.write(reinterpret_cast<const char*>(&header), sizeof(header));

    // Audio-Daten schreiben
    int samples = header.SamplesPerSec * sekunden;
    double amplitude = 32760; // max für 16-bit
    double twoPiF = 2.0 * M_PI * freq;
    for (int i = 0; i < samples; ++i) {
        int16_t sample;
        if (sinus) {
            sample = static_cast<int16_t>(amplitude * sin(twoPiF * i / header.SamplesPerSec));
        } else {
            sample = 0; // Stille
        }
        ofs.write(reinterpret_cast<const char*>(&sample), sizeof(int16_t));
    }

    ofs.close();
    std::cout << "Datei geschrieben: " << dateiname << std::endl;
}

int main() {
    // Erstelle 5 Sekunden 440-Hz-Sinuston
    schreibeWavDatei("ausgabe.wav", 5, true);
    return 0;
}
