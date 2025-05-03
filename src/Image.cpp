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

    if (imageData == nullptr) throw std::runtime_error("failed to load image data");
    
    *this = Image(filePath, channels, width, height);

    int index = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < channels; k++) {
                data[i][j*channels + k] = imageData[index++];
            }
        }
    }

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
    : Matrix(height, numChannels*width), filePath(filePath), numChannels(numChannels), width(width), height(height) {}

// Copy constructor
// YOUR CODE HERE
Image::Image(const Image& other) {
    if (this == &other) return;
    Matrix::operator=(other);
    filePath = other.filePath;
    numChannels = other.numChannels;
    width = other.width;
    height = other.height;

}

// Assignment operator
Image& Image::operator=(const Image& other) {
    // YOUR CODE HERE
    if (this == &other) return *this;
    
    filePath = other.filePath;
    numChannels = other.numChannels;
    width = other.width;
    height = other.height;
    Matrix::operator=(other);

    return *this;
}

// Destructor
Image::~Image() {
    //YOUR CODE HERE
    // no heap memory was allocated that we need to manage
    // std::vector will handle it for us
}

// Scaling an image
Image Image::operator*(double scalar) const {
    // YOUR CODE HERE
    Image other;
    other = *this;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < numChannels*width; j++) {
            other.data[i][j] = (uint8_t)((double)data[i][j] * scalar) > 255 ? 255 : (uint8_t)((double)data[i][j] * scalar);
        }
    }
    return other;
}

// Adding two images
Image Image::operator+(const Image& other) const {
   // YOUR CODE HERE
   Image ret;
   ret = *this;
   for (int i = 0; i < height; i++) {
       for (int j = 0; j < numChannels*width; j++) {
        ret.data[i][j] = ((this->data[i][j] + other.data[i][j]) > 255) ? 255 : this->data[i][j] + other.data[i][j];
       }
   }
   return ret;
}

// Subtracting two images
Image Image::operator-(const Image& other) const {
    // YOUR CODE HERE
    Image ret;
    ret = *this;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ret.data[i][j] = (this->data[i][j] - other.data[i][j]) < 0 ? 0 : this->data[i][j] - other.data[i][j];
        }
    }
    return ret;
}

// Multiplying two images
Image Image::operator*(const Image& other) const {
    // YOUR CODE HERE
    Image ret = *this;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ret.data[i][j] = 0;
            for (int k = 0; k < width; k++) {
                ret.data[i][j] += (this->data[i][j] + other.data[i][j]) > 255 ? 255 : this->data[i][j] + other.data[i][j];
            }
        }
    }

    return ret;
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

