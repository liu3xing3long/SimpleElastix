#ifndef __sitkmedimagegpufilter_h_
#define __sitkmedimagegpufilter_h_

#include "sitkCommon.h"
#include "sitkImage.h"

namespace itk { 
  namespace simple {

/** \class MedImageGPUFilter
* \brief The class that wraps the MedImageGPUFilter GPU library.
*/
class SITKCommon_EXPORT MedImageGPUFilter
{
public:

    MedImageGPUFilter( void );
    ~MedImageGPUFilter( void );

    typedef MedImageGPUFilter Self;                                

    const std::string GetName( void );

    Self& SetLogFileName( const std::string logFileName );
    std::string GetLogFileName( void );
    Self& RemoveLogFileName( void );

    Self& SetLogToFile( const bool logToFile );
    bool GetLogToFile( void );
    Self& LogToFileOn( void );
    Self& LogToFileOff( void );

    Self& SetLogToConsole( bool );
    bool GetLogToConsole( void );
    Self& LogToConsoleOn();
    Self& LogToConsoleOff();

    bool IsGPUEnabled( void );
public:
    ///////////////////////////////////////////////////////////////////////////
    // INTERFACE CALLS  
    // NOTE, ALL returned Image should be checked whether the GetNumberOfPixels == 0
    // 0 = method call failed, returned a blank image
    // ~0 = succeeded
    ///////////////////////////////////////////////////////////////////////////

    // resample input image at given spacing 
    Image Resample( const Image& inputImage, const std::vector<float> outputSpacing );

    // morphology operations
    Image BinaryDilate(const Image& inputImage, unsigned int dilateRadius = 1);
    Image BinaryErode(const Image& inputImage, unsigned int erodeRadius = 1);
    Image BinaryOpen(const Image& inputImage, unsigned int Radius = 1);
    Image BinaryClose(const Image& inputImage, unsigned int Radius = 1);
    

  private:

    struct MedImageGPUFilterImpl;
    MedImageGPUFilterImpl* m_Pimple;
    
};

// Procedural Interface 

} // end namespace simple
} // end namespace itk

#endif // __sitkelastiximagefilter_h_