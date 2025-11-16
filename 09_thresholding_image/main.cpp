#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * Displays an image in a window with optional waiting
 * @param img Image to display
 * @param name Window name
 * @param wait If true, waits for key press before continuing
 */
void show_img(const cv::Mat &img, const std::string &name, const bool wait = false) {
    cv::namedWindow(name, cv::WINDOW_GUI_EXPANDED);
    cv::imshow(name, img);
    if (wait) {
        std::cout << "Press any key to continue..." << std::endl;
        cv::waitKey(0);
    }
}

/**
 * Demonstrates different thresholding techniques on an image
 * @param img Input image (should be grayscale for proper thresholding)
 */
void thresholds(const cv::Mat &img) {
    cv::Mat out_img;

    // Convert to grayscale if image is color (important for thresholding)
    cv::Mat gray_img;
    if (img.channels() == 3) {
        cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
        std::cout << "Converted color image to grayscale for thresholding" << std::endl;
    } else {
        gray_img = img.clone();
    }

    std::cout << "\n=== THRESHOLDING TECHNIQUES DEMONSTRATION ===" << std::endl;

    // 1. Binary Threshold
    // Pixels > 127 become 255 (white), others become 0 (black)
    cv::threshold(gray_img, out_img, 127, 255, cv::THRESH_BINARY);
    show_img(out_img, "BINARY: >127=255, <=127=0", true);
    std::cout << "THRESH_BINARY: Values > 127 = 255, others = 0" << std::endl;

    // 2. Binary Inverse Threshold
    // Pixels > 127 become 0 (black), others become 255 (white)
    cv::threshold(gray_img, out_img, 127, 255, cv::THRESH_BINARY_INV);
    show_img(out_img, "BINARY_INV: >127=0, <=127=255", true);
    std::cout << "THRESH_BINARY_INV: Values > 127 = 0, others = 255" << std::endl;

    // 3. Truncate Threshold
    // Pixels > 127 are set to 127, others remain unchanged
    cv::threshold(gray_img, out_img, 127, 255, cv::THRESH_TRUNC);
    show_img(out_img, "TRUNC: >127=127, <=127=unchanged", true);
    std::cout << "THRESH_TRUNC: Values > 127 = 127, others unchanged" << std::endl;

    // 4. To Zero Threshold
    // Pixels <= 127 become 0, others remain unchanged
    cv::threshold(gray_img, out_img, 127, 255, cv::THRESH_TOZERO);
    show_img(out_img, "TOZERO: <=127=0, >127=unchanged", true);
    std::cout << "THRESH_TOZERO: Values <= 127 = 0, others unchanged" << std::endl;

    // 5. To Zero Inverse Threshold
    // Pixels > 127 become 0, others remain unchanged
    cv::threshold(gray_img, out_img, 127, 255, cv::THRESH_TOZERO_INV);
    show_img(out_img, "TOZERO_INV: >127=0, <=127=unchanged", true);
    std::cout << "THRESH_TOZERO_INV: Values > 127 = 0, others unchanged" << std::endl;

    cv::destroyAllWindows();
}

/**
 * Demonstrates adaptive thresholding techniques
 * @param img Input grayscale image
 */
void adaptive_thresholds(const cv::Mat &img) {
    cv::Mat gray_img;
    if (img.channels() == 3) {
        cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    } else {
        gray_img = img.clone();
    }

    std::cout << "\n=== ADAPTIVE THRESHOLDING TECHNIQUES ===" << std::endl;

    cv::Mat adaptive_mean, adaptive_gaussian;

    // Adaptive thresholding using mean of neighborhood
    cv::adaptiveThreshold(gray_img, adaptive_mean, 255,
                         cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2);
    show_img(adaptive_mean, "ADAPTIVE MEAN: Local mean thresholding", true);
    std::cout << "ADAPTIVE_THRESH_MEAN_C: Uses mean of neighborhood" << std::endl;

    // Adaptive thresholding using Gaussian weighted mean of neighborhood
    cv::adaptiveThreshold(gray_img, adaptive_gaussian, 255,
                         cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);
    show_img(adaptive_gaussian, "ADAPTIVE GAUSSIAN: Gaussian weighted thresholding", true);
    std::cout << "ADAPTIVE_THRESH_GAUSSIAN_C: Uses Gaussian weighted mean" << std::endl;
}

