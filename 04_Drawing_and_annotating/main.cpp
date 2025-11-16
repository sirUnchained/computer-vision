#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

#define CANVAS_WIDTH 512
#define CANVAS_HEIGHT 512

int main(int argc, char const *argv[])
{
    /*
     * Create a black canvas and demonstrate basic drawing operations
     */

    // Create a black image with 3 channels (BGR color space)
    cv::Mat img = cv::Mat::zeros(CANVAS_HEIGHT, CANVAS_WIDTH, CV_8UC3);

    std::cout << "Created canvas: " << CANVAS_WIDTH << "x" << CANVAS_HEIGHT
              << " | Channels: " << img.channels() << std::endl;

    cv::namedWindow("Blank Canvas (Black Image)", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Blank Canvas (Black Image)", img);
    std::cout << "Blank black canvas created. Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Draw a blue diagonal line across the canvas
     * OpenCV uses BGR color format: cv::Scalar(Blue, Green, Red)
     */
    cv::line(img,
             cv::Point(0, 0),         // Start point (top-left)
             cv::Point(511, 511),     // End point (bottom-right)
             cv::Scalar(255, 127, 0), // Color: Blue=255, Green=127, Red=0
             5);                      // Line thickness: 5 pixels

    cv::namedWindow("Canvas with Blue Diagonal Line", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Canvas with Blue Diagonal Line", img);
    std::cout << "Added blue diagonal line from (0,0) to (511,511)" << std::endl;
    std::cout << "Color: B=255, G=127, R=0 (Teal blue)" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Draw a red rectangle
     */
    cv::rectangle(img,
                  cv::Point(100, 100),   // Top-left corner
                  cv::Point(300, 250),   // Bottom-right corner
                  cv::Scalar(0, 0, 255), // Color: Pure red (B=0, G=0, R=255)
                  5);                    // Thickness: 5 pixels

    cv::namedWindow("Canvas with Red Rectangle", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Canvas with Red Rectangle", img);
    std::cout << "Added red rectangle from (100,100) to (300,250)" << std::endl;
    std::cout << "Rectangle size: 200x150 pixels" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    /*
     * Additional drawing examples for better understanding
     */

    // Draw a filled green circle
    cv::circle(img,
               cv::Point(400, 100),   // Center point
               50,                    // Radius: 50 pixels
               cv::Scalar(0, 255, 0), // Color: Pure green
               -1);                   // Thickness: -1 means filled

    cv::namedWindow("Added Filled Green Circle", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Added Filled Green Circle", img);
    std::cout << "Added filled green circle at center (400,100)" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    cv::waitKey(0);

    // Draw text on the image
    cv::putText(img,
                "OpenCV Drawing Demo",     // Text to display
                cv::Point(50, 450),        // Bottom-left position
                cv::FONT_HERSHEY_SIMPLEX,  // Font type
                1.0,                       // Font scale
                cv::Scalar(255, 255, 255), // Color: White
                2);                        // Thickness

    cv::namedWindow("Final Canvas with All Drawings", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Final Canvas with All Drawings", img);
    std::cout << "Added text: 'OpenCV Drawing Demo'" << std::endl;
    std::cout << "Press any key to continue to cow image example..." << std::endl;
    cv::waitKey(0);

    cv::destroyAllWindows();

    /*
     * Exercise: Load cow image and draw a rectangle around it
     */
    cv::Mat cow = cv::imread("./images/input.jpg", cv::IMREAD_COLOR);

    // Check if image loaded successfully
    if (cow.empty())
    {
        std::cerr << "Error: Could not load cow image './images/input.jpg'!" << std::endl;
        std::cerr << "Please check if the file exists and path is correct." << std::endl;
        return -1;
    }

    std::cout << "\nCow image loaded successfully!" << std::endl;
    std::cout << "Image size: " << cow.cols << "x" << cow.rows << std::endl;

    // Display original cow image
    cv::namedWindow("Original Cow Image", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Original Cow Image", cow);
    std::cout << "Press any key to add bounding box..." << std::endl;
    cv::waitKey(0);

    /*
     * Draw a rectangle around a region of interest in the cow image
     * Using a custom color (B=43, G=233, R=127) - teal green color
     */
    cv::rectangle(cow,
                  cv::Point(280, 270),      // Top-left corner of ROI
                  cv::Point(530, 400),      // Bottom-right corner of ROI
                  cv::Scalar(43, 233, 127), // Custom teal green color
                  3);                       // Thickness: 3 pixels

    // Add label to the rectangle
    cv::putText(cow,
                "Region of Interest",
                cv::Point(285, 265), // Position above the rectangle
                cv::FONT_HERSHEY_SIMPLEX,
                0.6,                      // Smaller font
                cv::Scalar(43, 233, 127), // Same color as rectangle
                2);

    cv::namedWindow("Cow Image with Bounding Box", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Cow Image with Bounding Box", cow);
    std::cout << "Added bounding box from (280,270) to (530,400)" << std::endl;
    std::cout << "Bounding box size: " << (530 - 280) << "x" << (400 - 270) << " pixels" << std::endl;
    std::cout << "Press any key to exit..." << std::endl;
    cv::waitKey(0);

    /*
     * Optional: Save the annotated image
     */
    bool save_success = cv::imwrite("../images/cow_with_bbox.jpg", cow);
    if (save_success)
    {
        std::cout << "Annotated image saved as 'images/cow_with_bbox.jpg'" << std::endl;
    }

    /*
     * Additional example: Draw multiple shapes on a clean canvas
     */
    cv::Mat demo_canvas = cv::Mat::zeros(400, 600, CV_8UC3);

    // Set canvas to light gray background
    demo_canvas.setTo(cv::Scalar(200, 200, 200));

    // Draw multiple shapes
    cv::rectangle(demo_canvas, cv::Point(50, 50), cv::Point(150, 150), cv::Scalar(0, 0, 255), 2);
    cv::circle(demo_canvas, cv::Point(300, 100), 40, cv::Scalar(255, 0, 0), -1);
    cv::line(demo_canvas, cv::Point(400, 50), cv::Point(550, 150), cv::Scalar(0, 255, 0), 3);
    cv::putText(demo_canvas, "Drawing Demo", cv::Point(200, 350), cv::FONT_HERSHEY_COMPLEX, 1.2, cv::Scalar(0, 0, 0), 2);

    cv::namedWindow("Advanced Drawing Demo", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Advanced Drawing Demo", demo_canvas);
    std::cout << "\nAdvanced drawing demo completed!" << std::endl;
    std::cout << "Press any key to exit program..." << std::endl;
    cv::waitKey(0);

    cv::destroyAllWindows();
    std::cout << "Program finished successfully!" << std::endl;

    return 0;
}