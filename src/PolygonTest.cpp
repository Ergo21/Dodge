/*
	Axiom
	PolygonTest.cpp
	Author: Joseph Watts
	Created on: 29 Apr 2014
	Based on code provided by aidan
*/
#include "PolygonTest.h"

bool PolygonTest::getCollision(vector<ModelTriangle> tL1, vector<ModelTriangle> tL2)
{	

	for(int i = 0; i < tL1.size(); i++)
	{
		for(int j = 0; j < tL2.size(); j++)
		{
			if(locColsDet(tL1.at(i), tL2.at(j)))
			{
				cout << "Collision with triangle " <<endl;
				cout << "X: " << tL1.at(i).getPoi1().getX() << " Y:" << tL1.at(i).getPoi1().getY() << " Z:" << tL1.at(i).getPoi1().getZ() << endl;
				cout << "X: " << tL1.at(i).getPoi2().getX() << " Y:" << tL1.at(i).getPoi2().getY() << " Z:" << tL1.at(i).getPoi2().getZ() << endl;
				cout << "X: " << tL1.at(i).getPoi3().getX() << " Y:" << tL1.at(i).getPoi3().getY() << " Z:" << tL1.at(i).getPoi3().getZ() << endl;
				cout << endl;
				cout << "and triangle " <<endl;
				cout << "X: " << tL2.at(j).getPoi1().getX() << " Y:" << tL2.at(j).getPoi1().getY() << " Z:" << tL2.at(j).getPoi1().getZ() << endl;
				cout << "X: " << tL2.at(j).getPoi2().getX() << " Y:" << tL2.at(j).getPoi2().getY() << " Z:" << tL2.at(j).getPoi2().getZ() << endl;
				cout << "X: " << tL2.at(j).getPoi3().getX() << " Y:" << tL2.at(j).getPoi3().getY() << " Z:" << tL2.at(j).getPoi3().getZ() << endl;
				cout << endl;

				return true;
			}
		}
	}

	return false;
}

bool PolygonTest::locColsDet(ModelTriangle tr1, ModelTriangle tr2)
{
	Vector3 nIn;
	float nInM, u1I, v1I, u2I, v2I;

	nIn = cross(tr1.getNormal(), tr2.getNormal());
	nInM = length(nIn);

	u1I = dot(tr1.getU(), nIn)/nInM;
	v1I = dot(tr1.getV(), nIn)/nInM;
	u2I = dot(tr2.getU(), nIn)/nInM;
	v2I = dot(tr2.getV(), nIn)/nInM;
	
	if((u1I > u2I && u1I < v2I )&&(v1I > u2I && v1I < v2I )) //Should be ||, but fires false positives either way
	{
		cout << "u1I " << u1I << endl;
		cout << "v1I " << v1I << endl;
		cout << "u2I " << u2I << endl;
		cout << "v2I " << v2I << endl;
		cout<<endl;
		return true;
	}
	else
	{
		return false;
	}
}
