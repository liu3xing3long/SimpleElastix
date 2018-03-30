#ifndef __sitkmedimagegpufilter_cxx_
#define __sitkmedimagegpufilter_cxx_

#include "sitkMedImageGPUFilter.h"
#include "sitkMedImageGPUFilterImpl.h"

namespace itk {
  namespace simple {

MedImageGPUFilter
::MedImageGPUFilter( void ) : m_Pimple( new MedImageGPUFilterImpl )
{
}

MedImageGPUFilter
::~MedImageGPUFilter( void )
{
  delete m_Pimple;
  m_Pimple = NULL;
}

const std::string 
MedImageGPUFilter
::GetName( void )
{ 
  return this->m_Pimple->GetName();
}

MedImageGPUFilter::Self& 
MedImageGPUFilter
::SetLogFileName( std::string logFileName )
{
  this->m_Pimple->SetLogFileName( logFileName );
  return *this;
}

std::string
MedImageGPUFilter
::GetLogFileName( void )
{
  return this->m_Pimple->GetLogFileName();
}

MedImageGPUFilter::Self& 
MedImageGPUFilter
::RemoveLogFileName( void )
{
  this->m_Pimple->RemoveLogFileName();
  return *this;
}

MedImageGPUFilter::Self& 
MedImageGPUFilter
::SetLogToFile( bool logToFile )
{
  this->m_Pimple->SetLogToFile( logToFile );
  return *this;
}

bool
MedImageGPUFilter
::GetLogToFile( void )
{
  return this->m_Pimple->GetLogToFile();
}

MedImageGPUFilter::Self& 
MedImageGPUFilter
::LogToFileOn()
{
  this->m_Pimple->LogToFileOn();
  return *this;
}

MedImageGPUFilter::Self& 
MedImageGPUFilter
::LogToFileOff()
{
  this->m_Pimple->LogToFileOff();
  return *this;
}

MedImageGPUFilter::Self& 
MedImageGPUFilter
::SetLogToConsole( bool logToConsole )
{
  this->m_Pimple->SetLogToConsole( logToConsole );
  return *this;
}

bool
MedImageGPUFilter
::GetLogToConsole( void )
{
  return this->m_Pimple->GetLogToConsole();
}

MedImageGPUFilter::Self& 
MedImageGPUFilter
::LogToConsoleOn()
{
  this->m_Pimple->LogToConsoleOn();
  return *this;
}

MedImageGPUFilter::Self& 
MedImageGPUFilter
::LogToConsoleOff()
{
  this->m_Pimple->LogToConsoleOff();
  return *this;
}

bool MedImageGPUFilter
::IsGPUEnabled( void )
{
  return this->m_Pimple->IsGPUEnabled();
}

Image MedImageGPUFilter
::Resample(const Image& inputImage, const std::vector<float> outputSpacing)
{
  return this->m_Pimple->Resample(inputImage, outputSpacing);
}

Image MedImageGPUFilter
::Threshold( const Image& inputImage, double lower /* = 0.0 */, double upper /* = 255.0 */, double outsideValue /* = 0.0 */)
{
  return this->m_Pimple->Threshold(inputImage, lower, upper, outsideValue);
}

Image MedImageGPUFilter
::BinaryDilate(const Image& inputImage, unsigned int dilateRadius)
{
  return this->m_Pimple->BinaryDilate(inputImage, dilateRadius);
}

Image MedImageGPUFilter
::BinaryErode(const Image& inputImage, unsigned int erodeRadius)
{
  return this->m_Pimple->BinaryErode(inputImage, erodeRadius);
}

Image MedImageGPUFilter
::BinaryOpen(const Image& inputImage, unsigned int Radius)
{
  return this->m_Pimple->BinaryOpen(inputImage, Radius);
}

Image MedImageGPUFilter
::BinaryClose(const Image& inputImage, unsigned int Radius)
{
  return this->m_Pimple->BinaryClose(inputImage, Radius);
}

Image MedImageGPUFilter
::BinaryThreshold(const Image& inputImage, double lower /* = 0.0 */, double upper /* = 255.0 */, uint8_t insideValue /* = 1u */, uint8_t outsideValue /* = 0u */)
{
  return this->m_Pimple->BinaryThreshold(inputImage, lower, upper, insideValue, outsideValue);
}

Image MedImageGPUFilter
::Median(const Image& inputImage, const std::vector<unsigned int>& radius /* = std::vector< unsigned int >(3, 1) */)
{
  return this->m_Pimple->Median(inputImage, radius);
}

Image MedImageGPUFilter
::Mean(const Image& inputImage, const std::vector<unsigned int>& radius/*  = std::vector< unsigned int >(3, 1) */)
{
  return this->m_Pimple->Mean(inputImage, radius);
}

Image MedImageGPUFilter
::GradientAnisotropicDiffusion(const Image& inputImage, double timeStep/*  = 0.125 */, double conductanceParameter/*  = 3 */, 
                               unsigned int conductanceScalingUpdateInterval/*  = 1u */, uint32_t numberOfIterations/*  = 5u */)
{
  return this->m_Pimple->GradientAnisotropicDiffusion(inputImage, timeStep, conductanceParameter, conductanceScalingUpdateInterval, numberOfIterations);
}

Image MedImageGPUFilter
::RecursiveGaussian (const Image &inputImage, double sigma /* = 1.0 */, bool normalizeAcrossScale /* = false */, unsigned int orderType /* = 0 */, unsigned int direction /* = 0u */)
{
  return this->m_Pimple->RecursiveGaussian(inputImage, sigma, normalizeAcrossScale, orderType , direction);
}

Image MedImageGPUFilter
::DiscreteGaussian (const Image& inputImage, double variance, unsigned int maximumKernelWidth/* =32u */, 
                    double maximumError/* =0.01 */, bool useImageSpacing/* =true */)
{
  return this->m_Pimple->DiscreteGaussian(inputImage, variance, maximumKernelWidth, maximumError, useImageSpacing);
}

Image MedImageGPUFilter
::DiscreteGaussian (const Image& inputImage, const std::vector< double >& variance/* =std::vector< double >(3, 1.0)*/, 
                    unsigned int maximumKernelWidth/* =32u */, const std::vector< double >& maximumError/* =std::vector< double >(3, 0.01) */, 
                    bool useImageSpacing/* =true */)
{
  return this->m_Pimple->DiscreteGaussian(inputImage, variance, maximumKernelWidth, maximumError, useImageSpacing);
}

/**
 * Procedural interface 
 */

} // end namespace simple
} // end namespace itk

#endif // __sitkelastiximagefilter_cxx_