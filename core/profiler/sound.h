// audio_engine.h
#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <mutex>

class AudioEngine {
public:
    struct SoundSource {
        ALuint source;
        ALuint buffer;
        std::string name;
        bool looping;
        float volume;
        float pitch;
    };

    static AudioEngine& getInstance() {
        static AudioEngine instance;
        return instance;
    }

    // Добавьте этот метод
    ALuint getSourceByName(const std::string& soundName) {
        for (const auto& source : sources) {
            if (source.name == soundName) {
                return source.source;
            }
        }
        return 0; // Возвращаем 0, если источник не найден
    }

    bool initialize() {
        // Получаем устройство по умолчанию
        device = alcOpenDevice(nullptr);
        if (!device) {
            std::cerr << "Failed to open audio device" << std::endl;
            return false;
        }

        // Создаем контекст
        context = alcCreateContext(device, nullptr);
        if (!context) {
            std::cerr << "Failed to create audio context" << std::endl;
            return false;
        }

        // Активируем контекст
        if (!alcMakeContextCurrent(context)) {
            std::cerr << "Failed to make context current" << std::endl;
            return false;
        }

        // Проверяем наличие ошибок
        ALenum error = alGetError();
        if (error != AL_NO_ERROR) {
            std::cerr << "OpenAL error after initialization: " << error << std::endl;
            return false;
        }

        return true;
    }

    void shutdown() {
        // Останавливаем все источники и очищаем их
        stopAll();

        for (auto& source : sources) {
            alDeleteSources(1, &source.source);
            alDeleteBuffers(1, &source.buffer);
        }
        sources.clear();

        soundBuffers.clear();

        // Уничтожаем контекст и закрываем устройство
        alcMakeContextCurrent(nullptr);
        if (context) {
            alcDestroyContext(context);
            context = nullptr;
        }
        if (device) {
            alcCloseDevice(device);
            device = nullptr;
        }
    }

    ALuint loadSound(const std::string& filename, const std::string& soundName) {
        // Загружаем WAV файл
        ALuint buffer;
        alGenBuffers(1, &buffer);

        if (!loadWavFile(filename, buffer)) {
            std::cerr << "Failed to load sound: " << filename << std::endl;
            alDeleteBuffers(1, &buffer);
            return 0;
        }

        soundBuffers[soundName] = buffer;
        return buffer;
    }

    ALuint createSource(const std::string& soundName, bool looping = false, 
                       float volume = 1.0f, float pitch = 1.0f) {
        auto it = soundBuffers.find(soundName);
        if (it == soundBuffers.end()) {
            std::cerr << "Sound not found: " << soundName << std::endl;
            return 0;
        }

        ALuint source;
        alGenSources(1, &source);

        // Настраиваем источник
        alSourcei(source, AL_BUFFER, it->second);
        alSourcei(source, AL_LOOPING, looping ? AL_TRUE : AL_FALSE);
        alSourcef(source, AL_GAIN, volume);
        alSourcef(source, AL_PITCH, pitch);

        SoundSource soundSource;
        soundSource.source = source;
        soundSource.buffer = it->second;
        soundSource.name = soundName;
        soundSource.looping = looping;
        soundSource.volume = volume;
        soundSource.pitch = pitch;

        sources.push_back(soundSource);
        return source;
    }

    void playSound(ALuint source) {
        alSourcePlay(source);
    }

    void playSound(const std::string& soundName) {
        for (auto& source : sources) {
            if (source.name == soundName) {
                alSourcePlay(source.source);
                return;
            }
        }
        std::cerr << "Source not found: " << soundName << std::endl;
    }

    void stopSound(ALuint source) {
        alSourceStop(source);
    }

    void pauseSound(ALuint source) {
        alSourcePause(source);
    }

    void resumeSound(ALuint source) {
        alSourcePlay(source);
    }

    void setVolume(ALuint source, float volume) {
        alSourcef(source, AL_GAIN, volume);
        for (auto& s : sources) {
            if (s.source == source) {
                s.volume = volume;
                break;
            }
        }
    }

    void setPitch(ALuint source, float pitch) {
        alSourcef(source, AL_PITCH, pitch);
        for (auto& s : sources) {
            if (s.source == source) {
                s.pitch = pitch;
                break;
            }
        }
    }

    void setLooping(ALuint source, bool looping) {
        alSourcei(source, AL_LOOPING, looping ? AL_TRUE : AL_FALSE);
        for (auto& s : sources) {
            if (s.source == source) {
                s.looping = looping;
                break;
            }
        }
    }

