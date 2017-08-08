#include<iostream>
#include<cmath>
#define INF 2147483647
using namespace std;
int i=0,j=0,k=0,m=0,n=0;
class Logic
{
public:
	int value[1024];//该蕴含项代表的数值
	int bitnumber;//该蕴含项的比特数目
	int sum;//该蕴含项中1的个数
	char bit[10];//蕴含项中的每一位，无意义项为‘2’
	bool nature;//是否为本质本源蕴含项
	bool change;//是否与别的蕴含项合并过
	bool print;//是否输出
	Logic();//默认构造函数
	Logic(int l_value,int l_bitnumber);//构造函数
};
Logic::Logic()
{
	int ii=0;
	bitnumber=0;
	for(ii=0;ii<1024;ii++) value[ii]=INF;
	for(ii=0;ii<10;ii++) bit[ii]='2';
	nature=false;
	change=false;
	print=false;
	sum=0;
}
Logic::Logic(int l_value,int l_bitnumber)
{
	int ii=0;
	for(ii=0;ii<1024;ii++) value[ii]=INF;
	value[0]=l_value;
	bitnumber=l_bitnumber;
	sum=0;
	int temp=l_value;
	for(ii=0;ii<10;ii++)
		bit[ii]='2';
	for(ii=0,temp=value[0];ii<bitnumber;ii++)
	{
		bit[ii]=(int)(temp/pow(2.0,(double)(bitnumber-1-ii)))+48;
		temp=temp-(bit[ii]-48)*(int)pow(2.0,(double)(bitnumber-1-ii));
	}
	for(ii=0;bit[ii]!='2';ii++)
		sum=sum+bit[ii]-48;
	nature=false;
	change=false;
	print=false;
}
int main()
{
	int nq=0;
	cin>>nq;//重复次数
	int *nm=NULL;nm=new int[nq+1];//第i次最小项个数
	int *nd=NULL;nd=new int[nq+1];//第i次无关项个数
	int **min=NULL;min=new int*[nq+1];//第i次最小项数组
	int **relative=NULL;relative=new int*[nq+1];//第i次无关项数组
	int *max=NULL;max=new int[nq+1];int *bit=NULL;bit=new int[nq+1];//第i次变量数
	for(i=0;i<nq;i++)
	{
		cin>>nm[i]>>nd[i];
		min[i]=new int[nm[i]+1];
		relative[i]=new int[nd[i]+1];
		for(j=0;j<nm[i];j++)
		{
			cin>>min[i][j];
			if(min[i][j]>max[i]) max[i]=min[i][j];
		}
		for(j=0;j<nd[i];j++)
		{
			cin>>relative[i][j];
			if(relative[i][j]>max[i]) max[i]=relative[i][j];
		}
		bit[i]=(int)(log((double)max[i])/log(2.0))+1;//计算第i次变量数
	}
	cout<<"陈誉博 2014011058"<<endl;
	for(i=0;i<nq;i++)
	{
		if((nm[i]==0&&nd[i]==0)||(nm[i]==0&&nd[i]==1))
		{
			cout<<'0'<<endl;
			continue;
		}
		else if(nm[i]==1&&min[i][0]==0&&nd[i]==0)
		{
			cout<<'1'<<endl;
			continue;
		}
		Logic *size1=NULL;size1=new Logic[nm[i]+nd[i]+1];
		int *num=NULL;num=new int[bit[i]+1+1];int sum=0;//第i项表示和为i的蕴含项的数目
		int naturelogic=0;//本质本源蕴含项的数目
		for(j=0;j<bit[i]+1+1;j++)
			num[j]=0;
		for(j=0;j<nm[i]+nd[i]+1;j++)
		{
			if(j<nm[i])
				size1[j]=Logic(min[i][j],bit[i]);//初始化蕴含项
			else if(j>=nm[i])
				size1[j]=Logic(relative[i][j-nm[i]],bit[i]);
			num[size1[j].sum]++;
		}
		Logic **logic=NULL;logic=new Logic*[1+bit[i]+1];//按照1的个数划分的蕴含项数组，第i个数组表示有i个1的蕴含项
		int ii=0;
		for(j=0;j<1+bit[i]+1;j++)//第j个蕴含项数组
		{
			ii=0;
			if(num[j]>0)
			{
				logic[j]=new Logic[num[j]+1];
				for(k=0;k<nm[i]+nd[i];k++)
					if(size1[k].sum==j)
					{
						logic[j][ii]=Logic(size1[k].value[0],size1[k].bitnumber);
						ii++;
					}
			}
			else logic[j]=new Logic[1];
		}
		int dif=0;int size2number=0;
		int a=nm[i]+nd[i];//计算所有size1的蕴含项的个数
		Logic **size=NULL;size=new Logic*[10+1];//第i个数组表示含有2^i+1个最小项的蕴含项
		size[0]=new Logic[a*(a-1)/2+1];
		for(j=0;j<bit[i];j++)//第j组
		{
			if(num[j]==0) continue;
			for(k=0;k<num[j];k++)//第j组第k个蕴含项
			{
				bool if_change=false;int ii=0;
				if(num[j+1]==0&&logic[j][k].change==false) {logic[j][k].nature=true;naturelogic++;break;}
				for(m=0;m<num[j+1];m++)//第j+1组第m个蕴含项
				{
					dif=0;
					for(n=0;n<bit[i];n++)//两个蕴含项的第n比特
						if(logic[j][k].bit[n]!=logic[j+1][m].bit[n])
							dif++;
					if(dif==1)
					{
						if_change=true;
						for(n=0;n<bit[i];n++)
							if(logic[j][k].bit[n]!=logic[j+1][m].bit[n])
								break;
						size[0][size2number]=Logic(logic[j][k].value[0],bit[i]);
						size[0][size2number].value[1]=logic[j+1][m].value[0];
						size[0][size2number].bit[n]='-';
						logic[j][k].change=true;
						logic[j+1][m].change=true;
						size2number++;
					}
				}
				if(if_change==false&&logic[j][k].change==false)
				{
					logic[j][k].nature=true;
					naturelogic++;
				}
			}
		}
		for(j=0;j<num[bit[i]];j++)
		{
			if(logic[bit[i]][j].change==false)
			{
				logic[bit[i]][j].nature=true;
				naturelogic++;
			}
		}
		if(size[0][0].value[0]!=INF&&size[0][0].value[0]>=0)
		{
			for(j=1;j<10;j++)//含有2^j+1个最小项的蕴含项
			{
				int number=0;int sizenumber=0;
				for(number=0;size[j-1][number].value[0]!=INF&&size[j-1][number].value[0]>=0;number++) ;//前一列的蕴含项的个数，用来确定该列的上限
				size[j]=new Logic[number*(number-1)/2+1];
				for(k=0;k<number;k++)//第k个蕴含项
				{
					bool if_change=false;
					for(m=0;m<number;m++)//与第m个蕴含项比较
					{
						int dif=0;
						for(n=0;n<bit[i];n++)//两个蕴含项的第n个比特
						{
							if(size[j-1][k].bit[n]!=size[j-1][m].bit[n])
								dif++;
						}
						if(dif==1)
						{
							if_change=true;
							Logic temp;
							temp=Logic(size[j-1][k].value[0],bit[i]);
							for(n=0;n<j+1;n++)
							{
								temp.value[n]=size[j-1][k].value[n];
								temp.value[n+j+1]=size[j-1][m].value[n];
							}
							for(n=0;n<bit[i];n++)
								temp.bit[n]=size[j-1][k].bit[n];
							for(n=0;n<bit[i];n++)
								if(size[j-1][k].bit[n]!=size[j-1][m].bit[n])
									break;
							temp.bit[n]='-';
							size[j-1][k].change=true;
							size[j-1][m].change=true;
							//防止重复
							int repeat=0;
							for(n=0;size[j][n].value[0]!=INF&&size[j][n].value[0]>=0;n++)//搜索size[j]中已有的蕴含项
							{
								repeat=0;
								for(int ii=0;ii<bit[i];ii++)
								{
									if(temp.bit[ii]==size[j][n].bit[ii])
										repeat++;
								}
								if(repeat==bit[i]) break; 
							}
							if(repeat!=bit[i])
							{
								size[j][sizenumber]=temp;
								sizenumber++;
							}
						}
					}
					if(if_change==false&&size[j-1][k].change==false)
					{
						size[j-1][k].nature=true;
						naturelogic++;
					}
				}
				if(size[0][0].value[0]==INF||size[j][0].value[0]<0)
					break;
			}
		}
		//寻找本原蕴含项（蕴含项合并）已经完成，还差寻找本质本原蕴含项
		Logic *nature=NULL;nature=new Logic[naturelogic+1];
		Logic *print=NULL;print=new Logic[naturelogic+1];
		int naturenumber=0;
		for(j=0;j<bit[i]+1;j++)//logic中的第j组蕴含项
		{
			for(k=0;k<num[j];k++)//logic中的第j组的第k个蕴含项
			{
				if(logic[j][k].nature==true)
				{
					nature[naturenumber]=logic[j][k];
					naturenumber++;
				}
			}
		}
		for(j=0;size[j][0].value[0]!=INF&&size[j][0].value[0]>=0;j++)//size中的第j组蕴含项
		{
			for(k=0;size[j][k].value[0]!=INF&&size[j][k].value[0]>=0;k++)//size中的第j组的第k个蕴含项
			{
				if(size[j][k].nature==true)
				{
					nature[naturenumber]=size[j][k];
					naturenumber++;
				}
			}
		}
		int **graph=new int*[naturelogic];
		for(int ii=0;ii<naturelogic;ii++)
			graph[ii]=new int[nm[i]];
		for(int ii=0;ii<naturelogic;ii++)
			for(int jj=0;jj<nm[i];jj++)
				graph[ii][jj]=2;
		for(int ii=0;ii<naturelogic;ii++)
			for(int jj=0;jj<nm[i];jj++)
				graph[ii][min[i][jj]]=0;
		for(int ii=0;ii<naturelogic;ii++)//第ii个nature蕴含项
		{
			for(int jj=0;nature[ii].value[jj]!=INF&&nature[ii].value[jj]>=0;jj++)//该蕴含项的第jj个value
			{
				graph[ii][nature[ii].value[jj]]=1;
			}
		}
		for(int jj=0;jj<nm[i];jj++)
		{
			int number=0;
			for(int ii=0;ii<naturelogic;ii++)
			{
				if(graph[ii][min[i][jj]]==1)
					number++;
			}
			if(number==1)
			{
				int ii=0;
				while(graph[ii][min[i][jj]]!=1) ii++;
				nature[ii].print=true;
			}
		}
		//
		int printnumber=0;
		for(int ii=0;ii<naturelogic;ii++)
			if(nature[ii].print==true)
			{
				print[printnumber]=nature[ii];
				nature[ii]=Logic();
				printnumber++;
			}
		for(int ii=0;ii<printnumber;ii++)//print数组的第ii个
		{
			bool if_exchange=false;
			for(int jj=ii+1;jj<printnumber;jj++)//print数组的第jj个
			{
				for(int kk=0;kk<bit[i];kk++)//每个print蕴含项的第kk比特
				{
					if(print[ii].bit[kk]==print[jj].bit[kk]) continue;
					else if(print[ii].bit[kk]>print[jj].bit[kk]) {if_exchange=true;break;}
					else 
					{
						Logic temp;
						temp=print[ii];
						print[ii]=print[jj];
						print[jj]=temp;
						if_exchange=true;
						break;
					}
				}
				if(if_exchange) continue;
			}
			if(if_exchange) continue;
		}
		bool out=false;
		for(int ii=0;ii<printnumber;ii++)//第ii个print蕴含项
		{
			if(print[ii].value[0]<0) continue;
			for(int jj=0;jj<bit[i];jj++)//该蕴含项的第jj比特
			{
				if(print[ii].bit[jj]=='1') cout<<char(16+print[ii].bit[jj]+jj);
				else if(print[ii].bit[jj]=='0') cout<<char(16+print[ii].bit[jj]+1+jj)<<"'";
				else continue;
			}
			if(ii<printnumber-1) cout<<'+';
			out=true;
		}
		//本质本原蕴含项已经全部输出，还差非本质本源蕴含项
		Logic *unature=new Logic[1];unature=new Logic[naturelogic+1];int unaturenumber=0;//非本质本源蕴含项
		for(int ii=0;ii<naturelogic;ii++)
		{
			if(nature[ii].value[0]!=INF&&nature[ii].value[0]>=0) 	
			{
				unature[unaturenumber]=nature[ii];
				unaturenumber++;
			}
		}
		int *littlegraph=NULL;littlegraph=new int[max[i]];//2代表不是最小项，0代表未被覆盖，1代表已被覆盖
		for(int ii=0;ii<=max[i];ii++)
			littlegraph[ii]=2;
		for(int ii=0;ii<nm[i];ii++)
		{
			littlegraph[min[i][ii]]=0;
		}
		int covernumber=0;//被本质本原蕴含项覆盖的最小项的个数
		for(int ii=0;ii<printnumber;ii++)//print中的第ii个本质本源蕴含项
		{
			for(int jj=0;print[ii].value[jj]!=INF&&print[ii].value[jj]>=0;jj++)//每个本质本源蕴含项的第jj个最小项
			{
				if(littlegraph[print[ii].value[jj]]==0)
					covernumber++;
				littlegraph[print[ii].value[jj]]=1;
			}
		}
		printnumber=0;
		while(covernumber<nm[i])
		{
			int a=0;int maxcover=0;
			Logic tempnature;
			for(int ii=0;ii<nm[i];ii++)
			{
				if(littlegraph[min[i][ii]]==0)
				{
					a=min[i][ii];
					break;
				}
			}
			for(int ii=0;ii<unaturenumber;ii++)//第ii个非本质本源蕴含项
			{
				for(int jj=0;unature[ii].value[jj]!=INF&&unature[ii].value[jj]>=0;jj++)
				{
					if(unature[ii].value[jj]==a)
					{
						int temp=0;
						while(unature[ii].value[jj]!=INF&&unature[ii].value[jj]>=0)
						{
							if(littlegraph[unature[ii].value[jj]]==0)
								temp++;
							jj++;
						}
						if(temp>=maxcover) 
						{
							maxcover=temp;
							tempnature=unature[ii];
						}
					}
				}
			}
			for(int ii=0;tempnature.value[ii]!=INF&&tempnature.value[ii]>=0;ii++)
			{
				if(littlegraph[tempnature.value[ii]]==0)
					covernumber++;
				littlegraph[tempnature.value[ii]]=1;
			}
			print[printnumber]=tempnature;
			printnumber++;
		}
		if(printnumber>0){
		for(int ii=0;ii<printnumber;ii++)//print数组的第ii个
		{
			bool if_exchange=false;
			for(int jj=ii+1;jj<printnumber;jj++)//print数组的第jj个
			{
				for(int kk=0;kk<bit[i];kk++)//每个print蕴含项的第kk比特
				{
					if(print[ii].bit[kk]==print[jj].bit[kk]) continue;
					else if(print[ii].bit[kk]>print[jj].bit[kk]) {if_exchange=true;break;}
					else 
					{
						Logic temp;
						temp=print[ii];
						print[ii]=print[jj];
						print[jj]=temp;
						if_exchange=true;
						break;
					}
				}
				if(if_exchange) continue;
			}
			if(if_exchange) continue;
		}
		for(int ii=0;ii<printnumber;ii++)//第ii个print蕴含项
		{
			cout<<'+';if(out==false) {cout<<'\b';out=true;}
			for(int jj=0;jj<bit[i];jj++)//该蕴含项的第jj比特
			{
				if(print[ii].bit[jj]=='1') cout<<char(16+print[ii].bit[jj]+jj);
				else if(print[ii].bit[jj]=='0') cout<<char(16+print[ii].bit[jj]+1+jj)<<"'";
				else continue;
			}
		}
		}
		cout<<endl;
	}
	return 0;
}
