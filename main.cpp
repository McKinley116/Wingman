#include <iostream>
#include <iomanip> // For alignment
#include <chrono> // For pauses
#include <thread> // For pauses
#include <cmath>
#include <vector>
#include <map>
#include <cstdlib> // For std::rand() and std::srand()
#include <ctime> // For srand(time(x)
#include <algorithm> // for decision tree


// Notch filter to filter out powerline frequency, filters out 50HZ and 60HZ.
std::vector<double> notchFilter(const std::vector<double>& signal, double sampleRate, double humFrequency, double bandwidth) {
// Compute the frequency response of the notch filter
    std::vector<double> frequencies(signal.size());
    for (size_t i = 0; i < frequencies.size(); ++i) {
    frequencies[i] = i * sampleRate / frequencies.size();
    }
    std::vector<double> transferFunction(signal.size(), 1.0);
    for (size_t i = 0; i < frequencies.size(); ++i) {
    if (std::abs(frequencies[i] - humFrequency) < bandwidth / 2) {
    transferFunction[i] = 0; // Apply notch filter
    }
}
// Apply the frequency response to the signal
std::vector<double> filteredSignal(signal.size(), 0.0);
    for (size_t i = 0; i < signal.size(); ++i) {
    filteredSignal[i] = signal[i] * transferFunction[i];
    }
    return filteredSignal;
}
// Function to implement a low-pass filter with 'same' convolution behavior, filter out above 150HZ
std::vector<double> lowPassFilter(const std::vector<double>& signal, int windowSize) {
    int halfWindowSize = windowSize / 2;
    std::vector<double> window(windowSize, 1.0); // Define a window for averaging
    std::vector<double> filteredSignal(signal.size(), 0.0); // Initialize filtered signal with zeros

// Perform convolution with 'same' behavior
    for (int i = halfWindowSize; i < signal.size() - halfWindowSize; ++i) {
// Extract the segment of the signal for convolution
    double sum = 0.0;
    for (int j = -halfWindowSize; j <= halfWindowSize; ++j) {
    sum += signal[i + j] * window[j + halfWindowSize];
    }
    filteredSignal[i] = sum / windowSize;
    }
    return filteredSignal;
}
// Function to implement a high-pass filter to filter out below 20HZ
std::vector<double> highPassFilter(const std::vector<double>& signal, int windowSize) {
    std::vector<double> lowPassFiltered = lowPassFilter(signal, windowSize); // Apply low-pass filtering
    std::vector<double> highPassFiltered(signal.size(), 0.0); // Subtract low-pass filtered signal from original signal
    for (size_t i = 0; i < signal.size(); ++i) {
    highPassFiltered[i] = signal[i] - lowPassFiltered[i];
    }
    return highPassFiltered;
}
//GESTURE CLASSES
enum Gesture {
    FIST,
    OPEN,
    TWO_FINGER_PINCH,
    THREE_FINGER_PINCH,
    POINTING,
    HOOK,
    THUMBS_UP,
    RING_FINGER_GRASP,
    NUM_GESTURES
};
//GESTURE STRUCTURE
struct GestureData {
    Gesture gesture;
    std::vector<double> emgSignal;
};

//GENERATES EMG SIGNAL (uses a rand(s))
std::vector<double> generateEMGSignal(int numSample, Gesture gesture) {
    std::vector<double> emgSignal(numSample);
    std::srand(time(0));
    for (int i = 0; i < numSample; ++i) {
    double Randomnum = static_cast<double>(rand()) / RAND_MAX;
    double NumSmall = (1 - 0.0001) * Randomnum + 0.0001;
    emgSignal[i] = NumSmall;
    }
    return emgSignal;
}

// Function to compute the Root Mean Square (RMS) of a signal
double computeRMS(const std::vector<double>& signal) {
    double sumOfSquares = 0.0;
    for (double value : signal) {
        sumOfSquares += value * value;
    }
    return std::sqrt(sumOfSquares / signal.size());
}

// Function to compute the Mean Absolute Value (MAV) of a signal
double computeMAV(const std::vector<double>& signal) {
    double sumOfAbs = 0.0;
    for (double value : signal) {
        sumOfAbs += std::abs(value);
    }
    return sumOfAbs / signal.size();
}

//start of decision tree..
struct TreeNode{
    int featureIndex;
    double threshold;
    int predictedClass;
    TreeNode * leftChild;
    TreeNode * rightChild;
    TreeNode(int featureIndex, double threshold, int predictedClass)
        : featureIndex(featureIndex), threshold(threshold), predictedClass(predictedClass), leftChild(nullptr), rightChild(nullptr) {}
};



