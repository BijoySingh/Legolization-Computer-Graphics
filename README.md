# Legolization-Computer-Graphics
## Legolization Project for Computer Graphics Course CS775 
Authors
- Bijoy Singh Kochar 
- Dheerendra Rathor

Instructor
- Prof. Parag Chaudhuri

A course project implementation of [Legolization: Optimizing LEGO Designs](http://www.cmlab.csie.ntu.edu.tw/~forestking/research/SIGA15-Legolization/)

## Legolization: Optimizing LEGO Designs
Authors
- Sheng-Jie Luo
- Yonghao Yue
- Chun-Kai Huang
- Yu-Huan Chung
- Sei Imai
- Tomoyuki Nishita
- Bing-Yu Chen

### Abstract
Building LEGO sculptures requires accounting for the target object’s shape, colors, and stability. In particular, finding a good layout of LEGO bricks that prevents the sculpture from collapsing (due to its own weight) is usually challenging, and it becomes increasingly difficult as the target object becomes larger or more complex. We devise a force-based analysis for estimating physical stability of a given sculpture. Unlike previous techniques for Legolization, which typically use heuristic-based metrics for stability estimation, our force-based metric gives 1) an ordering in the strength so that we know which structure is more stable, and 2) a threshold for stability so that we know which one is stable enough. In addition, our stability analysis tells us the weak portion of the sculpture. Building atop our stability analysis, we present a layout refinement algorithm that iteratively improves the structure around the weak portion, allowing for automatic generation of a LEGO brick layout from a given 3D model, accounting for color information, required workload (in terms of the number of bricks) and physical stability. We demonstrate the success of our method with real LEGO sculptures built up from a wide variety of 3D models, and compare against previous methods.

## To Run
cd legolization/
make unit

or 
python3 read_json.py
make

