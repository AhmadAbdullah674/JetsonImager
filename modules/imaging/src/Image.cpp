#include "Image.hpp"
#include <iostream>

Image::Image():inGPU(false), cpuData(nullptr),
    channels(0), bitDepth(0), x(0), y(0){
}

Image::~Image(){
  free(cpuData);
  //if on gpu call stuff for gpu
}

bool Image::getImageFromFile(std::string file){
  return true;
}

bool Image::saveImageToFile(std::string file){
  return true;
}

bool Image::placeInGPU(){
  return true;
}