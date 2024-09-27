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
Original vs My impementation vs cv::GaussianBlur functions
<a href="https://ibb.co/n6pJC9s"><img src="https://i.ibb.co/XjHR81Z/Test1024x1024pi.jpg" alt="Test1024x1024pi" border="0"></a>
<a href="https://ibb.co/g4xY1jW"><img src="https://i.ibb.co/0sx5ND9/test-blur.jpg" alt="test-blur" border="0"></a>
<a href="https://ibb.co/GH4W3Ck"><img src="https://i.ibb.co/hYJB12H/real-blur.jpg" alt="real-blur" border="0"></a>

### Contents
#### Using next mask with correlation 
<a href="https://imgbb.com/"><img src="https://i.ibb.co/FBHsTTr/image.png" alt="image" border="0"></a>
