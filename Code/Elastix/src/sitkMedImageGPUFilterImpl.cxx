#ifndef __sitkmedimagegpufilterimpl_cxx_
#define __sitkmedimagegpufilterimpl_cxx__

#include "sitkMedImageGPUFilter.h"
#include "sitkMedImageGPUFilterImpl.h"
#include "sitkCastImageFilter.h"
#include "elxCLGPUInterface.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE( x ) delete (x); (x) = NULL;
#endif

namespace itk
{
namespace simple
{

MedImageGPUFilter::MedImageGPUFilterImpl::MedImageGPUFilterImpl( void )
{
    // Register this class with SimpleITK
    this->m_LogFileName = "";
    
    this->m_LogToFile = false;
    this->m_LogToConsole = true;
    
}

MedImageGPUFilter::MedImageGPUFilterImpl::~MedImageGPUFilterImpl()
{
}

const std::string
MedImageGPUFilter::MedImageGPUFilterImpl::GetName( void )
{
    const std::string name = "MedImageGPUFilter";
    return name;
}

void
MedImageGPUFilter::MedImageGPUFilterImpl::SetLogFileName( std::string logFileName )
{
    this->m_LogFileName = logFileName;
}

std::string
MedImageGPUFilter::MedImageGPUFilterImpl::GetLogFileName( void )
{
    return this->m_LogFileName;
}

void
MedImageGPUFilter::MedImageGPUFilterImpl::RemoveLogFileName( void )
{
    this->m_LogFileName = "";
}

void
MedImageGPUFilter::MedImageGPUFilterImpl::SetLogToFile( bool logToFile )
{
    this->m_LogToFile = logToFile;
}

bool
MedImageGPUFilter::MedImageGPUFilterImpl::GetLogToFile( void )
{
    return this->m_LogToFile;
}

void
MedImageGPUFilter::MedImageGPUFilterImpl::LogToFileOn()
{
    this->SetLogToFile( true );
}

void
MedImageGPUFilter::MedImageGPUFilterImpl::LogToFileOff()
{
    this->SetLogToFile( false );
}

void
MedImageGPUFilter::MedImageGPUFilterImpl::SetLogToConsole( bool logToConsole )
{
    this->m_LogToConsole = logToConsole;
}

bool
MedImageGPUFilter::MedImageGPUFilterImpl::GetLogToConsole( void )
{
    return this->m_LogToConsole;
}

void
MedImageGPUFilter::MedImageGPUFilterImpl::LogToConsoleOn()
{
    this->SetLogToConsole( true );
}

void
MedImageGPUFilter::MedImageGPUFilterImpl::LogToConsoleOff()
{
    this->SetLogToConsole( false );
}

bool
MedImageGPUFilter::MedImageGPUFilterImpl::IsGPUAvailable()
{
    bool bEnabled = false;
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    bEnabled = pInterface->IsGPUAvailable();
    SAFE_DELETE( pInterface );
    
    return bEnabled;
}

void
MedImageGPUFilter::MedImageGPUFilterImpl::PrintGPUInfo()
{
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    pInterface->PrintGPUInfo();
    SAFE_DELETE( pInterface );
}

bool
MedImageGPUFilter::MedImageGPUFilterImpl::CheckImageDimension( const Image &inputImage )
{
    if ( inputImage.GetDimension() != 3 )
    {
        return false;
    }
    else
    {
        return true;
    }
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::Resample( const Image &inputImage,
                                                    const std::vector< float > outputSpacing /* = std::vector< float >( 3, 1.0 ) */,
                                                    unsigned int uInterplolatorOrder /*= 3*/,
                                                    int iDefault_voxel_value /*= -2048*/ )
{
    // here we set an empty image
    // 'empty' means GetNumberOfPixels() == 0
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) || outputSpacing.size() != 3 )
    {
        std::cout << "Input Image Dimension or Spacing not Match," << " Spacing size  " << outputSpacing.size()
                  << std::endl;
        return outputImage;
    }
    
    // transform to elastix layer
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::CPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::CPUInputImageType * >(
            Cast( inputImage, sitkFloat32 ).GetITKBase() );
    elastix::GPUOutputImageType::Pointer gpuImage = pInterface->Resample( itkImage, outputSpacing, uInterplolatorOrder,
                                                                          iDefault_voxel_value );
    
