#ifndef CudaHelper_HPP
#define CudaHelper_HPP

#include <iostream>
#include <mutex>
#include <thread>
//include some cuda stuff

class CudaHelper{
  private:
    CudaHelper(){
      //some cuda init stuff
      refs = 0;
    }
    static CudaHelper* cudaHelper_;
    static std::mutex mutex_;
    int refs;
    ~CudaHelper(){}
  
  public:   
    CudaHelper(CudaHelper& other) = delete;
    CudaHelper& operator=(const CudaHelper &) = delete;
    CudaHelper(CudaHelper&& other) noexcept = delete;
    CudaHelper& operator=(CudaHelper&& other) noexcept = delete;
    
    static CudaHelper* getCudaHelper(){
      std::lock_guard<std::mutex> guard(mutex_);
      if(cudaHelper_ == nullptr){
        cudaHelper_ = new CudaHelper;
      }
      cudaHelper_->refs++;
      return cudaHelper_;
    }
    static void deleteCudaHelper(){
      std::lock_guard<std::mutex> guard(mutex_);
      if(!cudaHelper_->refs){
        return;
      }
      cudaHelper_->refs--;
    }
};

CudaHelper* CudaHelper::cudaHelper_= nullptr;
std::mutex CudaHelper::mutex_;

#endif