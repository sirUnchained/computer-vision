#include <iostream>
#include <opencv2/opencv.hpp>

// validation function
void validate_alpha_beta(double alpha, int beta)
{
    if (alpha > 3.0 || beta > 100 || alpha < 0.1 || beta < 0)
    {
        std::cerr << "Invalid alpha or beta input!\n";
        std::cerr << "Alpha range: 0.1 - 3.0\n";
        std::cerr << "Beta range: 0 - 100\n";
        exit(-1);
    }
}

int main(int argc, char const *argv[])
{
    // Load image
    cv::Mat img = cv::imread("../images/input.jpg", cv::IMREAD_COLOR);
    if (img.empty())
    {
        std::cerr << "No image found!\n";
        return -1;
    }

    // show original image
    cv::namedWindow("Original Image", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Original Image", img);
    cv::waitKey();

    // Get user input for contrast (alpha) and brightness (beta)
    double alpha = 0.1;
    int beta = 0;

    std::cout << "Enter alpha (0.1-3.0): ";
    std::cin >> alpha;
    std::cout << "Enter beta (0-100): ";
    std::cin >> beta;

    // Validate input
    validate_alpha_beta(alpha, beta);

    // Apply contrast and brightness adjustment
    // Formula: output = alpha * input + beta
    cv::Mat out;
    cv::convertScaleAbs(img, out, alpha, beta);

    // Show result
    cv::namedWindow("Adjusted Image", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Adjusted Image", out);
    cv::waitKey();

    return 0;
}