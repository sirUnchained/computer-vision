#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

#define SIZE 300

int main(int argc, char const *argv[])
{
    /*
     * Create black and white squares for bitwise operations demonstration
     */
    // Create a black square (all zeros)
    cv::Mat black_square = cv::Mat::zeros(SIZE, SIZE, CV_8UC1);

    // Create a white square (all ones, but need to scale to 255 for display)
    cv::Mat white_square = cv::Mat::ones(SIZE, SIZE, CV_8UC1) * 255;

    std::cout << "created images:" << std::endl;
    std::cout << "black square: " << black_square.rows << "x" << black_square.cols
              << " | type: " << black_square.type() << std::endl;
    std::cout << "white square: " << white_square.rows << "x" << white_square.cols
              << " | type: " << white_square.type() << std::endl;

    // Display the original images
    cv::namedWindow("black Square (All Zeros)", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("black Square (All Zeros)", black_square);
    cv::namedWindow("black Square (All Zeros)", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("White square (All 255)", white_square);
    std::cout << "press any key to continue to bitwise operations..." << std::endl;
    cv::waitKey(0);

    /*
     * Bitwise AND Operation
     * Truth table: 0 & 0 = 0, 0 & 1 = 0, 1 & 0 = 0, 1 & 1 = 1
     * Since black=0 and white=255, result will be all zeros (black)
     */
    cv::Mat bit_and;
    cv::bitwise_and(black_square, white_square, bit_and);
    cv::namedWindow("bitwise AND (black & white)", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("bitwise AND (black & white)", bit_and);
    std::cout << "AND Operation: black(0) AND white(255) = black(0)" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Bitwise OR Operation
     * Truth table: 0 | 0 = 0, 0 | 1 = 1, 1 | 0 = 1, 1 | 1 = 1
     * Since black=0 and white=255, result will be all 255 (white)
     */
    cv::Mat bit_or;
    cv::bitwise_or(black_square, white_square, bit_or);
    cv::namedWindow("bitwise OR (black | White)", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("bitwise OR (black | White)", bit_or);
    std::cout << "OR Operation: black(0) OR white(255) = White(255)" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Additional bitwise operations for better understanding
     */

    // bitwise NOT (inversion)
    cv::Mat bit_not_black, bit_not_white;
    cv::bitwise_not(black_square, bit_not_black); // Black becomes white
    cv::bitwise_not(white_square, bit_not_white); // White becomes black

    cv::namedWindow("NOT Black (Inversion)", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("NOT Black (Inversion)", bit_not_black);
    cv::namedWindow("NOT White (Inversion)", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("NOT White (Inversion)", bit_not_white);
    std::cout << "NOT Operation demonstrated." << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Bitwise XOR Operation
     * Truth table: 0 ^ 0 = 0, 0 ^ 1 = 1, 1 ^ 0 = 1, 1 ^ 1 = 0
     * Useful for finding differences between images
     */
    cv::Mat bit_xor;
    cv::bitwise_xor(black_square, white_square, bit_xor);
    cv::namedWindow("Bitwise XOR (Black ^ White)", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Bitwise XOR (Black ^ White)", bit_xor);
    std::cout << "XOR Operation: Black(0) XOR White(255) = White(255)" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Demonstrate with gray image for more interesting results
     */
    cv::Mat gray_square = cv::Mat(SIZE, SIZE, CV_8UC1, cv::Scalar(128)); // Middle gray

    cv::Mat gray_and_white;
    cv::bitwise_and(gray_square, white_square, gray_and_white);
    cv::namedWindow("Gray Square (128)", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Gray Square (128)", gray_square);
    cv::namedWindow("AND: Gray & White", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("AND: Gray & White", gray_and_white);
    std::cout << "AND with gray: 128 & 255 = 128" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Practical example: Creating a mask and applying operations
     */
    cv::Mat circle_mask = cv::Mat::zeros(SIZE, SIZE, CV_8UC1);
    cv::circle(circle_mask, cv::Point(SIZE / 2, SIZE / 2), 100, cv::Scalar(255), -1);

    cv::Mat masked_result;
    cv::bitwise_and(white_square, white_square, masked_result, circle_mask);

    cv::namedWindow("Circle Mask", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Circle Mask", circle_mask);
    cv::namedWindow("Masked White Square", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Masked White Square", masked_result);
    std::cout << "Practical example: Using AND with mask to extract region." << std::endl;
    std::cout << "Press any key to exit..." << std::endl;
    cv::waitKey(0);

    /*
     * Print summary of operations
     */
    std::cout << "\n=== BITWISE OPERATIONS SUMMARY ===" << std::endl;
    std::cout << "AND: 0 & 255 = 0, 255 & 255 = 255, 0 & 0 = 0" << std::endl;
    std::cout << "OR:  0 | 255 = 255, 255 | 255 = 255, 0 | 0 = 0" << std::endl;
    std::cout << "XOR: 0 ^ 255 = 255, 255 ^ 255 = 0, 0 ^ 0 = 0" << std::endl;
    std::cout << "NOT: ~0 = 255, ~255 = 0" << std::endl;
    std::cout << "===================================" << std::endl;

    cv::destroyAllWindows();
    return 0;
}