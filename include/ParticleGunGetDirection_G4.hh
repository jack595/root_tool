#pragma once
#include"TRandom.h"
#include<vector>
#include"TMath.h"
#include"G4ThreeVector.hh"
#include "Randomize.hh"
using namespace std;
vector<double> GenerateUniformDirection_PointSource(double phi_begin,
                                                  double phi_end,
                                                  double theta_begin,
                                                  double theta_end,
                                                    TRandom * direction_generator)
{
//    TRandom *direction_generator = new TRandom();
    double phi_return = direction_generator->Uniform(phi_begin,phi_end);
    double cos_theta=direction_generator->Uniform(TMath::Cos(theta_begin),TMath::Cos(theta_end));
    //because we need to generate uniform dirention ,which means uniform delta_Omega=sin(theta)*d_phi*d_theta
    //So we need to uniform cos(theta) not theta
    double theta_return=TMath::ACos(cos_theta);

//    cout<<"cos_theta = "<<cos_theta<<" theta_return = "<<theta_return
//       <<" phi_return = "<<phi_return <<endl;

    vector<double> v_direction={phi_return,theta_return};
    return v_direction;
}

G4ThreeVector PolarCoordinateToRectangularCoordinate(vector<double> v_direction_PhiAndTheta)
//v_direction_PhiAndTheta should be {phi,the}
{
    double phi=v_direction_PhiAndTheta[0];
    double theta=v_direction_PhiAndTheta[1];
    double x = TMath::Cos(phi)*TMath::Sin(theta);
    double y = TMath::Sin(phi)*TMath::Sin(theta);
    double z = TMath::Cos(theta);
    G4ThreeVector v_direction_xyz={x,y,z};
//    G4cout<<" v_direction : "<<v_direction_xyz<<G4endl;
    return v_direction_xyz;
}
