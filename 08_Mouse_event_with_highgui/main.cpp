#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

/**
 * Creates an interactive window where users can draw circles by clicking
 * uses single-channel image for simple dot drawing
 */
void create_circle_dots()
{
    // Create black canvas (single channel grayscale)
    static cv::Mat img = cv::Mat::zeros(cv::Size(512, 512), CV_8U);
    std::string img_name = "Click to draw circles! (ESC to exit)";

    // mouse callback function for drawing circles
    auto draw_circle = [](int event, int x, int y, int flags, void *userdata)
    {
        // draw circle on left mouse click
        if (event == cv::EVENT_LBUTTONDOWN)
        {
            // draw filled circle at click position
            // Note: In grayscale, only first scalar value is used (134 = light gray)
            cv::circle(img, cv::Point(x, y), 10, cv::Scalar(134), -1);
        }
    };

    // create window and set mouse callback
    cv::namedWindow(img_name, cv::WINDOW_GUI_EXPANDED);
    cv::setMouseCallback(img_name, draw_circle);

    // Main loop - display image and check for ESC key
    while (true)
    {
        cv::imshow(img_name, img);
        if ((cv::waitKey(100) & 0xFF) == 27) // ESC key
        {
            break;
        }
    }

    cv::destroyAllWindows();
}

/**
 * Creates an interactive painting application with color selection
 * uses continuous line drawing with color changing functionality
 */
void paint()
{
    std::string img_name = "Painting App - B:Blue G:Green R:Red C:Clear ESC:Exit";

    // static variables maintain state between function calls
    static int prev_x = 0;                                            // previous X coordinate for smooth drawing
    static int prev_y = 0;                                            // previous Y coordinate for smooth drawing
    static cv::Mat img = cv::Mat::zeros(cv::Size(512, 512), CV_8UC3); // 3-channel color canvas
    static cv::Scalar pen_color = cv::Scalar(255, 0, 0);              // Start with blue pen (BGR format)
    static bool drawing = false;                                      // drawing state flag

    // mouse callback for brush functionality
    auto brush = [](int event, int x, int y, int flags, void *userdata)
    {
        if (event == cv::EVENT_LBUTTONDOWN)
        {
            // Start drawing and store initial position
            drawing = true;
            prev_x = x;
            prev_y = y;

            // draw initial dot at click position
            cv::circle(img, cv::Point(x, y), 5, pen_color, -1);
        }
        else if (event == cv::EVENT_LBUTTONUP)
        {
            // Stop drawing
            drawing = false;
        }
        else if (event == cv::EVENT_MOUSEMOVE)
        {
            if (drawing == true)
            {
                // draw line from previous position to current position
                cv::line(img, cv::Point(prev_x, prev_y), cv::Point(x, y), pen_color, 10, cv::LINE_AA);

                // Update previous position for next movement
                prev_x = x;
                prev_y = y;
            }
        }
    };

    // Setup window and mouse callback
    cv::namedWindow(img_name, cv::WINDOW_GUI_EXPANDED);
    cv::setMouseCallback(img_name, brush);

    // Main application loop
    while (true)
    {
        cv::imshow(img_name, img);
        int key = cv::waitKey(100) & 0xFF; // Non-blocking wait with 100ms delay

        if (key == 27) // ESC key - exit
        {
            break;
        }
        else if (key == 'b' || key == 'B') // Blue pen
        {
            pen_color = cv::Scalar(255, 0, 0); // BGR: Blue=255, Green=0, Red=0
            std::cout << "Pen color: Blue\n";
        }
        else if (key == 'g' || key == 'G') // Green pen
        {
            pen_color = cv::Scalar(0, 255, 0); // BGR: Blue=0, Green=255, Red=0
            std::cout << "Pen color: Green\n";
        }
        else if (key == 'r' || key == 'R') // Red pen
        {
            pen_color = cv::Scalar(0, 0, 255); // BGR: Blue=0, Green=0, Red=255
            std::cout << "Pen color: Red\n";
        }
        else if (key == 'c' || key == 'C') // Clear canvas
        {
            img = cv::Mat::zeros(cv::Size(512, 512), CV_8UC3);
            std::cout << "Canvas cleared\n";
        }
        else if (key == 'w' || key == 'W') // White pen (new feature)
        {
            pen_color = cv::Scalar(255, 255, 255);
            std::cout << "Pen color: White\n";
        }
        else if (key == 'k' || key == 'K') // Black pen (new feature)
        {
            pen_color = cv::Scalar(0, 0, 0);
            std::cout << "Pen color: Black\n";
        }
        else if (key == 's' || key == 'S') // Save drawing (new feature)
        {
            cv::imwrite("my_drawing.png", img);
            std::cout << "Drawing saved as 'my_drawing.png'\n";
        }
    }
    cv::destroyAllWindows();
}

// Enum for better code readability and maintainability
enum class AppMode
{
    CIRCLE_DOTS = 0,
    PAINTING = 1,
    EXIT = 2
};

int main(int argc, char const *argv[])
{
    // Display menu to user
    std::cout << "=== OpenCV Drawing Applications ===" << std::endl;
    std::cout << "0: Circle Dots - Click to draw circles" << std::endl;
    std::cout << "1: Painting - Draw with colored brushes" << std::endl;
    std::cout << "2: Exit" << std::endl;
    std::cout << "What do you want me to do? (0-2): ";

    int choice = 0;
    std::cin >> choice;

    // Convert input to enum for better type safety
    AppMode mode = static_cast<AppMode>(choice);

    switch (mode)
    {
    case AppMode::CIRCLE_DOTS:
        std::cout << "Starting Circle Dots application..." << std::endl;
        std::cout << "Instructions: Click anywhere to draw circles, ESC to exit" << std::endl;
        create_circle_dots();
        break;

    case AppMode::PAINTING:
        std::cout << "Starting Painting application..." << std::endl;
        std::cout << "Instructions:" << std::endl;
        std::cout << "  - Click and drag to draw" << std::endl;
        std::cout << "  - B: Blue, G: Green, R: Red, W: White, K: Black" << std::endl;
        std::cout << "  - C: Clear canvas, S: Save drawing, ESC: Exit" << std::endl;
        paint();
        break;

    case AppMode::EXIT:
        std::cout << "Exiting application." << std::endl;
        break;

    default:
        std::cout << "Invalid choice! Please run again and select 0, 1, or 2." << std::endl;
        break;
    }

    std::cout << "Application finished." << std::endl;
    return 0;
}