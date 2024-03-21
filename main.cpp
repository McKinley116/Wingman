#include <initializer_list>
#include <iostream>
#include <cmath>
#include <armadillo>

// Initialize variables and modules
void Initialize_EMG_Signal_Processing_Module() {
    std::cout << "Initalizing EMG Signal Processing Module..." << std::endl; 
}

void Initalize_Gesture_Regcognition_Module(){
    std::cout << "Initalizing Gesture Recoginition Module.." << std::endl;
}

void Initalize_Virtual_Prosthetic_Limb() {
    std::cout << "Powering Wingman Arm..." << std::endl;
}

void Initialize_Simulation_Environment() {
    std::cout << "Setting up Environment..." << std::endl;
}

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
            // Handle mismatch in number of elements (optional)
            // You can choose to skip or handle this case as per your requirements
            // For now, we'll skip the convolution at this index
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

// Muscle Activation Function using a Sigmoid Function. (x) = 1/1+e^-x
double muscleActivation(double time, double onsetTime, double peakActivation, double duration) {
    //Sigmoid Function for activation curve.
    double activation = peakActivation / (1 + exp(-(time - onsetTime)/ duration)); 
    return activation;
}
// List of Hand gesture identifications (G1-G8) 
// G1 = Fist
// G2 = Open
// G3 = Two-Finger Pinch
// G4 = Three-Finger Pinch
// G5 = Pointing
// G6 = Hook
// G7 = Thumbs up
// G8 = Ring finger Grasp

int main() {
        Initialize_EMG_Signal_Processing_Module();

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

    Initalize_Gesture_Regcognition_Module();



    //Test for Muscle Activation Function
    double time = 2.0;
    double onsetTime = 1.0;
    double peakActivation = 1.5;
    double duration = 3.0;
    double result = muscleActivation(time, onsetTime, peakActivation, duration);


    return 0;
}
// Main loop to continoulsy read user input
// Capture simulated EMG signals or gestures from user input
//emg_signals = Capture_EMG_Signals_From_User()
//recoginized_gesture = Recoginize_Gesture_From_User_Input()

// Process EMG signals and recoginze gestures
//processed_signals = Process_EMG_Signals(emg_signals)
//limb_command = Translate_Gensture_To_Limb_Command(recognized_gesture)

// Control virtual prosthetic limb
//Move_Virtual_Limb(limb_commands)

// Update simulation environtment and display
//Update_Simulation_Envrionment()
//Display_Virtual_Limb()

// Check for user input to exit
//if (User_PResses_Exit_Button())
 //   simulation_running = false;


