<h1 align="center">Mandelbrot Fractal</h1>
<h3 align="center">Mandelbrot fractal parallelized using the open MPI library.</h3>
<p align="center"> 
  <img src="https://img.shields.io/badge/OpenMPI-pink"/>  
  <img src="https://img.shields.io/badge/-EasyBMP-pink"/>
  <img src="https://img.shields.io/badge/gcc g++-pink"/>
</p>
<br/>

## Objective
<p align="justify"> 
  <a>The Mandelbrot fractal is a representation of a set of complex numbers and its calculation can be computationally intensive depending on the chosen parameters. 
    The objective of this project is to explore the parallelization of the Mandelbrot fractal calculation using the Open MPI, where we can divide the work 
    between several processes, thus taking advantage of the machine's processing power.
</p>
  
## Setup
<p align="justify"> 
 <a>To setup your system just use git clone command, all the files are included in this repository. To do it, use:</a>
</p>

```shell
git clone 'https://github.com/jvlima-ufsm/t1-zatgirl'
```

<a>Navigate to the directory</a>
</p>

```shell
cd .\x64\Debug\
```  

<a>Run the compiled project</a>
</p>

```shell
mpiexec -np <processes> .\MPIProject.exe
```  

## Results
<p align="justify"> 
 <a>Tests were performed varying the resolution of the image to be generated and maximum number of iterations.</a>
</p>

| Image Resolution | Max. Iterations   | Processes | Time (Average)          |
|------------------|-------------------|-----------|-------------------------|
| 800x600          | 1000              | 11        | 3.16278s                |
| 800x600          | 2000              | 11        | 6.27522s                |
| 800x600          | 1000              | 5         | 6.00727s                |
| 800x600          | 2000              | 5         | 11.7608s                |
| 800x600          | 1000              | 1         | 10.1438s                |
| 800x600          | 2000              | 1         | 20.0548s                |
| 2560x1440 (2K)   | 1000              | 11        | 24.3103s                |
| 2560x1440 (2K)   | 2000              | 11        | 47.9565s                |
| 2560x1440 (2K)   | 1000              | 5         | 45.7174s                |
| 2560x1440 (2K)   | 2000              | 5         | 89.8285s =~ 1min:29s    |
| 2560x1440 (2K)   | 1000              | 1         | 78.6253s =~ 1min:18s    |
| 2560x1440 (2K)   | 2000              | 1         | 153.681s =~ 2min:33s    |
| 3840x2160 (4K)   | 1000              | 11        | 54.0461s                |
| 3840x2160 (4K)   | 2000              | 11        | 108.486s =~ 1min:48s    |
| 3840x2160 (4K)   | 1000              | 5         | 102.748s =~ 1min:42s    |
| 3840x2160 (4K)   | 2000              | 5         | 204.288s =~ 3min:24s    |
| 3840x2160 (4K)   | 1000              | 1         | 177.567s =~ 2min:57s    |
| 3840x2160 (4K)   | 2000              | 1         | 346.188s =~ 5min:46s    |
| 7680x4320 (8K)   | 1000              | 32        | 110.274s =~ 1min:50s    |
| 7680x4320 (8K)   | 1000              | 11        | 219.704s =~ 3min:39s    |
| 7680x4320 (8K)   | 1000              | 1         | 707.677s =~ 11min:47s   |
| 7680x4320 (8K)   | 2000              | 11        | 431.415s =~ 7min:11s    |
| 7680x4320 (8K)   | 2000              | 1         | 1398.18s =~ 23min:18s   |
| 20000x11250 (20K)| 2000              | 11        | 53min                   |
| 40000x22500 (40K)| 2000              | 11        | 3h:11min                |

* For reasons of teeerrible computer, tests above 8K were executed only 1 time :rage:

From the data obtained, we can analyze that:
* Increase the number of maximum iterations to increase accuracy in calculating the Mandelbrot set, increased execution time;
* Increasing the number of processes decreases the execution time;
* Increasing the image resolution so that it is possible to zoom in and see the fractal details, significantly increased the execution time;
* Increasing the number of processes beyond the amount of available cores will divide the work more but will not necessarily run faster, as only x processes will be able to run simultaneously.
<br/> 

#### The images generated in different resolutions are available at the link below.
https://drive.google.com/drive/folders/1A_kC_pqUcka3hcDQ4YF53u62iM1YQn6h?usp=sharing
<br/> 
<br/> 
<a>I used Microsoft Visual Studio to build the project and Microsoft PowerShell to run MPI commands.</a>
<br/> 
<p align="right"> 
Developed by Mauren Walter D'Avila in the Parallel Programming discipline :purple_heart: <br/> 
Computer Engineering Academic
</p>
