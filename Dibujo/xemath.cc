#include <stdio.h>
#include <math.h>
//En el .h poner:
//#ifndef __LIBRERIA__H__
//#define __LIBRERIA__H__

namespace xemath{
  struct Vector2{
    float x,y;
  };
  struct Vector3{
    float x,y,z;
  };
  struct Vector4{
    float x,y,z,w;
  };
  struct Mat2{
    float m[4];
  };
   float ToRadianes(float valor){
    return valor*(3.1415f/180.0f);
  }


  //Sumar dos vectores2
  Vector2 SumVec2(Vector2 v1, Vector2 v2){
    Vector2 aux = {v1.x+v2.x,v1.y+v2.y};
    return aux;
  }
  //Restar dos vectores2
  Vector2 RestVec2(Vector2 v1, Vector2 v2){
    Vector2 aux = {v1.x-v2.x,v1.y-v2.y};
    return aux;
  }

  //Sumar dos vectores3
  Vector3 SumVec3(Vector3 vec1, Vector3 vec2){
    Vector3 aux={
      (vec1.x+vec2.x),
      (vec1.y+vec2.y),
      (vec1.z+vec2.z)
    };
    return aux;
  }

  //Sumar dos vectores4
  Vector4 SumVec4(Vector4 vec1, Vector4 vec2){
    Vector4 aux={
      (vec1.x+vec2.x),
      (vec1.y+vec2.y),
      (vec1.z+vec2.z),
      (vec1.w+vec2.w)
    };
    return aux;
  }

  //Sumar dos Mat2
  Mat2 SumMat2(Mat2 mat1, Mat2 mat2){
    Mat2 aux;
    aux.m[0] = mat1.m[0]+mat2.m[0];
    aux.m[1] = mat1.m[1]+mat2.m[1];
    aux.m[2] = mat1.m[2]+mat2.m[2];
    aux.m[3] = mat1.m[3]+mat2.m[3];
    return aux;
  }

  //Multiplicar Mat2 * Vector2
  Vector2 Vec2MultMatVec2(Mat2 mat, Vector2 vec){
    Vector2 aux={
      mat.m[0] * vec.x + mat.m[2] * vec.y,
      mat.m[1] * vec.x + mat.m[3] * vec.y
    };
    return aux;
  }

  //Multiplicar Vec2 * Vec2
  Vector2 MultVec2(Vector2 vec1, Vector2 vec2){
    Vector2 aux = {vec1.x * vec2.x, vec1.y * vec2.y};
    return aux;
  }

    //Si lo divido entre su modulo me tiene que dar 1
    //NO FUNCIONA
  bool CheckNormalizedVec2(Vector2 vec){
    bool normalizado = true;
    // v = raiz cuadrada de x^2+y^2
    float modulo = sqrt(vec.x*vec.x) + sqrt(vec.y * vec.y);
    if(modulo != 1) normalizado = false;

    return normalizado;
  }

  //Normalizar Vector2
  Vector2 Vec2Normalize(Vector2 vec){
    float hipotenusa=(vec.x*vec.x)+(vec.y*vec.y);
    hipotenusa = sqrt(hipotenusa);
    Vector2 aux = {
      vec.x/hipotenusa,
      vec.y/hipotenusa
    };
    return aux;
  }

  float Vec2Modulo(Vector2 vec){
    //Raiz de x^2 + y^2
    float aux = sqrt(((vec.x*vec.x)+(vec.y*vec.y)));
    return aux;
  }
  //Normalizar Vector3
  Vector3 Vec3Normalize(Vector3 vec){
    float hipotenusa=(vec.x*vec.x)+(vec.y*vec.y)+(vec.z*vec.z);
    hipotenusa = sqrt(hipotenusa);
    Vector3 aux = {
      vec.x/hipotenusa,
      vec.y/hipotenusa,
      vec.z/hipotenusa
    };
    return aux;
  }



  Vector2 RotateVec2(Vector2 vec, float angle){
    angle = ToRadianes(angle);
    Vector2 aux;
    aux.x = (vec.x * cos(angle)) - (vec.y * sin(angle));
    aux.y = (vec.x * sin(angle)) + (vec.y * cos(angle));
    return aux;
  }

 



  //Debug Vector2
  void DebugVector2(Vector2 vector){
    printf("X:[%f] Y:[%f]\n",vector.x,vector.y);
  }
  //Debug Vector3
  void DebugVector3(Vector3 vector){
    printf("X:[%f] Y:[%f] Z:[%f]\n",vector.x,vector.y,vector.z);
  }
  //Debug Vector4
  void DebugVector4(Vector4 vector){
    printf("X:[%f] Y:[%f] Z:[%f] W:[%f]\n",vector.x,vector.y,vector.z,vector.w);
  }
  //Debug Mat2
  void DebugMat2(Mat2 mat){
    printf("0:[%f] 1:[%f] 2:[%f] 3:[%f]\n",mat.m[0],mat.m[1],mat.m[2],mat.m[3]);
  }

  Vector2 ScalateVec2(Vector2 vec, float size){
    // float modulo = sqrt((vec.x * vec.x) + (vec.y * vec.y));
    // Vector2 aux = {(vec.x/modulo) * size, (vec.y/modulo) * size};
    // return aux;
    // printf("Original:\n");
    // DebugVector2(vec);
    
    Vector2 aux = Vec2Normalize(vec);
    aux.x = aux.x * size;
    aux.y = aux.y * size;
    return aux;
  }


}
