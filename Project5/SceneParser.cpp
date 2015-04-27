
#include <string>
#include "Scene.h"
#include "SceneParser.h"
#include "AmbientLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "sphere.h"
#include "Plane.h"
#include "Material.h"


#include <sstream>
#include <fstream>
#include <vector>

using namespace std;


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems,bool ignoreEmpty) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
		if(ignoreEmpty&&item.empty())
			continue;
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {

	return split(s,delim,elems,false);
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


bool ParseScene(vector<string> params,vector<string> extraParams,Scene& scene){
	if(params.size()<12)
		return false;

	Vector3f ScreenCenter(stof(params[0]),stof(params[1]),stof(params[2]));
	Vector3f CameraUpVec(stof(params[3]),stof(params[4]),stof(params[5]));
	float width = stof(params[6]);
	float xRes = stof(params[7]);
	float yRes = stof(params[8]);
	Vector3f AmbientLightI(stof(params[9]),stof(params[10]),stof(params[11]));

	Vector3f CameraCenter(0,0,0);
	Vector3f CameraForwardVec(ScreenCenter-CameraCenter);
	float DistanceFromCamera = CameraForwardVec.getLength();
	CameraForwardVec.normalize();
	Camera * camera = new Camera(CameraCenter, CameraUpVec, CameraForwardVec, ViewPlane(xRes, yRes, DistanceFromCamera), width); // need to check
	scene.camera = camera;
	scene.ambientLight =new AmbientLight(AmbientLightI);

}

bool ParseSpher(vector<string> params,vector<string> extraParams,Scene& scene){
	if(params.size()<14){
		return false;
	}
	Vector3f SpherPosition(stof(params[0]),stof(params[1]),stof(params[2]));
	float radios = stof(params[3]);
	Vector3f MetParamKa(stof(params[4]),stof(params[5]),stof(params[6]));
	Vector3f MetParamKd(stof(params[7]),stof(params[8]),stof(params[9]));
	Vector3f MetParamKs(stof(params[10]),stof(params[11]),stof(params[12]));
	float SpherShininess = stof(params[13]);
	
	Vector3f Reflection(0,0,0);
	if(extraParams.size()>0&&extraParams[0].compare("M") ==0){
		Vector3f ReflectionT(1,1,1);
		Reflection = ReflectionT;
	}

	Material mat(MetParamKa,MetParamKd,MetParamKs,Reflection,SpherShininess);

	scene.objects.push_back(new Sphere(SpherPosition,radios,mat));
	
}

bool ParseLight(vector<string> params,vector<string> extraParams,Scene& scene){
	if(params.size()<6)
		return false;
	Vector3f LightDirection(stof(params[0]),stof(params[1]),stof(params[2]));
	Vector3f LightIntensity(stof(params[3]),stof(params[4]),stof(params[5]));
	if(params.size()>=10) // spotLight
	{
		Vector3f LightPosition(stof(params[6]),stof(params[7]),stof(params[8]));
		float LightAngel = stof(params[9]);
		scene.lightSources.push_back(new SpotLight(LightPosition,LightDirection,LightIntensity,LightAngel));
	}
	else{  // Directional Light
		scene.lightSources.push_back(new DirectionalLight(LightDirection,LightIntensity));
	}
}

bool ParsePlane(vector<string> params,vector<string> extraParams,Scene& scene){
	if(params.size()<18){
		return false;
	}
	Vector3f PlaneNormal(stof(params[0]),stof(params[1]),stof(params[2]));
	Vector3f PlanePosition(stof(params[3]),stof(params[4]),stof(params[5]));
	float width = stof(params[6]);
	float length = stof(params[7]);
	Vector3f MetParamKa(stof(params[8]),stof(params[9]),stof(params[10]));
	Vector3f MetParamKd(stof(params[11]),stof(params[12]),stof(params[13]));
	Vector3f MetParamKs(stof(params[14]),stof(params[15]),stof(params[16]));
	float PlaneShininess = stof(params[17]);
	
	Vector3f Reflection(0,0,0);
	if(extraParams.size()>0&&extraParams[0].compare("M") ==0){
		Vector3f ReflectionT(1,1,1);
		Reflection = ReflectionT;
	}

	Material mat(MetParamKa,MetParamKd,MetParamKs,Reflection,PlaneShininess);
	scene.objects.push_back(new Plane(PlanePosition,PlaneNormal,width,length,mat));
}


void ParseScene(char* Filename,Scene & scene)
{
	std::string line;
	std::ifstream file;
	file.open("C:\\Users\\Yaniv\\Desktop\\scene.txt",ios::in);
		
	if (!file.is_open()){
		printf("error cannot open input file\n");
		return;
	}

	while (std::getline(file, line))
	{
		vector<string> vec;
		vector<string> params;
		vector<string> extraParams;
		split(line,' ',vec,true);
		if(vec.size()<2)
			continue;

		split(vec[1],',',params,true);
		for(int i=2;i<vec.size();i++)
			extraParams.push_back(vec[i]);

		if(vec[0].compare("scene")==0)
			ParseScene(params,extraParams,scene);
		else if(vec[0].compare("light")==0)
			ParseLight(params,extraParams,scene);
		else if(vec[0].compare("spher")==0) // need impl Reflection
			ParseSpher(params,extraParams,scene);
		else if(vec[0].compare("plane")==0) // need impl Reflection
			ParsePlane(params,extraParams,scene);
		else
			printf("Unknown Line Type");

	}
}