    if ( gpuImage.IsNotNull() )
    {
        // Image outputImage;
        outputImage = Image( itkDynamicCastInDebugMode< elastix::CPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    
    return outputImage;
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::Threshold( const Image &inputImage, double lower /* = 0.0 */,
                                                     double upper /* = 255.0 */, double outsideValue /* = 0.0 */)
{
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) )
    {
        std::cout << "Input Image Dimension or Spacing not Match" << std::endl;
        return outputImage;
    }
    
    // transform to elastix layer
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::CPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::CPUInputImageType * >(
            Cast( inputImage, sitkFloat32 ).GetITKBase() );
    elastix::GPUOutputImageType::Pointer gpuImage = pInterface->Threshold( itkImage, lower, upper, outsideValue );
    
    if ( gpuImage.IsNotNull() )
    {
        // Image outputImage;
        outputImage = Image( itkDynamicCastInDebugMode< elastix::CPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    
    return outputImage;
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::BinaryDilate( const Image &inputImage, unsigned int dilateRadius )
{
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) )
    {
        std::cout << "Input Image Dimension or Spacing not Match" << std::endl;
        return outputImage;
    }
    
    // transform to elastix layer
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::BinCPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::BinCPUInputImageType * >(
            Cast( inputImage, sitkUInt8 ).GetITKBase() );
    elastix::BinGPUOutputImageType::Pointer gpuImage = pInterface->BinaryDilate( itkImage, dilateRadius );
    
    if ( gpuImage.IsNotNull() )
    {
        // Image outputImage;
        outputImage = Image( itkDynamicCastInDebugMode< elastix::BinCPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    
    return outputImage;
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::BinaryErode( const Image &inputImage, unsigned int erodeRadius )
{
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) )
    {
        std::cout << "Input Image Dimension or Spacing not Match, require " << std::endl;
        return outputImage;
    }
    
    // transform to elastix layer
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::BinCPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::BinCPUInputImageType * >(
            Cast( inputImage, sitkUInt8 ).GetITKBase() );
    elastix::BinGPUOutputImageType::Pointer gpuImage = pInterface->BinaryErode( itkImage, erodeRadius );
    
    if ( gpuImage.IsNotNull() )
    {
        // Image outputImage;
        outputImage = Image( itkDynamicCastInDebugMode< elastix::BinCPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    return outputImage;
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::BinaryOpen( const Image &inputImage, unsigned int Radius )
{
    // open means first erode then dilate
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) )
    {
        std::cout << "Input Image Dimension or Spacing not Match, require " << std::endl;
        return outputImage;
    }
    
    ////////////////////////////////
    // erode
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::BinCPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::BinCPUInputImageType * >(
            Cast( inputImage, sitkUInt8 ).GetITKBase() );
    elastix::BinGPUOutputImageType::Pointer gpuImage = pInterface->BinaryErode( itkImage, Radius );
    
    if ( gpuImage.IsNotNull() )
    {
        itkImage = itkDynamicCastInDebugMode< elastix::BinCPUInputImageType * >( gpuImage );
        SAFE_DELETE( pInterface );
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
        SAFE_DELETE( pInterface );
        return outputImage;
    }
    
    ///////////////////////////////////
    // dilate
    pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    gpuImage = pInterface->BinaryDilate( itkImage, Radius );
    
    if ( gpuImage.IsNotNull() )
    {
        outputImage = Image( itkDynamicCastInDebugMode< elastix::BinCPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    return outputImage;
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::BinaryClose( const Image &inputImage, unsigned int Radius )
{
    // close means first dilate then erode
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) )
    {
        std::cout << "Input Image Dimension or Spacing not Match, require " << std::endl;
        return outputImage;
    }
    
    ////////////////////////////////
    // dilate
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::BinCPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::BinCPUInputImageType * >(
            Cast( inputImage, sitkUInt8 ).GetITKBase() );
    elastix::BinGPUOutputImageType::Pointer gpuImage = pInterface->BinaryDilate( itkImage, Radius );
    
    if ( gpuImage.IsNotNull() )
    {
        itkImage = itkDynamicCastInDebugMode< elastix::BinCPUInputImageType * >( gpuImage );
        SAFE_DELETE( pInterface );
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
        SAFE_DELETE( pInterface );
        return outputImage;
    }
    
    ///////////////////////////////////
    // dilate
    pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    gpuImage = pInterface->BinaryErode( itkImage, Radius );
    
    if ( gpuImage.IsNotNull() )
    {
        outputImage = Image( itkDynamicCastInDebugMode< elastix::BinCPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    return outputImage;
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::BinaryThreshold( const Image &inputImage, double lower /* = 0.0 */,
                                                           double upper /* = 1.0 */, uint8_t insideValue /* = 1u */,
                                                           uint8_t outsideValue /* = 0u */)
{
    // close means first dilate then erode
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) )
    {
        std::cout << "Input Image Dimension or Spacing not Match, require " << std::endl;
        return outputImage;
    }
    
    ////////////////////////////////
    // dilate
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::CPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::CPUInputImageType * >(
            Cast( inputImage, sitkFloat32 ).GetITKBase() );
    elastix::BinGPUOutputImageType::Pointer gpuImage = pInterface->BinaryThreshold( itkImage, lower, upper, insideValue,
                                                                                    outsideValue );
    
    if ( gpuImage.IsNotNull() )
    {
        // Image outputImage;
        outputImage = Image( itkDynamicCastInDebugMode< elastix::BinCPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    return outputImage;
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::Median( const Image &inputImage,
                                                  const std::vector< unsigned int > &radius /* = std::vector< unsigned int >(3, 1) */)
{
    // here we set an empty image
    // 'empty' means GetNumberOfPixels() == 0
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) )
    {
        std::cout << "Input Image Dimension or Spacing not Match, require " << std::endl;
        return outputImage;
    }
    if ( radius.size() != 3 )
    {
        std::cout << "Input Radius not match, require " << std::endl;
        return outputImage;
    }
    
    // transform to elastix layer
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::CPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::CPUInputImageType * >(
            Cast( inputImage, sitkFloat32 ).GetITKBase() );
    elastix::GPUOutputImageType::Pointer gpuImage = pInterface->Median( itkImage, radius );
    
    if ( gpuImage.IsNotNull() )
    {
        // Image outputImage;
        outputImage = Image( itkDynamicCastInDebugMode< elastix::CPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    
    return outputImage;
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::Mean( const Image &inputImage,
                                                const std::vector< unsigned int > &radius /* = std::vector< unsigned int >(3, 1) */)
{
    // here we set an empty image
    // 'empty' means GetNumberOfPixels() == 0
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) )
    {
        std::cout << "Input Image Dimension or Spacing not Match, require " << std::endl;
        return outputImage;
    }
    if ( radius.size() != 3 )
    {
        std::cout << "Input Radius not match, require " << std::endl;
        return outputImage;
    }
    
    // transform to elastix layer
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::CPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::CPUInputImageType * >(
            Cast( inputImage, sitkFloat32 ).GetITKBase() );
    elastix::GPUOutputImageType::Pointer gpuImage = pInterface->Mean( itkImage, radius );
    
    if ( gpuImage.IsNotNull() )
    {
        // Image outputImage;
        outputImage = Image( itkDynamicCastInDebugMode< elastix::CPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    
    return outputImage;
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::GradientAnisotropicDiffusion( const Image &inputImage,
                                                                        double timeStep /* = 0.125 */,
                                                                        double conductanceParameter /* = 3 */,
                                                                        unsigned int conductanceScalingUpdateInterval /* = 1u */,
                                                                        uint32_t numberOfIterations /* = 5u */)
{
    // here we set an empty image
    // 'empty' means GetNumberOfPixels() == 0
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) )
    {
        std::cout << "Input Image Dimension or Spacing not Match, require " << std::endl;
        return outputImage;
    }
    
    // transform to elastix layer
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::CPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::CPUInputImageType * >(
            Cast( inputImage, sitkFloat32 ).GetITKBase() );
    elastix::GPUOutputImageType::Pointer gpuImage = pInterface->GradientAnisotropicDiffusion( itkImage, timeStep,
                                                                                              conductanceParameter,
                                                                                              conductanceScalingUpdateInterval,
                                                                                              numberOfIterations );
    
    if ( gpuImage.IsNotNull() )
    {
        // Image outputImage;
        outputImage = Image( itkDynamicCastInDebugMode< elastix::CPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    
    return outputImage;
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::RecursiveGaussian( const Image &inputImage, double sigma /* = 1.0 */,
                                                             bool normalizeAcrossScale /* = false */,
                                                             unsigned int orderType /* = 0 */,
                                                             unsigned int direction /* = 0u */)
{
    // here we set an empty image
    // 'empty' means GetNumberOfPixels() == 0
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) )
    {
        std::cout << "Input Image Dimension or Spacing not Match, require " << std::endl;
        return outputImage;
    }
    
    // transform to elastix layer
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::CPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::CPUInputImageType * >(
            Cast( inputImage, sitkFloat32 ).GetITKBase() );
    elastix::GPUOutputImageType::Pointer gpuImage = pInterface->RecursiveGaussian( itkImage, sigma,
                                                                                   normalizeAcrossScale, orderType,
                                                                                   direction );
    
    if ( gpuImage.IsNotNull() )
    {
        // Image outputImage;
        outputImage = Image( itkDynamicCastInDebugMode< elastix::CPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    
    return outputImage;
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::DiscreteGaussian( const Image &inputImage, double variance,
                                                            unsigned int maximumKernelWidth/* =32u */,
                                                            double maximumError/* =0.01 */,
                                                            bool useImageSpacing/* =true */)
{
    // here we set an empty image
    // 'empty' means GetNumberOfPixels() == 0
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) )
    {
        std::cout << "Input Image Dimension or Spacing not Match, require " << std::endl;
        return outputImage;
    }
    
    // transform to elastix layer
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::CPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::CPUInputImageType * >(
            Cast( inputImage, sitkFloat32 ).GetITKBase() );
    elastix::GPUOutputImageType::Pointer gpuImage = pInterface->DiscreteGaussian( itkImage, variance,
                                                                                  maximumKernelWidth, maximumError,
                                                                                  useImageSpacing );
    
    if ( gpuImage.IsNotNull() )
    {
        // Image outputImage;
        outputImage = Image( itkDynamicCastInDebugMode< elastix::CPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    
    return outputImage;
}

Image
MedImageGPUFilter::MedImageGPUFilterImpl::DiscreteGaussian( const Image &inputImage,
                                                            const std::vector< double > &variance/* =std::vector< double >(3, 1.0) */,
                                                            unsigned int maximumKernelWidth/* =32u */,
                                                            const std::vector< double > &maximumError/* =std::vector< double >(3, 0.01) */,
                                                            bool useImageSpacing/* =true */)
{
    // here we set an empty image
    // 'empty' means GetNumberOfPixels() == 0
    Image outputImage;
    if ( !CheckImageDimension( inputImage ) )
    {
        std::cout << "Input Image Dimension or Spacing not Match, require " << std::endl;
        return outputImage;
    }
    
    // transform to elastix layer
    elastix::CLGPUInterface *pInterface = new elastix::CLGPUInterface();
    pInterface->Init();
    
    elastix::CPUInputImageType::Pointer itkImage = itkDynamicCastInDebugMode< elastix::CPUInputImageType * >(
            Cast( inputImage, sitkFloat32 ).GetITKBase() );
    elastix::GPUOutputImageType::Pointer gpuImage = pInterface->DiscreteGaussian( itkImage, variance,
                                                                                  maximumKernelWidth, maximumError,
                                                                                  useImageSpacing );
    
    if ( gpuImage.IsNotNull() )
    {
        // Image outputImage;
        outputImage = Image( itkDynamicCastInDebugMode< elastix::CPUInputImageType * >( gpuImage ) );
        outputImage.MakeUnique();
    }
    else
    {
        std::cout << pInterface->GetLastError() << std::endl;
    }
    
    SAFE_DELETE( pInterface );
    
    return outputImage;
}


} // end namespace simple
} // end namespace itk

#endif // __sitkelastiximagefilterimpl_cxx_