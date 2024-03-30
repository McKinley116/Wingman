#include <initializer_list>
#include <iostream>
#include <cmath>
#include <vector>
#include <armadillo>

// EMG FILTERING MODULE
// Notch filter to filter out powerline frequency, filters out 50HZ and 60HZ.
arma::vec notchFilter(const arma::vec& signal, double sampleRate, double humFrequency, double bandwidth) {
    // Compute the frequency response of the notch filter
    arma::vec frequencies = arma::linspace<arma::vec>(0, sampleRate, signal.n_elem);
    arma::cx_vec transferFunction(signal.n_elem, arma::fill::ones);

    for (size_t i = 0; i < frequencies.n_elem; ++i) {
        if (std::abs(frequencies(i) - humFrequency) < bandwidth / 2) {
            transferFunction(i) = 0; // Apply notch filter
        }
    }

    // Apply the frequency response to the signal using the Fourier transform
    arma::cx_vec fft_signal = arma::fft(signal);
    arma::cx_vec filtered_fft_signal = fft_signal % transferFunction;

    // Inverse transform the filtered signal to obtain the time-domain signal
    arma::vec filteredSignal = arma::real(filtered_fft_signal);

    return filteredSignal;
}

// Function to implement a low-pass filter with 'same' convolution behavior, filter out above 150HZ
arma::vec lowPassFilter(const arma::vec& signal, int windowSize) {
    int halfWindowSize = windowSize / 2;
    arma::vec window(windowSize, arma::fill::ones); // Define a window for averaging
    arma::vec filteredSignal(signal.n_elem, arma::fill::zeros); // Initialize filtered signal with zeros

    // Perform convolution with 'same' behavior
    for (int i = halfWindowSize; i < signal.n_elem - halfWindowSize; ++i) {
        // Extract the segment of the signal for convolution
        arma::vec signalSegment = signal.subvec(i - halfWindowSize, i + halfWindowSize);

        // Ensure window and signal segment have the same number of elements
        if (signalSegment.n_elem == window.n_elem) {
            filteredSignal(i) = arma::dot(signalSegment, window) / windowSize;
        }
        else {
            filteredSignal(i) = signal(i);
        }
    }

    return filteredSignal;
}

// Function to implement a high-pass filter to filter out below 20HZ
arma::vec highPassFilter(const arma::vec& signal, int windowSize) {
    arma::vec lowPassFiltered = lowPassFilter(signal, windowSize); // Apply low-pass filtering
    arma::vec highPassFiltered = signal - lowPassFiltered; // Subtract low-pass filtered signal from original signal
    return highPassFiltered;
}

// GESTURE RECOGINITION MODULE
// Muscle Activation Functions using a Sigmoid Function. (x) = 1/1+e^-x
double muscleActivation(double time, double onsetTime, double peakActivation, double duration) {
    //Sigmoid Function for activation curve.
    double activation = peakActivation / (1 + exp(-(time - onsetTime)/ duration)); 
    return activation;
}


// VIRTUAL LIMB

// SIMULATION ENVIRONMENT
//The COMPONENTS part checks that OGRE was built the way we need it
//The CONFIG flag makes sure we get OGRE instead of OGRE-next
//find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
 
//add the source files as usual
//add_executable(0_Bootstrap Bootstrap.cpp)
 
//this also sets the includes and pulls third party dependencies
//target_link_libraries(0_Bootstrap OgreBites)


int main() {

    // EMG signal and window size input
    arma::vec emgSignal = {5.0, 6.0, 15.0, 10.0, 16.0, 20.0}; // These are in Hz.
    int windowSize = 5;
    // Apply low-pass filtering
    arma::vec lowPassFilteredSignal = lowPassFilter(emgSignal, windowSize);
    // Apply high-pass filtering
    arma::vec highPassFilteredSignal = highPassFilter(emgSignal, windowSize);
    // Display original and filtered signals
    std::cout << "Original EMG Signal:\n" << emgSignal << std::endl;
    std::cout << "Low-pass Filtered Signal:\n" << lowPassFilteredSignal << std::endl;
    std::cout << "High-pass Filtered Signal:\n" << highPassFilteredSignal << std::endl;

    double time = 5.0; // seconds
    double activationFist = muscleActivation(time, 1.0, 0.6, 1.5);
    double activatonOpen = muscleActivation(time, 1.0, 0.6, 1.5);
    double activatonTwoFinger = muscleActivation(time, 1.2, 1.6, 0.5);
    double activatonThreeFinger = muscleActivation(time, 1.5, 2.6, 1.5);
    double activatonPointing = muscleActivation(time, 1.0, 0.2, 1.0);
    double activatonHook = muscleActivation(time, 1.1, 1.6, 1.7);
    double activatonThumbsUp = muscleActivation(time, 1.0, 0.6, 1.5);
    double activatonRingFingerGrasp = muscleActivation(time, 1.3, 1.3, 1.8);
    std::cout << "Hand Gestures are classified as follows: running for 5 seconds" << std::endl; 
    std::cout << "G1 = Fist" << std::endl;   
    std::cout << "G2 = Open" << std::endl;
    std::cout << "G3 = Two Finger Pinch" << std::endl;
    std::cout << "G4 = Three Finger Pinch" << std::endl;
    std::cout << "G5 = Pointing" << std::endl;
    std::cout << "G6 = Hook" << std::endl;
    std::cout << "G7 = Thumbs Up" << std::endl;
    std::cout << "G8 = Ring Finger Grasp" << std::endl;
  


    return 0;
}

