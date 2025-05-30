// Image.cpp

#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <utility>

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
    //size check:
    if (this->height != other.height || this->width != other.width || this->numChannels != other.numChannels) {
        throw std::runtime_error("Size mismatch in Image::operator+");
    }
    
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
    //size check:
    if (this->height != other.height || this->width != other.width || this->numChannels != other.numChannels) {
        throw std::runtime_error("Size mismatch in Image::operator-");
    }
    
    Image ret;
    ret = *this;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < numChannels*width; j++) {
            ret.data[i][j] = (this->data[i][j] - other.data[i][j]) < 0 ? 0 : this->data[i][j] - other.data[i][j];
        }
    }
    return ret;
}

// Multiplying two images
Image Image::operator*(const Image& other) const {
    // YOUR CODE HERE
    Image ret = *this;
    if (this->getHeight() != other.getHeight()) throw std::runtime_error("size mismatch in Image::operator*");
    if (this->numChannels != other.numChannels) throw std::runtime_error("num channel mismatch in Image::operator*");
    
    for (int chans = 0; chans < numChannels; chans++) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                uint32_t sum = 0;
                for (int k = 0; k < width; k++) {
                    sum += this->data[i][k*numChannels + chans] * other.data[k][j*numChannels + chans];
                }
                ret[i][j*numChannels + chans] = (uint8_t)std::min(sum, (uint32_t)255);
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
    std::vector<uint8_t> input(height * width * numChannels);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int c = 0; c < numChannels; ++c) {
                input[(i * width + j) * numChannels + c] = data[i][j * numChannels + c];
            }
        }
    }
    std::vector<uint8_t> output(newHeight * newWidth * numChannels);
    int success = stbir_resize_uint8(input.data(),  width,  height, 0, output.data(), newWidth, newHeight, 0, numChannels);
    if (!success) throw std::runtime_error("stbir_resize_uint8 failed");
    Vector<Vector<uint8_t>> newvec(newHeight);
    for (int i = 0; i < newHeight; ++i) {
        newvec[i] = Vector<uint8_t>(newWidth * numChannels);
        for (int j = 0; j < newWidth; ++j) {
            for (int c = 0; c < numChannels; ++c) {
                newvec[i][j * numChannels + c] = output[(i * newWidth + j) * numChannels + c];
            }
        }
    }
    Matrix newmat(height, width*numChannels);
    newmat.data = newvec;
    Matrix::operator=(newmat);
    width = newWidth;
    height = newHeight;

}

Image Image::transpose() {
    Image res{"", height, width, numChannels};
    for (int c = 0; c < numChannels; c++) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                res[j][numChannels*i+c] = data[i][numChannels*j+c];
            }
        }
    }
    return res;
}

