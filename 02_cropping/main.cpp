#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

void validate_cropping(cv::Mat &pic, cv::Rect &crop_rect)
{
    if (crop_rect.x < 0 || crop_rect.y < 0 ||
        crop_rect.x + crop_rect.width > pic.cols ||
        crop_rect.y + crop_rect.height > pic.rows)
    {
        std::cerr << "Error: Cropping rectangle is out of image bounds!" << std::endl;
        std::cerr << "Image size: " << pic.cols << "x" << pic.rows << std::endl;
        std::cerr << "Crop region: (" << crop_rect.x << ", " << crop_rect.y
                  << ") " << crop_rect.width << "x" << crop_rect.height << std::endl;
        exit(-1);
    }
}

int main(int argc, char const *argv[])
{
    /*
     * Load and display the original image
     */
    cv::Mat mml = cv::imread("../images/mml-gol.jpg", cv::IMREAD_COLOR);

    // check if image loaded successfully
    if (mml.empty())
    {
        std::cerr << "Error: Could not load image './images/mml-gol.jpg'!" << std::endl;
        std::cerr << "Please check:" << std::endl;
        std::cerr << "1. File exists at the specified path" << std::endl;
        std::cerr << "2. File is not corrupted" << std::endl;
        std::cerr << "3. Correct file permissions" << std::endl;
        return -1;
    }

    // display original image with window name
    cv::namedWindow("Original MML Image", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Original MML Image", mml);
    std::cout << "Original image loaded successfully!" << std::endl;
    std::cout << "Image size: " << mml.cols << "x" << mml.rows
              << " | Channels: " << mml.channels() << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * define cropping region and extract ROI (Region of Interest)
     */
    // create rectangle for cropping: (x, y, width, height)
    // starting from (50,50) and taking 120x120 pixel region
    cv::Rect crop_mml_rect(50, 50, 120, 120);

    // Validate cropping coordinates to avoid out-of-bounds access
    validate_cropping(mml, crop_mml_rect);

    // extract region of interest - this creates a VIEW (not a copy) of the original
    cv::Mat crop_mml = mml(crop_mml_rect);

    // Display cropped image
    cv::namedWindow("Cropped MML Region", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Cropped MML Region", crop_mml);
    std::cout << "Cropped image size: " << crop_mml.cols << "x" << crop_mml.rows << std::endl;
    std::cout << "Press any key to exit..." << std::endl;
    cv::waitKey(0);

    /*
     * Save the cropped image
     */
    bool save_success = cv::imwrite("../images/mml-cropped.jpg", crop_mml);
    if (save_success)
    {
        std::cout << "Cropped image saved as 'images/mml-cropped.jpg'" << std::endl;
    }
    else
    {
        std::cerr << "Warning: Could not save cropped image!" << std::endl;
    }

    /*
     * Optional: Demonstrate creating an actual copy (not a view)
     */
    cv::Mat crop_mml_copy = mml(crop_mml_rect).clone();
    std::cout << "Created a separate copy of the cropped region." << std::endl;

    /*
     * Cleanup and exit
     */
    cv::destroyAllWindows();
    std::cout << "Program completed successfully!" << std::endl;

    return 0;
}