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

/**
 * Procedural interface 
 */

} // end namespace simple
} // end namespace itk

#endif // __sitkelastiximagefilter_cxx_