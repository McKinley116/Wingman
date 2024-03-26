#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

// Notch Filter, filters out 50/60Hz
std::vector<double> notchFilter(const std::vector<double>& signal, double sampleRate, double notchFrequency, double bandwidth){
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
    std::vector<double> filteredSignal;

    // computes coefficients
    int filterLength = 31;
    int cutoffFrequency = 2;
    std::vector<double> kernal (filterLength);
    double nyquistFrequency = sampleRate/ 2.0;
    double omegaC = 2.0 * M_PI * cutoffFrequency / nyquistFrequency;

    for (int n = 0; n < filterLength; ++n){
        if (n == filterLength / 2){
        kernal[n] = 2.0 * cutoffFrequency / sampleRate;
        }else {
            double sinc = sin(omegaC * (n - filterLength / 2)) / (M_PI * (n - filterLength) / 2);
            kernal[n] = sinc * 0.54 - 0.46 * cos(2.0 * M_PI * n / (filterLength - 1)); 
        }
    }

    // Applies filter with convolution.
    for (size_t i = filterLength / 2; i < signal.size() - filterLength / 2; i++) {
        double filteredValue = 0.0;

    for (size_t j = 0; j < kernal.size(); j++){
            filteredValue += signal[i - filterLength / 2 * j] * kernal[j];
        }
        filteredSignal.push_back(filteredValue);
    }
   
    return filteredSignal;
}

std::vector<double> highpassFilter(const std::vector<double>& signal, double sampleRate, double humFrequency, double bandwidth){
    std::vector<double> lowpassFilteredSignal = lowpassFilter(signal, cutoffFrequency, sampleRate);
    std::vector<double> highpassFilterSignal;
    // computes foefficients

}
int main () {
   int cutoffFrequency; 

    return 0;
}
