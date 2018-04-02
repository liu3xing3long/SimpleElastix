#ifndef __sitkmedimagegpufilter_h_
#define __sitkmedimagegpufilter_h_

#include "sitkCommon.h"
#include "sitkImage.h"

namespace itk
{
namespace simple
{

/** \class MedImageGPUFilter
* \brief The class that wraps the MedImageGPUFilter GPU library.
*/
class SITKCommon_EXPORT MedImageGPUFilter
{
public:
    
    MedImageGPUFilter( void );
    
    ~MedImageGPUFilter( void );
    
    typedef MedImageGPUFilter Self;
    
    const std::string
    GetName( void );
    
    Self &
    SetLogFileName( const std::string logFileName );
    
    std::string
    GetLogFileName( void );
    
    Self &
    RemoveLogFileName( void );
    
    Self &
    SetLogToFile( const bool logToFile );
    
    bool
    GetLogToFile( void );
    
    Self &
    LogToFileOn( void );
    
    Self &
    LogToFileOff( void );
    
    Self &
    SetLogToConsole( bool );
    
    bool
    GetLogToConsole( void );
    
    Self &
    LogToConsoleOn();
    
    Self &
    LogToConsoleOff();
    
    bool
    IsGPUEnabled( void );

    void 
    PrintGPUInfo( void );

public:
    ///////////////////////////////////////////////////////////////////////////
    // INTERFACE CALLS
    // NOTE, ALL returned Image should be checked whether the GetNumberOfPixels == 0
    // 0 = method call failed, returned a blank image
    // ~0 = succeeded
    ///////////////////////////////////////////////////////////////////////////
    
    // resample input image at given spacing
    Image
    Resample( const Image &inputImage, const std::vector< float > outputSpacing );
    
    Image
    Threshold( const Image &inputImage, double lower = 0.0, double upper = 255.0, double outsideValue = 0.0 );
    
    // morphology operations
    Image
    BinaryDilate( const Image &inputImage, unsigned int dilateRadius = 1 );
    
    Image
    BinaryErode( const Image &inputImage, unsigned int erodeRadius = 1 );
    
    Image
    BinaryOpen( const Image &inputImage, unsigned int Radius = 1 );
    
    Image
    BinaryClose( const Image &inputImage, unsigned int Radius = 1 );
    
    // image filters
    Image
    BinaryThreshold( const Image &inputImage, double lower = 0.0, double upper = 255.0, uint8_t insideValue = 1u,
                     uint8_t outsideValue = 0u );
    
    Image
    Median( const Image &inputImage, const std::vector< unsigned int > &radius = std::vector< unsigned int >( 3, 1 ) );
    
    Image
    Mean( const Image &inputImage, const std::vector< unsigned int > &radius = std::vector< unsigned int >( 3, 1 ) );
    
    Image
    GradientAnisotropicDiffusion( const Image &inputImage, double timeStep = 0.125, double conductanceParameter = 3,
                                  unsigned int conductanceScalingUpdateInterval = 1u,
                                  uint32_t numberOfIterations = 5u );
    
    Image
    RecursiveGaussian( const Image &inputImage, double sigma = 1.0, bool normalizeAcrossScale = false,
                       unsigned int orderType = 0, unsigned int direction = 0u );
    
    Image
    DiscreteGaussian( const Image &inputImage, double variance = 1.0, unsigned int maximumKernelWidth = 32u,
                      double maximumError = 0.01, bool useImageSpacing = true );
    
    Image
    DiscreteGaussian( const Image &inputImage, const std::vector< double > &variance = std::vector< double >( 3, 1.0 ),
                      unsigned int maximumKernelWidth = 32u,
                      const std::vector< double > &maximumError = std::vector< double >( 3, 0.01 ),
                      bool useImageSpacing = true );

private:
    struct MedImageGPUFilterImpl;
    MedImageGPUFilterImpl *m_Pimple;
    
};

// Procedural Interface 

} // end namespace simple
} // end namespace itk

#endif // __sitkelastiximagefilter_h_