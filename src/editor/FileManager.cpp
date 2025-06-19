#include <iostream>
#include <vector>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <regex>
#include <string>
#include <cstdio>

#include "../instances/WorldInstance.cpp"

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

    WorldInstance loadWorldInstance(string filepath) // temp uses instanceManager will make new WorldInstance
    {
        WorldInstance worldInstance = WorldInstance();
        vector<string> lines = getElementsOfFile(filepath);
        for (string perLine : lines)
        {
            if(perLine.substr(0,4) == "name"){
                worldInstance.worldName = perLine.substr(4,perLine.length()-1);
            }
            if (perLine.find("bsinst") != string::npos)
            {
                if (perLine.find("trainst") != string::npos)
                {
                    {
                        size_t posStart = perLine.find("Position:(");
                        size_t posEnd = perLine.find(")", posStart);
                        std::string posStr = perLine.substr(posStart + 10, posEnd - (posStart + 10));
                        float px, py, pz;
                        sscanf(posStr.c_str(), "%f,%f,%f", &px, &py, &pz);

                        size_t rotStart = perLine.find("Rotation:(");
                        size_t rotEnd = perLine.find(")", posStart);
                        std::string rotStr = perLine.substr(rotStart + 10, rotEnd - (rotStart + 10));
                        float rx, ry, rz;
                        sscanf(rotStr.c_str(), "%f,%f,%f", &rx, &ry, &rz);
                        if (perLine.find("meshinst") != string::npos){
                            if (perLine.find("cubemeshinst") != string::npos){
                                size_t dimStart = perLine.find("Dimentions:(");
                                size_t dimEnd = perLine.find(")", dimStart);
                                std::string dimStr = perLine.substr(dimStart + 12, dimEnd - (dimStart + 12));
                                float dx, dy, dz;
                                sscanf(dimStr.c_str(), "%f,%f,%f", &dx, &dy, &dz);
                                        
                                worldInstance.instanceManager->makeCubeMesh({px, py, pz}, {rx, ry, rz}, {dx, dy, dz});
                            }
                            else if (perLine.find("planemeshinst") != string::npos){
                                size_t dimStart = perLine.find("Dimentions:(");
                                size_t dimEnd = perLine.find(")", dimStart);
                                std::string dimStr = perLine.substr(dimStart + 12, dimEnd - (dimStart + 12));
                                float dx, dy;
                                sscanf(dimStr.c_str(), "%f,%f", &dx, &dy);
                                        
                                worldInstance.instanceManager->makePlaneMesh({px, py, pz}, {rx, ry, rz}, {dx, dy});
                            }
                        }

                    }
                }

            }
        }
        return worldInstance;
    }
    int saveWorldInstance(WorldInstance *worldInstance)
    {
        std::ofstream worldSave("myWorld.vWorld");
        if (worldSave.is_open())
        {
            worldSave<<"name"<<worldInstance->worldName<<endl;
            for (auto &ins : worldInstance->instanceManager->instances)
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