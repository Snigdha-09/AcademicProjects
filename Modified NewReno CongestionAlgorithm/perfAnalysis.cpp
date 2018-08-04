#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>

using namespace std;

struct frame {
	int packetNo;
	int size;
	float time;
	int flag;
};

int main()
{
	struct frame frameObj;
	vector<frame> frameVector;
	vector<frame>::iterator itr;
	float tme,totalDelay=0.0,jitterTime=0.0, lastJitterTime = 0.0, currentJitterTime = 0.0;
	int packNo,r=0,d=0,totalSize=0;
	string element;
	ifstream infile;
  infile.open("out.tr");
	while(infile>>element)
	{
		if(element.compare("+") == 0)
		{
			infile>>element;
			frameObj.time = stof(element);
			infile>>element;
			if(element.compare("2") != 0)
			{
				for(int i=0;i<9;i++)
					infile>>element;
				continue;
			}
			for(int i=0;i<3;i++)
				infile>>element;
			frameObj.size = stoi(element);
			for(int i=0;i<6;i++)
				infile>>element;
			frameObj.packetNo = stoi(element);
			frameObj.flag = 0;
			frameVector.push_back(frameObj);
		}
		else if(element.compare("r") == 0)
		{
			infile>>element;
			tme = stof(element);
			infile>>element;
			infile>>element;
			if(element.compare("9") != 0)
			{
				for(int i=0;i<8;i++)
					infile>>element;
				continue;
			}
			r++;
			for(int i=0;i<8;i++)
				infile>>element;
			packNo = stoi(element);
			//cout<<packNo<<endl;
			for(itr = frameVector.begin();itr!=frameVector.end();itr++)
			{
				if((itr->packetNo) == packNo)
				{
					currentJitterTime = (itr->time) - lastJitterTime;
					jitterTime = jitterTime + currentJitterTime;
					lastJitterTime = currentJitterTime;
					(itr->time) = tme - (itr->time);
					totalDelay = totalDelay + (itr->time);
					totalSize = totalSize + (itr->size);
					(itr->flag) = 1;
				}
			}
		}
		else if(element.compare("-") == 0)
		{
			for(int i=0;i<11;i++)
				infile>>element;
		}
		else if(element.compare("d") == 0)
		{
			d++;
			for(int i=0;i<11;i++)
				infile>>element;
		}
	}
//	cout<<"Number of successful transmissions: "<<r<<endl;
//	cout<<"Number of packet dropped: "<<d<<endl;
	float throughput = (float)totalSize/tme;
	cout<<"Throughput: "<<throughput<<"Bps"<<endl;
	float g = (float)d/(d+r);
	cout<<"Packet Drop Ratio (PDR): "<<g<<endl;
	cout<<"Forwarding delay: "<<totalDelay/(float)r<<endl;
	cout<<"Jitter delay: "<<jitterTime/(float)r<<endl;
  infile.close();
	return 0;
}
