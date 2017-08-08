#include<iostream>
#include<stdio.h>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> cover;
class Logic
{
public:
	char bit[11];
	vector<short> value;
	bool flag;//flag=0代表未被合并
	friend bool sort_by_bit(const Logic *ref1,const Logic *ref2);
};
class Queue
{
public:
	vector<short int> source;
	short int itself;
};
short int compare1(short int &n,char *a,char *b)
{
	int count=0,k=0;
	for(int i=0;i<n;i++)
	{
		if(a[i]!=b[i])
		{
			count++;
			k=i;
		}
	}
	if(count==1)
		return k;
	else return -1;
}
bool sort_by_bit(const Logic* ref1,const Logic* ref2)
{
	int n=strlen(ref1->bit);
	for(int i=0;i<n;i++)
	{
		if(ref1->bit[i]>ref2->bit[i])
			return true;
		else if(ref1->bit[i]<ref2->bit[i])
			return false;
		else continue;
	}
	return false;
}
int main()
{
	short int i=0,j=0,k=0,m=0,n=0,ii=0,jj=0,kk=0;short int w=0;
	short int nq=0;
	scanf("%d",&nq);//cin>>nq;//重复次数
	short int *nm=new short int[nq+1];//第i次最小项个数
	short int *nd=new short int[nq+1];//第i次无关项个数
	short int **min=new short int*[nq+1];//第i次最小项数组
	short int **relative=new short int*[nq+1];//第i次无关项数组
	short int *max=new short int[nq+1];short int *bit=new short int[nq+1];//第i次变量数
	for(i=0;i<nq;i++)
	{
		scanf("%d%d",&nm[i],&nd[i]);//cin>>nm[i]>>nd[i];
		min[i]=new short int[nm[i]+1];
		relative[i]=new short int[nd[i]+1];
		for(j=0;j<nm[i];j++)
		{
			scanf("%d",&min[i][j]);//cin>>min[i][j];
			if(min[i][j]>max[i]) max[i]=min[i][j];
		}
		for(j=0;j<nd[i];j++)
		{
			scanf("%d",&relative[i][j]);//cin>>relative[i][j];
			if(relative[i][j]>max[i]) max[i]=relative[i][j];
		}
		bit[i]=(short int)(log((double)max[i])/log(2.0))+1;//计算第i次变量数
	}
	printf("陈誉博 2014011058\n");//cout<<"陈誉博 2014011058"<<endl;
	vector<Logic*>v[11];//输入的最小项和无关项
	vector<Logic*>size[10];//合并之后的蕴含项，第i个vector中存的是由i个最小项或者无关项合并而成的蕴含项
	vector<Logic*>nature;//存放未被合并的蕴含项或非本质本源蕴含项
	vector<Logic*>print1;//存放需要输出的本质本源蕴含项
	vector<Logic*>print2;//存放需要输出的非本质本源蕴含项
	vector<Queue>queue;Queue tempqueue;
	char temp[11];
	short int temp1=0,min_onenumber=0;
	bool repeat=false,change=false,cover=false;
	short int count=0;short int tempnature=0;
	short int graph[1025];//2为无用项，0为被覆盖，1为未被覆盖
	short int maxcover=0,count2=0;
	short int sum=0,tempsum=0;
	int tempsize1=0,tempsize2=0,tempsize3=0,tempsize4=0;
	for(i=0;i<nq;i++)
	{
		if(nm[i]==0)
		{
			cout<<'0'<<endl;
			continue;
		}
		else if(nm[i]+nd[i]==(int)pow(2.0,bit[i]))
		{
			cout<<'1'<<endl;
			continue;
		}
		else if(nm[i]==1&&min[i][0]==0&&nd[i]==0)
		{
			cout<<'1'<<endl;
			continue;
		}
		for(j=0;j<11;j++) v[j].clear();
		for(j=0;j<10;j++) size[j].clear();
		nature.clear();
		print1.clear();
		print2.clear();
		queue.clear();
		memset(temp,0,11*sizeof(char));
		memset(graph,0,(1025)*sizeof(short int));
		for(j=0;j<nm[i]+nd[i];j++)
		{
			min_onenumber=0;
			temp1=(j<nm[i])?min[i][j]:relative[i][j-nm[i]];
			for(k=bit[i]-1;k>=0;k--)
			{
				if(temp1%2==0)
					temp[k]='0';
				else 
				{
					temp[k]='1';
					min_onenumber++;
				}
				temp1=temp1/2;
			}
			temp[bit[i]]='\0';
			v[min_onenumber].push_back(new Logic);
			strcpy(v[min_onenumber].back()->bit,temp);
			v[min_onenumber].back()->value.push_back((j<nm[i])?min[i][j]:relative[i][j-nm[i]]);
			v[min_onenumber].back()->flag=false;
		}
		for(k=0;k<bit[i];k++)//合并的前一项所在的组
		{
			if(v[k].empty()||v[k+1].empty()) continue;
			tempsize1=v[k].size();
			for(m=0;m<tempsize1;m++)
			{
				tempsize2=v[k+1].size();
				for(n=0;n<tempsize2;n++)
				{
					repeat=false;
					if(compare1(bit[i],v[k][m]->bit,v[k+1][n]->bit)!=-1)
					{
						w=compare1(bit[i],v[k][m]->bit,v[k+1][n]->bit);
						strcpy(temp,v[k][m]->bit);
						temp[w]='-';
						v[k][m]->flag=v[k+1][n]->flag=true;
						size[0].push_back(new Logic);
						strcpy(size[0].back()->bit,temp);
						size[0].back()->flag=false;
						size[0].back()->value.push_back(v[k][m]->value[0]);
						size[0].back()->value.push_back(v[k+1][n]->value[0]);
					}
				}
			}
		}
		for(k=0;k<bit[i]+1;k++)
		{
			if(v[k].empty()) continue;
			tempsize1=v[k].size();
			for(m=0;m<tempsize1;m++)
			{
				if(v[k][m]->flag==false)
				{
					nature.push_back(new Logic);
					strcpy(nature.back()->bit,v[k][m]->bit);
					nature.back()->flag=false;
					for(n=0;n<v[k][m]->value.size();n++)
						nature.back()->value.push_back(v[k][m]->value[n]);
				}
			}
		}
		if(!size[0].empty())
		{
			for(j=1;j<11;j++)//合并次数
			{
				tempsize1=size[j-1].size();
				for(k=0;k<tempsize1;k++)//合并的前一项所在的组
				{
					tempsize2=size[j-1].size();
					for(m=k+1;m<tempsize2;m++)//合并的后一项
					{
						repeat=false;change=false;
						if(compare1(bit[i],size[j-1][k]->bit,size[j-1][m]->bit)!=-1)
						{
							change=true;
							w=compare1(bit[i],size[j-1][k]->bit,size[j-1][m]->bit);
							strcpy(temp,size[j-1][k]->bit);
							temp[w]='-';
							size[j-1][k]->flag=true;
							size[j-1][m]->flag=true;
							if(!size[j].empty())
							{
								tempsize3=size[j].size();
								for(n=0;n<tempsize3;n++)
									if(strcmp(temp,size[j][n]->bit)==0) repeat=true;
							}
							if(repeat==false)
							{
								size[j].push_back(new Logic);
								strcpy(size[j].back()->bit,temp);
								size[j].back()->flag=false;
								tempsize3=(short)pow(2.0,j);
								for(n=0;n<tempsize3;n++)
								{
									size[j].back()->value.push_back(size[j-1][k]->value[n]);
									size[j].back()->value.push_back(size[j-1][m]->value[n]);
								}
							}
						}
					}
					if(change==false&&size[j-1][k]->flag==false)
					{
						nature.push_back(new Logic);
						strcpy(nature.back()->bit,size[j-1][k]->bit);
						nature.back()->flag=false;
						tempsize2=(short)pow(2.0,j);
						for(m=0;m<tempsize2;m++)
							nature.back()->value.push_back(size[j-1][k]->value[m]);
					}
				}
				if(size[j].empty())
					break;
			}
		}
		for(j=0;j<nm[i];j++)
		{
			count=0;repeat=false;
			tempsize1=nature.size();
			for(k=0;k<tempsize1;k++)
			{
				tempsize2=nature[k]->value.size();
				for(m=0;m<tempsize2;m++)
				{
					if(nature[k]->value[m]==min[i][j])
					{
						count++;
						tempnature=k;
					}
				}
			}
			if(!print1.empty())
			{
				tempsize2=print1.size();
				for(k=0;k<tempsize2;k++)
					if(strcmp(print1[k]->bit,nature[tempnature]->bit)==0)
						repeat=true;
			}
			if(count==1&&repeat==false)
			{
				print1.push_back(new Logic);
				strcpy(print1.back()->bit,nature[tempnature]->bit);
				for(k=0;k<nature[tempnature]->value.size();k++)
					print1.back()->value.push_back(nature[tempnature]->value[k]);
			}
		}
		sort(print1.begin(),print1.end(),sort_by_bit);
		tempsize1=print1.size();
		for(j=0;j<tempsize1;j++)
		{
			for(k=0;k<nature.size();k++)
			{
				if(strcmp(print1[j]->bit,nature[k]->bit)==0)
					nature.erase(nature.begin()+k);
			}
		}
		short int **table=new short int*[nature.size()];//2为无关，0为未被覆盖，1为被覆盖
		tempsize1=nature.size();
		for(j=0;j<tempsize1;j++)
		{
			table[j]=new short int[max[i]+1];
			memset(table[j],0,(max[i]+1)*sizeof(short int));
			for(k=0;k<nature[j]->value.size();k++)
				table[j][nature[j]->value[k]]=1;
		}
		for(j=0;j<nm[i];j++)
			graph[min[i][j]]=1;
		tempsize1=print1.size();
		for(j=0;j<tempsize1;j++)
		{
			tempsize2=print1[j]->value.size();
			for(k=0;k<tempsize2;k++)
			{
				graph[print1[j]->value[k]]=0;
			}
		}
		//用BFS实现寻找最小项数的最大覆盖
		sum=0;
		for(j=0;j<nm[i];j++)
			sum+=graph[min[i][j]];
		queue.clear();
		if(sum!=0)
		{
			maxcover=0;
			tempsize1=nature.size();
			for(j=0;j<tempsize1;j++)
			{
				maxcover=0;
				for(k=0;k<nature[j]->value.size();k++)
				{
					if(table[j][nature[j]->value[k]]==1&&graph[nature[j]->value[k]]==1)
						maxcover++;
				}
				if(maxcover==sum) 
				{
					tempqueue=Queue();
					queue.push_back(tempqueue);
					queue.back().itself=j;
					break;
				}
			}
			if(!queue.empty())
			{
				print2.push_back(new Logic);
				strcpy(print2.back()->bit,nature[queue.front().itself]->bit);
			}
			else if(queue.empty())
			{
				for(j=0;j<nature.size();j++)
				{
					for(k=j+1;k<nature.size();k++)
					{
						tempqueue=Queue();
						queue.push_back(tempqueue);
						queue.back().source.push_back(j);
						queue.back().itself=k;
					}
				}
				for(ii=2;ii<=nature.size();ii++)//尝试覆盖的项数
				{
					for(j=0;j<queue.size();j++)
					{
						maxcover=0;cover=false;
						for(k=0;k<nm[i];k++)
						{
							if(graph[min[i][k]]==0) continue;
							cover=false;
							for(m=0;m<queue[j].source.size();m++)
							{
								if(table[queue[j].source[m]][min[i][k]]==1)
								{
									cover=true;
									break;
								}
							}
							if(cover==true) 
							{
								maxcover++;
								continue;
							}
							if(table[queue[j].itself][min[i][k]]==1)
							{
								cover=true;
								maxcover++;
							}
						}
						if(maxcover>=sum) break;
					}
					if(j<queue.size()) break;
					tempsize1=queue.size();
					for(k=0;k<tempsize1;k++)
					{
						for(m=queue.front().itself+1;m<nature.size();m++)
						{
							queue.push_back(queue.front());
							queue.back().source.push_back(queue.front().itself);
							queue.back().itself=m;
						}
						queue.erase(queue.begin());
					}
				}
				tempsize1=queue[j].source.size();
				for(jj=0;jj<tempsize1;jj++)
				{
					print2.push_back(new Logic);
					strcpy(print2.back()->bit,nature[queue[j].source[jj]]->bit);
				}
				print2.push_back(new Logic);
				strcpy(print2.back()->bit,nature[queue[j].itself]->bit);
			}
		}
		sort(print2.begin(),print2.end(),sort_by_bit);
		//for(j=0;j<(short)nature.size();j++)
		//{
		//	delete []table[j];table[j]=NULL;
		//}
		//delete []table;
		tempsize1=print2.size();
		for(j=0;j<tempsize1;j++)
		{
			print1.push_back(new Logic);
			strcpy(print1.back()->bit,print2[j]->bit);
		}
		tempsize1=print1.size();
		for(j=0;j<tempsize1;j++)
		{
			for(k=0;k<bit[i];k++)
			{
				if(print1[j]->bit[k]=='1') printf("%c",16+print1[j]->bit[k]+k);
				else if(print1[j]->bit[k]=='0') printf("%c\'",16+print1[j]->bit[k]+1+k);
				else continue;
			}
			if(j<tempsize1-1) printf("+");//cout<<'+';
		}
		printf("\n");
	}
	return 0;
}