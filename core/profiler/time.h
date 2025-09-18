#include <iostream>
#include <chrono>
#include <deque>

class SmoothFPSCounter {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
    std::deque<float> fpsHistory;
    const int historySize = 30; // количество кадров для усреднения
    float smoothedFPS;
    
public:
    SmoothFPSCounter() : smoothedFPS(0.0f) {
        lastTime = std::chrono::high_resolution_clock::now();
    }
    
    void update() {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count();
        
        lastTime = currentTime;
        
        if (elapsed == 0) return;
        
        float instantFPS = 1000000.0f / elapsed;
        
        // Добавляем в историю
        fpsHistory.push_back(instantFPS);
        if (fpsHistory.size() > historySize) {
            fpsHistory.pop_front();
        }
        
        // Вычисляем среднее
        float sum = 0.0f;
        for (float fps : fpsHistory) {
            sum += fps;
        }
        smoothedFPS = sum / fpsHistory.size();
    }
    
    float getFPS() const {
        return smoothedFPS;
    }
    
    float getInstantFPS() const {
        if (fpsHistory.empty()) return 0.0f;
        return fpsHistory.back();
    }
};