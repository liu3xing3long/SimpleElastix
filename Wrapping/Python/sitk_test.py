import os
import sys

import SimpleITK as sitk

data = "/home/liuxinglong/data/LUNA/raw/000.mhd"

test_iterations = 1

for i in range(test_iterations):
    try:
        med_filter = sitk.MedImageGPUFilter()
        img = sitk.ReadImage(data)

        # simg = med_filter.BinaryThreshold(img, -1000, 1000, 1, 0) # PASS
        # simg = med_filter.Threshold(img, -1000, 1000, -1000) # PASS
        # simg = med_filter.Mean(img, [3, 3, 3]) # PASS
        # simg = med_filter.DiscreteGaussian(img) # PASS
        # simg = med_filter.GradientAnisotropicDiffusion(img, 0.04) # PASS
        # simg = med_filter.RecursiveGaussian(img) # PASS
        # simg = med_filter.Median(img, [3, 3, 3])
        simg = med_filter.Median(img, [2,2,2])
        
        # print img
        # print simg
        # sitk.Show(img)
        sitk.Show(simg)


    except Exception, e:
        print "Exception occured {}".format(e.message)



















