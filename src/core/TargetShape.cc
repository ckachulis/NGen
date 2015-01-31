#include "TargetShape.h"
#include <iostream>
#include <stdlib.h>
TargetShape::TargetShape()
{
  density=-1;
  for(int i=0;i<3;i++)
    {
      pos0[i]=0;

    }
  vX=new TVector3(1,0,0);
  vY=new TVector3(0,1,0);
  vZ=new TVector3(0,0,1);

  vXi=new TVector3(1,0,0);
  vYi=new TVector3(0,1,0);
  vZi=new TVector3(0,0,1);

  vM=new TMatrixD(3,3);
  vMi=NULL;
}

TargetShape::~TargetShape()
{

  delete vX;
  delete vY;
  delete vZ;
 
  delete vXi;
  delete vYi;
  delete vZi;
 
  delete vM;

  if(vMi) delete vMi;

}


void TargetShape::TransformCoordsMineToGen(TVector3 * v)
{

  double x=v->Dot(*vX);
  double y=v->Dot(*vY);
  double z=v->Dot(*vZ);
  
  v->SetXYZ(x+pos0[0],y+pos0[1],z+pos0[2]);

}

void TargetShape::TransformCoordsGenToMine(TVector3 * v)
{
  v->SetXYZ(v->X()-pos0[0],v->Y()-pos0[1],v->Z()-pos0[2]);

  
  double x=v->Dot(*vXi);
  double y=v->Dot(*vYi);
  double z=v->Dot(*vZi);

  v->SetXYZ(x,y,z);



}


void TargetShape::UpdatevM()
{
  if(vX->Dot(*vY)!=0 or vX->Dot(*vZ)!=0 or vY->Dot(*vZ)!=0)
    {
      std::cout<<"TargetShape Error: coordinate system not orthogonal"<<std::endl;
      exit(1);

    }

  vM[0][0]=vX->X();
  vM[0][1]=vX->Y();
  vM[0][2]=vX->Z();

  vM[1][0]=vY->X();
  vM[1][1]=vY->Y();
  vM[1][2]=vY->Z();

  vM[2][0]=vZ->X();
  vM[2][1]=vZ->Y();
  vM[2][2]=vZ->Z();

  if(vMi) delete vMi;
  vMi=new TMatrixD(*vM);
  vMi->Invert();

  vXi->SetXYZ(TMatrixDRow(*vMi,0)(0),TMatrixDRow(*vMi,0)(1),TMatrixDRow(*vMi,0)(2));
  vYi->SetXYZ(TMatrixDRow(*vMi,1)(0),TMatrixDRow(*vMi,1)(1),TMatrixDRow(*vMi,1)(2));
  vZi->SetXYZ(TMatrixDRow(*vMi,2)(0),TMatrixDRow(*vMi,2)(1),TMatrixDRow(*vMi,2)(2));
}
