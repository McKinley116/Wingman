#include <initializer_list>
#include <iostream>
#include <cmath>
#include <armadillo>

// Initialize variables and modules
//Initalize_EMG_Signal_Processing_Module()

// Function to implement a low-pass filter
arma::vec lowPassFilter(const arma::vec& signal, int windowSize) {
    arma::vec window(windowSize, arma::fill::ones); // Define a window for averaging
    arma::vec filteredSignal = arma::conv(signal, window) / windowSize; // Apply convolution with the window
    return filteredSignal;
}

// Function to implement a high-pass filter
arma::vec highPassFilter(const arma::vec& signal, int windowSize) {
    arma::vec lowPassFiltered = lowPassFilter(signal, windowSize); // Apply low-pass filtering
    arma::vec highPassFiltered = signal - lowPassFiltered; // Subtract low-pass filtered signal from original signal
    return highPassFiltered;
}
//Initalize_Gesture_Regcognition_Modle()

//Initalize_Virtual_Prosthetic_Limb()

//Initialize_Simulation_Environment()

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

//int main () { (THIS WAS TO TEST THE ARMADILLO LIBRARY)

//  arma::vec v = {1, 2, 3};
// std::cout << "vector v:\n" << v << std::endl;
// Function to implement a low-pass filter
int main() {
    // Sample EMG signal (replace with your actual signal)
    arma::vec emgSignal = {1, 2, 3, 4, 5, 4, 3, 2, 1};

    // Apply low-pass filtering with a window size of 3
    arma::vec lowPassFilteredSignal = lowPassFilter(emgSignal, 3);

    // Apply high-pass filtering with a window size of 3
    arma::vec highPassFilteredSignal = highPassFilter(emgSignal, 3);

    // Display original and filtered signals
    std::cout << "Original EMG Signal:\n" << emgSignal << std::endl;
    std::cout << "Low-pass Filtered Signal:\n" << lowPassFilteredSignal << std::endl;
    std::cout << "High-pass Filtered Signal:\n" << highPassFilteredSignal << std::endl;

    return 0;
}
//return 0;
//}
