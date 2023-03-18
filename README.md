# Master-thesis-3D-reconstruction


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

## Setup

Python 3 dependencies:

* Tensorflow 1.15
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

Examples to run code on two scenes is given below. You can download the rest of the synthetic and real data used in the paper [here](https://drive.google.com/drive/folders/128yBriW1IG_3NJ5Rp7APSTZsJqdJdfc1).

### Optimizing a NeRF

Run
```
bash download_example_data.sh
```
to get synthetic Lego dataset and the LLFF Fern dataset.

For 200k iterations, it took about 10 hours on NVIDIA GeForce RTX 3090.


To optimize a low-res Fern NeRF:
```
python run_nerf.py --config config_fern.txt
```


To optimize a low-res Lego NeRF:
```
python run_nerf.py --config config_lego.txt
```

Results will be uploaded later.


### Rendering a NeRF

Run
```
bash download_example_weights.sh
```
to get a pretrained high-res NeRF for the Fern dataset. Now you can use [`render_demo.ipynb`](https://github.com/bmild/nerf/blob/master/render_demo.ipynb) to render new views.

### Replicating the paper results

The example config files run at lower resolutions than the quantitative/qualitative results in the paper and video. To replicate the results from the paper, start with the config files in [`paper_configs/`](https://github.com/bmild/nerf/tree/master/paper_configs). Our synthetic Blender data and LLFF scenes are hosted [here](https://drive.google.com/drive/folders/128yBriW1IG_3NJ5Rp7APSTZsJqdJdfc1) and the DeepVoxels data is hosted by Vincent Sitzmann [here](https://drive.google.com/open?id=1lUvJWB6oFtT8EQ_NzBrXnmi25BufxRfl).


### Acknowledgements

This work is Adapted from [NeRF](https://github.com/bmild/nerf)
 

    
### Citation

If you find this repo helpful, please cite below paper.

```
@inproceedings{mildenhall2020nerf,
  title={NeRF: Representing Scenes as Neural Radiance Fields for View Synthesis},
  author={Ben Mildenhall and Pratul P. Srinivasan and Matthew Tancik and Jonathan T. Barron and Ravi Ramamoorthi and Ren Ng},
  year={2020},
  booktitle={ECCV},
}
```