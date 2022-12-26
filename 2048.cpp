#include<iostream>
#include<stdlib.h>              //����gotoxy�����ת���Ͻǣ�ÿ�����������һ�ε���� 
#include<windows.h>           //����HideCursor(); ���ع�� 
#include<time.h>            //����srand((unsigned)time(NULL)); ȡ����� 
#include<conio.h>          //getch() ��ͷ�ļ� 
using namespace std;
const int M =13;           //2��ָ��13����� 
const int N = 4;          // ������ 

int number[M];        //�����������ֵnumber[ loc[][] ] ->1~2048
int loc[N][N];       //���2��ָ��  0~12��һ������4��4�н��� 

void gotoxy(int x, int y);        // ���Ĵ��� 
void HideCursor();               //  ���Ĵ���


void Begin();                    //��Ϸ��ʼǰ��ʼ������ 
void Run();                      //��Ϸ���� 
void add();                      //�ƶ�һ����������� 

void up();                       //�ƶ����� 
void down();                    //�ƶ����� 
void left();                   //�ƶ����� 
void right();                 //�ƶ����� 

bool isgameover();            //��Ϸ�Ƿ���� 
bool iswin();                 //��Ϸ�Ƿ�ʤ�� 
void Print();                 //�������( number[ loc[i][j] ] ) 

int flag=0;                  //�ж�add����ֵ 
int score=0;                 //���� 



