#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

class SoundManager {
private:
    // Sound effects storage
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    std::vector<sf::Sound> activeSounds;  // Pool of sound objects for multiple simultaneous sounds
    
    // Music storage
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> musicTracks;
    sf::Music* currentMusic;
    
    // Settings
    float masterVolume;
    float soundVolume;
    float musicVolume;
    bool soundEnabled;
    bool musicEnabled;
    
    // Helper functions
    sf::Sound* getAvailableSound();
    void cleanupFinishedSounds();
    
public:
    SoundManager();
    ~SoundManager() = default;
    
    // Sound effect management
    bool loadSound(const std::string& name, const std::string& filePath);
    void playSound(const std::string& name, float volume = 100.0f, float pitch = 1.0f);
    void stopAllSounds();
    
    // Music management
    bool loadMusic(const std::string& name, const std::string& filePath);
    void playMusic(const std::string& name, bool loop = true);
    void pauseMusic();
    void stopMusic();
    void setMusicVolume(float volume);
    
    // Volume control
    void setMasterVolume(float volume);      // 0-100
    void setSoundVolume(float volume);       // 0-100
    void setMusicVolumeControl(float volume);// 0-100
    
    // Enable/Disable
    void enableSound(bool enable);
    void enableMusic(bool enable);
    
    // Utility
    void update();  // Call this every frame to cleanup finished sounds
    bool hasSound(const std::string& name) const;
    bool hasMusic(const std::string& name) const;
    void listLoadedSounds() const;
    void listLoadedMusic() const;
    
    // Current state queries
    bool isMusicPlaying() const;
    std::string getCurrentMusicName() const;
    float getMasterVolume() const { return masterVolume; }
    float getSoundVolume() const { return soundVolume; }
    float getMusicVolume() const { return musicVolume; }
};