#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

/**
 * Applies gamma correction using lookup table (LUT) for better performance
 */
cv::Mat gammaCorrectionLUT(const cv::Mat &img, double gamma)
{
    cv::Mat result;

    // Create lookup table
    cv::Mat lookup_table(1, 256, CV_8U);
    uchar *p = lookup_table.ptr();
    for (int i = 0; i < 256; i++)
    {
        // Apply gamma correction: output = 255 * (input/255)^(1/gamma)
        p[i] = cv::saturate_cast<uchar>(pow(i / 255.0, 1.0 / gamma) * 255.0);
    }

    // Apply lookup table
    cv::LUT(img, lookup_table, result);

    return result;
}

int main(int argc, char const *argv[])
{
    cv::Mat img = cv::imread("../images/input.jpg");
    if (img.empty())
    {
        std::cerr << "Could not load image!\n";
        return -1;
    }

    // Demonstrate different gamma values
    std::vector<double> gammas = {0.5, 1.0, 2.0, 3.0};
    std::vector<std::string> names = {"Gamma 0.5 (Brighten)", "Gamma 1.0 (Original)",
                                      "Gamma 2.0 (Darken)", "Gamma 3.0 (Very Dark)"};

    for (size_t i = 0; i < gammas.size(); i++)
    {
        cv::Mat corrected = gammaCorrectionLUT(img, gammas[i]);
        cv::namedWindow(names[i], cv::WINDOW_GUI_EXPANDED);
        cv::imshow(names[i], corrected);
    }

    cv::waitKey();

    return 0;
}