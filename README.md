# Master-thesis-3D-reconstruction

In this repo TensorFlow v2.12.0 is used in comparison with the TensorFlow v1 in original repo.

## Installation

To setup a conda environment, download example training data, begin the training process, and launch Tensorboard:
```

conda env create -f environment.yml
conda activate nerf
bash download_example_data.sh
python run_nerf.py --config config_fern.txt
tensorboard --logdir=logs/summaries --port=6006
```
If everything works without errors, you can now go to `localhost:6006` in your browser and watch the "Fern" scene train.

You can also clone this repo by 
```
git clone --recursive https://github.com/vipasyan/Master-thesis-3D-reconstruction.git

```

## Setup

Python 3 dependencies:

* Tensorflow 2.12.0
* matplotlib
* numpy
* imageio
* configargparse

The LLFF data loader requires ImageMagick.

A conda environment setup file is provided including all of the above dependencies. Create the conda environment `nerf` by running:
```
conda env create -f environment.yml
```

You will also need the [LLFF code](http://github.com/fyusion/llff) (and COLMAP) set up to compute poses if you want to run on your own real data.



## Running code

Examples to run code on two scenes is given below. You can download the rest of the synthetic and real data [here](https://drive.google.com/drive/folders/128yBriW1IG_3NJ5Rp7APSTZsJqdJdfc1).

### Optimizing a NeRF

Run
```
bash download_example_data.sh
```
to get synthetic Lego dataset and the LLFF Fern dataset.

For 200k iterations, it took about 10 hours on NVIDIA GeForce RTX 3090.


To optimize a low-res Lego NeRF:
```
python run_nerf.py --config config_lego.txt
```


### Generating surfels from NeRF

Extracting the sufel points from NeRF with desired viewing direction is given in [`surfels.ipynb`](https://github.com/vipasyan/Master-thesis-3D-reconstruction/blob/main/NeRF_scripts/surfels.ipynb).


### Data

Synthetic Blender data and LLFF scenes are hosted [here](https://drive.google.com/drive/folders/128yBriW1IG_3NJ5Rp7APSTZsJqdJdfc1) and the DeepVoxels data is hosted by Vincent Sitzmann [here](https://drive.google.com/open?id=1lUvJWB6oFtT8EQ_NzBrXnmi25BufxRfl).


### PADrend

To know how to install and setup PADrend you can visit [Tutorials](https://padrend.github.io/Tutorials/index.html).

### OpenGL

To know how to set up OpenGL project you can visit [LearnOpenGL](https://learnopengl.com/).

### Acknowledgements

This work is Adapted from [NeRF](https://github.com/bmild/nerf), [PADrend](https://github.com/PADrend/PADrendComplete) and [OpenGL](https://github.com/JoeyDeVries/LearnOpenGL/tree/master)
 

    
