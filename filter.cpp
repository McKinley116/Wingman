#include <iostream>
#include <cmath>
#include <vector>

// Notch Filter, filters out 50/60Hz
std::vector<double> notchFilter(const std::vector<double>& signal, double sampleRate, double notchFrequency. double bandwidth){
    std::vector<double> filteredSignal;
    // Computes coefficients for filter
    double w0 = 2.0 * M_PI * notchFrequency / sampleRate;
    double alpha = sin(w0) / (2.0 * bandwidth);
    double a0 = 1.0 + alpha;
    double a1 = -2.0 * cos(w0);
    double a2 = 1.0 - alpha;
    double b0 = 1.0;
    double b1 = -2.0 * cos(w0);
    double b2 = 1.0 + alpha;
    // Filter variables
    double x1 = 0.0, x2 = 0.0, y1= 0.0, y2 = 0.0;
    //Applies filter to signal
    for (double x : signal) {
        double y = (b0 * x + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2) / a0;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
        filteredSignal.push_back(y);
    }
        return filteredSignal;
}

//Low Filter, filters out above 120Hz
    std::vector<double> lowpassFilter(const std::vector<double>& signal, double sampleRate, double humFrequency, double bandwidth){
    
}
int main () {
    

    return 0;
}
