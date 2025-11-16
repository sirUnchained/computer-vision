#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

/**
 * Converts color image to grayscale using iterator method
 * @param main_img Reference to the input image (will be modified in-place)
 */
void first_way(cv::Mat &main_img)
{
    // Input validation
    if (main_img.empty())
    {
        std::cerr << "Error: Input image is empty!" << std::endl;
        return;
    }

    if (main_img.channels() != 3)
    {
        std::cerr << "Error: Input image must have 3 channels!" << std::endl;
        return;
    }

    // Get begin and end iterators for efficient pixel traversal
    cv::Mat_<cv::Vec3b>::iterator it_begin = main_img.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator it_end = main_img.end<cv::Vec3b>();

    // Iterate through all pixels using iterator (efficient method)
    while (it_begin != it_end)
    {
        // Calculate grayscale value using weighted method (better than simple average)
        // Using standard luminance formula: 0.299*R + 0.587*G + 0.114*B
        uchar gray_value = cv::saturate_cast<uchar>(
            (*it_begin)[2] * 0.299 + // Red channel (OpenCV uses BGR format)
            (*it_begin)[1] * 0.587 + // Green channel
            (*it_begin)[0] * 0.114   // Blue channel
        );

        // Set all channels to the calculated grayscale value
        (*it_begin)[0] = gray_value; // Blue channel
        (*it_begin)[1] = gray_value; // Green channel
        (*it_begin)[2] = gray_value; // Red channel

        // Move to next pixel
        it_begin++;
    }
}

/**
 * Converts color image to grayscale using direct pixel access method
 * @param main_img Reference to the input image (will be modified in-place)
 */
void second_way(cv::Mat &main_img)
{
    // Input validation
    if (main_img.empty())
    {
        std::cerr << "Error: Input image is empty!" << std::endl;
        return;
    }

    if (main_img.channels() != 3)
    {
        std::cerr << "Error: Input image must have 3 channels!" << std::endl;
        return;
    }

    // Loop through all pixels using direct coordinate access
    for (int y = 0; y < main_img.rows; y++)
    {
        for (int x = 0; x < main_img.cols; x++)
        {
            // Get pixel at position (y, x) - NOTE: OpenCV uses (row, column) format
            cv::Vec3b &pixel = main_img.at<cv::Vec3b>(y, x);

            // Calculate grayscale using weighted method
            uchar gray_value = cv::saturate_cast<uchar>(
                pixel[2] * 0.299 + // Red
                pixel[1] * 0.587 + // Green
                pixel[0] * 0.114   // Blue
            );

            // Set all channels to grayscale value
            pixel[0] = gray_value; // Blue
            pixel[1] = gray_value; // Green
            pixel[2] = gray_value; // Red
        }
    }
}

/**
 * Alternative efficient method using OpenCV operations
 */
void third_way_efficient(cv::Mat &main_img)
{
    if (main_img.empty() || main_img.channels() != 3)
    {
        std::cerr << "Error: Invalid input image!" << std::endl;
        return;
    }

    // Most efficient way: Use OpenCV's built-in cvtColor
    cv::Mat gray;
    cv::cvtColor(main_img, gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(gray, main_img, cv::COLOR_GRAY2BGR); // Convert back to 3-channel
}

int main(int argc, char const *argv[])
{
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;

    // Load input image
    cv::Mat img = cv::imread("../images/input.jpg", cv::IMREAD_COLOR);

    // Check if image loaded successfully
    if (img.empty())
    {
        std::cerr << "Error: Could not load input image!" << std::endl;
        return -1;
    }

    // Display original image
    cv::namedWindow("Original Image", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Original Image", img);
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    // Convert to grayscale using OpenCV function
    cv::Mat gray_img;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    cv::namedWindow("OpenCV Grayscale", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("OpenCV Grayscale", gray_img);
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    // Display image information
    std::cout << "Image size: " << img.size()
              << " | Channels: " << img.channels()
              << " | Type: " << img.type() << std::endl;

    cv::destroyAllWindows();

    /*
     * Exercise 1: Manual grayscale conversion
     */
    cv::Mat main = cv::imread("../images/input.jpg", cv::IMREAD_COLOR);
    if (main.empty())
    {
        std::cerr << "Error: Could not load image for exercise 1!" << std::endl;
        return -1;
    }

    if (main.channels() == 1)
    {
        std::cout << "Image is already grayscale." << std::endl;
    }
    else
    {
        // Create a copy to preserve original
        cv::Mat manual_gray = main.clone();

        // Use either method (comment/uncomment to test)
        first_way(manual_gray);
        // second_way(manual_gray);
        // third_way_efficient(manual_gray);

        cv::namedWindow("Manual Grayscale Conversion", cv::WINDOW_GUI_EXPANDED);
        cv::imshow("Manual Grayscale Conversion", manual_gray);
        std::cout << "Press any key to continue..." << std::endl;
        cv::waitKey(0);
        cv::destroyAllWindows();
    }

    /*
     * Exercise 2: Display checkerboard as numbers
     */
    cv::Mat cb_image = cv::imread("../images/checkerboard_18x18.png", cv::IMREAD_GRAYSCALE);
    if (cb_image.empty())
    {
        std::cerr << "Error: Could not load checkerboard image!" << std::endl;
        return -1;
    }

    if (cb_image.channels() != 1)
    {
        std::cout << "Warning: Checkerboard image is not grayscale. Converting..." << std::endl;
        cv::cvtColor(cb_image, cb_image, cv::COLOR_BGR2GRAY);
    }

    std::cout << "\nCheckerboard values (" << cb_image.rows << "x" << cb_image.cols << "):" << std::endl;
    std::cout << "==========================================" << std::endl;

    // Display pixel values in a formatted way
    for (int y = 0; y < cb_image.rows; y++)
    {
        for (int x = 0; x < cb_image.cols; x++)
        {
            // Format output for better readability
            std::cout << std::setw(3) << static_cast<int>(cb_image.at<uchar>(y, x)) << " ";
        }
        std::cout << std::endl;
    }

    // Optional: Also display the checkerboard image
    cv::namedWindow("Checkerboard", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Checkerboard", cb_image);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}