## GaussianBlur

Original vs My impementation of GaussianBlur vs cv::GaussianBlur functions
<a href="https://ibb.co/n6pJC9s"><img src="https://i.ibb.co/XjHR81Z/Test1024x1024pi.jpg" alt="Test1024x1024pi" border="0"></a>
<a href="https://ibb.co/8K3HhB6"><img src="https://i.ibb.co/gj1xn7z/test-blur.jpg" alt="test-blur" border="0"></a>
<a href="https://ibb.co/sgwh4qX"><img src="https://i.ibb.co/Zf83rxb/real-blur.jpg" alt="real-blur" border="0"></a>

### Contents
#### Using next formulas:
1. A Gaussian function of two variables was used to form the mask:
			 $h(x,y)=e^{\frac{-(x^2 + y^2)}{2\sigma^2}}$
2. Prepared mask using Gaussian function:
	$w(x,y)=h(x,y)$
3. To get the image, I used correlation with the prepared mask:
	$w(x,y)\circ f(x,y)=\sum_{s=-a}^a \sum_{t=-b}^b w(s,t)f(x+s,y+t)$

## MedianBlur
Original vs My impementation of MedianBlur vs cv::MedianBlur functions
<a href="https://ibb.co/n6pJC9s"><img src="https://i.ibb.co/XjHR81Z/Test1024x1024pi.jpg" alt="Test1024x1024pi" border="0"></a>
<a href="https://ibb.co/LvFHhTs"><img src="https://i.ibb.co/nRGt8XK/test-blur.jpg" alt="test-blur" border="0"></a>
<a href="https://ibb.co/7n9x7Qg"><img src="https://i.ibb.co/y63mLph/real-blur.jpg" alt="real-blur" border="0"></a>


### Contents
#### Using next formulas:
1. Calculating the median point:
			$\tilde{f}(x,y)= \displaystyle med_{(r,c)\in S_{xy}} \{g(s,t)\}$

## Laplacian
Original vs My impementation vs cv::Laplacian functions
![Test1024x1024pi](https://github.com/user-attachments/assets/6b7bc3cd-0b3f-4525-8268-b7f65afcf7db)
![test_blur](https://github.com/user-attachments/assets/0cf51e9e-1eca-4040-ac91-e6ee4ed19b24)
![real_blur](https://github.com/user-attachments/assets/8ebba210-ad54-4b2f-a9d7-c0cb10cc562b)

### Contents
#### Using next mask with correlation 
<a href="https://imgbb.com/"><img src="https://i.ibb.co/FBHsTTr/image.png" alt="image" border="0"></a>

## Sobel
Original vs My impementation vs cv::Sobel functions
![Test1024x1024pi](https://github.com/user-attachments/assets/6b7bc3cd-0b3f-4525-8268-b7f65afcf7db)
![test_blur](https://github.com/user-attachments/assets/874bb9c5-43cf-4be1-8736-8f8a29b464f2)
![real_blur](https://github.com/user-attachments/assets/e325a15b-d0d8-4434-88ff-47ee014c399d)

### Contents
#### Using next mask with discrete approximation of the sobel operator
$$
M(x,y) = | {(z_7 + 2z_8 + z_9) - (z_1 + 2z_2 + z_3) | + | (z_3 + 2z_6 + z_9) - (z_1 + 2z_4 + z_7) | }
$$
equivalent to
$$
M(x,y) = mag(\nabla f) = mag(grad(f)) = \begin{bmatrix}-1&-2&-1\cr 0&0&0 \cr 1&2&1 \end{bmatrix}
$$