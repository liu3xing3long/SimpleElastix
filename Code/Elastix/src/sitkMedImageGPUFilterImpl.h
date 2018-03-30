#ifndef __sitkmedimagegpufilterimpl_h_
#define __sitkmedimagegpufilterimpl_h_

// SimpleITK
#include "sitkMedImageGPUFilter.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkDualMemberFunctionFactory.h"

// Elastix
// #include "elxElastixFilter.h"
// #include "elxParameterObject.h"

namespace itk { 
  namespace simple {

struct MedImageGPUFilter::MedImageGPUFilterImpl
{
public:
  MedImageGPUFilterImpl( void );
  ~MedImageGPUFilterImpl( void );

  typedef MedImageGPUFilterImpl Self;                                

  const std::string GetName( void );

  void SetLogFileName( const std::string logFileName );
  std::string GetLogFileName( void );
  void RemoveLogFileName( void );

  void SetLogToFile( const bool logToFile );
  bool GetLogToFile( void );
  void LogToFileOn( void );
  void LogToFileOff( void );

  void SetLogToConsole( bool );
  bool GetLogToConsole( void );
  void LogToConsoleOn();
  void LogToConsoleOff();

  bool IsGPUEnabled( void );

public:
  Image Resample( const Image& inputImage, const std::vector<float> outputSpacing );
  Image Threshold( const Image& inputImage, double lower = 0.0, double upper = 255.0, double outsideValue = 0.0);
  
  Image BinaryDilate(const Image& inputImage, unsigned int dilateRadius=1);
  Image BinaryErode(const Image& inputImage, unsigned int erodeRadius = 1);
  Image BinaryOpen(const Image& inputImage, unsigned int Radius = 1);
  Image BinaryClose(const Image& inputImage, unsigned int Radius = 1);

  Image BinaryThreshold(const Image& image1, double lower = 0.0, double upper = 1.0, uint8_t insideValue = 1u, uint8_t outsideValue = 0u);
  Image Median(const Image& inputImage, const std::vector<unsigned int>& radius = std::vector< unsigned int >(3, 1));
  Image Mean(const Image& inputImage, const std::vector<unsigned int>& radius = std::vector< unsigned int >(3, 1));
  Image GradientAnisotropicDiffusion(const Image & image1, double timeStep = 0.125, double conductanceParameter = 3, unsigned int conductanceScalingUpdateInterval = 1u, uint32_t numberOfIterations = 5u);
  Image RecursiveGaussian (const Image &inputImage, double sigma = 1.0, bool normalizeAcrossScale = false, unsigned int orderType = 0, unsigned int direction = 0u);
  Image DiscreteGaussian (const Image &image1, double variance, unsigned int maximumKernelWidth=32u, double maximumError=0.01, bool useImageSpacing=true);
  Image DiscreteGaussian (const Image &image1, const std::vector< double > &variance=std::vector< double >(3, 1.0), unsigned int maximumKernelWidth=32u, const std::vector< double > &maximumError=std::vector< double >(3, 0.01), bool useImageSpacing=true);


private:
  bool CheckImageDimension(const Image& inputImage);

public:
  std::string             m_LogFileName;

  bool                    m_LogToFile;
  bool                    m_LogToConsole;
};

} // end namespace simple
} // end namespace itk

#endif // __sitkelastiximagefilterimpl_h_