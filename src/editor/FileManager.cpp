#include <iostream>
#include <vector>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <regex>
#include <string>
#include <cstdio>

#include "../instanceManagers/InstanceManager.cpp"

using namespace std;
class FileManager
{
public:
    FileManager()
    {
    }

    vector<string> getElementsOfFile(string filepath)
    {
        vector<string> lines;
        std::ifstream inputFile(filepath.c_str());
        if (inputFile.is_open())
        {
            string line;
            while (inputFile >> line)
            {
                lines.push_back(line);
            }
            inputFile.close();
        }
        else
        {
            std::cerr << "Error opening input file." << std::endl;
        }

        return lines;
    }

    int loadWorldInstance(string filepath, InstanceManager *instanceManager) // temp uses instanceManager will make new WorldInstance
    {
        vector<string> lines = getElementsOfFile(filepath);
        for (string perLine : lines)
        {
            if (perLine.c_str()[0] == 'c')
            {
                float dx;
                float dy;
                float dz;
                char mfp;
                int cdv;
                int cdc;

                float px;
                float py;
                float pz;
                float rx;
                float ry;
                float rz;
                char n;

                sscanf(perLine.c_str(), "cCubeMeshInstance:Dimentions:(%f,%f,%f)MeshInstance:MaterialInstance:FilePath%sColliderInstance:DebugVisible%dDoesColliton:%dTransformInstance:Position:(%f,%f,%f)Rotation:(%f,%f,%f)Instance:Name:%s", &dx, &dy, &dz, &mfp, &cdv, &cdc, &px, &py, &pz, &rx, &ry, &rz ,&n);
                instanceManager->makeCubeMesh((Vector3){px,py,pz},(Vector3){rx,ry,rz},(Vector3){dx,dy,dz});
            }
        }
        return 0;
    }
    int saveWorldInstance(InstanceManager *instanceManager)
    {
        std::ofstream worldSave("myWorld.vWorld");
        if (worldSave.is_open())
        {

            for (auto &ins : instanceManager->instances)
            {

                worldSave << ins->getSaveString() << endl;
            }
        }
        else
        {
            std::cerr << "Error opening input file." << std::endl;
            return 1;
        }
        return 0;
    }
};

// example of a file for PlaneMeshInstance
// PlaneMeshInstance:Name:<namehere>Position:(0,0,0)Rotation(0,0,0)Dimentions(0,0)
//

/*
        std::ofstream worldSave("myWorld.txt");
        if(worldSave.is_open()){
            worldSave<<"test!!"<<endl;
            worldSave<<"pp poo poo"<<endl;


        }
        else
        {
            std::cerr << "Error opening input file." << std::endl;
        }
        std::ifstream inputFile("myWorld.txt");
        if (inputFile.is_open()) {
            string line;
            while (inputFile >> line) {
                lines.push_back(line);
            }
            inputFile.close();
        }else {
            std::cerr << "Error opening input file." << std::endl;
        }
    #include <cstdio>
    #include <iostream>
    #include <string>

    int main() {
      std::string data = "ID: 123, Value: 456.78";
      int id;
      double value;
      sscanf(data.c_str(), "ID: %d, Value: %lf", &id, &value);
      std::cout << "ID: " << id << ", Value: " << value << std::endl; // Output: ID: 123, Value: 456.78
    }
            */