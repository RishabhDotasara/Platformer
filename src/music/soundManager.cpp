#include "soundManager.hpp"
#include <algorithm>

SoundManager::SoundManager() 
    : currentMusic(nullptr), masterVolume(100.0f), soundVolume(100.0f), 
      musicVolume(100.0f), soundEnabled(true), musicEnabled(true) {
    
    // Pre-allocate sound objects for better performance
    activeSounds.reserve(16);  // Support up to 16 simultaneous sounds
}

bool SoundManager::loadSound(const std::string& name, const std::string& filePath) {
    // Check if already loaded
    if (soundBuffers.find(name) != soundBuffers.end()) {
        std::cout << "Sound '" << name << "' already loaded!" << std::endl;
        return true;
    }
    
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        std::cerr << "Error: Failed to load sound '" << name << "' from: " << filePath << std::endl;
        return false;
    }
    
    soundBuffers[name] = std::move(buffer);
    std::cout << "Successfully loaded sound: " << name << std::endl;
    return true;
}

void SoundManager::playSound(const std::string& name, float volume, float pitch) {
    if (!soundEnabled) return;
    
    // Find the sound buffer
    auto it = soundBuffers.find(name);
    if (it == soundBuffers.end()) {
        std::cerr << "Error: Sound '" << name << "' not found!" << std::endl;
        return;
    }
    
    // Get an available sound object
    sf::Sound* sound = getAvailableSound();
    if (!sound) {
        std::cerr << "Warning: No available sound slots for '" << name << "'!" << std::endl;
        return;
    }
    
    // Configure and play the sound
    sound->setBuffer(it->second);
    sound->setVolume((volume * soundVolume * masterVolume) / 10000.0f);  // Normalize to 0-100
    sound->setPitch(pitch);
    sound->play();
}

bool SoundManager::loadMusic(const std::string& name, const std::string& filePath) {
    // Check if already loaded
    if (musicTracks.find(name) != musicTracks.end()) {
        std::cout << "Music '" << name << "' already loaded!" << std::endl;
        return true;
    }
    
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filePath)) {
        std::cerr << "Error: Failed to load music '" << name << "' from: " << filePath << std::endl;
        return false;
    }
    
    musicTracks[name] = std::move(music);
    std::cout << "Successfully loaded music: " << name << std::endl;
    return true;
}

void SoundManager::playMusic(const std::string& name, bool loop) {
    // add music checking if a sound track is finished playing.
    if (!musicEnabled) return;
    
    auto it = musicTracks.find(name);
    if (it == musicTracks.end()) {
        std::cerr << "Error: Music '" << name << "' not found!" << std::endl;
        return;
    }
    
    // Stop current music if playing
    if (currentMusic && currentMusic->getStatus() == sf::Music::Playing) {
        currentMusic->stop();
    }
    
    // Play new music
    currentMusic = it->second.get();
    currentMusic->setLoop(loop);
    currentMusic->setVolume((musicVolume * masterVolume) / 100.0f);
    currentMusic->play();
    
    std::cout << "Playing music: " << name << std::endl;
}

// void SoundManager::pauseMusic() {
//     if (currentMusic) {
//         currentMusic->pause();
//     }
// }

void SoundManager::stopMusic() {
    if (currentMusic) {
        currentMusic->stop();
        currentMusic = nullptr;
    }
}

void SoundManager::stopAllSounds() {
    for (auto& sound : activeSounds) {
        if (sound.getStatus() == sf::Sound::Playing) {
            sound.stop();
        }
    }
}

void SoundManager::setMasterVolume(float volume) {
    masterVolume = std::clamp(volume, 0.0f, 100.0f);
    
    // Update current music volume
    if (currentMusic) {
        currentMusic->setVolume((musicVolume * masterVolume) / 100.0f);
    }
}

void SoundManager::setSoundVolume(float volume) {
    soundVolume = std::clamp(volume, 0.0f, 100.0f);
}

void SoundManager::setMusicVolumeControl(float volume) {
    musicVolume = std::clamp(volume, 0.0f, 100.0f);
    
    // Update current music volume
    if (currentMusic) {
        currentMusic->setVolume((musicVolume * masterVolume) / 100.0f);
    }
}

void SoundManager::enableSound(bool enable) {
    soundEnabled = enable;
    if (!enable) {
        stopAllSounds();
    }
}

void SoundManager::enableMusic(bool enable) {
    musicEnabled = enable;
    if (!enable && currentMusic) {
        currentMusic->pause();
    } else if (enable && currentMusic && currentMusic->getStatus() == sf::Music::Paused) {
        currentMusic->play();
    }
}

void SoundManager::update() {
    cleanupFinishedSounds();
}

sf::Sound* SoundManager::getAvailableSound() {
    // First, try to find a stopped sound
    for (auto& sound : activeSounds) {
        if (sound.getStatus() == sf::Sound::Stopped) {
            return &sound;
        }
    }
    
    // If no stopped sound found and we haven't reached capacity, create new one
    if (activeSounds.size() < activeSounds.capacity()) {
        activeSounds.emplace_back();
        return &activeSounds.back();
    }
    
    return nullptr;  // No available sound slots
}

void SoundManager::cleanupFinishedSounds() {
    // Remove sounds that have finished playing (optional optimization)
    // For now, we just reuse the existing sound objects
}

bool SoundManager::hasSound(const std::string& name) const {
    return soundBuffers.find(name) != soundBuffers.end();
}

bool SoundManager::hasMusic(const std::string& name) const {
    return musicTracks.find(name) != musicTracks.end();
}

bool SoundManager::isMusicPlaying() const {
    return currentMusic && currentMusic->getStatus() == sf::Music::Playing;
}
