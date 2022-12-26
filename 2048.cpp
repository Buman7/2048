#include<iostream>
#include<stdlib.h>              //用于gotoxy光标跳转左上角，每次输出覆盖上一次的输出 
#include<windows.h>           //用于HideCursor(); 隐藏光标 
#include<time.h>            //用于srand((unsigned)time(NULL)); 取随机数 
#include<conio.h>          //getch() 的头文件 
using namespace std;
const int M =13;           //2的指数13种情况 
const int N = 4;          // 行列数 

int number[M];        //存放真正的数值number[ loc[][] ] ->1~2048
int loc[N][N];       //存放2的指数  0~12，一共构成4行4列界面 

void gotoxy(int x, int y);        // 光标的处理 
void HideCursor();               //  光标的处理


void Begin();                    //游戏开始前初始化界面 
void Run();                      //游戏运行 
void add();                      //移动一次随机新增数 

void up();                       //移动函数 
void down();                    //移动函数 
void left();                   //移动函数 
void right();                 //移动函数 

bool isgameover();            //游戏是否结束 
bool iswin();                 //游戏是否胜利 
void Print();                 //输出界面( number[ loc[i][j] ] ) 

int flag=0;                  //判断add返回值 
int score=0;                 //分数 



int main() //产生随机数->游戏开始前初始化工作->游戏运行 
{
	
	srand((unsigned)time(NULL));
	Begin();
	Run();
	return 0;
}
void Begin()  
{
	int i,j;
	int t =1;  //2的指数 
	
	for(i=0;i<M;i++)
	{
		number[i]=t;
		t*=2;
	}//number数组存放真正的数值2~2048 

	int n=2; //游戏开始出现两个2，其他坐标无数值(0) 
	loc[N][N]={0};  
	for (i=0;i<n;i++)
	{
		int x = rand()%N;
		int y = rand()%N;
		// 随机一组坐标，让坐标所在位置变成2或4 
		loc[x][y]=1;//这个1代表2的一次方，最终展现的是2 
	}
 		//loc[0][0]=11;// 调试iswin函数 
/*	int j;
	for(i=0;i<3;i++)
	{
	    for(j=0;j<5;j++)
		{
	       printf("%d",loc[i][j]) ;
	  	}
	//遍历loc，初始化loc[][]有3个1 
	}*/
}
void Run()
{
	
			HideCursor();//隐藏光标 
			Print();         //输出游戏刚开始的界面 
			
			
		
			switch (getch()) //玩家通过wsad调用移动函数实现数字移动和合并 
			{
				case 'w':up();break;
				case 's':down();break;
				case 'a':left();break;
				case 'd':right();break;
			}             //移动函数内部有新增数函数(随机出现 2(90%)或 4(10%) 
			while(!isgameover()) //判断游戏是否结束 未结束一直循环 
			{
				gotoxy(0,0);      //让下次输出内容覆盖上次内容 
				Print();           //输出 
				if(iswin())         //判断游戏是否胜利 
				{
					cout<<"成功通关!";//printf("成功通关！");
					exit(0);           //程序中止 
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
			}//isgameover函数返回true时跳出循环 
			
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
void left()//以向左移动举例，向下、上、右类似 
{

	int i,j;
	char sample[N][N];
	for (i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			sample[i][j]=loc[i][j];
		}
	}			//sample相当于保存移动前的数字，用于后续判断loc是否变化，从而判断add新增数函数返回情况
	for(i=0;i<N;i++)  //从第一行开始，循环4次，从第一行到第四行 
	{                      //每一行的执行情况相同 
		int k=0;  //先从最左边开始往右两个两个(k和j)判断移动或合并 
		for(j=1;j<N;j++)  //j的下标到达最右边时再判断最后一次后退出循环 
		{
			if(loc[i][j-1]==0&&loc[i][k+1]==0&&loc[i][j]!=loc[i][k]&&loc[i][k]!=0) //新增情况，可应对如4080 4008类型的情况   
			{
				int d=loc[i][k+1];
				loc[i][k+1]=loc[i][j];                                    //4080->4080(j下标值加1)-> 满足266行if条件->4800->4800(j下标值加1) 
				loc[i][j]=d;
				
			}                                    									//新增情况，可应对如4080 4008的情况               
			if(loc[i][j]!=0) //！！关键   j代表的位置上的若是0，不和 k 判断，j下标往右移动一格                    
			{ //j的位置上的不为0  与 k 开始判断 
				if(loc[i][k]!=loc[i][j])           //如 2422-> 2422(k和j下标值均加1) ->2422 (k和j下标值均加1)->k和j位置值相同->2440 
				{   // k 和 j 位置所在值不相等
					if(loc[i][k]==0)
					{  
						int t =loc[i][j];
						loc[i][j]=loc[i][k];
						loc[i][k]=t;
						 // k 为 0 的话，k 和 j 的值发生互换 
						continue; //不执行下列语句， k下标值不变，j下标向右移动 
					}else
					{
						k++;    // k 的位置值不为0的话 ，k下标向右移动一格 
					} 
					
					
				}else // k位置值等于j的位置值时  
				{
					loc[i][k]++;
					score+=number[loc[i][k]];  //得分增加值等于合并后的 k 的位置值 
					loc[i][j]=0;            //j的位置值变成0 
					k++;                    //k下标向右移动一格 
					//k的位置值加1，即发生合并，2的指数加1 
				}
			
			}//执行到这时，j的下标向右移动1格 
			
		}//执行到这时，行数加1，转移到下一行，继续重复上方移动合并操作 
	
		
	}//273到299为最初的函数，后发现无法将4080或4008这种类型数移动，后新增 266-272可以将4080或4008变成4800 
		for (i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if (sample[i][j]!=loc[i][j])
			{//只要移动函数调用后若loc[]][]的值变化了，系统需要新增1个 2或4 
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
			
			
		}//0不输出
		cout<<"\n\n\n";//printf("\n\n\n");
	}
	cout<<"\n分数："<<score;//printf("\n分数：%d",score);
}
void add()
{
	int i,j;
	do
	{
		i=rand()%N;
		j=rand()%N;
	}while(loc[i][j]!=0);//找出随机一个位置值为0的坐标作为新增数 
	
	if(rand()%10==1) //10%的概率 
	{
		loc[i][j]=2;
	}else//90%的概率
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
				return false; //二维数组内还有0代表界面仍然没有填满数字，游戏不结束 
			}			
		}
	}
	

		return true;       //界面填满数字后再次调用移动函数，若界面数字没有发生变化，游戏结束
		                     //因此存在一个问题，例如界面填满数字后只有向上移动时可以合并，
							 //但如果向另外三个方向移动后会判断游戏结束 
	
}
bool iswin()
{
	int i,j;
	int x=0;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(loc[i][j]==11) //界面内若有数字变成2048，游戏胜利 
			{
				return true;
			}
		}
	}
	return false;
	
}

//光标跳转
void gotoxy(int x, int y)//将光标调整到(x,y)的位置
{
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle, pos);
}
//光标隐藏
void HideCursor()//隐藏光标显示
{
	CONSOLE_CURSOR_INFO cursor_info = {1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),& cursor_info);
}

