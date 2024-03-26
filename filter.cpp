#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>


// Notch Filter: Filters out 50/60Hz
std::vector<double> notchFilter(const std::vector<double>& signal, double sampleRate, double notchFrequency, double bandwidth) {
    std::vector<double> filteredSignal;
    
    // Compute filter coefficients
    double w0 = 2.0 * M_PI * notchFrequency / sampleRate;
    double alpha = sin(w0) / (2.0 * bandwidth);
    double a0 = 1.0 + alpha;
    double a1 = -2.0 * cos(w0);
    double a2 = 1.0 - alpha;
    double b0 = 1.0;
    double b1 = -2.0 * cos(w0);
    double b2 = 1.0 + alpha;

    // Initialize filter variables
    double x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0;

    // Apply filter to signal
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

// Lowpass Filter: Filters out frequencies above cutoffFrequency
std::vector<double> lowpassFilter(const std::vector<double>& signal, double sampleRate, double cutoffFrequency, double bandwidth) {
    std::vector<double> filteredSignal;

    // Compute filter kernel coefficients
    int filterLength = 31; // Adjust filter length as needed
    std::vector<double> kernel(filterLength);
    double nyquistFrequency = sampleRate / 2.0;
    double omegaC = 2.0 * M_PI * cutoffFrequency / nyquistFrequency;

    for (int n = 0; n < filterLength; ++n) {
        if (n == filterLength / 2) {
            kernel[n] = 2.0 * cutoffFrequency / sampleRate;
        } else {
            double sinc = sin(omegaC * (n - filterLength / 2)) / (M_PI * (n - filterLength / 2));
            kernel[n] = sinc * 0.54 - 0.46 * cos(2.0 * M_PI * n / (filterLength - 1)); 
        }
    }

    // Apply filter with convolution
    for (size_t i = filterLength / 2; i < signal.size() - filterLength / 2; i++) {
        double filteredValue = 0.0;

        for (size_t j = 0; j < kernel.size(); j++) {
            filteredValue += signal[i - filterLength / 2 * j] * kernel[j];
        }
        filteredSignal.push_back(filteredValue);
    }
   
    return filteredSignal;
}

