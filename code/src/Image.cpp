// Image.cpp

#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

// Default constructor
Image::Image() : Matrix(), filePath(""), numChannels(0), width(0), height(0) {}

Image::Image(const std::string& filePath) {
    // Load the image using stb_image
    int width, height, channels;
    uint8_t* imageData = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

    // Initialize the Matrix base class with the image data
    // (You need to implement a constructor or a function in the Matrix class
    //  that allows you to initialize it with image data)
    // ...

    // Set the Image properties
    this->filePath = filePath;
    this->numChannels = channels;
    this->width = width;
    this->height = height;

    // Free the loaded image data
    stbi_image_free(imageData);
}

// Constructor with file path, channels, width, and height
Image::Image(const std::string& filePath, int numChannels, int width, int height)
    : Matrix(height, width), filePath(filePath), numChannels(numChannels), width(width), height(height) {}

// Copy constructor
// YOUR CODE HERE

// Assignment operator
Image& Image::operator=(const Image& other) {
    // YOUR CODE HERE
    return *this;
}

// Destructor
Image::~Image() {
    //YOUR CODE HERE
}

// Scaling an image
Image Image::operator*(double scalar) const {
    // YOUR CODE HERE
}

// Adding two images
Image Image::operator+(const Image& other) const {
   // YOUR CODE HERE
}

// Subtracting two images
Image Image::operator-(const Image& other) const {
    // YOUR CODE HERE
}

// Multiplying two images
Image Image::operator*(const Image& other) const {
    // YOUR CODE HERE
}


int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

void Image::save(const std::string& filePath) const {
    // Convert the Matrix data into a 1D array suitable for saving as an image
    std::vector<uint8_t> imageData;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < numChannels; ++k) {
                imageData.push_back(data[i][j * numChannels + k]);
            }
        }
    }
    
    // Save the image data to the specified file using stb_image_write
    stbi_write_png(filePath.c_str(), width, height, numChannels, imageData.data(), width * numChannels);
}

void Image::resize(int newWidth, int newHeight) {
    // YOUR CODE HERE
}

