#include <iostream>
#include <fstream>
#include <complex>
#include <time.h>


using namespace std;


float width = 3000;
float height = 3000;
int mandelVal(int x, int y);
int main() {
  srand(time(NULL));
  

  ofstream image("mandelbrot2-inverse.ppm");
  if(image.is_open()){
    image << "P3\n" << width << " " << height << " 255\n";
    #pragma omp parallel for
    {
      for(int i = 0; i < width;i++){
	for(int j = 0;j < height;j++){
	  int num = mandelVal(i, j);
	  image << 0 << ' ' << 0 << ' ' << num << "\n";
	}
      }
    }
    image.close();
  }else{
    cout << "Could not open the file" << endl;
  }

  
  return 0;
}


int mandelVal(int x, int y){
  complex<float> point((float)x/width-1.5,(float)y/height-0.5);
  //divide by image dimensions to get values smaller than 1
  //then apply a transition.
  complex<float> z(0,0);
  unsigned int nb_iter = 0;
  while((abs(z) < 2) && (nb_iter <= 34)){
    z = z * z + point;
    nb_iter++;
  }
  if(nb_iter < 34)
    return (255*33)/nb_iter;
  else
    return 0;
  
}