int main() //���������->��Ϸ��ʼǰ��ʼ������->��Ϸ���� 
{
	
	srand((unsigned)time(NULL));
	Begin();
	Run();
	return 0;
}
void Begin()  
{
	int i,j;
	int t =1;  //2��ָ�� 
	
	for(i=0;i<M;i++)
	{
		number[i]=t;
		t*=2;
	}//number��������������ֵ2~2048 

	int n=2; //��Ϸ��ʼ��������2��������������ֵ(0) 
	loc[N][N]={0};  
	for (i=0;i<n;i++)
	{
		int x = rand()%N;
		int y = rand()%N;
		// ���һ�����꣬����������λ�ñ��2��4 
		loc[x][y]=1;//���1����2��һ�η�������չ�ֵ���2 
	}
 		//loc[0][0]=11;// ����iswin���� 
/*	int j;
	for(i=0;i<3;i++)
	{
	    for(j=0;j<5;j++)
		{
	       printf("%d",loc[i][j]) ;
	  	}
	//����loc����ʼ��loc[][]��3��1 
	}*/
}
void Run()
{
	
			HideCursor();//���ع�� 
			Print();         //�����Ϸ�տ�ʼ�Ľ��� 
			
			
		
			switch (getch()) //���ͨ��wsad�����ƶ�����ʵ�������ƶ��ͺϲ� 
			{
				case 'w':up();break;
				case 's':down();break;
				case 'a':left();break;
				case 'd':right();break;
			}             //�ƶ������ڲ�������������(������� 2(90%)�� 4(10%) 
			while(!isgameover()) //�ж���Ϸ�Ƿ���� δ����һֱѭ�� 
			{
				gotoxy(0,0);      //���´�������ݸ����ϴ����� 
				Print();           //��� 
				if(iswin())         //�ж���Ϸ�Ƿ�ʤ�� 
				{
					cout<<"�ɹ�ͨ��!";//printf("�ɹ�ͨ�أ�");
					exit(0);           //������ֹ 
				}
				if(flag)
				{
					add();
					gotoxy(0,0);
					Print();
					flag=0;
				}
				switch (getch())   
				{
					case 'w':up();break;
					case 's':down();break;
					case 'a':left();break;
					case 'd':right();break;
				}
			}//isgameover��������trueʱ����ѭ�� 
			
		cout<<endl;        
		cout<<"Game Over!";
} 
void up() 
{
	int i,j;                 
	char sample[N][N];     
	for (i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			sample[i][j]=loc[i][j];
		}
	}       
	for(j=0;j<N;j++)      
	{
		
		int k=0;
		for(i=1;i<N;i++)  
		{
			if(loc[i-1][j]==0&&loc[k+1][j]==0&&loc[i][j]!=loc[k][j]&&loc[k][j]!=0)     
			{
				int d=loc[i][j];
				loc[i][j]=loc[k+1][j];
				loc[k+1][j]=d;
				
			}  					                                                   													                                               
			if(loc[i][j]!=0)  
			{
				if(loc[k][j]!=loc[i][j])
				{
					if(loc[k][j]==0)
					{
						int t =loc[i][j];
						loc[i][j]=loc[k][j];
						loc[k][j]=t;
						
						continue;
					}
					k++;
					
				}else
				{
					loc[k][j]++;
					score+=number[loc[k][j]];
					loc[i][j]=0;
					k++;
					
				}
			
			}
		}
		
	}
	for (i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if (sample[i][j]!=loc[i][j])
			{
				flag=1;
				break;
			}
		}
		if(flag)
		{
			break;
		}
	}
}
void down()
{
	int i,j;
	char sample[N][N];
	for (i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			sample[i][j]=loc[i][j];
		}
	}
	for(j=0;j<N;j++)
	{
		int k=N-1;
		for(i=N-2;i>=0;i--)
		{
			if(loc[i+1][j]==0&&loc[k-1][j]==0&&loc[i][j]!=loc[k][j]&&loc[k][j]!=0)
			{
				int d=loc[i][j];
				loc[i][j]=loc[k-1][j];
				loc[k-1][j]=d;
				
			}                                                                
			if(loc[i][j]!=0) 
			{
				if(loc[k][j]!=loc[i][j])
				{
					if(loc[k][j]==0)
					{
						int t =loc[i][j];
						loc[i][j]=loc[k][j];
						loc[k][j]=t;
						
						continue;
					}
					k--;
					
				}else
				{
					loc[k][j]++;
					score+=number[loc[k][j]];
					loc[i][j]=0;
					k--;
					
				}
			
			}
		}
	}
		for (i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if (sample[i][j]!=loc[i][j])
			{
				flag=1;
				break;
			}
		}
		if(flag)
		{
			break;
		}
	}
}
void left()//�������ƶ����������¡��ϡ������� 
{

	int i,j;
	char sample[N][N];
	for (i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			sample[i][j]=loc[i][j];
		}
	}			//sample�൱�ڱ����ƶ�ǰ�����֣����ں����ж�loc�Ƿ�仯���Ӷ��ж�add�����������������
	for(i=0;i<N;i++)  //�ӵ�һ�п�ʼ��ѭ��4�Σ��ӵ�һ�е������� 
	{                      //ÿһ�е�ִ�������ͬ 
		int k=0;  //�ȴ�����߿�ʼ������������(k��j)�ж��ƶ���ϲ� 
		for(j=1;j<N;j++)  //j���±굽�����ұ�ʱ���ж����һ�κ��˳�ѭ�� 
		{
			if(loc[i][j-1]==0&&loc[i][k+1]==0&&loc[i][j]!=loc[i][k]&&loc[i][k]!=0) //�����������Ӧ����4080 4008���͵����   
			{
				int d=loc[i][k+1];
				loc[i][k+1]=loc[i][j];                                    //4080->4080(j�±�ֵ��1)-> ����266��if����->4800->4800(j�±�ֵ��1) 
				loc[i][j]=d;
				
			}                                    									//�����������Ӧ����4080 4008�����               
			if(loc[i][j]!=0) //�����ؼ�   j�����λ���ϵ�����0������ k �жϣ�j�±������ƶ�һ��                    
			{ //j��λ���ϵĲ�Ϊ0  �� k ��ʼ�ж� 
				if(loc[i][k]!=loc[i][j])           //�� 2422-> 2422(k��j�±�ֵ����1) ->2422 (k��j�±�ֵ����1)->k��jλ��ֵ��ͬ->2440 
				{   // k �� j λ������ֵ�����
					if(loc[i][k]==0)
					{  
						int t =loc[i][j];
						loc[i][j]=loc[i][k];
						loc[i][k]=t;
						 // k Ϊ 0 �Ļ���k �� j ��ֵ�������� 
						continue; //��ִ��������䣬 k�±�ֵ���䣬j�±������ƶ� 
					}else
					{
						k++;    // k ��λ��ֵ��Ϊ0�Ļ� ��k�±������ƶ�һ�� 
					} 
					
					
				}else // kλ��ֵ����j��λ��ֵʱ  
				{
					loc[i][k]++;
					score+=number[loc[i][k]];  //�÷�����ֵ���ںϲ���� k ��λ��ֵ 
					loc[i][j]=0;            //j��λ��ֵ���0 
					k++;                    //k�±������ƶ�һ�� 
					//k��λ��ֵ��1���������ϲ���2��ָ����1 
				}
			
			}//ִ�е���ʱ��j���±������ƶ�1�� 
			
		}//ִ�е���ʱ��������1��ת�Ƶ���һ�У������ظ��Ϸ��ƶ��ϲ����� 
	
		
	}//273��299Ϊ����ĺ����������޷���4080��4008�����������ƶ��������� 266-272���Խ�4080��4008���4800 
		for (i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if (sample[i][j]!=loc[i][j])
			{//ֻҪ�ƶ��������ú���loc[]][]��ֵ�仯�ˣ�ϵͳ��Ҫ����1�� 2��4 
				flag=1;
				break;
			}
		}
		if(flag)
		{
			break;
		}
	}
}
void right()
{
	int i,j;
	char sample[N][N];
	for (i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			sample[i][j]=loc[i][j];
		}
	}
	
	for(i=0;i<N;i++)
	{
		int k=N-1;
		for(j=N-2;j>=0;j--)
		{
			if(loc[i][j+1]==0&&loc[i][k-1]==0&&loc[i][j]!=loc[i][k]&&loc[i][k]!=0)
			{
				int d=loc[i][k-1];
				loc[i][k-1]=loc[i][j];
				loc[i][j]=d;
				
			}                                                    
			if(loc[i][j]!=0) // 0 0 2 2                      4 0 0 0
			{
				if(loc[i][k]!=loc[i][j])
				{
					if(loc[i][k]==0)
					{
						int t =loc[i][j];
						loc[i][j]=loc[i][k];
						loc[i][k]=t;
						
						continue;
					}
					k--;
					
				}else
				{
					loc[i][k]++;
					score+=number[loc[i][k]];
					loc[i][j]=0;
					k--;
					
				}
			
			}
		}
		
	}
	for (i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if (sample[i][j]!=loc[i][j])
			{
				flag=1;
				break;
			}
		}
		if(flag)
		{
			break;
		}
	}
}