/**
 * Demonstrates Otsu's thresholding (automatic threshold selection)
 * @param img Input grayscale image
 */
void otsu_threshold(const cv::Mat &img) {
    cv::Mat gray_img;
    if (img.channels() == 3) {
        cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    } else {
        gray_img = img.clone();
    }

    std::cout << "\n=== OTSU'S THRESHOLDING (AUTOMATIC) ===" << std::endl;

    cv::Mat otsu_result;
    double otsu_thresh = cv::threshold(gray_img, otsu_result, 0, 255,
                                      cv::THRESH_BINARY | cv::THRESH_OTSU);

    show_img(otsu_result, "OTSU: Automatic threshold = " + std::to_string(otsu_thresh), true);
    std::cout << "Otsu's method found optimal threshold: " << otsu_thresh << std::endl;
    std::cout << "Automatically selects the best threshold value" << std::endl;
}

/**
 * Interactive thresholding with trackbar
 * @param img Input grayscale image
 */
void interactive_threshold(const cv::Mat &img) {
    cv::Mat gray_img;
    if (img.channels() == 3) {
        cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    } else {
        gray_img = img.clone();
    }

    std::cout << "\n=== INTERACTIVE THRESHOLDING ===" << std::endl;
    std::cout << "Use trackbar to adjust threshold value in real-time" << std::endl;
    std::cout << "Press ESC to exit interactive mode" << std::endl;

    cv::Mat result;
    int threshold_value = 127;
    int max_value = 255;

    cv::namedWindow("Interactive Thresholding", cv::WINDOW_GUI_EXPANDED);

    // Create trackbar callback function
    auto on_trackbar = [](int value, void* userdata) {
        auto data = static_cast<std::pair<cv::Mat*, cv::Mat*>*>(userdata);
        cv::Mat* src = data->first;
        cv::Mat* dst = data->second;

        cv::threshold(*src, *dst, value, 255, cv::THRESH_BINARY);

        // Add threshold value text to image
        cv::Mat display = dst->clone();
        if (display.channels() == 1) {
            cv::cvtColor(display, display, cv::COLOR_GRAY2BGR);
        }

        std::string text = "Threshold: " + std::to_string(value);
        cv::putText(display, text, cv::Point(10, 30),
                   cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);

        cv::imshow("Interactive Thresholding", display);
    };

    // Prepare user data for callback
    std::pair<cv::Mat*, cv::Mat*> user_data(&gray_img, &result);

    // Create trackbar
    cv::createTrackbar("Threshold", "Interactive Thresholding",
                      &threshold_value, max_value, on_trackbar, &user_data);

    // Initial call to display image
    on_trackbar(threshold_value, &user_data);

    // Wait for ESC key
    while (true) {
        int key = cv::waitKey(100) & 0xFF;
        if (key == 27) { // ESC key
            break;
        }
    }

    cv::destroyWindow("Interactive Thresholding");
}

int main() {
    std::cout << "=== OPENCV THRESHOLDING DEMONSTRATION ===" << std::endl;

    // Load and display gradient image
    cv::Mat img = cv::imread("../images/gradient.jpg", cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Error: Could not load gradient.jpg" << std::endl;
        return -1;
    }
    show_img(img, "Original Gradient Image", true);
    thresholds(img);

    // Additional demonstrations on gradient image
    adaptive_thresholds(img);
    otsu_threshold(img);
    interactive_threshold(img);

    // Load and display plate image
    cv::Mat plate_img = cv::imread("../images/plate.jpg", cv::IMREAD_COLOR);
    if (plate_img.empty()) {
        std::cerr << "Error: Could not load plate.jpg" << std::endl;
        return -1;
    }
    show_img(plate_img, "Original Plate Image", true);
    thresholds(plate_img);

    // Additional demonstrations on plate image
    adaptive_thresholds(plate_img);
    otsu_threshold(plate_img);

    std::cout << "\n=== PROGRAM COMPLETED ===" << std::endl;
    cv::destroyAllWindows();
    return 0;
}