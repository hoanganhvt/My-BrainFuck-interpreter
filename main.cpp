#include<bits/stdc++.h>

using namespace std;

#define ARRLENGTH 30000
typedef pair<int,int>II;

int CurrentIndex = 0;
int *arr;
bool haltCommand = false;
stack<II>loopStack;
void process(char c, int &i, int &j){
	if(c == '[' || c == ']'){
		if(c == '['){
			if(arr[CurrentIndex]){
				loopStack.push(II(i,j));
			}
			else{
				haltCommand = true;
			}
		}
		else{
			int curI = loopStack.top().first;
			int curJ = loopStack.top().second-1;
			loopStack.pop();
			if(!haltCommand){
				if(arr[CurrentIndex] != 0){
					i = curI;
					j = curJ;
				}
				else{
					haltCommand = false;
					return;
				}
			}
			else if(haltCommand && loopStack.empty()){
				haltCommand = false;
			}
		}
	}
	else{
		if(haltCommand) return;

		if(c == '+'){
			arr[CurrentIndex]++;
			if(arr[CurrentIndex] > 255) arr[CurrentIndex] = 0;
		}
		else if(c == '-'){
			arr[CurrentIndex]--;
			if(arr[CurrentIndex] < 0) arr[CurrentIndex] = 255;
		}
		else if(c == '>'){
			CurrentIndex = min(CurrentIndex+1, ARRLENGTH-1);
		}
		else if(c == '<'){
			CurrentIndex = max(CurrentIndex-1, 0);
		}
		else if(c == '.'){
			cout << (char)arr[CurrentIndex];
		}
	}
}

int main(int agrc, char **agrv){
	string fileName = agrv[1];
	ifstream inputFile(fileName);
	vector<string>data;
	arr = (int*)calloc(ARRLENGTH,sizeof(int));
	while(!inputFile.eof()){
		string tmp;
		inputFile >> tmp;
		data.push_back(tmp);
	}
	int i = 0;
	while(i < data.size()){
		int j = 0;
		while(j < data[i].length()){
			process(data[i][j], i, j);
			j++;
		}
		i++;
	}
	inputFile.close();
	return 0;
}