void Print()
{
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(loc[i][j]!=0)
			cout<<number[loc[i][j]]<<'\t';//printf("%d\t",number[loc[i][j]]);
			else
			cout<<'\t';//printf("\t");
			
			
		}//0�����
		cout<<"\n\n\n";//printf("\n\n\n");
	}
	cout<<"\n������"<<score;//printf("\n������%d",score);
}
void add()
{
	int i,j;
	do
	{
		i=rand()%N;
		j=rand()%N;
	}while(loc[i][j]!=0);//�ҳ����һ��λ��ֵΪ0��������Ϊ������ 
	
	if(rand()%10==1) //10%�ĸ��� 
	{
		loc[i][j]=2;
	}else//90%�ĸ���
	{
		loc[i][j]=1;
	}
		
		
		
		

		
}
bool isgameover()
{
	int i,j;

	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(loc[i][j]==0)
			{
				return false; //��ά�����ڻ���0���������Ȼû���������֣���Ϸ������ 
			}			
		}
	}
	

		return true;       //�����������ֺ��ٴε����ƶ�����������������û�з����仯����Ϸ����
		                     //��˴���һ�����⣬��������������ֺ�ֻ�������ƶ�ʱ���Ժϲ���
							 //��������������������ƶ�����ж���Ϸ���� 
	
}
bool iswin()
{
	int i,j;
	int x=0;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(loc[i][j]==11) //�������������ֱ��2048����Ϸʤ�� 
			{
				return true;
			}
		}
	}
	return false;
	
}

//�����ת
void gotoxy(int x, int y)//����������(x,y)��λ��
{
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle, pos);
}
//�������
void HideCursor()//���ع����ʾ
{
	CONSOLE_CURSOR_INFO cursor_info = {1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),& cursor_info);
}