    void setPosition(ALuint source, float x, float y, float z) {
        ALfloat position[] = { x, y, z };
        alSourcefv(source, AL_POSITION, position);
    }

    void setVelocity(ALuint source, float x, float y, float z) {
        ALfloat velocity[] = { x, y, z };
        alSourcefv(source, AL_VELOCITY, velocity);
    }

    void setListenerPosition(float x, float y, float z) {
        ALfloat position[] = { x, y, z };
        alListenerfv(AL_POSITION, position);
    }

    void setListenerVelocity(float x, float y, float z) {
        ALfloat velocity[] = { x, y, z };
        alListenerfv(AL_VELOCITY, velocity);
    }

    void setListenerOrientation(float atX, float atY, float atZ, 
                               float upX, float upY, float upZ) {
        ALfloat orientation[] = { atX, atY, atZ, upX, upY, upZ };
        alListenerfv(AL_ORIENTATION, orientation);
    }

    bool isPlaying(ALuint source) {
        ALint state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        return state == AL_PLAYING;
    }

    void stopAll() {
        for (auto& source : sources) {
            alSourceStop(source.source);
        }
    }

    void update() {
        // Можно добавить периодическое обновление, если нужно
        ALenum error = alGetError();
        if (error != AL_NO_ERROR) {
            std::cerr << "OpenAL error: " << error << std::endl;
        }
    }

private:
    ALCdevice* device = nullptr;
    ALCcontext* context = nullptr;
    std::vector<SoundSource> sources;
    std::unordered_map<std::string, ALuint> soundBuffers;

    AudioEngine() = default;
    ~AudioEngine() {
        shutdown();
    }

    AudioEngine(const AudioEngine&) = delete;
    AudioEngine& operator=(const AudioEngine&) = delete;

    bool loadWavFile(const std::string& filename, ALuint buffer) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return false;
        }

        char chunkId[5] = {0};
        uint32_t chunkSize;
        char format[5] = {0};

        // Читаем RIFF заголовок
        file.read(chunkId, 4);
        file.read(reinterpret_cast<char*>(&chunkSize), 4);
        file.read(format, 4);

        if (std::string(chunkId) != "RIFF" || std::string(format) != "WAVE") {
            std::cerr << "Not a valid WAV file" << std::endl;
            return false;
        }

        char subchunkId[5] = {0};
        uint32_t subchunkSize;
        uint16_t audioFormat;
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitsPerSample;

        // Ищем fmt chunk
        while (true) {
            file.read(subchunkId, 4);
            file.read(reinterpret_cast<char*>(&subchunkSize), 4);

            if (std::string(subchunkId) == "fmt ") {
                file.read(reinterpret_cast<char*>(&audioFormat), 2);
                file.read(reinterpret_cast<char*>(&numChannels), 2);
                file.read(reinterpret_cast<char*>(&sampleRate), 4);
                file.read(reinterpret_cast<char*>(&byteRate), 4);
                file.read(reinterpret_cast<char*>(&blockAlign), 2);
                file.read(reinterpret_cast<char*>(&bitsPerSample), 2);

                // Пропускаем оставшиеся байты в chunk
                if (subchunkSize > 16) {
                    file.seekg(subchunkSize - 16, std::ios::cur);
                }
                break;
            } else {
                // Пропускаем этот chunk
                file.seekg(subchunkSize, std::ios::cur);
            }

            if (file.eof()) {
                std::cerr << "fmt chunk not found" << std::endl;
                return false;
            }
        }

        // Ищем data chunk
        while (true) {
            file.read(subchunkId, 4);
            file.read(reinterpret_cast<char*>(&subchunkSize), 4);

            if (std::string(subchunkId) == "data") {
                break;
            } else {
                // Пропускаем этот chunk
                file.seekg(subchunkSize, std::ios::cur);
            }

            if (file.eof()) {
                std::cerr << "data chunk not found" << std::endl;
                return false;
            }
        }

        // Читаем аудио данные
        std::vector<char> data(subchunkSize);
        file.read(data.data(), subchunkSize);

        // Определяем формат OpenAL
        ALenum formatAL;
        if (numChannels == 1) {
            formatAL = (bitsPerSample == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
        } else {
            formatAL = (bitsPerSample == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
        }

        // Загружаем данные в буфер
        alBufferData(buffer, formatAL, data.data(), subchunkSize, sampleRate);

        file.close();
        return true;
    }
};