/* ***********************************************
Author        :guanjun
Created Time  :2017/4/11 22:37:25
File Name     :first.cpp
************************************************ */
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  

using namespace std;  
using namespace cv;  

struct point{
    double x;
    double y;
    double inty;
};

bool cmp(point a,point b){
    if(a.y==b.y){
        return a.x<b.x;
    }
    return a.y<b.y;
}
bool cmp1(point a,point b){
    return a.y<b.y;
}
vector<point>points;

struct cmp2{
    bool operator()(point a,point b){
        if(a.x==b.x) return a.y> b.y;
        return a.x>b.x;
    }
};
int main()  
{  
    ifstream in("/home/guan/Desktop/gg/temp_xyi.txt");
    if(!in){
        cout<<"open error"<<endl;
        exit(0);
    }
    else cout<<"open correct! "<<endl;
    double x,y,inty;
    double Minx,Miny,Maxx,Maxy,Mini,Maxi;
    Maxy=Maxx=Maxi=-1e9;
    Minx=Miny=Mini=1e9;
    point p;
    while(in>>x>>y>>inty){
        if(x>Maxx)Maxx=x;
        if(x<Minx)Minx=x;
        if(y>Maxy)Maxy=y;
        if(y<Miny)Miny=y;
        if(inty>Maxi)Maxi=inty;
        if(inty<Mini)Mini=inty;
        //cout<<x<<" "<<y<<" "<<inty<<endl;
        p.x=x;
        p.y=y;
        p.inty=inty;
        points.push_back(p);
    }
    sort(points.begin(),points.end(),cmp);
    cout<<Minx<<" "<<Maxx<<" "<<Miny<<" "<<Maxy<<" "<<Mini<<" "<<Maxi<<endl;
/*    
    double disx=fabs(Minx);
    double disy=fabs(Miny);
    for(int i=0;i<points.size();i++){
        points[i].x+=disx;
        points[i].y+=disy;
    }
    Minx+=disx;
    Miny+=disy;
    Maxx+=disx;
    Maxy+=disy;
*/
    int a,b,c,d;
    
    a=((int)(Miny/5))*5;
    
    c=((int)(Minx/5))*5;

    b=((int)(Maxy/5)+1)*5;

    d=((int)(Maxx/5)+1)*5;


    int w=0;

    int nump=0;
    for(int i=a;i<=b;i+=5){

        priority_queue<point,vector<point>,cmp2>q;

        for(int k=nump;k<points.size();k++){
            if(points[k].y<(double)i){
                q.push(points[k]);
                nump++;
            }
            else break;
        }
        if(q.empty())continue;
        int cnt=0;
        unsigned char image[100][100];


        point start,end;
        for(int j=c;j<=d;j+=5){
            cnt=0;
            memset(image,0,sizeof image);

            //start=q.top();

            while(!q.empty()){
                point tmp=q.top();
                if(tmp.x<(double)j){
                    q.pop();
                    cnt++;
                    //cout<<"double"<<(tmp.x-i+5)*100<<endl;
                    image[(int)((tmp.y-i+5)*20)][(int)((tmp.x-j+5)*20)]=tmp.inty;

                    //end=tmp;
                }
                else break;
            }
            //cout<<cnt<<endl;
            if(cnt>5){
                Mat srcImage = Mat(100,100,CV_8U,image);
                Mat dstImage;
                cvtColor(srcImage,dstImage, CV_GRAY2BGR);    
                ostringstream oss;
                oss<<"/home/guan/Desktop/done/"<<(0.05)<<"_map_"<<(j-5)<<"_"<<(i-5)<<"_"<<j<<"_"<<i<<".png";
                //oss<<"/home/guan/Desktop/done/"<<(0.05)<<"_map_"<<start.x<<"_"<<start.y<<"_"<<end.x<<"_"<<end.y<<".png";
                imwrite(oss.str(),dstImage);
                w++;
            }
        }
        
    }

    return 0;    
}  
