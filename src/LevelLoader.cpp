#include "LevelLoader.h"

/*LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{
}*/

vector<shared_ptr<GameAsset>> LevelLoader::getLevel(int i) //Loads new level file
{	
	level0Str.clear();
	string line;
	string file = "levels/" + to_string(i) + ".txt";
	ifstream myfile (file);
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
		  cout << "Add line" <<endl;
		  level0Str.push_back(line);
		}
	    	myfile.close();
    	}

	buildLevel();
	cout << "Build Level" <<endl;

	return level0;
}

void LevelLoader::buildLevel()	//Loads new scenes file
{
	level0.clear();

	for(int i = 0; i < level0Str.size(); i++)
	{
		cout << level0Str.at(i) << endl;
		for(int j = 0; j < level0Str.at(i).length(); j++)
		{
			switch(level0Str.at(i).at(j))
			{
				case 'F':
				{
					level0.push_back(shared_ptr<CuboidAsset> (new CuboidAsset(j, -1, i, 1, 1, 1)));
cout << "Cuboid created"<< endl;
					break;
				}
				case 'W':
				{
					
					break;
				}
				case 'P':
				{
					break;
				}
				case 'G':
				{
					break;
				}
			}

		}
	}
	
}

