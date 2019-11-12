#include <iostream>
#include <cstring>
#include <string>
using namespace std;

//这是把中缀表达式转化成后缀表达式的类 
class Transform{
	private:
		char* str;
		int top;
		int size;
	public:
		//表达式求值的构造函数 
		Transform(int size){
			this->size = size;
			str = new char[size];
			top = -1;
		}
		
		//栈是否为空的函数
		bool IsEmpty(){
			return top == -1;
		}
		
		//栈是否已满的函数
		bool IsFull(){
			return top == this->size-1;
		}
		
		//入栈函数
		void Push(char ch){
			if(!this->IsFull()){
				this->str[++top] = ch;	
			}
		}
		
		//获得栈顶元素 
		char Top(){
			return this->str[top];
		}
		
		//出栈函数
		void Pop(){
			this->top--;
		} 
		
		//栈外运算符优先级 
		int icp(char ch){
			int result = 0;
			if(ch == '#'){
				result = 0;
			}
			if(ch == '('){
				result = 6;
			}
			if(ch == '*'||ch == '/'){
				result = 4;
			}
			if(ch == '+'||ch == '-'){
				result = 2;
			}	
			if(ch == ')'){
				result = 1;
			}
			return result;		
		}
		
		//栈内运算符优先级 
		int isp(char ch){
			int result = 0;
			if(ch == '#'){
				result = 0;
			}
			if(ch == '('){
				result = 1;
			}
			if(ch == '*'||ch == '/'){
				result = 5;
			}
			if(ch == '+'||ch == '-'){
				result = 3;
			}	
			if(ch == ')'){
				result = 6;
			}
			return result;		
		}
		
		//中缀表达式转为后缀表达式函数
		string Transform_Median(string median){
			//在中缀表达式和栈中追加"#"表示结束 
			median.append("#"); 
			this->Push('#');
			char* c;
			int cnt = 0;
			char* tmp;
			c = new char[median.length()];
			tmp = new char[median.length()];			//后缀表达式的暂存数组 
			strcpy(c,median.c_str());
			for(int i = 0 ; i < median.length() ; i++){
				//如果是数字直接输出到后缀表达式中 
				if(c[i] >= '0' && c[i] <= '9'){
					tmp[cnt++] = c[i];
				}else{
					//如果不是数字，则需要和栈顶元素比较运算符优先级 
					char ch = this->Top();
					//栈顶元素在栈内的优先级比栈外元素的优先级高,则栈外元素入栈 
					if(this->isp(ch) < this->icp(c[i])){
						this->Push(c[i]); 
					}else if(this->isp(ch) > this->icp(c[i])){
						//栈顶元素在栈内的优先级比栈外元素的优先级低
						//则栈内元素出栈,并输出到后缀表达式中,循环变量减1 
						tmp[cnt++] = ch;
						this->Pop();
						i--;
					}else{
						//栈顶元素在栈内的优先级等于栈外元素的优先级
						//说明已经运行到“#”，则出栈即可 
						this->Pop();	
					}
				}
			}
			//返回中缀表达式的字符串 
			string after = string(tmp,cnt);
			return after;
		}	
}; 

//这是后缀表达式计算类 
class Sum{
	private:
		int* sum;
		int top;
		int size;
	public:
		//表达式求值的构造函数 
		Sum(int size){
			this->size = size;
			sum = new int[size];
			top = -1;
		}
		
		//栈是否为空的函数
		bool IsEmpty(){
			return top == -1;
		}
		
		//栈是否已满的函数
		bool IsFull(){
			return top == this->size-1;
		}
		
		//入栈函数
		void Push(int num){
			if(!this->IsFull()){
				this->sum[++top] = num;	
			}
		}
		
		//获得栈顶元素 
		int Top(){
			return this->sum[top];
		}
		
		//出栈函数
		void Pop(){
			this->top--;
		} 
		
		//后缀表达式求和
		int Sum_After(string after){
			char* s;
			s = new char[after.length()];
			strcpy(s,after.c_str());
			for(int i = 0 ; i < after.length() ; i++){
				if(s[i] >= '0' && s[i] <= '9'){
					this->Push(s[i]-'0');
				}else{
					int b = this->Top();
					this->Pop();
					int a = this->Top();
					this->Pop();
					int result = 0;
					switch(s[i]){
						case '+': result = a + b ;break;
						case '-': result = a - b ;break;
						case '*': result = a * b ;break;
						case '/': result = a / b ;break;
					};
					this->Push(result);
				}
			}
			return this->Top();
		} 
};


int main()
{
	string median;
	cout<<"请输入中缀表达式："<<endl;
	cin>>median;
	Transform transform(median.length());
	string after = transform.Transform_Median(median);
	cout<<"后缀表达式为："<<endl<<after<<endl;
	Sum sum(after.length()); 
	int result = sum.Sum_After(after);
	cout<<"结果为："<<endl<<result<<endl; 
	
	return 0;
 } 
