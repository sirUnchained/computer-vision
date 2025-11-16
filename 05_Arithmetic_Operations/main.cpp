#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char const *argv[])
{
    /*
     * Load and display the original cow image
     */
    cv::Mat cow = cv::imread("../images/input.jpg", cv::IMREAD_COLOR);
    if (cow.empty())
    {
        std::cerr << "Error: Could not load image 'images/input.jpg'!" << std::endl;
        std::cerr << "Please check:" << std::endl;
        std::cerr << "1. File exists in the 'images' directory" << std::endl;
        std::cerr << "2. Correct file name and extension" << std::endl;
        return -1;
    }

    std::cout << "Cow image loaded successfully!" << std::endl;
    std::cout << "Image size: " << cow.cols << "x" << cow.rows << std::endl;
    std::cout << "Image type: " << cow.type() << " (CV_8UC3 = 16)" << std::endl;
    std::cout << "Image channels: " << cow.channels() << std::endl;

    cv::namedWindow("Original Cow Image", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Original Cow Image", cow);
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Create a matrix with same size as cow image and set all values to 100
     * NOTE: cv::Mat::ones() creates matrix with values of 1, not 255
     */
    cv::Mat matrix = cv::Mat::ones(cow.size(), cow.type()); // Creates 3-channel matrix with values (1,1,1)
    matrix = matrix * 100;                                  // Scale to (100,100,100) - creates a dark gray color

    std::cout << "\nCreated constant matrix with value 100 in all channels" << std::endl;
    std::cout << "Matrix size: " << matrix.size() << " | Type: " << matrix.type() << std::endl;

    cv::namedWindow("Constant Matrix (Value 100)", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Constant Matrix (Value 100)", matrix);
    std::cout << "This appears as dark gray because 100/255 ≈ 0.39 intensity" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Add images together - Brightening effect
     * Pixel values are saturated: min(255, cow_pixel + 100)
     */
    cv::Mat out_sum;
    cv::add(cow, matrix, out_sum);

    cv::namedWindow("Addition: Cow + Matrix", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Addition: Cow + Matrix", out_sum);
    std::cout << "\nAddition Operation (Brightening):" << std::endl;
    std::cout << "Each pixel: cow_pixel + 100" << std::endl;
    std::cout << "Result: Image becomes brighter by adding 100 to all channels" << std::endl;
    std::cout << "Values are saturated at 255 to prevent overflow" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Subtract matrix from image - Darkening effect
     * Pixel values are saturated: max(0, cow_pixel - 100)
     */
    cv::Mat out_sub;
    cv::subtract(cow, matrix, out_sub);

    cv::namedWindow("Subtraction: Cow - Matrix", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Subtraction: Cow - Matrix", out_sub);
    std::cout << "\nSubtraction Operation (Darkening):" << std::endl;
    std::cout << "Each pixel: cow_pixel - 100" << std::endl;
    std::cout << "Result: Image becomes darker by subtracting 100 from all channels" << std::endl;
    std::cout << "Values are saturated at 0 to prevent underflow" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Additional operations for better understanding
     */

    // Multiplication operation - Contrast enhancement
    cv::Mat out_mul;
    cv::Mat matrix_scale = cv::Mat::ones(cow.size(), cow.type()) * 1.5; // Scale factor
    cv::multiply(cow, matrix_scale, out_mul);

    cv::namedWindow("Multiplication: Cow × 1.5", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Multiplication: Cow × 1.5", out_mul);
    std::cout << "\nMultiplication Operation (Contrast):" << std::endl;
    std::cout << "Each pixel: cow_pixel × 1.5" << std::endl;
    std::cout << "Result: Increases contrast, bright areas become brighter" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    // Division operation - Contrast reduction
    cv::Mat out_div;
    cv::Mat matrix_div = cv::Mat::ones(cow.size(), cow.type()) * 2.0; // Division factor
    cv::divide(cow, matrix_div, out_div);

    cv::namedWindow("Division: Cow ÷ 2.0", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Division: Cow ÷ 2.0", out_div);
    std::cout << "\nDivision Operation (Reduce Contrast):" << std::endl;
    std::cout << "Each pixel: cow_pixel ÷ 2.0" << std::endl;
    std::cout << "Result: Decreases contrast, image becomes darker and flatter" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Demonstrate weighted addition (alpha blending)
     */
    cv::Mat blended;
    double alpha = 0.7; // Weight for first image
    double beta = 0.3;  // Weight for second image
    double gamma = 0.0; // Scalar added to each sum

    cv::addWeighted(cow, alpha, matrix, beta, gamma, blended);

    cv::namedWindow("Weighted Addition: 0.7×Cow + 0.3×Matrix", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Weighted Addition: 0.7×Cow + 0.3×Matrix", blended);
    std::cout << "\nWeighted Addition (Alpha Blending):" << std::endl;
    std::cout << "Formula: dst = alpha×cow + beta×matrix + gamma" << std::endl;
    std::cout << "Used: 0.7×Cow + 0.3×Matrix + 0" << std::endl;
    std::cout << "Result: Creates a blend between original and constant matrix" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Demonstrate saturation behavior
     */
    cv::Mat bright_matrix = cv::Mat::ones(cow.size(), cow.type()) * 200;
    cv::Mat overexposed;
    cv::add(cow, bright_matrix, overexposed);

    cv::namedWindow("Saturation Example: Cow + 200", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Saturation Example: Cow + 200", overexposed);
    std::cout << "\nSaturation Behavior Demonstration:" << std::endl;
    std::cout << "Adding 200 to all pixels causes saturation at 255" << std::endl;
    std::cout << "Many pixels become pure white (255,255,255)" << std::endl;
    std::cout << "This prevents overflow and maintains valid image data" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Show pixel value examples for better understanding
     */
    std::cout << "\n=== PIXEL VALUE EXAMPLES ===" << std::endl;
    std::cout << "Original pixel (sample): " << static_cast<int>(cow.at<cv::Vec3b>(100, 100)[0])
              << ", " << static_cast<int>(cow.at<cv::Vec3b>(100, 100)[1])
              << ", " << static_cast<int>(cow.at<cv::Vec3b>(100, 100)[2]) << std::endl;
    std::cout << "After addition: " << static_cast<int>(out_sum.at<cv::Vec3b>(100, 100)[0])
              << ", " << static_cast<int>(out_sum.at<cv::Vec3b>(100, 100)[1])
              << ", " << static_cast<int>(out_sum.at<cv::Vec3b>(100, 100)[2]) << std::endl;
    std::cout << "After subtraction: " << static_cast<int>(out_sub.at<cv::Vec3b>(100, 100)[0])
              << ", " << static_cast<int>(out_sub.at<cv::Vec3b>(100, 100)[1])
              << ", " << static_cast<int>(out_sub.at<cv::Vec3b>(100, 100)[2]) << std::endl;
    std::cout << "=============================" << std::endl;

    /*
     * Save results for comparison
     */
    cv::imwrite("../images/cow_original.jpg", cow);
    cv::imwrite("../images/cow_brightened.jpg", out_sum);
    cv::imwrite("../images/cow_darkened.jpg", out_sub);
    cv::imwrite("../images/cow_contrast_high.jpg", out_mul);
    cv::imwrite("../images/cow_contrast_low.jpg", out_div);
    cv::imwrite("../images/cow_blended.jpg", blended);

    std::cout << "\nAll results saved in 'images' directory:" << std::endl;
    std::cout << "- cow_original.jpg" << std::endl;
    std::cout << "- cow_brightened.jpg" << std::endl;
    std::cout << "- cow_darkened.jpg" << std::endl;
    std::cout << "- cow_contrast_high.jpg" << std::endl;
    std::cout << "- cow_contrast_low.jpg" << std::endl;
    std::cout << "- cow_blended.jpg" << std::endl;

    std::cout << "\nProgram completed successfully!" << std::endl;
    cv::destroyAllWindows();
    return 0;
}