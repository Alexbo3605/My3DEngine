----In development----

Hello everyone, this is my humble implementation of a 3D visualizer (because it's a shame to call it an engine ;) )

Below is the entire theoretical part that I used


1. dot Product a ⋅ b
   
The result is a scalar (number) that shows how much the two vectors point in the same direction. The larger the dot product, the closer the vectors are to being parallel and pointing in the same direction.

a = (aX, aY ,aZ)

b = (bX, bY ,bZ)

a ⋅ b =  aX * bX + aY * bY + aZ * bZ

<img width="3998" height="2666" alt="image" src="https://github.com/user-attachments/assets/d0d14a8f-6175-405e-8bf5-649b8351e8d2" />



2. Cross Product  a × b

The cross product of two vectors, a and b, results in a new vector that is perpendicular to both a and b. (Using for cliping)

a = (aX, aY ,aZ)

b = (bX, bY ,bZ)

a × b = c where  c =(cX, cY ,cZ)

cX = aY * bZ - aZ * bY

cY = aZ * bX - aX * bZ

cZ = aX * bY - aY * bX
​





<h2>Converting a 3D object to a 2D image</h2>



We have a 3D model, namely its points and edges (we will omit the edges for now).
Let's assume there is a point A(x,y,z) in order to convert these 3D coordinates into 2D,
the following steps are performed:


1) Each vertex of the model has 3D coordinates (x,y,z). These are converted into homogeneous coordinates by adding a fourth component "w = 1", resulting in the 
vector (x,y,z,w) ==> vector (x,y,z,1)

This is needed for future matrix multiplication (and you can only multiply matrices of the same dimension)

<hr>
2) A 4x4 matrix is created to define how the 3D scene will be "flattened" onto a 2D plane. There are two main types of how to do this: perspective(human eye) and orthographic. 
We will use orthographic: <br><br>



<img width="370" height="152" alt="image" src="https://github.com/user-attachments/assets/9f6eef52-563e-4bcc-a513-0a28cac4dd3e" />
<br><br>
n ==> The distance to the near plane.<br><br>
f ==> The distance to the far plane.<br><br>
r ==> The distance to the right side of the clipping plane.<br><br>
t ==> The distance to the top side of the clipping plane.<br><br>
(may vary depending on the task and implementation)<br><br><br>

<hr>
3) The model's coordinate vector is multiplied by the projection matrix. 

The result is a new vector  

​vector (x',y',z',w'), which represents the "raw" coordinates in Clip Space.

<hr>
4) The coordinates  are divided by the fourth component w

This process normalizes the coordinates into a range of -1 to 1, creating the Normalized Device Coordinates (NDC).

<hr>
5) The NDC coordinates are scaled and shifted to match the dimensions of the screen. 
This final step gives you the 2D coordinates in pixels, ready to be displayed on the monitor

(Depending on the task at hand, there may be more steps here)
​<hr>
 


