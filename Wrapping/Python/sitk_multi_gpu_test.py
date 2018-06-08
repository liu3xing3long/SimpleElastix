import os
import sys

import SimpleITK as sitk

data = "/home/liuxinglong/data/LUNA/raw/000.mhd"


os.environ["CUDA_VISIBLE_DEVICES"] = "0,1,2,3"

med_filter = sitk.MedImageGPUFilter()
img = sitk.ReadImage(data)
rimg = med_filter.Resample(img)









