#ifndef __sitkmedimagegpufilterimpl_h_
#define __sitkmedimagegpufilterimpl_h_

// SimpleITK
#include "sitkMedImageGPUFilter.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkDualMemberFunctionFactory.h"

// Elastix
#include "elxElastixFilter.h"
#include "elxParameterObject.h"

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
  Image BinaryDilate(const Image& inputImage, unsigned int dilateRadius=1);
  Image BinaryErode(const Image& inputImage, unsigned int erodeRadius = 1);
  Image BinaryOpen(const Image& inputImage, unsigned int Radius = 1);
  Image BinaryClose(const Image& inputImage, unsigned int Radius = 1);

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