#include "LevelLoader.h"

vector<shared_ptr<GameAsset>> LevelLoader::getLevel(int i) //Loads new level file
{	
	level0Str.clear();
	string line;
	string file = "src/levels/" + to_string(i) + ".txt";
	ifstream myfile (file);
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
		  level0Str.push_back(line);
		}
	    	myfile.close();
    	}

	buildLevel();

	return level0;
}

void LevelLoader::buildLevel()	//Loads new scenes file
{
	level0.clear();

	cout << level0.size() << endl;

	string verShade = "shaders/hello-gl.v.glsl";
	string redFShad = "shaders/redF.glsl";
	string bluFShad = "shaders/bluF.glsl";
	string fraShade = "shaders/hello-gl.f.glsl";
	vector<Global::Force> forces; 

	for(int i = 0; i < level0Str.size(); i++)
	{
		for(int j = 0; j < level0Str.at(i).length(); j++)
		{
			forces.clear();
			switch(level0Str.at(i).at(j))
			{
				case 'F':
				{
					level0.push_back(shared_ptr<CuboidAsset> (new CuboidAsset(j, -1, i, 1, 1, 1, verShade, bluFShad)));
					forces.push_back(Global::COLS);
					forces.push_back(Global::STAT);
					level0.back()->setGAP(shared_ptr<GAPlus>(new GAPlus('F', forces)));
					break;
				}
				case 'W':
				{
					level0.push_back(shared_ptr<CuboidAsset> (new CuboidAsset(j, 0, i, 1, 2, 1)));
					forces.push_back(Global::COLS);
					forces.push_back(Global::STAT);
					level0.back()->setGAP(shared_ptr<GAPlus>(new GAPlus('W', forces)));
					break;
				}
				case 'P':
				{
					level0.push_back(shared_ptr<CuboidAsset> (new CuboidAsset(j, -1, i, 1, 1, 1, verShade, bluFShad)));		
					forces.push_back(Global::COLS);
					forces.push_back(Global::STAT);
					level0.back()->setGAP(shared_ptr<GAPlus>(new GAPlus('F', forces)));
					forces.clear();
					level0.push_back(shared_ptr<CuboidAsset> (new CuboidAsset(j, 0, i, 0.1, 0.1, 0.1)));
					forces.push_back(Global::COLS);
					forces.push_back(Global::DYNA);
					level0.back()->setGAP(shared_ptr<GAPlus>(new GAPlus('P', forces)));
					Vector4 thTemCam = Camera::getInstance().getCameraM().getCol3();
					thTemCam.setX(j);
					thTemCam.setZ(i);
					Camera::getInstance().getCameraM().setCol3(thTemCam);
					
					break;
				}
				case 'B':
				{
					level0.push_back(shared_ptr<CuboidAsset> (new CuboidAsset(j, -1, i, 1, 1, 1, verShade, bluFShad)));		
					forces.push_back(Global::COLS);
					forces.push_back(Global::STAT);
					level0.back()->setGAP(shared_ptr<GAPlus>(new GAPlus('F', forces)));
					forces.clear();
					level0.push_back(shared_ptr<CuboidAsset> (new CuboidAsset(j, 0, i, 0.75, 0.75, 0.75, verShade, redFShad)));
					forces.push_back(Global::COLS);
					forces.push_back(Global::DYNA);
					level0.back()->setGAP(shared_ptr<GAPlus>(new GAPlus('B', forces)));
					break;
				}
			}
		}
	}
	//cout << level0.size() << endl;
	
}

