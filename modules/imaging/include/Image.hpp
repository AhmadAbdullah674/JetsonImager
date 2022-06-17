#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <string>

//Only a move class
//ATM will on care about 8 or more bit depth image data
//TODO: Add support for float types

class Image{
    bool inGPU;
    //Some cuda stuff for loading in gpu
    void *cpuData;
    int channels; //rgb and other stuff
    int bitDepth; //perchannel
    size_t x;
    size_t y;
  public:
    Image();
    Image(const Image&) = delete;
    Image(Image&&) = default;
    ~Image();

    Image& operator=(Image&&) = default;
    
    bool operator==(const Image& rhs){
      if(!inGPU && !rhs.inGPU && x == rhs.x && y == rhs.y
        && channels == rhs.channels && bitDepth == rhs.bitDepth){
          //Not good for floats type images
        char* a = static_cast<char*> (cpuData);
        char* b = static_cast<char*> (rhs.cpuData);
        for(size_t i = 0; i < x * y * channels * bitDepth; ++i){
          if(a[i] != b[i]){
            return false;
          }
        }
        return true;
      }
      else if(inGPU && rhs.inGPU && x == rhs.x && y == rhs.y
        && channels == rhs.channels && bitDepth == rhs.bitDepth){
          //TODO: Have to do this, should I write a cuda kernel for this??
        return true;
      }
      return false;
    }
    bool operator!=(const Image& rhs){
      return !(*this == rhs);
    }

    //No such comparision for Images I think??
    bool operator< (const Image& rhs) = delete;
    bool operator> (const Image& rhs) = delete;
    bool operator<=(const Image& rhs) = delete;
    bool operator>=(const Image& rhs) = delete;
    
    Image& operator=(const Image&) = delete;

    bool getImageFromFile(std::string file);
    bool saveImageToFile(std::string file);
    bool placeInGPU();
};
#endif