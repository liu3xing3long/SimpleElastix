import os
import sys

import SimpleITK as sitk

data = "/home/liuxinglong/data/LUNA/raw/000.mhd"

try:
    med_filter = sitk.MedImageGPUFilter()
    img = sitk.ReadImage(data)

    # simg = med_filter.BinaryThreshold(img, -1000, 1000, 1, 0)
    # simg = med_filter.Threshold(img, -1000, 1000, -1000)
    # simg = med_filter.Mean(img, 6)
    # simg = med_filter.DiscreteGaussian(img, 0.1)
    simg = med_filter.GradientAnisotropicDiffusion(img, 0.04)

    # sitk.Show(img)
    # sitk.Show(simg)

except Exception, e:
    print "Exception occured {}".format(e.message)



