int main() {
    using namespace std::this_thread;
    using namespace std::chrono;
    std::cout << "Loading Gestures....." << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << std::endl;
    sleep_until(system_clock::now() + seconds(1));
    std::cout << "Hand Gestures are classified as follows: " << std::endl;
    std::cout << "----------------------" << std::endl;
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "G1 = Fist" << std::endl;
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "G2 = Open" << std::endl;
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "G3 = Two Finger Pinch" << std::endl;
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "G4 = Three Finger Pinch" << std::endl;
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "G5 = Pointing" << std::endl;
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "G6 = Hook" << std::endl;
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "G7 = Thumbs Up" << std::endl;
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "G8 = Ring Finger Grasp" << std::endl;
    std::cout << std::endl;
    sleep_until(system_clock::now() + milliseconds(1500));
    std::cout << "Ready to generate EMGs....." << std::endl;
    std::cout << "-----------------------" << std::endl;
    sleep_until(system_clock::now() + milliseconds(500));

    std::cout << "Please enter a sample size to generate an EMG signal for Wingman Gestures...." << std::endl;
    int numSample;
    std::cin >> numSample;
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "Please enter a window size....." << std::endl;
    int windowSize;
    std::cin >> windowSize;
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "------------------------" << std::endl;
    std::cout << "Please choose a gesture...." << std::endl;
//ALLOWS USER TO CHOOSE A GESTURE THEN GENERATE EMG
    int gestureNumber;
    std::cin >> gestureNumber;
    sleep_until(system_clock::now() + milliseconds(1000));
    Gesture selectedGesture;

switch (gestureNumber) {
    case 1:
    selectedGesture = FIST;
    break;
    case 2:
    selectedGesture = OPEN;
    break;
    case 3:
    selectedGesture = TWO_FINGER_PINCH;
    break;
    case 4:
    selectedGesture = THREE_FINGER_PINCH;
    break;
    case 5:
    selectedGesture = POINTING;
    break;
    case 6:
    selectedGesture = HOOK;
    break;
    case 7:
    selectedGesture = THUMBS_UP;
    break;
    case 8:
    selectedGesture = RING_FINGER_GRASP;
    break;
    default:
    std::cerr << "Invalid gesture number!" << std::endl;

    return 1; // Exit with error code
}
// Map gesture enum values to their corresponding names
std::map<Gesture, std::string> gestureNames = {
    {FIST, "Fist"},
    {OPEN, "Open"},
    {TWO_FINGER_PINCH, "Two Finger Pinch"},
    {THREE_FINGER_PINCH, "Three Finger Pinch"},
    {POINTING, "Pointing"},
    {HOOK, "Hook"},
    {THUMBS_UP, "Thumbs Up"},
    {RING_FINGER_GRASP, "Ring Finger Grasp"}
};
//THIS GENERATES A EMG SIGNAL BASED ON USER INPUT OF SAMPLE SIZE, WINDOW SIZE, AND GESTURE SELECTION...
std::vector<double> emgSignal = generateEMGSignal(numSample, selectedGesture);
    std::cout << std::fixed << std::setprecision(4) << "EMG Signal generated for " <<
    gestureNames[selectedGesture] << " gesture:\n" << std::endl;
    for (const auto& val : emgSignal) {
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << val << " " << std::endl;
}

    std::cout << std::endl;
    sleep_until(system_clock::now() + milliseconds(1000));
    std::cout << "Filtering EMG signal..." << std::endl;
    sleep_until(system_clock::now() + milliseconds(250));
    for (int x = 0; x < 5; x++){
    std::cout << "Loading" << std::endl;
// Move the cursor up one line
    std::cout << "\033[F";
// Clear the line I don't know why these do what they do...
    std::cout << "\033[K";
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "Loading." << std::endl;
// Move the cursor up one line
    std::cout << "\033[F";
// Clear the line
    std::cout << "\033[K";
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "Loading.." << std::endl;
// Move the cursor up one line
    std::cout << "\033[F";
// Clear the line
    std::cout << "\033[K";
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << "Loading..." << std::endl;
    sleep_until(system_clock::now() + milliseconds(500));
// Move the cursor up one line
    std::cout << "\033[F";
// Clear the line
    std::cout << "\033[K";
}

//FILTERS THE USERS GENERATED EMG SIGNALS...
    double sampleRate = 10; // If sample rate is too high, output will only be zeros..
    double humFrequency = 60;
    double bandwidth = 2;
    std::vector<double> filteredSignal = notchFilter(emgSignal, sampleRate, humFrequency,
    bandwidth);
    filteredSignal = lowPassFilter(filteredSignal, windowSize);
    filteredSignal = highPassFilter(filteredSignal, windowSize);
    std::cout << "Filtered EMG signal for " << gestureNames[selectedGesture] << " gesture:\n" <<
    std::endl;
    for (const auto& val : filteredSignal) {
    sleep_until(system_clock::now() + milliseconds(500));
    std::cout << val << " " << std::endl;
    }
    std::cout << std::endl;
    std::vector<double> extractedFilter = filteredSignal;
    std::cout << "Ready to extract features..." << std::endl;
    
    // Compute RMS and MAV
    double rms = computeRMS(extractedFilter);
    double mav = computeMAV(extractedFilter);

    std::vector<double> featureVector;
    featureVector.push_back(rms);
    featureVector.push_back(mav);

    std::cout << "Extracted Features...." << std::endl;
    std::cout << "RMS: " << rms << std::endl;
    std::cout << "MAV: " << mav << std::endl;
    return 0;
}
